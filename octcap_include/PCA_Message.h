// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE  PLUGIN_Message
//                               ----------------------
//
//
//  PURPOSE: Provides messages of Plug-in Communication API.
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Message.h
//____________________________________________________________________________
//
// Copyright (c) 1996 Hewlett-Packard Company, All Rights Reserved.
// RESTRICTED RIGHTS LEGEND Use, duplication, or disclosure by the U.S.
// Government is subject to restrictions as set forth in sub-paragraph
// (c)(1)(ii) of the Rights in Technical Data and Computer Software
// clause in DFARS 252.227-7013.
//
// Hewlett-Packard Company
// 3000 Hanover Street
// Palo Alto, CA 94304 U.S.A.
// Rights for non-DOD U.S. Government Departments and Agencies are as
// set forth in FAR 52.227-19(c)(1,2).
//____________________________________________________________________________
//
//
//  AUTHOR:
//                                               DATE: 
//
//  Rev: 
//       $Source: /SLEE/code/PLUGIN_Message/PCA_Message.h $
//       $Revision: 1.21 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_MESSAGE_H)
#define __PCA_MESSAGE_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#ifdef __GNUG__
#include <new>
#include <stdexcept>
#endif // __GNUG__
#include <inttypes.h>
#if (__cplusplus >= 199707L || __GNUG__ )
#include <string>
#ifdef _HP_NAMESPACE_STD
    using namespace std;
#endif
typedef string Str;
#else
#include <UslString.h>
typedef String Str;
#endif

#include <PCA_Common.h>

// Migration to HP-UX 11.0/32 bits
// The following macro replaces all size_t expressions that are 11/32-safe
// UX11-32MIGR : CrCh275 : NONE
#define SIZE_T size_t


/*
__________________________________________________________________________

              C L A S S    P C A _ M e s s a g e
__________________________________________________________________________
*/

class PCA_Session;
class PCA_Message_impl;
class PCA_BufferAllocator;


/**
 * Provides messages of Plug-in Communication API.
 *
 * This class inherits publically from PCA_BufferArray that provides rough
 * linked data buffers.
 * It adds definition and handling capability for PCA structured messages.
 *
 * @short Handling of PCA structured messages
 */
class PCA_Message {
public:
   /**
    * Definition of message types
    *
    * @see #getType
    * @see #getHeader
    * @see #putHeader
    * @see #DataHeader
    * @see #ErrorHeader
    */
   enum MessageType { UNKNOWN, DATA, ERROR };

   /**
    * Definition of data message types
    *
    * @see #DataHeader
    * @see #getHeader
    * @see #putHeader
    */
   enum DataType { PRIVATE, DDL, BER };

   /**
    * Structure of data message headers
    *
    * @see #getHeader
    * @see #putHeader
    */
   struct DataHeader {       // Structure of data message header
      DataHeader() : type(DATA), session(0) {};
      MessageType   type;      // Type of the message: DATA
      PCA_Session*  session;   // Pointer to the session object
      DataType      dataType;  // Type of the data
      uint32_t msgSetId;  // Message set identifier
      uint32_t messageId; // Message identifier within the message set

      uint32_t birthDate;
      // Date of message creation (applies only to inbound messages)
      // If profiling is activated by setting global variable G_pcaProfile to 1,
      // this is set automatically by the PCA when a message is received, using
      // gettimeofday() in ms. 
      // Otherwise this is set to 0
   };

   /**
    * Structure of error message headers
    *
    * @see #getHeader
    * @see #putHeader
    */
   struct ErrorHeader {      /* Structure of error message header */
      ErrorHeader() : type(ERROR), session(0) {};
      MessageType   type;      /* Type of the message: ERROR */
      PCA_Session*  session;   // Pointer to the session object
      PCA_Status    errorCode; // Reason for the failure
   };


public:



public:
   /**
    * Constructor
    *
    * @param P_allocator pointer to the buffer allocator to use
    */
   PCA_Message(PCA_BufferAllocator* P_allocator);
   /**
    * Constructor
    * 
    * @param P_size initial size
    * @param P_allocator pointer to the buffer allocator to use
    */
   PCA_Message(SIZE_T P_size, PCA_BufferAllocator* P_allocator);
   /**
    * Destructor
    *
    */
   virtual ~PCA_Message();

   /**
    * Peek copies a number of bytes from a given offset.
    *
    * It does not affect message read and write pointers.
    *
    * @param P_offset initial offset
    * @param P_size number of bytes to copy
    * @param P_dest pointer to destination buffer
    * @return number of bytes copied
    */
   SIZE_T peek(SIZE_T P_offset, SIZE_T P_size, char* P_dest) const;

