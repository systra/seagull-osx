/**				-*- Mode: C -*-
 * @file OC/oc_stropts.h
 * @brief Opencall wrapper for UNIX STREAMS
 * 
 * UNIX defines the <stropts.h> header file as the single entry point for the
 * whole STREAMS API, both in kernel & user-space.
 * 
 * Use it with:
 *
 * @verbatim
 * #include <OC/oc_stropts.h>
 * @endverbatim
 * 
 * This file is suitable for inclusion both in user-space & kernel-space code.
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 * 
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

#ifndef _OC_STROPTS_H
#define _OC_STROPTS_H

#include <OC/oc_config.h>

#if defined(__hpux)
#include <sys/types.h>
#endif

#if defined(__linux__) && defined(__KERNEL__)

#define _ASM_HW_IRQ_H		/* to avoid STR re-definition */

/*
 * Please the compiler with the prototype. Use of '-Werror' compiler options
 * breaks the CONS build due to missing function prototypes.
 */
void do_BUG (const char *, int);

#endif /* __linux__ && __KERNEL__ */

/*
 * Single official UNIX STREAMS header
 */
#include <stropts.h>

#if defined(__linux__)

#if !defined(_LIS_STROPTS_H)
#error "Check your #include path. We want to use the LiS version of <stropts.h>"
#endif /* !_LIS_STROPTS_H */

/*
 * Using Linux STREAMS <stropts.h>
 */

#if defined(__KERNEL__)
#define STRMSGSZ 16*1024
#endif /* __KERNEL__ */

/* Linux STREAMS (LiS) does not rely on __linux__ */
#ifndef LINUX
#define LINUX 1
#endif

#include <sys/stream.h>
#include <sys/cmn_err.h>
#include <sys/dki.h>
#if !defined(__KERNEL__)
#include <sys/ioctl.h>
#endif /* !__KERNEL__ */

/*
 * LiS's strlog is implemented in a separated symbol.  Provided definitions are
 * borrowed from HP-UX.
 */
#include <sys/LiS/strlog.h>
#define strlog( mid, sid, level, flags, fmt, ... ) \
	lis_strlog( mid, sid, level, flags, fmt, __VA_ARGS__ )

#define SL_FATAL        0x1	/* Fatal error */
#define SL_NOTIFY       0x2	/* Notify the system administrator */
#define SL_ERROR        0x4	/* Pass message to error logger */
#define SL_TRACE        0x8	/* Pass message to tracer */
#define SL_CONSOLE      0x10	/* Print the message on the console */
#define SL_WARN         0x20	/* Warning */
#define SL_NOTE         0x40	/* Notice this message */

/* LiS's makedevice relies on the default Linux MKDEV() */
#ifndef makedev
#define makedev	makedevice
#endif

#elif defined(__hpux)

#include <stream.h>
#include <strlog.h>
#include <cmn_err.h>

#endif /* __os__ */

#endif /* _OC_STROPTS */
