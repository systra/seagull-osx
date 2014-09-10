//------------------------------------------------------------------------------
//
//  Rev: 
//       $Source: /ISUP/code/common/IsupCommon.h $
//       $Revision: 6.6 $
//       
//
//                               MODULE   IsupCommon.h
//                               -----------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupCommon.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TND.
// = COPYRIGHT
//           Hewlett Packard - Telecom Network Division (1996).
//
//------------------------------------------------------------------------------
#ifndef ISUP_COMMON_H
#define ISUP_COMMON_H

#include <OC/oc_config.h>

#include <arpa/inet.h>		// htonl()

#if !defined(__GNUG__) && (__cplusplus < 199707L)
# include <List.h>
#else
# include <list>
# include <vector>
#endif


#include <ainCppCommon.h>

#define MAX_PROBE_NUMBER 4
//START DYNAMIC CONFIG
#define MAX_CONFIG_STRING 150
#define MAX_PC_LENGTH     12
//END DYNAMIC CONFIG

#ifdef _USE_RESOURCE_LOCATOR
#define ISUP_D_SECTION            "isup"
#define COMM_SECTION              0
#define SPEC_SECTION              1
#define ISUP_D_KEY_ISUP_CONF      "isup_conf"
#define ISUP_D_KEY_ISUP_APP_CONF  "isup_app_conf"
#define ISUP_D_KEY_ISUP_APP_CHG   "isup_app_chg"
#define ISUP_D_KEY_ISUP_APP_DUMP  "isup_app_dump"
#endif

#ifdef __cplusplus

//START DYNAMIC CONFIG
class IsupMocMsgSet;
class IsupRange;
//END DYNAMIC CONFIG

class IsupMocCircuit;

// Class scope used until namescopes available
class ISUP
{
public:
   typedef short          MsgSetID;
   typedef int            MsgID;      
   typedef int            ParmID;
   typedef HPAIN::Uint32  PointCode;
   typedef HPAIN::Uint16  Cic;
   typedef HPAIN::Uint32  Milliseconds;
   
   enum Protocol {
                   ITU=0x10,
                   NTT=ITU+1,
                   TTC=ITU+2,
                   ITU97=ITU+3,
                   TTC3=ITU+4,
                   SSUR=ITU+5,
                   SPR98=ITU+6,
                   CHINA=ITU+7,
                   ETSI3=ITU+8,
                   BRITISH=ITU+9,
                   ITU_LOOPBACK=0x20,
                   NTT_LOOPBACK=ITU_LOOPBACK+1,
                   TTC_LOOPBACK=ITU_LOOPBACK+2,
                   ITU97_LOOPBACK=ITU_LOOPBACK+3,
                   TTC3_LOOPBACK=ITU_LOOPBACK+4,
                   SSUR_LOOPBACK=ITU_LOOPBACK+5,
                   SPR98_LOOPBACK=ITU_LOOPBACK+6,
                   CHINA_LOOPBACK=ITU_LOOPBACK+7,
                   ETSI3_LOOPBACK=ITU_LOOPBACK+8,
                   BRITISH_LOOPBACK=ITU_LOOPBACK+9,
                   ANSI=0x30,
                   ANSI_LOOPBACK=0x40,
                   BYPASS_LOOPBACK=0x50,
                   NO=0x60,
                   UNKNOWN=0x70 };

   enum ConnectionType { PRIMARY, SECONDARY };

//START DYNAMIC CONFIG
#ifdef ISUP_I88
   enum CircuitState {
                      IDLE,
                      IDLE_MN_LOCALLY_BLOCKED,
                      IDLE_MN_REMOTELY_BLOCKED,
                      IDLE_MN_LOCALLY_AND_REMOTELY_BLOCKED,
                      BUSY_INCOMING_ACTIVE,
                      BUSY_INCOMING_MN_LOCALLY_BLOCKED,
                      BUSY_INCOMING_MN_REMOTELY_BLOCKED,
                      BUSY_INCOMING_MN_LOCALLY_AND_REMOTELY_BLOCKED,
                      BUSY_OUTGOING_ACTIVE,
                      BUSY_OUTGOING_MN_LOCALLY_BLOCKED,
                      BUSY_OUTGOING_MN_REMOTELY_BLOCKED,
                      BUSY_OUTGOING_MN_LOCALLY_AND_REMOTELY_BLOCKED,

