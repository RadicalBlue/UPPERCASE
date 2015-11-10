/*
 * This file is part of EmsBench.
 *
 * Copyright 2015 University of Augsburg
 *
 * EmsBench is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EmsBench is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EmsBench.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * $Id: header-ems.c 480 2015-10-27 12:42:40Z klugeflo $
 * @file fuelAndIgnitionCalcs.c
 * @ingroup measurementsAndCalculations
 *
 * @brief Fuel and ignition calculations.
 *
 * This file contains all of the main fuel and ignition calculations based
 * upon the variables that we have already determined in previous stages.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#define FUELANDIGNITIONCALCS_C
#include "inc/freeEMS.h"
#include "inc/utils.h"
#include "inc/commsCore.h"
#include "inc/tableLookup.h"
#include "inc/DecoderInterface.h"
#include "inc/fuelAndIgnitionCalcs.h"


/** @brief Fuel and ignition calculations
 *
 * Using a variety of primary algorithms calculate a base pulsewidth and then
 * apply various corrections to it such as injector dead time, transient fuel
 * correction, engine temperature enrichment and per cylinder trims. The fuel
 * injection timing is also determined here.
 *
 * Calculate the ignition timing and dwell here too. Several corrections are
 * applied to these as well.
 *
 * @todo TODO implement the all of the ignition stuff and finish off all of the
 *       fuel injection stuff.
 * @todo TODO change the way configuration is done and make sure the most common
 *       options are after the first if().
 * @todo TODO add actual configuration options to the fixed config blocks for
 *       these items.
 *
 * @author Fred Cooke
 */
