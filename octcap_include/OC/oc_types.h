/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file OC/oc_types.h
 * @brief system types portable declaration.  includes integer types.
 *
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_types.h>
 * @endverbatim
 * 
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 * 
 * @see oc_inttypes.h
 */

#ifndef _OC_TYPE_H
#define _OC_TYPE_H

#include <OC/oc_config.h>
#include <stdarg.h>

#if defined(__linux__) && defined(__KERNEL__)
# include <linux/types.h>
# include <linux/param.h>
#else
# include <sys/types.h>
# include <sys/time.h>
#endif /* __linux && __KERNEL__ */

#include <OC/oc_inttypes.h>

#ifdef __linux__
/*
 * For FTC..
 */
typedef int spu_t;
#endif /* __linux__ */

/*
 * HP-UX does not define the "struct timeval" member "tv_usec" as of type
 * suseconds_t (which is not defined at all), as stated by UNIX2000.  force
 * this type definition.  UNIX2000 also state that "suseconds_t" is unchanged
 * with regards to "long".
 */
#ifdef __hpux
typedef long suseconds_t;
#endif /* __hpux */

/*
 * Some types needed by the kernel-space SS7 H/W drivers & some other
 * user-space tools.
 */

typedef char char_t;
#if !defined(__hpux)
typedef unsigned char uchar_t;	/* in /usr/conf/h/stream.h */
#endif
typedef unsigned int boolean_t;
typedef int return_t;

enum { bFalse = 0, bTrue = 1 };
enum { retFail_Objdeleted = -2, retFail = -1, retOk = 0 };

/**
 * @defgroup OC-types
 * @{
 *
 * Opencall types used in external API's
 */

typedef double COM_T_real;

/*
 * dates & time
 */
struct COM_timeval {
	COM_T_uint32 tv_sec;	/* seconds */
	COM_T_int32 tv_usec;	/* microseconds */
};
typedef struct COM_timeval COM_T_timeval;

typedef COM_T_uint32 COM_T_dateStamp;

/*
 * void COM_M_timeval2octimeval(COM_T_timeval dest, struct timeval src)
 */
#define COM_M_TIMEVAL2OCTIMEVAL(dest,src)				\
	{								\
		(dest).tv_sec  = (COM_T_uint32)((src).tv_sec);		\
		(dest).tv_usec = (COM_T_int)((src).tv_usec);		\
	}

/*
 * void COM_M_octimeval2timeval(struct timeval src, COM_T_timeval dest)
 */
#define COM_M_OCTIMEVAL2TIMEVAL(dest,src)				\
	{								\
		(dest).tv_sec  = (time_t)((src).tv_sec);		\
		(dest).tv_usec = (suseconds_t)((src).tv_usec);		\
	}

/* backward compatible names & macros */
#define tag_COM_T_timeStamp	COM_timeval
#define timeval_32		COM_timeval
#define COM_T_timeStamp		COM_T_timeval

#ifndef Long_in_Integer
#define Long_in_Integer(dest,src) (dest) = (int)(src)
#endif

#ifndef tvalfromCOM
#define tvalfromCOM		COM_M_OCTIMEVAL2TIMEVAL
#endif

#ifndef COMfromtval
#define COMfromtval		COM_M_OCTIMEVAL2TIMEVAL
#endif

/*
 * explicit union tagging
 */
typedef int32_t COM_T_union;
/* Followed by type data, length dependant on actual union */
typedef uint8_t COM_T_lenString;
typedef uint8_t COM_T_string;
/* Followed by string data, length dependant on actual string */
typedef uint8_t COM_T_lenBcd;
typedef uint8_t COM_T_bcd;
/* Followed by bcd data, length dependant on actual bcd */

typedef struct {
	COM_T_byte len;
	COM_T_byte subIdBytes[31];
} COM_T_objectId;

typedef struct {
	COM_T_objectId oid;
	COM_T_byte mask[4];
} COM_T_maskedObjectId;

#if defined(__KERNEL__) || defined(_KERNEL)
/* Convert the milli seconds to ticks. */
#define MS2TICKS(ms)	( (unsigned long) (ms) * HZ / 1000 )
/* Convert the ticks to milli seconds. */
#define TICKS2MS(ticks)	( (unsigned long) (ticks) * 1000 / HZ )
#endif /* __KERNEL__ || _KERNEL */

#if defined(__linux__) && defined(__KERNEL__)
/* Convert usecs to ticks */
static inline int
drv_usectohz (int usecs) {
	return ( ( (unsigned long) usecs * HZ) / 1000000 );
}
#endif /* __linux__ && __KERNEL__ */

/**
 * @}
 */

#endif /* _OC_TYPE_H */
