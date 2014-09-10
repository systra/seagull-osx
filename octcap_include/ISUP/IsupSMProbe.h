//------------------------------------------------------------------------------
//
//                               MODULE   IsupSMProbe.h
//                               --------------------
//
//
//  PURPOSE:
//
// = FILENAME
//     IsupSMProbe.
//
// = AUTHOR(S)
//     HP OC SS7 ISUP was developed by Hewlett Packard, TID
// = COPYRIGHT
//     Hewlett Packard - Telecom Infrastructure Division (1999).

//  Rev: 
//       $Source: /ISUP/code/isupcore/IsupSMProbe.h $
//       $Revision: 6.2 $
//       
//
//------------------------------------------------------------------------------
#ifndef ISUP_SMPROBE_H
#define ISUP_SMPROBE_H

#include <IsupCommon.h>
#include <IsupAdditionalInfo.h>
#include <IsupProbe.h>

class IsupMsg;

class IsupSMProbe : public IsupProbe {

   // = TITLE
   //     The entry point for sending and receiving ISUP primitives.
   //	  (<{VERSION 2.0}>)
   //
   // = DESCRIPTION
   // = BEGIN<INDENT>
   //     This class corresponds to an object dedicated to a HP OC SS7 Stack connection.
   //     It provides access to the HP OC SS7 stack involving state-machine interaction.
   //     ISUP primitives exchanged are for the Call Control or circuit supervision. Their
   //     associated messages are implicitly encoded/decoded by the HP OC ISUP subsystem.
   //
   //     Applications are provided by the HP OC ISUP API with the ability to manage the state
   //     of the circuits attached to the IsupSMProbe. This promotes High Availability
   //     at the application level, easing application failover. The standby application can
   //     set and retreive the state of circuits maintained by HP OC ISUP.
   //     Managing the circuits is only possible after the point that
   //     IsupSMProbe has been created and before it has been activated (the connection opened).
   //     It is <{not}> possible for an appilcation
   //     to manage the HP OC ISUP circuit states while HP OC ISUP is active.
   // = END<INDENT>
   
 public:

   class ActivityObject {
         public:
           ActivityObject() {};
           virtual ~ActivityObject() {};

           virtual void recvActivity(IsupSMProbe * aProbe, int nbOfRecvToDo) = 0;
           virtual void sendPossible(IsupSMProbe * aProbe) = 0;
           virtual void cnxStatus(IsupSMProbe * aProbe, ISUP::CnxStatus aStatus) = 0;
   };

   // = METHODS
   //  

   virtual ISUP::SetStatus setCircuitState( ISUP::Address &  P_address,
                                            ISUP::CircuitState     P_state ) = 0;
   // This method allows the application to set the state of a circuit to IDLE, 
   // ..., BUSY_OUTGOING_LOCALLY_AND_REMOTELY_BLOCKED, before opening the IsupSMProbe.
   //
   //
   // <{Return Status}>
   //  NO_ERROR              - no error.
   //  LPC_NOT_FOUND         - the LPC specified doesn't exist in 
   //                          the configuration.
   //  PROBE_ALREADY_ACTIVE  - illegal call because the probe is active.
   //  DPC_NOT_FOUND         - the DPC specified doesn't exist in 
   //                          the configuration.
   //  CIRCUIT_NOT_FOUND     - the CIC specified doesn't exist in 
   //                          the configuration.
   //  WRONG_STATE           - the circuit state specified is not valid.
   //  INTERNAL_ERROR
   // 
  
   
   virtual ISUP::GetStatus getCircuitState( ISUP::Address &  P_address,
                                            ISUP::CircuitState  &  P_state ) = 0;
   // This method allows the application to retreive the state of a circuit ( IDLE,
   // ..., BUSY_OUTGOING_LOCALLY_AND_REMOTELY_BLOCKED ).
   //
   //
   // <{Return Status}> 
   //  NO_ERROR           - no error.
   //  LPC_NOT_FOUND      - the LPC specified doesn't exist in 
   //                       the configuration.
   //  DPC_NOT_FOUND      - the DPC specified doesn't exist in 
   //                       the configuration.
   //  CIRCUIT_NOT_FOUND  - the CIC specified doesn't exist in 
   //                       the configuration.
   //  INTERNAL_ERROR
   //

   enum PrimitiveType {

