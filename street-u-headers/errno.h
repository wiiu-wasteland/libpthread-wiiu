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

#ifndef _ERRNO_H_
#define _ERRNO_H_

// -----------------------------------------------------------------------
// Thread safe errno access

#ifdef __cplusplus
extern "C" {
#endif
//int *__gh_errno_ptr(void);
extern int *shim_GetErrnoPtr(void);
#ifdef __cplusplus
}
#endif
//#define errno (*__gh_errno_ptr())
#define errno (*shim_GetErrnoPtr())


// -----------------------------------------------------------------------
// Error codes (SO compatible)

#define EPERM   		64					// (GHS: 1 - used in libShim threading code)
#define ENOENT  		65					// (GHS: 2 - used in libShim file access code)
/*
#define ESRCH   		3
*/
#define EINTR   		50					// not a perfect match as signals to abort blocking operations do not exist, but it's the closest thing to it

#define EIO     		66					// (GHS: 5 - used in libShim file access code)

/*
#define ENXIO   		6
#define E2BIG   		7
#define ENOEXEC 		8
*/
#define EBADF   		67					// (GHS: 9 - used in libShim file access code)
/*
#define ECHILD  		10
*/
#define EAGAIN  		6

#define EDEADLK			68					// (GHS: ? - used in libShim threading code)

#define ENOMEM  		18

#define EACCES  		68					// (GHS: 13 - used in libShim file access code)

#define EFAULT  		29
#define EBUSY   		44

#define EEXIST  		17					// OVERLAPS: SO_EHAVEOOB - used by sqlite
/*
#define EXDEV   		18
*/
#define ENODEV  		19
/*
#define ENOTDIR 		20
*/
#define EISDIR  		21					// OVERLAPS: SO_EAFNOSUPPORT - used by sqlite

#define EINVAL  		11
/*
#define ENFILE  		23
*/
#define EMFILE  		51
/*
#define ENOTTY  		25
#define ETXTBSY 		26
#define EFBIG   		27
#define ENOSPC  		28
#define ESPIPE  		29
#define EROFS   		30
#define EMLINK  		31
*/
#define EPIPE   		13

#define	EWOULDBLOCK		EAGAIN
#define	EINPROGRESS		22
#define	EALREADY		10

#define	ENOTSOCK		24
#define	EDESTADDRREQ	14
#define	EMSGSIZE		12
#define	EPROTOTYPE		32
#define	ENOPROTOOPT		16
#define	EPROTONOSUPPORT	31
/*
#define	ESOCKTNOSUPPORT	44
*/
#define	EAFNOSUPPORT	21
#define	EADDRINUSE		20
#define	EADDRNOTAVAIL	19

/*
#define	ENETDOWN		50
*/
#define	ENETUNREACH		30
/*
#define	ENETRESET		52
*/
#define	ECONNABORTED	5
#define	ECONNRESET		8
#define	ENOBUFS			1
#define	EISCONN			3
#define	ENOTCONN		9
#define	ESHUTDOWN		15
#define	ETOOMANYREFS	28
#define	ETIMEDOUT		2
#define	ECONNREFUSED	7

/*
#define	EHOSTDOWN		64
#define	EHOSTUNREACH	65

#define EPROCLIM        67
#define EUSERS          68
#define EDQUOT          69
*/

#define EOVERFLOW		79

#define ENOLCK			46
#define ENOSYS			89
#define	ESTALE			127

#define EDOM    33		/* also #define'd in math.h & does NOT overlap with any SO... values! - used in CRT */
#define ERANGE  34		/* also #define'd in math.h & does NOT overlap with any SO... values! - used in CRT */

#define ENOSPC  28		/* GHS' VALUE OVERLAPS: ETOOMANYREFS -- used in some curl code to propagate "buffer full" conditions */

#endif /* _ERRNO_H_ */
