// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   IsupUpa.h
//                               ------------------
//
//
//  PURPOSE:
//
// = LIBRARY
//     ISUP
//
// = FILENAME
//     IsupUpa.h
//
// = AUTHOR(S)
//          HP OC ISUP was developed by Hewlett Packard, TID.
// = COPYRIGHT
//           Hewlett Packard - Telecom Infrastructure Division (1999).

//  Revision: 
//            $Source: /ISUP/code/message/IsupUpa.h $
//            $Revision: 1.5 $
//            
//
//------------------------------------------------------------------------------

#ifndef ISUPUPA_H
#define ISUPUPA_H

#include <IsupCommon.h>
#include <IsupMsg.h>
#ifdef ISUP_I88
#include <IsupSgm.h>
#endif

class BF_MDMsg;
class BF_MDMsgElem;

class IsupUpa : public IsupMsg
//
// = TITLE
// C++ encapsulation of an ISUP UPA (<{VERSION 2.0}>).
// 
// = DESCRIPTION
// This message class provides a specific interface to individually build and 
// access each parameter of an <[UPA message]>.
{
public:

  // = CONSTRUCTION

  IsupUpa(ISUP::MsgSetID);
  // This constructor builds an empty UPA message. The parameter <{P_msgSetId}>,
  // previously allocated by a call to <{IsupMgr::whichMsgSet()}>, must be 
  // passed. Therefore, the UPA as defined in the load metadata will
  // be built, but all defined accessors may not succeed if a parameter is
  // not part of the message as specified by the message set description.
  // See User Manual for more information. To check the success of this
  // constructor, a call to <{IsupUpa::isValid()}> inspects the state of the
  // object.
  // From an implementation point of view, this constructor gets an instance
  // of a local representation of the UPA message.

  virtual ~IsupUpa();
  // This destructor deletes a UPA message. 

  static IsupUpa* castMsg(const IsupMsg* P_msg) ;
  // This method provides a safe down cast.
  // This call is usually used on the inbound path where the user receives an
  // <{IsupMsg}> from an <{IsupProbe}>. Using the <{getMsgType()}> method, the
  // user can then call this method (limited overhead - no physical copy)
  // to get access to all the <{IsupUpa}> class accessors. If the message set
  // customization options are used, the same message set as the one used by
  // <{P_msgPtr}> will be used.

  IsupUpa(const IsupUpa& P_from);
  // The copy constructor provides a way to construct a UPA message and does
  // a bit wise copy of an existing message instance.

  // = MSG SET CUSTOMIZATION SUPPORT
  // The following methods are for advanced users using the message set 
  // customization options. They allow registration of a specific new parameter
  // for an UPA message.
  // \fP

  static ISUP::InfoStatus installParm(const char* P_parmName,
				      ISUP::MsgSetID P_msgSetId,
				      ISUP::ParmID& P_parmId);
  // This method makes the new parameter <{P_parmName}> accessible via the <{IsupUpa}>
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
  // Accessors provide a generic facility for accessing UPA parameters. Each 
  // parameter has two accessors defined : one for reading, one for 
  // writing. Optional parameters have an additional accessor: to check for the
  // presence of the field
  // 
  // end_is
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

  IsupUpa* parameterCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{parameterCompatibility}>
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

  IsupUpa* messageCompatibility(ISUP::ParmValue& P_val, ISUP::MsgStatus& P_status);
  // Provides write access to the <{messageCompatibility}>
  // parameter. Setting a value activates the presence flag.
  // This methods does not delete the provided <{ISUP::ParmValue}> instance.

  // begin_trailer
  

  // = ERROR HANDLING
  // See the definition of the concerning methods in its abstract class.
  // \fP

  // = STREAMS HANDLING

  friend ostream& operator<< (ostream& P_os, const IsupUpa& P_msg);
  // Do a pretty output on <{ostream}> of a reference to a <{IsupUpa}> instance.

  friend ostream& operator<< (ostream& P_os, const IsupUpa* P_msg);
  // Do a pretty output on <{ostream}> of a pointer to a <{IsupUpa}> instance.

private:

  // = CONSTRUCTION - INITIALIZATION

  const IsupUpa& operator=(const IsupUpa&);
  // The assignment is protected to prevent users from calling it

  static ISUP::InfoStatus init(HPAIN::Uint16 P_NumberOfMsgSet);
  // Ask to initialise the IsupUpa static data 

  static void end();
  // Ask to end with the IsupUpa static data 

  // = STANDARD MESSAGE MANAGEMENT
  
  static ISUP::InfoStatus installStdMsg(ISUP::MsgSetID P_msgSetId,
					HPAIN::Int32& P_tag);
  // Ask to support the standard message UPA which is belonging to
  // message set <{P_msgSetId}>.

  static const BF_MDMsg* getMsg(ISUP::MsgSetID P_msgSetId);
  // Ask the related BF reference of the UPA message.

  static HPAIN::Uint16 numberOfMsgSet;
  // number of message sets supported by this class.

  static const BF_MDMsg** relatedMsg;
  // Table containing the new UPA messages.

  static const BF_MDMsgElem*** relatedMsgElem;
  // Table containing the new parameters of the UPA messages.

  static ISUP::ParmID* lastParmIndex;
  // indexes of table "relatedMsgElem".

  static ISUP::ParmID* numberMaxOfParm;
  // numbers maximum of parameters in table "relatedMsgElem".

  // = FRIENDSHIP
  
  friend class IsupMsg;
  // Because class IsupMsg uses methods init, end and installStdMsg
}; 
#endif // ISUPUPA_H
//
// = EXAMPLE
//
// This example shows how a message UPA can be accessed.
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
//  // IsupUpa is a standard derived class of IsupMsg
//  // This message has a new parameter : NEW_PARM
//  install = IsupUpa::installParm ("NEW_PARM", msgSetId, parmId);
//  if (!install->isOk()) exit(1);
//
//  IsupUpa* msgPtr = NEW IsupUpa(msgSetId);
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