                SETUP_REQ, //0
                SETUP_IND, //1
                SETUP_IND_ACK, //2
                SETUP_RESP, //3
                SETUP_CONF, //4

                SOLICITED_INFO_REQ, //5
                SOLICITED_INFO_IND,  //6 
                SOLICITED_INFO_RESP, //7 
                SOLICITED_INFO_CONF, //8 

                UNSOLICITED_INFO_REQ, //9
                UNSOLICITED_INFO_IND, //10

		INFORMATION_IND, //11             // Only For ITU-88
                INFORMATION_REQ, //12
		
                SETUP_FAILURE_IND, //13

                ADDRESS_COMPLETE_REQ, //14
                ADDRESS_COMPLETE_IND, //15

                CALL_PROGRESS_REQ, //16
                CALL_PROGRESS_IND, //17


                ISUP_USR_MSG_REQ, //18
                ISUP_USR_MSG_IND, //19

                RELEASE_REQ, //20
                RELEASE_IND,
                RELEASE_RESP,
                RELEASE_CONF,

                BLOCKING_REQ,                
                BLOCKING_IND,
                BLOCKING_RESP,
                BLOCKING_CONF,               
                UNBLOCKING_REQ,
                UNBLOCKING_IND,
                UNBLOCKING_RESP, //30
                UNBLOCKING_CONF,
                 
                GROUP_BLOCKING_REQ,          // for ANSI-95 and ITU-88 (Maintenance)
                GROUP_BLOCKING_IND,        
                GROUP_BLOCKING_RESP,
                GROUP_BLOCKING_CONF,
                GROUP_UNBLOCKING_REQ,
                GROUP_UNBLOCKING_IND,
                GROUP_UNBLOCKING_RESP,
                GROUP_UNBLOCKING_CONF, 

                HW_GROUP_BLOCKING_REQ, //40      // only for ITU-88 (hardware)
		HW_GROUP_BLOCKING_IND,       
                HW_GROUP_BLOCKING_RESP,
                HW_GROUP_BLOCKING_CONF,
                HW_GROUP_UNBLOCKING_REQ,
                HW_GROUP_UNBLOCKING_IND,
                HW_GROUP_UNBLOCKING_RESP,
                HW_GROUP_UNBLOCKING_CONF,

		GROUP_QUERY_IND,              // Only For ITU-88
		GROUP_QUERY_RESP,             // Only For ITU-88

                MAINTENANCE_SYSTEM_IND, //50

                START_RELEASE_IND,
                START_RELEASE_IND_ACK,

                CIRCUIT_RESERVATION_IND,      // Only For ANSI-95
                CIRCUIT_RESERVATION_RESP,     // Only For ANSI-95
		
		CIRCUIT_VALIDATION_IND,       // Only For ANSI-95
		CIRCUIT_VALIDATION_RESP,      // Only For ANSI-95

                SUSPEND_IND,
                RESUME_IND,
		
		EXIT_IND,

                FORWARD_TRANSFER_IND,  //60

                RESET_REQ,
                RESET_IND,
                RESET_RESP,
                RESET_CONF,

                START_RESET_IND,
                START_RESET_IND_ACK,

                GROUP_RESET_REQ,
                GROUP_RESET_IND,
                GROUP_RESET_RESP,
                GROUP_RESET_CONF, //70

                PASS_ALONG_REQ,                 // only for ANSI-95 and ITU-88
                PASS_ALONG_IND,

                FACILITY_REQUEST_REQ,           // Only For ITU-88
                FACILITY_REQUEST_IND,           // Only For ITU-88

                FACILITY_ACCEPT_REQ,            // Only For ITU-88
                FACILITY_ACCEPT_IND,            // Only For ITU-88

                FACILITY_REJECT_REQ,            // Only For ITU-88
                FACILITY_REJECT_IND,            // Only For ITU-88

                STOP_REQ,
                STOP_CONF, //80

                GROUP_STOP_REQ,
                GROUP_STOP_CONF,

                CONFUSION_IND,

                UNEQUIPPED_CIRCUIT_IND,

                MTP_PAUSE_IND,
                MTP_RESUME_IND,
                MTP_DPC_CONGESTED_IND,
                MTP_DPC_UNCONGESTED_IND,
                MTP_AVAILABLE_IND,
                MTP_UNAVAILABLE_IND, //90
                MTP_CONGESTED_IND,
                MTP_UNCONGESTED_IND,
                MTP_RESTARTING_IND,
                MTP_UPU_UNAVAILABLE_IND,

