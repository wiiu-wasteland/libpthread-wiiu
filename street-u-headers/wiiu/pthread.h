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


#ifndef _PTHREAD_H
#define _PTHREAD_H


#define OS_ATOMIC_DONT_INLINE 



#include <sys/time.h> 

#include "sched.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PTHREAD_ONCE_INIT				0
#define PTHREAD_KEYS_MAX				32

#define __SIZEOF_PTHREAD_ATTR_T 		20
#define __SIZEOF_PTHREAD_MUTEXATTR_T	4
#define __SIZEOF_PTHREAD_CONDATTR_T		4

enum
{
	PTHREAD_MUTEX_TIMED_NP = 0,
	PTHREAD_MUTEX_RECURSIVE_NP,
	PTHREAD_MUTEX_ERRORCHECK_NP,
	PTHREAD_MUTEX_ADAPTIVE_NP,
	PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
	PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
	PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
	PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL,
	PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
};

enum
{
	SCHED_FIFO = 0,
	SCHED_RR,
	SCHED_OTHER
};

typedef unsigned int pthread_key_t;
typedef int pthread_once_t;

typedef OSThread *	pthread_t;
typedef OSCond *	pthread_cond_t;
	
typedef void *		pthread_mutex_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
} pthread_attr_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_CONDATTR_T];
  int __align;
} pthread_condattr_t;

int pthread_setspecific(pthread_key_t key, const void *pointer);
void *pthread_getspecific(pthread_key_t key);
int pthread_key_create(pthread_key_t *key, void (*destr_function) (void *));
int pthread_once(pthread_once_t *once_control, void (*init_routine) (void));
int pthread_equal(pthread_t thread1, pthread_t thread2);
int pthread_create(pthread_t *newthread, const pthread_attr_t *attr, void *(*start_routine)(void *arg), void *arg);
int pthread_setexitcallback(pthread_t thread, void (*exit_callback)(void *arg));	// uses same arg as what was passed into create
pthread_t pthread_self(void);
int pthread_join(pthread_t th, void **thread_return);
int pthread_detach(pthread_t th);
int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param);
int pthread_getschedparam(pthread_t thread, int *policy, struct sched_param *param);
int pthread_setschedprio(pthread_t thread, int prio);
int pthread_yield(void);
void pthread_exit(void *retval);

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind);
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *cond_attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);

int pthread_kill(pthread_t thread, int sig);

int pthread_key_delete(pthread_key_t key);
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_getattr_np(pthread_t thread, pthread_attr_t *attr);
int pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr, size_t * stacksize);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param);
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
int pthread_attr_setthreadname(pthread_attr_t *attr, const char *threadname);

inline pthread_mutex_t _InitDefaultMutex(void) { pthread_mutex_t _mutex; pthread_mutex_init(&_mutex, NULL); return(_mutex); }
#define	PTHREAD_MUTEX_INITIALIZER	_InitDefaultMutex()

//
//  "Extentions" to pthread
//

#define	PTHREAD_WIIU_PRIO_LOWEST		24
#define	PTHREAD_WIIU_PRIO_LOWER			20
#define	PTHREAD_WIIU_PRIO_DEFAULT		16
#define	PTHREAD_WIIU_PRIO_HIGHER		12
#define	PTHREAD_WIIU_PRIO_HIGHEST		8

#define	PTHREAD_WIIU_AFFINITY_CORE0		0
#define	PTHREAD_WIIU_AFFINITY_CORE1		1
#define	PTHREAD_WIIU_AFFINITY_CORE2		2

//
// signal.h - here for simplicity
//

#define		SIGUSR2		1

typedef struct sigset {
			int		dummy;
		} sigset_t;

typedef struct siginfo {	
	int           si_signo;									// Signal number
	int           si_code;									// Signal code
	} siginfo_t;
		
typedef struct sigaction {
	void		(*sa_handler)(int);							// Pointer to a signal-catching function or one of the macros SIG_IGN or SIG_DFL
	sigset_t	sa_mask;									// Set of signals to be blocked during execution of the signal handling function
	int			sa_flags;									// Special flags
	void		(*sa_sigaction)(int, siginfo_t *, void *);	// Pointer to a signal-catching function
	} sigaction_t;
	
int sigemptyset(sigset_t *);
int sigaddset(sigset_t *, int);
int sigsuspend(const sigset_t *);
int sigaction(int, const struct sigaction *, struct sigaction *);

void shim_pthread_ShutdownFreely(void);

#ifdef __cplusplus
}
#endif

#endif
