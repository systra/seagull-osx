/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file OC/oc_poll.h
 * @brief Opencall wrapper for poll(2) syscall
 * 
 * Use it with:
 *
 * @verbatim
 * #include <OC/oc_poll.h>
 * @endverbatim
 * 
 * This file is suitable for inclusion both in user-space & kernel-space code,
 * having no effect on the kernel-space code.
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_POLL_H
#define _OC_POLL_H

#include <OC/oc_config.h>

#if !defined(__KERNEL__) && !defined(_KERNEL)

#if defined(__linux__) && defined(__GLIBC__)

#include <sys/poll.h>
#define POLLNORM	POLLIN

#elif defined(__hpux)

#include <poll.h>

#endif /* __os__ */

#elif defined(__linux__) && defined(__KERNEL__)

#if defined(_LIS_STROPTS_H)
#include <sys/poll.h>
#else  /* !_LIS_STROPTS_H */
#include <linux/poll.h>
#endif /* !_LIS_STROPTS_H */

#endif /* __linux__ && __KERNEL__ */

#endif /* _OC_POLL_H */