                CONTINUITY_REPORT_IND  ,           
                CONTINUITY_RECHECK_IND ,
		CONNECT_LOOP_IND       ,
		CONNECT_LOOP_IND_ACK   ,
		REMOVE_LOOP_IND        ,
		REMOVE_LOOP_IND_ACK    , //100
		DISABLE_ECHO_IND       ,
		DISABLE_ECHO_IND_ACK   ,
		ENABLE_ECHO_IND        ,
		ENABLE_ECHO_IND_ACK    ,	
                SUSPEND_REQ            ,
                RESUME_REQ             ,            

                BACKWARD_CHECK_TONE_ACK    ,        
                CONNECT_TRANSCEIVER_IND    ,        
                CONNECT_TRANSCEIVER_IND_ACK,
                CONTINUITY_RECHECK_REQ     , //110
                CONTINUITY_REPORT_REQ      ,
                REMOVE_TONE_IND            ,
                REMOVE_TONE_IND_ACK        ,
                REMOVE_TRANSCEIVER_IND     ,
                REMOVE_TRANSCEIVER_IND_ACK ,
                START_CHECK_TONE_IND       ,
                START_CHECK_TONE_IND_ACK   ,
                STOP_CHECK_TONE_IND        ,
                STOP_CHECK_TONE_IND_ACK    ,
                TONE_ACK                   , //120
                TONE_DISAPPEARS_ACK        , 
                FACILITY_REQ               ,     
                FACILITY_IND               ,
                CONTINUITY_RECHECK_CONF    ,
                GROUP_QUERY_REQ            ,          // ITU,TTC,NTT 
                GROUP_QUERY_CONF           ,          // ITU,TTC,NTT
                NETWORK_RESOURCE_MGT_REQ   ,
                NETWORK_RESOURCE_MGT_IND   ,
                UNKNOWN_MSG_REQ            ,
                UNKNOWN_MSG_IND            , //130
//TTC3-Start
                PROGRESS_REQ               ,
                PROGRESS_IND               ,
                ALERT_REQ                  ,
                ALERT_IND                  ,
                CHARGING_REQ               ,
                CHARGING_IND               , //136
//TTC3-End
// NL: GREhp18457 99/11/23 - SOFTRESET
                SOFTRESET_REQ              , //137
// NL: End

//START_NTT
                SOFTBLOCKING_REQ           , //138
//END-NTT
//Spirou-Start
                APP_TRANSPORT_REQ          , //139
                APP_TRANSPORT_IND          , //140
                PRE_REL_INFORMATION_REQ    , //141
                PRE_REL_INFORMATION_IND    , //142
                CHARGING_UNIT_REQ          , //143
                CHARGING_UNIT_IND          , //144
                CHARGING_UNIT_ACK          , //145
                CHARGING_UNIT_CONF         , //146
//Spirou-End
                CIRCUIT_VALIDATION_REQ     ,//147 : ONLY FOR ANSI-95
                CIRCUIT_VALIDATION_CONF    ,//148 : ONLY FOR ANSI-95
//Start SSUR-V2
                RATING_CHANGE_REQ          ,//149 : ONLY FOR SSUR
                RATING_CHANGE_IND          ,//150 : ONLY FOR SSUR
                TAXATION_REQ               ,//151 : ONLY FOR SSUR
                TAXATION_IND               ,//152 : ONLY FOR SSUR
//Stop SSUR-V2
//Start CHINA
                METER_PULSE_REQ            ,//153 : ONLY FOR CHINA
                METER_PULSE_IND            ,//154 : ONLY FOR CHINA
                OPERATOR_REQ               ,//155 : ONLY FOR CHINA
                OPERATOR_IND               ,//156 : ONLY FOR CHINA
                CALLING_CLEAR_REQ          ,//157 : ONLY FOR CHINA
                CALLING_CLEAR_IND           //158 : ONLY FOR CHINA
//Stop CHINA
         };
   		
