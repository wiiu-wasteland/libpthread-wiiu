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

#ifndef _SHIM_H_
#define _SHIM_H_

#ifdef __cplusplus
extern "C" {
#endif

extern void shim_Init(void);
extern void shim_Exit(void);

extern void shim_SetStorageWaitReadyCallback(int (*WaitForStorageReady)());

extern void* shim_GetFSClient(void);
extern int shim_GetFSMaxArgPathSize();
extern int shim_GetFSMaxFullPathSize();
extern int shim_GetFSMaxEntNameSize();

#define SHIM_FS_CLIENT_MAX_NAME		32
typedef struct SHIMfsClient_t
	{
	void	*mpFSClient;
	char	maClientName[SHIM_FS_CLIENT_MAX_NAME];
	} SHIMfsClient;

extern int shim_GetAllFSClients(SHIMfsClient *paOutClients, int maxOutClients);

#define SHIM_FS_FILE_MAX_NAME		512

typedef struct SHIMfsErrorInfo_t {
		int		m_fsErrorCode;
		int		m_dispErrorCode;
		char	m_fileName[SHIM_FS_FILE_MAX_NAME];
} SHIMfsErrorInfo;

#define SHIM_SO_HOST_MAX_NAME		512

typedef struct SHIMsoErrorInfo_t {
		int		m_soErrorCode;
		int		m_dispErrorCode;
		char	m_hostName[SHIM_SO_HOST_MAX_NAME];
} SHIMsoErrorInfo;

extern SHIMfsErrorInfo *shim_GetFSError(void);
extern int shim_HasFSError(void);

extern SHIMsoErrorInfo *shim_GetSOError(void);
extern int shim_HasSOError(void);

extern const char *shim_GetLanguage(void);

#ifdef __cplusplus
}
#endif

#endif // _SHIM_H_




