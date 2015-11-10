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
 * @file FixedConfig1.c
 * @ingroup dataInitialisers
 *
 * @brief First fixed config block
 *
 * This file contains the definition of the first fixed configuration block.
 * The declaration can be found in the global constants header file.
 *
 * Please ensure that all variables added here have good default values.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

#include "inc/freeEMS.h"


/// @todo TODO for coreSettingsA masks See definitions in freeEMS.h OR is it in
///       structs.h ???
/// @todo TODO divide fixedConfig1 into useful chunks
/// @todo TODO create presets sensor values struct
/// @todo TODO create engine setup struct
/// @todo TODO create ranges struct
/// @todo TODO add userTextField1 to the dictionary/address lookup


/** @copydoc fixedConfig1 */
const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {

  {
    typicalCylinderSize,    	/* perCylinderVolume */
    stoichiometricAFROctane,	/* stoichiometricAFR */
    typicalInjectorSize,    	/* injectorFlow */
    densityOfOctane,        	/* densityOfFuelAtSTP */
    /* new and old.... */
    575,                  	/* capacityOfAirPerCombustionEvent */
    192,                  	/* perPrimaryInjectorChannelFlowRate */
    192,                  	/* perSecondaryInjectorChannelFlowRate */
    6,                    	/* ports */
    6,                    	/* coils */
    6,                    	/* combustionEventsPerEngineCycle */
    2,                    	/* revolutionsPerEngineCycle */
    24,                   	/* primaryTeeth */
    0                    	/* missingTeeth */
  },

  {
    divisorFor115200bps,  	/* baudDivisor */
    1                    	/* networkAddress */
  },

  {
    tachoTickFactor4at50, 	/* tachoTickFactor */
    tachoTotalFactor4at50	/* tachoTotalFactor */
  },

  0x07F0,                 	/* coreSettingsA */

  {"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but more won't be possible later!!"}
};