   /**
    * Peek copies all bytes from a given offset.
    *
    * It does not affect message read and write pointers.
    *
    * @param P_offset initial offset
    * @param P_dest pointer to destination buffer
    * @return number of bytes copied
    */
   SIZE_T peek(SIZE_T P_offset, char* P_dest) const;

   /**
    * Read copies a number of bytes from the current message read pointer.
    *
    * Message read pointer is affected by this operation.
    *
    * @param P_size number of bytes to copy
    * @param P_dest pointer to destination buffer
    * @return number of bytes copied
    */
   SIZE_T read(SIZE_T P_size, char* P_dest);

   /**
    * Read copies all bytes from the current read pointer.
    *
    * Message read pointer is affected by this operation.
    *
    * @param P_dest pointer to destination buffer
    * @return number of bytes copied
    */
   SIZE_T read(char* P_dest);

   /**
    * Read copies a number of bytes from the current message read pointer.
    *
    * Message read pointer is affected by this operation.
    *
    * @param P_size number of bytes to copy
    * @param P_dest reference of the destination string
    * @return number of bytes copied
    */
   SIZE_T read(SIZE_T P_size, Str& P_dest);

   /**
    * Read copies all bytes from the current read pointer.
    *
    * Message read pointer is affected by this operation.
    *
    * @param P_dest reference of the destination string
    * @return number of bytes copied
    */
   SIZE_T read(Str& P_dest);

   /**
    * Write copies a number of bytes to the current message write pointer.
    *
    * Message write pointer is affected by this operation.
    *
    * @param P_size number of bytes to copy
    * @param P_from pointer to source buffer
    * @return number of bytes copied
    */
   SIZE_T write(SIZE_T P_size, const char* P_from);

   /**
    * Write copies the bytes of a string to the current message write pointer.
    *
    * Message write pointer is affected by this operation.
    *
    * @param P_from reference of the source string
    * @return number of bytes copied
    */
   SIZE_T write(const Str& P_from);

   /**
    * WriteAtHead copies a number of bytes to the message head
    *
    * @param P_size number of bytes to copy
    * @param P_from pointer to source buffer
    * @return number of bytes copied
    */
   SIZE_T writeAtHead(SIZE_T P_size, const char* P_from);

   /**
    * Skips a number of readable bytes
    *
    * Message read pointer is affected by this operation.
    *
    * @param P_size number of skipped bytes
    */
   void skip(SIZE_T P_size);


   /**
    * Cuts a number of written bytes at the tail of the message
    *
    * Message write pointer is affected by this operation.
    *
    * @param P_size number of cut bytes
    */
   void shrink(SIZE_T P_size);

   /**
    * Message chaining.
    *
    * Adds a message at the tail of the current one.
    * If reading of the current message is exhausted, read pointer is
    * set to the beginning of the new one buffer.
    * Otherwise it remains unchanged.
    * The additionnal message object is left empty and should be deleted or
    * re-used
    *
    * @param P_message pointer to the message to be chained
    * @return Number of successfully added bytes (may be 0 or the size of the
    *         additionnal message)
    */
   SIZE_T append(PCA_Message* P_message);

   /**
    * Get the first data buffer of the chain.
    * 
    * @param P_size output parameter that returns the size of the data buffer
    * @return pointer to first data buffer, or NULL if end of chain is reached
    */
   const char* getFirstDb(SIZE_T& P_size);

   /**
    * Walk through the chain of data buffers
    * 
    * @param P_size output parameter that returns the size of the data buffer
    * @return pointer to current data buffer, or NULL if end of chain is reached
    */
   const char* getNextDb(SIZE_T& P_size);

   /**
    * Add bytes at the tail of the message.
    *
    * Message write pointer is affected by this operation.
    *
    * This function attempts to find a free area at the tail of the message,
    * or allocates a new one. This chunk is then considered as a readable
    * part of the message.
    * The area, together with its size, is returned to the user that is
    * intended to put meaningfull bytes in it.
    *
    * @param P_size the requested size as input and the actual size as output
    * @return the base address of the additional area, or NULL if failure
    */
   const char* paste(SIZE_T& P_size);

   /**
    * Destroys the whole chain of data buffers
    */
   void erase();

   /**
    * Empties the whole chain of data buffers
    *
    * This can be used for re-cycling existing buffers
    */
   void reset();

