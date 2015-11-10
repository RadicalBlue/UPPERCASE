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
 * @file errorDefines.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief Error ID hash defines
 *
 * This file contains all error codes for propagation up and out to a PC.
 * When adding new codes, ensure that they are unique and also that you
 * group them appropriately in ranges for easy visual identification.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */
/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_ERRORDEFINES_H_SEEN
#define FILE_ERRORDEFINES_H_SEEN


/** @todo TODO Introduce some structure to the numbering such that they can be
 * interpreted somewhat without a chart */

// A OK Nothing is wrong No error error.
#define NO_PROBLEMO						0x0666

/* Unconfigured options */
#define IAT_NOT_CONFIGURED_CODE			0x1000
#define CHT_NOT_CONFIGURED_CODE			0x1001
#define TPS_NOT_CONFIGURED_CODE			0x1002
#define EGO_NOT_CONFIGURED_CODE			0x1003
#define BRV_NOT_CONFIGURED_CODE			0x1004
#define MAP_NOT_CONFIGURED_CODE			0x1005
#define AAP_NOT_CONFIGURED_CODE			0x1006
#define MAT_NOT_CONFIGURED_CODE			0x1007
#define EGO2_NOT_CONFIGURED_CODE		0x1008
#define IAP_NOT_CONFIGURED_CODE			0x1009
#define LOAD_NOT_CONFIGURED_CODE		0x100A
#define AIRFLOW_NOT_CONFIGURED_CODE		0x100B
#define BPW_NOT_CONFIGURED_CODE			0x100C


/* Badly configured options */
#define VE_TABLE_MAIN_LOAD_LENGTH_TOO_LONG	0x2000
#define VE_TABLE_MAIN_RPM_LENGTH_TOO_LONG	0x2001
#define VE_TABLE_MAIN_MAIN_LENGTH_TOO_LONG	0x2002
#define BRV_MAX_TOO_LARGE					0x2003


/* Flash burning error codes */
#define sizeNotMultipleOfSectorSize		0x3000
#define sizeOfBlockToBurnIsZero			0x3001
#define smallBlockCrossesSectorBoundary	0x3002
#define addressNotSectorAligned			0x3003
#define addressNotWordAligned			0x3004
#define addressNotFlashRegion			0x3005
#define flashEraseFailed				0x3006
#define flashAccessError				0x3007
#define flashProtectionError			0x3008


// memory check error
#define MEMORY_WRITE_ERROR				0x3009

/* Communications error codes */
#define unimplementedFunction			0x4000
#define packetChecksumMismatch			0x4001
#define sourceAddressIsBroadcast		0x4002
#define sourceAddressIsDuplicate		0x4003
#define payloadLengthTypeMismatch		0x4004
#define payloadLengthHeaderMismatch		0x4005
#define invalidPayloadID				0x4006
#define unrecognisedPayloadID			0x4007
#define invalidMemoryActionForID		0x4008
#define invalidIDForMainTableAction		0x4009
#define invalidIDForTwoDTableAction		0x400A
#define noSuchAsyncDatalogType			0x400B
#define datalogLengthExceedsMax			0x400C
#define locationIDNotFound				0x400D
#define requestedRAMPageInvalid			0x400E
#define requestedFlashPageInvalid		0x400F
#define requestedLengthTooLarge			0x4010
#define requestedAddressDisallowed		0x4011

#define invalidAxisOrder				0 /* prevent parsing */
#define invalidAxisIndex				1 /* prevent parsing */

#define errorBaseMainTableRPM			0x6000
#define invalidMainTableRPMOrder		0x6000
#define invalidMainTableRPMIndex		0x6001
#define invalidMainTableRPMLength		0x6002
#define errorBaseMainTableLoad			0x6003
#define invalidMainTableLoadOrder		0x6003
#define invalidMainTableLoadIndex		0x6004
#define invalidMainTableLoadLength		0x6005
#define invalidMainTableMainLength		0x6006

#define errorBaseTwoDTableAxis			0x6010
#define invalidTwoDTableAxisOrder		0x6010
#define invalidTwoDTableIndex			0x6011


#else
/* let us know if we are being untidy with headers */
#warning "Header file ERRORDEFINES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
