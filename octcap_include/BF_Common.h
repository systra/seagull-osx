//  Copyright (C) Hewlett-Packard Company, 1995, 1996.

// begin_is
//------------------------------------------------------------------------------
//
//                               MODULE   BF_Common.h
//                               --------------------
//
//
//  PURPOSE: 
//
//  NOTES and CAUTIONS:
//
//  FILE : /users/eric/BabelF/code/Common/BF_Common.h
//____________________________________________________________________________
//
//
//  AUTHOR: Eric Julien 
//                                               DATE: Mon May 29 11:18:25 1995
//
//----------------------------------------------------------------------------
//  HISTORY:
//
//  Date       Modification Location              Summary              Name
//  ----       ---------------------              -------              ----
//                First Version                                             
//----------------------------------------------------------------------------
// end_is

#ifndef BF_COMMON_H
#define BF_COMMON_H

#include <OC/oc_config.h>
#include <OC/oc_stream.H>

#define ERROR WIN32_ERROR
#define SIZE  WIN32_SIZE
#include <ainCppCommon.h>
#undef ERROR
#undef SIZE

#if ((__cplusplus>=199707L) && (!defined(_WIN32))) || defined(__GNUG__)
#define CONSTCAST(_t)   const_cast<_t>
#else
#define CONSTCAST(_t)   (_t)
#endif // __cplusplus>=199707L

//
// Define a MACRO for new operator
//
#if __cplusplus >= 199707L && !defined(__HPACC_NOEH) || defined(__GNUG__)
#define NEW new(nothrow)
#include <new>
#else
#define NEW new
#endif 

class BF_MDMsgSet_impl;
class BF_MDMsg_impl;
class BF_MDMsgElem_impl;
class BF_MDOperation_impl;

//----------------------------------------------------------------------------
// Babel Fish Specific Types
//----------------------------------------------------------------------------

enum BF_boolean { BFalse=0, BTrue=1 };

ostream& operator<< (ostream& P_os, BF_boolean P_value);

typedef HPAIN::Uint32	BF_identifier;
typedef HPAIN::Int32		BF_scalar;

class BF_Type {
public:
   enum kind { 
	SEQUENCE, SET, SEQUENCE_OF, SET_OF,	// pure ASN.1 specification
	CHOICE, ANY, OBJECT_ID, OCTET_STRING, 	// pure ASN.1 specification
	BIT_STRING, ENUM, INTEGER, BOOLEAN, 	// pure ASN.1 specification
	EMPTY,					// pure ASN.1 specification
	BCD_STRING,				// BF ASN.1+ specification
	BMP_STRING,				// BF ASN.1+ specification
	PACKED_BIN,				// BF ASN.1+ specification
	PSEUDO, 				// Pseudo attribute
	SHIFT_INTEGER,				// BF ASN.1+ specification
	UNKNOWN					// Not supported
   };
   friend ostream& operator<< (ostream& P_os, BF_Type::kind P_type);
};

//----------------------------------------------------------------------------
// Babel Fish Specific Constants
//----------------------------------------------------------------------------

// maximum number of Message set supported
const HPAIN::Uint16 BF_maxMsgSet = 16;	

// DAmaximum number of CODEC supported
const HPAIN::Uint16 BF_maxCoDec = 3;

// temporary const for bcd filler: should be in config
const HPAIN::Int32 BF_bcdFiller = 0xF0;

//----------------------------------------------------------------------------
// Babel Fish SCP Specific Types
//----------------------------------------------------------------------------

class BF_DDLtype {
public:
   enum kind { 
      ARRAY, RECORD, UNION, ANY, ENUM, 
      OBJECT_ID, STRING, BCD, BMP, BIT_STRING, INTEGER, BOOLEAN, UNKNOWN
   };
};

class BF_scpGenType {
public:
   union _scpGenType{
      HPAIN::Int32 scalar;
      char* stringPtr;
      void* anyPtr;
      struct _bitString {
         HPAIN::Uint32 nbPad;
         char* valuePtr;
      } bitString;
   }scpGenType;
};


//----------------------------------------------------------------------------
// Babel Fish error class
//----------------------------------------------------------------------------

class BF_status {
public:

