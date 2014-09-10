//  Copyright (C) Hewlett-Packard Company, 1995, 1996.

// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   BF_LRMsgScp.h
//                               ----------------------
//
//
//  PURPOSE: 
//
//  NOTES and CAUTIONS:
//
//  FILE : /users/eric/BabelF/code/LocRep/BF_LRMsgScp.h
//____________________________________________________________________________
//
//
//  AUTHOR: Eric Julien 
//                                               DATE: Mon May 29 11:18:25 1995
//
//  Rev: 
//       $Source: /BabelF/code/LocRep/BF_LRMsgScp.h $
//       $Revision: 2.9.1.1 $
//       
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version   			
//----------------------------------------------------------------------------
// end_is

#ifndef BF_LRMSGSCP_H
#define BF_LRMSGSCP_H

#include <BF_Common.h>          // for BF common types
#include <BF_LRMsg.h>           // definition of base class

class BF_MDMsg;
class BF_MDMsgElem; 
class BF_LRIterator;


class BF_LRMsgScp : public BF_LRMsg
//
// = TITLE
// C++ encapsulation of a <{Local Representation}> i.e. the decoded form
// of the message. This is a class dedicated to the SCP/SLEE.
// 
// = CLASS TYPE
// Derived from BF_LRMsg
//
// = VERSION
// $Revision: 2.9.1.1 $
//
// = DATE RELEASED
// $Date: 2000/10/23 15:58:47 $
//
// = DESCRIPTION
// Provides reading/writing access to the local representation contents, i.e.
// the message parameters.