   virtual ISUP::SendStatus send( PrimitiveType          P_type,
                                  ISUP::Address &        P_address,
                                  IsupMsg *              P_isupMsg,
                                  IsupAdditional::Info * P_info = 0) = 0;
   // This method allows the application to send a primitive and an associated 
   // message to the HP OC ISUP subsystem. The primitive type and the message type, 
   // contained in the IsupMsg object must be consistent (i.e. SETUP primitive
   // sent with an IAM message). If not, the call fails with the 
   // corresponding error.
   //
   //  
   // <{Return Status}>
   //  NO_ERROR                  - no error.
   //  PROBE_NOT_OPEN            - illegal call because the probe is 
   //                              not open.
	//  PROBE_NOT_ACTIVE          - Illegal call because the probe is not active.
   //  NOT_CONNECTED             - not connected or the connect sequence 
   //                              is not complete.
   //  ILLEGAL_PRIMITIVE         - illegal primitive for this probe.
   //  INCONSISTENT_ARGUMENTS    - primitive and message type are 
   //                              inconsistent.
   //  ENCODING_ERROR            - the Isup message cannot be 
   //                              encoded.
   //  MSG_TOO_LONG              - the Isup message encoding results in
   //                              a PDU that is too long.
   //  IPC_SEND_FULL             - the socket connection with the SS7
   //                              stack is congested.
   //  LPC_CONGESTED             - the specified LPC is congested.
   //  DPC_CONGESTED             - the specified DPC is congested.
   //  LPC_UNAVAILABLE           - the MTP level3 is inactive,
   //                              out of service or restarting.
   //  DPC_UNAVAILABLE           - the specified DPC is not accessible via 
   //                              the ss7 network.
   //  NO_MORE_MEMORY            - there is no memory available for
   //                              creation of new object.
   //  INVALID_MESSAGE           - the Isup message is not valid.
   //  DPC_NOT_FOUND             - the specified DPC doesn't exist in 
   //                              the configuration.
   //  LPC_NOT_FOUND             - the specified LPC doesn't exist in 
   //                              the configuration.
   //  CIRCUIT_NOT_FOUND         - the specified CIC doesn't exist in 
   //                              the configuration.
   //  UNEQUIPPED_CIRCUIT        - the specified circuit is configured as 
   //                              unequipped.
   //  NO_END_TO_END_METHOD      - the circuit has not been initialized with a 
   //                              end to end method.
   //  INBOUND_CIRCUIT           - the circuit is reserved for incoming 
   //                              calls
   //  WRONG_STATE               - illegal primitive regarding the state.
   //  IDLE_STATE                - illegal primitive because the 
   //                              circuit/call state is IDLE.
   //  CIRCUITS_LEFT_UNRESPONDED - some circuits have not responded after  
   //                              a group-action.
   //  ALREADY_SEIZED_INCOMING   - the circuit is already in use for an 
   //                              incoming call. 
   //  ALREADY_SEIZED_OUTGOING   - the circuit is already in use for an 
   //                              outgoing call.
   //  CNX_CLOSED                - the connection with the SS7 stack has 
   //                              been closed.
   //  API_BUSY                  - switch-over in progress, retry later.
	//  API_DISABLED              - The connexion is now a secondary connexion.
   //  INVALID_GROUP             - invalid range or no circuits in the
   //                              group message.
   //  INTERNAL_ERROR
   //
   //
   virtual ISUP::RecvStatus receive( PrimitiveType &          P_type,
                                     ISUP::Address &          P_address,
                                     IsupMsg *&               P_isupMsg,
                                     IsupAdditional::Info *&  P_info,
                                     int &                    P_nbIndication ) = 0;
   //   This method allows the application to receive a primitive and an associated
   //   message from the ISUP layer. The indication can be a normal indication 
   //   (call processing or maintenance indication) or special indication which 
   //   corresponds to an action to be performed on the physical circuit. In addition
   //   HP OC ISUP can pass MTP indication to the user.
   //
   // 
   // <{Return Status}> 
   // NO_ERROR        - no error.
   // PROBE_NOT_OPEN  - illegal call because the probe is 
   //                   not open.
   // NO_MSG          - there is no message to receive.
   // INTERNAL_ERROR
   //
   //
   virtual ISUP::SendStatus releaseCircuit( ISUP::Address & P_address ) = 0;
   //
   // This method allows the application to release a circuit without requiring any other
   // interaction between the ISUP API and the application.
   // Calling this method triggers a normal release procedure and a reset procedure if
   // the release procedure fails. If both procedures fail, HP OC
   // ISUP resets locally the circuit.
   //
   // <{Return Status}>
   //  NO_ERROR                  - no error.
   //  PROBE_NOT_OPEN            - illegal call because the probe is
   //                              not open.
	//  PROBE_NOT_ACTIVE          - Illegal call because the probe is not active.
   //  NOT_CONNECTED             - not connected or the connect sequence
   //                              is not complete.
   //  IPC_SEND_FULL             - the socket connection with the SS7
   //                              stack is congested.
   //  LPC_CONGESTED             - the specified LPC is congested.
   //  DPC_CONGESTED             - the specified DPC is congested.
   //  LPC_UNAVAILABLE           - MTP level3 is inactive,
   //                              out of service or restarting.
   //  DPC_UNAVAILABLE           - the specified DPC is not accessible via
   //                              the ss7 network.
   //  NO_MORE_MEMORY            - there is no memory available for
   //                              creation of new object.
   //  INVALID_MESSAGE           - the Isup message is not valid.
   //  DPC_NOT_FOUND             - the specified DPC doesn't exist in
   //                              the configuration.
   //  LPC_NOT_FOUND             - the specified LPC doesn't exist in
   //                              the configuration.
   //  CIRCUIT_NOT_FOUND         - the specified CIC doesn't exist in
   //                              the configuration.
   //  UNEQUIPPED_CIRCUIT        - the specified circuit is configured as
   //                              unequipped.
   //  WRONG_STATE               - illegal primitive regarding the state.
   //  IDLE_STATE                - illegal primitive because the
   //                              circuit/call state is IDLE.
   //  CNX_CLOSED                - the connection with the SS7 stack has
   //                              been closed.
   //  API_BUSY                  - switch-over in progress, retry later.
	//  API_DISABLED              - The connexion is now a secondary connexion.
   //  INTERNAL_ERROR
   //
   //
   // =	PARAMETERS 
   //
   //   <{CircuitState}> - IDLE, BUSY_INCOMING, BUSY_OUTGOING 
   // 
   //   <{PrimitiveType}> - HP OC ISUP primitive types for ANSI-95, ITU-88, TTC and/or NTT flavors.
   //         SETUP_REQ, SETUP_IND, SETUP_IND_ACK, SETUP_RESP, SETUP_CONF,
   //         SOLICITED_INFO_REQ, SOLICITED_INFO_IND, SOLICITED_INFO_RESP,
   //         SOLICITED_INFO_CONF,
   //         UNSOLICITED_INFO_REQ, UNSOLICITED_INFO_IND,
   //         INFORMATION_IND, INFORMATION_REQ,
   //         SETUP_FAILURE_IND, 
   //         ADDRESS_COMPLETE_REQ, ADDRESS_COMPLETE_IND,
   //         CALL_PROGRESS_REQ, CALL_PROGRESS_IND,
   //         ISUP_USR_MSG_REQ, ISUP_USR_MSG_IND,
   //         RELEASE_REQ, RELEASE_IND, RELEASE_RESP, RELEASE_CONF,
   //         BLOCKING_REQ, BLOCKING_IND, BLOCKING_RESP, BLOCKING_CONF,
   //         UNBLOCKING_REQ, UNBLOCKING_IND, UNBLOCKING_RESP, UNBLOCKING_CONF,
   //         GROUP_BLOCKING_REQ, GROUP_BLOCKING_IND, GROUP_BLOCKING_RESP, GROUP_BLOCKING_CONF,
   //         GROUP_UNBLOCKING_REQ, GROUP_UNBLOCKING_IND, GROUP_UNBLOCKING_RESP, GROUP_UNBLOCKING_CONF,
   //         HW_GROUP_BLOCKING_REQ, HW_GROUP_BLOCKING_IND, HW_GROUP_BLOCKING_RESP, 
   //         HW_GROUP_BLOCKING_CONF,
   //         HW_GROUP_UNBLOCKING_REQ, HW_GROUP_UNBLOCKING_IND, HW_GROUP_UNBLOCKING_RESP,
   //         HW_GROUP_UNBLOCKING_CONF,
   //         GROUP_QUERY_IND, GROUP_QUERY_RESP,
   //         GROUP_QUERY_REQ, GROUP_QUERY_CONF,
   //         MAINTENANCE_SYSTEM_IND,
   //         START_RELEASE_IND, START_RELEASE_IND_ACK,
   //         CIRCUIT_RESERVATION_IND, CIRCUIT_RESERVATION_RESP,
   //         CIRCUIT_VALIDATION_IND, CIRCUIT_VALIDATION_RESP,
   //         SUSPEND_IND, RESUME_IND,
   //         EXIT_IND, FORWARD_TRANSFER_IND,
   //         RESET_REQ, RESET_IND, RESET_RESP, RESET_CONF,
   //         START_RESET_IND, START_RESET_IND_ACK,
   //         GROUP_RESET_REQ, GROUP_RESET_IND, GROUP_RESET_RESP, GROUP_RESET_CONF,
   //         PASS_ALONG_REQ, PASS_ALONG_IND,
   //         FACILITY_REQUEST_REQ, FACILITY_REQUEST_IND,
   //         FACILITY_ACCEPT_REQ, FACILITY_ACCEPT_IND,
   //         FACILITY_REJECT_REQ, FACILITY_REJECT_IND,
   //         STOP_REQ, STOP_CONF, CONFUSION_IND, UNEQUIPPED_CIRCUIT_IND,
   //         GROUP_STOP_REQ, GROUP_STOP_CONF,
   //         MTP_PAUSE_IND, MTP_RESUME_IND, MTP_DPC_CONGESTED_IND,
   //         MTP_DPC_UNCONGESTED_IND, MTP_AVAILABLE_IND,
   //         MTP_UNAVAILABLE_IND, MTP_CONGESTED_IND,
   //         MTP_UNCONGESTED_IND, MTP_RESTARTING_IND,
   //         MTP_UPU_UNAVAILABLE_IND,
   //         UNKNOWN_MSG_REQ, UNKNOWN_MSG_IND
   //
   //  <{ISUP::Address}> - HP OC ISUP addressing containing routing label and CIC.
   // 
   //  <{IsupMsg}> - HP OC ISUP message base class encapsulating an ISUP message.
   //  
   // = SEE ALSO
   // = BEGIN<INDENT>
   //	    IsupMgr, IsupProbe, IsupBPProbe, IsupMsg, IsupMsgIntro, IsupIntro, IsupCustom
   // = END<INDENT>  
   protected:

