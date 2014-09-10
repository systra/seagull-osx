// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: Provides access to the client side of the API
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Client.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Client.h $
//       $Revision: 1.19 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_CLIENT_H)
#define __PCA_CLIENT_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#include <inttypes.h>
#if (__cplusplus >= 199707L || __GNUG__)
#include <string>
#ifdef _HP_NAMESPACE_STD
    using namespace std;
#endif
typedef string Str;
#else
#include <UslString.h>
typedef String Str;
typedef int bool;
#endif
#include <PCA_Common.h>

/*
__________________________________________________________________________

              C L A S S    P C A _ C l i e n t
__________________________________________________________________________
*/

class PCA_BufferAllocator;
class PCA_Queue;
class PCA_ClientImpl;
class PCA_Message;
class PCA_SessionFactory;
class PCA_Session;

/**
 * Provides access to the client side of the API
 *
 * This class is intended to be derived, in order to implement a client
 * (like the actual SLEE)
 * User must specialize call control primitives
 *
 * @short Client side of the communication API.
 */
class PCA_Client {
public:
   /**
     * Constructor.
     *
     * Builds a client object.
     * The object must then be initialized by init().
     * @see #init
     */
   PCA_Client();

   /**
     * Destructor.
     *
     * Destroys client object and its implementation, if any.
     * Destroys underlying components in the communication API.
     * close() must be called prior to deleting the object.
     * @see #close
     */
   virtual ~PCA_Client();

   /**
     * Initialization.
     *
     * Initializes a client and sets-up its underlying components in the API.
     * Allocates the client implentation object.
     * This function must ALWAYS be called after the client is created.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded
     *    @li FAILURE - operation failed.
     *
     * @param P_serverName name of the target server.
     *                     Format is "serviceName@serverProcessName".
     * @param P_clientInfo a litteral information transfered from the client
     *                     to the server at connection setup time. The format
     *                     of this string is private to client and server.
     * @param P_inboundQueue pointer to the user-provide inbound queue.
     * @param P_sessionFactory user-provided session factory.
     * @param P_bufferAllocator user-provided buffer allocator for inbound PCA messages
     * @param P_outQueueSize size of the outbound queue.
     * @param P_outQueueHighWatermark threshold for overflow condition.
     * @param P_outQueueLowWatermark threshold for overflow condition completion.
     * @param P_totalVcps  total size of VC pool.
     * @param P_clientVcps size of client VC pool.
     * @param P_status result of the operation.
     */
   void init(
      const Str& P_serverName,
      const Str& P_clientInfo,
      PCA_Queue* P_inboundQueue,
      PCA_SessionFactory* P_sessionFactory,
      PCA_BufferAllocator* P_bufferAllocator,
      int P_outQueueSize,
      int P_outQueueHighWatermark, int P_outQueueLowWatermark,
      int P_totalVcps, int P_clientVcps,
      PCA_Status& P_status
   );
   /**
     * Obsolete initialization.
     *
     * The following version of the init method is OBSOLETE. 
     * It is provided only for compatibility needs 
     * and is no more supported.
     * Do prefer the previous one.
     */
   void init(
      const Str& P_serverName,
      const Str& P_clientInfo,
      PCA_Queue* P_inboundQueue,
      PCA_SessionFactory* P_sessionFactory,
      int P_outQueueSize,
      int P_outQueueHighWatermark, int P_outQueueLowWatermark,
      int P_totalVcps, int P_clientVcps,
      PCA_Status& P_status
   )
   {
      init(P_serverName, P_clientInfo,
           P_inboundQueue, P_sessionFactory,
           NULL,
           P_outQueueSize, P_outQueueHighWatermark, P_outQueueLowWatermark,
           P_totalVcps, P_clientVcps,
           P_status);
   };

