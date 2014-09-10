/**
 * @file oc_sys_select.h
 * @brief all-in-one access to select(2)
 *
 * provide declaration & manifest constant accross OS for select(2) &
 * associated stuffs.
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

#ifndef OC_SYS_SELECT_H
#define OC_SYS_SELECT_H

#include <OC/oc_config.h>		/* must be before system headers */

#include <unistd.h>

/*
 * to get access to select(2) declaration:
 *
 * @li HP-UX wants only <sys/time.h>,
 * @li Linux/Glibc wants <sys/time.h>, <sys/types.h>, <unistd.h>,
 * @li UNIX2000 wants only <sys/select.h>.
 */

#include <OC/oc_types.h>

#if defined(__linux) || defined(__hpux)
#include <sys/time.h>
#else  /* !__linux && !__hpux */
#include <sys/select.h>
#endif /* !__linux && !__hpux */

/*
 * Number of bits per word of `fd_set' (some code assumes this is 32).  This is
 * defined under _BSD_SOURCE OR _SVID_SOURCE
 */
#ifndef NFDBITS
#define NFDBITS		__NFDBITS
#endif

/*
 * UNIX & BSD states that the "FD_SETSIZE" value is defined.  we assumes that
 * it is correctly set, whether "_USE_BIG_FDS" is defined on compilation
 * command-line or not.
 *
 * Furthermore, depending on the C compiler used on HP-UX (old ANSI-89 C or new
 * aCC trimmed down to C-89), the considered select(2) protoype is not the
 * same.
 */

#if !defined(_XOPEN_SOURCE_EXTENDED)

STATIC_INLINE int
oc_select (int n, fd_set *rm, fd_set *wm, fd_set *em, struct timeval *tp)
{
	return select((size_t) n, (int *)rm, (int *)wm, (int *)em, tp);
}

#else  /* _XOPEN_SOURCE_EXTENDED */

STATIC_INLINE int
oc_select (int n, fd_set *rm, fd_set *wm, fd_set *em, struct timeval *tp)
{
	return select(n, rm, wm, em, tp);
}

#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* OC_SYS_SELECT_H */
