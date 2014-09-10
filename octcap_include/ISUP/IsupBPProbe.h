//------------------------------------------------------------------------------
//
//                               MODULE   IsupBPProbe.h
//                               ----------------------
//
//
//  PURPOSE:
//
// = FILENAME
//     IsupBPProbe.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).
//

//  Rev: 
//       $Source: /ISUP/code/isupcore/IsupBPProbe.h $
//       $Revision: 2.5 $
//       
//
//------------------------------------------------------------------------------
#ifndef ISUP_BP_PROBE_H
#define ISUP_BP_PROBE_H

#include <IsupCommon.h>
 
class IsupMsg;

class IsupBPProbe : public IsupProbe {

   // = TITLE
   //     The entry point for the exchange of ISUP messages.
   //     (<{VERSION 2.0}>)
   //
   // = DESCRIPTION
   // = BEGIN<INDENT>
   //     This class corresponds to an object dedicated to a HP OC SS7 Platform connection.
   //     It provides the means to exchange ISUP messages. By using the IsupBPProbe object
   //     instead of IsupSMProbe, the HP OC SS7 ISUP user can send or receive messages
   //     without interacting with the HP OC SS7 ISUP provided state-machines. It provides
   //     direct access to MTP-3. 
   //	  Scheduling of the IsupBPProbe is performed by the IsupMgr using the global cnxHandler.
   // = END<INDENT>
 public:

  

   class ActivityObject {
         public:
           ActivityObject() {};
           virtual ~ActivityObject() {};

           virtual void recvActivity(IsupBPProbe * aProbe, int nbOfRecvToDo) = 0;
           virtual void sendPossible(IsupBPProbe * aProbe) = 0;
           virtual void cnxStatus(IsupBPProbe * aProbe, ISUP::CnxStatus aStatus) = 0;
   };

   enum PrimitiveType {
                        ISUP_MSG_REQ,
                        ISUP_MSG_IND,
                        PASS_ALONG_REQ,
                        PASS_ALONG_IND,
                        UNKNOWN_MSG_REQ,
                        UNKNOWN_MSG_IND,

                        MTP_PAUSE_IND,
                        MTP_RESUME_IND,
                        MTP_DPC_CONGESTED_IND,
                        MTP_DPC_UNCONGESTED_IND,
                        MTP_AVAILABLE_IND,
                        MTP_UNAVAILABLE_IND,
                        MTP_CONGESTED_IND,
                        MTP_UNCONGESTED_IND,
                        MTP_RESTARTING_IND,
                        MTP_UPU_UNAVAILABLE_IND,

                        INVALID_ISUP_MSG_IND,
                        UNKNOWN_OPC_MSG_IND
                      }; 
   
  
   //
   // = METHODS
      
