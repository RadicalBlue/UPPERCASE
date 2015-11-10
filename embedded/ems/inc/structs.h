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
 * @file structs.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief General struct typedefs
 *
 * This file contains all of the general purpose and smaller struct typedefs.
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_STRUCTS_H_SEEN
#define FILE_STRUCTS_H_SEEN


/* For noobs: http://www.space.unibe.ch/comp_doc/c_manual/C/SYNTAX/struct.html
 *	      http://en.wikipedia.org/wiki/Composite_type
 *	      http://www.cs.usfca.edu/~wolber/SoftwareDev/C/CStructs.htm
 *	      http://sandbox.mc.edu/~bennet/cs220/codeex/struct_c.html
 */


/* Naming should be in the singular form such that the instantiation can be the
 * plural */


/* Types summary
 *
 * BEWARE : Be explicit!!
 *
 * char		8 bit (defaults to unsigned, but always specify signed/unsigned
 *                    anyway)
 * short	16 bit (defaults to signed, but always specify signed/unsigned
 *                     anyway)
 * int		16 bit DO NOT USE! (current compile flags make this 16 bits, but
 *                     a change of flags could will change your program if you
 *                     use this because they will all be 32 bit all of a sudden)
 * long		32 bit (defaults to signed, but always specify signed/unsigned
 *                     anyway)
 * long long	64 bit (inefficient, avoid these, if using : defaults to signed,
 *                     but always specify signed/unsigned anyway)
 * float	32 bit IEEE floating point numbers (inefficient, avoid these,
 *                     used fixed point math)
 * double	64 bit IEEE floating point numbers (inefficient, avoid these,
 *                     used fixed point math)
 */


// TODO various new structs
// Status struct
// Ignition struct
// Injection struct
// Engine position struct
// Validity flags, or they should be in the status struct?


/**
 * Addressable memory block description. This structure holds
 * the size, RAM page and address and flash page and address.
 * It is used for looking up the details of a memory block to
 * allow serial operations on RAM and flash data structures.
 */
typedef struct {
  unsigned char RAMPage;
  unsigned char FlashPage;
  void* RAMAddress;
  void* FlashAddress;
  unsigned short size;
} blockDetails;


#define DERIVED_VARS_SIZE sizeof(DerivedVar)
/* How many elements per array currently 2 at 25/6/08 */
#define DERIVED_VARS_WIDTH IN_OUT_BANKS
/* How large each element is in bytes (short = 2 bytes) */
#define DERIVED_VARS_UNIT 2
/* Use this block to make it easy to manage the derived variables */
typedef struct {
  /* Calculated from core vars */
  /* Configurable unit of load */
  unsigned short LoadMain;
//	unsigned short LoadSecondary;
  /* Divide by 512 to get % */
  unsigned short VEMain;
//	unsigned short VESecondary;
  /* Divide by 32768 to get Lamda */
  unsigned short Lambda;
  /* Top half of the equation */
  unsigned short AirFlow;
  /* Bottom half of the equation */
  unsigned short densityAndFuel;
  /* Raw PW before corrections */
  unsigned short BasePW;
  /* Additional PW for ETE correction */
  unsigned short ETE;
  /* Transient fuel correction PW (+/-) */
  signed short TFCTotal;
  /* Actual PW of fuel delivery */
  unsigned short EffectivePW;
  /* Minimum PW before fuel flow begins */
  unsigned short IDT;
  /* Reference electrical PW */
  unsigned short RefPW;
  /*  */
  unsigned short sp1;
  /*  */
  unsigned short sp2;
  /*  */
  unsigned short sp3;
  /*  */
  unsigned short sp4;
  /*  */
  unsigned short sp5;
} DerivedVar;


#define RUNTIME_VARS_SIZE sizeof(RuntimeVar)
/* How many runtime vars */
#define RUNTIME_VARS_LENGTH 13
/* How large each element is in bytes (short = 2 bytes) */
#define RUNTIME_VARS_UNIT 2
/* Use this block to manage the execution time of various functions loops and
 * ISRs etc */
typedef struct {
  /* Engine position and RPM code runtimes */
  unsigned short primaryInputLeadingRuntime;
  unsigned short primaryInputTrailingRuntime;
  unsigned short secondaryInputLeadingRuntime;
  unsigned short secondaryInputTrailingRuntime;

  /* Mathematics runtimes */
  unsigned short calcsRuntime;
  unsigned short genCoreVarsRuntime;
  unsigned short genDerivedVarsRuntime;
  unsigned short mathTotalRuntime;
  unsigned short mathSumRuntime;

  unsigned short RTCRuntime;

  /*  */
  unsigned short mainLoopRuntime;
  unsigned short logSendingRuntime;
  unsigned short serialISRRuntime;
} RuntimeVar;


