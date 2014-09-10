/**
 * @file oc_signal.h
 * @brief provide HP-UX "sigvector" syscall to Linux
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_signal.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_SIGNAL_H
#define _OC_SIGNAL_H

#include <OC/oc_config.h>

#ifdef __hpux
#ifndef __USE_BSD
#define __USE_BSD
#endif /* !__USE_BSD */
#endif /* __hpux */

#include <signal.h>
#include <sys/types.h>


#ifdef __linux

/*
 * Function prototype.
 */

#ifdef __cplusplus
extern "C" {
#endif

OC_API
int
oc_sigvector( int sig,
	      const struct sigvec *vec,
	      struct sigvec *ovec );

#ifdef __cplusplus
}
#endif

#endif /* __linux */

#ifndef SIGNULL
#define SIGNULL                     0
#endif

#endif /* _OC_SIGNAL_H */