                      IDLE_HW_LOCALLY_BLOCKED,
                      IDLE_HW_REMOTELY_BLOCKED,
                      IDLE_HW_LOCALLY_AND_REMOTELY_BLOCKED,

                      IDLE_HW_MN_LOCALLY_BLOCKED,
                      IDLE_HW_MN_REMOTELY_BLOCKED,
                      IDLE_HW_MN_LOCALLY_AND_REMOTELY_BLOCKED,

                      IDLE_HW_LOCALLY_BLOCKED_MN_REMOTELY_BLOCKED,
                      IDLE_HW_REMOTELY_BLOCKED_MN_LOCALLY_BLOCKED,
                      IDLE_HW_LOCALLY_BLOCKED_MN_LOCALLY_AND_REMOTELY_BLOCKED,
                      IDLE_HW_LOCALLY_AND_REMOTELY_BLOCKED_MN_LOCALLY_BLOCKED,
                      IDLE_HW_LOCALLY_AND_REMOTELY_BLOCKED_MN_REMOTELY_BLOCKED,
                      IDLE_HW_REMOTELY_BLOCKED_MN_LOCALLY_AND_REMOTELY_BLOCKED
                     };

#else

   enum CircuitState {
                      IDLE,
                      IDLE_LOCALLY_BLOCKED,
                      IDLE_REMOTELY_BLOCKED,
                      IDLE_LOCALLY_AND_REMOTELY_BLOCKED,
                      BUSY_INCOMING_ACTIVE,
                      BUSY_INCOMING_LOCALLY_BLOCKED,
                      BUSY_INCOMING_REMOTELY_BLOCKED,
                      BUSY_INCOMING_LOCALLY_AND_REMOTELY_BLOCKED,
                      BUSY_OUTGOING_ACTIVE,
                      BUSY_OUTGOING_LOCALLY_BLOCKED,
                      BUSY_OUTGOING_REMOTELY_BLOCKED,
                      BUSY_OUTGOING_LOCALLY_AND_REMOTELY_BLOCKED
                     };
#endif

	enum Reserved {
		NOT = 0 ,
		RESERVED_INCOMING = 1 ,
		RESERVED_OUTGOING = 2 ,
		UNEQUIPPED = 3
	};
//END DYNAMIC CONFIG

   //--------------------------------------------------------------------------
   // isup addressing using DPC, CIC, and SLS
   //--------------------------------------------------------------------------
   class Address {
      PointCode  originatingPointCode;   //
      PointCode  destinationPointCode;   //  Routing Label
      HPAIN::Uint32    signalingLinkSelection; // 
      
      Cic        circuitIdentificationCode;
      HPAIN::Uint8     serviceIndicatorOctet;
      
   public:
      void OPC(PointCode P_OPC);
      PointCode OPC() const;

      void DPC(PointCode P_DPC);
      PointCode DPC() const;

      void SLS(HPAIN::Uint32 P_SLS);
      HPAIN::Uint32 SLS() const;

      void CIC(Cic P_CIC);
      Cic CIC() const;

      void SIO(HPAIN::Uint8 P_SIO);
      HPAIN::Uint8  SIO() const;
      
      Address(HPAIN::Uint32 P_DPC, HPAIN::Uint16 P_CIC,
	      HPAIN::Uint32 P_SLS=0);
      Address();
      Address(const Address& P_from);   
      
      Address& swap(); // Swap OPC and DPC values
   };
   
//START DYNAMIC CONFIG
	class dpcAddress {
		PointCode lpc;
		PointCode dpc;
		
	public:
		void OPC(PointCode P_OPC);
      PointCode OPC() const;

		void DPC(PointCode P_DPC);
      PointCode DPC() const;

		dpcAddress(PointCode P_LPC, PointCode P_DPC);
		dpcAddress();
		dpcAddress(const dpcAddress& P_from);
	};

	class cicRangeAddress {
		dpcAddress addr;
		Cic       cicMin;
		Cic       cicMax;

	public:
		void OPC(PointCode P_OPC);
      PointCode OPC() const;

		void DPC(PointCode P_DPC);
      PointCode DPC() const;

		void ADDR(dpcAddress *P_addr);
		const dpcAddress *ADDR() const;

		void CICMIN(Cic P_CICMIN);
		Cic CICMIN() const;

		void CICMAX(Cic P_CICMAX);
		Cic CICMAX() const;

		cicRangeAddress(dpcAddress *P_addr,Cic P_CICMIN,Cic P_CICMAX);
		cicRangeAddress();
		cicRangeAddress(const cicRangeAddress& P_from);
	};

	class lpcInfo {
		public: 
			PointCode OPC() const;
			Protocol  mtpProtocol() const;
			Protocol  isupProtocol() const;
			const char      *className() const;
			lpcInfo(PointCode P_opc, Protocol P_mtp,
					Protocol P_isup, const char *P_name);
			lpcInfo();
			~lpcInfo();
			void OPC(PointCode P_OPC);
			void mtpProtocol (Protocol P_protocol);
			void isupProtocol (Protocol P_protocol);
			void className (const char *P_name);

		private:
			PointCode  opc;
			Protocol   mtp;
			Protocol   isup;
			char       *classname;

		friend class IsupMocLpc;
	};

	class dpcInfo {
		public:
			dpcInfo (dpcAddress *P_addr, 
						IsupMocMsgSet *P_msgSet, 
						HPAIN::Uint16 P_cause);
			dpcInfo();
			~dpcInfo();
			PointCode OPC() const;
			PointCode DPC() const;
			const dpcAddress *ADDR() const;
			IsupMocMsgSet *MsgSet() const;
			const char *MsgSetName() const;
			HPAIN::Uint16 releaseCause() const;
			void OPC(PointCode P_OPC);
			void DPC(PointCode P_DPC);
			void ADDR(dpcAddress *P_ADDR);
			void MsgSet (IsupMocMsgSet *P_msgSet);
			void releaseCause (HPAIN::Uint16 P_cause);
		private:
			dpcAddress addr;
			IsupMocMsgSet    *msgSet;
			HPAIN::Uint16    cause;
	};

