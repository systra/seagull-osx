//------------------------------------------------------------------------------
//
//                               MODULE   IsupUserMsg.h
//                               ------------------
//
//
//  PURPOSE:
//
// = FILENAME
//     IsupUserMsg.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TND.
// = COPYRIGHT
//           Hewlett Packard - Telecom Network Division (1996).

//  Rev: 
//       $Source: /ISUP/code/message/IsupUserMsg.h $
//       $Revision: 2.5 $
//       
//
//------------------------------------------------------------------------------

#ifndef ISUPUSERMSG_H
#define ISUPUSERMSG_H

#include <ainCppCommon.h>
#include <IsupMsg.h>

class BF_MDMsg;
class BF_MDMsgElem;
class IsupInfoMgr;

class IsupUserMsg : public IsupMsg 
//
// = TITLE
// C++ encapsulation of a user defined Isup message (<{VERSION 2.0}>).
// 
// = CLASS TYPE
// Concrete
//
// = DESCRIPTION
// Provides a generic interface to build and access each individual
// parameter of a <[User defined message]>.
{
public:

  // = METHODS

  IsupUserMsg(ISUP::MsgID P_msgId);
  // This constructor builds an empty user defined message. 
  // A valid message identifier <{P_msgId}> previously allocated by a call to
  // <{IsupInfoMgr::installMsg()}> is expected to be passed. See User Manual for
  // more information. 
  // To check the success of this constructor on completion, a call to the
  // method <{IsupUserMsg::isValid()}> inspects the state of the object.
  // From an implementation point of view, this constructor gets an instance of
  // a <{BF_LRMsg}> object.

  ~IsupUserMsg();
  // This destructor delete a User defined message. 

  static IsupUserMsg* castMsg(const IsupMsg* P_msg);
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method,
  // the user can then call this method (limited overhead - no physical
  // copy) to get access to all the <{IsupUserMsg}> class accessors. 
  
  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgID P_msgId,
				      ISUP::ParmID& P_parmId);
  // This method lets the <{IsupAnm}> class know of new parameter 
  // <{P_parmName}>. An identifier is returned in parameter <{P_parmId}> which 
  // should be used for any further call to the specific methods <{getValue()}> 
  // and <{setValue()}>. The result of the method may be obtained by accessing
  // the returned <{ISUP::InfoStatus}> class instance.   
  
  ISUP::MsgID msgId() const;
  // This methods allows to get from a <{UserDef}> instance, the related 
  // message identifier which is defining the message, previously installed
  // by a call to the <{installMsg}> method. 
  
 
  // = GENERIC ACCESSORS

  // These methods allow to access parameter which have been installed by
  // the installParm method.
  // \fP

  virtual void getValue(ISUP::ParmID P_parmId, HPAIN::Int32& P_iVal,
			ISUP::MsgStatus& P_status) const;
  // Allows to retrieve a scalar value of an installed parameter.

  virtual void setValue(ISUP::ParmID P_parmId, HPAIN::Int32 P_iVal,
			ISUP::MsgStatus& P_status);
  // Allows to set a scalar value of an installed parameter.

  virtual void getValue(ISUP::ParmID P_parmId, ISUP::ParmValue*& P_iVal,
			ISUP::MsgStatus& P_status) const;
  // Allows to retrieve a string of an installed parameter. It is to the user
  // to delete the provided <{ISUP::ParmValue}> instance.

  virtual void setValue(ISUP::ParmID P_parmId, ISUP::ParmValue& P_iVal,
			ISUP::MsgStatus& P_status);
  // Allows to set a string of an installed parameter. this methods doesn't
  // delete the provided <{ISUP::ParmValue}> instance.

  virtual HPAIN::Boolean isParmPresent(ISUP::ParmID P_parmId,
				       ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter of an installed parameter in 
  // message is present.

  // = SPECIFIC ACCESSORS
  // Accessors provide generic facility for accessing ISUP parameters. Each 
  // parameter have a couple of accessors defined : one for reading, one for 
  // writing. For optional parameters, one other accessor is defined : to
  // check the presence of the field. Since probably all the parameters (as
  // defined by (union ANSI + ITU) are not available for a given User defined
  // message, the related assessors are to fail at their invocation.

  // = accessTransport

  HPAIN::Boolean accessTransportIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{accessTransport}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* accessTransport(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{accessTransport}> parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* accessTransport(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{accessTransport}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = automCongestionLevel

  HPAIN::Boolean automCongestionLevelIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{automCongestionLevel}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* automCongestionLevel(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{automCongestionLevel}> 
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* automCongestionLevel(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{automCongestionLevel}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = backwardCallIndicator

  HPAIN::Boolean backwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{backwardCallIndicators}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* backwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{backwardCallIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* backwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{backwardCallIndicators}>
  // parameter.

  // = callModificationIndicators

  HPAIN::Boolean callModificationIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callModificationIndicators}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* callModificationIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{callModificationIndicators}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* callModificationIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{callModificationIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = callReference

  HPAIN::Boolean callReferenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callReference}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* callReference(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{callReference}> parameter. 

  IsupUserMsg* callReference(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{callReference}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = calledPartyNumber

  HPAIN::Boolean calledPartyNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{calledPartyNumber}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* calledPartyNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{calledPartyNumber}> parameter. 

  IsupUserMsg* calledPartyNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{calledPartyNumber}> parameter.

  // = callingPartysCategory

  HPAIN::Boolean callingPartysCategoryIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{callingPartyNumber}> is present in
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* callingPartysCategory(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{callingPartysCategory}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* callingPartysCategory(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{callingPartysCategory}>
  // parameter.

  // = causeIndicators

  HPAIN::Boolean causeIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{causeIndicators}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* causeIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{causeIndicators}> parameter. 

  IsupUserMsg* causeIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{causeIndicators}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = cirGroupSuperMessageTypeInd

  HPAIN::Boolean cirGroupSuperMessageTypeIndIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{cirGroupSuperMessageTypeInd}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* cirGroupSuperMessageTypeInd(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{cirGroupSuperMessageTypeInd}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* cirGroupSuperMessageTypeInd(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{cirGroupSuperMessageTypeInd}>
  // parameter.

  // = circuitAssignmentMap

  HPAIN::Boolean circuitAssignmentMapIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{circuitAssignmentMap}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* circuitAssignmentMap(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{circuitAssignmentMap}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* circuitAssignmentMap(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{circuitAssignmentMap}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = circuitStateIndicator

  HPAIN::Boolean circuitStateIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{circuitStateIndicator}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* circuitStateIndicator(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{circuitStateIndicator}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* circuitStateIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{circuitStateIndicator}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = CUGinterlockCode

  HPAIN::Boolean CUGinterlockCodeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{CUGinterlockCode}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* CUGinterlockCode(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{CUGinterlockCode}> parameter. 

  IsupUserMsg* CUGinterlockCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{CUGinterlockCode}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = connectedNumber

  HPAIN::Boolean connectedNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{connectedNumber}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* connectedNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{connectedNumber}> parameter. 

  IsupUserMsg* connectedNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{connectedNumber}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = connectionRequest

  HPAIN::Boolean connectionRequestIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{connectionRequest}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* connectionRequest(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{connectionRequest}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* connectionRequest(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{connectionRequest}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = continuityIndicators

  HPAIN::Boolean continuityIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{continuityIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* continuityIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{continuityIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* continuityIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{continuityIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = eventInformation

  HPAIN::Boolean eventInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{eventInformation}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* eventInformation(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{eventInformation}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* eventInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{eventInformation}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = facilityIndicator

  HPAIN::Boolean facilityIndicatorIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{facilityIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* facilityIndicator(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{facilityIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* facilityIndicator(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{facilityIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = forwardCallIndicators

  HPAIN::Boolean forwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{forwardCallIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* forwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{forwardCallIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* forwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{forwardCallIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = genericName

  HPAIN::Boolean genericNameIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{genericName}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* genericName(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{genericName}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* genericName(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{genericName}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = hopCounter

  HPAIN::Boolean hopCounterIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{hopCounter}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* hopCounter(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{hopCounter}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* hopCounter(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{hopCounter}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = informationIndicators

  HPAIN::Boolean informationIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{informationIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* informationIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{informationIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* informationIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{informationIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = informationRequestIndicators

  HPAIN::Boolean informationRequestIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{informationRequestIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* informationRequestIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{informationRequestIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* informationRequestIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{informationRequestIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = natureOfCnxIndicators

  HPAIN::Boolean natureOfCnxIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{natureOfCnxIndicators}> is
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* natureOfCnxIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{natureOfCnxIndicators}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* natureOfCnxIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{natureOfCnxIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = operatorServicesInformation

  HPAIN::Boolean operatorServicesInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{operatorServicesInformation}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* operatorServicesInformation(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{operatorServicesInformation}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* operatorServicesInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{operatorServicesInformation}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = optionBackwardCallIndicators

  HPAIN::Boolean optionBackwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{optionBackwardCallIndicators}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* optionBackwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{optionBackwardCallIndicators}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* optionBackwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{optionBackwardCallIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = optionForwardCallIndicators

  HPAIN::Boolean optionForwardCallIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{optionForwardCallIndicators}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* optionForwardCallIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{optionForwardCallIndicators}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* optionForwardCallIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{optionForwardCallIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = originalCalledNumber

  HPAIN::Boolean originalCalledNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{originalCalledNumber}> is present  
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* originalCalledNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{originalCalledNumber}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* originalCalledNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{originalCalledNumber}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = precedence

  HPAIN::Boolean precedenceIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{precedence}> is present in
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag.

  ISUP::ParmValue* precedence(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{precedence}> parameter.

  IsupUserMsg* precedence(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{precedence}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = rangeAndStatus

  HPAIN::Boolean rangeAndStatusIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{rangeAndStatus}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* rangeAndStatus(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{rangeAndStatus}> parameter. 

  IsupUserMsg* rangeAndStatus(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{rangeAndStatus}> parameter.
  // Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = redirectingNumber

  HPAIN::Boolean redirectingNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectingNumber}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* redirectingNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{redirectingNumber}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* redirectingNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{redirectingNumber}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionInformation

  HPAIN::Boolean redirectionInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionInformation}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* redirectionInformation(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{redirectionInformation}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* redirectionInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{redirectionInformation}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = redirectionNumber

  HPAIN::Boolean redirectionNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{redirectionNumber}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* redirectionNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{redirectionNumber}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* redirectionNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{redirectionNumber}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = remoteOperations

  HPAIN::Boolean remoteOperationsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{remoteOperations}> is present in
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag.

  ISUP::ParmValue* remoteOperations(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{remoteOperations}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* remoteOperations(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{remoteOperations}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = serviceActivation1995

  HPAIN::Boolean serviceActivation1995IsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{serviceActivation1995}> is present in
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag.

  ISUP::ParmValue* serviceActivation1995(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{serviceActivation1995}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* serviceActivation1995(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{serviceActivation1995}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = signallingPointCode

  HPAIN::Boolean signallingPointCodeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{signallingPointCode}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* signallingPointCode(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{signallingPointCode}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* signallingPointCode(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{signallingPointCode}>
  // parameter.

  // = subsequentNumber

  HPAIN::Boolean subsequentNumberIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{subsequentNumber}> is present in 
  // message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* subsequentNumber(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{subsequentNumber}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* subsequentNumber(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{subsequentNumber}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = suspendResumeIndicators

  HPAIN::Boolean suspendResumeIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{suspendResumeIndicators}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* suspendResumeIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{suspendResumeIndicators}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* suspendResumeIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{suspendResumeIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = transitNetworkSelection

  HPAIN::Boolean transitNetworkSelectionIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transitNetworkSelection}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* transitNetworkSelection(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{transitNetworkSelection}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* transitNetworkSelection(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{transitNetworkSelection}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = transmissionMediumRequire

  HPAIN::Boolean transmissionMediumRequireIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transmissionMediumRequire}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* transmissionMediumRequire(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{transmissionMediumRequire}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* transmissionMediumRequire(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{transmissionMediumRequire}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = transmissionMediumUsed

  HPAIN::Boolean transmissionMediumUsedIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transmissionMediumUsed}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* transmissionMediumUsed(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{transmissionMediumUsed}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* transmissionMediumUsed(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{transmissionMediumUsed}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = transmitNetworkSelect

  HPAIN::Boolean transmitNetworkSelectIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{transmitNetworkSelect}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* transmitNetworkSelect(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{transmitNetworkSelect}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* transmitNetworkSelect(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{transmitNetworkSelect}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = userServiceInformation

  HPAIN::Boolean userServiceInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userServiceInformation}> is 
  // present in message. Note that no write access is provided : only the 
  // setting of a value will activate the presence flag. 

  ISUP::ParmValue* userServiceInformation(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{userServiceInformation}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* userServiceInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{userServiceInformation}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = userServiceInformationPrime

  HPAIN::Boolean userServiceInformationPrimeIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userServiceInformationPrime}> is
  // present in message. Note that no write access is provided : only the
  // setting of a value will activate the presence flag.

  ISUP::ParmValue* userServiceInformationPrime(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{userServiceInformationPrime}>
  // parameter.
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* userServiceInformationPrime(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{userServiceInformationPrime}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = userToUserIndicators

  HPAIN::Boolean userToUserIndicatorsIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userToUserIndicators}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 

  ISUP::ParmValue* userToUserIndicators(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{userToUserIndicators}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* userToUserIndicators(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{userToUserIndicators}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = userToUserInformation

  HPAIN::Boolean userToUserInformationIsPresent(ISUP::MsgStatus& P_status) const;
  // Returns TRUE is the optional parameter <{userToUserInformation}> is present
  // in message. Note that no write access is provided : only the setting of a
  // value will activate the presence flag. 
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  ISUP::ParmValue* userToUserInformation(ISUP::MsgStatus& P_status) const;
  // This accessor provides read access to the <{userToUserInformation}>
  // parameter. 
  // It is to the user to delete the <{ISUP::ParmValue}> object instance.

  IsupUserMsg* userToUserInformation(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // This accessor provides write access to the <{userToUserInformation}>
  // parameter. Setting a value will activate the presence flag.
  // This methods doesn't delete the provided <{ISUP::ParmValue}> instance.

  // = ERROR HANDLING
  // See the definition of that method in its actract class.
  // \fP

  // virtual const BF_status* getStatus(ISUP::MsgStatus& P_status) const;
  // Returns the related status.

  // = STREAMS HANDLING

  friend ostream& operator<< (ostream& P_os, const IsupUserMsg& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupUserMsg}>
  // instance

  friend ostream& operator<< (ostream& P_os, const IsupUserMsg* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupUserMsg}>
  // instance

private:

  static ISUP::MsgID getFromTag(ISUP::MsgSetID P_msgSetId, HPAIN::Int32 L_tag);
  // Ask to return the message identifier <{P_msgId}> which is belonging to
  // message set <{P_msgSetId}> with the tag value <{L_tag}>.

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsg, 
			       HPAIN::Boolean P_enforceFlag);
  // Ask to initialise the IsupUserMsg static data 

  static void end();
  // Ask to end with the IsupUserMsg static data 

  static const BF_MDMsg* getMsg(ISUP::MsgID P_msgId);
  // Ask the related BF message of the IsupUserMsg instance
  
  static ISUP::InfoStatus supportMsg(const char* P_msgName, 
				     ISUP::MsgSetID P_msgSetId,
				     ISUP::MsgID& P_msgId);
  // Ask to support the message <{P_msg}> which is belonging to message set
  // <{P_msgSetId}>.

  static HPAIN::Boolean enforceFlag;
  // flag indicating if no standard message as User defined is enforced

  static ISUP::MsgID numberOfMsg;
  // number of messages supported by this class

  static ISUP::MsgID lastMsgIndex;
  // last message index

  static const BF_MDMsg** relatedMsg;
  // Table containing the new user defined messages

  static ISUP::MsgSetID* relatedMsgSet;
  // Table of related message sets of the new user defined messages

  static HPAIN::Int32* relatedMsgTag;
  // Table of tags of the new user defined messages

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the user defined messages

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem" 

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem"

  ISUP::MsgID instanceMsg;
  // message identifier related to one instance of IsupUserMsg 

  friend class IsupInfoMgr;
  // Because class IsupInfoMgr uses the private method installStdMsg()

  friend class IsupMsg;
  // Because class IsupMsg uses the private method getFromTag()
}; 
#endif // ISUPUSERMSG_H
//
// = EXAMPLE
//
// This example shows how a User defined message can be installed and accessed.
//
// = BEGIN<CODE>
//
//  ISUP::InfoStatus install;
//  ISUP::MsgStatus status;
//
//  // This API handles a new message set : ISUP_FROM_ANYWHERE
//  ISUP::MsgSetID msgSetId;
//  install = IsupInfoMgr::installMsgSet ("ISUP_FROM_ANYWHERE", msgSetId); 
//  if (!install->isOk()) exit(1);
//
//  // This message set has a new message : NEW_MSG
//  ISUP::MsgID msgSet;
//  install = IsupInfoMgr::installMsg ("NEW_MSG", msgSetId, msgId);
//  if (!install->isOk()) exit(1);
//
//  // This message has a new parameter : NEW_PARM
//  ISUP::ParmID parmId;
//  install = IsupUserMsg::installParm ("NEW_PARM", msgId, parmId);
//  if (!install->isOk()) exit(1);
//
//  ISUP::ParmValue* L_indicator = NEW ISUP::ParmValue("\x03", 1);
//  ISUP::ParmValue* L_party = NEW ISUP::ParmValue("\x03\x31", 2);
//  ISUP::ParmValue* L_value = NEW ISUP::ParmValue();
//
//  IsupUserMsg* msgPtr = NEW IsupUserMsg(msgSetId, msgId);
//
//  msgPtr->natureOfCnxIndicator (*L_indicator, status);
//  if ((!status->isOk()) { // handle error. }
//
//  msgPtr->calledPartyNumber (*L_party, status);
//  if ((!status->isOk()) { // handle error. }
//
//  msgPtr->setValue (parmId, L_value->assign(HPAIN::Byte)0x31), status);
//  if ((!status->isOk()) { // handle error. }
//  ....
//
// = END<CODE>
//
// = NOTES
//  None.
//
// = SEE ALSO
//  IsupMgr class, IsupInfoMgr class, IsupMsg class
