// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: Define Plug-in Comm Api (PCA) common data and tools
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Common.h
//____________________________________________________________________________
//
// Copyright (c) 1996 Hewlett-Packard Company, All Rights Reserved.
// RESTRICTED RIGHTS LEGEND Use, duplication, or disclosure by the U.S.
// Government is subject to restrictions as set forth in sub-paragraph
// (c)(1)(ii) of the Rights in Technical Data and Computer Software
// clause in DFARS 252.227-7013.
//
// Hewlett-Packard Company
// 3000 Hanover Street
// Palo Alto, CA 94304 U.S.A.
// Rights for non-DOD U.S. Government Departments and Agencies are as
// set forth in FAR 52.227-19(c)(1,2).
//____________________________________________________________________________
//
//
//  AUTHOR:
//                                               DATE: 
//
//  Rev: 
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Common.h $
//       $Revision: 1.10 $
//       
//----------------------------------------------------------------------------
// end_is


#if !defined(__PCA_COMMON_H)
#define __PCA_COMMON_H

/**
 * Define Plug-in Comm Api (PCA) common data and tools
 */

/**
 * Error codes.
 *
 * Error codes are either success, warning or failure status
 *
 *    @li PCA_NO_ERROR
 *       - Operation succeeded
 *    @li PCA_OVERFLOW
 *       - Warning: operation succeded but target device is overflowed
 *    @li PCA_FAILURE
 *       - Operation failed. Cause is unspecified, this may be an internal
 *         error
 *    @li PCA_BUSY
 *       - Operation failed. The target device is too heavy loaded to process
 *         the request
 *    @li PCA_MSG_UNKNOWN
 *       - Message type is unknown
 *    @li PCA_MSG_BAD
 *       - Message format is bad
 *    @li PCA_NO_CLIENT
 *       - Session setup failed because no SLEE client is connected yet
 *    @li PCA_NO_VC
 *       - Session setup failed because not enough VC are configured
 *    @li PCA_POOL_EXHAUSTED
 *       - SOperation failed, because an internal object pool is exhausted
 *    @li PCA_NOT_ACTIVE
 *       - Operation failed because the device is not in HA active state
 *    @li PCA_VERSION_MISMATCH
 *       - Connection setup failed because SLEE and plug-in do not use the
 *         same version of PCA.
 *    @li PCA_ABORTED
 *       - Session has been aborted at peer side.
 */
enum PCA_Status {
   PCA_NO_ERROR=0,
   // UX11-32MIGR : CrOb200 : NONE
   PCA_OVERFLOW,
   PCA_FAILURE=1000,
   PCA_BUSY, 
   PCA_MSG_UNKNOWN, 
   PCA_MSG_BAD, 
   PCA_NO_CLIENT, 
   PCA_NO_VC, 
   PCA_POOL_EXHAUSTED,
   PCA_NOT_ACTIVE, 
   PCA_VERSION_MISMATCH,
   PCA_ABORTED
};

#define IS_SUCCESS(P_Status)		 	((P_Status) == PCA_NO_ERROR)
#define IS_RECOVERABLE(P_Status)		((P_Status) < PCA_FAILURE)

#endif // __PCA_COMMON_H

