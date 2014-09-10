//  Copyright (C) Hewlett-Packard Company, 1995, 1996.

// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   BF_LRMsg.h
//                               -------------------
//
//
//  PURPOSE: 
//
//  NOTES and CAUTIONS:
//
//  FILE : /users/eric/BabelF/code/LocRep/BF_LRMsg.h
//____________________________________________________________________________
//
//
//  AUTHOR: Eric Julien 
//                                               DATE: Mon May 29 11:18:25 1995
//
//  Rev: 
//       $Source: /BabelF/code/LocRep/BF_LRMsg.h $
//       $Revision: 2.18 $
//       
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version                                             
//----------------------------------------------------------------------------
// end_is

#ifndef BF_LRMSG_H
#define BF_LRMSG_H

#include <BF_Common.h>          // for BF common types

class BF_LRMsg_impl;
class BF_MDMsg;
class BF_MDMsgElem;
class BF_LRIterator;
class BF_GtoTRMsg;


class BF_LRMsg 
// = TITLE C++ class for handling Local Representation of a message
// parameter.
// 
// = VERSION
// $Revision: 2.18 $
//
// = DATE RELEASED
// $Date: 1999/04/21 08:41:58 $
//
// = DESCRIPTION
// The <{BF_LRMsg}> class is the Local Representation of a message parameter,
// as it is defined in the Meta Data. In addition, the Local
// Representation stores actual values for the different fields of the
// parameter. Local Representation can be encoded into a Transfer
// Representation, which in turn can be decoded into Local Representation.