   /**
     * Connection setup.
     *
     * Initiates connection setup.
     * Connection setup completes when either stateOpened() or stateClosed() is
     * invoked by the communication API.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded
     *    @li FAILURE - operation failed.
     *
     * @param P_status result of the operation.
     * @see #close
     * @see #stateOpened
     * @see #stateClosed
     */
   void open(PCA_Status& P_status);

   /**
     * Shutdown.
     *
     * Closes a connection.
     * Cleans up pending outbound messages and broken sessions .
     *
     * @see #open
     */
   void close();

   /**
     * Sends a message to the server.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded
     *    @li OVERFLOW - operation suceeded but Tx path is overflowed
     *    @li BUSY - operation failed because Tx path is jamed
     *                       This status usually follows a number of OVERFLOW
     *    @li MSG_BAD - message format is not correct
     *    @li NOT_ACTIVE - client is disabled
     *    @li FAILURE - operation failed for internal reason.
     * If status is BUSY message remains under the reponsibility of the client,
     * otherwise it is managed/deleted by the underlying stack.
     *
     * @param P_message message to be sent.
     * @param P_status result of the operation.
     */
   void send(PCA_Message* P_message, PCA_Status& P_status);

   /**
     * Forces transmission of any blocked buffer.
     *
     * This does not actually apply to the client.
     * It simply downwards the command to the API.
     */
   void flush();

   /**
     * Creates a session.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded
     *    @li BUSY - operation failed, outbound path is overflowed
     *         Caller should no longer attempt to open a session,
     *         untill its sessionResume() function gets invoked
     *    @li FAILURE - operation failed.
     *
     * @param P_status result of the operation.
     * @return pointer to the created session object if operation succeeded.
     * @see #abortSession
     * @see #closeSession
     * @see #sessionResume 
     * @see #enable
     * @see #disable
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   PCA_Session* openSession(PCA_Status& P_status);

   /**
     * Aborts a session.
     *
     * The local session is closed with the propagation of an
     * abort error message and an error code value.
     * The actual deletion of the local session object may be delayed
     * until object is unlocked and all pending messages related to the session
     * have been processed.
     *
     * @param P_session session to be aborted
     * @param P_errText text to send in the abort error message
     * @param P_status error code to send in the abort error message
     * @see #openSession
     * @see #closeSession
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   void abortSession(PCA_Session* P_session,const Str& P_errText,int P_errValue);

   /**
     * Aborts a session.
     *
     * The local session is closed with the propagation of an
     * abort error message.
     * The actual deletion of the local session object may be delayed
     * until object is unlocked and all pending messages related to the session
     * have been processed.
     *
     * @param P_session session to be aborted
     * @param P_errText text to send in the abort error message
     * @see #openSession
     * @see #closeSession
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   void abortSession(PCA_Session* P_session,const Str& P_errText);

   /**
     * Closes a session.
     *
     * The actual deletion of the local session object may be delayed
     * until object is unlocked and all pending messages related to the session
     * have been processed.
     *
     * @param P_session session to be closed
     * @see #openSession
     * @see #abortSession
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   void closeSession(PCA_Session* P_session);

   /**
     * Obsolete re-enable delivery of messages into the inbound queue.
     *
     * Called by the above code (like SLEE) to re-enable delivery of incoming messages
     * when the inbound queue exits the overflowed state
     *
     * This method is OBSOLETE.
     * It is provided only for compatibility needs
     * and is no more supported.
     * Implementation is nop.
     *
     * @see PCA_Queue#get
     * @see PCA_Queue#isOverflowed
     */
   void recvResume() {};

   /**
     * Allows the client to enter the ACTIVE state.
     *
     * Then, once connection is established, client can send/recv data
     * within sessions.
     * This function must be called during connection setup when process enters
     * the HA ACTIVE state.
     *
     * @see #disable
     * @see #openSession
     * @see #send
     */
   void enable();
     
