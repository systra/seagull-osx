// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupRel.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupRel.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupRel.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPREL_H
#define ISUPREL_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupRel : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP REL (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[REL message]>.
{
public:

  // = CONSTRUCTION

  IsupRel(ISUP::MsgSetID);
  // This constructor builds an empty REL message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the REL as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupRel::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the REL message.

  virtual ~IsupRel();
  // This destructor deletes a REL message. 

  static IsupRel* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupRel}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupRel(const IsupRel& P_from);
  // The copy constructor provides a way to construct a REL message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an REL message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupRel}>
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
  // Accessors provide a generic facility for accessing REL parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
  // = causeIndicators

  ISUP::ParmValue* causeIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{causeIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupRel* causeIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeIndicators}>
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

  IsupRel* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessTransport}>
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

  IsupRel* automCongestionLevel(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{automCongestionLevel}>
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

  IsupRel* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = chargeNumber

  HPAIN::Boolean chargeNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{chargeNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  chargeNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{chargeNumber}> as absent
  // in the message. 

  ISUP::ParmValue* chargeNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{chargeNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupRel* chargeNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargeNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = genericAddress

  HPAIN::Boolean genericAddressIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericAddress}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  genericAddressSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{genericAddress}> as absent
  // in the message. 

  ISUP::ParmValue* genericAddress(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{genericAddress}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupRel* genericAddress(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericAddress}>
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

  IsupRel* genericNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNumber}>
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

  IsupRel* redirectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupRel* redirectionNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumber}>
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

  IsupRel* signallingPointCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{signallingPointCode}>
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

  IsupRel* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserInformation}>
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

  IsupRel* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupRel* redirectionNumberRestriction(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionNumberRestriction}>
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

  IsupRel* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
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

  IsupRel* accessDeliveryInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessDeliveryInformation}>
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

  IsupRel* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserIndicators}>
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

  IsupRel* displayInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{displayInformation}>
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

  IsupRel* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{remoteOperations}>
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

  IsupRel* mobileCommEndInfoTrf(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{mobileCommEndInfoTrf}>
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

  IsupRel* causeForRedirection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeForRedirection}>
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

  IsupRel* serviceActivation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupRel* serviceActivation1995(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation1995}>
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

  IsupRel* calledPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledPartyNumber}>
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

  IsupRel* unRecognizedParameter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{unRecognizedParameter}>
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

  friend ostream& operator<< (ostream& P_os, const IsupRel& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupRel}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupRel* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupRel}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupRel& operator=(const IsupRel&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupRel static data 

  static void end();
  // Ask to end with the IsupRel static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message REL which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the REL message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new REL messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the REL messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPREL_H
//
// = EXAMPLE
//
// This example shows how a message REL can be accessed.
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
//  // IsupRel is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupRel::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupRel* msgPtr = NEW IsupRel(msgSetId);
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