   /**
    * Size (in bytes) of the message
    *
    * This must not be confused with the amount of data within the buffer
    *
    * @return the total message size
    * @see #getDataSize
    */
   SIZE_T getTotalSize() const;

   /**
    * Amount of data in the buffer
    *
    * This is computed from read and write pointers, and is lower than the
    * size of the whole message
    *
    * @return the amount of data in the buffer
    * @see #getTotalSize
    */
   SIZE_T getDataSize() const;

   /**
    * Dumps the contents of a buffer (for debugging purpose)
    */
   void dump();

   /**
    * Message type retrieval.
    *
    * This function must be called prior to getSession() and getHeader() on
    * a message which type is unknown.
    * It does not affect underlying PCA_ArrayBuffer read pointer and can be
    * called as many times as required.
    *
    * Status is updated as follows:
    * @li NO_ERROR - Operation succeeded
    * @li MSG_UNKNOWN - Operation failed, message type is unknown
    * @li MSG_BAD - Operation failed, message structure is bad
    *
    * @param P_status result of the operation
    * @return Type of the message
    * @see #getSession
    * @see #getHeader
    */
   MessageType getType(PCA_Status& P_status) const;

   /**
    * Message session retrieval
    *
    * This function can be called for a message which type is either DATA or
    * ERROR.
    * It does not affect underlying PCA_ArrayBuffer read pointer and can be
    * called as many times as required.
    * It performs no sanity checks on the return session pointer
    *
    * @return Pointer to the session object associated to the message
    * @see #getType
    */
   PCA_Session* getSession();
    
   /**
    * Data message building.
    *
    * Adds a data header to the payload part of a message
    * The function makes a safe copy of the provided header
    * It does not check the consistency of header fields
    * It must be called only once for each outgoing message
    *
    * Status is updated as follows:
    * @li NO_ERROR  - Operation succeeded
    * @li ..error.. - Operation failed for specified reason
    *
    * @param P_dataHeader header for data message
    * @param P_status result of the operation
    */
   void putHeader(const DataHeader& P_dataHeader, PCA_Status& P_status);

   /**
    * Error message building.
    *
    * Adds a error header to the payload part of a message
    * The function makes a safe copy of the provided header
    * It does not check the consistency of header fields
    * It must be called only once for each outgoing message
    *
    * Status is updated as follows:
    * @li NO_ERROR  - Operation succeeded
    * @li ..error.. - Operation failed for specified reason
    *
    * @param P_errorHeader header for an error message
    * @param P_status result of the operation
    */
   void putHeader(const ErrorHeader& P_errorHeader, PCA_Status& P_status);

   /**
    * Extracts the data header of a data message
    *
    * Prerequisite: getType() succeeded for this message, and function is
    * called with the resulting header paramater
    * The function does not check the consistency of header fields
    * On return, the underlying buffer points to the payload part of
    * the initial message
    * This function must be called only once for each incoming message
    *
    * @param P_dataHeader header for data message
    * @see #getType
    */
   void getHeader(DataHeader& P_dataHeader);

   /**
    * Extracts the error header of an error message
    *
    * Prerequisite: getType() succeeded for this message, and function is
    * called with the resulting header paramater
    * The function does not check the consistency of header fields
    * On return, the underlying buffer points to the payload part of
    * the initial message
    * This function must be called only once for each incoming message
    *
    * @param P_errorHeader header for an error message
    * @see #getType
    */

   void getHeader(ErrorHeader& P_errorHeader);
	

	/* initialize the PCA_Message ObjectPool
	* @param P_size zize of the pool
	*/

static  int initObjectPool(unsigned P_size);   



#if !defined(DONT_USE_MEM_HANDLER)

	#if (__cplusplus >= 199707L || __GNUG__)//aCC
	/**
    * New operator
    */
	void *operator new( size_t P_size ) throw(bad_alloc);\
    /**
    * New(nothrow) operator
    */
	void *operator new( size_t P_size , const nothrow_t &P_nothrow) throw();\
	/**
	* Delete operator
	*/
	void  operator delete( void *P_object ) throw();
	
	#else //cfront
	/**
    * New operator
    */

	void* operator new(size_t P_size);              
	/**
	* Delete operator
	*/
	void operator delete(void* P_object);           
	#endif //__cplusplus >= 199707L

#endif //DONT_USE_MEM_HANDLER

protected:


private:
   PCA_Message_impl* rep; // Pointer to the associated implementation

};



#undef SIZE_T
#endif // __PCA_MESSAGE_H
