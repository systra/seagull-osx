//------------------------------------------------------------------------------
//
//                               MODULE   IsupProbe.h
//                               --------------------
//
//
//  PURPOSE: 
//
// = FILENAME
//     IsupProbe.h
//
// = AUTHOR(S)
//           HP OC SS7 ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).
//

// 
//
// $Source: /ISUP/code/isupcore/IsupProbe.h $
// $Revision: 2.7 $
// 
//
//------------------------------------------------------------------------------
#ifndef ISUP_PROBE_H
#define ISUP_PROBE_H

#include <IsupCommon.h>

#define MAX_MSG_LENGTH 300
#define LOCAL_MTP_BUFFER_LENGTH 300
#define LOCAL_SCCP_BUFFER_LENGTH 256

class IsupMgr;
class IsupAP;

class IsupProbe {

   // = TITLE
   //     HP OC ISUP base class for Probe objects IsupSMProbe and IsupBPProbe.
   //	   (<{VERSION 2.0}>)
   //
   // = DESCRIPTION
   // = BEGIN<INDENT>
   // This class is the base class for the two Probe types; IsupSMProbe and
   // IsupBPProbe. It implements the common functions for IPC configuration, 
   // opening/closing the Probes.
   //
   // The creation of Probe objects is achieved by IsupMgr methods (see IsupMgr 
   // MAN page). These methods only instantiate and initialize the Probe 
   // objects. Therefore, it's necessary to <{explicitly}> <{open}> a connection with the
   // HP OC SS7 Stack. Probe destruction operates in a similar way.
   // First, the Probe must be <{closed}> before it is destroyed
   // by the appropriate method of the IsupMgr object.
   //
   // Usually <{IPC configuration}> is not required. HP OC ISUP provides the user
   // with default buffers for communication between the Application and the HP OC 
   // SS7 stack. In order to optimize performance by reducing the number of IPC 
   // system calls, it may be necessary to modify the attributes of these default buffers. 
   // In this way, it is possible to alter buffer size, transit time and also to flush them.
   // = END<INDENT>
   
 public:   
   //
   // = METHODS
   //

   virtual ISUP::OpenStatus open(ISUP::ConnectionType P_type) = 0;
   // This method connects the Probe object with the HP OC SS7 Stack using a primary or
   // a secondary connection type. Primary correspond to an active connection and secondary
   // means that the connection is standby and needs to be enabled before use.
   //
   // <{Return Status}>
   //  NO_ERROR          - probe object ready.
   //  NO_CONFIG         - configuration file not accessible.
   //  BAD_GLOBAL_CONFIG - incorrect information parsed in file.
   //  CONNECT_INT       - connection attempt rejected.
   //  API_BUSY          - switchover in progress.
   //  ALREADY_OPEN      - the probe is already connected to the
   //                      SS7 process.
   //  INTERNAL_ERROR    - error in HP OC ISUP subsystem.
   //
   //

   virtual ISUP::OpenStatus open() = 0;
   // This method connects the Probe object with the HP OC SS7 Stack. This operation is
   // synchronous, which means that once it returns without any error, the Probe is usable.
   //
   // <{Return Status}>
   //  NO_ERROR          - probe object ready.
   //  NO_CONFIG         - configuration file not accessible.
   //  BAD_GLOBAL_CONFIG - incorrect information parsed in file. 
   //  CONNECT_INT       - connection attempt rejected. 
   //  API_BUSY          - switchover in progress.
   //  ALREADY_OPEN      - the probe is already connected to the 
   //                      SS7 process.
   //  INTERNAL_ERROR    - error in HP OC ISUP subsystem.
   //
   //

   virtual ISUP::CloseStatus close() = 0;
   // This method closes the connection between the Probe object and the HP OC SS7 Stack.
   //
   // <{Return Status}>
   //  NO_ERROR       - probe object closed.
   //  PROBE_NOT_OPEN - probe not connected to the SS7 stack.
   //  ALREADY_CLOSED - probe already closed.
   //  IPC_SEND_FULL  - connection to HP OC SS7 Stack congested.
   //  CLOSE_FAILED   - closure attempt rejected.
   //  INTERNAL_ERROR - error in HP OC ISUP subsystem.
   //

   virtual ISUP::CtrlStatus disable() = 0;
   // This method desactivates the primary connection which becomes
   // secondary. Nothing happens on the (other) secondary connection.
   // 
   // <{Return Status}>
   //  NO_ERROR       - command succeeded.
   //  PROBE_NOT_OPEN - illegal call because the probe is
   //                   not open.
   //  NOT_CONNECTED  - not connected or the connect sequence is
   //                   not completed.
   //  CNX_CLOSED     - the SS7 platform has closed the connection.
   //  API_BUSY       - a manual or automatic switchover is in
   //                   progress, so the call should be retried later.
   //  INTERNAL_ERROR - error in HP OC ISUP subsystem.