#define ISR_LATENCY_VARS_SIZE sizeof(ISRLatencyVar)
/* How many latency vars */
#define ISR_LATENCY_VARS_LENGTH 2
/* How large each element is in bytes (short = 2 bytes) */
#define ISR_LATENCY_VARS_UNIT 2
/* Use this block to manage the execution time of various functions loops and
 * ISRs etc */
typedef struct {
  /* Engine position and RPM code latencies */
  unsigned short primaryInputLatency;
  unsigned short secondaryInputLatency;

  /* Injector latencies */
  unsigned short Injector1Latency;
  unsigned short Injector2Latency;
  unsigned short Injector3Latency;
  unsigned short Injector4Latency;
  unsigned short Injector5Latency;
  unsigned short Injector6Latency;

  unsigned short DwellLatency;
  unsigned short IgniteLatency;

  /* Not an ISR, but important none the less */
  unsigned short mathLatency;
  unsigned short mathSampleTimeStamp0;
  unsigned short mathSampleTimeStamp1;
} ISRLatencyVar;


#define CORE_VARS_SIZE sizeof(CoreVar)
/* How many arrays */
#define CORE_VARS_LENGTH 16
/* How large each element is in bytes (short = 2 bytes) */
#define CORE_VARS_UNIT 2
/* Use this block to make it easy to manage the core variables */
typedef struct {
  /* Calculated and averaged from ADC0 readings */

  /* Inlet Air Temperature (MAT JS):
   *  0.0 - 655.35  (0.01 Kelvin (/100))
   */
  unsigned short IAT;
  /* Coolant / Head Temperature (CLT JS):
   *  0.0 - 655.35  (0.01 Kelvin (/100))
   */
  unsigned short CHT;
  /* Throttle Position Sensor (TPS JS):
   *  0.0 - 102.39  (0.001? % (/640))
   */
  unsigned short TPS;
  /* Exhaust Gas Oxygen (O2 JS)	:
   * 0.000 - 1.999999	(0.0001? lambda (/32768))
   */
  unsigned short EGO;
  /* Manifold Absolute Pressure (5euroh1):
   *  0.0 - 655.35  (0.01 kPa (/100))
   */
  unsigned short MAP;
  /* Atmospheric Absolute Pressure (6euroh1) :
   *  0.0 - 655.35 (0.01 kPa (/100))
   */
  unsigned short AAP;
  /* Battery Reference Voltage (4euroh1):
   *  0.000 - 65.535  (0.001 Volts (/1000))
   */
  unsigned short BRV;
  /* Manifold Air Temperature (Spare JS):
   *  0.0 - 655.35  (0.01 Kelvin (/100))
   */
  unsigned short MAT;

  /* Calculated and averaged from ADC1 readings */

  /* Exhaust Gas Oxygen (NC):
   *  0.000 - 1.999999  (0.0001? lambda (/32768))
   */
  unsigned short EGO2;
  /* Intercooler Absolute Pressure (NC) :
   *  0.0 - 655.35  (0.01 kPa (/100))
   */
  unsigned short IAP;
  /* Mass Air Flow:
   *  0.0 - 65535.0 (raw units from lookup)
   */
  unsigned short MAF;

  /* Calculated from MAP and TPS history */

  /* Delta MAP kPa/second or similar */
  unsigned short DMAP;
  /* Delta TPS %/second or similar */
  unsigned short DTPS;

  /* Calculated from engine position data */

  /* Revolutions Per Minute (Calced):
   *  0 - 32767.5  (0.5 RPM (/2))
   */
  unsigned short RPM;
  /* Delta RPM (Calced):
   *  0 - 32767.5  (0.5 RPM/Second (/2))
   */
  unsigned short DRPM;
  /* Delta Delta RPM (Calced):
   * 0 - 32767.5  (0.5 RPM/Second^2 (/2))
   */
  unsigned short DDRPM;
} CoreVar;


#define ADC_ARRAY_SIZE sizeof(ADCArray)
/* How many arrays */
#define ADC_ARRAY_LENGTH 16
/* How large each element is in bytes (short = 2 bytes) */
#define ADC_ARRAY_UNIT 2
/* Use this block to ensure that the components are contiguous and we can then
 * reference them via offsets and pointers */
