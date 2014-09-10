// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupUkwn.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupUkwn.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupUkwn.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPUKWN_H
#define ISUPUKWN_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupUkwn : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP UKWN (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[UKWN message]>.
{
public:

  // = CONSTRUCTION

  IsupUkwn(ISUP::MsgSetID);
  // This constructor builds an empty UKWN message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the UKWN as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupUkwn::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the UKWN message.

  virtual ~IsupUkwn();
  // This destructor deletes a UKWN message. 

  static IsupUkwn* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupUkwn}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupUkwn(const IsupUkwn& P_from);
  // The copy constructor provides a way to construct a UKWN message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an UKWN message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupUkwn}>
  // message class. An identifier is returned in parameter <{P_parmId}> which 
  // should be used for any further calls to the specific methods <{getValue()}> 
  // and <{setValue()}>. The result of the method may be obtained by accessing
  // the returned <{ISUP::InfoStatus}> class instance pointer. 
  
  // = MFVO ENCODING/DECODING 
  // See the method definitions in the <{IsupMsg}> abstract class.

  // = GENERIC ACCESSORS

  // These methods provide access to parameters installed by the
  // installParm method.
  // NOTE : all possible variants of <{[g|s]etBasicValue()}> that the
  // MFVO engine implements should be supported. 
  // \fP

  virtual void getValue(ISUP::ParmID P_parmId, HPAIN::Int32& P_iVal,
			ISUP::MsgStatus& P_status) const;
  // Retrieves a scalar value of an installed parameter in a
  // received message.

  virtual void setValue(ISUP::ParmID P_parmId, HPAIN::Int32 P_iVal,
			ISUP::MsgStatus& P_status);
  // Sets a scalar value of an installed parameter in a 
  // message to be sent.

  virtual void getValue(ISUP::ParmID P_parmId, ISUP::ParmValue*& P_sVal,
			ISUP::MsgStatus& P_status) const;
  // Retrieves a ISUP::ParmValue* of an installed parameter 
  // in a received message. 
  // The user must delete the <{ISUP::ParmValue}> object instance.

  virtual void setValue(ISUP::ParmID P_parmId, ISUP::ParmValue& P_sVal,
			ISUP::MsgStatus& P_status);
  // Sets a ISUP::ParmValue* of an installed parameter in a 
  // message to be sent. This methods does not delete the provided 
  // <{ISUP::ParmValue}> instance.

  virtual HPAIN::Boolean isParmPresent(ISUP::ParmID P_parmId,
				       ISUP::MsgStatus& P_status) const;
  // Returns TRUE if the optional parameter of an installed parameter in 
  // message is present.

  // = SPECIFIC ACCESSORS
  // Accessors provide a generic facility for accessing UKWN parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
  // = CCSS

  HPAIN::Boolean CCSSIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{CCSS}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  CCSSSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{CCSS}> as absent
  // in the message. 

  ISUP::ParmValue* CCSS(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{CCSS}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* CCSS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{CCSS}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = CUGinterlockCode

  HPAIN::Boolean CUGinterlockCodeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{CUGinterlockCode}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  CUGinterlockCodeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{CUGinterlockCode}> as absent
  // in the message. 

  ISUP::ParmValue* CUGinterlockCode(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{CUGinterlockCode}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* CUGinterlockCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{CUGinterlockCode}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = MCIDRequestIndicator

  HPAIN::Boolean MCIDRequestIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{MCIDRequestIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  MCIDRequestIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{MCIDRequestIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* MCIDRequestIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{MCIDRequestIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* MCIDRequestIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{MCIDRequestIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = MCIDResponseIndicator

  HPAIN::Boolean MCIDResponseIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{MCIDResponseIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  MCIDResponseIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{MCIDResponseIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* MCIDResponseIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{MCIDResponseIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* MCIDResponseIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{MCIDResponseIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = MLPPPrecedence

  HPAIN::Boolean MLPPPrecedenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{MLPPPrecedence}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  MLPPPrecedenceSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{MLPPPrecedence}> as absent
  // in the message. 

  ISUP::ParmValue* MLPPPrecedence(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{MLPPPrecedence}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* MLPPPrecedence(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{MLPPPrecedence}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = SCFId

  HPAIN::Boolean SCFIdIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{SCFId}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  SCFIdSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{SCFId}> as absent
  // in the message. 

  ISUP::ParmValue* SCFId(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{SCFId}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* SCFId(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{SCFId}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = accessDeliveryInformation

  HPAIN::Boolean accessDeliveryInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{accessDeliveryInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  accessDeliveryInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{accessDeliveryInformation}> as absent
  // in the message. 

  ISUP::ParmValue* accessDeliveryInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{accessDeliveryInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* accessDeliveryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessDeliveryInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = accessTransport

  HPAIN::Boolean accessTransportIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{accessTransport}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  accessTransportSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{accessTransport}> as absent
  // in the message. 

  ISUP::ParmValue* accessTransport(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{accessTransport}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessTransport}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = applicationTransport

  HPAIN::Boolean applicationTransportIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{applicationTransport}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  applicationTransportSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{applicationTransport}> as absent
  // in the message. 

  ISUP::ParmValue* applicationTransport(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{applicationTransport}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* applicationTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{applicationTransport}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = automCongestionLevel

  HPAIN::Boolean automCongestionLevelIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{automCongestionLevel}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  automCongestionLevelSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{automCongestionLevel}> as absent
  // in the message. 

  ISUP::ParmValue* automCongestionLevel(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{automCongestionLevel}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* automCongestionLevel(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{automCongestionLevel}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = backwardCallIndicators

  HPAIN::Boolean backwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{backwardCallIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  backwardCallIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{backwardCallIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* backwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{backwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* backwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = backwardGVNS

  HPAIN::Boolean backwardGVNSIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{backwardGVNS}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  backwardGVNSSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{backwardGVNS}> as absent
  // in the message. 

  ISUP::ParmValue* backwardGVNS(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{backwardGVNS}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* backwardGVNS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardGVNS}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callDiversionInformation

  HPAIN::Boolean callDiversionInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callDiversionInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callDiversionInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callDiversionInformation}> as absent
  // in the message. 

  ISUP::ParmValue* callDiversionInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callDiversionInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callDiversionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callDiversionInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callDiversionTreatmentIndicator

  HPAIN::Boolean callDiversionTreatmentIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callDiversionTreatmentIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callDiversionTreatmentIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callDiversionTreatmentIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* callDiversionTreatmentIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callDiversionTreatmentIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callDiversionTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callDiversionTreatmentIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callHistoryInformation

  HPAIN::Boolean callHistoryInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callHistoryInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callHistoryInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callHistoryInformation}> as absent
  // in the message. 

  ISUP::ParmValue* callHistoryInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callHistoryInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callHistoryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callHistoryInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callOfferingTreatmentIndicator

  HPAIN::Boolean callOfferingTreatmentIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callOfferingTreatmentIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callOfferingTreatmentIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callOfferingTreatmentIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* callOfferingTreatmentIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callOfferingTreatmentIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callOfferingTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callOfferingTreatmentIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callReference

  HPAIN::Boolean callReferenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callReference}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callReferenceSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callReference}> as absent
  // in the message. 

  ISUP::ParmValue* callReference(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callReference}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callTransferNumber

  HPAIN::Boolean callTransferNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callTransferNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callTransferNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callTransferNumber}> as absent
  // in the message. 

  ISUP::ParmValue* callTransferNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callTransferNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callTransferNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callTransferNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callTransferReference

  HPAIN::Boolean callTransferReferenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callTransferReference}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callTransferReferenceSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callTransferReference}> as absent
  // in the message. 

  ISUP::ParmValue* callTransferReference(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callTransferReference}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callTransferReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callTransferReference}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledDirectoryNumber

  HPAIN::Boolean calledDirectoryNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledDirectoryNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  calledDirectoryNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{calledDirectoryNumber}> as absent
  // in the message. 

  ISUP::ParmValue* calledDirectoryNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledDirectoryNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* calledDirectoryNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledDirectoryNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledINNumber

  HPAIN::Boolean calledINNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledINNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  calledINNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{calledINNumber}> as absent
  // in the message. 

  ISUP::ParmValue* calledINNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledINNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* calledINNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledINNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledPartyNumber

  HPAIN::Boolean calledPartyNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledPartyNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  calledPartyNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{calledPartyNumber}> as absent
  // in the message. 

  ISUP::ParmValue* calledPartyNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledPartyNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* calledPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledPartyNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callingPartyNumber

  HPAIN::Boolean callingPartyNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callingPartyNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callingPartyNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callingPartyNumber}> as absent
  // in the message. 

  ISUP::ParmValue* callingPartyNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callingPartyNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callingPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingPartyNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callingPartysCategory

  HPAIN::Boolean callingPartysCategoryIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callingPartysCategory}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callingPartysCategorySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callingPartysCategory}> as absent
  // in the message. 

  ISUP::ParmValue* callingPartysCategory(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callingPartysCategory}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* callingPartysCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingPartysCategory}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = causeIndicators

  HPAIN::Boolean causeIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{causeIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  causeIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{causeIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* causeIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{causeIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* causeIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = ccnrPossibleIndicator

  HPAIN::Boolean ccnrPossibleIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{ccnrPossibleIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  ccnrPossibleIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{ccnrPossibleIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* ccnrPossibleIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{ccnrPossibleIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* ccnrPossibleIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{ccnrPossibleIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargedPartyIdentification

  HPAIN::Boolean chargedPartyIdentificationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargedPartyIdentification}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargedPartyIdentificationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargedPartyIdentification}> as absent
  // in the message. 

  ISUP::ParmValue* chargedPartyIdentification(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargedPartyIdentification}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargedPartyIdentification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargedPartyIdentification}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargeUnitNumber

  HPAIN::Boolean chargeUnitNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargeUnitNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargeUnitNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargeUnitNumber}> as absent
  // in the message. 

  ISUP::ParmValue* chargeUnitNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargeUnitNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargeUnitNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargeUnitNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = cirGroupSupervMessageTypeInd

  HPAIN::Boolean cirGroupSupervMessageTypeIndIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{cirGroupSupervMessageTypeInd}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  cirGroupSupervMessageTypeIndSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{cirGroupSupervMessageTypeInd}> as absent
  // in the message. 

  ISUP::ParmValue* cirGroupSupervMessageTypeInd(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{cirGroupSupervMessageTypeInd}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* cirGroupSupervMessageTypeInd(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{cirGroupSupervMessageTypeInd}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = circuitAssignmentMap

  HPAIN::Boolean circuitAssignmentMapIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{circuitAssignmentMap}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  circuitAssignmentMapSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{circuitAssignmentMap}> as absent
  // in the message. 

  ISUP::ParmValue* circuitAssignmentMap(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{circuitAssignmentMap}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* circuitAssignmentMap(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{circuitAssignmentMap}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = circuitStateIndicator

  HPAIN::Boolean circuitStateIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{circuitStateIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  circuitStateIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{circuitStateIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* circuitStateIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{circuitStateIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* circuitStateIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{circuitStateIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = collectCallRequest

  HPAIN::Boolean collectCallRequestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{collectCallRequest}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  collectCallRequestSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{collectCallRequest}> as absent
  // in the message. 

  ISUP::ParmValue* collectCallRequest(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{collectCallRequest}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* collectCallRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{collectCallRequest}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = conferenceTreatmentIndicator

  HPAIN::Boolean conferenceTreatmentIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{conferenceTreatmentIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  conferenceTreatmentIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{conferenceTreatmentIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* conferenceTreatmentIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{conferenceTreatmentIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* conferenceTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{conferenceTreatmentIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = connectedNumber

  HPAIN::Boolean connectedNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{connectedNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  connectedNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{connectedNumber}> as absent
  // in the message. 

  ISUP::ParmValue* connectedNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{connectedNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* connectedNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectedNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = connectionRequest

  HPAIN::Boolean connectionRequestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{connectionRequest}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  connectionRequestSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{connectionRequest}> as absent
  // in the message. 

  ISUP::ParmValue* connectionRequest(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{connectionRequest}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* connectionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectionRequest}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = continuityIndicators

  HPAIN::Boolean continuityIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{continuityIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  continuityIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{continuityIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* continuityIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{continuityIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* continuityIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{continuityIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = correlationId

  HPAIN::Boolean correlationIdIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{correlationId}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  correlationIdSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{correlationId}> as absent
  // in the message. 

  ISUP::ParmValue* correlationId(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{correlationId}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* correlationId(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{correlationId}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = displayInformation

  HPAIN::Boolean displayInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{displayInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  displayInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{displayInformation}> as absent
  // in the message. 

  ISUP::ParmValue* displayInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{displayInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* displayInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{displayInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = echoControlInformation

  HPAIN::Boolean echoControlInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{echoControlInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  echoControlInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{echoControlInformation}> as absent
  // in the message. 

  ISUP::ParmValue* echoControlInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{echoControlInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* echoControlInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{echoControlInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = eventInformation

  HPAIN::Boolean eventInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{eventInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  eventInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{eventInformation}> as absent
  // in the message. 

  ISUP::ParmValue* eventInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{eventInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* eventInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{eventInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = facilityIndicator

  HPAIN::Boolean facilityIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{facilityIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  facilityIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{facilityIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* facilityIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{facilityIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* facilityIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{facilityIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = forwardCallIndicators

  HPAIN::Boolean forwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{forwardCallIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  forwardCallIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{forwardCallIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* forwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{forwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* forwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{forwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = forwardGVNS

  HPAIN::Boolean forwardGVNSIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{forwardGVNS}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  forwardGVNSSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{forwardGVNS}> as absent
  // in the message. 

  ISUP::ParmValue* forwardGVNS(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{forwardGVNS}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* forwardGVNS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{forwardGVNS}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = genericDigits

  HPAIN::Boolean genericDigitsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericDigits}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  genericDigitsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{genericDigits}> as absent
  // in the message. 

  ISUP::ParmValue* genericDigits(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{genericDigits}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* genericDigits(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericDigits}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = genericNotification

  HPAIN::Boolean genericNotificationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericNotification}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  genericNotificationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{genericNotification}> as absent
  // in the message. 

  ISUP::ParmValue* genericNotification(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{genericNotification}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* genericNotification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNotification}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = genericNumber

  HPAIN::Boolean genericNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  genericNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{genericNumber}> as absent
  // in the message. 

  ISUP::ParmValue* genericNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{genericNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* genericNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = hopCounter

  HPAIN::Boolean hopCounterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{hopCounter}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  hopCounterSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{hopCounter}> as absent
  // in the message. 

  ISUP::ParmValue* hopCounter(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{hopCounter}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* hopCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{hopCounter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = informationIndicators

  HPAIN::Boolean informationIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{informationIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  informationIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{informationIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* informationIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{informationIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* informationIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{informationIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = informationRequestIndicators

  HPAIN::Boolean informationRequestIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{informationRequestIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  informationRequestIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{informationRequestIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* informationRequestIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{informationRequestIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* informationRequestIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{informationRequestIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = locationNumber

  HPAIN::Boolean locationNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{locationNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  locationNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{locationNumber}> as absent
  // in the message. 

  ISUP::ParmValue* locationNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{locationNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* locationNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{locationNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = loopPreventionIndicator

  HPAIN::Boolean loopPreventionIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{loopPreventionIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  loopPreventionIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{loopPreventionIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* loopPreventionIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{loopPreventionIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* loopPreventionIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{loopPreventionIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = messageCompatibility

  HPAIN::Boolean messageCompatibilityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{messageCompatibility}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  messageCompatibilitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{messageCompatibility}> as absent
  // in the message. 

  ISUP::ParmValue* messageCompatibility(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{messageCompatibility}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* messageCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{messageCompatibility}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = messageNumber

  HPAIN::Boolean messageNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{messageNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  messageNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{messageNumber}> as absent
  // in the message. 

  ISUP::ParmValue* messageNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{messageNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* messageNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{messageNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = natureOfCnxIndicators

  HPAIN::Boolean natureOfCnxIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{natureOfCnxIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  natureOfCnxIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{natureOfCnxIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* natureOfCnxIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{natureOfCnxIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* natureOfCnxIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{natureOfCnxIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = networkManagementControl

  HPAIN::Boolean networkManagementControlIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{networkManagementControl}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  networkManagementControlSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{networkManagementControl}> as absent
  // in the message. 

  ISUP::ParmValue* networkManagementControl(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{networkManagementControl}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* networkManagementControl(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkManagementControl}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = networkSpecificFacility

  HPAIN::Boolean networkSpecificFacilityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{networkSpecificFacility}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  networkSpecificFacilitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{networkSpecificFacility}> as absent
  // in the message. 

  ISUP::ParmValue* networkSpecificFacility(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{networkSpecificFacility}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = optionBackwardCallIndicators

  HPAIN::Boolean optionBackwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{optionBackwardCallIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  optionBackwardCallIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{optionBackwardCallIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* optionBackwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{optionBackwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* optionBackwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{optionBackwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = optionForwardCallIndicators

  HPAIN::Boolean optionForwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{optionForwardCallIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  optionForwardCallIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{optionForwardCallIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* optionForwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{optionForwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* optionForwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{optionForwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = originalCalledNumber

  HPAIN::Boolean originalCalledNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{originalCalledNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  originalCalledNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{originalCalledNumber}> as absent
  // in the message. 

  ISUP::ParmValue* originalCalledNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{originalCalledNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* originalCalledNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originalCalledNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = originationISCPointCode

  HPAIN::Boolean originationISCPointCodeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{originationISCPointCode}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  originationISCPointCodeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{originationISCPointCode}> as absent
  // in the message. 

  ISUP::ParmValue* originationISCPointCode(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{originationISCPointCode}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* originationISCPointCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originationISCPointCode}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = parameterCompatibility

  HPAIN::Boolean parameterCompatibilityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{parameterCompatibility}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  parameterCompatibilitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{parameterCompatibility}> as absent
  // in the message. 

  ISUP::ParmValue* parameterCompatibility(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{parameterCompatibility}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = propagationDelayCounter

  HPAIN::Boolean propagationDelayCounterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{propagationDelayCounter}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  propagationDelayCounterSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{propagationDelayCounter}> as absent
  // in the message. 

  ISUP::ParmValue* propagationDelayCounter(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{propagationDelayCounter}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* propagationDelayCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{propagationDelayCounter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = rangeAndStatus

  HPAIN::Boolean rangeAndStatusIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{rangeAndStatus}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  rangeAndStatusSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{rangeAndStatus}> as absent
  // in the message. 

  ISUP::ParmValue* rangeAndStatus(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{rangeAndStatus}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* rangeAndStatus(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{rangeAndStatus}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectingNumber

  HPAIN::Boolean redirectingNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectingNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectingNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectingNumber}> as absent
  // in the message. 

  ISUP::ParmValue* redirectingNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectingNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectingNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectingNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionInformation

  HPAIN::Boolean redirectionInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectionInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectionInformation}> as absent
  // in the message. 

  ISUP::ParmValue* redirectionInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectionInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionNumber

  HPAIN::Boolean redirectionNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectionNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectionNumber}> as absent
  // in the message. 

  ISUP::ParmValue* redirectionNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectionNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectionNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionNumberRestriction

  HPAIN::Boolean redirectionNumberRestrictionIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionNumberRestriction}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectionNumberRestrictionSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectionNumberRestriction}> as absent
  // in the message. 

  ISUP::ParmValue* redirectionNumberRestriction(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectionNumberRestriction}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectionNumberRestriction(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumberRestriction}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = remoteOperations

  HPAIN::Boolean remoteOperationsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{remoteOperations}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  remoteOperationsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{remoteOperations}> as absent
  // in the message. 

  ISUP::ParmValue* remoteOperations(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{remoteOperations}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{remoteOperations}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = serviceActivation

  HPAIN::Boolean serviceActivationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{serviceActivation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  serviceActivationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{serviceActivation}> as absent
  // in the message. 

  ISUP::ParmValue* serviceActivation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{serviceActivation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* serviceActivation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = signallingPointCode

  HPAIN::Boolean signallingPointCodeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{signallingPointCode}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  signallingPointCodeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{signallingPointCode}> as absent
  // in the message. 

  ISUP::ParmValue* signallingPointCode(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{signallingPointCode}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* signallingPointCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{signallingPointCode}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = subsequentNumber

  HPAIN::Boolean subsequentNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{subsequentNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  subsequentNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{subsequentNumber}> as absent
  // in the message. 

  ISUP::ParmValue* subsequentNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{subsequentNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* subsequentNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{subsequentNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = suspendResumeIndicators

  HPAIN::Boolean suspendResumeIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{suspendResumeIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  suspendResumeIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{suspendResumeIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* suspendResumeIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{suspendResumeIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* suspendResumeIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{suspendResumeIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transMediumRequirePrime

  HPAIN::Boolean transMediumRequirePrimeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transMediumRequirePrime}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  transMediumRequirePrimeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{transMediumRequirePrime}> as absent
  // in the message. 

  ISUP::ParmValue* transMediumRequirePrime(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transMediumRequirePrime}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* transMediumRequirePrime(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transMediumRequirePrime}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transitNetworkSelection

  HPAIN::Boolean transitNetworkSelectionIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transitNetworkSelection}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  transitNetworkSelectionSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{transitNetworkSelection}> as absent
  // in the message. 

  ISUP::ParmValue* transitNetworkSelection(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transitNetworkSelection}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* transitNetworkSelection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transitNetworkSelection}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transmissionMediumRequire

  HPAIN::Boolean transmissionMediumRequireIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transmissionMediumRequire}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  transmissionMediumRequireSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{transmissionMediumRequire}> as absent
  // in the message. 

  ISUP::ParmValue* transmissionMediumRequire(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transmissionMediumRequire}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* transmissionMediumRequire(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transmissionMediumRequire}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transmissionMediumUsed

  HPAIN::Boolean transmissionMediumUsedIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transmissionMediumUsed}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  transmissionMediumUsedSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{transmissionMediumUsed}> as absent
  // in the message. 

  ISUP::ParmValue* transmissionMediumUsed(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transmissionMediumUsed}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* transmissionMediumUsed(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transmissionMediumUsed}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = uidActionIndicator

  HPAIN::Boolean uidActionIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{uidActionIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  uidActionIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{uidActionIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* uidActionIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{uidActionIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* uidActionIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{uidActionIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = uidCapabilityIndicator

  HPAIN::Boolean uidCapabilityIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{uidCapabilityIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  uidCapabilityIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{uidCapabilityIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* uidCapabilityIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{uidCapabilityIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* uidCapabilityIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{uidCapabilityIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = userServiceInformation

  HPAIN::Boolean userServiceInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userServiceInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  userServiceInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{userServiceInformation}> as absent
  // in the message. 

  ISUP::ParmValue* userServiceInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{userServiceInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* userServiceInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userServiceInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = userServiceInformationPrime

  HPAIN::Boolean userServiceInformationPrimeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userServiceInformationPrime}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  userServiceInformationPrimeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{userServiceInformationPrime}> as absent
  // in the message. 

  ISUP::ParmValue* userServiceInformationPrime(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{userServiceInformationPrime}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* userServiceInformationPrime(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userServiceInformationPrime}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = userTeleserviceInformation

  HPAIN::Boolean userTeleserviceInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userTeleserviceInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  userTeleserviceInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{userTeleserviceInformation}> as absent
  // in the message. 

  ISUP::ParmValue* userTeleserviceInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{userTeleserviceInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* userTeleserviceInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userTeleserviceInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = userToUserIndicators

  HPAIN::Boolean userToUserIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userToUserIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  userToUserIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{userToUserIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* userToUserIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{userToUserIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = userToUserInformation

  HPAIN::Boolean userToUserInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userToUserInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  userToUserInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{userToUserInformation}> as absent
  // in the message. 

  ISUP::ParmValue* userToUserInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{userToUserInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = CCBS

  HPAIN::Boolean CCBSIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{CCBS}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  CCBSSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{CCBS}> as absent
  // in the message. 

  ISUP::ParmValue* CCBS(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{CCBS}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* CCBS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{CCBS}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = freephoneIndicators

  HPAIN::Boolean freephoneIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{freephoneIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  freephoneIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{freephoneIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* freephoneIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{freephoneIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* freephoneIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{freephoneIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = networkFunctionType

  HPAIN::Boolean networkFunctionTypeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{networkFunctionType}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  networkFunctionTypeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{networkFunctionType}> as absent
  // in the message. 

  ISUP::ParmValue* networkFunctionType(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{networkFunctionType}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* networkFunctionType(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkFunctionType}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargingAreaInformation

  HPAIN::Boolean chargingAreaInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargingAreaInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargingAreaInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargingAreaInformation}> as absent
  // in the message. 

  ISUP::ParmValue* chargingAreaInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargingAreaInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargingAreaInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingAreaInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargingInformation

  HPAIN::Boolean chargingInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargingInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargingInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargingInformation}> as absent
  // in the message. 

  ISUP::ParmValue* chargingInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargingInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargingInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingInformation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargingInformationType

  HPAIN::Boolean chargingInformationTypeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargingInformationType}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargingInformationTypeSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargingInformationType}> as absent
  // in the message. 

  ISUP::ParmValue* chargingInformationType(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargingInformationType}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargingInformationType(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingInformationType}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = mobileCommEndInfoTrf

  HPAIN::Boolean mobileCommEndInfoTrfIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{mobileCommEndInfoTrf}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  mobileCommEndInfoTrfSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{mobileCommEndInfoTrf}> as absent
  // in the message. 

  ISUP::ParmValue* mobileCommEndInfoTrf(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{mobileCommEndInfoTrf}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* mobileCommEndInfoTrf(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{mobileCommEndInfoTrf}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = mobileCommCallRef

  HPAIN::Boolean mobileCommCallRefIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{mobileCommCallRef}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  mobileCommCallRefSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{mobileCommCallRef}> as absent
  // in the message. 

  ISUP::ParmValue* mobileCommCallRef(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{mobileCommCallRef}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* mobileCommCallRef(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{mobileCommCallRef}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = additionalUserCategory

  HPAIN::Boolean additionalUserCategoryIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{additionalUserCategory}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  additionalUserCategorySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{additionalUserCategory}> as absent
  // in the message. 

  ISUP::ParmValue* additionalUserCategory(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{additionalUserCategory}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* additionalUserCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{additionalUserCategory}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargingInformationDelay

  HPAIN::Boolean chargingInformationDelayIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargingInformationDelay}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargingInformationDelaySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargingInformationDelay}> as absent
  // in the message. 

  ISUP::ParmValue* chargingInformationDelay(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargingInformationDelay}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* chargingInformationDelay(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingInformationDelay}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = operatorInformationTransfer

  HPAIN::Boolean operatorInformationTransferIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{operatorInformationTransfer}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  operatorInformationTransferSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{operatorInformationTransfer}> as absent
  // in the message. 

  ISUP::ParmValue* operatorInformationTransfer(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{operatorInformationTransfer}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* operatorInformationTransfer(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{operatorInformationTransfer}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = isdnUserIndication

  HPAIN::Boolean isdnUserIndicationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{isdnUserIndication}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  isdnUserIndicationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{isdnUserIndication}> as absent
  // in the message. 

  ISUP::ParmValue* isdnUserIndication(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{isdnUserIndication}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* isdnUserIndication(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{isdnUserIndication}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = contractorNumber

  HPAIN::Boolean contractorNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{contractorNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  contractorNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{contractorNumber}> as absent
  // in the message. 

  ISUP::ParmValue* contractorNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{contractorNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* contractorNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{contractorNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = phsTerminalIdentification

  HPAIN::Boolean phsTerminalIdentificationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{phsTerminalIdentification}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  phsTerminalIdentificationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{phsTerminalIdentification}> as absent
  // in the message. 

  ISUP::ParmValue* phsTerminalIdentification(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{phsTerminalIdentification}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* phsTerminalIdentification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{phsTerminalIdentification}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = causeForCallerNumPresRest

  HPAIN::Boolean causeForCallerNumPresRestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{causeForCallerNumPresRest}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  causeForCallerNumPresRestSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{causeForCallerNumPresRest}> as absent
  // in the message. 

  ISUP::ParmValue* causeForCallerNumPresRest(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{causeForCallerNumPresRest}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* causeForCallerNumPresRest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeForCallerNumPresRest}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = causeForRedirection

  HPAIN::Boolean causeForRedirectionIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{causeForRedirection}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  causeForRedirectionSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{causeForRedirection}> as absent
  // in the message. 

  ISUP::ParmValue* causeForRedirection(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{causeForRedirection}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* causeForRedirection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeForRedirection}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionCapability

  HPAIN::Boolean redirectionCapabilityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionCapability}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectionCapabilitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectionCapability}> as absent
  // in the message. 

  ISUP::ParmValue* redirectionCapability(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectionCapability}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectionCapability(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionCapability}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionCounter

  HPAIN::Boolean redirectionCounterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionCounter}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectionCounterSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectionCounter}> as absent
  // in the message. 

  ISUP::ParmValue* redirectionCounter(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectionCounter}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupUkwn* redirectionCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionCounter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // begin_resize
#ifdef ISUP_I88
  HPAIN::Uint32 resize(HPAIN::Uint32 P_length, ISUP::MsgStatus& P_status);
  // remove userToUserInformation parameter (if exist) and return the new length 
  // of the message. P_length is the original length of the message.
  // This method applied on an encoded or a decoded message since message length
  // is given as parameter.
#endif
  
  // end_seg
  // begin_trailer
  

  // = ERROR HANDLING
  // See the definition of the concerning methods in its abstract class.
  // \fP

  // = STREAMS HANDLING

  friend ostream& operator<< (ostream& P_os, const IsupUkwn& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupUkwn}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupUkwn* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupUkwn}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupUkwn& operator=(const IsupUkwn&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupUkwn static data 

  static void end();
  // Ask to end with the IsupUkwn static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message UKWN which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the UKWN message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new UKWN messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the UKWN messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPUKWN_H
//
// = EXAMPLE
//
// This example shows how a message UKWN can be accessed.
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
//  install = instanceMgr->whichMsgSet(ClassName, theDpc, msgSetId); 
//  if (!install->isOk()) exit(1);
//
//  // IsupUkwn is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupUkwn::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupUkwn* msgPtr = NEW IsupUkwn(msgSetId);
//  ISUP::ParmValue* parmPtr = NEW ISUP::ParmValue();
//
//  msgPtr->setValue(L_parmId, parmPtr->assign((HPAIN::Byte)0x7e), status);
//  // handle error.
//  if (!status->isOk()) { ... }
//  {
//    cout << "Error : " << status->getStatus();
//  }
//
// = END<CODE>
//
// = NOTE
//  Uses the BF underlying sub-system.
//
// = SEE ALSO
//  IsupMgr class, IsupInfoMgr class, IsupMsg class 
// end_trailer
