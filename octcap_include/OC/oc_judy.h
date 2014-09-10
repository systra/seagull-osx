/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file oc_judy.h
 * @brief wrapper over Judy arrays
 *
 * hp opencall wrapper over the Judy lib, re-specify the JUDYERROR() macro.
 * 
 * Use it using:
 *
 * @verbatim
 * #include <OC/oc_judy.h>
 * @endverbatim
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _OC_JUDY_H
#define _OC_JUDY_H


#include <HP_AIN_ERRORS.h>

/* This is the macro that the Judy macro APIs uses for return codes of -1:*/

#ifndef JUDYERROR_NOTEST

#include <ttlCommon.h>

#define JUDYERROR(CallerFile, CallerLine, JudyFunc, JudyErrno, JudyErrID){ \
 TTL_log(TTL_E_LOG_ERROR, TTL_E_NEW_THREAD,                                \
	 JUDY_LIB_ERROR,                                                   \
         TTL_M_STR(CallerFile),                                            \
	 TTL_M_INT(CallerLine),                                            \
      	 TTL_M_STR(JudyFunc),                                              \
	 TTL_M_INT(JudyErrno),                                             \
	 TTL_M_INT(JudyErrID),TTL_M_EOA);     }

#endif /* JUDYERROR_NOTEST */

/* This error handling macro must be included before the
   #include <Judy.h> statement
*/
#include <Judy.h>

#endif /* _OC_JUDY_H */
