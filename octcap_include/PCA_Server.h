// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommAPI
//                               -----------------------
//
//
//  PURPOSE: Provides access to the server side of the API
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Server.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Server.h $
//       $Revision: 1.18 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_SERVER_H)
#define __PCA_SERVER_H

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

              C L A S S    P C A _ S e r v e r
__________________________________________________________________________
*/

class PCA_BufferAllocator;
class PCA_Queue;
class PCA_ServerImpl;
class PCA_Message;
class PCA_SessionFactory;
class PCA_Session;

/**
 * Provides access to the server side of the API.
 *
 * This class is intended to be derived, in order to implement the actual
 * server.
 * User must specialize call control primitives.
 *
 * @short Server side of the communication API.
 */
class PCA_Server {
public:
   /**
     * Constructor.
     *
     * Builds a server object
     */
   PCA_Server();

   /**
     * Destructor.
     *
     * Destroys client object and its implementation, if any.
     * Destroys underlying components in the communication API
     */
   virtual ~PCA_Server();

   /**
     * Initialization.
     *
     * Initializes a server and sets-up its underlying components in the API.
     * This function must ALWAYS be called after the server is created.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded.
     *    @li FAILURE - operation failed.
     *
     * @param P_inboundQueue pointer to the user-provide inbound queue
     * @param P_sessionFactory user-provided session factory
     * @param P_bufferAllocator user-provided buffer allocator for inbound PCA messages
     * @param P_outQueueSize size of the outbound queue
     * @param P_outQueueHighWatermark threshold for overflow condition
     * @param P_outQueueLowWatermark threshold for overflow condition completion
     * @param P_status result of the operation
     */
   void init(
      PCA_Queue* P_inboundQueue,
      PCA_SessionFactory* P_sessionFactory,
      PCA_BufferAllocator* P_bufferAllocator,
      int P_outQueueSize,
      int P_outQueueHighWatermark, int P_outQueueLowWatermark,
      PCA_Status& P_status
   );

   /**
     * Obsolete initialisation
     *
     * The following version of the init method is OBSOLETE.
     * It is provided only for compatibility needs 
     * and is no more supported.
     * Do prefer the previous one.
     */
   void init(
      PCA_Queue* P_inboundQueue,
      PCA_SessionFactory* P_sessionFactory,
      int P_outQueueSize,
      int P_outQueueHighWatermark, int P_outQueueLowWatermark,
      PCA_Status& P_status
   )
   {
      init(P_inboundQueue,
           P_sessionFactory,
           NULL,
           P_outQueueSize, P_outQueueHighWatermark, P_outQueueLowWatermark,
           P_status);
   };


   /**
     * Connection setup.
     *
     * Set server in the listening state, knowing its own address.
     * Connection setup completes when authorizeClient() followed by either
     * clientConnected() or clientDisconnected() are invoked by the
     * communication API
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded
     *    @li FAILURE - operation failed.
     *
     * @param P_serverName name of the server
     *                     Format is "serviceName@serverProcessName"
     * @param P_status result of the operation
     * @see #close
     * @see #authorizeClient
     * @see #clientConnected
     * @see #clientDisconnected
     */
   void open(const Str& P_serverName, PCA_Status& P_status);

   /**
     * Shutdown.
     *
     * Closes a connection.
     * This function can only be called when there is no client connected.
     *
     * @see #open
     */
   void close();

   /**
     * Sends a message to a client.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded.
     *    @li OVERFLOW - operation suceeded but Tx path is overflowed.
     *    @li BUSY - operation failed because Tx path is jamed.
     *                       This status usually follows a number of OVERFLOW.
     *    @li MSG_BAD - message format is not correct.
     *    @li NOT_ACTIVE - server is disabled.
     *    @li FAILURE - operation failed for internal reason.
     * If status is BUSY message remains under the reponsibility of the server,
     * otherwise it is managed/deleted by the underlying stack.
     *
     * @param P_message message to be sent
     * @param P_status result of the operation
     * @see #enable
     * @see #disable
     */
   void send(PCA_Message* P_message, PCA_Status& P_status);

   /**
     * Forces transmission of any blocked buffer.
     *
     * This does not actually apply to the server.
     * It simply downwards the command to the API.
     *
     * @see #setCnxEnableBuffering
     */
   void flush();

