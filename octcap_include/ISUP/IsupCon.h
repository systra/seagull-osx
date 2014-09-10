// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupCon.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupCon.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupCon.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPCON_H
#define ISUPCON_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupCon : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP CON (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[CON message]>.
{
public:

  // = CONSTRUCTION

  IsupCon(ISUP::MsgSetID);
  // This constructor builds an empty CON message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the CON as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupCon::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the CON message.

  virtual ~IsupCon();
  // This destructor deletes a CON message. 

  static IsupCon* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupCon}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupCon(const IsupCon& P_from);
  // The copy constructor provides a way to construct a CON message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an CON message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupCon}>
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
  // Accessors provide a generic facility for accessing CON parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
  // = backwardCallIndicators

  ISUP::ParmValue* backwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{backwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupCon* backwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardCallIndicators}>
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

  IsupCon* applicationTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{applicationTransport}>
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

  IsupCon* optionBackwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{optionBackwardCallIndicators}>
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

  IsupCon* connectedNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectedNumber}>
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

  IsupCon* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
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

  IsupCon* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserIndicators}>
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

  IsupCon* backwardGVNS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{backwardGVNS}>
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

  IsupCon* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
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

  IsupCon* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupCon* transmissionMediumUsed(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transmissionMediumUsed}>
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

  IsupCon* echoControlInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{echoControlInformation}>
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

  IsupCon* accessDeliveryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessDeliveryInformation}>
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

  IsupCon* callHistoryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callHistoryInformation}>
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

  IsupCon* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupCon* redirectionNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupCon* serviceActivation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation}>
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

  IsupCon* redirectionNumberRestriction(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumberRestriction}>
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

  IsupCon* conferenceTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{conferenceTreatmentIndicator}>
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

  IsupCon* networkFunctionType(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkFunctionType}>
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

  IsupCon* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupCon* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupCon* genericNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupCon* genericNotification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNotification}>
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

  IsupCon* calledSubBasicServiceMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  friend ostream& operator<< (ostream& P_os, const IsupCon& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupCon}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupCon* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupCon}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupCon& operator=(const IsupCon&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupCon static data 

  static void end();
  // Ask to end with the IsupCon static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message CON which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the CON message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new CON messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the CON messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPCON_H
//
// = EXAMPLE
//
// This example shows how a message CON can be accessed.
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
//  // IsupCon is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupCon::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupCon* msgPtr = NEW IsupCon(msgSetId);
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