{

public:
   // CONSTRUCTORS

   BF_LRMsgScp(const BF_MDMsg& P_msg); 
   // ctor.
   // This ctor uses its associated meta data object to retreive the 
   // Local Representation size and allocates the corresponding data
   // block.
   BF_LRMsgScp(const BF_MDMsg& P_msg, BF_LRMsg::kind P_type);
   // ctor.
   // This ctor uses its associated meta data object to retreive the
   // Local Representation size and allocates the corresponding data
   // block. allow to enable overload in case of SCP using ISUP message
   // set.
   BF_LRMsgScp(const BF_MDMsg* P_msg, BF_LRMsg::kind P_type,HPAIN::Uint32 P_disc);
   // ctor.
   // This ctor uses its associated meta data object to retreive the
   // Local Representation size and allocates the corresponding data
   // block. allow to enable overload in case of SCP using ISUP message
   // set. Used to prevent from creation of unsupported messages
  
   virtual ~BF_LRMsgScp(); 
   // dtor

   virtual const BF_MDMsg* getRelatedMsg() const;
   // Return the associated BF_MDMsg message

   // = ACCESS METHODS
   virtual void getCA(const BF_MDMsgElem& P_msgElem, 
                      BF_DDLtype::kind P_DDLtype,
                      HPAIN::Uint32& P_length,
                      BF_scpGenType& P_var,
                      BF_status& P_status,
                      HPAIN::Boolean P_isOdd=HPAIN::bFalse) const;
   //
   // This method gives read access to the value of the message parameter
   // identified by <{P_msgElem}>. This value is returned in <{P_var}>, and 
   // <{P_length}> is updated accordingly.
   // <{P_length}> is expressed in bytes, but for the BF_DDLType::BCD type
   // where it is expressed in digits.
   // Supported ddl types are: BF_DDLType::INTEGER, BF_DDLType::STRING,
   // BF_DDLType::BOOLEAN, BF_DDLType::BCD, BF_DDLType::ANY.
   // <{P_isOdd}> is used for BCD strings of variable length, for which the 
   // odd/even indication is necessary.
   // <{P_status}> may notify of a type error (TYPE_MISMATCH or 
   // TYPE_NOT_SUPPORTED), the absence of an optional parameter 
   // (OPTIONAL_ABSENT), an uninitialized union-type (UNINIT_CHOICE), or an 
   // unauthorized access to the Local Representation (write-only mode).


   virtual void getCA(const BF_MDMsgElem& P_msgElem, 
                      const BF_LRIterator* P_iter,
                      BF_DDLtype::kind P_DDLtype,
                      HPAIN::Uint32& P_length,
                      BF_scpGenType& P_var,
                      BF_status& P_status,
                      HPAIN::Boolean P_isOdd=HPAIN::bFalse) const;
   //
   // This method provides the same functionality as the previous one, but also
   // requires a pointer to a BF_Iterator instance argument: <{P_iter}>. That
   // means that <{P_msgElem}> is a list type (associated with a SEQUENCE OF or
   // SET OF). As well as the previous error codes, <{P_status}> may indicate
   // a problem on <{P_iter}> (non-existent: MISSING_ITER or has an invalid
   // value: INVALID_ITER_VALUE.

   virtual void getBCA(const BF_MDMsgElem& P_msgElem, 
                       BF_DDLtype::kind P_DDLtype,
                       HPAIN::Uint32& P_length,
                       HPAIN::Uint32& P_remLength,
                       BF_scpGenType& P_var,
                       BF_status& P_status,
                       HPAIN::Boolean P_isOdd=HPAIN::bFalse) const;
 
   virtual void getBCA(const BF_MDMsgElem& P_msgElem, 
                       const BF_LRIterator* P_iter,
                       BF_DDLtype::kind P_DDLtype,
                       HPAIN::Uint32& P_length,
                       HPAIN::Uint32& P_remLength,
                       BF_scpGenType& P_var,
                       BF_status& P_status,
                       HPAIN::Boolean P_isOdd=HPAIN::bFalse) const;

   virtual void setCA(const BF_MDMsgElem& P_msgElem, 
                      BF_DDLtype::kind P_DDLtype,
                      HPAIN::Uint32 P_length,
                      BF_scpGenType& P_var,
                      BF_status& P_status);
   //
   // This method gives write access to the value of the message parameter  
   // identified by <{P_msgElem}>. This value is supplied in <{P_var}> and 
   // its length in <{P_length}>.
   // <{P_length}> is expressed in bytes, but for the BF_DDLType::BCD type 
   // it is expressed in digits.
   // Supported ddl types are: BF_DDLType::INTEGER, BF_DDLType::STRING,
   // BF_DDLType::BOOLEAN, BF_DDLType::BCD, BF_DDLType::ANY.
   // <{P_status}> may indicate a type error (TYPE_MISMATCH or 
   // TYPE_NOT_SUPPORTED), the dual initialization of a union-type 
   // (CHOICE_ALREADY_SET), an incorrect value with regard to the constraints
   // (INVALID_VALUE, INVALID_SIZE), or an unauthorized access to the Local
   // Representation (read-only mode).
 
   
   virtual void setCA(const BF_MDMsgElem& P_msgElem, 
                      const BF_LRIterator* P_iter,
                      BF_DDLtype::kind P_DDLtype,
                      HPAIN::Uint32 P_length,
                      BF_scpGenType& P_var,
                      BF_status& P_status);
   //
   // This method provides the same functionality as the previous one, but takes
   // in addition, a pointer to a BF_Iterator instance argument: <{P_iter}>. 
   // That means that <{P_msgElem}> is a list type (associated with a SEQUENCE
   // OF or SET OF). As well as the previous error codes, <{P_status}> may 
   // indicate a problem on <{P_iter}> (non-existent: MISSING_ITER or has an
   // invalid value: INVALID_ITER_VALUE.

   virtual BF_LRIterator *createIterator(const BF_MDMsgElem& P_msgElem,
                                         BF_status &P_status);
   // In either read or write mode, creates an iterator of <{this}>
   // Local Representation on a list defined by Meta Data <{P_msgElem}>.

   virtual BF_LRIterator *createIterator(const BF_MDMsgElem& P_msgElem,
                                         const BF_LRIterator *P_fromIter,
                                         BF_status &P_status);
   // In either read or write mode, creates an iterator of <{this}>
   // Local Representation on a nested list defined by Meta Data
   // <{P_msgElem}> and upper level Iterator <{P_fromIter}>.



private:

   // to prevent public copy ctor usage: no implementation
   BF_LRMsgScp(const BF_LRMsgScp& P_srceObj); 

   // to prevent public operator= usage: no implementation
   BF_LRMsgScp& operator=(const BF_LRMsgScp& P_rhs);


};


#endif           /* BF_LRMSGSCP_H */
//
// = EXAMPLE
//
//  This example shows how to set a message parameter from a local representation
//
// = BEGIN<CODE>
//
//  BF_status L_status;
//
//  BF_MDMsg* L_MDMsg;
//  //  initialize L_MDMsg
//
//  BF_MDMsgElem* L_MDMsgElem;
//  //  initialize L_MDMsgElem
//
//  HPAIN::Uint32 length;
//
//  BF_SCPGenType.stringPtr L_parm;
//
//  BF_LRMsgScp* L_locRep = new BF_LRMsgScp(L_MDMsg);
//
//  L_locRep->setCA(*L_MDMsgElem, 
//                  BF_DDLType::STRING,
//                  strlen(L_parm),
//                  L_parm,
//                  L_status);
//
//  if (!L_status.isOk())
//     //  do something ....
//
//
// = END<CODE>
//
// = LIBRARY
//  $(BabelfDM)
//
// = FILENAME
//  BF_LRMsgScp.h
//
// = NOTE
//
// = SEE ALSO
//  BF_LRMsg class, BF_LRIterator class.
