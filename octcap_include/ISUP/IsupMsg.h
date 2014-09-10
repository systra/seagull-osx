//------------------------------------------------------------------------------
//
//                               MODULE   IsupMsg.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupMsg.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupMsg.h $
//            $Revision: 2.37 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPMSG_H
#define ISUPMSG_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#include <IsupCommon.h>
#include <BF_LRMsgScp.h>

class BF_CoDec;
class BF_TRMsg;
class BF_MDMsgElem;
class BF_MDMsg;
class BF_status;
class IsupSMProbeImpl;
class IsupBPProbeImpl;
class IsupInspector;
class IsupRange;
class IsupANSI92Strategy;
class IsupITU88Strategy;
class IsupInfoMgr;
class IsupInspector;
class IsupRange;
class IsupBPStrategy;
class IsupFsm;

#ifdef ISUP_A92
class IsupANSI92Strategy;
class ANSI92_CRI;
class ANSI92_CRS;
class ANSI92_CRR;
class ANSI92_GBUR;
class ANSI92_BLR;
class ANSI92_CGRR;
class ANSI92_CQR;
class ANSI92_GBUS;
class ANSI92_BLS;
class ANSI92_CGRS;
class ANSI92_CPC;
class ANSI92_CRO;
class ANSI92_DCO;
class ANSI92_CCO;
class ANSI92_ACR;
class ANSI92_CVTR; //CVTS SM Implementation
class ANSI92_CVTS; //CVTS SM Implementation
#endif /* ISUP_A92 */
#ifdef ISUP_I88
class IsupITU88Strategy;
class IsupITU88Fsm;
class ITU88_CRS;
class ITU88_CRR;
class ITU88_GBUR;
class ITU88_BLR;
class ITU88_BLS;
class ITU88_MGBR;
class ITU88_MGBS;
class ITU88_HGBR;
class ITU88_HGBS;
class ITU88_CGRR;
class ITU88_CGRS;
class ITU88_CQR;
class ITU88_ACR;
class ITU88_CPC;
class ITU88_CCI;
class ITU88_CRCR;
class ITU88_CRCS;

class ITU97_SSC;
class ITU97_CPC;
class ITU97_CRCR;
class ITU97_CGRR;
class ITU97_MGBR;
class ITU97_MGBS;
class ITU97_HGBS;
class ITU97_HGBR;
class ITU97_BLS;
class ITU97_CGRS;
#endif /* ISUP_I88 */

