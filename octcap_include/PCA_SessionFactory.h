// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: Creates and Destroys session objects
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_SessionFactory.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_SessionFactory.h $
//       $Revision: 1.11 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_SESSIONFACTORY_H)
#define __PCA_SESSIONFACTORY_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#if (__cplusplus >= 199707L || __GNUG__)
#  include <string>
#ifdef _HP_NAMESPACE_STD
  using namespace std;
#endif
   typedef string Str;
#else
#  include <UslString.h>
   typedef String Str;
#endif
#include <PCA_Session.h>
/*
__________________________________________________________________________

           C L A S S    P C A _ S e s s i o n F a c t o r y
__________________________________________________________________________
*/


/**
 * Creates and Destroys session objects.
 *
 * This class must be specialized by the user to handle its own sessions.
 *
 * @short creates/deletes session objects
 */
class PCA_SessionFactory {
public:
   /**
    * Constructor.
    */
   PCA_SessionFactory();

   /**
    * Destructor.
    */
   virtual ~PCA_SessionFactory();

   /**
    * Session creation.
    *
    * Default implementation creates a base session object
    *
    * @param P_sessionType either session is incoming or outgoing
    * @param P_status result of the operation. The output value of this
    *                 parameter is left to developer. This is intended to
    *                 personnalize error handling.
    * @return pointer to the new session object, or NULL if operation failed
    * @see #getLastErrorText
    */
   virtual PCA_Session* createSession(
      PCA_Session::Type P_sessionType, PCA_Status& P_status
   );
   
   /**
    * Session destruction.
    *
    * @param P_session pointer to the object to be destroyed
    */
   virtual void destroySession(PCA_Session* P_session);

   /**
    * Diagnostic.
    *
    * This function is called when an error occured in createSession(), to
    * retrieve the associated diagnostic.
    * Since, in the default implementation the only failure cause is memory
    * overflow this returns so.
    *
    * @return an error text describing the last error
    * @see #createSession
    */
   virtual const Str getLastErrorText();
   

protected:


private:
   /**
     * Effective C++
     *
     * To prevent public copy ctor usage: no implementation
     */
   PCA_SessionFactory(const PCA_SessionFactory&);

   /**
     * Effective C++
     *
     * To prevent public operator= usage: no implementation
     */
   PCA_SessionFactory& operator=(const PCA_SessionFactory&);

};



#endif // __PCA_SESSIONFACTORY_H
