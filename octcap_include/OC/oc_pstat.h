/**
 * @file oc_pstat.h
 * @brief provide HP-UX "pstat" syscall to Linux
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_pstat.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_PSTAT_H
#define OC_PSTAT_H

#include <OC/oc_config.h>
#include <OC/oc_types.h>

#ifdef __linux

#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>

#define CMDLINE_STR		"cmdline"

/* 
 * Following values are taken from HP-UX.
 */

#define MAX_COMMAND_LEN		2048

/*
 * lengths for cached command line and u_comm entries
 */
#define PST_CLEN		64
#define PST_UCOMMLEN		(14 + 1)
#define PST_MAX_CPUSTATES	15

struct pst_status {
	int32_t pst_idx;		/* Index for further pstat() requests */
	int32_t pst_uid;		/* Real UID */
	int32_t pst_pid;		/* Process ID */
	int32_t pst_ppid;		/* Parent process ID */
	int32_t pst_dsize;		/* # real pages used for data */
	int32_t pst_tsize;		/* # real pages used for text */
	int32_t pst_ssize;		/* # real pages used for stack */
	int32_t pst_nice;		/* Nice value */
	char pst_cmd[PST_CLEN];		/* Command line for the process, if available */
	char pst_ucomm[PST_UCOMMLEN];	/* executable basename the process is running */
};

/*
 * Function prototype.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern int	oc_pstat_getproc( struct pst_status *buf,
				  size_t elemsize,
				  size_t elemcount,
				  int index );

#ifdef __cplusplus
}
#endif

#elif defined(__hpux)

#include <sys/param.h>
#include <sys/pstat.h>

#define oc_pstat_getproc	pstat_getproc

#else

#warning "Unsupported OS"

#endif /* __os */

#endif /* OC_PSTAT_H */
