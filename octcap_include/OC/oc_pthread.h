/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_pthread.h
 * @brief wrapper over POSIX threads
 *
 * hp opencall wrapper over the POSIX-threads mutil-threading API.
 * 
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_pthread.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_PTHREAD_H
#define OC_PTHREAD_H

#include <OC/oc_config.h>

#ifdef _REENTRANT

#include <pthread.h>

/**
 * Linux current multi-thread implementation (LinuxThreads) is not compliant
 * with the Single UNIX specification.  Both API return z ero int in case of
 * success, but the error case is different:
 *
 * @li if the POSIX pthread_xxx API functions return value is non-zero, the
 *     value itself can be interpreted as errno using the <errno.h> table,
 *
 * @li if the LinuxThreads pthread_xxx API functions return value is non-zero,
 *     the error code is given by the errno shared variable.
 *
 * This problem is fixed when compiling against GNUpth (GNU POSIX threads),
 * which is the foundation of the Linux NGPT (Next Generation POSIX Threads).
 *
 */
#if defined(__linux) && !defined(_POSIX_THREAD_IS_GNU_PTH)
#define OC_PTHREAD( fc )	(fc != 0 ? errno : 0)
#else  /* !__linux || _POSIX_THREAD_IS_GNU_PTH */
#define OC_PTHREAD( fc )	fc
#endif /* !__linux || _POSIX_THREAD_IS_GNU_PTH */

/*
 * disallow use of HP-UX DCE threads.
 */
#if defined(__hpux)
#undef _PTHREADS_DRAFT4
#endif

#endif /* _REENTRANT */
#endif /* OC_PTHREAD_H */
