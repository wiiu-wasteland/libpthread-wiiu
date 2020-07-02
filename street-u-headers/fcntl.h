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


#ifndef FCNTL_H_
#define FCNTL_H_

/* for open */
#define O_CREAT 00100
#define O_EXCL 00200
#define O_NOCTTY 00400
#define O_TRUNC 01000

#define O_RDONLY 1
#define O_WRONLY 2
#define O_RDWR 4

/* for fcntl */
#define F_DUPFD 0 
#define F_GETFD 1 
#define F_SETFD 2 
#define F_GETFL 3 
#define F_SETFL 4 
#define F_GETLK 5 
#define F_SETLK 6 
#define F_SETLKW 7 
#define F_FREESP 8 

#define F_RDLCK 1
#define F_WRLCK 2
#define F_UNLCK 3

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct flock {
    short l_type;
    short l_whence;
    off_t l_start;
    off_t l_len;
    pid_t l_pid;
};

int open(const char *name, int flags, int mode);
int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif


#endif