   enum Status {
      NO_ERROR,                 // no error
      NO_MGR,                   // mgr not initialized
      NO_CODEC,                 // no such codec
      NO_MSGSET,                // no such message set
      NO_MSGELEM,               // no such message element
      NO_MSG,                   // no such message
      NO_OPERATION,             // no such operation
      NO_ITERATOR,              // no such iterator
      NO_LRMSG,                 // no such local representation
      NO_TRMSG,                 // no such transfer representation
      EMPTY_TRMSG,              // empty transfer representation
      TOO_MANY_TRMSG,           // too many transfer representation allocated
      IS_BFTYPE,                // the container is the BFType itself
      ERROR_ENCODE,             // error during BFType encoding
      ERROR_DECODE,             // error during BFType decoding
      NO_PRIVATE,               // no private info for this BFtype
      TYPE_NOT_SUPPORTED,       // data type not supported
      NOT_YET_SUPPORTED,        // feature not yet supported
      TYPE_MISMATCH,            // in get, set (CA and BasicValue)
      ELEM_MISMATCH,            // in get, set (CA and BasicValue)
      VALUE_MISMATCH,           // in get, set (CA and BasicValue)
      INTERNAL_ERROR,           // HPAIN::Internal error associated with a diagnostic
      OPTIONAL_ABSENT,          // optional parameter is not present
      UNINIT_CHOICE,            // choice type parameter not initialized
      CHOICE_ALREADY_SET,       // choice already set to another alternative
      UNSET_TRANSFER_DATA,      // Transfer representation as not been set
      INVALID_SIZE,             // size is invalid (versus maxSize)
      MISSING_ITER,             // iterator missing in list
      OP_NOT_ALLOWED,           // operation not allowed (set in RO, get in WO)
      INVALID_VALUE,            // invalid value at set operation
      INVALID_ITER_VALUE,       // invalid iterator value
      NO_FREE_ITERATOR,         // no free iterator for this LR
      ITERATOR_YET_USED,        // provided iterator yet linked to another one
      NO_DEFAULT,               // no default value for that element
      NOTHING,                  // the last one (to avoid forgetting the comma)
      LENGTH_NOT_SUPPORTED,     // Length value given in parameter not supported
      NULL_DATA_POINTER,        // NULL Data PoHPAIN::Inter given by the user
      OFFSET_TOO_BIG,           // Offset value greater than global buffer value
      MORE_DATA,                // more data to read in cache buffer
      ALLOCATE_BUFFER,          // a cache buffer managed by the user is needed
      BUFFER_TOO_SHORT          // cache buffer managed by the user is too short
   } theStatus;

