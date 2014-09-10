// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: Base class for user-defined sessions
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Session.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Session.h $
//       $Revision: 1.7 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_SESSION_H)
#define __PCA_SESSION_H

#include <PCA_Common.h>


/*
__________________________________________________________________________

              C L A S S    P C A _ S e s s i o n
__________________________________________________________________________
*/

class PCA_SessionImpl;

/**
 * Base class for user-defined sessions.
 *
 * A session is made of an interface class and an implementation class.
 * Sessions are allocated via a session factory.
 *
 * @short Base class for user-defined sessions.
 */
class PCA_Session {
   friend class PCA_SessionImpl;
   friend class PCA_SessionFactory;

public:
   /**
    * Originating side for the session.
    *
    *    @li CALLER - local side opened the session
    *    @li CALLEE - remote side opened the session
    *
    * @see #getType
    */
   enum Type { CALLER, CALLEE };

   /**
    * Whether session setup was originated by the local side or not.
    *
    * @return see definition
    * @see #Type
    */
   Type getType() const;


   /**
    * Session state.
    *
    *    @li ACTIVE - session is fully usable
    *    @li REJECTED - session has been rejected by the remote side.
    *                           This has been notified by an ERROR message.
    *                           User should no try to send further messages on
    *                           the message.
    *    @li BROKEN - the associated SLEE is disconnected
    *    @li ZOMBIE - session is already closed, but there are stil some
    *                         message attached to it. It can not be used to send
    *                         further messages
    *
    * @see #getState
    */
   enum State { ACTIVE, REJECTED, BROKEN, ZOMBIE };

   /**
    * Session state.
    *
    * This function should be called prior to send a message.
    *
    * @return see definition
    * @see #State
    */
   State getState() const;

   /**
    * Lock the session object.
    *
    * The lock count of the session is incremented.
    * If the session is closed or aborted the actual deletion of the session
    * object will be delayed until object is unlocked and all pending messages
    * related to the session have been processed.
    *
    * @see #unlock
    * @see PCA_Server#abortSession
    * @see PCA_Server#closeSession
    */
   void lock();

   /**
    * Unlock the session object.
    *
    * The lock count of the session is decremented.
    * If the session is closed or aborted the actual deletion of the session
    * object may be delayed until object is unlocked and all pending messages
    * related to the session have been processed.
    *
    * @see #lock
    * @see PCA_Server#abortSession
    * @see PCA_Server#closeSession
    */
   void unlock();

protected:

protected:
   /**
    * Constructor.
    */
   PCA_Session();

   /**
    * Destructor.
    */
   virtual ~PCA_Session();


private:
   PCA_SessionImpl* impl; // Pointer to session implementation

   /**
     * Effective C++
     *
     * To prevent public copy ctor usage: no implementation
     */
   PCA_Session(const PCA_Session&);

   /**
     * Effective C++
     *
     * To prevent public operator= usage: no implementation
     */
   PCA_Session& operator=(const PCA_Session&);

};



#endif // __PCA_SESSION_H