typedef struct {
  /* ADC0 raw readings */

  /* Inlet Air Temperature (MAT JS)
   *  COMPULSORY! */
  unsigned short IAT;
  /* Coolant / Head Temperature (CLT JS)
   *  COMPULSORY! */
  unsigned short CHT;
  /* Throttle Position Sensor (TPS JS)
   *  Reduced performance without */
  unsigned short TPS;
  /* Exhaust Gas Oxygen (O2 JS)
   *  Recommended */
  unsigned short EGO;
  /* Manifold Absolute Pressure (5euroh1)
   * COMPULSORY OR TPS OR MAF */
  unsigned short MAP;
  /* Atmospheric Absolute Pressure (6euroh1)
   *  Recommended */
  unsigned short AAP;
  /* Battery Reference Voltage (4euroh1)
   * COMPULSORY! */
  unsigned short BRV;
  /* Manifold Air Temperature (Spare JS)
   * Could help heat soak issues */
  unsigned short MAT;

  /* ADC1 raw readings */

  /* Exhaust Gas Oxygen (NC)
   *  V engine option */
  unsigned short EGO2;
  /* Intercooler Absolute Pressure (NC)
   * Turbo engine option */
  unsigned short IAP;
  /* Mass Air Flow (NC)
   * OEM engine option */
  unsigned short MAF;
  /* Spare ADC1 port 3 (NC)*/
  unsigned short SpareADC3;
  /* Spare ADC1 port 4 (NC)*/
  unsigned short SpareADC4;
  /* Spare ADC1 port 5 (NC)*/
  unsigned short SpareADC5;
  /* Spare ADC1 port 6 (NC)*/
  unsigned short SpareADC6;
  /* Spare ADC1 port 7 (NC)*/
  unsigned short SpareADC7;
} ADCArray;


#define MAINTABLE_SIZE sizeof(mainTable)
/* How many cells on the X axis */
#define MAINTABLE_RPM_LENGTH 24
/* How many cells on the Y axis */
#define MAINTABLE_LOAD_LENGTH 19
/* How many cells on the X axis max */
#define MAINTABLE_MAX_RPM_LENGTH 27
/* How many cells on the Y axis max */
#define MAINTABLE_MAX_LOAD_LENGTH 21
/* 924B 462 shorts maximum main table length */
#define MAINTABLE_MAX_MAIN_LENGTH 462


/**	@struct maintable
 *
 * @brief Main Table Structure definition
 *
 * Use this block to manage the main VE, Lambda and Timing tables. Tables can
 * be made any size from 1x1 to 27x17 or 22x21 provided that the multiple of
 * the two doesn't exceed the max main length and neither axis exceeds it's
 * specified maximum.
 *
 * Currently the following tables use this structure:
 * - VETableMainFlash;
 * - VETableSecondaryFlash;
 * - VETableTertiaryFlash;
 * - LambdaTableFlash;
 * - IgnitionAdvanceTableMainFlash;
 * - IgnitionAdvanceTableSecondaryFlash;
 * - InjectionAdvanceTableMainFlash;
 * - InjectionAdvanceTableSecondaryFlash;
 * - VETableMainFlash2;
 * - VETableSecondaryFlash2;
 * - VETableTertiaryFlash2;
 * - LambdaTableFlash2;
 * - IgnitionAdvanceTableMainFlash2;
 * - IgnitionAdvanceTableSecondaryFlash2;
 * - InjectionAdvanceTableMainFlash2;
 * - InjectionAdvanceTableSecondaryFlash2;
 *
 * For a more detailed discussion of how this structure is actually used...
 *
 * @see lookupPagedMainTableCellValue
 *
 * @author Fred Cooke
 */
typedef struct {
  /* The length of the RPM axis array */
  unsigned short RPMLength;
  /* The length of the Load axis array */
  unsigned short LoadLength;
  /* The array of RPM (X) axis values */
  unsigned short RPM[MAINTABLE_MAX_RPM_LENGTH];
  /* The array of Load (Y) axis values */
  unsigned short Load[MAINTABLE_MAX_LOAD_LENGTH];
  /* The table as an array of values */
  unsigned short Table[MAINTABLE_MAX_MAIN_LENGTH];
} mainTable;


#define TWODTABLEUS_SIZE sizeof(twoDTableUS)
#define TWODTABLEUS_LENGTH 16
/* This block used for various curves */
typedef struct {
  unsigned short Axis[TWODTABLEUS_LENGTH];
  unsigned short Values[TWODTABLEUS_LENGTH];
} twoDTableUS;


#define TWODTABLESS_SIZE sizeof(twoDTableSS)
#define TWODTABLESS_LENGTH 16
/* This block used for various curves */
typedef struct {
  signed short Axis[TWODTABLESS_LENGTH];
  signed short Values[TWODTABLESS_LENGTH];
} twoDTableSS;