class IsupMsg : public BF_LRMsgScp
//
// = TITLE
// C++ encapsulation of an ISUP Message (<{VERSION 2.0}>)
// 
// = DESCRIPTION
// This message class is a base class for all ISUP messages classes manipulated by 
// the ISUP API.
// The error handling relies on a stored <{ISUP::MsgStatus}> class object,
// and is used when associated methods are called. This class 
// allows for stack errors, and has a convenient signature for all accessors
// which are not expected to fail. The base implementation of the
// <{ISUP::MsgStatus}> class encapsulates a single error. <{It is the user's  
// responsibility to define a derived class to implement a stack mechanism}>.
{
public:

   enum Type
   { 
      ACM,     // Address Complete Message
      ANM,     // Answer
      BLA,     // Blocking Acknowledgement
      BLO,     // Blocking
      CCR,     // Continuity check Request
      CFN,     // Confusion
      CGB,     // Circuit Group Blocking
      CGBA,    // Circuit Group Blocking Acknowledgement
      CGU,     // Circuit Group Unblocking
      CGUA,    // Circuit Group Unblocking Acknowledgement
      CMC,     // Call Modification Completed               (for ITU only)
      CMR,     // Call Modification Request                 (for ITU only)
      CMRJ,    // Call Modification Reject                  (for ITU only)
      CON,     // Connect                                   (for ITU only)
      COT,     // Continuity                  
      CPG,     // Call Progress
      CRG,     // Charge Information                        (for ITU only)
      CQM,     // Circuit Group Query
      CQR,     // Circuit Group Query Response
      CRA,     // Circuit Reservation Acknowledgement       (for ANSI only)
      CRM,     // Circuit Reservation                       (for ANSI only)
      CVR,     // Circuit Validation Response               (for ANSI only)
      CVT,     // Circuit Validation Test                   (for ANSI only)
      DRS,     // Delayed Release                           (for ITU only)
      EXM,     // Exit
      FAA,     // Facility Accepted                         (for ITU only)
      FAR,     // Facility Rejected                         (for ITU only)
      FOT,     // Forward Transfer
      FRJ,     // Facility Reject                           (for ITU only)
      GRA,     // Circuit Group Reset Acknowledgement
      GRS,     // Circuit Group Reset
      IAM,     // Initial Address
      INF,     // Information
      INR,     // Information Request                       (for ITU only)
      LPA,     // Loop Back Acknowledgement
      OLM,     // Overload                                  (for ITU only)
      REL,     // Release                  
      RES,     // Resume
      RLC,     // Release Complete
      RSC,     // Reset Circuit 
      SAM,     // Subsequent Address                        (for ITU only)
      SUS,     // Suspend
      UBA,     // Unblocking Acknowledgement
      UBL,     // Unblocking
      UCIC,    // Unequipped Circuit Identification Code
      FAC,     // Facility message
      USR,     // User To User Information                  (for ITU only)
      USERDEF, // Defined by user
      SGM,     // Simple Segmentation Message               (for ITU 97 only)
      NRM,     // Network Resource Mgt Message              (for ITU 97 only)
      LOP,     // (for ITU 97 only) // HL
      UPT,     // User Part Test                            (for ITU 97 only)
      UPA,     // User Part Available                       (for ITU 97 only)
      UKWN,    // Unknown Message                           (for ITU 97 only)
      PRG,     // Progress Message                          (for TTC3 only)
      ALT,     // ALERT Message                             (for TTC3 only)
      CHG,      //Charging Message                           (for TTC3 only)
      APM,      //Application TransportMessage               (for SPR98 only)
      PRI,      //Pre-Release indormation                    (for SPR98 only)
      ITX,      //Charge Unit                                (for SPR98/SSUR only)
      TXA,      //Charging Acknowledgement                   (for SPR98/SSUR only)
      CHT,      //tarification change                        (For SSUR only)
      TAX,       //Taxation                                  (For SSUR only)
      MPM,       //Meter Pulse Message                       (For CHINA only)
      CCL,       //Calling Party Clear                       (For CHINA only)
      OPR        //Operator Message                          (For CHINA only)
   };

   // = CONSTRUCTION
   
   virtual ~IsupMsg();
   // This destructor deletes a ISUP message. 

#ifdef OBJ_POOL

   // redefined operators new() and delete() take and
   // remove from the associated object pool
//   void * operator new(size_t s);
//   void operator delete(void * o);
#if (__cplusplus >= 199707L && !defined(__HPACC_NOEH)) || defined(__GNUG__)
   // aCC Version
      void *operator new(size_t s, const nothrow_t &P_nothrow) throw();
      void operator delete(void *o) throw();
#else // __HPACC_NOEH
      void *operator new(size_t s);
      void operator delete(void *o);
#endif //__HPACC_NOEH


#endif

   // = ACCESS
   
   virtual Type getMsgType() const;
   // Returns the message type (IAM, ANM..., UserDef) of the current message.

   virtual void setMsgType(IsupMsg::Type P_type);
   // Sets the message type (IAM, ANM..., UserDef) of the current message.

   virtual const BF_MDMsg* getRelatedMessage() const;
   // Returns the pointer to the associated BF message.

   IsupMsg(const BF_MDMsg* P_msg);
   // Instantiate an IsupMsg object from a BF_MDMsg

   
   // = GENERIC ACCESSORS
   // These methods provide access to parameters installed by
   // the <{installParm()}> method. 
   // NOTE : all possible variants of <{[g|s]etValue()}>
   // which have been implemented by the MFVO engine should be supported.
   // \fP
   
   virtual void getValue(ISUP::ParmID P_parmId, HPAIN::Int32& P_iVal,
			 ISUP::MsgStatus& P_status) const;
   //  Retrieves a scalar value of an installed parameter.
   
   virtual void setValue(ISUP::ParmID P_parmId, HPAIN::Int32 P_iVal,
			 ISUP::MsgStatus& P_status) ;
   // Sets a scalar value of an installed parameter.
   
   virtual void getValue(ISUP::ParmID P_parmId, ISUP::ParmValue*& P_sVal,
			 ISUP::MsgStatus& P_status) const;
   // Retrieves a string of an installed parameter. The user
   // must delete the provided <{ISUP::ParmValue}> instance.
   
   virtual void setValue(ISUP::ParmID P_parmId, ISUP::ParmValue& P_sVal,
			 ISUP::MsgStatus& P_status) ;
   // Sets a string of an installed parameter. This method does not
   // delete the provided <{ISUP::ParmValue}> instance.
   
   virtual HPAIN::Boolean isParmPresent(ISUP::ParmID P_parmId,
					ISUP::MsgStatus& P_status) const;
   // Returns TRUE if the optional parameter of an installed parameter in 
   // message is present.
   
   
   // = ERROR HANDLING
   
   virtual HPAIN::Boolean isObjectValid(ISUP::MsgStatus& P_status) const;
   // This method returns a validity indicator value.
   
   // = STREAMS HANDLING
   
   friend ostream& operator<< (ostream& P_os, const IsupMsg& P_msg);
   // Do a pretty output on <{ostream}> of a reference to a <{IsupMsg}> instance
   
   friend ostream& operator<< (ostream& P_os, const IsupMsg* P_msg);
   // Do a pretty output on <{ostream}> of a pointer to a <{IsupMsg}> instance
   
#ifdef ISUP_A92
   virtual unsigned char getMsgPriority();
   // Get MTP priority for the message (ANSI-95 only)
#endif

   void encode(ISUP::MsgStatus& P_status);
   // Allows encoding of an ISUP message for sending in MFVO format.

   void decode(ISUP::MsgStatus& P_status);
   // Allows decoding from MFVO format of a received ISUP message.

   void setPDU(const void* P_PDU, HPAIN::Uint32 P_length,
		       ISUP::MsgStatus& P_status);
   // Allows initialisation of the transfer representation of an ISUP message.

   void getPDU(void* P_PDU, HPAIN::Uint32 * P_length,
		       ISUP::MsgStatus& P_status);
   // Allows access to the transfer representation of an ISUP message.
   
   virtual IsupMsg *segment(HPAIN::Uint32 P_maxSegSize, ISUP::MsgStatus& P_status);
   // Segments the original message. If successful, an SGM is returned, else NULL
   // is returned.

   virtual HPAIN::Boolean isSegmented(ISUP::MsgStatus& P_status);
   // Returns TRUE if the message has the SSI bits set to 1. Else FALSE is
   // returned.

   virtual void assemble(IsupMsg*& P_sgm, ISUP::MsgStatus& P_status);
   // Copies the parameters from an SGM message to the current
   // message (if it supports the same parameters).

   HPAIN::Uint32 length() const;
   // Returns the length of the encoded message representation

   void   setTagValue(HPAIN::Byte P_tag);
   // Sets the Tag value of the message (used only for the generic UKWN message)

   HPAIN::Byte   getTagValue();
   // Gets the Tag value of the message (used only for the generic UKWN message)
   
protected :
   
   // = TO BE USED ONLY BY THE CLASS AND DERIVATED CLASSES
   
   IsupMsg(Type P_type, const BF_MDMsg* P_msg);
   // This constructor is protected to prevent users from calling it
   
   IsupMsg(const IsupMsg& P_from, const BF_MDMsg* P_msg);
   // This constructor is protected to prevent users from calling it
   
   void coreGetValue(const BF_MDMsgElem* P_msgElemId,
		     HPAIN::Int32& P_iVal,
		     ISUP::MsgStatus& P_status) const;
   // Retrieves the scalar value of an installed parameter.
   
   void coreSetValue(const BF_MDMsgElem* P_msgElemId, 
		     HPAIN::Int32 P_iVal,
		     ISUP::MsgStatus& P_status);
   // Sets the scalar value of an installed parameter.
   
   void coreGetValue(const BF_MDMsgElem* P_msgElemId,
		     const ISUP::ParmValue* & P_sVal,
		     ISUP::MsgStatus& P_status) const;
   // Retrieves the string of an installed parameter.
   
   void coreSetValue(const BF_MDMsgElem* P_msgElemId,
		     ISUP::ParmValue& P_iVal,
		     ISUP::MsgStatus& P_status);
   // Sets the string of an installed parameter.
   
   void coreSetAbsent(const BF_MDMsgElem* P_msgElemId,
				ISUP::MsgStatus& P_status);
   // This method allows to set an optional parameter as absent.

   HPAIN::Boolean coreIsPresent(const BF_MDMsgElem* P_msgElemId,
				ISUP::MsgStatus& P_status) const;
   // Sets the string of an installed parameter.
   
   void setStatus(ISUP::MsgStatus& P_status, 
		  ISUP::MsgStatus::Status P_error) const;
   // Pushes an error to the error stack.
   
   HPAIN::Boolean isPam() const;
   // Returns an indicator denoting if the message is a PAM

   virtual HPAIN::Uint32 resize(HPAIN::Uint32 P_length, ISUP::MsgStatus& P_status);
   // if msg length is higher than P_length, remove userToUserInformation 
   // parameter(if exist) and return the new length if it is lower than P_length.
   // If msg cannot be resized, -1 is returned and P_status is set to INVALID_LENGTH.

   // = CLASS DATA 
   
   Type instanceMsgType;
   // Type related to one instance of a Isup message.
   
   BF_status* instanceBFstatus;
   // BF Status related to one instance of a Isup message.
   
   HPAIN::Boolean instanceIsPam;
   // Flag related to one instance of a Isup message denoting a PAM.
   
   ISUP::MsgStatus* instanceStatus;
   // Status stack related to one instance of a Isup message.
   
   HPAIN::Boolean instanceValidFlag;
   // Validity flag related to one instance of a Isup message.
   
   BF_TRMsg* instanceTrfRep;
   // Transfer representation related to one instance of a Isup message.

   ISUP::MsgSetID instanceMsgSet;
   // Message set related to one instance of an Isup message.

   HPAIN::Byte    tagValue;
   // Real tag of the message
   
private:

   // = PROTECTION FROM OUTSIDE
   
   // These methods are private to prevent any initialisation from any user.
   // Only the friend classes are to initialize or end.
   // \fP
   
   IsupMsg();
   // The constructor is protected to prevent users from calling it
   
   IsupMsg(const IsupMsg& P_from);
   // The copy constructor is protected to prevent users from calling it
   
   const IsupMsg& operator=(const IsupMsg& P_from);
   // The assignment is protected to prevent users from calling it
   
   static IsupMsg* createMsg(ISUP::MsgSetID P_msgSetId, const void* P_PDU,
			     HPAIN::Uint32 P_length, ISUP::MsgStatus& P_status);
   // This method allows to get an IsupMsg derived class.
   
   void deleteTrfRep();
   // Allows to delete the transfert representation of an ISUP message.

   static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
   // Ask to initialise the IsupMsg derived classes static data 
   
   static void end();
   // Ask to end with the IsupMsg derived classes static data 
   
   // = STANDARD MESSAGE MANAGEMENT
   
#ifdef _WIN32
public:
#endif /* _WIN32 */

#if __cplusplus >= 199707L || defined(__GNUG__)
  // aCC compiler
public:
#endif // __cplusplus >= 199707L

   static HPAIN::Uint32 getNumOfStdMsg();
   // Ask the number of standard implemented messages. 

#ifdef _WIN32
private:
#endif /* _WIN32 */

#if __cplusplus >= 199707L || defined(__GNUG__)
  // aCC compiler
private:
#endif // __cplusplus >= 199707L
   
   static ISUP::InfoStatus installPamMsg(ISUP::MsgSetID P_msgSetId,
					 HPAIN::Int32& P_tag);
   // Ask install the Pass Along Message which is belonging to
   // message set <{P_msgSetId}>.
   
   static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId);
   // Ask to install the standard messages which are belonging to
   // message set <{P_msgSetId}>.
   
   // = READ / WRITE MESSAGE
   
   virtual void write(const void* P_PDU, HPAIN::Uint32 P_length,
		      HPAIN::Uint32 P_offset, ISUP::MsgStatus& P_status);
   // This method allows to write into an encoded ISUP message representation.
   
   virtual void read(void* P_PDU, HPAIN::Uint32& P_length,
		     ISUP::MsgStatus& P_status);
   // This method allows to read an encoded ISUP message representation.
   
   virtual void resetIndex(ISUP::MsgStatus& P_status);
   // this method allows to reset the read/write index of an encoded ISUP
   // message representation

   // = MESSAGE INFORMATION
   
   void isPam(HPAIN::Boolean);
   // This method set the indicator denoting if the message is a PAM
   
   
   HPAIN::Boolean isEncoded() const;
   // This method returns an indicator denoting if the message has been encoded
   

   ISUP::InfoStatus range(ISUP::ParmValue*& P_parm) const;
   // This method returns a range value (array of Cic) related to message
   
   
   // = FRIENDSHIP
   
   friend class IsupInfoMgr;
   // Because class IsupInfoMgr uses methods init(), end(), installStdMsg()
   
   friend class IsupInspector;
   // Because class IsupInspector uses methods createMsg(), read() and write()
   
   friend class IsupRange;
   //because class IsupRange uses method range()

