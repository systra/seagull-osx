/**
 * @file oc_sys_socket.h
 * @brief all-in-one header to use the BSD UNIX SOCKETS API
 *
 * provide declaration & manifest constant accross OS for socket(2) &
 * associated stuffs.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_sys_socket.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */
#ifndef _OC_SYS_SOCKET_H
#define _OC_SYS_SOCKET_H

/* general-purpose configuration */
#include <OC/oc_config.h>

/* ANSI C headers needed here */
#include <errno.h>
#include <string.h>

/*
 * The GNU Libc -- used by Linux in particular -- requires <sys/types.h> also
 * for socket(2), according to the man page.
 */
#ifdef __GLIBC__
#include <sys/types.h>
#endif	/* __GLIBC__ */

#include <sys/socket.h>

/**
 * AF_INET6 support
 * 
 * @li Single UNIX Specification requires that INET_ADDRSTRLEN is defined in
 * <netinet/in.h>.  This is not the case on HP-UX.
 * 
 * @li on HP-UX <netinet/in6.h> is automatically included by <netinet/in.h>.
 */
#include <netinet/in.h>

#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN 16		/* includes trailing '\0' */
#endif

#if defined(__GLIBC__) || (defined(__hpux) && defined(_NETINET_IN6_H))
#define HAVE_IPV6
#endif

/**
 * AF_UNIX support
 * 
 * for UNIX domain sockets
 */
#include <OC/oc_sys_un.h>

/**
 * inet_ntop(3) and inet_pton(3) are the new portable (IPv4, IPv6, UNIX,
 * ...etc.)  interface to tackle with network & printable addresses
 * representations described by the Single UNIX Specification v3.  These 2
 * functions deprecates inet_ntoa(3) & inet_aton(3).
 * 
 * These functions are mandatory as soon as the underlying OS is IPv6-capable.
 *
 * @li HP-UX 11.00 (hppa, UNIX95, AKA SusV1) does not implement these
 * functions.  So hp opencall provides replacement code for the IPv4 address
 * family, based on the deprecated inet_ntoa(3) and inet_addr(3) functions.
 * 
 * @li HP-UX 11.11 (hppa) is un-officially SusV2 (UNIX98) and implement these
 * functions.
 * 
 * @li HP-UX 11.22 (ia64) is un-officially SusV2 (UNIX98) and implement these
 * functions.
 */

#include <arpa/inet.h>

#if !defined(HAVE_IPV6)

STATIC_INLINE const char*
inet_ntop( int family, const void *addr, char *dst,
	   socklen_t cnt )
{
	if( family != AF_INET ) {
		errno = EAFNOSUPPORT;
		return NULL;
	}

	if( cnt < (socklen_t)INET_ADDRSTRLEN ) {
		errno = ENOSPC;
		return NULL;
	}
	strncpy( dst, inet_ntoa( *(struct in_addr*)addr ), INET_ADDRSTRLEN );
	return dst;
}

STATIC_INLINE int
inet_pton( int family, const char *src, void *dst )
{
	struct in_addr* addr = (struct in_addr*)dst;

	if( family != AF_INET ) {
		errno = EAFNOSUPPORT;
		return 0;
	}

	if( !src || !dst ) {
		return 0;
	}

	addr->s_addr = inet_addr( src );
	return ( (int)addr->s_addr >= 0 );
}

#endif /* !HAVE_IPV6 */

/*
 * HP-UX's default declaration of accept(2) does not match the one of the Single UNIX
 * Specification.
 */
STATIC_INLINE int
oc_accept( int s, struct sockaddr *addr, socklen_t *addrlen )
{
#if !defined(_XOPEN_SOURCE_EXTENDED)
	return accept( s, (void*)addr, (int*)addrlen);
#else  /* _XOPEN_SOURCE_EXTENDED */
	return accept( s, addr, addrlen );
#endif /* _XOPEN_SOURCE_EXTENDED */
}

STATIC_INLINE int
oc_getsockname(int s, struct sockaddr *addr, socklen_t *addrlen)
{
#if !defined(_XOPEN_SOURCE_EXTENDED)
	return getsockname( s, (void*)addr, (int*)addrlen );
#else  /* _XOPEN_SOURCE_EXTENDED */
	return getsockname( s, addr, addrlen );
#endif /* _XOPEN_SOURCE_EXTENDED */
}

#endif /* _OC_SYS_SOCKET_H */