   friend class IsupMgr;

   // creation and destruction of probes is done by the IsupMgr (open and 
   // close IsupSMProbe)
   IsupSMProbe() {};
   virtual ~IsupSMProbe() {};

   // no copies and assigment operators
   IsupSMProbe(const IsupSMProbe&);
   IsupSMProbe& operator= (const IsupSMProbe&);
 
};      // IsupSMProbe

   ostream& operator<< (ostream& P_os, IsupSMProbe::PrimitiveType P_type);
   // Do a pretty print on <{ostream}> of a IsupSMProbe::PrimitiveType variable.

   // = EXAMPLE
   // = BEGIN<INDENT>
   //
   // This example shows how to send a SETUP request with a IAM message to 
   // the destination point code number 1020 for the CIC 457:
   //
   // IsupIam *                 L_myIamPtr = NEW IsupIam();  
   // IsupAdditional::Info *    L_myInfo = NEW IsupAdditional::Setup();
   // ISUP::Address             L_myAddress(1020,457);
   // ISUP::SendStatus          L_sendStatus;
   //
   // // ... fill in the Iam message and the Additional info parameter ...
   // 
   // L_sendStatus = IsupSMProbe->send(SETUP, L_myAddress, L_myIamPtr, L_myInfo);
   // if( ! L_myStatus.isOk())
   //   { ... handle error... }
   //
   // This example shows how to receive an indication with a message 
   // from ISUP:
   // 
   //
   // IsupSMProbe::primitiveType  L_recvType;
   // ISUP::Address               L_recvAddress;
   // ISUP::RecvStatus            L_recvStatus;
   // IsupMsg *                   L_recvIsupMsg;
   // IsupAdditional::Info *      L_recvInfo;
   // int                         nbMsg;
   //
   // do {
   //     L_recvStatus = IsupSMProbe->receive( L_recvType, 
   //                                          L_recvAddress,
   //                                          L_recvIsupMsg, 
   //                                          L_recvInfo,
   //                                          nbMsg);
   //     if( ! L_recvStatus.isOk())
   //       { ... handle error ... }
   //
   //     // ... process the message ...
   // 
   //    } while (nbMsg > 0);
   //
   // = END<INDENT>
   //

#endif           /* ISUP_SMPROBE_H */
