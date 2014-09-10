// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupAnm.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupAnm.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupAnm.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPANM_H
#define ISUPANM_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupAnm : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP ANM (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[ANM message]>.
{
public:

  // = CONSTRUCTION

  IsupAnm(ISUP::MsgSetID);
  // This constructor builds an empty ANM message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the ANM as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupAnm::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the ANM message.

  virtual ~IsupAnm();
  // This destructor deletes a ANM message. 

  static IsupAnm* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupAnm}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupAnm(const IsupAnm& P_from);
  // The copy constructor provides a way to construct a ANM message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an ANM message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupAnm}>
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
  // Accessors provide a generic facility for accessing ANM parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
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

  IsupAnm* applicationTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{applicationTransport}>
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

  IsupAnm* backwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = businessGroup

  HPAIN::Boolean businessGroupIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{businessGroup}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  businessGroupSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{businessGroup}> as absent
  // in the message. 

  ISUP::ParmValue* businessGroup(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{businessGroup}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* businessGroup(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{businessGroup}>
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

  IsupAnm* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
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

  IsupAnm* connectedNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupAnm* connectionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectionRequest}>
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

  IsupAnm* informationIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{informationIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = networkTransport

  HPAIN::Boolean networkTransportIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{networkTransport}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  networkTransportSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{networkTransport}> as absent
  // in the message. 

  ISUP::ParmValue* networkTransport(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{networkTransport}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* networkTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkTransport}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = notificationIndicator

  HPAIN::Boolean notificationIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{notificationIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  notificationIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{notificationIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* notificationIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{notificationIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* notificationIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{notificationIndicator}>
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

  IsupAnm* optionBackwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{optionBackwardCallIndicators}>
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

  IsupAnm* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserIndicators}>
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

  IsupAnm* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{remoteOperations}>
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

  IsupAnm* transmissionMediumUsed(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transmissionMediumUsed}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = isdnUserIndicator

  HPAIN::Boolean isdnUserIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{isdnUserIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  isdnUserIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{isdnUserIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* isdnUserIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{isdnUserIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* isdnUserIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{isdnUserIndicator}>
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

  IsupAnm* accessDeliveryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessDeliveryInformation}>
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

  IsupAnm* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupAnm* backwardGVNS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardGVNS}>
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

  IsupAnm* callHistoryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callHistoryInformation}>
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

  IsupAnm* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
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

  IsupAnm* redirectionNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumber}>
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

  IsupAnm* serviceActivation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = serviceActivation1995

  HPAIN::Boolean serviceActivation1995IsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{serviceActivation1995}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  serviceActivation1995SetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{serviceActivation1995}> as absent
  // in the message. 

  ISUP::ParmValue* serviceActivation1995(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{serviceActivation1995}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* serviceActivation1995(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation1995}>
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

  IsupAnm* echoControlInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{echoControlInformation}>
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

  IsupAnm* redirectionNumberRestriction(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumberRestriction}>
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

  IsupAnm* displayInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{displayInformation}>
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

  IsupAnm* isdnUserIndication(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{isdnUserIndication}>
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

  IsupAnm* chargingAreaInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingAreaInformation}>
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

  IsupAnm* mobileCommEndInfoTrf(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{mobileCommEndInfoTrf}>
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

  IsupAnm* additionalUserCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{additionalUserCategory}>
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

  IsupAnm* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserInformation}>
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

  IsupAnm* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessTransport}>
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

  IsupAnm* genericNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNumber}>
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

  IsupAnm* genericNotification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNotification}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = unRecognizedParameter

  HPAIN::Boolean unRecognizedParameterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{unRecognizedParameter}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  unRecognizedParameterSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{unRecognizedParameter}> as absent
  // in the message. 

  ISUP::ParmValue* unRecognizedParameter(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{unRecognizedParameter}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* unRecognizedParameter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{unRecognizedParameter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledSubBasicServiceMarks

  HPAIN::Boolean calledSubBasicServiceMarksIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledSubBasicServiceMarks}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  calledSubBasicServiceMarksSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{calledSubBasicServiceMarks}> as absent
  // in the message. 

  ISUP::ParmValue* calledSubBasicServiceMarks(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledSubBasicServiceMarks}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupAnm* calledSubBasicServiceMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledSubBasicServiceMarks}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // begin_seg
#ifdef ISUP_I88

  // = message segmentation/reassembly methods

  IsupMsg *segment(HPAIN::Uint32 P_maxSegSize, ISUP::MsgStatus& P_status);
  // Segments the message in two parts of P_maxSegSize maximum length.
  // The second part returned as an IsupMsg* is an IsupSgm*.
  // If userToUserInformation parameter exists and does not fit in one of the segments, 
  // it is discarded. If one of the segments is longer than P_maxSegSize, P_status
  // is set to MsgStatus::INVALID_LENGTH and NULL is returned.
  // If succeed, the SSI bit is set to 1 in the first part of the message.
  // This method apply on an already encoded message.

  HPAIN::Boolean isSegmented(ISUP::MsgStatus& P_status);
  // Returns TRUE if the message has the SSI bits set to 1. Else FALSE is
  // returned.

  void assemble(IsupMsg*& P_sgm, ISUP::MsgStatus& P_status);
  // Copy the parameter from an Sgm message in the current
  // message.
#endif

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

  friend ostream& operator<< (ostream& P_os, const IsupAnm& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupAnm}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupAnm* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupAnm}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupAnm& operator=(const IsupAnm&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupAnm static data 

  static void end();
  // Ask to end with the IsupAnm static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message ANM which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the ANM message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new ANM messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the ANM messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPANM_H
//
// = EXAMPLE
//
// This example shows how a message ANM can be accessed.
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
//  // IsupAnm is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupAnm::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupAnm* msgPtr = NEW IsupAnm(msgSetId);
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
