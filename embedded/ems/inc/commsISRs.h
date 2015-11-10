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
 * @file commsISRs.h
 * @ingroup allHeaders
 * @brief 
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_COMMS_ISRS_H_SEEN
#define FILE_COMMS_ISRS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
/* If fail on warning is off, remove the definition such that we can redefine
 * correctly. */
#undef EXTERN
#endif


#ifdef COMMSISRS_C
#define EXTERN
#else
#define EXTERN extern
#endif


/* SCISR1 register fields
 *
 * From left most/most significant to right most/least significant.
 *
 * Abrev  Description			Actions/Meaning
 * TRDE - Transmit Data Register Empty	- Load with more data if there is any			- Main Flag
 * TC   - Transmit Complete		- Nothing being sent and nothing loaded ready		- unused
 * RDRF - Receive Data Register Full	- Store data in buffer until packet complete		- Main Flag
 * IDLE - Idle Line			- Receive line is quiet					- unused
 * OR   - Overrun			- Discard partial data received and increment counter
 * NF   - Noise Flag			- Discard partial data received and increment counter
 * FE   - Framing Error			- Discard partial data received and increment counter
 * PF   - Parity Error			- Discard partial data received and increment counter
 *
 * SCISR1 flag masks */
#define SCISR1_TX_REGISTER_EMPTY	BIT7
#define SCISR1_TX_COMPLETE			BIT6
#define SCISR1_RX_REGISTER_FULL		BIT5
#define SCISR1_RX_IDLE_LINE			BIT4
#define SCISR1_RX_OVERRUN			BIT3
#define SCISR1_RX_NOISE				BIT2
#define SCISR1_RX_FRAMING			BIT1
#define SCISR1_RX_PARITY			BIT0


/* TX/RX state variables */
EXTERN unsigned char	TXByteEscaped;
EXTERN unsigned char	RXCalculatedChecksum;


#undef EXTERN

#else
/* let us know if we are being untidy with headers */
#warning "Header file COMMS_ISRS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
