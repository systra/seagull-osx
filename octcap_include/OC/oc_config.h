/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_config.h
 * @brief portability top-header
 *
 * General-purpose configuration file, absorbing differences between various
 * OS'es.  This file is suitable for inclusion both in user-space &
 * kernel-space code.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_config.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_CONFIG_H
#define _OC_CONFIG_H

/**
 * standardize the way the OS name is available from the compiler. allowed
 * names are:
 * 
 * @li __linux__
 * @li __hpux
 */

/**
 * every OS provides a header listing where all the Libc & Syscalls features
 * are made available.  The Single UNIX Specifications does not requires a
 * particular file name.
 *
 * byte-ordering is left outside of the Single UNIX Specification, so we
 * retrieve this information by other means.
 */

#if defined(__linux__) && !defined(__KERNEL__)

#include <features.h>		/* provided by Glibc */
#include <endian.h>

#elif defined(__linux__) && defined(__KERNEL__)

/*
 * configuration used to build the target kernel
 */
#include <linux/config.h>

/*
 * force usage of spinlocks if the kernel wants to use them
 */
#if defined(CONFIG_SMP) && !defined(__SMP__)
# define __SMP__
#endif

#ifdef MODULE
/*
 * load kernel symbols mangling macros.  this must be done prior to
 * any inclusion of other kernel headers
 */
#if defined(CONFIG_MODVERSIONS) && !defined(MODVERSIONS)
#  define MODVERSIONS		/* force it on */
#endif

#ifdef MODVERSIONS
#  include <linux/modversions.h>
#endif

#include <linux/module.h>
#endif /* MODULE */

#elif defined(__hpux) && !defined(_KERNEL)

#include <sys/stdsyms.h>

#if !defined(_BIG_ENDIAN)
#define	_BIG_ENDIAN		/* Memory storage (bytes in word) */
#endif /* _BIG_ENDIAN */

#elif defined(__hpux) && defined(_KERNEL)

#include <sys/stdsyms.h>

#elif defined(_WIN32)

#include <windows.h>
#undef FAR

#elif defined(MSDOS)

#include <msdos.h>

#else

#error "Unsupported OS"

#endif /* __os */

/**
 * at this point, we must have enough information to deduce the underlying
 * architecture word byte-order.
 */

#if !defined(__KERNEL__) && !defined(_KERNEL)

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN    4321
#endif

#if defined(__hpux)

#if defined _BIG_ENDIAN
# define BYTE_ORDER BIG_ENDIAN
#endif
#if defined _LITTLE_ENDIAN
# define BYTE_ORDER LITTLE_ENDIAN
#endif

#endif /* __hpux */

#ifndef BYTE_ORDER
#error "BYTE_ORDER shall be defined"
#endif

#endif /* !__KERNEL__ && !_KERNEL */

/**
 * _XOPEN_SOURCE_EXTENDED is not specified by the Single UNIX Specification:
 * rather, a specific value is assigned to _XOPEN_SOURCE.  However, the HP-UX
 * OS headers expect that the user provides this flag.  Knowing that
 * _HPUX_SOURCE means "use the maximum capacity of the OS", we forecefully
 * define _XOPEN_SOURCE_EXTENDED when _HPUX_SOURCE is there.
 */

#if !defined(__KERNEL__) && !defined(_KERNEL)

#if defined(__hpux) && defined(_HPUX_SOURCE)
# if !defined(_XOPEN_SOURCE_EXTENDED)
#  define _XOPEN_SOURCE_EXTENDED
# endif	/* !_XOPEN_SOURCE_EXTENDED */
#endif /* __hpux && _HPUX_SOURCE */

#endif /* !__KERNEL__ && !_KERNEL */

/**
 * GCC provided the non C-standard "tagged" structure initialization, the
 * ability to some specified members of a structure.  Un-specified fields are
 * initialized to scalar NULL.  See example below:
 * 
 * struct timeval tv = { tv_sec: 1 }
 * 
 * ISO-C99 provides another format for the same purpose:
 *
 * struct timeval tv = { .tv_sec = 1 }
 */

#ifdef _ISOC99_SOURCE
#define GFIELD(f) .f =
#else  /* !_ISOC99_SOURCE */
#ifdef __GNUC_
#define GFIELD(f) f:
#else  /* !__GNUC_ */
#define GFIELD(f)
#endif /* !__GNUC_ */
#endif /* !_ISOC99_SOURCE */

/**
 * ATTRIBUTE_UNUSED gives the ability to flag a variable as unused, for
 * compilation clean-ness purpose.
 */
#if defined(__GNUC__)
#define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#else  /* !__GNUC__ */
#define ATTRIBUTE_UNUSED
#endif /* !__GNUC__ */

/**
 * MS-Windos requires to explicitely declare the symbols as suitable for export
 * in the symbols-table of a shared library (AKA Dynamically Loaded Library,
 * AKA DLL)
 */

