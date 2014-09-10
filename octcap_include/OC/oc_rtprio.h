/**
 * @file oc_rtprio.h
 * @brief define values needed to map HP-UX's RT priorities into "nice"
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_rtprio.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_RTPRIO_H
#define OC_RTPRIO_H

#ifdef __linux

#include <OC/oc_types.h>

#define RTPRIO_RTOFF	1001
#define RTPRIO_MIN	0
#define RTPRIO_MAX	127

#ifdef __cplusplus
extern "C" {
#endif

extern int	rtprio( pid_t pid,
			int prio );

#ifdef __cplusplus
}
#endif

#elif defined(__hpux)

#include <sys/rtprio.h>

#else
#warning "Unsupported OS"
#endif /* __os */

#endif /* OC_RTPRIO_H */