#define TWODTABLEMS_SIZE sizeof(twoDTableMS)
#define TWODTABLEMS_LENGTH 16
/* This block used for various curves */
typedef struct {
  unsigned short Axis[TWODTABLEMS_LENGTH];
  signed short Values[TWODTABLEMS_LENGTH];
} twoDTableMS;


#define TWODTABLEUC_SIZE sizeof(twoDTableUC)
#define TWODTABLEUC_LENGTH 8
/* This block used for various curves */
typedef struct {
  unsigned char Axis[TWODTABLEUC_LENGTH];
  unsigned char Values[TWODTABLEUC_LENGTH];
} twoDTableUC;


#define COUNTER_SIZE sizeof(Counter)
/* How many counters */
#define COUNTER_LENGTH 21
/* How large each element is in bytes (short = 2 bytes) */
#define COUNTER_UNIT 2
/* Use this block to manage the execution count of various functions loops and
 * ISRs etc */
typedef struct {
  /* Event Counters (all require init to zero) */

  /* Counter to ensure we aren't accidentally triggering unused ISRs*/
  unsigned short callsToUISRs;
  /* Counter for low voltage conditions	*/
  unsigned short lowVoltageConditions;

  /* Counter for number of lost crank syncs*/
  unsigned short crankSyncLosses;
  /* Counter for number of lost cam syncs*/
  unsigned short camSyncLosses;
  /* Counter for number of lost RPM validity events*/
  unsigned short RPMValidityLosses;
  /* Counter for number of primary teeth dropped due to no primary sync	*/
  unsigned short primaryTeethDroppedFromLackOfSync;
// TODO remove the one above this line about teeth dropped???? probably...

  /* Free running counters for number of teeth seen such that...*/
  unsigned short primaryTeethSeen;
  /* ...tooth timing can be used to reconstruct the signal at lower rpm	*/
  unsigned short secondaryTeethSeen;
  /* Incremented each time a syncronous ADC reading is taken*/
  unsigned short syncedADCreadings;
  /* Incremented for each ADC reading in RTC because of timeout	*/
  unsigned short timeoutADCreadings;
  /* Incremented for each time the fuel and ign calcs are done*/
  unsigned short calculationsPerformed;
  /* Incremented for each time we send out a log entry*/
  unsigned short datalogsSent;

  /* UART/serial specific counters */

  /* Incremented when a start byte is found inside a packet*/
  unsigned short serialStartsInsideAPacket;
  /* Incremented when an escape is found but not followed by an escapee	*/
  unsigned short serialEscapePairMismatches;
  /* Incremented when the buffer fills up before the end*/
  unsigned short serialPacketsOverLength;
  /* Incremented when noise is detected*/
  unsigned short serialNoiseErrors;
  /* Incremented when an overrun occurs	*/
  unsigned short serialOverrunErrors;
  /* Incremented when a framing error occurs*/
  unsigned short serialFramingErrors;
  /* Incremented when a parity error occurs*/
  unsigned short serialParityErrors;

  /* Generic com counters */

  /* Incremented when calculated checksum did not match the received one*/
  unsigned short commsChecksumMismatches;
  /* Incremented when a debug message can't be sent due to the TX buffer  */
  unsigned short commsDebugMessagesNotSent;
  /* Incremented when an error message can't be sent due to the TX buffer */
  unsigned short commsErrorMessagesNotSent;
} Counter;


#define CLOCK_SIZE sizeof(Clock)
/* How many clocks */
#define CLOCK_LENGTH 9
/* How large each element is in bytes (short = 2 bytes) */
#define CLOCK_UNIT 2
/* Use this block to manage the various clocks kept */
typedef struct {
  /* Real Time and other Clocks (all require init to zero) */

  /* Variable to count RTI executions, 0.125ms exactly	*/
  unsigned short realTimeClockMain;
  /* Variable to count milliseconds exactly */
  unsigned short realTimeClockMillis;
  /* Variable to count tenths of a second exactly */
  unsigned short realTimeClockTenths;
  /* Variable to count seconds exactly */
  unsigned short realTimeClockSeconds;
  /* Variable to count minutes exactly */
  unsigned short realTimeClockMinutes;
  /* Roll-over variable for counting tenths */
  unsigned short millisToTenths;
  /* Roll-over variable for counting seconds */
  unsigned short tenthsToSeconds;
  /* Roll-over variable for counting minutes*/
  unsigned short secondsToMinutes;
  /* Timeout clock/counter for synced ADC readings*/
  unsigned short timeoutADCreadingClock;
} Clock;


#else
/* let us know if we are being untidy with headers */
#warning "Header file STRUCTS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
