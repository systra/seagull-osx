//  Copyright (C) Hewlett-Packard Company, 1995, 1996.

// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   BF_MDMgr.h
//                               -------------------
//
//
//  PURPOSE: 
//
//  NOTES and CAUTIONS:
//
//  FILE : /users/eric/BabelF/code/publicHeaders/BF_MDMgr.h
//____________________________________________________________________________
//
//
//  AUTHOR: Eric Julien 
//                                               DATE: Mon May 29 11:18:25 1995
//
//  Rev: 
//       $Source: /HMSDataBase/dev/U4/BabelF/code/publicHeaders/BF_MDMgr.h
//       $Revision: 2.6 $
//       
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version                                             
//----------------------------------------------------------------------------
// end_is

#ifndef BF_MDMGR_H
#define BF_MDMGR_H

#include <BF_Common.h>

class BF_MDMgr_impl;
class BF_CoDec;
class BF_MDMsgSet;

class BF_MDMgr
//
// = TITLE
// C++ encapsulation of the manager of the Babel Fish API
// 
// = CLASS TYPE
// Concrete
//
// = VERSION
// $Revision: 2.6 $
//
// = DATE RELEASED
// $Date: 1996/08/23 11:22:41 $
//
// = DESCRIPTION
// Provides a specific interface to the manager of the Babel Fish API.
// This manager is in charge of starting / ending the Babel Fish API
// (i.e. of allocating primary static data to create the message set META
// DATA and acting as a general garbage collector at the end of the
// Babel Fish API usage).
{
public:
   // = INITIALIZATION/END

   static void init(HPAIN::Uint16 P_msgSetMaxNb = BF_maxMsgSet,
		    HPAIN::Uint16 P_coDecMaxNb = BF_maxCoDec);
   // This static method starts the Babel Fish API.
   // The first default parameter <{P_msgSetMaxNb}> allows specification of the 
   // number of message set instances to be created during this Babel Fish 
   // "session" (there may be one instance only per message set).
   // The second default parameter <{P_coDecMaxNb}> specifies the 
   // number of CoDec instances to be created during this Babel Fish "session".
   // Default values of the parameters are defined in the file <{BF_Common.h}>.

   static void end();
   // This static method ends the Babel Fish API.

   // = MESSAGE SET CREATION/DELETION

   static BF_MDMsgSet* createMsgSet(const char* P_msgSetName, 
				    BF_status& P_status);
   // Create a META DATA related to an ASN.1+ message set description
   // whose name is provided by the string <{P_msgSetName}>. If the BF
   // API works with static message sets only, at most one message can
   // satisfy the name asked for. Otherwise, the latest user version
   // number is selected through either dynamic and static, if any,
   // message set bases. In that case, the dynamic message set bases are
   // selected from the directory referenced to by the variable
   // msldbRoot positionned in the global.cong configuration file.
   // 
   // This method is a factory of instances for the <{BF_MDMsgSet}>
   // class, and is an encapsulation of the message set contained in the
   // META DATA.  The method also involves creating in memory instances
   // of the <{BF_MDMsg}> classes (BFtypes of the message set),
   // instances of the <{BF_MDMsgElem}> classes (elements of the
   // BFtypes), instances of the <{BF_MDConstraint}> classes
   // (constraints of elements), and instances of the <{BF_MDOperation}>
   // classes (operations of the message set). If a message set has
   // already been created, this method is to return a reference to the
   // same instance (i.e. there is only one instance per ASN.1+ message
   // set description) and increments the counter representing the
   // number of users working with that reference. The parameter
   // <{P_status}> may return the following errors :
   //
   // NO_MGR : The manager is not initialized: <{init()}> method was not
   // invoked. 
   //
   // NO_MSGSET : There is no such message set with that name or the 
   // constructor has failed.

   static BF_MDMsgSet* createMsgSet(const char* P_msgSetName, 
				    HPAIN::Uint32 P_majorVer, HPAIN::Uint32 P_minorVer, 
				    BF_status& P_status);
   // Create a META DATA related to an ASN.1+ message set description
   // whose name is provided by the string <{P_msgSetName}> and whose
   // version is provided by arguments <{P_majorVer}> and <{P_minorVer}>
   // representing respectively the major version number and the minor
   // version number. The dynamic message set bases, when appropriate,
   // are selected from the directory referenced to by the variable
   // msldbRoot positionned in the global.cong configuration file.
   // 
   // This method is a factory of instances for the <{BF_MDMsgSet}> class,
   // and is an encapsulation of the message set contained in the META DATA. 
   // The method also involves creating in memory instances of the
   // <{BF_MDMsg}> classes (BFtypes of the message set), instances of the
   // <{BF_MDMsgElem}> classes (elements of the BFtypes), instances of the
   // <{BF_MDConstraint}> classes (constraints of elements), and instances 
   // of the <{BF_MDOperation}> classes (operations of the message set).
   // If a message set has already been created, this method is to return
   // a reference to the same instance (i.e. there is only one instance per
   // ASN.1+ message set description) and increments the counter representing
   // the number of users working with that reference.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MGR : The manager is not initialized: <{init()}> method was not
   // invoked. 
   //
   // NO_MSGSET : There is no such message set with that name or the 
   // constructor has failed.

   static BF_MDMsgSet* createMsgSet(BF_identifier P_msgSetId, 
			     	    BF_status& P_status);
   // Creates a META DATA related to an ASN.1+ message set description
   // whose identity is provided by the BF_identifier <{P_msgSetId}>. If
   // the BF API works with static message sets only, at most one
   // message can satisfy the name asked for. Otherwise, the latest user
   // version number is selected through either dynamic and static, if
   // any, message set bases. In that case, the dynamic message set
   // bases are selected from the directory referenced to by the
   // variable msldbRoot positionned in the global.cong configuration
   // file.
   // 
   // This method is a factory of instances of the <{BF_MDMsgSet}> class,
   // and an encapsulation of the message set in the META DATA.
   // The method also involves creating in memory instances of the
   // <{BF_MDMsg}> classes (BFtypes of the message set), instances of the
   // <{BF_MDMsgElem}> classes (elements of the BFtypes), instances of the
   // <{BF_MDConstraint}> classes (constraints of elements), and instances 
   // of the <{BF_MDOperation}> classes (operations of the message set).
   // If a message set has already been created, this method returns
   // a reference to the same instance (i.e. there is only one instance per
   // ASN.1+ message set description) and increments the counter representing
   // the number of users working with that reference.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MGR : The manager is not initialized: <{init()}> method was not
   // invoked. 
   //
   // NO_MSGSET : There is no such message set with that BF identifier or the 
   // constructor has failed.

   static BF_MDMsgSet* createMsgSet(BF_identifier P_msgSetId, 
				    HPAIN::Uint32 P_majorVer, HPAIN::Uint32 P_minorVer, 
			     	    BF_status& P_status);
   // Creates a META DATA related to an ASN.1+ message set description
   // whose identity is provided by the BF_identifier <{P_msgSetId}> and
   // whose version is provided by arguments <{P_majorVer}> and
   // <{P_minorVer}> representing respectively the major version number
   // and the minor version number. The dynamic message set bases, when
   // appropriate, are selected from the directory referenced to by the
   // variable msldbRoot positionned in the global.cong configuration
   // file.
   // 
   // This method is a factory of instances of the <{BF_MDMsgSet}> class,
   // and an encapsulation of the message set in the META DATA.
   // The method also involves creating in memory instances of the
   // <{BF_MDMsg}> classes (BFtypes of the message set), instances of the
   // <{BF_MDMsgElem}> classes (elements of the BFtypes), instances of the
   // <{BF_MDConstraint}> classes (constraints of elements), and instances 
   // of the <{BF_MDOperation}> classes (operations of the message set).
   // If a message set has already been created, this method returns
   // a reference to the same instance (i.e. there is only one instance per
   // ASN.1+ message set description) and increments the counter representing
   // the number of users working with that reference.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MGR : The manager is not initialized: <{init()}> method was not
   // invoked. 
   //
   // NO_MSGSET : There is no such message set with that BF identifier or the 
   // constructor has failed.

   static void deleteMsgSet(BF_MDMsgSet* P_msgSet, 
			    BF_status& P_status);
   //
   // Delete from META DATA related to a message set.
   // The method also involves deleting in memory instances of 
   // <{BF_MDMsg}> classes (BFtypes of the message set), instances of 
   // <{BF_MDMsgElem}> classes (elements of the BFtypes), instances of 
   // <{BF_MDConstraint}> classes (constraints of elements), and instances 
   // of <{BF_MDOperation}> classes (operations of the message set).
   // The message set is actually deleted if the number of users working 
   // with that reference is null.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MGR : The manager is not initialized: <{init()}> method was not
   // invoked. 
   
   // = META DATA ACCESS 

   static HPAIN::Uint16 getMsgSetId(const BF_MDMsgSet* P_msgSet,
			     BF_status& P_status);
   //
   // Get from META DATA, the dynamic identifier of a message set. The Dynamic
   // identifier is an integer allocated at the creation of the message set.
   // It allows the user to handle an integer instead of a reference to an 
   // object instance. From such an integer, the related reference may be 
   // obtained by using the <{getMsgSet}> method.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MSGSET : There is no such message set with that reference.

   static BF_MDMsgSet* getMsgSet(HPAIN::Uint16 P_msgSetId,
				 BF_status& P_status);
   // Get from META DATA, the reference of the message set identified by the 
   // dynamic identifier. This identifier has been previously obtained by using
   // the <{getMsgSetId}> method.
   // The parameter <{P_status}> may return the following errors :
   //
   // NO_MSGSET : There is no such message set with that identifier.

   // = MEMORY HANDLER SPECIAL
   // set size of the MemoryHandler Pool associated with BF_LRMsg and BF_TRMsg 
   // objects.
   static void setPoolSize(HPAIN::Uint32 numberOfLRMsgScp, 
                           HPAIN::Uint32 numberOfGtoTRMsg);
   // This methods allows the user to adjust the size of MemoryHandler object
   // pools.
   // <{numberOfLRMsgScp}>: number of BF_LRMsgScp and BF_LRMsgScp_impl objects 
   // to be set in the BF_LRMsgScp_POOL and BF_LRMsgScpI_POOL MemoryHandler 
   // object pools.
   // <{numberOfGtoTRMsg}>: number of BF_GtoTRMsg and BF_GtoTRMsg_impl objects 
   // to be set in the BF_GtoTRMsg_POOL and BF_GtoTRMsgI_POOL MemoryHandler 
   // object pools.
   // The default value is <{1024}> for this two parameters.

private:
   static BF_MDMgr_impl* hidden;
   // pointer to implementation object

   BF_MDMgr();
   // to prevent ctor usage

   ~BF_MDMgr();
   // to prevent dtor usage
};
#endif           /* BF_MDMGR_H */
//
// = EXAMPLE
//
//  This example shows how a message set can be created.
//
// = BEGIN<CODE>
//
//  BF_status L_status;
//
//  BF_MDMgr::init();
//
//  const BF_MDMsgSet* L_set = BF_MDMgr::createMsgSet(12, L_status);
//
//  HPAIN::Uint16 L_id = BF_MDMgr::getMsgSetId(L_set, L_status);
//     
//  BF_MDMgr::deleteMsgSet(L_status);
//
//  BF_MDMgr::end();
//
// = END<CODE>
//
// = LIBRARY
//  $(BabelfDM)
//
// = FILENAME
//  BF_MDMgr.h
//
// = NOTE
//
// = SEE ALSO
//  BF_MDMsgSet class, BF_MDMsg class, BF_MDMsgElem class, 
//  BF_MDConstraint class, BF_MDOperation class.