   virtual ISUP::CtrlStatus enable() = 0;
   // This method activates the secondary connection. The primary connection
   // (if any) automatically becomes secondary.
   //
   // <{Return Status}>
   //  NO_ERROR       - command succeeded.
   //  PROBE_NOT_OPEN - illegal call because the probe is
   //                   not open.
   //  NOT_CONNECTED  - not connected or the connect sequence is
   //                   not completed.
   //  CNX_CLOSED     - the SS7 platform has closed the connection.
   //  API_BUSY       - a manual or automatic switchover is in
   //                   progress, so the call should be retried later.
   //  INTERNAL_ERROR - error in HP OC ISUP subsystem.

   virtual ISUP::CtrlStatus setIPCSendSize(size_t P_newSize) = 0;
   virtual ISUP::CtrlStatus setIPCRecvSize(size_t P_newSize) = 0;
   // These two methods allows the sizing of the IPC buffers. The new IPC 
   // buffer size can only be set to a value higher than the default value.
   //
   virtual ISUP::CtrlStatus setLowTransitTime(ISUP::Milliseconds P_newTime) = 0;
   // This method sets the maximum transit time before messages are sent on the LAN
   // with low traffic.
   //
   virtual ISUP::CtrlStatus setHighTransitTime(ISUP::Milliseconds P_newTime) = 0;
   // This method sets the maximum transit time before messages are sent on the LAN
   // with heavy traffic.
   //
   virtual ISUP::CtrlStatus setBufferingMode() = 0;
   // This method activates the buffering mode which allows buffering of the  
   // messages waiting to be sent. The send buffer must be explicitly flushed, using  
   // the flush or flushConditional calls.
   //
   virtual ISUP::CtrlStatus setNonBufferingMode() = 0;
   // This method returns in non-buffering mode. The send buffer is
   // automatically flushed after each send call.
   //
   virtual ISUP::CtrlStatus flush() = 0;
   virtual ISUP::CtrlStatus flushConditional() = 0;
   // These two methods allow performance to be optimized by reducing 
   // the number of IPC system calls. Buffering should be done as soon as the 
   // application requires high message throughput. Using this blocking mode 
   // the user can choose between an immediate flush or a conditional flush,
   // which sends the buffer only if one of the following conditions is met:
   //   - The transmit buffer is full.
   //   - The transit time of the oldest message stored in buffer has been
   //     exceeded. The transit time value is in a range between a low 
   //     transit time (Low transit time is the value available with low
   //     traffic, high transit time with the high traffic). 
   // 
   // <{Return Status}>
   //  NO_ERROR       - command succeeded.
   //  PROBE_NOT_OPEN - illegal call because the probe is 
   //                   not open.
   //  ILLEGAL_VALUE  - the value provided for this command is 
   //                   illegal.
   //  NOT_CONNECTED  - not connected or the connect sequence is 
   //                   not completed.
   //  CNX_CLOSED     - the SS7 platform has closed the connection.
   //  API_BUSY       - a manual or automatic switchover is in 
   //                   progress, so the call should be retried later.
   //  INTERNAL_ERROR - error in HP OC ISUP subsystem.
   //

	virtual HPAIN::Boolean isPrimary() = 0;

   
   // = SEE ASLO
   // = BEGIN<INDENT>
   //    IsupMgr, IsupSMProbe, IsupBPProbe, IsupMsg
   // = END<INDENT>
   
   protected:

   friend class IsupMgr;
   friend class IsupAP;

   // pointer to the MTP access point singleton object
   IsupAP * networkAccessPoint;

   // buffer and buffer length for interfacing with IsupMtpAP
   unsigned char localBuffer[MAX_MSG_LENGTH];
   HPAIN::Uint32 localBufferLength;

   // creation and destruction of probes is done by the IsupMgr 
   IsupProbe() {};
   virtual ~IsupProbe() {};

   // no copies and assigment operators
   IsupProbe(const IsupProbe&);
   IsupProbe& operator= (const IsupProbe&);

   virtual void doMsgProcessing() = 0;
   virtual ISUP::SendStatus processTaskQueue() = 0;
   virtual HPAIN::Uint32 numberOfIsupMessage() = 0;

	// local point code
	ISUP::PointCode LPC;

};	// IsupProbe

#endif           /* ISUP_PROBE_H */