   virtual ISUP::SendStatus send( PrimitiveType          P_type,
                                  ISUP::Address &        P_address,
                                  IsupMsg *              P_isupMsg ) = 0;
   // 
   // This method allows the ISUP user to send a primitive and its associated
   // message to the ISUP sub-system. The primitive type, and the message type
   // contained in the IsupMsg object must be consistent (i.e. ISUP_MSG_REQ primitive
   // sent with an IAM message). If not, the call will fail with the 
   // corresponding error.
   //
   // <{Return Status}>
   //  NO_ERROR               - no error.
   //  PROBE_NOT_OPEN         - illegal call because the probe is not 
   //                           open.
   //  NOT_CONNECTED          - not connected or the connect sequence 
   //                           is not complete.
   //  ILLEGAL_PRIMITIVE      - illegal primitive for this probe.
   //  INCONSISTENT_ARGUMENTS - primitive and message type are 
   //                           inconsistents.
   //  ENCODING_ERROR         - the attached Isup message cannot 
   //                           be encoded.
   //  MSG_TOO_LONG           - the Isup message encoding results 
   //                           in a too long PDU.
   //  IPC_SEND_FULL          - the socket connection with the SS7 
   //                           stack is congested.
   //  LPC_CONGESTED          - the specified LPC specified is congested.
   //  DPC_CONGESTED          - the specified DPC specified is congested.
   //  LPC_UNAVAILABLE        - the MTP level3 is inactive, out of service 
   //                           or restarting.
   //  DPC_UNAVAILABLE        - the specified DPC is not accessible via 
   //                           the ss7 network.
   //  NO_MORE_MEMORY         - there is no memory available for the creation 
   //                           of a new object.
   //  INVALID_MESSAGE        - the Isup message is not valid.
   //  DPC_NOT_FOUND          - the specified DPC doesn't exist in the 
   //                           configuration.
   //  LPC_NOT_FOUND          - the specified LPC doesn't exist in the 
   //                           configuration.
   //  CIRCUIT_NOT_FOUND      - the specified CIC doesn't exist in the 
   //                           configuration.
   //  UNEQUIPPED_CIRCUIT     - the specified circuit is configured as 
   //                           unequipped.
   //  NO_END_TO_END_METHOD   - the circuit is not initialized with an 
   //                           end to end method.
   //  CNX_CLOSED             - the connection with the SS7 stack has 
   //                           been closed.
   //  API_BUSY               - switch-over in progress, retry later.
   //  INTERNAL_ERROR
   //
   //
   virtual ISUP::RecvStatus receive( PrimitiveType &         P_type,
                                     ISUP::Address &         P_address,
                                     IsupMsg *&              P_isupMsg,
                                     int &                   P_nbMsg ) = 0;
   // This method allows the ISUP user to receive a primitive with its associated 
   // message from the ISUP sub-system. The indication can be either a normal indication
   // (call processing or maintenance indication) or an MTP indication. 
   // 
   //   
   // <{Return Status}>
   //  NO_ERROR           - no error.
   //  PROBE_NOT_OPEN     - illegal call because the probe is not opened.
   //  NO_MSG             - there is no message to receive.
   //  INTERNAL_ERROR
   //
   // =	PARAMETERS 
   // = BEGIN<INDENT>
   //   <{PrimitiveType}> - HP OC SS7 ISUP primitive types for all supported standards.
   //         ISUP_MSG_REQ, ISUP_MSG_IND,
   //         PASS_ALONG_REQ, PASS_ALONG_IND, // only ANSI and ITU_T standards
   //         UNKNOWN_MSG_REQ, UNKNOWN_MSG_IND, // Only ITU-T 97 standard
   //         MTP_PAUSE_IND, MTP_RESUME_IND, MTP_DPC_CONGESTED_IND,
   //         MTP_DPC_UNCONGESTED_IND, MTP_AVAILABLE_IND,
   //         MTP_UNAVAILABLE_IND, MTP_CONGESTED_IND,
   //         MTP_UNCONGESTED_IND, MTP_RESTARTING_IND,
   //         MTP_UPU_UNAVAILABLE_IND,
   //         INVALID_ISUP_MSG_IND, UNKNOWN_OPC_MSG_IND
   //
   //  <{ISUP::Address}> - HP OC SS7 ISUP addressing containing routing label and CIC.
   //
   //  <{IsupMsg}> - HP OC SS7 ISUP message base class encapsulating an ISUP message.
   // = END<INDENT>
   //
   // = SEE ALSO
   //	    IsupMgr, IsupProbe, IsupSMProbe, IsupMsg, IsupMsgIntro, IsupCustom, IsupIntro
   //
   protected:

   friend class IsupMgr;

   // creation and destruction of probes is done by the IsupMgr (open and
   // close IsupBPProbe)
   IsupBPProbe() {};
   virtual ~IsupBPProbe() {};

   // no copies and assigment operators
   IsupBPProbe(const IsupBPProbe&);
   IsupBPProbe& operator= (const IsupBPProbe&);

};      // IsupBPProbe

   ostream& operator<< (ostream& P_os, IsupBPProbe::PrimitiveType P_type);
   // Do a pretty print on <{ostream}> of a IsupBPProbe::PrimitiveType variable.



   // = EXAMPLE
   //
   // This example shows how to send an IAM message to the DPC 1020 for CIC 457
   //
   // = BEGIN<CODE>
   //
   // IsupIam * L_myIamPtr = NEW IsupIam();  
   //  
   //  // ...
   //
   // myIamPtr->natureOfCnxIndicator(0x7e);
   //
   //  // ...
   //
   // if((!L_myIamPtr->getStatus()).isOk())
   //   {
   //    // handle error
   //   } 
   //
   // ISUP::Address     L_myAddress(1020,457);
   // ISUP::SendStatus  L_sendStatus;
   // 
   // L_sendStatus = IsupBPProbe->send(ISUP_MSG_REQ, L_myAddress, L_myIamPtr);
   // if( ! L_sendStatus.isOk())
   //   {
   //    // handle error
   //   }
   //
   // This example shows how to receive an indication with a message 
   // from ISUP:
   // IsupBPProbe::primitiveType L_recvType;
   // ISUP::Address              L_recvAddress();
   // ISUP::RecvStatus           L_recvStatus;
   // IsupMsg *                  L_recvIsupMsg;
   // int                        nbMsg;
   //
   // do {
   //     L_recvStatus = IsupProbe->receive( L_recvType,
   //                                        &L_recvAddress,
   //                                        L_recvIsupMsg,
   //                                        &nbMsg);
   //     if( ! L_recvStatus.isOk())
   //       {
   //        // ... handle error ...
   //       }
   //
   //     // ... process the message ...
   //
   //    } while (nbMsg > 0);
   //
   // = END<CODE>
   //
   //

#endif           /* ISUP_BP_PROBE_H */
