/*
 * Copyright (c) 2012 NINTENDO.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions, and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NINTENDO AND ITS CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL NINTENDO OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF 
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
	This file coexists with GHS' time.h
	It's location allows inclusion via "sys/time.h", which is not the case
	for GHS' version of things. This file implements a super set. (in a sense)
*/

#ifndef TIME_H_
#define TIME_H_

// Pull in GHS' time.h
// (as the SDK also does this, we are forced to base this file on whatever is defined in there)
#include <time.h>

// ------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------------

struct timespec
  {
    long int tv_sec;            /* Seconds.  */
    long int tv_nsec;           /* Nanoseconds.  */
  };

#if defined(LGPL)
  struct timeval {
      unsigned long tv_sec;		// This needs to be unsigned so the matrix doesn't stop working in 2038.
      long tv_usec;				// Seriously, WebKit doesn't even run if the system clock is set to Jan 19, 2038 or later.
  };							// For more information, google "timeval 2038".
  
  typedef unsigned long fd_mask;
  
  typedef struct fd_set {
      fd_mask fd_bits;
  } fd_set;
#endif

// Januray 1, 1970 to January 1, 2000 in seconds
#define TIMESTAMP_DELTA 946684800

#define CLOCK_REALTIME 0

typedef void *timezone_ptr_t;

int gettimeofday(struct timeval *tv, timezone_ptr_t tz);
int utimes(const char *path, const struct timeval times[2]);
int nanosleep(const struct timespec *requested_time, struct timespec *remaining);

// defined in GHS' time.h -------------------------------------

struct tm *convertsecondstocalendar(const time_t *timer);
// ------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif

