//------------------------------------------------------------------------------
//
//                               MODULE   IsupAdditionalInfo.h
//                               ------------------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupAdditionalInfo.h
//
// = AUTHOR
//      HP OC ISUP was developed by Hewlett Packard, TID.
//
// = COPYRIGHT
//     Hewlett Packard - Telecom Infrastructure Division (1999).

//  Rev: 
//       $Source: /ISUP/code/isupcore/IsupAdditionalInfo.h $
//       $Revision: 6.3 $
//       
//------------------------------------------------------------------------------

#ifndef ISUP_ADDITIONAL_INFO_H
#define ISUP_ADDITIONAL_INFO_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#include <IsupCommon.h>

#ifdef ISUP_A92
class ANSI92_CPC;
class ANSI92_CRO;
class ANSI92_CRR;
class ANSI92_CRI;
class ANSI92_DCO;
class ANSI92_CRS;
class ANSI92_BLR;
class ANSI92_BLS;
class ANSI92_CGRS;
class ANSI92_GBUS;
class ANSI92_CQS;  
#endif /* ISUP_A92 */
#ifdef ISUP_I88
class ITU88_CPC;
class ITU88_CRS;
class ITU88_BLR;
class ITU88_BLS;
class ITU88_MGBR;
class ITU88_MGBS;
class ITU88_HRB;
class ITU88_HLB;
class ITU88_HGBS;
class ITU88_HGBR;
class ITU88_CGRS;
class ITU88_CRR;
class ITU88_CRCR;
class ITU88_CRCS;
// HL: ITU97
class ITU97_CPC;
class ITU97_CRCR;
class ITU97_MGBR;
class ITU97_MGBS;
class ITU97_HGBS;
class ITU97_HGBR;
class ITU97_BLS;
class ITU97_CGRS;
// HL: End
#endif /* ISUP_I88 */

class IsupInspector;

class IsupAdditional
{

public:
   
   class Info
   {
   public:
      
      enum Type { SETUP, SETUP_FAILURE, START_RELEASE, START_RESET, 
                  MAINTENANCE_SYSTEM, LOCAL_RESET, RESET,
//START DYNAMIC CONFIG
                  SUSPEND_RESUME, NOTIF_DEL_DPC, NOTIF_DEL_CICS,
                  NOTIF_ADD_DPC, NOTIF_CICS };
//END DYNAMIC CONFIG
      
      virtual ~Info();                             // Delete an Info object. 
      virtual Type getInfoType() const=0;    // Returns info type (SETUP, ...)
                                                   // of current information parameter.
      friend ostream& operator<< (ostream& P_os, const Info& P_info);
      friend ostream& operator<< (ostream& P_os, const Info* P_info);
      
   protected:
      Info();                                        // constructor
     
   private:   // These methods are private to prevent any initialisation from any user.
      
      Info(const Info& P_from);                      // copy constructor          
      const Info& operator=(const Info& P_from);     // assignement
   };


  class Setup : public Info
  {
  public:
     
     Setup();                                // This constructor builds an empty Setup object.
     Setup(HPAIN::Boolean P_acm);            // This constructor builds a Setup object 
                                             // and set the acmControl parameter.
     virtual ~Setup();                       // This destructor delete a Setup object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static Setup* castInfo(const Info* P_addInfo);
     
     // Accessors providing read or write access for Setup parameter:
     HPAIN::Boolean getAcmControl() const;
     void setAcmControl(HPAIN::Boolean P_acm);
     
     friend ostream& operator<< (ostream& P_os, const Setup& P_info);
     friend ostream& operator<< (ostream& P_os, const Setup* P_info);
     
  private: 
     
     HPAIN::Boolean acmControlFlag;
     
     // These methods are private to prevent any initialisation from any user:
     Setup(const Setup& P_from);
     const Setup& operator=(const Setup&);
  };

  class SetupFailure : public Info
  {

#ifdef ISUP_A92
     friend class ANSI92_CPC;
#endif

#ifdef ISUP_I88
     // HL: ITU97
     friend class ITU97_CPC;
     friend class ITU97_CRCR;
     // HL: End
     friend class ITU88_CPC;
     friend class ITU88_CRCR; 
     friend class ITU88_CRCS;
#endif

     friend class IsupInspector;
     
  public:
     
     enum Cause { UNSPECIFIED, DUAL_SEIZURE , 
                  FLOW_CONTROL, BLOCKING,
                  COT_FAILURE,
                  RELEASE,
                  T27_TIMEOUT,
                  CPC_BUSY,
		  CRCR_RESET
                };    // setup failure cause
     
