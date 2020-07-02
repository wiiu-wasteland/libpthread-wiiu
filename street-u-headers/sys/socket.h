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

#ifndef SOCKET_H_
#define SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LIBSHIM_PROTOTYPES_ONLY // (internal use only!)

#include <sys/time.h>

/*
// Constants ------------------------------------------------------------------
*/

#define SOCKET_ERROR	(-1)

#define AF_UNSPEC   	0
#define AF_INET 		2

#define SOCK_STREAM 	1
#define SOCK_DGRAM  	2

#define IPPROTO_IP  	0
#define IPPROTO_TCP 	6
#define IPPROTO_UDP 	17

#define MSG_OOB 	   0x1
#define MSG_PEEK	   0x2
#define MSG_DONTROUTE  0x4
#define MSG_NEWPIPE    0x8
#define MSG_EOR 	   0x10
#define MSG_DONTWAIT   0x20

#define SHUT_RD 		0
#define SHUT_WR 		1
#define SHUT_RDWR   	2

#define SOL_SOCKET  	-1

#define SO_REUSEADDR	 0x00004
#define SO_KEEPALIVE	 0x00008
#define SO_DONTROUTE	 0x00010
#define SO_BROADCAST	 0x00020
#define SO_LINGER   	 0x00080
#define SO_OOBINLINE	 0x00100
#define SO_TCPSACK  	 0x00200
#define SO_HDRINCL  	 0x02000
#define SO_SNDBUF   	 0x1001
#define SO_RCVBUF   	 0x1002

#ifdef SO_ERROR
#undef SO_ERROR
#endif

#define SO_ERROR		 0x1007			// note: naming conflict with SO error code (optiming here to use the BSD standard define for compatibility!)
#define SO_TYPE 		 0x1008
#define SO_HOPCNT   	 0x1009
#define SO_MAXMSG   	 0x1010
#define SO_RXDATA   	 0x1011
#define SO_TXDATA   	 0x1012
#define SO_MYADDR   	 0x1013
#define SO_NBIO 		 0x1014
#define SO_BIO  		 0x1015
#define SO_NONBLOCK 	 0x1016

#define IP_TOS  			  3
#define IP_TTL_OPT  		  4
#define IP_TTL  		 IP_TTL_OPT

#define TCP_ACKDELAYTIME 0x2001
#define TCP_NOACKDELAY   0x2002
#define TCP_MAXSEG  	 0x2003
#define TCP_NODELAY 	 0x2004

#define AI_PASSIVE         0x01
#define AI_CANONNAME       0x02
#define AI_NUMERICHOST     0x04
#define AI_NUMERICSERV     0x08

#define NI_NOFQDN          0x01
#define NI_NUMERICHOST     0x02
#define NI_NAMEREQD        0x04
#define NI_NUMERICSERV     0x08
#define NI_DGRAM           0x10

#define NI_MAXHOST         1025
#define NI_MAXSERV         32

#define	EAI_ADDRFAMILY   1
#define	EAI_AGAIN        2
#define	EAI_BADFLAGS     3
#define	EAI_FAIL         4
#define	EAI_FAMILY       5
#define	EAI_MEMORY       6
#define	EAI_NODATA       7
#define	EAI_NONAME       8
#define	EAI_SERVICE      9
#define	EAI_SOCKTYPE    10
#define	EAI_SYSTEM      11
#define	EAI_BADHINTS    12
#define	EAI_PROTOCOL    13
#define EAI_OVERFLOW    14
#define	EAI_MAX         15

/*
// Types ----------------------------------------------------------------------
*/

struct linger
{
	int l_onoff;
	int l_linger;
};

struct sockaddr
{
   unsigned short    sa_family;
#ifdef IP_V6
   char 	sa_data[32];
#else
   char 	sa_data[14];
#endif
};

#define INADDR_ANY 0L

struct in_addr
{
	unsigned long s_addr;
};

struct sockaddr_in
{
	unsigned short     sin_family;
	unsigned short     sin_port;
	struct   in_addr   sin_addr;
	char			   sin_zero[8];
};

typedef int 		  socklen_t;

typedef unsigned long ip_addr;

struct hostent
{
   char *   h_name;
   char **	h_aliases;
   int   	h_addrtype;
   int   	h_length;
   char **	h_addr_list;
#define  	h_addr   h_addr_list[0]
};

struct addrinfo {
  int     			ai_flags;
  int     			ai_family;
  int     			ai_socktype;
  int     			ai_protocol;
  int     			ai_addrlen;
  char *			ai_canonname;
  struct sockaddr  *ai_addr;
  struct addrinfo  *ai_next;
};

/*
// Macros ---------------------------------------------------------------------
*/

#define FD_SETSIZE (32)
#define FD_SET(n, p)		((p)->fd_bits |= (1 << (n)))
#define FD_CLR(n, p)		((p)->fd_bits &= ~(1 << (n)))
#define FD_ISSET(n, p)  	((p)->fd_bits & (1 << (n)))
#define FD_ZERO(p)  		((p)->fd_bits = 0)
#define FD_COPY(f, t)   	((t)->fd_bits = (f)->fd_bits)

#endif	// LIBSHIM_PROTOTYPES_ONLY

/*
// libShim's Socket API -------------------------------------------------------
*/

