// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupInf.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupInf.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupInf.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPINF_H
#define ISUPINF_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupInf : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP INF (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[INF message]>.
{
public:

  // = CONSTRUCTION

  IsupInf(ISUP::MsgSetID);
  // This constructor builds an empty INF message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the INF as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupInf::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the INF message.

  virtual ~IsupInf();
  // This destructor deletes a INF message. 

  static IsupInf* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupInf}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupInf(const IsupInf& P_from);
  // The copy constructor provides a way to construct a INF message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an INF message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupInf}>
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
  // Accessors provide a generic facility for accessing INF parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
  // = informationIndicators

  ISUP::ParmValue* informationIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{informationIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* informationIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{informationIndicators}>
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

  IsupInf* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessTransport}>
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

  IsupInf* businessGroup(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupInf* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
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

  IsupInf* callingPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupInf* callingPartysCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingPartysCategory}>
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

  IsupInf* chargeNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargeNumber}>
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

  IsupInf* connectionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectionRequest}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = originatingLineInformation

  HPAIN::Boolean originatingLineInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{originatingLineInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  originatingLineInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{originatingLineInformation}> as absent
  // in the message. 

  ISUP::ParmValue* originatingLineInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{originatingLineInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* originatingLineInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originatingLineInformation}>
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

  IsupInf* redirectingNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupInf* redirectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionInformation}>
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

  IsupInf* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupInf* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupInf* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
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

  IsupInf* unRecognizedParameter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{unRecognizedParameter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = nationalInformationIndicator

  HPAIN::Boolean nationalInformationIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{nationalInformationIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  nationalInformationIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{nationalInformationIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* nationalInformationIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{nationalInformationIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* nationalInformationIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{nationalInformationIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callingSubBasicServiceMarks

  HPAIN::Boolean callingSubBasicServiceMarksIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callingSubBasicServiceMarks}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callingSubBasicServiceMarksSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callingSubBasicServiceMarks}> as absent
  // in the message. 

  ISUP::ParmValue* callingSubBasicServiceMarks(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callingSubBasicServiceMarks}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* callingSubBasicServiceMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingSubBasicServiceMarks}>
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

  IsupInf* calledSubBasicServiceMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledSubBasicServiceMarks}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callingSubsOriginatingFacilityMarks

  HPAIN::Boolean callingSubsOriginatingFacilityMarksIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callingSubsOriginatingFacilityMarks}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  callingSubsOriginatingFacilityMarksSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{callingSubsOriginatingFacilityMarks}> as absent
  // in the message. 

  ISUP::ParmValue* callingSubsOriginatingFacilityMarks(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callingSubsOriginatingFacilityMarks}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* callingSubsOriginatingFacilityMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingSubsOriginatingFacilityMarks}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledSubsTerminatingFacilityMarks

  HPAIN::Boolean calledSubsTerminatingFacilityMarksIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledSubsTerminatingFacilityMarks}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  calledSubsTerminatingFacilityMarksSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{calledSubsTerminatingFacilityMarks}> as absent
  // in the message. 

  ISUP::ParmValue* calledSubsTerminatingFacilityMarks(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledSubsTerminatingFacilityMarks}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupInf* calledSubsTerminatingFacilityMarks(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledSubsTerminatingFacilityMarks}>
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

  friend ostream& operator<< (ostream& P_os, const IsupInf& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupInf}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupInf* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupInf}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupInf& operator=(const IsupInf&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupInf static data 

  static void end();
  // Ask to end with the IsupInf static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message INF which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the INF message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new INF messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the INF messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPINF_H
//
// = EXAMPLE
//
// This example shows how a message INF can be accessed.
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
//  // IsupInf is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupInf::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupInf* msgPtr = NEW IsupInf(msgSetId);
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