   enum Diagnostic {
      NO_DIAG,                  // no diagnostic associated
      // Encoder/Decoder diagnostic Definition
      UNEXPECTED_COMPONENT,     // unexpected component of SET or SEQUENCE
      INVALID_LENGTH,           // Invalid Length of attribute
      BAD_MATRIX,               // Matrix does not correspond to the access
      MEMORY_SHORTAGE,          // memory error on call to virtual buffer 
                                // service provider
      OVERBOUND,                // decoded length greater than input buffer lg
      NO_INPUT_BUFFER,          // No data to decoded
      MAX_ELEMENT,              // Maximum number of element for a set or a 
                                // sequence are reached
      WRONG_ENCODING,           // wrong encoding input data buffer (header...)
      BIT_STRING_ERROR,         // Problem with bit string encoding
      MANDATORY_MISSING,        // missing a mandatory component of SET or SEQ
      EOC_PROBLEM,              // problem with EOC with undefined length using
      ASNEXIT_FAILED,           // problem during asnexit() execution
      REAL_ERROR,               // Error on real type encoding
      UNSATISFIED_CONSTRAINT,   // Error on constraint checking
      // Other Diagnostic
      BAD_LR_STATE,             // LRMsg is not in a valid state for action
      INVALID_INSTR, 		// inconsistent PostProc instruction
      UNKNOWN_INSTR, 		// unrecognized PostProc instruction
      MAX_IMPLEMENT_SIZE,       // implement size not respected
      // PCMO specific diagnostics
      PROTOCOL_DIS_DECODING,    // error while decoding the protocol 
				// discriminator
      CALL_REF_LENGTH_DECODING, // error while decoding the call reference
				// length
      MESSAGE_TYPE_DECODING,    // error while decoding the message type
      WRONG_INFO_VALUE,         // wrong value of an information element which
				// tag is greater than 128
      WRONG_INFO_TAG,           // wrong tag of an information element which 
				// tag is greater than 128
      WRONG_CALL_REF_LENGTH,    // call reference length greater than 
				// MAX_LEN_PCMO
      WRONG_PRAGMA_E_LENGTH,    // pragma 'e' element length greater than 127
      WRONG_LENGTH_BYTE_NUMBER, // wrong bytes number of length of a pragma 'e'
				// element : greater than an integer sizeof
      // PER specific diagnostics
      INVALID_PDU_LENGTH,       // Invalid Length of PDU
      MISSING_ENUM_VALUE,       // value to encode not in enumerated type
      VALUE_NOT_IN_TABLE,       // the constraint value is not present in the
			        // constraint table
      WRONG_CONSTRAINT,         // error while checking the constraints
      BOOLEAN_ENCODING,         // error while coding a boolean type
      INTEGER_ENCODING,         // error while coding an integer type
      OCTET_STRING_ENCODING,    // error while coding a sized octet string type
      MARKER_ENCODING,          // error while coding the extension marker
      CHOICE_ENCODING,          // error while coding a choice type index
      ENUMERATION_ENCODING,     // error while coding an enumeration type index
      CHARACTER_ENCODING,       // error while coding a character string type
      WRONG_INTEGER,            // the integer value is not within the 
				// constraint
      WRONG_BIT_STRING,         // the bit string value is larger than the 
				// constraints
      WRONG_OCTET_STRING,       // the octet string value is larger than the
				// constraints
      WRONG_CHOICE,             // wrong alternative in a choice
      WRONG_STRING_LENGTH,      // wrong length of the input character string
      WRONG_CHARACTER,          // the character to encode not in the alphabet
      INT_LENGTH_DECODING,      // error while decoding an integer value length
      REAL_FORMAT,              // real format greater than the format of the 
				// receiver
      REAL_LENGTH_DECODING,     // error while decoding a real value length
      REAL_DECODING,            // error while decoding a real value
      MANTISSA_DECODING,        // wrong mantissa length while decoding a real
				// value
      REAL_FLAG_NOT_SET,        // the flag ASNREAL should be defined
      PRECISION_LOSS,           // precision loss possible
      NOT_IMPLEMENTED,          // the current case is not yet implemented 
      PROGRAMMING_ERROR,        // programming error
      LENGTH_MULTIPLIER,        // bad length multiplier
      DEFAULT_DECODING,         // error while decoding a default value
      BOUNDS_ERROR,             // error while getting codec visible bounds
      STREAM_FRAGMENTATION,     // stream fragmentation error
      UNKNOWN_EXTENSION,        // error while decoding unsupported extension
      // Marben loadables matrixes
      LDB_DIR_OPEN_ERROR,
      LDB_DIR_CLOSE_ERROR,
      LDB_NOT_FOUND,
      LDB_OPEN_ERROR,
      LDB_EMPTY_FILE,
      LDB_BAD_SIGNATURE,
      LDB_READING_ERROR,
      LDB_DECODING_ERROR,
      LDB_LOADING_ERROR,
      LDB_NOT_COMPATIBLE,
      LDB_DEALL_ERROR
   } theDiag;

   friend ostream& operator<< (ostream& P_os, BF_status::Status P_type);

   friend ostream& operator<< (ostream& P_os, BF_status::Diagnostic P_type);

   friend ostream& operator<< (ostream& P_os, const BF_status& P_stat);

   friend ostream& operator<< (ostream& P_os, const BF_status* P_stat) {
     P_os << *P_stat; return P_os; }

   BF_status() { theStatus=NO_ERROR; theDiag=NO_DIAG; } // ctor
   BF_status(Status s) { theStatus=s; theDiag=NO_DIAG; } // ctor
   BF_status(Status s, Diagnostic d) { theStatus=s; theDiag=d; } // ctor

   // get enum value
   virtual Status getStatus() const { return theStatus; }
   // get diag value
   virtual Diagnostic getDiag() const { return theDiag; }
   // is this status a temporary setback (ie an error and not fatal)?
   // if derived BF_baseStatus object has only fatal errors it can just use
   // this version
   virtual HPAIN::Boolean isRecoverable() const { return HPAIN::bTrue; }
   // is this status an error?
   virtual HPAIN::Boolean isOk() const { return (theStatus==NO_ERROR) ? HPAIN::bTrue : HPAIN::bFalse; }
   // reset the status 
   virtual void reset() { setStatus(NO_ERROR); }
   // set the status 
   virtual void setStatus(BF_status::Status s) { 
                                         theStatus = s; theDiag = NO_DIAG; }
   virtual void setStatus(BF_status::Status s, BF_status::Diagnostic d) { 
                                         theStatus = s; theDiag = d; }

   friend class BF_MDMsgSet_impl;
   friend class BF_MDMsg_impl;
   friend class BF_MDMsgElem_impl;
   friend class BF_MDOperation_impl;
};

#endif           /* BF_COMMON_H */
