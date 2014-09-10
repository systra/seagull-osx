/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_inttypes.h
 * @brief system & ANSI integer types portable declaration
 * 
 * This file is suitable for inclusion both in user-space & kernel-space code.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_inttypes.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 * 
 * @see oc_types.h
 * 
 * @note this header file MUST NOT contain any #include to system functions
 * prototype declaration.
 */

#ifndef _OC_INTTYPES_H
#define _OC_INTTYPES_H

#include <OC/oc_config.h>

#if defined(__linux__) && defined(__KERNEL__)
# include <linux/types.h>
#elif defined(__hpux)
# include <stdarg.h>			/* required by <inttypes.h> */
# include <inttypes.h>
#else
# include <stdint.h>
#endif

#if defined(__linux__) && !defined(_BSD_SOURCE) && !defined(__KERNEL__)
typedef __u_short u_short;
typedef __u_int u_int;

typedef __u_char u_char;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
#endif /* __linux && !_BSD_SOURCE && !__KERNEL__ */

#if 0					/* HP-UX < 10.20 */
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef int int32_t;
typedef int intfast_t;			/* most efficient signed integer type */
typedef unsigned int uintfast_t;	/* most efficient unsigned integer type */
#endif /* 0 */

/**
 * @defgroup OC integer types
 * @deprecated use ISO ANSI C 99 types instead
 * @{
 * 
 * Opencall integer types used in public APIs
 */

typedef int			COM_T_int;
typedef int			COM_T_int32;
typedef unsigned char		COM_T_uint8;
typedef unsigned short		COM_T_uint16;
typedef unsigned int		COM_T_uint32;
#ifdef __LP64__
typedef unsigned long		COM_T_uint64;
#else  /* !__LP64__ */
typedef unsigned long long	COM_T_uint64;
#endif /* !__LP64__ */

typedef unsigned int		COM_T_boolean;
typedef unsigned char		COM_T_byte;

/**
 * @}
 */

#endif /* _OC_INTTYPES_H */
