//----------------------------------------------------------------------------
//
//                               MODULE   Win32_Porting
//                               ----------------------
//
//
//  PURPOSE: Includes the right files for UNIX select(2) function,
//           depending on target OS, either HP-UX or Windows NT
//
//  NOTES and CAUTIONS:
//
//  FILE : Select.h
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
//       $Source: /SLEE/code/Win32_Porting/Select.h $
//       $Revision: 1.4 $
//       
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version                                             
//----------------------------------------------------------------------------

/*
 * Includes the right files for UNIX select(2) function,
 * depending on target OS, either HP-UX or Windows NT
 */
#ifdef WIN32
#  include <winsock2.h>
#  undef NO_ERROR         // Noisy definition
#  undef ERROR            //      "
#  undef IGNORE           //      "

#else
#  include <sys/time.h>
#  include <string.h>     // for FD_ZERO() that uses memset()

#endif
