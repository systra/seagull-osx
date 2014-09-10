// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_ExecApi
//                               -----------------------
//
//
//  PURPOSE: PIC registry interface class.
//
//  NOTES and CAUTIONS:
//
//  FILE : PIC_Registry.h
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
//       $Source: /SLEE/code/PLUGIN_ExecApi/PIC_Registry.h $
//       $Revision: 1.4 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PIC_REGISTRY_H)
#define __PIC_REGISTRY_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#if (__cplusplus >= 199707L || __GNUG__)
#  include <string>
#  ifdef _HP_NAMESPACE_STD
   using namespace std;
#  endif // _HP_NAMESPACE_STD
typedef string Str;
#else
#  include <UslString.h>
   typedef String Str;
#endif

/*
__________________________________________________________________________

              C L A S S    P I C _ R e g i s t r y
__________________________________________________________________________
*/

class PIC_RegistryImpl;

/**
 * PIC registry interface class.
 *
 * This class provides non virtual members that offer some basic services
 * on PIC attrubutes to the plug-in.
 *
 * @short PIC registry interface.
 */
class PIC_Registry {
public:

   /**
    * Constructor.
    */

   PIC_Registry();

   /**
    * Destructor.
    */
   ~PIC_Registry();


public:
// +-------------------------------------------------------------------+
// + The following functions are made available to the plug-in writter +
// +-------------------------------------------------------------------+

   /**
    * Retrieves the logical name of the PIC process.
    *
    * This function should be used by the plug-in writter to build the plug-in
    * address for the PCA.
    *
    * @return see definition
    */
   Str& getProcessName();


protected:


private:
   /**
     * Implementation of the PIC_Registry.
     */
   PIC_RegistryImpl* const impl;
};

#endif // __PIC_REGISTRY_H