     virtual ~SetupFailure();                // This destructor delete a SetupFailure object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static SetupFailure* castInfo(const Info* P_addInfo) ;
     
     // Accessor providing read access for SetupFailure parameter:
     Cause getCause() const;
     
     friend ostream& operator<< (ostream& P_os, const SetupFailure& P_info);
     friend ostream& operator<< (ostream& P_os, const SetupFailure* P_info);
     
  private:
     
     Cause setupFailureCause;
     
     // These methods can be only used by friend classes:
     SetupFailure();                // This constructor builds an empty SetupFailure object.
     SetupFailure(Cause P_cause);   // This constructor builds a SetupFailure object
  				    // and set the setupFailureCause parameter.
     void setCause(Cause P_cause);  // Accessor providing write access for SetupFailure parameter:

     
     // These methods are private to prevent any initialisation from any user:
     SetupFailure(const SetupFailure& P_from);
     const SetupFailure& operator=(const SetupFailure&);
  };
  
  class StartRelease : public Info
  {

#ifdef ISUP_A92
     friend class ANSI92_CPC;
     friend class ANSI92_CRO;
#endif

#ifdef ISUP_I88
     friend class ITU88_CPC;
     friend class ITU88_CRCS;
     // HL: ITU97
     friend class ITU97_CPC;
     // HL: End
#endif

     friend class IsupInspector;
     
  public:
     
     enum Cause { UNEXPECTED_RLC, T7_TIMEOUT , T33_TIMEOUT , 
                  T_CRA_TIMEOUT , BLOCKING,
                  RELEASE_REQUEST,
                  T8_TIMEOUT, T1_TIMEOUT, DCO_SUCCESS, STOP_REQ,
                  T9_TIMEOUT, CONTINUITY_SUCCESS, BACKWARD_CHECK_TONE_ACK,
                  T6_TIMEOUT, T2_TIMEOUT, UNEXPECTED_CCL	//CHINA Flavor
                }; // StartRelease cause
     
     virtual ~StartRelease();        // This destructor delete a StartRelease object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static StartRelease* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for StartRelease parameter:
     Cause getCause() const;
     
     friend ostream& operator<< (ostream& P_os, const StartRelease& P_info);
     friend ostream& operator<< (ostream& P_os, const StartRelease* P_info);
     
  private:
     
     Cause releaseCause;
     
     // These methods can be only used by friend classes:
     StartRelease();                 // This constructor builds an empty StartRelease object.
     StartRelease(Cause P_cause);    // This constructor builds a StartRelease object
 				     // and set the releaseCause parameter.
     void setCause(Cause P_cause);   // Accessor providing write access for StartRelease parameter:

     // These methods are private to prevent any initialisation from any user:
     StartRelease(const StartRelease& P_from);
     const StartRelease& operator=(const StartRelease&);
  };
  
  class StartReset : public Info
  {
#ifdef ISUP_A92
     friend class ANSI92_CPC;
     friend class ANSI92_CRR;
     friend class ANSI92_CRI;
     friend class ANSI92_CRO;  
     friend class ANSI92_DCO;  
     friend class IsupANSI92Strategy;
#endif

#ifdef ISUP_I88
     friend class ITU88_CPC;
     friend class ITU88_CRR;
     // HL: ITU97
     friend class ITU97_CPC;
     // HL: End
     friend class IsupITU88Strategy;
#endif

     friend class IsupInspector;
     
  public:
     
     enum Cause { NO_REASON, UNEXPECTED_MESSAGE, T5_TIMEOUT, BLOCKING_WITH_RELEASE,
                  COT_CC_NOT_REQUIRED, COT_FAILURE, TCCRr_TIMEOUT, T27_TIMEOUT, T34_TIMEOUT,
                  DCO_LPA_FAIL , UNEQUIPPED_CIRCUIT, TIMER_SHORTAGE
                };// StartReset cause
     
     virtual ~StartReset();         // This destructor delete a StartReset object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static StartReset* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for StartReset parameter:
     Cause getCause() const;
     
     friend ostream& operator<< (ostream& P_os, const StartReset& P_info);
     friend ostream& operator<< (ostream& P_os, const StartReset* P_info);
     
  private:
     
     Cause resetCause;
     
     // These methods can be only used by friend classes:
     StartReset();                  // This constructor builds an empty StartReset object.
     StartReset(Cause P_cause);     // This constructor builds a StartReset object
   				    // and set the resetCause parameter.   
     void setCause(Cause P_cause);  // Accessor providing write access for StartReset parameter:

