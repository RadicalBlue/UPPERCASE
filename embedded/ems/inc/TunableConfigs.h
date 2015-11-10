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
 * @file TunableConfigs.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Struct typedefs for tunable configuration
 *
 * This file contains both the struct data type definitions and the arrays of
 * default values for small tables. Place reusable definitions of default table
 * values in here such that they can be used in multiple tunable table
 * definitions.
 *
 * You should add your configuration item here if it is best that it is adjusted
 * with instant results on a running engine. For everything else, please
 * consider placing it in one of the fixed configuration structs.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_TUNABLE_CONFIGS_H_SEEN
#define FILE_TUNABLE_CONFIGS_H_SEEN


/** An array of 16 zeros to fill out currently unused tables. */
#define ARRAY_OF_16_ZEROS    	{    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0}
/** An array of 16 scaled voltages for use as axes. */
#define ARRAY_OF_16_VOLTAGES 	{ 6000,  7200,  8400,  9000,  9600, 10200, 10800, 11400, 12000, 12600, 13200, 13800, 14400, 17800, 21000, 24500}
/** An array of 16 dwell times in native ticks. */
#define ARRAY_OF_16_DWELLS   	{10913,  8625,  6975,  6375,  5925,  5513,  5213,  4875,  4613,  4313,  4106,  3900,  3713,  2850,  2138,  1500}
/** An array of 16 injector dead times in native ticks. */
#define ARRAY_OF_16_DEADTIMES	{ 3638,  2875,  2325,  2125,  1975,  1838,  1738,  1625,  1538,  1438,  1369,  1300,  1238,   950,   713,   500}
/** An array of 16 temperatures in Kelvin. */
#define ARRAY_OF_16_TEMPS		{24315, 25315, 26315, 27315, 28315, 29315, 30315, 31315, 32315, 33315, 34315, 35315, 36315, 37315, 38315, 39315}
/** An array of 16 percentages for temperature based enrichment. */
#define ARRAY_OF_16_PERCENTS	{49152, 47513, 45875, 44237, 42598, 40960, 39321, 37683, 36045, 34406, 33587, 32768, 32768, 34406, 36045, 39321}
/** Any array of 16 RPM values forAxis values for use as axes. TODO fill out values */
#define ARRAY_OF_16_RPMS     	{    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0}
/** An array of 6 percentage fuel trims, the value is 100%. */
#define ARRAY_OF_6_FUEL_TRIMS	{32768, 32768, 32768, 32768, 32768, 32768}


/**
 * One of four structs of live tunable data such as small tables and fuel trims
 * etc. If you add something here, please ensure you update all of the following
 * - Default values in the initial definitions in TunableConfig.c and
 *   TunableConfig2.c
 * - The address values within the initPagedRAMTune() function in init.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 *
 * @todo TODO add doxy comments for each element of the struct
 */
typedef struct {
  twoDTableUS dwellDesiredVersusVoltageTable;
  twoDTableUS injectorDeadTimeTable;
  twoDTableUS postStartEnrichmentTable;
  twoDTableUS engineTempEnrichmentTableFixed;
  /// @todo TODO define units. perhaps micro litres (cubic milli meters) would
  //        be good, 5 - 100 seem to be the norm 327.68 = 65535/200
  twoDTableUS primingVolumeTable;
  twoDTableUS engineTempEnrichmentTablePercent;
  twoDTableUS dwellMaxVersusRPMTable;
  unsigned char filler[576];
} SmallTables1;


/** @copydoc SmallTables1 */
typedef struct {
  /* Trims for injection, from 0% to 200% of base */
  unsigned short perCylinderFuelTrims[INJECTION_CHANNELS];
  unsigned char filler[1012];
} SmallTables2;


/** @copydoc SmallTables1 */
typedef struct {
  unsigned char filler[1024];
} SmallTables3;


/** @copydoc SmallTables1 */
typedef struct {
  unsigned char filler[1024];
} SmallTables4;


#else
/* let us know if we are being untidy with headers */
#warning "Header file TUNABLE_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