void calculateFuelAndIgnition() {
  /*&&&&&&&&&&&&& Perform the basic calculations one step at a time to get a
   * final pulsewidth &&&&&&&&&&&&*/

  if(TRUE /* Genuine method */) {
    unsigned short airInletTemp = CoreVars->IAT; /* All except MAF use this. */
    /* Determine the type of air flow data */
    if(TRUE /* SpeedDensity */) {
      /* This won't overflow until 512kPa or about 60psi of boost with 128% VE. */
      DerivedVars->AirFlow = ((unsigned long)CoreVars->MAP * DerivedVars->VEMain) / oneHundredPercentVE;
      /* Result is 450 - 65535 always. */
    }
    else
      if(FALSE /*AlphaN*/) {
	/* Not actually VE, but rather tuned air flow without density
	 * information */
        DerivedVars->AirFlow = DerivedVars->VEMain;
      }
      else
        if(FALSE /*MAF*/) {
          /* Just fix temperature at appropriate level to provide correct
           * Lambda */
          DerivedVars->AirFlow = CoreVars->MAF;
          /// @todo TODO figure out what the correct "temperature" is to make
          ///       MAF work correctly!
          // 293.15k is 20c * 100 to get value, so divide by 100 to get real
          // number
          airInletTemp = roomTemperature;
        }
        else
          if(FALSE /*FixedAF*/) {
            /* Fixed air flow from config */
            DerivedVars->AirFlow = fixedConfigs2.sensorPresets.presetAF;
          }
          else { /* Default to no fuel delivery and error */
            DerivedVars->AirFlow = 0;
            /* If anyone is listening, let them know something is wrong */
      //sendError(AIRFLOW_NOT_CONFIGURED_CODE); // or maybe queue it?
          }


    /* This won't overflow until well past 125C inlet, 1.5 Lambda and fuel as
     * dense as water */
    DerivedVars->densityAndFuel = (((unsigned long)((unsigned long)airInletTemp * DerivedVars->Lambda) / stoichiometricLambda) * fixedConfigs1.engineSettings.densityOfFuelAtSTP) / densityOfFuelTotalDivisor;
    /* Result is 7500 - 60000 always. */

    /* Divisors for air inlet temp and pressure :
     * #define airInletTempDivisor 100
     * #define airPressureDivisor 100
     * cancel each other out! all others are used. */


    DerivedVars->BasePW = (bootFuelConst * DerivedVars->AirFlow) / DerivedVars->densityAndFuel;
  }
  else
    if(FALSE /*configured*/) { /* Fixed PW from config */
      DerivedVars->BasePW = fixedConfigs2.sensorPresets.presetBPW;
    }
    else { /* Default to no fuel delivery and error */
      DerivedVars->BasePW = 0;
      /* If anyone is listening, let them know something is wrong */
//		sendError(BPW_NOT_CONFIGURED_CODE); // or maybe queue it?
    }

  /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




  /*&&&&&&&&&&&&& Apply All Corrections PCFC, ETE, IDT, TFC etc &&&&&&&&&&&&&&*/

  /* Apply the corrections after calculating */
  DerivedVars->EffectivePW = safeTrim(DerivedVars->BasePW, DerivedVars->TFCTotal);
  DerivedVars->EffectivePW = safeScale(DerivedVars->EffectivePW, DerivedVars->ETE);


  // the declaration of this variable is used in multiple loops below.
  unsigned char channel;

  /* "Calculate" the individual fuel pulse widths */
  for(channel = 0; channel < INJECTION_CHANNELS; channel++) {
    /// @todo TODO make injector channels come from config, not defines.
    /* Add or subtract the per cylinder fuel trims */
    unsigned short channelPW;
    channelPW = safeScale(DerivedVars->EffectivePW, TablesB.SmallTablesB.perCylinderFuelTrims[channel]);

    /* Add on the IDT to get the final value and put it into the array */
    injectorMainPulseWidthsMath[channel] = safeAdd(channelPW, DerivedVars->IDT);
  }

  /* Reference PW for comparisons etc */
  unsigned short refPW = safeAdd(DerivedVars->EffectivePW, DerivedVars->IDT);
  DerivedVars->RefPW = refPW;
  /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




  /*&&&& Based on IDT schedule PW start such that Fuel is correctly timed &&&&*/

  for(channel = 0; channel < INJECTION_CHANNELS; channel++) {
    /// @todo TODO make injector channels come from config, not defines.
    //injectorMainAdvances[channel] = IDT blah blah.
  }

  /* This will involve using RPM, injector firing angle and IDT to schedule the
   * events correctly */

  /** @todo TODO work needs to be done on scheduling before this can be
   *        completed. */

  /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




  /*&&&&&&&&&&&&&&&&&& Calculate Dwell and Ignition angle &&&&&&&&&&&&&&&&&&&&*/
  /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




  /*&& Based on Dwell and Ignition angle schedule the start and end of dwell &*/
  /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




  /*&&&&&&&&&&&&&&&&&&&& TEMPORARY (and old) &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

  /* "Calculate" the nominal total pulse width before per channel corrections */
  // FAK: FIXME - calculation of refPW yield 0 at another place and thus no more
  //              injections/ignitions are scheduled
  masterPulseWidth = 123;//refPW;//(ADCArrays->EGO << 6) + (ADCArrays->MAP >> 4);

  /* "Calculate" the individual fuel pulse widths */
  for(channel = 0; channel < INJECTION_CHANNELS; channel++) {
    injectorMainPulseWidthsMath[channel] = masterPulseWidth;
  }

  /// @todo TODO x 6 main pulsewidths, x 6 staged pulsewidths, x 6 flags for
  ///       staged channels if(coreSettingsA & STAGED_ON){}

  /* Set the staged status on or off (for now based on changeable settings) */
  if(fixedConfigs1.coreSettingsA & STAGED_ON) {
    coreStatusA |= STAGED_REQUIRED;
    /// @todo TODO determine the requirement for staged based on some sort of
    ///       map and or complex load based configuration.
  }
  else {
    coreStatusA &= STAGED_NOT_REQUIRED;
  }

  // temporary ign tests
  unsigned short intendedAdvance = ADCArrays->MAT << 6;
  unsigned short intendedDwell = intendedAdvance >> 1;

  short c;
  for(c=0; c<IGNITION_CHANNELS; c++) {
    ignitionAdvances[IGNITION_CHANNELS] = intendedAdvance;
  }
  *currentDwellMath = intendedDwell;

//	unsigned short minPeriod = ignitionMinimumDwell << 1;
  //	if(intendedDwell < ignitionMinimumDwell){
//		dwellLength = ignitionMinimumDwell;
//	}else{
//		dwellLength = intendedDwell;
//	}
//	if(intendedPeriod < minPeriod){
//		dwellPeriod = minPeriod;
//	}else{
//		dwellPeriod = intendedPeriod;
//	}
//	PITLD0 = dwellPeriod;

  /** @todo TODO Calculate the fuel advances (six of) */
  // just use one for all for now...
  totalAngleAfterReferenceInjection = (ADCArrays->TPS << 6);

  /** @todo TODO Calculate the dwell period (one of) */

  /** @todo TODO Calculate the ignition advances (twelve of) */

  /*&&&&&&&&&&&&&&&&&&&&&&&&&& TEMPORARY END &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
}