     // These methods are private to prevent any initialisation from any user:
     StartReset(const StartReset& P_from);
     const StartReset& operator=(const StartReset&);
  };
  
  class MaintenanceSystem : public Info
  {

#ifdef ISUP_A92
     friend class ANSI92_CPC;
     friend class ANSI92_CRS;
     friend class ANSI92_BLR;
     friend class ANSI92_BLS;
     friend class ANSI92_CGRS;
     friend class ANSI92_GBUS;
     friend class ANSI92_CRI;
     friend class ANSI92_CRO;
     friend class ANSI92_ACR;
     friend class IsupANSI92Strategy;
     friend class ANSI92_CVTS;
     friend class ANSI92_CQS;
     friend class ANSI92_CRR;
#endif

#ifdef ISUP_I88
     friend class ITU88_CPC;
     friend class ITU88_CRS;
     friend class ITU88_BLR;
     friend class ITU88_BLS;
     friend class ITU88_MGBR;
     friend class ITU88_MGBS;
     friend class ITU88_HRB;
     friend class ITU88_HLB;
     friend class ITU88_HGBS;
     friend class ITU88_HGBR;
     friend class ITU88_CGRS;
     friend class ITU88_CRCR;
     friend class ITU88_CRCS;
     friend class ITU88_CQS;
     friend class ITU88_ACR;
     // HL: ITU97
     friend class ITU97_CPC;
     friend class ITU97_SSC;
     friend class ITU97_CQS;
     friend class ITU97_CRCR;
     friend class ITU97_MGBR;
     friend class ITU97_MGBS;
     friend class ITU97_HGBS;
     friend class ITU97_HGBR;
     friend class ITU97_BLS;
     friend class ITU97_CGRS;
     // HL: End
     friend class IsupITU88Strategy;
#endif

     friend class IsupInspector;
     
  public:
     
     // MaintenanceSystem event
     enum Event
              {
                  T5_TIMEOUT, 
                  T17_TIMEOUT, 
                  RSC_AFTER_T17, 
                  RLC_AFTER_T17,
                  CRS_STOP ,
                  
                  MN_BLOCKING, 
                  HW_BLOCKING, 
                  MN_UNBLOCKING,
                  HW_UNBLOCKING,
                  MN_GROUP_BLOCKING,
                  HW_GROUP_BLOCKING,
                  MN_GROUP_UNBLOCKING,
                  HW_GROUP_UNBLOCKING,

                  T12_NOT_RUNNING,
                  T13_TIMEOUT,
                  T14_NOT_RUNNING,
                  T15_TIMEOUT,
                  T22_NOT_RUNNING,
                  T19_TIMEOUT,
                  T21_TIMEOUT,
                  T23_TIMEOUT,
                  T18_NOT_RUNNING,
                  PRIORITY_TO_GROUP_RESET,
                  T20_NOT_RUNNING,

                  WRONG_STATUS_BITS,
                  UCIC_STOP,
                  COT_RECEIVED,
                  DCO_FAIL,
                  DCO_SUCCESS,
                  STOP_REQ,
                  REL_RECEIVED,

                  T24_TIMEOUT,
                  BACKWARD_CHECK_TONE_ACK,

                  T28_TIMEOUT,
                  T34_TIMEOUT,

                  UNEQUIPPED_CIRCUIT,
                  TIMER_SHORTAGE,
                  RECV_ON_UNEQUIPPED_CIRCUIT,

                  BLA_WHEN_IDLE,
                  UBA_WHEN_LOCALLY_BLOCKED,
                  NON_ISDN_ACCESS_INDICATION,
                  CIRCUIT_VALIDATION_TEST_FAILED,

                  BLOCKING,    // GREhp33363
                  UNBLOCKING,  // GREhp33363
                  
                  RSC_RECEIVED
                }; 
     
     virtual ~MaintenanceSystem();       // This destructor delete a MaintenanceSystem object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static MaintenanceSystem* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for MaintenanceSystem parameter:
     Event getEvent() const;
     
     friend ostream& operator<< (ostream& P_os, const MaintenanceSystem& P_info);
     friend ostream& operator<< (ostream& P_os, const MaintenanceSystem* P_info);
     
  private:
     
     Event maintenanceSystemEvent;
     
