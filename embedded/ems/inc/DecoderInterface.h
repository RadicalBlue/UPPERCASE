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
 * @file DecoderInterface.h
 * @ingroup allHeaders
 * @brief Objects through which a decoder communicates.
 *
 * This file contains the declarations of objects used as a common interface
 * between all of the different wheel decoders and the main loop scheduler.
 *
 * <h> original author</h> Fred Cooke
 * @author Andreas Meixner, Claudius Heine,
 * Florian Kluge <kluge@informatik.uni-augsburg.de>
 *
 * This file is based on the original FreeEMS 0.1.1 code by Fred Cooke.
 */
/* Header file multiple inclusion protection courtesy eclipse Header Template*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual*/
#ifndef FILE_DECODER_INTERFACE_H_SEEN
#define FILE_DECODER_INTERFACE_H_SEEN


// RPM Calculations:
//
// Either need a per decoder function that is called from the main loop OR...
// RPM calculation is done in real time inside one of the RPM interrupts OR...
// The choice of either, up to the decoder to decide how it is done, in this
// case the function can either do nothing, or swap some pointers/var values
// around or similar.

// MAP Sampling:
//
// Max number of samples = max number of cylinders, has to be handled by decoder
// due to potential mismatch between wheel pattern and cylinder firing pattern.

// Scheduling:
//
// arrays of output channels, iterate and check for wheel event number, if
// matched, fire: doesn't allow for firing a pin more than once a cycle!! no use
// allows multi channel on a single wheel event (virtually useless) but is slow,
// one loop and array per type of output channel.
//
// array of wheel events, do lookup for wheel event, then if output channel
// valid, schedule it. single channel per tooth event (acceptable, wire in
// parallel if required), fast, memory hog, need one array per type of channel,
// array length = max expected tooth count! do we need to support every single
// tooth on a nissan 360 style decoder or just cyl event count, what about
// porsche 130? next stop is 60, seems good. can we use bit-fields to save
// memory, 1 bit = 2 possible pins, 2 bits = 4, etc, this will be slower,
// though. probably just an unsigned char[]


// TODO @todo the below vars are just drafts so far, nothing is used, except the
// RPM stuff which I migrated here from the main header. More work to come.
// not teeth, teeth is misleading - could be leading or trailing edge or both
#define numberOfWheelEvents 1
unsigned char currentWheelEvent; // Current or last wheel event index.
// For logging wheel patterns as observed. LOTS of memory :-/ may not be
// possible except by sending lastStamp rapidly at low RPM
unsigned long wheelEventTimeStamps[numberOfWheelEvents];
// final output variable, probably move into inputVars struct?
unsigned short* RPM;
// intermediate storage variable, do something with this?
unsigned short* RPMRecord;
unsigned char ignitionEvents[6];
unsigned char injectionEvents[12];
unsigned char ADCSampleEvents[12]; // ???
unsigned char stagedInjectionEvents; // ???
unsigned char chickenCookerEvents; //  ???


// Init routine:
//
// Allow configuration of timer details? tick size? If so, need to introduce
// scaling to calcs to produce correct tick count and therefore pulsewidth.
// Migrate dead time to time units and scale to get ticks to add to final pw.
//
// We require some configuration to allow the Nissan style decoder to use the
// pulse accumulators to count those one degree slots accurately to a high rpm
// without excessive cpu load.


// move the following to  fuel calcs or sched code header, it doesn't belong
// here...
// stuff to do with timing and sync etc. ie, figuring out upon which



#else
/* let us know if we are being untidy with headers */
#warning "Header file DECODER_INTERFACE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
