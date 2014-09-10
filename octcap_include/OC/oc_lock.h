/**
 * @file oc_lock.h
 * @brief provide HP-UX "plock" syscall to Linux
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_plock.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_LOCK_H
#define OC_LOCK_H

#include <OC/oc_config.h>

#ifdef __linux

#include <sys/mman.h>

/*
 * Following values are taken from HP-UX.
 */

#define PROCLOCK		0x00000001

/*
 * Function prototype.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern int	oc_plock( int op );

#ifdef __cplusplus
}
#endif


#else  /* __hpux */

#include <sys/lock.h>			/* for plock() */
#define oc_plock	plock

#endif /* __hpux */

#endif /* _OC_LOCK_H */