{

public:
   enum kind
   { 
      CORE,     // Core Local Representation
      SCP,      // SCP oriented Local Representation
      ISUP_SCP  // SCP oriented Local Representation but with overload
   };
   // = CONSTRUCTOR/DESCTRUCTOR
   
   BF_LRMsg(const BF_MDMsg& P_msg);
   // Constructor needs associated meta data to get the global size and 
   // and hence allocate the bit block.
   
   virtual ~BF_LRMsg(); 
   // Destructor is virtual with a default implementation. This allows 
   // the definition of specific behavior for derived classes.
   // Default behavior is provided when destructor is not re-defined for 
   // derived classes.

   // = Local Representation MANAGEMENT
   virtual BF_LRMsg& duplicate(const BF_LRMsg& P_source, 
                               BF_status& P_status);
   // This operation assigns the content of one Local Representation to
   // another, including the iterators. This can be performed on
   // condition that both Local Representations are related to the same
   // message: this is why it differs from the assignment operator.
   
   virtual void wipe(); 
   // Erases the content of a Local Representation, resets its iterators
   // to their initial states.
   
   virtual HPAIN::Boolean isReadAllowed() const;
   virtual HPAIN::Boolean isWriteAllowed() const;
   // Returns a boolean which indicates whether a read operation
   // (respectively a write operation) is allowed on this Local
   // Representation.
   
   virtual void checkConstraintOn();
   virtual void checkConstraintOff();
   // Triggers the constraint checking for set operations.

   // = Local Representation ACCESSORS
   
   virtual BF_LRIterator *createIterator(const BF_MDMsgElem& P_msgElem,
                                         BF_status &P_status);
   // In either read or write mode, creates an iterator of <{this}>
   // Local Representation for a list defined by Meta Data <{P_msgElem}>.

   virtual BF_LRIterator *createIterator(const BF_MDMsgElem& P_msgElem,
                                         const BF_LRIterator *P_fromIter,
                                         BF_status &P_status);
   // In either read or write mode, creates an iterator of <{this}>
   // Local Representation for a nested list defined by Meta Data
   // <{P_msgElem}> and upper level Iterator <{P_fromIter}>.
   
   virtual void putIndexedElem(const BF_LRIterator& P_iter,
                               BF_status &P_status);
   // In write mode, adds a new element at place pointed to by Iterator
   // <{P_iter}>.
  
   virtual void setSubTree(const BF_MDMsgElem& P_msgElem,
			         BF_LRMsg&     P_fromLR, 
			         BF_status&    P_status);
   // This methods copies the complete decoded tree from P_fromLR 
   // to the subtree rooted at P_toThisMsgElem of this. This method will only 
   // work if the subtree identified by
   // P_msgElem is of the same ASN.1 type as the originating P_fromLR.
   // P_fromLR is modified because its pointers are physically copied 
   // and updated in order to duplicate them in this.
   // Note that if pointers has been already set in the sub-tree part of this,
   // they are crushed and buffers are lost.
   // The iterator of P_fromLR will not be copied.
   //     
   /* gcc warns on multi-line comment
   **                                    * this
   **                                   / \
   **                o    setSubTree   o   \
   **               / \  -----------> /\    i
   **              n   m             n  m   |
   **                                       j...
   **/
   //
   //

   virtual void setSubTree(const BF_MDMsgElem& P_msgElem,
			   const BF_LRIterator *P_iter,
			         BF_LRMsg&     P_fromLR,
			         BF_status&    P_status);
   // Same as above to iterated elements.

   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by the metadata
   // <{P_msgElem}>, for <{this}> Local Representation, to NULL.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              BF_status &P_status);
   // In write mode, sets the basic list element defined by the 
   // element defined by Meta Data <{P_msgElem}> and Iterator <{P_iter}>,
   // for <{this}> Local Representation, to NULL.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_scalar P_iVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by the metadata
   // <{P_msgElem}>, for {this}> Local Representation, to integer value
   // <{P_iVal}>.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              BF_scalar P_iVal,
                              BF_status &P_status);
   // In write mode,W sets the basic list element defined by Meta Data
   // <{P_msgElem}> and Iterator <{P_iter}>, for <{this}> Local Representation,
   // to integer value <{P_iVal}>.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_boolean bVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by Meta Data <{P_msgElem}>, 
   // for <{this}> Local Representation, to boolean value <{P_bVal}>.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *iter,
                              BF_boolean bVal,
                              BF_status &P_status);
   // In write mode,  sets the basic list element defined
   // by Meta Data <{P_msgElem}> and Iterator <{P_iter}>,
   // for <{this}> Local Representation, to boolean value <{P_bVal}>.
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              HPAIN::Uint32 P_length,
                              const void *P_sVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by metadata
   // <{P_msgElem}>, for <{this}> Local Representation, to octet string
   // value <{P_sVal}> in the format of an hexa string e.g. "184ba".
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              HPAIN::Uint32 P_length,
                              const void* P_sVal,
                              BF_status &P_status);
   // In write mode, sets basic list element defined by metadata
   // <{P_msgElem}>, for <{this}> Local Representation and Iterator
   // <{P_iter}> to octet string value <{P_sVal}> in the format of an
   // hexa string e.g. "184ba".

   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              HPAIN::Uint32 P_length,
                              HPAIN::Uint32 P_padLength,
                              const void* P_sVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by metadata
   // <{P_msgElem}>, for <{this}> Local Representation, to bit string
   // value <{P_sVal}> in the format of an hexa string e.g. "184ba".
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              HPAIN::Uint32 P_length,
                              HPAIN::Uint32 P_padLength,
                              const void* P_sVal,
                              BF_status &P_status);
   // In write mode, sets basic list element defined by metadata
   // <{P_msgElem}>, for <{this}> Local Representation and Iterator
   // <{P_iter}> to bit string value <{P_sVal}> in the format of an hexa
   // string e.g. "184ba".

   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              char* P_sVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by Meta Data
   // <{P_msgElem}>, for <{this}> Local Representation, to object
   // identifier value <{P_sVal}> given in format "{n0 n1 n2.. np}".
   
   virtual void setBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              char* P_sVal,
                              BF_status &P_status);
   // In write mode, sets the basic element defined by Meta Data
   // <{P_msgElem}>, for <{this}> Local Representation and Iterator
   // <{P_iter}> to object identifier value <{P_sVal}> given in format
   // "{n0 n1 n2.. np}".

   virtual void attach(const BF_MDMsgElem& P_msgElem,
                       const BF_GtoTRMsg& P_anyPtr,
                       BF_status& P_status);

   // In write mode, attaches the encoded Tranfer Representation
   // <{P_anyPtr}> as a value of <{P_msgElem}> which type is ANY.
   
   virtual void attach(const BF_MDMsgElem& P_msgElem,
                       const BF_LRIterator *P_iter,
                       const BF_GtoTRMsg& P_anyPtr,
                       BF_status& P_status);

   // In write mode, attaches the encoded Tranfer Representation
   // <{P_anyPtr}> as a value of <{P_msgElem}>, which position is
   // defined by <{P_iter}> and which type is ANY.
   
   virtual BF_GtoTRMsg* extract(const BF_MDMsgElem& P_msgElem,
                                BF_status& P_status);
   
   // In read mode, extracts the encoded Tranfer Representation
   // <{P_anyPtr}> as a value of <{P_msgElem}> which type is ANY.
   
   virtual BF_GtoTRMsg* extract(const BF_MDMsgElem& P_msgElem,
                                const BF_LRIterator *P_iter,
                                BF_status& P_status);
   
   // In read mode, extracts the encoded Tranfer Representation
   // <{P_anyPtr}> as a value of <{P_msgElem}>, which position is
   // defined by <{P_iter}> and which type is ANY.
   
   virtual HPAIN::Uint32 getLength(const BF_MDMsgElem& P_msgElem,
                            BF_status &P_status) const;
   // In read mode, gets number of elements in list defined by Meta Data
   // <{P_msgElem}>.
   
   virtual HPAIN::Uint32 getLength(const BF_MDMsgElem& P_msgElem,
                            const BF_LRIterator& P_iter,
                            BF_status &P_status) const;
   // In read mode, gets number of elements in a nested list identified
   // by Meta Data <{P_msgElem}> and Iterator <{P_iter}>.
   
   virtual HPAIN::Int32 getAlternative(const BF_MDMsgElem& P_msgElem,
                                BF_status &P_status) const;
   // In read mode, gets rank of alternating elements of a CHOICE
   // identified by Meta Data <{P_msgElem}>.
   
   virtual HPAIN::Int32 getAlternative(const BF_MDMsgElem& P_msgElem,
                                const BF_LRIterator *P_link,
                                BF_status &P_status) const;
   // In read mode, gets rank of alternating elements of a CHOICE in a
   // list identified by Meta Data <{P_msgElem}> and Iterator
   // <{P_link}>.

   virtual void  setAbsent(const BF_MDMsgElem& P_msgElem, BF_status &P_status);
   // In write mode, force an present OPTIONAL parameter to be absent of
   // the Local representation. The element is identified by Meta Data
   // <{P_msgElem}>. This operation is allowed for ISUP_SCP types of Local
   // Representations.


   virtual HPAIN::Boolean isPresent(const BF_MDMsgElem& P_msgElem,
                             BF_status &P_status) const;
   // In read mode, checks the presence of an OPTIONAL element identified by
   // Meta Data <{P_msgElem}>.
   
   virtual HPAIN::Boolean isPresent(const BF_MDMsgElem& P_msgElem,
                             const BF_LRIterator *P_link,
                             BF_status &P_status) const;
   // In read mode, checks the presence of an OPTIONAL element in a list
   // identified by Meta Data <{P_msgElem}> and Iterator <{P_iter}>.

   virtual void getSubTree(const BF_MDMsgElem& P_msgElem,
			         BF_LRMsg&     P_toLR, 
			         BF_status&    P_status);
   // This methods copies the subtree rooted at P_msgElem of this
   // to P_toLR. This method will only work if the subtree identified by
   // P_msgElem is of the same ASN.1 type as the originating P_toLR.
   // P_toLR pointers are physically copied and updated in order to 
   // duplicate them in this.
   // The iterators of P_toLR will be initialised.
   //     
   /* gcc warns on multi-line comment
   **                                    * this
   **                                   / \ 
   **                o    getSubTree   o   \ 
   **               / \  <----------- /\    i
   **              n   m             n  m   |
   **                                       j...
   **/
   //
   //

   virtual void getSubTree(const BF_MDMsgElem& P_msgElem,
			   const BF_LRIterator *P_iter,
			         BF_LRMsg&     P_toLR,
			         BF_status&    P_status);
   // Same as above to iterated elements.

   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_status &P_status) const;
   // In read mode, gets the value of NULL field identified by metadata
   // <{P_msgElem}>, from <{this}> Local Representation. If <{P_status}> is
   // OK, the <{P_msgElem}> is available with value NULL. 
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              BF_status &P_status) const;
   // In read mode, gets the value of NULL field identified by metadata
   // <{P_msgElem}> and Iterator <{P_iter}>, from <{this}> Local 
   // Representation. If <{P_status}> is OK, the <{P_msgElem}> is available 
   // with value NULL. 
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_scalar& P_iVal,
                              BF_status &P_status) const;
   // In read mode,  gets the value of integer field identified by metadata
   // <{P_msgElem}>, from <{this}> Local Representation, and sets
   // <{P_iVal}> to this value.
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              BF_scalar& P_iVal,
                              BF_status &P_status) const;
   // In read mode, gets the value of integer field identified by
   // Meta Data <{P_msgElem}> and Iterator <{P_iter}>, for <{this}> 
   // Local Representation, and sets <{P_iVal}> to this value.
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              BF_boolean& P_bVal,
                              BF_status& P_status) const;
   // In read mode, gets the value of boolean field identified by
   // Meta Data <{P_msgElem}>, for <{this}> Local Representation, 
   // and sets <{P_bVal}> to this value.
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              BF_boolean& P_bVal,
                              BF_status& P_status) const;
   // In read mode, gets the value of boolean field identified by 
   // Meta Data <{P_msgElem}> and Iterator <{P_iter}>, from <{this}> 
   // Local Representation, and sets <{P_bVal}> to this value.
   
   virtual const void* getBasicValue(const BF_MDMsgElem& P_msgElem,
                                     HPAIN::Uint32& P_length,
                                     BF_status &P_status) const;
   // In read mode, for <{this}> Local Representation, returns the value
   // of octet string field identified by Meta Data <{P_msgElem}> and
   // sets <{P_length}> to its length. This operation also applies if
   // <{P_msgElem}> defines either a BCD string or a hyperlinked octet
   // string.

   // In case the octet string has no size limit and the value that was
   // given to it exceeds the BF internal limit, the only effect is that
   // <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.

   virtual const void* getBasicValue(const BF_MDMsgElem& P_msgElem,
                                     const BF_LRIterator *P_iter,
                                     HPAIN::Uint32& P_length,
                                     BF_status& P_status) const;
   // In read mode, from <{this}> Local Representation, gets the value
   // of octet string field identified by Meta Data <{P_msgElem}> and
   // Iterator <{P_iter}>, returns this value and sets <{P_length}> to
   // its length. This operation also applies if <{P_msgElem}> defines
   // either a BCD string or a hyperlinked octet string.

   // In case the octet string has no size limit and the value that was
   // given to it exceeds the BF internal limit, the only effect is that
   // <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.
   
   virtual const void* getBasicValue(const BF_MDMsgElem& P_msgElem,
                                     HPAIN::Uint32& P_length,
                                     HPAIN::Uint32& P_padLength,
                                     BF_status &P_status) const;
   // In read mode, for <{this}> Local Representation, returns the value
   // of bit string field identified by Meta Data <{P_msgElem}>, sets
   // <{P_length}> to the global length and <{P_padLength}> to the
   // length of the bit padding.

   // In case the bit string has no size limit and the value that was
   // given to it exceeds the BF internal limit, the only effect is that
   // <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.

   virtual const void* getBasicValue(const BF_MDMsgElem& P_msgElem,
                                     const BF_LRIterator *P_iter,
                                     HPAIN::Uint32& P_length,
                                     HPAIN::Uint32& P_padLength,
                                     BF_status& P_status) const;
   // In read mode, from <{this}> Local Representation, gets the value
   // of bit string field identified by Meta Data <{P_msgElem}> and
   // Iterator <{P_iter}>, returns this value, sets <{P_length}> to the
   // global length and <{P_padLength}> to the length of the bit
   // padding.

   // In case the bit string has no size limit and the value that was
   // given to it exceeds the BF internal limit, the only effect is that
   // <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              HPAIN::Uint32& P_length,
                              char*& P_sVal,
                              BF_status& P_status) const;
   // In read mode, gets the value of the attribute typed OBJECT
   // IDENTIFIER identified by Meta Data <{P_msgElem}>, from <{this}>
   // Local Representation, sets <{P_sVal}> to this value and
   // <{P_length}> to its length.

   // In case the object identifier has no size limit and the value that
   // was given to it exceeds the BF internal limit, the only effect is
   // that <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.
   
   virtual void getBasicValue(const BF_MDMsgElem& P_msgElem,
                              const BF_LRIterator *P_iter,
                              HPAIN::Uint32& P_length,
                              char*& P_sVal,
                              BF_status& P_status) const;
   // In read mode, gets the value of the attribute typed OBJECT
   // IDENTIFIER identified by Meta Data <{P_msgElem}> and Iterator
   // <{P_iter}>, from <{this}> Local Representation, sets <{P_sVal}> to
   // this value and <{P_length}> to its length. 

   // In case the object identifier has no size limit and the value that
   // was given to it exceeds the BF internal limit, the only effect is
   // that <{P_length}> is set to the length needed and <{P_status}> to
   // BF_Status::ALLOCATE_BUFFER. Thus, the user has to call the
   // appropriate getUnlimitedValue function with a buffer for storing
   // the result: this buffer is fully handled by the user and its
   // length must be at least <{P_length}>.
   
   virtual void getUnlimitedValue(const BF_MDMsgElem& P_msgElem,
                                  HPAIN::Uint32& P_length,
                                  HPAIN::Uint32& P_remLength,
                                  void* P_buf,
                                  BF_status& P_status) const;

   // In read mode and for unlimited types only, get the value of the
   // attribute identified by Meta Data <{P_msgElem}> from <{this}>
   // Local Representation, write it into the user's buffer <{P_buf}>
   // and set <{P_length}> to the length of read data.

   // For unlimited bit strings and octet strings only, in case
   // <{P_buf}> is too short a buffer, <{P_status}> is set to
   // BF_Status::MORE_DATA, <{P_length}> to the length that could be
   // actually written into <{P_buf}> and <{P_remLength}> to the length
   // of the data that could not be read. Then, the same function may be
   // called iteratively until <{P_remLength}> is 0.

   virtual void getUnlimitedValue(const BF_MDMsgElem& P_msgElem,
                                  const BF_LRIterator *P_iter,
                                  HPAIN::Uint32& P_length,
                                  HPAIN::Uint32& P_remLength,
                                  void* P_sVal,
                                  BF_status& P_status) const;

   // In read mode and for unlimited types only, get the value of the
   // attribute identified by Meta Data <{P_msgElem}> and Iterator
   // <{P_iter}> from <{this}> Local Representation, write it into the
   // user's buffer <{P_buf}> and set <{P_length}> to the length of read
   // data.

   // For unlimited bit strings and octet strings only, in case
   // <{P_buf}> is too short a buffer, <{P_status}> is set to
   // BF_Status::MORE_DATA, <{P_length}> to the length that could be
   // actually written into <{P_buf}> and <{P_remLength}> to the length
   // of the data that could not be read. Then, the same function may be
   // called iteratively until <{P_remLength}> is 0.

   virtual HPAIN::Boolean isValid(BF_status& P_status) const;
   // Returns a boolean indicating whether <{this}> has been sucessfully
   // created. This method should be called after every creation of a
   // Local Representation.
   
   friend ostream& operator<< (ostream& P_os, const BF_LRMsg& P_locRep);
   friend ostream& operator<< (ostream& P_os, const BF_LRMsg* P_locRep);
   // Outputs content of <{this}>, takes either a reference or a
   // pointer.
   
   static void enableOverload();
   static void disableOverload();
   // Enables or disables overloading a decoded Local Representation,
   // N.B. The SCP mode is not affected by this enable/disable mode.
   
   static HPAIN::Uint8 bcdFiller();
   // For BCD management, returns an octet containing the BCD filler
   // common to all Local Representations, default filler is 0x0.

   static HPAIN::Boolean bcdDoPadding();
   // For BCD management, returns a boolean indicating whether a padding
   // string has to be added to the end of BCD values.
  
   static HPAIN::Uint8 bcdPadValue();
   // For BCD management, returns an octet containing the BCD pad value
   // common to all Local Representations, default filler is 0x0.
   
   static void defineBcdFormat(HPAIN::Uint8 P_fillerValue=0, 
                               HPAIN::Boolean P_doPadding=HPAIN::bFalse, 
                               HPAIN::Uint8 P_padValue=0);
   // For initiating BCD management, positions the filler value (default
   // value 0x0), the pad value (default value 0x0) and mode with/without 
   // padding (default is without).

   // to return the implementation object
   BF_LRMsg_impl* getImplementedPart() const;

protected:
   // pointer to the implementation object : so BF_LRMsgScp can retrieve it
   BF_LRMsg_impl* hidden; 

   // Constructors used by derivated classes.
   BF_LRMsg(const BF_MDMsg& P_msg, kind P_type);
   BF_LRMsg(const BF_MDMsg* const P_msg, kind P_type);
   BF_LRMsg(const BF_MDMsg* P_msg, kind P_type,HPAIN::Uint32 P_disc);
   
private:
   // to prevent public copy ctor usage: no implementation
   BF_LRMsg(const BF_LRMsg&); 

   // to prevent public operator= usage: no implementation
   BF_LRMsg& operator=(const BF_LRMsg& P_rhs);

   friend class BF_BERCoDec;          // this one actually needed
   friend class BF_MFVOCoDec;         // this one needed too
   friend class BF_PCMOCoDec;         // this one needed too
   friend class BF_PERCoDec;          // this one needed too
};

#endif // BF_LRMsg.h

// = LIBRARY
//  $(BabelfDM)
//
// = FILENAME
//  BF_LRMsg.h
//
// = NOTE
//
// = SEE ALSO
//  BF_LRMsgScp class, BF_LRIterator class.