#ifdef ISUP_A92
   
   friend class IsupANSI92Strategy;
   // Because class IsupANSI92Strategy uses method isPam(), createMsg(), length()

   friend class IsupBPStrategy;
   // Because class IsupBPStrategy uses method isPam(), createMsg()
   
   friend class IsupSMProbeImpl;
   // Because class IsupSMProbeImpl uses method read()
   
   friend class IsupBPProbeImpl;
   // Because class IsupBPProbeImpl uses method read()
   
   friend class IsupFsm;
   // Because class IsupFsm uses method encode()

   friend class ANSI92_CRI;
   // Because class ANSI92_CRI uses method encode()
   
   friend class ANSI92_CRS;
   // Because class ANSI92_CRS uses method encode()
   
   friend class ANSI92_CRR;
   // Because class ANSI92_CRR uses method encode()

   friend class ANSI92_GBUR;
   // Because class ANSI92_GBUR uses method encode()

   friend class ANSI92_BLR;
   // Because class ANSI92_BLR uses method encode()

   friend class ANSI92_CGRR;
   // Because class ANSI92_CGRR uses method encode()

   friend class ANSI92_CQR;
   // Because class ANSI92_CQR uses method encode()

// START ANSI_CQS
   friend class ANSI92_CQS;
   // Because class ANSI92_CQR uses method encode()