     // These methods can be only used by friend classes:
     MaintenanceSystem();                // This constructor builds an empty MaintenanceSystem object.
     MaintenanceSystem(Event P_event);   // This constructor builds a MaintenanceSystem object
                                         // and set the maintenanceSystemEvent parameter.
     void setEvent(Event P_event);       // Accessor providing write access for MaintenanceSystem parameter

     // These methods are private to prevent any initialisation from any user:
     MaintenanceSystem(const MaintenanceSystem& P_from);
     const MaintenanceSystem& operator=(const MaintenanceSystem&);
  };

  class Reset : public Info
  {     
  public:
     
     // Reset event
     enum Event { GROUP_RESET }; 
     
     Reset();                           // This constructor builds an empty Reset object.
     Reset(Event P_event);              // This constructor builds a Reset object
                                        // and set the resetEvent parameter.
     virtual ~Reset();                  // This destructor delete a Reset object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static Reset* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for Reset parameter:
     Event getEvent() const;
     void setEvent(Event P_event);
     
     friend ostream& operator<< (ostream& P_os, const Reset& P_info);
     friend ostream& operator<< (ostream& P_os, const Reset* P_info);
     
  private:
     
     Event resetEvent;
     
     // These methods are private to prevent any initialisation from any user:
     Reset(const Reset& P_from);
     const Reset& operator=(const Reset&);
  };

  class LocalReset : public Info
  {

#ifdef ISUP_A92
     friend class ANSI92_CPC;
     friend class ANSI92_GBUS;
     friend class ANSI92_CGRS;
     friend class ANSI92_CRS;
     friend class ANSI92_BLS;
     friend class ANSI92_CQS; // ANSI_CQS
#endif

#ifdef ISUP_I88
     friend class ITU88_CPC;
     // HL: ITU97
     friend class ITU97_CPC;
     friend class ITU97_MGBS;
     friend class ITU97_HGBS;
     friend class ITU97_CQS;
     friend class ITU97_BLS;
     friend class ITU97_SSC;
     friend class ITU97_CGRS;
     friend class ITU97_CRCR;
     // HL: End
     friend class ITU88_CRS;
     friend class ITU88_CQS;
     friend class ITU88_CGRS;
     friend class ITU88_MGBS;
     friend class ITU88_HGBS;
     friend class ITU88_CRCS;
     friend class ITU88_BLS;
     friend class ITU88_CRCR;
     friend class ITU88_ACR;
#endif

     friend class IsupInspector;
     
  public:
     
     // LocalReset cause
     enum Cause { MTP_UNAVAILABLE, DPC_UNAVAILABLE , BLS_STOPPED, CRS_STOPPED, CQS_STOPPED, CRCR_STOPPED,
		  GBUS_STOPPED, CGRS_STOPPED, MGBS_STOPPED, HGBS_STOPPED, CRCS_STOPPED, DCO_STOPPED}; 
     
     virtual ~LocalReset();       // This destructor delete a MaintenanceSystem object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static LocalReset* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for MaintenanceSystem parameter:
     Cause getCause() const;
     
     friend ostream& operator<< (ostream& P_os, const LocalReset& P_info);
     friend ostream& operator<< (ostream& P_os, const LocalReset* P_info);
     
  private:
     
     Cause LocalResetCause;
     
     // These methods can be only used by friend classes:
     LocalReset();                 // This constructor builds an empty MaintenanceSystem object.
     LocalReset(Cause P_cause);    // This constructor builds a MaintenanceSystem object
                                   // and set the maintenanceSystemEvent parameter.
     void setCause(Cause P_cause); // Accessor providing write access for MaintenanceSystem parameter:


     // These methods are private to prevent any initialisation from any user:
     LocalReset(const LocalReset& P_from);
     const LocalReset& operator=(const LocalReset&);
  };

  
  class SuspendResume : public Info
  {
#ifdef ISUP_I88
     friend class ITU88_CPC;
     // HL: ITU97
     friend class ITU97_CPC;
     // HL: End
#endif

     friend class IsupInspector;
     
  public:
     
     enum Origin { FROM_USER, FROM_NETWORK };// SuspendResume Origin
     
     virtual ~SuspendResume();         // This destructor delete a SuspendResume object.
     virtual Info::Type getInfoType() const; // Returns info type
     
     // This method provides a safe down cast:
     static SuspendResume* castInfo(const Info* P_addInfo);
     
     // Accessor providing read access for SuspendResume parameter:
     Origin getOrigin() const;
     
     friend ostream& operator<< (ostream& P_os, const SuspendResume& P_info);
     friend ostream& operator<< (ostream& P_os, const SuspendResume* P_info);
     
  private:
     
