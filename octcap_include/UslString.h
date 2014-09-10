//----------------------------------------------------------------------------
//
//                               MODULE   Win32_Porting
//                               ----------------------
//
//
//  PURPOSE: The purpose of this header file is to hide the actual
//           implementation of an USL class to the user modules.
//
//  NOTES and CAUTIONS:
//
//  FILE : UslString.h
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
//       $Source: /SLEE/code/Win32_Porting/UslString.h $
//       $Revision: 1.2 $
//       
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version                                             
//----------------------------------------------------------------------------


/*
 * The purpose of this header file is to hide the actual implementation of an USL
 * class to the user modules.
 * USL classes are either native on HP-UX, or built on the top of STL templates
 * on Windows NT
 */ 
#ifndef __GNUG__
#ifdef WIN32
#include <ntString.h> 

#else
#include <String.h>

#endif
#endif // __GNUG__

