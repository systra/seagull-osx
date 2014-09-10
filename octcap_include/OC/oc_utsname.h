/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_utsname.h
 * @file wrapper on uname(2), getting the UNIX system name
 *
 * common wrapper over the UNIX system name.  note a major difference between
 * Linux & HP-UX:
 *
 * @li HP-UX system name is the non-qualified one, limited to 8 characters (9
 *     with the NULL termination).  FQDN is added as an alias in /etc/hosts,
 *
 * @li Linux system name is the FQDN.  application seeking the NQDN must
 *     replace the first '.' by '\0' & use the beginning.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_inttypes.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef OC_UTSNAME_H
#define OC_UTSNAME_H

#include <OC/oc_config.h>

/*
 * Even though SingleUnix standard specifies the struct utsname, it does not
 * specify any thing about the size of char array's for name revison etc.
 */

#include <sys/utsname.h>

#ifdef __linux

#define SYS_NMLN	_UTSNAME_LENGTH
#define UTSNAME		SYS_NMLN
#define _SYS_NMLN	SYS_NMLN
#define UTSLEN		SYS_NMLN

#endif /* __linux */

#endif /* _OC_UTSNAME_H */
