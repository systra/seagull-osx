/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_limits.h
 * @brief Opencall wrapper providing system limits
 * 
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_limits.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_LIMITS_H
#define _OC_LIMITS_H

#include <OC/oc_config.h>

#if defined(__linux__)

#if defined(__KERNEL__)
# include <linux/limits.h>
#else  /* !__KERNEL__ */
# include <limits.h>		/* ANSI C */
# include <sys/param.h>
# include <asm/page.h>		/* PAGE_SIZE */
#endif /* !__KERNEL__ */

#elif defined(__hpux)

#include <limits.h>		/* ANSI C */

#endif /* __linux__ */

/*
 * HP-UX defines POSIX's FD_SETSIZE based on _MAXFUPLIM, which in turns depends
 * on _USE_BIG_FDS (to turn on support of huge number of file descriptors in a
 * user-space process).  See <_fd_macros.h> for details.
 *
 * Linux has no such capability & no _MAXFUPLIM defined.  So _MAXFUPLIM is
 * defined based on the system-allowed FD_SETSIZE.
 */
#ifndef _MAXFUPLIM
#define _MAXFUPLIM			FD_SETSIZE
#endif

#ifndef NOFILE
# define NOFILE				_MAXFUPLIM
#endif

/* FIXME: where does this value comes from? */
#define MAX_CHANNELS			2048

#ifndef _WIN32
# define MAXLEN_FILEPATH		_POSIX_PATH_MAX
# define MAXLEN_FILENAME		_POSIX_NAME_MAX
#else  /* !_WIN32 */
# define MAXLEN_FILEPATH		512
# define MAXLEN_FILENAME		512
#endif /* !_WIN32 */

#if defined(__linux__)
/*
 * - PAGE_SIZE: On Linux, a command-line cannot exceed a CPU page size (4096 on
 *   i386, 8192 (might be 4096/8192/16384/65535) on ia64.
 * - LINE_MAX: ANSI C standard value.
 */
#define OC_MAX_PROCESS_NAME_LENGTH	PAGE_SIZE
#define OC_MAX_LINE_LENGTH		LINE_MAX

#endif /* __linux */

#if defined(__hpux)

#define OC_MAX_PROCESS_NAME_LENGTH	512
#define OC_MAX_LINE_LENGTH		2048	/* should be NL_TESTMAX */

#endif /* __hpux */

/**
 * HP-UX & Linux have a rather different approach on what is a 'hostname':
 *
 * @li HP-UX hostname is always the non-qualified domain name, which length
 *   cannot exceed 8 characters (9, with the trailing '\0').  FQDN is always
 *   provided as an alias, when configured in '/etc/hosts' file on in DNS
 *   records.
 *
 * @li Linux hostname is the system FQDN.  the NQDN is deduced from the FQDN
 *   on-the-fly by applications.  consequently, the hostname maximum length is
 *   64.
 *
 * in opencall, the hostnames have essentially an impact on the MsgLib internal
 * buffer initial size, therfore we need the FQDN size.
 */

#define MAXLEN_HOSTNAME    64	/* UNIX value, from <oc_utsname.h> */
#define MAXLEN_SERVICENAME 20	/* guessed value */

#endif /* _OC_LIMITS_H */