// END ANSI_CQS

   friend class ANSI92_GBUS;
   // Because class ANSI92_GBUS uses method encode()

   friend class ANSI92_BLS;
   // Because class ANSI92_BLS uses method encode()

   friend class ANSI92_CGRS;
   // Because class ANSI92_CGRS uses method encode()

   friend class ANSI92_CPC;
   // Because class ANSI92_CPC uses method encode()

   friend class ANSI92_CRO;
   // Because class ANSI92_CRO uses method encode()

   friend class ANSI92_DCO;
   // Because class ANSI92_DCO uses method encode()

   friend class ANSI92_CCO;
   // Because class ANSI92_CCO uses method encode()

   friend class ANSI92_ACR;
   // Because class ANSI92_ACR uses method encode()

   friend class ANSI92_CVTS;    //CVTS SM Implementation
   // Because class ANSI92_CVTS uses method write(), resetIndex()

#endif

#ifdef ISUP_I88
   friend class IsupITU88Strategy;
   // Because class IsupITU88Strategy uses method isPam(), createMsg(), length()

   friend class IsupFsm;
   // Because class IsupFsm uses method encode()

   friend class IsupITU88Fsm;
   // Because class IsupFsm uses method encode()

   friend class IsupBPStrategy;
   // Because class IsupBPStrategy uses method isPam(), createMsg()

   friend class IsupSMProbeImpl;
   // Because class IsupSMProbeImpl uses method read()

   friend class IsupBPProbeImpl;
   // Because class IsupBPProbeImpl uses method read()

   friend class ITU88_CRS;
   // Because class ITU88_CRS uses method encode()

   friend class ITU88_CRR;
   // Because class ITU88_CRR uses method encode()

   friend class ITU88_GBUR;
   // Because class ITU88_GBUR uses method encode()

   friend class ITU88_BLR;
   // Because class ITU88_BLR uses method encode()

   friend class ITU88_BLS;
   // Because class ITU88_BLS uses method encode()
   
   friend class ITU88_MGBR;
   // Because class ITU88_MGBR uses method encode()

   friend class ITU88_MGBS;
   // Because class ITU88_MGBS uses method encode()
   
   friend class ITU88_HGBR;
   // Because class ITU88_HGBR uses method encode()

   friend class ITU88_HGBS;
   // Because class ITU88_HGBS uses method encode()

   friend class ITU88_CGRR;
   // Because class ITU88_CGRR uses method encode()

   friend class ITU88_CGRS;
   // Because class ITU88_CGRS uses method encode()

   friend class ITU88_CQR;
   // Because class ITU88_CQR uses method encode()

   friend class ITU88_ACR;
   // Because class ITU88_ACR uses method encode()

   friend class ITU88_CPC;
   // Because class ITU88_CPC uses method encode()

   friend class ITU88_CCI;
   // Because class ITU88_CCI uses method encode()

   friend class ITU88_CRCR;
   // Because class ITU88_CRCR uses method encode()

   friend class ITU88_CRCS;
   // Because class ITU88_CRCS uses method encode()

   friend class ITU97_SSC;
   // Because class ITU97_SSC uses method encode()

   friend class ITU97_CPC;
   // Because class ITU97_CPC uses method encode()

   friend class ITU97_CRCR;
   // Because class ITU97_CRCR uses method encode()

   friend class ITU97_CGRR;
   // Because class ITU97_CGRR uses method encode()

   friend class ITU97_MGBR;
   // Because class ITU97_MGBR uses method encode()

   friend class ITU97_MGBS;
   // Because class ITU97_MGBS uses method encode()

   friend class ITU97_HGBS;
   // Because class ITU97_HGBS uses method encode()

   friend class ITU97_HGBR;
   // Because class ITU97_HGBR uses method encode()

   friend class ITU97_BLS;
   // Because class ITU97_BLS uses method encode()

   friend class ITU97_CGRS;
   // Because class ITU97_CGRS uses method encode()