extern int shim_accept(int fd, struct sockaddr *addr, int *addrlen);
extern int shim_bind(int fd, struct sockaddr *addr, int addrlen);
extern int shim_connect(int fd, struct sockaddr *addr, int addrlen);
extern int shim_listen(int fd, int backlog);
extern int shim_recv(int fd, void *buffer, int len, int flags);
extern int shim_recvfrom(int fd, void *buffer, int len, int flags, struct sockaddr *from, int *fromlen);
extern int shim_send(int fd, const void *buffer, int len, int flags);
extern int shim_sendto(int fd, const void *buffer, int len, int flags, const struct sockaddr *dest_addr, int dest_len);
extern int shim_shutdown(int fd, int how);
extern int shim_socket(int family, int type, int proto);
extern int shim_socketclose(int fd);
extern int shim_inet_aton(const char *cp, struct in_addr *addr);
extern char *shim_inet_ntoa(struct in_addr in);
extern char *shim_inet_ntoa_r(struct in_addr in, char *buf);
extern const char *shim_inet_ntop(int af, const void *src, char *dst, socklen_t size);
extern int shim_inet_pton(int af, const char *src, void  *dst);
extern int shim_getpeername(int fd, struct sockaddr *name, int *addrlen);
extern int shim_getsockname(int fd, struct sockaddr *name, int *addrlen);
extern int shim_getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen);
extern int shim_setsockopt(int fd, int level, int optname, void *optval, socklen_t optlen);
extern int shim_socketlasterr(void);
extern void shim_setsocketlasterr(int err);
extern int shim_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
extern unsigned int shim_ntohl(unsigned int val);
extern unsigned int shim_htonl(unsigned int val);
extern unsigned short shim_ntohs(unsigned short val);
extern unsigned short shim_htons(unsigned short val);

extern void shim_freeaddrinfo(struct addrinfo *);
extern int shim_getaddrinfo(const char *, const char *, const struct addrinfo *, struct addrinfo **);
extern int shim_getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, socklen_t nodelen, char *service, socklen_t servicelen, int flags);
extern const char *shim_gai_strerror(int);
extern struct hostent * shim_gethostbyname(const char * name);
extern struct hostent * shim_gethostbyaddr(const void* addr, int len, int type );

extern int shim_socket_lib_init(void);
extern void shim_socket_lib_finish(void);

/*
// Map standard BSD API to lilbShim's API -------------------------------------
*/
#ifndef LIBSHIM_PROTOTYPES_ONLY

inline int accept(int fd, struct sockaddr *addr, int *addrlen) { return shim_accept(fd, addr, addrlen); }
inline int bind(int fd, struct sockaddr *addr, int addrlen) { return shim_bind(fd, addr, addrlen); }
inline int connect(int fd, struct sockaddr *addr, int addrlen) { return shim_connect(fd, addr, addrlen); }
inline int listen(int fd, int backlog) { return shim_listen(fd, backlog); }
inline int recv(int fd, void *buffer, int len, int flags) { return shim_recv(fd, buffer, len, flags); }
inline int recvfrom(int fd, void *buffer, int len, int flags, struct sockaddr *from, int *fromlen) { return shim_recvfrom(fd, buffer, len, flags, from, fromlen); }
inline int send(int fd, const void *buffer, int len, int flags) { return shim_send(fd, buffer, len, flags); }
inline int sendto(int fd, const void *buffer, int len, int flags, const struct sockaddr *dest_addr, int dest_len) { return shim_sendto(fd, buffer, len, flags, dest_addr, dest_len); }
inline int shutdown(int fd, int how) { return shim_shutdown(fd, how); }
inline int socket(int family, int type, int proto) { return shim_socket(family, type, proto); }
inline int socketclose(int fd) { return shim_socketclose(fd); }
inline int inet_aton(const char *cp, struct in_addr *addr) { return shim_inet_aton(cp, addr); }
inline char *inet_ntoa(struct in_addr in) { return shim_inet_ntoa(in); }
inline char *inet_ntoa_r(struct in_addr in, char *buf) { return shim_inet_ntoa_r(in, buf); }
inline const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) { return shim_inet_ntop(af, src, dst, size); }
inline int inet_pton(int af, const char *src, void  *dst) { return shim_inet_pton(af, src, dst); }
inline int getpeername(int fd, struct sockaddr *name, int *addrlen) { return shim_getpeername(fd, name, addrlen); }
inline int getsockname(int fd, struct sockaddr *name, int *addrlen) { return shim_getsockname(fd, name, addrlen); }
inline int getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen) { return shim_getsockopt(fd, level, optname, optval, optlen); }
inline int setsockopt(int fd, int level, int optname, void *optval, socklen_t optlen) { return shim_setsockopt(fd, level, optname, optval, optlen); }
inline int socketlasterr(void) { return shim_socketlasterr(); }
inline void setsocketlasterr(int err) { shim_setsocketlasterr(err); }
inline int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) { return shim_select(nfds, readfds, writefds, exceptfds, timeout); }
inline unsigned int ntohl(unsigned int val) { return shim_ntohl(val); }
inline unsigned int htonl(unsigned int val) { return shim_htonl(val); }
inline unsigned short ntohs(unsigned short val) { return shim_ntohs(val); }
inline unsigned short htons(unsigned short val) { return shim_htons(val); }

inline void freeaddrinfo(struct addrinfo *info) { shim_freeaddrinfo(info); }
inline int getaddrinfo(const char *a, const char *b, const struct addrinfo *c, struct addrinfo **d) { return shim_getaddrinfo(a, b, c, d); }
inline int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *node, socklen_t nodelen, char *service, socklen_t servicelen, int flags) { return shim_getnameinfo(sa, salen, node, nodelen, service, servicelen, flags); }
inline const char *gai_strerror(int a) { return shim_gai_strerror(a); }
inline struct hostent * gethostbyname(const char * name) { return shim_gethostbyname(name); }
inline struct hostent * gethostbyaddr(const void* addr, int len, int type ) { return shim_gethostbyaddr(addr, len, type); }

inline int socket_lib_init(void) { return shim_socket_lib_init(); }
inline void socket_lib_finish(void) { shim_socket_lib_finish(); }

#endif

#ifdef __cplusplus
}
#endif

#endif

