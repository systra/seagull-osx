// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupIam.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupIam.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupIam.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPIAM_H
#define ISUPIAM_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupIam : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP IAM (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[IAM message]>.
{
public:

  // = CONSTRUCTION

  IsupIam(ISUP::MsgSetID);
  // This constructor builds an empty IAM message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the IAM as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupIam::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the IAM message.

  virtual ~IsupIam();
  // This destructor deletes a IAM message. 

  static IsupIam* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupIam}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupIam(const IsupIam& P_from);
  // The copy constructor provides a way to construct a IAM message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an IAM message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupIam}>
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
  // Accessors provide a generic facility for accessing IAM parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
  // = natureOfCnxIndicators

  ISUP::ParmValue* natureOfCnxIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{natureOfCnxIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* natureOfCnxIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{natureOfCnxIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = forwardCallIndicators

  ISUP::ParmValue* forwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{forwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* forwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{forwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = callingPartysCategory

  ISUP::ParmValue* callingPartysCategory(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{callingPartysCategory}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* callingPartysCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingPartysCategory}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transmissionMediumRequire

  ISUP::ParmValue* transmissionMediumRequire(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transmissionMediumRequire}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* transmissionMediumRequire(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transmissionMediumRequire}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = calledPartyNumber

  ISUP::ParmValue* calledPartyNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{calledPartyNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* calledPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledPartyNumber}>
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

  IsupIam* applicationTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{applicationTransport}>
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

  IsupIam* businessGroup(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callReference}>
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

  IsupIam* calledDirectoryNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledDirectoryNumber}>
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

  IsupIam* callingPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callingPartyNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = carrierIdentification

  HPAIN::Boolean carrierIdentificationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{carrierIdentification}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  carrierIdentificationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{carrierIdentification}> as absent
  // in the message. 

  ISUP::ParmValue* carrierIdentification(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{carrierIdentification}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* carrierIdentification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{carrierIdentification}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = carrierSelectionInformation

  HPAIN::Boolean carrierSelectionInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{carrierSelectionInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  carrierSelectionInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{carrierSelectionInformation}> as absent
  // in the message. 

  ISUP::ParmValue* carrierSelectionInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{carrierSelectionInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* carrierSelectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{carrierSelectionInformation}>
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

  IsupIam* chargeNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* connectionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{connectionRequest}>
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

  IsupIam* CUGinterlockCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{CUGinterlockCode}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = egressService

  HPAIN::Boolean egressServiceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{egressService}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  egressServiceSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{egressService}> as absent
  // in the message. 

  ISUP::ParmValue* egressService(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{egressService}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* egressService(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{egressService}>
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

  IsupIam* genericAddress(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericAddress}>
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

  IsupIam* informationRequestIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{informationRequestIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = jurisdiction

  HPAIN::Boolean jurisdictionIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{jurisdiction}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  jurisdictionSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{jurisdiction}> as absent
  // in the message. 

  ISUP::ParmValue* jurisdiction(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{jurisdiction}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* jurisdiction(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{jurisdiction}>
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

  IsupIam* networkTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkTransport}>
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

  IsupIam* optionForwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* originalCalledNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originalCalledNumber}>
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

  IsupIam* originatingLineInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* redirectingNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* redirectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionInformation}>
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

  IsupIam* serviceActivation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = serviceCodeIndicator

  HPAIN::Boolean serviceCodeIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{serviceCodeIndicator}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  serviceCodeIndicatorSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{serviceCodeIndicator}> as absent
  // in the message. 

  ISUP::ParmValue* serviceCodeIndicator(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{serviceCodeIndicator}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* serviceCodeIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceCodeIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = specialProcessingRequest

  HPAIN::Boolean specialProcessingRequestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{specialProcessingRequest}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  specialProcessingRequestSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{specialProcessingRequest}> as absent
  // in the message. 

  ISUP::ParmValue* specialProcessingRequest(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{specialProcessingRequest}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* specialProcessingRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{specialProcessingRequest}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = transactionRequest

  HPAIN::Boolean transactionRequestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transactionRequest}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  transactionRequestSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{transactionRequest}> as absent
  // in the message. 

  ISUP::ParmValue* transactionRequest(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{transactionRequest}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* transactionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transactionRequest}>
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

  IsupIam* transitNetworkSelection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transitNetworkSelection}>
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

  IsupIam* userServiceInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userServiceInformation}>
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

  IsupIam* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userToUserIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = precedence

  HPAIN::Boolean precedenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{precedence}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  precedenceSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{precedence}> as absent
  // in the message. 

  ISUP::ParmValue* precedence(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{precedence}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* precedence(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{precedence}>
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

  IsupIam* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{remoteOperations}>
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

  IsupIam* serviceActivation1995(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{serviceActivation1995}>
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

  IsupIam* userServiceInformationPrime(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userServiceInformationPrime}>
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

  IsupIam* circuitAssignmentMap(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{circuitAssignmentMap}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = genericName

  HPAIN::Boolean genericNameIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericName}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  genericNameSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{genericName}> as absent
  // in the message. 

  ISUP::ParmValue* genericName(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{genericName}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* genericName(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericName}>
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

  IsupIam* hopCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{hopCounter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = operatorServicesInformation

  HPAIN::Boolean operatorServicesInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{operatorServicesInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  operatorServicesInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{operatorServicesInformation}> as absent
  // in the message. 

  ISUP::ParmValue* operatorServicesInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{operatorServicesInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* operatorServicesInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{operatorServicesInformation}>
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

  IsupIam* locationNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{locationNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = contractNumber

  HPAIN::Boolean contractNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{contractNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  contractNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{contractNumber}> as absent
  // in the message. 

  ISUP::ParmValue* contractNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{contractNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* contractNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{contractNumber}>
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

  IsupIam* isdnUserIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{isdnUserIndicator}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = originatingAreaInformation

  HPAIN::Boolean originatingAreaInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{originatingAreaInformation}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  originatingAreaInformationSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{originatingAreaInformation}> as absent
  // in the message. 

  ISUP::ParmValue* originatingAreaInformation(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{originatingAreaInformation}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* originatingAreaInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originatingAreaInformation}>
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

  IsupIam* networkFunctionType(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkFunctionType}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = reasonNotPresentingCallerId

  HPAIN::Boolean reasonNotPresentingCallerIdIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{reasonNotPresentingCallerId}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  reasonNotPresentingCallerIdSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{reasonNotPresentingCallerId}> as absent
  // in the message. 

  ISUP::ParmValue* reasonNotPresentingCallerId(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{reasonNotPresentingCallerId}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* reasonNotPresentingCallerId(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{reasonNotPresentingCallerId}>
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

  IsupIam* propagationDelayCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{propagationDelayCounter}>
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

  IsupIam* networkSpecificFacility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkSpecificFacility}>
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

  IsupIam* userTeleserviceInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{userTeleserviceInformation}>
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

  IsupIam* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupIam* MLPPPrecedence(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{MLPPPrecedence}>
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

  IsupIam* transMediumRequirePrime(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{transMediumRequirePrime}>
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

  IsupIam* forwardGVNS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{forwardGVNS}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

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

  IsupIam* CCSS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{CCSS}>
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

  IsupIam* networkManagementControl(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{networkManagementControl}>
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

  IsupIam* correlationId(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{correlationId}>
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

  IsupIam* callDiversionTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callDiversionTreatmentIndicator}>
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

  IsupIam* calledINNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{calledINNumber}>
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

  IsupIam* callOfferingTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{callOfferingTreatmentIndicator}>
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

  IsupIam* conferenceTreatmentIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{conferenceTreatmentIndicator}>
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

  IsupIam* SCFId(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{SCFId}>
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

  IsupIam* uidCapabilityIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{uidCapabilityIndicator}>
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

  IsupIam* echoControlInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{echoControlInformation}>
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

  IsupIam* collectCallRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{collectCallRequest}>
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

  IsupIam* originationISCPointCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{originationISCPointCode}>
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

  IsupIam* CCBS(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* freephoneIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{freephoneIndicators}>
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

  IsupIam* isdnUserIndication(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* chargingAreaInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{chargingAreaInformation}>
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

  IsupIam* contractorNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{contractorNumber}>
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

  IsupIam* mobileCommEndInfoTrf(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* mobileCommCallRef(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{mobileCommCallRef}>
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

  IsupIam* phsTerminalIdentification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* causeForCallerNumPresRest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* causeForRedirection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{causeForRedirection}>
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

  IsupIam* additionalUserCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{additionalUserCategory}>
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

  IsupIam* operatorInformationTransfer(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{operatorInformationTransfer}>
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

  IsupIam* redirectionCapability(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* redirectionCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectionCounter}>
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

  IsupIam* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{accessTransport}>
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

  IsupIam* genericNotification(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
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

  IsupIam* genericNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericNumber}>
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

  IsupIam* genericDigits(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{genericDigits}>
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

  IsupIam* unRecognizedParameter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{unRecognizedParameter}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = nationalForwardCallIndicatorsLbL

  HPAIN::Boolean nationalForwardCallIndicatorsLbLIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{nationalForwardCallIndicatorsLbL}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  nationalForwardCallIndicatorsLbLSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{nationalForwardCallIndicatorsLbL}> as absent
  // in the message. 

  ISUP::ParmValue* nationalForwardCallIndicatorsLbL(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{nationalForwardCallIndicatorsLbL}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* nationalForwardCallIndicatorsLbL(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{nationalForwardCallIndicatorsLbL}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = nationalForwardCallIndicators

  HPAIN::Boolean nationalForwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{nationalForwardCallIndicators}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  nationalForwardCallIndicatorsSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{nationalForwardCallIndicators}> as absent
  // in the message. 

  ISUP::ParmValue* nationalForwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{nationalForwardCallIndicators}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* nationalForwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{nationalForwardCallIndicators}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = presentationNumber

  HPAIN::Boolean presentationNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{presentationNumber}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  presentationNumberSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{presentationNumber}> as absent
  // in the message. 

  ISUP::ParmValue* presentationNumber(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{presentationNumber}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* presentationNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{presentationNumber}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = lastDivertingLineIdentity

  HPAIN::Boolean lastDivertingLineIdentityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{lastDivertingLineIdentity}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  lastDivertingLineIdentitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{lastDivertingLineIdentity}> as absent
  // in the message. 

  ISUP::ParmValue* lastDivertingLineIdentity(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{lastDivertingLineIdentity}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* lastDivertingLineIdentity(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{lastDivertingLineIdentity}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = partialCallingLineIdentity

  HPAIN::Boolean partialCallingLineIdentityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{partialCallingLineIdentity}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  partialCallingLineIdentitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{partialCallingLineIdentity}> as absent
  // in the message. 

  ISUP::ParmValue* partialCallingLineIdentity(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{partialCallingLineIdentity}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* partialCallingLineIdentity(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{partialCallingLineIdentity}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = pivotCapability

  HPAIN::Boolean pivotCapabilityIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{pivotCapability}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  pivotCapabilitySetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{pivotCapability}> as absent
  // in the message. 

  ISUP::ParmValue* pivotCapability(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{pivotCapability}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* pivotCapability(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{pivotCapability}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // = redirectCounter

  HPAIN::Boolean redirectCounterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectCounter}>
  // is present in message. Note that no write access is provided : only
  // the setting of a value activates the presence flag.

  void  redirectCounterSetAbsent(ISUP::MsgStatus& P_status);
  // Sets the optional parameter <{redirectCounter}> as absent
  // in the message. 

  ISUP::ParmValue* redirectCounter(ISUP::MsgStatus& P_status) const;
  // Provides read access to the <{redirectCounter}>
  // parameter.
  // The user must delete the <{ISUP::ParmValue}> object instance.

  IsupIam* redirectCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{redirectCounter}>
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

  friend ostream& operator<< (ostream& P_os, const IsupIam& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupIam}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupIam* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupIam}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupIam& operator=(const IsupIam&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupIam static data 

  static void end();
  // Ask to end with the IsupIam static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message IAM which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the IAM message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new IAM messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the IAM messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPIAM_H
//
// = EXAMPLE
//
// This example shows how a message IAM can be accessed.
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
//  // IsupIam is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupIam::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupIam* msgPtr = NEW IsupIam(msgSetId);
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