#endif
   

};

ostream& operator<< (ostream& P_os, IsupMsg::Type P_kind);
// Do a pretty print on <{ostream}> of a IsupMsg::Type variable.

#endif // ISUPMSG_H
//
// = EXAMPLE
//
//  This example shows how a new message set can be installed.
//
// = BEGIN<CODE>
//
//  ISUP::InfoStatus install;
//  ISUP::PointCode theDpc = 12;
//  ISUP::MsgSetID msgSetId;
//  ISUP::MsgStatus status;
//  IsupMgr* instanceMgr;
//  ISUP::ParmID parmId;
//
//  IsupMgr::init(instanceMgr);
//
//  install = instanceMgr->whichMsgSet(theDpc, msgSetId); 
//  if (!install.isOk()) exit(1);
//
//  // IsupIam is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupIam::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install.isOk()) exit(1);
// 
//  IsupIam* msgPtr = NEW IsupIam(msgSetId);
//  ISUP::ParmValue* parmPtr = NEW ISUP::ParmValue();
//
//  // Do the usual work on IAM...
//  msgPtr->natureOfCnxIndicators(parmPtr->assign("\0x7e\0x23", 2), status);
//  if (!status.isOk()) { ... }
//
//  // ... and access the new parm NEW_IAM_PARM
//  msgPtr->setValue(L_parmId, parmPtr->assign((HPAIN::Byte)0x7e), status);
//  if (!status.isOk()) { ... }
//
// = END<CODE>
//
// = NOTES
//  None.
//
// = SEE ALSO
//  IsupMgr class, IsupInfoMgr class