     Origin susresOrigin;
     
     // These methods can be only used by friend classes:
     SuspendResume();               // This constructor builds an empty SuspendResume object.
     SuspendResume(Origin P_origin);  // This constructor builds a SuspendResume object
   				    // and set the Origin parameter.   
     void setOrigin(Origin P_origin);  // Accessor providing write access for SuspendResume parameter:

     // These methods are private to prevent any initialisation from any user:
     SuspendResume(const SuspendResume& P_from);
     const SuspendResume& operator=(const SuspendResume&);
  };

//START DYNAMIC CONFIG
	class NotifDelDpc : public Info
	{
		friend class IsupMgr;
		public :
			// These methods can be only used by friend classes:
			NotifDelDpc();               // This constructor builds an empty NotifDelDpc object.
			NotifDelDpc(ISUP::dpcAddress *P_addr);

			virtual ~NotifDelDpc();             // The destructor delete a NotifDelDpc object.
			virtual Info::Type getInfoType() const; // Returns info type	

			// This method provide a safe down cast:
			static NotifDelDpc *castInfo(const Info *P_info);

			// Accessor providing read access for NotifDelDpc parameters:
			ISUP::PointCode OPC() const;
			ISUP::PointCode DPC() const;

			friend ostream& operator<< (ostream& P_os, const NotifDelDpc& P_info);
			friend ostream& operator<< (ostream& P_os, const NotifDelDpc* P_info);

		private:

			ISUP::dpcAddress addr;
			
			void setOPC(ISUP::PointCode P_OPC);
			void setDPC(ISUP::PointCode P_DPC);

			// These methods are private to prevent any initialization from any user:
			NotifDelDpc (const NotifDelDpc& P_from);
			const NotifDelDpc& operator=(const NotifDelDpc&);
	};

	class NotifDelCics : public Info
	{
		friend class IsupMgr;
		public:
			// These methods can be only used by friend classes:
			NotifDelCics();               // This constructor builds an empty NotifDelCics object.
			NotifDelCics(ISUP::cicRangeAddress *P_addr);

			virtual ~NotifDelCics();             // The destructor delete a NotifDelCics object.
			virtual Info::Type getInfoType() const; // Returns info type	

			// This method provide a safe down cast:
			static NotifDelCics *castInfo(const Info *P_info);

			// Accessor providing read access for NotifDelCics parameters:
			ISUP::PointCode OPC() const;
			ISUP::PointCode DPC() const;
			ISUP::Cic CICMIN() const;
			ISUP::Cic CICMAX() const;

			friend ostream& operator<< (ostream& P_os, const NotifDelCics& P_info);
			friend ostream& operator<< (ostream& P_os, const NotifDelCics* P_info);

		private:

			ISUP::cicRangeAddress addr;
			
			void setOPC(ISUP::PointCode P_OPC);
			void setDPC(ISUP::PointCode P_DPC);
			void setCICMIN(ISUP::Cic P_min);
			void setCICMAX(ISUP::Cic P_max);

			// These methods are private to prevent any initialization from any user:
			NotifDelCics (const NotifDelCics& P_from);
			const NotifDelCics& operator=(const NotifDelCics&);
	};

	class NotifAddDpc : public Info
	{
		friend class IsupMgr;
		public :
			// These methods can be only used by friend classes:
			NotifAddDpc();               // This constructor builds an empty NotifAddDpc object.
			NotifAddDpc(ISUP::dpcAddress *P_addr,char *P_name,HPAIN::Uint32 P_cause);

			virtual ~NotifAddDpc();             // The destructor delete a NotifAddDpc object.
			virtual Info::Type getInfoType() const; // Returns info type	

			// This method provide a safe down cast:
			static NotifAddDpc *castInfo(const Info *P_info);

			// Accessor providing read access for NotifAddDpc parameters:
			ISUP::PointCode OPC() const;
			ISUP::PointCode DPC() const;
			const char *MsgSetName() const;
			HPAIN::Uint32 releaseCause() const;

			friend ostream& operator<< (ostream& P_os, const NotifAddDpc& P_info);
			friend ostream& operator<< (ostream& P_os, const NotifAddDpc* P_info);

		private:

			ISUP::dpcAddress addr;
			char       *msgSetName;
			HPAIN::Uint16    cause;
			
			void setOPC(ISUP::PointCode P_OPC);
			void setDPC(ISUP::PointCode P_DPC);
			void setADDR(ISUP::dpcAddress *P_addr);
			void setMsgSetName(const char *P_name);
			void setReleaseCause(HPAIN::Uint32 P_cause);