	class cicsInfo {
		public:
#ifdef ISUP_A92
//			cicsInfo(cicRangeAddress *P_addr,
//						Reserved P_res, CircuitState P_state,
//						IsupRange *P_group);
			cicsInfo(cicRangeAddress *P_addr,Reserved P_res,IsupRange *P_group);
#else
//			cicsInfo(cicRangeAddress *P_addr,Reserved P_res,CircuitState P_state);
			cicsInfo(cicRangeAddress *P_addr,Reserved P_res);
#endif
			cicsInfo();
			~cicsInfo();
			PointCode OPC() const;
			PointCode DPC() const;
			Cic CICMIN() const;
			Cic CICMAX() const;
			const dpcAddress *ADDR() const;
			const cicRangeAddress *RADDR() const;
			Reserved  reserved() const;
//			CircuitState circuitState() const;
#ifdef ISUP_A92
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
			List<Cic> *defaultGroup() const;
#else
			list<Cic> *defaultGroup() const;
#endif
//USL&STL-End
#endif
			void OPC(PointCode P_OPC);
			void DPC(PointCode P_OPC);
			void CICMIN(Cic P_min);
			void CICMAX(Cic P_max);
			void ADDR(dpcAddress *P_ADDR);
			void RADDR(cicRangeAddress *P_ADDR);
			void reserved (Reserved P_res);
//			void circuitState (CircuitState P_state);
#ifdef ISUP_A92
			void defaultGroup(IsupRange *P_group);
#endif
		private:
			cicRangeAddress addr;
			Reserved        res;
//			CircuitState    state;
#ifdef ISUP_A92
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
			List<Cic>       *group;
#else
			list<Cic>       *group;
#endif
//USL&STL-End
#endif
	};
//END DYNAMIC CONFIG

//==========================================================================
//                      STATUS CLASSES
//==========================================================================

//--------------------------------------------------------------------------
//                      InitStatus 
//--------------------------------------------------------------------------
   class InitStatus : public HPAIN::StatusBase {
   public:
      enum Status {
      NO_ERROR=0,
      ALREADY_CREATED, // The IsupMgr already exists.
      NO_MORE_MEMORY,  // Problem during memory allocation for the IsupMgr.
      NO_ISUP_CONFIG,  // Cannot access to the isup config file ( absent
                       //  or permission denied ).
      BAD_ISUP_CONFIG, // The isup config file is wrong.
      INTERNAL_ERROR
      };
      InitStatus(StatusValue s) : StatusBase(s) {};
      InitStatus() {};
      ~InitStatus() {};
   };

//--------------------------------------------------------------------------
//                      SetStatus
//--------------------------------------------------------------------------
   class SetStatus : public HPAIN::StatusBase {
   public:
      enum Status {
      NO_ERROR=0,
      LPC_NOT_FOUND,        // The LPC specified doesn't exist in the configuration.
      PROBE_ALREADY_ACTIVE, // Illegal call because the probe is active.
      DPC_NOT_FOUND,        // The DPC specified doesn't exist in the configuration.
      CIRCUIT_NOT_FOUND,    // The CIC specified doesn't exist in the configuration.
      WRONG_STATE,          // The circuit state specified is not valid.
      INTERNAL_ERROR
      };
      SetStatus(StatusValue s) : StatusBase(s) {};
      SetStatus() {};
      ~SetStatus() {};
   };

//--------------------------------------------------------------------------
//                      GetStatus
//--------------------------------------------------------------------------
   class GetStatus : public HPAIN::StatusBase {
   public:
      enum Status {
         NO_ERROR=0,      
         LPC_NOT_FOUND,      // The LPC specified doesn't exist in the configuration.
         DPC_NOT_FOUND,      // The DPC specified doesn't exist in the configuration.
         CIRCUIT_NOT_FOUND,  // The CIC specified doesn't exist in the configuration.
         INTERNAL_ERROR
      };
      GetStatus(StatusValue s) : StatusBase(s) {};
      GetStatus() {};
      ~GetStatus() {};
   };

//--------------------------------------------------------------------------
//                      CnxStatus
//--------------------------------------------------------------------------
   class CnxStatus : public HPAIN::StatusBase {
   public:
      enum Status { 
         NO_ERROR=0,       // The connection with the SS7 stack is OK. 
         CNX_CLOSED,       // The connection with the SS7 stack has been closed.
         API_BUSY,         // Switch-over in progress.
         INTERNAL_ERROR
      };
      CnxStatus(StatusValue s) : StatusBase(s) {};
      CnxStatus() {};
      ~CnxStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      OpenStatus
//--------------------------------------------------------------------------
   class OpenStatus : public HPAIN::StatusBase {
   public:
      enum Status 
      {
         NO_ERROR = 0,
         NO_CONFIG,         // the configuration file could not be accessed.
         BAD_GLOBAL_CONFIG, // the configuration file could not be parsed to find 
                            // the specified SS7 name and/or which information.
         CONNECT_INIT,      // the attempt to connect was rejected. Check that the SS7 
                            // daemon is running, or check the configuration.
         API_BUSY,          // switch-over in progress, retry later.
         ALREADY_OPEN,      // the probe is already connected to the SS7 process.
         BAD_CNX_TYPE,      // the connection type is wrong (should be PRIMARY
                            // or SECONDARY.
         INTERNAL_ERROR
      };
      OpenStatus(StatusValue s) : StatusBase(s) {};
      OpenStatus() {};
      ~OpenStatus() {};
   };

//--------------------------------------------------------------------------
//                      CreateStatus
//--------------------------------------------------------------------------
   class CreateStatus : public HPAIN::StatusBase {
   public:
      enum Status
      {
         NO_ERROR = 0,              // No error.
         NO_MORE_MEMORY,            // Instanciation of the Probe failed.
         MAX_PROBE_NUMBER_EXCEEDED, // the maximum number of probe has been exceeded.
         ALREADY_CREATED,           // A probe already exists for this LPC.
         INVALID_CLASSNAME,         // The className specified is unknown.
         LPC_NOT_FOUND,             // There is no LPC corresponding to the className.
         INVALID_SET_NAME,          // Invalid message set name associated to the LPC.
         WRONG_PROBE_TYPE,          // The probe type doesn't correspond to the config.
         INTERNAL_ERROR             // Internal error detected.
      };
      CreateStatus(StatusValue s) : StatusBase(s) {};
      CreateStatus() {};
      ~CreateStatus() {};
   };

//--------------------------------------------------------------------------
//                      DestroyStatus
//--------------------------------------------------------------------------
   class DestroyStatus : public HPAIN::StatusBase {
   public:
      enum Status
      {
         NO_ERROR = 0,
         ALREADY_DESTROYED  // The object has been already destroyed.
      };
      DestroyStatus(StatusValue s) : StatusBase(s) {};
      DestroyStatus() {};
      ~DestroyStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      CloseStatus
//--------------------------------------------------------------------------
   class CloseStatus : public HPAIN::StatusBase {
   public:
      enum Status 
      {
         NO_ERROR = 0,
         PROBE_NOT_OPEN, // The Probe is not connected to the SS7 stack.
         ALREADY_CLOSED, // The Probe has been already closed.
         IPC_SEND_FULL,  // The socket connection with the SS7 stack is congested.
         CLOSE_FAILED,   // The attempt to close the connection with the SS7 stack failed.
         INTERNAL_ERROR
      };
      CloseStatus(StatusValue s) : StatusBase(s) {};
      CloseStatus() {};
      ~CloseStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      SendStatus
//--------------------------------------------------------------------------
   class SendStatus : public HPAIN::StatusBase {
   public:
      enum Status {
         NO_ERROR=0,
         PROBE_NOT_OPEN,         // Illegal call because the probe is not opened.
         PROBE_NOT_ACTIVE,       // Illegal call because the probe is not active.
         NOT_CONNECTED,          // Not connected or the connect sequence is not completed.
         ILLEGAL_PRIMITIVE,      // Illegal primitive for this probe.
         INCONSISTENT_ARGUMENTS, // Primitive and message type are inconsistents.
         ENCODING_ERROR,         // The Isup message attached cannot be encoded.
         MSG_TOO_LONG,		 // The Isup message encoding results in a too long PDU.
         IPC_SEND_FULL,          // The socket connection with the SS7 stack is congested.
         LPC_CONGESTED,          // The LPC specified is congested.
         DPC_CONGESTED,          // The DPC specified is congested.
         LPC_UNAVAILABLE,        // The MTP level3 is inactive, out of service or restarting.
         DPC_UNAVAILABLE,        // The DPC specified is not accessible via the ss7 network.
         NO_MORE_MEMORY,         // There is no available memory for creation of new object.
         INVALID_MESSAGE,        // The Isup message built is not valid.
         DPC_NOT_FOUND,          // The DPC specified doesn't exist in the configuration.
         LPC_NOT_FOUND,          // The LPC specified doesn't exist in the configuration.
         CIRCUIT_NOT_FOUND,      // The CIC specified doesn't exist in the configuration.
         UNEQUIPPED_CIRCUIT,     // The circuit specified is configured as unequipped.
	 NO_END_TO_END_METHOD,   // The circuit is not initialized with a end to end method.
	 INBOUND_CIRCUIT,        // The circuit is reserved for incoming calls.
	 ALREADY_SEIZED_OUTGOING,// The circuit is already in use with an outgoing call.
	 WRONG_STATE,            // Illegal primitive regarding the state.
	 IDLE_STATE,             // Illegal primitive  because the circuit/call state is IDLE.
         CIRCUITS_LEFT_UNRESPONDED,//Some circuits are not responded after a group-action.
	 ALREADY_SEIZED_INCOMING,// The circuit is already in use with an incoming call.
         CNX_CLOSED,             // The connection with the SS7 stack has been closed.
         API_BUSY,               // switch-over in progress, retry later.
         API_DISABLED,           // The connexion is now a secondary connexion.
	 INVALID_GROUP,          // invalid range or no circuits in the group message.
         INTERNAL_ERROR
      };
      SendStatus(StatusValue s) : StatusBase(s) {};
      SendStatus() {};
      ~SendStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      RecvStatus
//--------------------------------------------------------------------------
   class RecvStatus : public HPAIN::StatusBase {
   public:
      enum Status 
      {
         NO_ERROR=0,
         PROBE_NOT_OPEN,    // Illegal call because the probe is not opened.
         PROBE_NOT_ACTIVE,  // Illegal call because the probe is not active.
         NO_MSG,            // There is no message to receive.
         API_DISABLED,      // The connexion is now a secondary connexion.
         INTERNAL_ERROR
      };
      RecvStatus(StatusValue s) : StatusBase(s) {};
      RecvStatus() {};
      ~RecvStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      CtrlStatus
//--------------------------------------------------------------------------
   class CtrlStatus : public HPAIN::StatusBase {
   public:
      enum Status 
      {
       NO_ERROR=0,
       PROBE_NOT_OPEN,         // Illegal call because the probe is not open.
       ILLEGAL_VALUE,          // The value provided for this command is illegal.
       NOT_CONNECTED,          // Not connected or the connect sequence is not completed.
       CNX_CLOSED,             // The SS7 platform has closed the connection.
       API_BUSY,               // A manual or automatic switchover is in progress, so the
                               // should be retried later.
       PROBE_ALREADY_ACTIVE,   // Illegal call because the probe is already active.
       PROBE_ALREADY_INACTIVE, // Illegal call because the probe is already inactive.
       INTERNAL_ERROR
      };
      CtrlStatus(StatusValue s) : StatusBase(s) {};
      CtrlStatus() {};
      ~CtrlStatus() {};
   };
   
//--------------------------------------------------------------------------
//                      MsgStatus
//--------------------------------------------------------------------------
   class MsgStatus : public HPAIN::StatusBase {
   public:                                 
      enum Status {                       
         NO_ERROR=0,
         NO_MORE_MEMORY,
         SET_VALUE_ERROR,	// Parameter set accessor has failed
         GET_VALUE_ERROR,	// Parameter get accessor has failed
         IS_PRESENT_ERROR,	// Parameter isPresent accessor has failed
         READ_ERROR,		// Internal encoded data read has failed 
         WRITE_ERROR,		// Internal encoded data write has failed 
         RESETX_ERROR,		// Internal reset index on encoded data has failed 
         DECODE_ERROR,		// Internal decoding has failed 
         ENCODE_ERROR,		// Internal encoding has failed 
         INVALID_MESSAGE,	// Message invalid for this message set
         INVALID_PARM,		// Parameter invalid for this message
         INVALID_PARM_ID,	// Parameter identifier not known for this message
         INVALID_LENGTH,	// Parameter's length not matching description
         TYPE_MISMATCH,		// Parameter's type not matching description
         NOT_OPTIONAL,		// Parameter not optional
         INVALID_ACTION,	// Invalid action performed on message
         INVALID_TAG,		// Internal decoding has failed
         INTERNAL_ERROR,
         SET_ABSENT_ERROR     // Parameter Set Absent accessor has failed
      };                                              
      virtual void setStatus(StatusValue s) { StatusBase::setStatus(s); }
      MsgStatus() {};         
      ~MsgStatus() {};      
   };                                                    
      
//--------------------------------------------------------------------------
//                      InfoStatus
//--------------------------------------------------------------------------
   class InfoStatus : public HPAIN::StatusBase {
   public:
      enum Status {
         NO_ERROR=0,
         NO_MORE_MEMORY,
         INIT_FAILURE,		// Primitive called before initialisation
         INVALID_SET_NAME,	// Invalid message set name in Data Base 
         INVALID_SET_ID,	// Invalid provided message set identifier
         TOO_MANY_SET,		// Too many specified message set 
         INVALID_MSG_NAME,	// Invalid provided message name
         INVALID_MSG_ID,	// Invalid provided message identifier
         TOO_MANY_MSG,		// Too many specified messages 
         INVALID_PARM_NAME,	// Invalid provided parameter name
         TOO_MANY_PARM,		// Too many specified parameters 
         INVALID_MSG,		// Message already supported for that message set 
         INVALID_SPEC,		// ASN.1 description is invalid
         INVALID_DPC,		// Specified DPC not found in Data Base
	 INVALID_CLASS_NAME,	// Specified class name not found in Data Base
         INVALID_PARM,		// Parameter already supported for that message
         INTERNAL_ERROR
      };
      InfoStatus(StatusValue s) : StatusBase(s) {};
      InfoStatus() {};      
      ~InfoStatus() {};      
   };

//START DYNAMIC CONFIG
//--------------------------------------------------------------------------
//                      ConfigStatus
//--------------------------------------------------------------------------
   class ConfigStatus : public HPAIN::StatusBase {
   public:
      enum Status
      {
         NO_ERROR=0,
			NO_ISUP_MGR,         // Illegal call because IsupMgr is not initialized
         RELOAD_IN_PROGRESS,  // A Reload is already in progress
         DUMP_IN_PROGRESS,    // A dump is already in progress
			RELOAD_FAILED,			// The Reload has failed
			DUMP_FAILED,			// The dump has failed
			INTERNAL_ERROR
      };
      ConfigStatus(StatusValue s) : StatusBase(s) {};
      ConfigStatus() {};
      ~ConfigStatus() {};
   };
//--------------------------------------------------------------------------
//                      OamStatus
//--------------------------------------------------------------------------
   class OamStatus : public HPAIN::StatusBase {
   public:
      enum Status
      {
         NO_ERROR=0,
	 NO_ISUP_MGR,         // Illegal call because IsupMgr is not initialized
         RELOAD_IN_PROGRESS,  // Others notifications will be sent.
         RELOAD_IN_PROGRESS_NO_REPORT,  // No notifications will be sent
			DUMP_IN_PROGRESS,		// A dump is in progress
         RELOAD_FINISHED,     // No more notifications will be sent.
         DUMP_FINISHED,       // The Dump is finished
			RELOAD_FAILED,       // The reload has failed
			DUMP_FAILED,         // The dump has failed
			NO_REPORT,           // No notifications will be sent
         INTERNAL_ERROR,
         OPEN_CNX_IN_PROGRESS, // Open connection in progress
         OPEN_CNX_FINISHED,   // MTP router has been informed about ISUP instance's DPC set
         OPEN_CNX_FAILED      // Could not inform MTP router about ISUP instance's DPC set
      };
      OamStatus(StatusValue s) : StatusBase(s) {};
      OamStatus() {};
      ~OamStatus() {};
   };

//END DYNAMIC CONFIG