   /**
     * Creates a session.
     *
     * The status is updated as follows:
     *    @li NO_ERROR - operation suceeded.
     *    @li BUSY - operation failed, outbound path is overflowed.
     *         Caller should no longer attempt to open a session,
     *         untill its sessionResume() function gets invoked
     *    @li NOT_ACTIVE - server is disabled.
     *    @li FAILURE - operation failed.
     *
     * @param P_status result of the operation
     * @return pointer to the created session object if operation succeeded
     * @see #abortSession
     * @see #closeSession
     * @see #closeBrokenSessions
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
     * @param P_status error code value to send in the abort error message
     * @see #openSession
     * @see #closeSession
     * @see #closeBrokenSessions
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
     * @see #closeBrokenSessions
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
     * @see #closeBrokenSessions
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   void closeSession(PCA_Session* P_session);

   /**
     * Destroys all broken sessions.
     *
     * This function may be called by the server to close easily broken sessions
     * upon clientDisconnected() signal.
     * Broken sessions can also be closed directly by closeSession().
     * The actual deletion of the local session objects may be delayed
     * until objects are unlocked and all pending messages related to the session
     * have been processed.
     *
     * @see #openSession
     * @see #abortSession
     * @see #closeSession
     * @see PCA_Session#lock
     * @see PCA_Session#unlock
     */
   void closeBrokenSessions();

   /**
     * Obsolete re-enable delivery of messages into the inbound queue.
     *
     * Called by the user plug-in to re-enable delivery of incoming messages
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
     * Allows the server to enter the ACTIVE state.
     *
     * Then, once connection is established, server can send/recv data
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
     * Disallows the server from the ACTIVE state.
     *
     * Then server can no longer send or receive data, nor open sessions.
     * This function is typically called when process exits the HA active
     * state
     *
     * @param P_status error status sent to the peer in REJECT messages
     * @see #enable
     * @see #openSession
     * @see #send
     */
   void disable(PCA_Status& P_status);

   /**
     * Notifies the server that further sessions can be opened.
     *
     * Server developer must implement its own processing of such an event.
     * Default implementation is nop.
     *
     * @see #openSession
     */
   virtual void sessionResume();

   /**
     * Notifies the server that a set of sessions gets unflowctl'd.
     *
     * The contents of the argument array is only valid within the scope of the
     * function. It may hold blank entries (NULL)
     * Default implementation is nop
     *
     * @param P_sessionArray the array of sessions getting unflowctl'd
     * @param P_nSessions number of sessions in the array
     * @see #send
     */
   virtual void sendResume(PCA_Session* const *P_sessionArray, int P_nSessions);
  
   /**
     * Informs the server that a new client wishes to connect.
     *
     * The server may either accept or reject the call.
     * If client is accepted, server must then wait for a clientDis/connected to
     * know about the actual completion of the call.
     * Default implementation is accept
     *
     * The status is updated as follows:
     *    @li NO_ERROR - Call accepted
     *    @li FAILURE - Call rejected.
     *
     * @param P_clientName name of the client.
     *                     Format is "instanceName@clientProcessName"
     * @param P_status answer of the server
     * @see #clientConnected
     * @see #clientDisconnected
     */
   virtual void authorizeClient(
      const Str& P_clientName, PCA_Status& P_status
   );

   /**
     * Client successfully connected.
     *
     * Developer is free to refine this function for client management purpose.
     * Default implementation is nop.
     *
     * @param P_clientName name of the client.
     *                     Format is "instanceName@clientProcessName"
     * @param P_clientInfo litteral informations about the client
     * @see #authorizeClient
     * @see #clientDisconnected
     */
   virtual void clientConnected(
      const Str& P_clientName, const Str& P_clientInfo
   );

   /**
     * Client connection is closed (or establishment failed).
     *
     * Developer is free to refine this function for client management purpose.
     *
     * @param P_clientName name of the client.
     *                     Format is "instanceName@clientProcessName"
     * @see #authorizeClient
     * @see #clientConnected
     */
   virtual void clientDisconnected(const Str& P_clientName);

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
    *               false otherwise
    * @see #setCnxLowTransitTime
    * @see #setCnxLowTransitTime
    * @see #flush
    */
   void setCnxEnableBuffering(bool P_flag);

   /**
    * Set the buffer size used to receive messages.
    *
    * For a TCP connection, this parameter controls the rx TCP buffer size.
    *
    * @param P_rxSize size of buffer in bytes
    * @see #setCnxSendBufferSize
    */
   void setCnxRecvBufferSize(int32_t P_rxSize);

   /**
    * Set the buffer size used to send messages.
    *
    * For a TCP connection, this parameter controls the tx TCP buffer size.
    *
    * @param P_txSize size of buffer in bytes
    * @see #setCnxRecvBufferSize
    */
   void setCnxSendBufferSize(int32_t P_txSize);


protected:


private:
   /**
     * Implementation of the server
     */
   PCA_ServerImpl* const impl;

   /**
     * Effective C++
     *
     * To prevent public copy ctor usage: no implementation
     */
   PCA_Server(const PCA_Server&);

   /**
     * Effective C++
     *
     * To prevent public operator= usage: no implementation
     */
   PCA_Server& operator=(const PCA_Server&);

};



#endif // __PCA_SERVER_H