   /**
     * Disallows the client from the ACTIVE state.
     *
     * Then it can no longer send or receive data, nor open sessions.
     * This function is typically called when process exits the HA active
     * state.
     *
     * @param P_status error status sent to the peer in REJECT messages.
     * @see #enable
     * @see #openSession
     * @see #send
     */
   void disable(PCA_Status& P_status);

   /**
     * Outbound flow control.
     *
     * Notifies the client that further sessions can be opened.
     * Client developer must implement its own processing of such an event.
     * Default implementation is nop.
     *
     * @see #openSession
     */
   virtual void sessionResume();

   /**
     * Outbound flow control.
     *
     * Notifies the client that a set of sessions gets unflowctl'd.
     * The contents of the argument array is only valid within the scope of the
     * function. It may hold blank entries (NULL).
     * Default implementation is nop.
     *
     * @param P_sessionArray the array of sessions getting unflowctl'd.
     * @param P_nSessions number of sessions in the array.
     * @see #send
     */
   virtual void sendResume(PCA_Session* const *P_sessionArray, int P_nSessions);

   /**
     * Connection opened.
     *
     * Client is notified this event after an open() request when connection
     * actually turns opened.
     * Default implementation is nop.
     */
   virtual void stateOpened();

   /**
     * Connection closed.
     *
     * Client is notified this event when the connection is broken.
     * This may happen either in the setup phase or once connection is
     * established.
     * Developer must implement its own processing of this event, s/he can not
     * delete the client immediately.
     * Default implementation is nop.
     */
   virtual void stateClosed();

   /**
    * Sets the minimum low load buffering time.
    *
    * Sets the minimum time buffered messages have to wait before being sent
    * during low traffic load, that is, when PCA buffers are not full.
    * Shorter is "P_ltTime" parameter, upper is the CPU consumption. 
    * Consequently, it's not advice to set this value under 1 msecond.
    * It is effective only when buffering is enabled.
    *
    * @param P_ltTime time in useconds.
    * @see #setCnxEnableBuffering
    * @see #setCnxHighTransitTime
    */
   void setCnxLowTransitTime(int32_t P_ltTime);

   /**
     * Sets the maximum low load buffering time.
     *
     * Sets the maximum time buffered messages may wait before being sent
     * during low traffic load, that is, when PCA buffers are not full.
     * It is effective only when buffering is enabled.
     *
     * @param P_htTime time in useconds.
     * @see #setCnxEnableBuffering
     * @see #setCnxLowTransitTime
     */
   void setCnxHighTransitTime(int32_t P_htTime);

   /**
    * Enable or disable buffering of outgoing messages.
    *
    * For performance consideration, buffering of outgoing messages should
    * not be disabled unless it is really necessary.
    *
    * @param P_flag true if buffering should be enabled,
    *               false otherwise.
    * @see #setCnxLowTransitTime
    * @see #setCnxHowTransitTime
    * @see #flushOutBuffer
    */
   void setCnxEnableBuffering(bool P_flag);

   /**
    * Set the buffer size used to receive messages.
    *
    * For a TCP connection, this parameter controls the rx TCP buffer size.
    *
    * @param P_rxSize size of buffer in bytes.
    * @see #setCnxSendBufferSize
    */
   void setCnxRecvBufferSize(int32_t P_rxSize);

   /**
    * Set the buffer size used to send messages.
    *
    * For a TCP connection, this parameter controls the tx TCP buffer size.
    *
    * @param P_txSize size of buffer in bytes.
    * @see #setCnxRecvBufferSize
    */
   void setCnxSendBufferSize(int32_t P_txSize);

protected:


private:
   /**
     * Implementation of the client.
     */
   PCA_ClientImpl* const impl;

   /**
     * Effective C++
     *
     * To prevent public copy ctor usage: no implementation
     */
   PCA_Client(const PCA_Client&);

   /**
     * Effective C++
     *
     * To prevent public operator= usage: no implementation
     */
   PCA_Client& operator=(const PCA_Client&);

};



#endif // __PCA_CLIENT_H
