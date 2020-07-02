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



#ifndef _THREAD_CTRL_WIIU_H_
#define _THREAD_CTRL_WIIU_H_



#ifdef __cplusplus
extern "C" {
#endif

	typedef struct OSThread OSThread;
	typedef int (*OSThreadEntryPointFn)(int argc, const char **argv);
	
	
signed shim_CreateThread(OSThread* thread, OSThreadEntryPointFn entryPoint, int intArg, void* ptrArg, void* stack, unsigned stackSize, signed priority, unsigned short attr);

void shim_ThreadDone(void);

void _shim_threadCtrl_Startup(void);
void _shim_threadCtrl_Shutdown(void);

#define	SHIM_SWITCH_NONE		0
#define	SHIM_SWITCH_TO_BG		1
#define	SHIM_SWITCH_TO_FG		2
#define	SHIM_SWITCH_SHUTDOWN	3

	void shim_RegisterSyncThread(OSThread *pThread);
	void shim_UnregisterSyncThread(OSThread *pThread);


unsigned shim_PollForSwitch(void);
void shim_AcknowledgeSwitch(void);

#define	SHIM_SWITCHTARGET_HBM		0		// Bring up HBM
#define	SHIM_SWITCHTARGET_SETTINGS	1		// Launch Settings
#define	SHIM_SWITCHTARGET_ACCOUNT	2		// Launch Account Management
#define	SHIM_SWITCHTARGET_MENU		3		// Launch menu and quit app
#define	SHIM_SWITCHTARGET_BROWSER	4		// Bring up Browser
#define	SHIM_SWITCHTARGET_SELF		5		// Restart app

void shim_RequestProcessSwitch(int target, const void *pParam0, const void *pParam1);

void shim_RegisterExitMessageCallback(void (*callback)(void));

int shim_IsBackground(void);

signed shim_EnableHBM(signed enable);
signed shim_WasHBMDenied(void);
void shim_ResetHBMDenied(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _THREAD_CTRL_WIIU_H_
