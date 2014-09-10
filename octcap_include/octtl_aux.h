/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License v2 as published by the Free Software Foundation; only
 *  version 2 of the License is valid for this software, unless
 *  explicitly otherwise stated.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License v2 along with this program; if not, write to the
 *  Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 *  MA 02139, USA.
 */

#ifndef _OCTTL_AUX_H
#define _OCTTL_AUX_H

#ifndef _KERNEL

#include <stdio.h>
#include <stdarg.h>

#ifdef __GNUC__
#include <nl_types.h>
#endif /* __GNUC__ */

/*
** WARNING !!! the theorical limitations is
** NL_TESTMAX in limits.h (8192).
** We reduce that to 2k
*/
#define TTL_C_MAX_LOG_MSG_LENGTH 2048

/* used in my_vsprintf_new */
/* Name of the tracing process */
#define TTL_C_MAX_TRACE_PROCESS_NAME 512

/* Max length of a formatted trace msg + args */
#define TTL_C_MAX_TRACE_MSG_LENGTH 2048

#define SIZE_MAX_MSG (TTL_C_MAX_TRACE_MSG_LENGTH - TTL_C_MAX_TRACE_PROCESS_NAME)

/* Max no of trace messages for all threads */
#define MAX_NUMBER_CONCURRENT_TRACE_MSG 20

#ifdef COCA_WIN32
#define TTL_NULL_FILE "NUL"
#else  /* !COCA_WIN32 */
#define TTL_NULL_FILE "/dev/null"
#endif /* !COCA_WIN32 */

#ifndef true
#define true 1
#define false 0
#endif /* !true */

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif /* !TRUE */

/* To keep the name of the tracing process             */
/* multiple call of TTL_M_INIT. This to allow on-line  */
/* change of traces masks. default is true. It will be */
/* set to false the first time TTL_M_INIT is called.   */

extern char TTL_V_SCP_M_INIT_ProcessName[TTL_C_MAX_TRACE_PROCESS_NAME];
#endif /* !_KERNEL */

#endif /* _AUX_H */