   class ParmValue 
   //
   // = TITLE
   // C++ encapsulation of a parameter value
   // 
   // = CLASS TYPE
   // Concrete
   //
   // = DESCRIPTION
   // Provides a base class for encapsulating a pointer of a parameter value.
   {
   public :
      ParmValue& assign(const char* s, HPAIN::Uint32 l);
      ParmValue& assign(const void* s, HPAIN::Uint32 l);
      ParmValue& assign(HPAIN::Uint32 i);
      ParmValue& assign(HPAIN::Uint16 i);
      ParmValue& assign(HPAIN::Byte b);
      ParmValue(const char* s, HPAIN::Uint32 l);
      ParmValue(const void* s, HPAIN::Uint32 l);
      ParmValue(HPAIN::Uint32 i);
      ParmValue(HPAIN::Uint16 i);
      ParmValue(HPAIN::Byte b);
      ParmValue();
      HPAIN::Boolean is_empty() const;
      void make_empty();
      HPAIN::Uint32 length() const;
      const void* pointer() const;
      
   private:
      ParmValue(const ParmValue&);
      const ParmValue& operator=(const ParmValue&);
      
      HPAIN::Uint32 _len;
      const void* _str;
      HPAIN::Boolean _isString;
   };
   //
   // = EXAMPLE
   //
   // This example shows how a ISUP::ParmValue can be set.
   //
   // = BEGIN<CODE>
   //
   //   ISUP::ParmValue* L_strParm = NEW ISUP::ParmValue("\0x7e", 1);
   //
   //   ISUP::ParmValue* L_byteParm = NEW ISUP::ParmValue();
   //   L_byteParm->assign((HPAIN::Byte)0x7e);
   //
   // = END<CODE>
   //
   // = NOTES
   
   
};  // end of ISUP class

ostream& operator<< (ostream& os, const ISUP::InfoStatus* m);
ostream& operator<< (ostream& os, const ISUP::InfoStatus& m);

ostream& operator<< (ostream& os, const ISUP::InitStatus* m);
ostream& operator<< (ostream& os, const ISUP::InitStatus& m);

ostream& operator<< (ostream& os, const ISUP::SetStatus* m);
ostream& operator<< (ostream& os, const ISUP::SetStatus& m);

ostream& operator<< (ostream& os, const ISUP::GetStatus* m);
ostream& operator<< (ostream& os, const ISUP::GetStatus& m);

ostream& operator<< (ostream& os, const ISUP::CtrlStatus* m);
ostream& operator<< (ostream& os, const ISUP::CtrlStatus& m);

ostream& operator<< (ostream& os, const ISUP::OpenStatus* m);
ostream& operator<< (ostream& os, const ISUP::OpenStatus& m);

ostream& operator<< (ostream& os, const ISUP::CloseStatus* m);
ostream& operator<< (ostream& os, const ISUP::CloseStatus& m);

ostream& operator<< (ostream& os, const ISUP::CreateStatus* m);
ostream& operator<< (ostream& os, const ISUP::CreateStatus& m);

ostream& operator<< (ostream& os, const ISUP::DestroyStatus* m);
ostream& operator<< (ostream& os, const ISUP::DestroyStatus& m);

ostream& operator<< (ostream& os, const ISUP::MsgStatus* m);
ostream& operator<< (ostream& os, const ISUP::MsgStatus& m);

ostream& operator<< (ostream& os, const ISUP::SendStatus* m);
ostream& operator<< (ostream& os, const ISUP::SendStatus& m);

ostream& operator<< (ostream& os, const ISUP::RecvStatus* m);
ostream& operator<< (ostream& os, const ISUP::RecvStatus& m);

ostream& operator<< (ostream& os, const ISUP::CnxStatus* m);
ostream& operator<< (ostream& os, const ISUP::CnxStatus& m);

ostream& operator<< (ostream& os, const ISUP::ParmValue* m);
ostream& operator<< (ostream& os, const ISUP::ParmValue& m);

//START DYNAMIC CONFIG
ostream& operator<< (ostream& os, const ISUP::ConfigStatus* m);
ostream& operator<< (ostream& os, const ISUP::ConfigStatus& m);

ostream& operator<< (ostream& os, const ISUP::OamStatus* m);
ostream& operator<< (ostream& os, const ISUP::OamStatus& m);

ostream& operator<< (ostream& os, const ISUP::CircuitState P_status);
ostream& operator<< (ostream& P_os, const ISUP::Protocol P_type);
ostream& operator<< (ostream& P_os, const ISUP::Reserved P_value);

//END DYNAMIC CONFIG

#endif /* __cplusplus */
#endif /* ISUP_COMMON_H */