			// These methods are private to prevent any initialization from any user:
			NotifAddDpc (const NotifAddDpc& P_from);
			const NotifAddDpc& operator=(const NotifAddDpc&);
	};

	
	class NotifCics : public Info
	{
		friend class IsupMgr;
		public:
			enum Operation { CICS_ADDED, CICS_MODIFIED };
			// These methods can be only used by friend classes:
			NotifCics();               // This constructor builds an empty NotifCics object.
#ifdef ISUP_A92
//			NotifCics(ISUP::cicRangeAddress *P_addr, 
//						ISUP::Reserved P_res, ISUP::CircuitState P_state,
//						list<ISUP::Cic> *P_range, Operation P_op);
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
			NotifCics(ISUP::cicRangeAddress *P_addr, 
						ISUP::Reserved P_res,
						List<ISUP::Cic> *P_range, Operation P_op);
#else
			NotifCics(ISUP::cicRangeAddress *P_addr, 
						ISUP::Reserved P_res,
						list<ISUP::Cic> *P_range, Operation P_op);
#endif
//USL&STL-End
#else
//			NotifCics(ISUP::cicRangeAddress *P_addr, 
//						ISUP::Reserved P_res, ISUP::CircuitState P_state,
//						Operation P_op);
			NotifCics(ISUP::cicRangeAddress *P_addr, 
						ISUP::Reserved P_res, Operation P_op);
#endif

			virtual ~NotifCics();             // The destructor delete a NotifCics object.
			virtual Info::Type getInfoType() const; // Returns info type	

			// This method provide a safe down cast:
			static NotifCics *castInfo(const Info *P_info);

			// Accessor providing read access for NotifCics parameters:
			ISUP::PointCode OPC() const;
			ISUP::PointCode DPC() const;
			ISUP::Cic CICMIN() const;
			ISUP::Cic CICMAX() const;
			Operation getOperation() const;
			ISUP::Reserved reserved() const;
//			ISUP::CircuitState circuitState() const;
#ifdef ISUP_A92
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
			List <ISUP::Cic> defaultGroup() const;
#else
			list <ISUP::Cic> defaultGroup() const;
#endif
//USL&STL-End
#endif

			friend ostream& operator<< (ostream& P_os, const NotifCics& P_info);
			friend ostream& operator<< (ostream& P_os, const NotifCics* P_info);

		private:

			ISUP::cicRangeAddress addr;
			ISUP::Reserved        res;
//			ISUP::CircuitState    state;
			Operation             op;
#ifdef ISUP_A92
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
			List<ISUP::Cic>       group;
#else
			list<ISUP::Cic>       group;
#endif
//USL&STL-End
#endif
			
			void setOPC(ISUP::PointCode P_OPC);
			void setDPC(ISUP::PointCode P_DPC);
			void setCICMIN(ISUP::Cic P_min);
			void setCICMAX(ISUP::Cic P_max);
			void setADDR(ISUP::dpcAddress *P_addr);
			void setRADDR(ISUP::cicRangeAddress *P_addr);
			void setOperation(Operation P_op);
			void setReserved(ISUP::Reserved P_res);
//			void setCircuitState(ISUP::CircuitState P_state);
#ifdef ISUP_A92
			void setDefaultGroup(IsupRange *P_range);
#endif

			// These methods are private to prevent any initialization from any user:
			NotifCics (const NotifCics& P_from);
			const NotifCics& operator=(const NotifCics&);
	};
//END DYNAMIC CONFIG
    
  
};
ostream& operator<< (ostream& P_os, IsupAdditional::Info::Type P_kind);
ostream& operator<< (ostream& P_os, IsupAdditional::SetupFailure::Cause P_cause);
ostream& operator<< (ostream& P_os, IsupAdditional::StartRelease::Cause P_cause);
ostream& operator<< (ostream& P_os, IsupAdditional::StartReset::Cause P_cause);
ostream& operator<< (ostream& P_os, IsupAdditional::MaintenanceSystem::Event P_event);
ostream& operator<< (ostream& P_os, IsupAdditional::Reset::Event P_event);
ostream& operator<< (ostream& P_os, IsupAdditional::LocalReset::Cause P_cause);
ostream& operator<< (ostream& P_os, IsupAdditional::SuspendResume::Origin P_origin);
ostream& operator<< (ostream& P_os, IsupAdditional::NotifCics::Operation P_op);

#endif // ISUP_ADDITIONAL_INFO_H
