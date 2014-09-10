//-----------------------------------------------------------------
//
//                               MODULE   IsupMgr.h
//                               ------------------
//
//
//  PURPOSE:
//
// = FILENAME
//     IsupMgr.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TND.
// = COPYRIGHT
//           Hewlett Packard - Telecom Network Division (1996).
//

// 
//
// $Source: /ISUP/code/isupcore/IsupMgr.h $
// $Revision: 6.1.1.5 $
// 
//
//-----------------------------------------------------------------

#ifndef ISUP_MGR_H
#define ISUP_MGR_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#include <IsupCommon.h>
#include <IsupProbe.h>
#include <IsupBPProbe.h>
#include <IsupSMProbe.h>
#include <IsupAdditionalInfo.h>
#include <signal.h>
//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
#include <List.h>
#else
#include <list>
#endif
//USL&STL-End

class IsupSMProbeImpl;
class IsupBPProbeImpl;
class IsupNavigator;
class IsupAdditionalInfo;

// START DYNAMIC CONFIG
void reloadHandler(int sig);
// END DYNAMIC CONFIG

class IsupMgr : public HPAIN::Schedulable
 {
   // = TITLE
   //     The main entry point of the HP OC ISUP API. (<{VERSION 2.0}>).
   //
   // = DESCRIPTION
   // = BEGIN<INDENT>
   // This class is mostly a factory of IsupSMProbe and IsupBPProbe objects. In 
   // addition, it provides the basic scheduling for the HP OC ISUP API: selectMasks(), 
   // handler() and doWork() interfaces. Only a single instance of the IsupMgr is
   // allowed.
   //
   // <{Creation/Destruction of the Probes}> :
   // The creation of a Probe object (IsupSMProbe or IsupBPProbe) is achieved in two steps. 
   // The first step
   // is the instantiation of the object and its internal initialization. At this 
   // stage, it is not possible to exchange data with the network until
   // the opening procedure has been fully completed. The second step is the 
   // connection with the HP OC SS7 Stack using the open() method on the newly  
   // created Probe object (see <{IsupProbe}> MAN page). The reverse principle is
   // applied to close and delete a Probe. First, the close() method of the Probe
   // (see <{IsupMgr}> MAN page), then the appropriate destroy method of the IsupMgr
   // is applied.
   //
   // <{Scheduling}> :
   // The IsupMgr is responsible for scheduling the HP OC ISUP API.
   // Scheduling is based on three calls, in addition to the HP-UX select (2): 
   // selectMask, handler and doWork.
   //
   // Before calling select, the <{selectMask}> method must be called in order to set
   // the masks corresponding to the connections associated with the different
   // Probes. There is no distinction between normal (IsupSMProbe) and bypass
   // (IsupBPProbe) Probes. The selectMask method 
   // also includes a timeout value to be used for the select call. This value
   // is compared to the value necessary for the API and the smaller is returned.
   // Then, <{select(2)}> can be called. 
   //
   // After the select, the <{handler}> method of the IsupMgr must be called.
   // It analyses the result of the select call, extracting messages 
   // from channels, and services all the active connections to the HP OC SS7 Platform.
   // The handler method returns the remaining "amount of work" to be done. 
   // 
   // In order to process the messages and activate the state machines, the IsupMgr's
   // <{doWork}> method must be called.
   // During the doWork function, a callback function (given in the opening procedure)
   // is called indicating, for each Probe the number of indications/messages waiting
   // to be received. At this point, the <{recv}> method is called (several times if 
   // necessary), to receive the ISUP indications/messages. 
   // 
   // = END<INDENT> 
	   
	   
 public:
	   
	static HPAIN::Uint32 getApplicationId();
	// This method is called to get the applicationId 

   // = METHODS
   static ISUP::InitStatus init(HPAIN::Uint32 P_applicationId);

   static ISUP::InitStatus init(IsupMgr *& P_mgr);
   // This static method creates and initializes the IsupMgr object
   // (only one instance), load the ISUP configuration defined in the
   // isup.app0.conf (or if inexistent isup.conf) file and creates/initializes
   // all necessary internal objects.
   // If the IsupMgr already exists, P_mgr will point
   // to the already existing instance. 
   //
   // <{Return Status}> 
   //  NO_ERROR            
   //  ALREADY_CREATED  - the IsupMgr already exists.
   //  NO_MORE_MEMORY   - problem during memory allocation for 
   //                     the IsupMgr.
   //  NO_ISUP_CONFIG   - cannot access to the isup config file
   //                     ( absent or permission denied ).
   //  BAD_ISUP_CONFIG  - the isup config file is wrong.
   //  INTERNAL_ERROR       
   //
   //

   static ISUP::InitStatus init(IsupMgr *& P_mgr,HPAIN::Uint32 P_applicationId);
   // This static method creates and initializes the IsupMgr object for a given
   // application identified by P_applicationId.
   // (only one instance), load the ISUP configuration defined in the
   // isup.app<P_applicationId>.conf (or if unexistent isup.conf) file located in
   // the ISUP configuration directory and creates/initializes all the internal
   // objects. If the IsupMgr already exists, P_mgr will point
   // to the already existing instance.

   // <{Return Status}>
   //  NO_ERROR
   //  ALREADY_CREATED  - the IsupMgr already exists.
   //  NO_MORE_MEMORY   - problem during memory allocation for
   //                     the IsupMgr.
   //  NO_ISUP_CONFIG   - cannot access to the isup config file
   //                     ( absent or permission denied ).
   //  BAD_ISUP_CONFIG  - the isup config file is wrong.
   //  INTERNAL_ERROR
   //
   //
   //

   static ISUP::InitStatus init(IsupMgr *& P_mgr,
				HPAIN::Uint32 P_applicationId,
				HPAIN::Boolean P_cicDistributed);
   // This init method performs the same actions as the previously described
   // init method except for the connection to the network. If
   // P_cicDistributed is TRUE then the CIC-based distribution is enabled and
   // the connection to the network is made through the Traffic Distributor
   // (also called TDI that is connected on top of SS7 Stack). This allows
   // several ISUP applications to be connected to the network. Else the
   // connection is made directly on top of SS7 Stack.
   //
   //
   //

   static HPAIN::Boolean getCicDistributedState();
   // This method indicates whether the CIC-based distribution is set or not.
   //
   //
   // <{Return Value}>
   //	HPAIN::bTrue		- CIC-based distribution is enabled
   //	HPAIN::bFalse		- CIC-based distribution is disabled
   //
   //
   //

   static ISUP::DestroyStatus destroy(IsupMgr *& P_mgr);
   // This static method allows to destroy the Isup Manager object.
   //
   // <{Return Status}> 
   //  NO_ERROR             
   //  ALREADY_DESTROYED    - the object has been already destroyed.
   //
   //
   //
   ISUP::CreateStatus createSMProbe(const char *                         P_className,
                                    IsupSMProbe::ActivityObject * const  P_cbObj,
                                    IsupSMProbe *&                       P_newProbe);
   // Factory of IsupSMProbe objects. An IsupSMProbe object is built in order to be
   // bound later (using open() method on the createdIsupSMProbe) to a HP OC SS7 Stack
   // named by P_className (cf global. conf). As there is no  direct constructor for the
   // IsupProbe object, it must be initialized via the IsupMgr object. 
   // Note that in the current version, only one IsupSMProbe or IsupBPProbe is allowed per 
   // HP OC SS7 Stack (className).
   //
   ISUP::CreateStatus createBPProbe(const char *                         P_className,
                                    IsupBPProbe::ActivityObject * const  P_cbObj,
                                    IsupBPProbe *&                       P_newProbe);
   // Factory of IsupBPProbe objects. An IsupBPProbe object is built in order to be
   // bound later (using open() on the created IsupBPProbe) onto the HP OC SS7 stack
   // named by P_className (cf global.conf). Like the IsupSMProbe, there is no direct  
   // constructor  for the IsupBPProbe object, it must be initialized via the IsupMgr 
   // object. Note that in current version, only one IsupProbe or IsupBPProbe  
   // is allowed per HP OC SS7 Stack (className). 
   //
   // <{Return Status}>
   //  NO_ERROR                  - no error.
   //  NO_MORE_MEMORY            - instantiation of the Probe failed.
   //  MAX_PROBE_NUMBER_EXCEEDED - the maximum number of probe has been 
   //                              exceeded.
   //  ALREADY_CREATED           - a probe already exists for this LPC.
   //  LPC_NOT_FOUND             - the className specified is unknown.
   //  INVALID_CLASSNAME         - there is no LPC corresponding to the 
   //                              className.
   //  INVALID_SET_NAME          - invalid message set name associated to 
   //                              the LPC.
   //  WRONG_PROBE_TYPE          - probe type not consistent with the 
   //                              configuration.
   //  INTERNAL_ERROR            - internal error detected.
   //

   ISUP::DestroyStatus destroySMProbe(IsupSMProbe *& P_SMprobe);
   // This method destroys an IsupSMProbe. The pointer to the IsupSMProbe
   // is set to NULL to avoid the user reusing the object after its destruction.
   //
   ISUP::DestroyStatus destroyBPProbe(IsupBPProbe *& P_BPprobe);
   // This method destroys an IsupBPProbe. The pointer to the IsupBPProbe
   // is set to NULL to avoid the user reusing the object after its destruction.
   //
   // <{Return Status}>
   //  NO_ERROR          - no error.
   //  ALREADY_DESTROYED - the object has been already destroyed.
   //

//START DYNAMIC CONFIG
	static ISUP::ConfigStatus reload();
	// This method perform a dynamic reload of the ISUP configuration. 
   // The new ISUP configuration is generated using SAM interface.
	// 
	// <{Return Status}>
	// NO_ERROR                  - no error.
	// NO_ISUP_MGR               - no init has been done on IsupMgr.
	// RELOAD_IN_PROGRESS        - a reload is already in progress.
	// DUMP_IN_PROGRESS          - a dump is already in progress.
	// RELOAD_FAILED             - the reload has failed.
	//

	static ISUP::ConfigStatus dump();
	// This method perform a dynamic dump of the current ISUP configuration.
	//
	// <{Return Status}>
	// NO_ERROR                  - no error.
	// NO_ISUP_MGR               - no init has been done on IsupMgr.
	// RELOAD_IN_PROGRESS        - a reload is already in progress.
	// DUMP_IN_PROGRESS          - a dump is already in progress.
	// DUMP_FAILED               - a dump has failed.
	//

	ISUP::OamStatus oamReceive(IsupAdditional::Info *&P_notif, HPAIN::Uint32 &P_nbLast);
	// This method gets the Isup notification corresponding to configuration changes
	// which occurred during a reload procedure.
	// If set P_notif points to a notification corresponding to a configuration change.
	// The P_nbLast is the number of notifications last to be read.
	// 
	// <{Return Status}>
	// NO_ERROR                            - no error.
	// NO_ISUP_MGR                         - no init has been done on IsupMgr.
	// NO_REPORT                           - reportOnReload has not been enabled.
	// RELOAD_IN_PROGRESS                  - others notifications will be sent.
	// RELOAD_FINISHED                     - no more notifications will be sent.
  	// RELOAD_IN_PROGRESS_NO_REPORT        - reportOnReload has not been enabled and a reload is in progress.
	// RELOAD_FAILED                       - reload has failed.
	//

	ISUP::OamStatus oamStatus();
	// This method return a status indicating reload/dump procedure status.
	// 
	// <{Return Status}>
	// NO_ERROR                            - no error.
	// RELOAD_IN_PROGRESS                  - others notifications will be sent.
	// RELOAD_FINISHED                     - no more notifications will be sent.
  	// RELOAD_IN_PROGRESS_NO_REPORT        - reportOnReload has not been enabled.
	// RELOAD_FAILED                       - reload has failed
	// DUMP_IN_PROGRESS                    - a dump is in progress
	// DUMP_FINISHED                       - a dump is finished
	// DUMP_FAILED                         - a dump has failed
	//
//END DYNAMIC CONFIG
	
  
#ifdef _WIN32
   virtual int preWaitForMultipleObjects(DWORD*  P_numHdl,
					DWORD    P_maxHdl,
					HANDLE*  P_hdlTab,
					int*     P_timeout);

  virtual HPAIN::Schedulable::Work handler(DWORD P_numHdl,
			HANDLE *P_hdlTab,
			DWORD P_wfmoRet);
#else
   int selectMask( int                 P_maxFd, 
                   fd_set *            P_readMask, 
                   fd_set *            P_writeMask, 
                   fd_set *            P_exceptionMask, 
                   timeval *&          P_timeout);
   // selectMask takes the read/write/exception mask to be used in the HP-UX select(2) 
   // call. It OR's the bits already set in the mask with those required to manage a 
   // connection to the HP OC SS7 Platform. Any of the read/write/exception parameters may 
   // be NULL indicating no mask. "fd_set" is defined in <sys/types.h>. See HP-UX select(2)
   // MAN page. The HP OC ISUP user passes also the 
   // timeout value which will be used in the HP-UX select(2) call. It is compared  
   // with the timeout desired by the HP OC ISUP Library. The HP OC ISUP user can pass    
   // a NULL pointer if no timeout is scheduled. If the value is shorter than the timeout 
   // required by the HP OC ISUP Library, the pointer is not altered. If it is greater,
   // the pointer is changed to point to the HP OC ISUP Library's required timeout.
   //   
   // <{Return Value}>: maximum file descriptor.
   //  
   
   HPAIN::Schedulable::Work handler( int        P_numFd,
                                     fd_set *   P_readMask,
                                     fd_set *   P_writeMask,
                                     fd_set *   P_exceptionMask);
   // The handler method services all the active connections to HP OC SS7 Platform. It 
   // manages the internal HP OC SS7 High Availability mechanisms. It should be called after 
   // every HP-UX select(2) made by the user. Parameters are the select return value and 
   // the select masks for read/write/exception. The other bits masks which are not used 
   // by the HP OC ISUP user are left unchanged. It may occur that after a return from 
   // handler, none of the connections require servicing. This is the case when internal  
   // timeouts or messages are received.
   //   
   // <{Return Value}>: number of work unit necessary to perform all the work.
   // 
   
#endif /* :_WIN32 */

   HPAIN::Schedulable::Work doWork( HPAIN::Schedulable::Work P_work);
   // This method must be called after the "handler" call, as it involves the result of 
   // this call, meaning the amount of work to be done (number of active connections ). 
   // P_work is the bandwith the user assigns to this task, knowing what is necessary
   // to perform the complete reception of the messages waiting to be received.
   // The doWork call does not distinguish between IsupSMProbe or IsupBPProbe.
   // It calls the different IsupSMProbe(s) or IsupBPProbe(s) in order to process the   
   // ISUP messages waiting to be received on the IPC connection. During the doWork call,
   // the activityCB (callback) function of the user is called for each Probe, indicating
   // the number of ISUP primitive indications (or ISUP messages, for IsupBPProbe) waiting 
   // to be received. The activityObject methods do not implement the reception of the 
   // primitives/messages, but just store the information passed by the Probe.
   //   
   //  <{Return Value}>: number a work unit necessary to perform the remaining work.
   //

   HPAIN::Uint32 getNumberOfCircuit();
   // This method allows the application to know the number of circuits which
   // have been configured in the configuration file (isup.conf).
   //
   //  <{Return Value}>: the number of circuits configured.
   //
   

   ISUP::InfoStatus whichMsgSet(const char* P_className,
                                ISUP::PointCode P_Dpc,
                                ISUP::MsgSetID& P_msgSetId);
   // This method asks for the message set identifier which describes the syntax
   // used by the messages exchanged with the DPC <{P_Dpc}>. This syntax has been
   // post compiled by the HP OC ISUP Message Compiler and its related metadata
   // has been integrated in this library. 
   // On completion, an identifier is returned in the parameter <{P_msgSetId}>
   // which should be used in subsequent message customization management calls.
   // If new messages have been added to this message set, a specific call
   // to <{installMsg()}> should be made to include them in the message 
   // classes manipulated by HP OC ISUP API.


   ISUP::InfoStatus whichMsgSet(const char* P_msgSetName,
                                ISUP::MsgSetID& P_msgSetId);
   // This method asks for the message set identifier which is associated with
   // the name <{P_msgSetName}>.
   // On completion, an identifier is returned in the parameter <{P_msgSetId}>
   // which should be used in subsequent message customization management calls
   // If new messages have been added to this message set, a specific call
   // to <{installMsg()}> should be made to include them in the message 
   // classes manipulated by HP OC ISUP API.

   ISUP::InfoStatus installMsg(const char *P_msgName,
                               ISUP::MsgSetID P_msgSetId,
                               ISUP::MsgID& P_msgId);
   // This method installs the ISUP message named by <{P_msgName}> within the set 
   // of messages identified by <{P_msgSetId}> which should be a valid identifier 
   // returned by <{whichMsgSet()}>. Only the non standard messages (as 
   // defined in (union ANSI + ITU)) should be installed.
   // On completion, a message identifier is returned in  the parameter <{P_msgId}>
   // and should be used in subsequent calls to manage message customizing.
   // After this call completes, only the standard parameters defined in 
   // (union ANSI + ITU) are installed.
   // If new parameters have been introduced in this message, a specific call 
   // to <{installParm()}> in each derived class (<{IsupIam}>, <{IsupAnm}> etc)
   // should be made.
   // This method initializes some variables in the <{IsupUserMsg}> class.
   //
   // <{Return Status}>
   //  NO_ERROR
   //  NO_MORE_MEMORY     - instantiation failed.
   //  INIT_FAILURE       - primitive called before initialisation.
   //  INVALID_SET_NAME   - invalid message set name in Data Base.
   //  INVALID_SET_ID     - invalid provided message set identifier.
   //  TOO_MANY_SET       - too many specified message set.
   //  INVALID_MSG_NAME   - invalid provided message name.
   //  INVALID_MSG_ID     - invalid provided message identifier.
   //  TOO_MANY_MSG       - too many specified messages.
   //  INVALID_PARM_NAME  - invalid provided parameter name.
   //  TOO_MANY_PARM      - too many specified parameters.
   //  INVALID_MSG        - message already supported for that message 
   //                       set.
   //  INVALID_SPEC       - ASN.1 description is invalid.
   //  INVALID_DPC        - specified DPC not found in Data Base.
   //  INVALID_CLASS_NAME - specified class name not found in Data Base.
   //  INVALID_PARM       - parameter already supported for that message.
   //  INTERNAL_ERROR
   //

   void setTraceOn();
   // This method activates the trace during the message encoding/decoding.

   void setTraceOff();
   // This method disables the trace during the message encoding/decoding.

	static IsupProbe* getProbe (ISUP::PointCode P_pointCode);
	// this method return a pointer to the probe that manages the connection
   // with the Stack that has LPC = P_pointCode 

   // 
   // = PARAMETERS
   // = BEGIN<INDENT>
   //	<{ISUP::MsgSetID}> - identify set of messages and state-machines used.
   //
   //	<{IsupSMProbe::ActivityObject}>  - HP OC ISUP user's IsupSMProbe 
   //					   callback function.
   //
   //	<{IsupBPProbe::ActivityObject}>  - HP OC ISUP user's IsupBPProbe
   //					   callback function.  
   //
   //	<{fd_set}>		         - file descriptor set (cf sys/types.h).
   //
   //
   //	<{HPAIN::schedulable::Work}>     - UNLIMITED, URGENT, NONE, or positive value.
   //
   // = END<INDENT>

 private:

   // THE unique pointer to the singleton manager 
   static IsupMgr       *theMgrObject;

   // static variable to use with the SS7_ifselectmask and SS7_ifcnxhandler
   static int cnxArray[MAX_PROBE_NUMBER];
   static int cnxActiveNumber;
   #ifdef _WIN32
   static int maskTab[MAX_PROBE_NUMBER];
   #endif /* _WIN32 */

   // created and deleted via init and destroy methods.
   IsupMgr() {};
   virtual ~IsupMgr() {};

   // no copies and assigment operators
   IsupMgr(const IsupMgr&);
   IsupMgr& operator= (const IsupMgr&);

//START DYNAMIC CONFIG
	IsupNavigator *myNavigator;
	HPAIN::Boolean reloadFlag;
	HPAIN::Boolean dumpFlag;
	HPAIN::Boolean reportOnReload;
	HPAIN::Uint32  reloadSignal;
	HPAIN::Uint32  applicationId;
	HPAIN::Boolean reloadPerformed;
	HPAIN::Boolean dumpPerformed;
	HPAIN::Boolean reloadDumpFail;
	static HPAIN::Boolean CicDistributedState;

//USL&STL-Start
#if !defined(__GNUG__) && (__cplusplus < 199707L)
     List_of_p<ISUP::dpcAddress> *dpcsRemovedList;
     List_of_p<ISUP::cicRangeAddress> *cicsRemovedList;
     List_of_p<ISUP::dpcInfo> *dpcsAddedList;
     List_of_p<ISUP::cicsInfo> *cicsAddedList;
     List_of_p<ISUP::cicsInfo> *cicsModifiedList;
#else
	list<ISUP::dpcAddress*> *dpcsRemovedList;
	list<ISUP::cicRangeAddress*> *cicsRemovedList;
	list<ISUP::dpcInfo*> *dpcsAddedList;
	list<ISUP::cicsInfo*> *cicsAddedList;
	list<ISUP::cicsInfo*> *cicsModifiedList;
#endif
//USL&STL-End

	static void setReportOnReload(HPAIN::Boolean P_yesOrNo);
	// This method is called by the IsupNavigator to set the reportOnReload variable
		
	static void setReloadSignal(HPAIN::Uint32 P_signal);
	// This method is called by the IsupNavigator to set the reloadSignal variable
	// and to call the signal method to perform a reload at the signal receipt
		
	static HPAIN::Boolean getReportOnReload();
	// This method return the reportOnReload flag value

	static void endReload(HPAIN::Uint32 P_errors,HPAIN::Boolean P_configError);
	// This method is called by the IsupNavigator when a reload is finished.

	static void endDump(HPAIN::Uint32 P_errors);
	// This method is called by the IsupNavigator when a dump is finished.

	static void dpcRemoved (ISUP::dpcAddress *P_addr);
	// This method add the removed dpc in the dcpsRemoved list

	static void cicsRemoved (ISUP::cicRangeAddress *P_addr);
	// this method add the removed cics range in the cicsRemoved list 
	
	static void dpcAdded (ISUP::dpcInfo *P_info);
	// this method add the added dpc in the dpcsAdded list
	
	static void cicsAdded (ISUP::cicsInfo *P_info);
	// this method add the added cic range in the cicsAdded list 
	
	static void cicsModified (ISUP::cicsInfo *P_info);
	// this method add the modified cics range to the cicsModified list

	friend class IsupNavigator;
	friend class IsupAP;
	friend class IsupMtpAP;
	friend class IsupSccpAP;
//END DYNAMIC CONFIG

   // method to register a probe for future scheduling
   friend class IsupSMProbeImpl;
   friend class IsupBPProbeImpl;
   
   void registerProbeCnx(HPAIN::Int32 P_probeId, HPAIN::Int32 P_cnxId);
   void declareProbeActive(HPAIN::Int32 P_probeId);
   HPAIN::Boolean localEventFlag;
   struct timeval getWorkUnitDuration();
   // This method allows the application to know what is the average time of the work
   // unit, that means the time to process a ISUP message coming from the network.
   //
   //  <{Return Value}>: the average time in seconds and microseconds.
   //


   // this object allows the IsupMgr to manage all the different probes.
#if ((__cplusplus >= 199707L) || (defined(_WIN32))) || defined(__GNUG__)
  // aCC
   class ProbeLookUp {
   public:
#endif // __cplusplus >= 199707L

   class ProbeDescriptor {
         public:
           IsupProbe *      pointer;
           HPAIN::Int32     cnxId;
           HPAIN::Boolean   activeFlag;
           HPAIN::Uint32    nbOfMsg;
         };
#if !defined(__GNUG__) && ((!defined( _WIN32)) && (__cplusplus<199707L))
   class ProbeLookUp {
#endif /*!_WIN32 */

         public:
           ProbeDescriptor probeTable[MAX_PROBE_NUMBER];
           
           void init();
           HPAIN::Int32 findEmptySlot();
           ProbeDescriptor * getProbeFromCnxId(HPAIN::Int32 P_cnxId); 
           ProbeDescriptor * getProbeFromProbeId(HPAIN::Int32 P_probeId);
           void setProbeDescriptor( HPAIN::Int32 P_probeId, IsupProbe * P_probe);
           void setProbeCnxId( HPAIN::Int32 P_probeId, HPAIN::Int32 P_cnxId);
			  HPAIN::Boolean areProbesActives();
          };

   ProbeLookUp theProbeLookUp;

   class DoWorkSample {
         public:
           HPAIN::Uint32 elapsedTime;
           HPAIN::Uint32 nbOfMsgProcessed;
        };
   static DoWorkSample * doWorkStatisticTable;
   
   // = EXAMPLE
   //
   // This example shows how to create an IsupSMProbe:
   //
   // = BEGIN<CODE>
   // 
   //  // ..... definition of the user callback class:
   //  // class myProbeCB: public IsupSMProbe::ActivityObject {
   //  //      public:
   //  //        void recvActivity(IsupSMProbe * aProbe, int nbMsg);
   //  //        void sendpossible(IsupSMProbe * aProbe);
   //  //  }
   // 
   //  // myProbeCB::recvActivity(IsupProbe * aProbe, int nbMsg)
   //  //    {
   //  //     ..... implementation of the recvActivity function.
   //  //    }
   //
   //  IsupMgr *                        L_myIsupMgr;
   //  IsupSMProbe *                    L_myIsupProbe;
   //  HPAIN::Schedulable::Work *       L_IsupWork;
   //  fd_set *                         L_rm;
   //  fd_set *                         L_wm; 
   //  struct timeval                   L_time; 
   //  struct timeval *                 L_timeout = &L_time;
   //  int                              L_maxFd; 
   //  int                              L_numFd;
   //  ISUP::MsgSetID                   L_msgSetId;
   //  ISUP::OpenStatus                 L_Ostatus;
   //  ISUP::CreateStatus               L_Cstatus;
   //  ISUP::InitStatus                 L_Istatus;
   //
   //  myCBobj = NEW myProbeCB();
   // 
   //  // initialize the Isup Manager
   //  L_Istatus = IsupMgr::init(L_myIsupMgr);
   //  if(!L_Istatus.isOK())
   //    { ... handle error ...}
   //
   //  // load the ISUP version ANSI_88
   //  L_msgSetId = IsupInfoMgr::installMsgSet("ANSI_88");
   //
   //  // create a normal probe using this ANSI version
   //  L_Cstatus = IsupMgr::createSMProbe("SS7_Stack", myCBobj, &L_myIsupProbe);
   //  if(!L_Cstatus.isOK())
   //    { ... handle error ...}
   // 
   //  // open a connection with the SS7 process
   //  L_Ostatus = L_myIsupProbe->open();
   //  if(!L_Ostatus.isOK())
   //    { ... handle error ...}
   //
   //  // the probe being ready, the user can send and receive Isup primitives
   //
   //  // scheduling
   //  L_time.tv_sec = 2;  
   //  L_time.tv_usec = 0;
   //
   //  FD_ZERO(&rm);
   //  FD_ZERO(&wm);
   //  
   //  L_maxFd = IsupMgr->selectMask(0, rm, wm, 0, L_timeout);
   //  if(( L_numFd = select(L_maxFd, rm, wm, 0, L_timeout))== -1)
   //      printf("select failed");
   //
   //  L_IsupWork = IsupMgr->handler(L_numFd, rm, wm, 0);
   //  L_IsupWork = IsupMgr->doWork(HPAIN::Schedulable::UNLIMITED);
   //
   //  // ... receive the pending primitives
   //
   // = END<CODE>
   //
   // = SEE ALSO
   // = BEGIN<INDENT>
   //     IsupProbe, IsupSMProbe, IsupBPProbe, IsupInfoMgr, IsupMsg, select(2),
   // 	  IsupIntro, IsupMsgIntro, IsupCustom
   // = END<INDENT> 
   
      
};	// IsupMgr

#endif           /* ISUP_MGR_H */