#ifdef _WIN32
# ifndef OC_API
#  define OC_API	__declspec(dllimport)
# endif
#else  /* !_WIN32 */
# define OC_API		extern
#endif /* !_WIN32 */

/* backward-compatible naming convention */
#define HPAIN_API	OC_API

/**
 * ISO-C 99 defines a magic __func__ variable, giving the current function
 * name.  Note that __func__ might be replaced either using a litteral string
 * (suitable for pre-processor concatenation) or as an external symbol.
 *
 * HP ANSI C (ISO C-89) does not provide this functionality at the moment.
 * When the current C level is not enough, we define a dumb __func__ value.
 */

#if !defined(__GNUC__) && !defined(__HP_aCC)
#if !(defined(__ia64) && !defined(_KERNEL))
#define __func__ "(nil)"
#endif /* __ia64 && _KERNEL */
#endif /* __GNUC__ && __HP_aCC */

/**
 * explicit disabling of static inlining, when compiling in -DDEBUG mode or
 * when using non GCC compilers, to get full back-trace information.
 */

#ifdef INLINE
#undef INLINE
#endif

#ifdef STATIC_INLINE
#undef STATIC_INLINE
#endif

#if defined(DEBUG)
#  define INLINE
#else  /* !DEBUG */
#  if defined(__GNUC__)
#   define INLINE inline
#  else
#   ifndef __cplusplus		/* not using aCC */
#    ifndef __ia64		/* using HPPA ansic */
#     ifndef __HP_cc		/* using 11.11.02 ansic or earlier:
				   there's no inline keyword support */
#      define INLINE
#     else			/* using 11.11.04+ ansic or later */
#      if (__HP_cc<=111104)	/* using 11.11.04 ansic */
#       ifdef __STDC_EXT__	/* using 11.11.04 ansic in -Ae mode:
				   'inline' keyword is supported for
				   front-end inlining */
#        define INLINE inline
#       else			/* using 11.11.04 ansic in -Aa or -Ac mode:
				   no inline keyword support */
#        define INLINE
#       endif			/* __STDC_EXT__ */
#      else			/* using 11.11.06+ ansic */
#       ifdef __STDC_EXT__	/* using 11.11.06+ ansic in -Ae mode:
				   '__inline' keyword is supported */
#        define INLINE __inline
#       else			/* __STDC_EXT__ */
#        if (__STDC_VERSION__>=199901L)	/* using 11.11.06+ ansic in -AC99 mode:
					   'inline' keyword is supported */
#         define INLINE inline
#        else			/* using 11.11.06+ ansic in -Aa or -Ac mode:
				   no inline keyword support */
#         define INLINE
#        endif			/* __STDC_VERSION__>=199901L */
#       endif			/* __STDC_EXT__ */
#      endif			/* __HP_cc<=111104 */
#     endif			/*__HP_cc  */
#    else			/* using IPF ansic */
#     ifdef __STDC_EXT__	/* using IPF ansic in -Ae mode:
				   '__inline' keyword is supported */
#      define INLINE __inline
#     else			/* __STDC_EXT__ */
#      if (__STDC_VERSION__>=199901L)	/* using IPF ansic in -AC99 mode:
					   'inline' keyword is supported */
#       define INLINE inline
#      else			/* using IPF ansic in -Aa mode:
				   no inline keyword support */
#       define INLINE
#      endif			/*__STDC_VERSION__>=199901L  */
#     endif			/* __STDC_EXT__ */
#    endif			/* __ia64 */
#   else			/* using aCC, ie. support of front-end
				   inlining via 'inline' keyword */
#    define INLINE inline
#   endif /* __cplusplus */
#  endif
#endif /* !DEBUG */

#define STATIC_INLINE static INLINE

/**
 * C++ portability
 */
#ifdef __cplusplus

/**
 * Starting with GCC-3.0, defining the C++ default namespace is mandatory.
 */
#if defined(__GNUG__) && (__GNUC__ >= 3)
using namespace std;
#endif /* __GNUG__ && __GNUC__ >= 3 */

/**
 * some old C++ compilers do not have namespaces
 */
#if (__cplusplus>=199707L) || defined(__GNUG__)
#define HAVE_NAMESPACES
#endif

#endif /* __cplusplus */

/**
 * @def __OC_STR__
 *
 * this macro turns the given numeric or code parameter into a const char*
 * string.  it is handly to turn the pre-processor __LINE__ (or other numeric
 * stuffs) into a printable string.
 *
 * @param s code string to turn into const char*,
 * @see __OC_LINESTR__
 */
#define __OC_STRHELPER__(x)     #x
#define __OC_STR__(y)           __OC_STRHELPER__(y)

/**
 * @def __LINESTR__
 *
 * this macro takes no parameters.  it gives the const char* version of the
 * current source code line, given by __LINE__.
 */
#define __LINESTR__             __OC_STR__(__LINE__)

#endif /* _OC_CONFIG_H */
