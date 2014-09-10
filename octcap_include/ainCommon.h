/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file ainCommon.h
 * @brief basic definitions of types and manifest constants
 *
 * This file is part of the HP Opencall API external interface
 *
 * Information about using this file:
 *
 * @li It should be included in user's source code via #include <ainCommon.h>
 * @li Before including it in the file that implements the main() function, you
 *     should #define EXEC_MAIN in order to properly instanciate the variables
 *     needed for tracing.
 * @li It can be included in any other file (library or otherwise) without
 *     defining EXEC_MAIN in order to have the externs and the macro
 *     definitions.
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _AINCOMMON_H
#define _AINCOMMON_H

/*
 * Headers.
 */

#include <OC/oc_config.h>	/* must be before any system headers */

#include <OC/oc_limits.h>	/* MAX/MIN/LEN/...etc. */
#include <OC/oc_types.h>	/* POSIX: u?int.+_t, COM_T_xxx */
#include <OC/oc_nl_types.h>	/* native language */

/*
 * Macros.
 */

/* Introduced for 40k socket support (hpux only) */
#ifdef _USE_BIG_FDS
# define INIT_BIG_FD_MODE() MSG_SetBigFdMode (_MAXFUPLIM, sizeof (fd_set))
#endif

#define FD_ZERO_SMALL(p)   memset ((void *)(p), (int) 0, MSG_GetFdSetSize ())

#ifndef MAX
#define MAX(a,b) ((a)<(b) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#endif

#ifndef true
#define true 1
#define false 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifndef NULL
#define NULL        ((void *)0)
#endif /* NULL */

#define ROK 0
#define RFAILED 1

#include <ttlCommon.h>

/*
 * @warning TB_T_types should now be obtained by using '#include <TB_basic.h>'.
 */

#endif /* AINCOMMON_H */
