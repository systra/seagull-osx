/**
 * @file oc_getaccess.h
 * @brief Provide HP-UX syscall "getaccess" to Linux
 * 
 * Use it using:
 * 
 * @verbatim
 * #include <OC/oc_getaccess.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */


#ifndef OC_GETACCESS_H
#define OC_GETACCESS_H

#include <OC/oc_config.h>

#if defined(__linux)

#include <OC/oc_types.h>

#include <sys/stat.h>
#include <unistd.h>

/*
 * Following values are taken from HP-UX.
 */

#define UID_EUID	-34
#define UID_RUID	-33
#define UID_SUID	-32

#define NGROUPS_EGID	-1
#define NGROUPS_RGID	-2
#define NGROUPS_SGID	-3

/*
 * Function prototype.
 */

#ifdef __cplusplus
extern "C" {
#endif

OC_API int oc_getaccess( const char *path,
			 uid_t uid,
			 int ngroups,
			 const gid_t *gidset,
			 void *label,
			 void *privs );

#ifdef __cplusplus
}
#endif

#elif defined(__hpux)

#include <sys/getaccess.h>

#define oc_getaccess	getaccess

#endif /* __os */

#endif /* OC_GETACCESS_H */
