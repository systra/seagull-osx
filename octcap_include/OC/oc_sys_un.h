/**
 * @file oc_sys_un.h
 * @brief system wrapper to use sockets of the UNIX domain.
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

#ifndef OC_SYS_UN_H
#define OC_SYS_UN_H

/* general-purpose configuration */
#include <OC/oc_config.h>

#include <OC/oc_limits.h>
#include <sys/un.h>

#ifndef UNIX_MAX_PATH

/*
 * UNIX_MAX_PATH value is hardwired in system-specific header.  the following
 * declaration has taken the hard-wired value & turned in into a #define.
 */
#ifdef __linux
#define UNIX_MAX_PATH	108
#endif

#ifdef __hpux
#define UNIX_MAX_PATH	92
#endif

#endif /* !UNIX_MAX_PATH */

#endif /* OC_SYS_UN_H */

