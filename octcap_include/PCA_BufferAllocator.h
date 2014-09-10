// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_Message
//                               -----------------------
//
//
//  PURPOSE: Allocates and free data buffers chained in PCA messages.
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_BufferAllocator.h
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
//       $Source: /SLEE/code/PLUGIN_Message/PCA_BufferAllocator.h $
//       $Revision: 1.11 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__BUFFERALLOCATOR_H)
#define __BUFFERALLOCATOR_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

//Exception implementation
#ifndef USE_USL

 
#include <new>
#ifdef _HP_NAMESPACE_STD
    using namespace std;
#endif
#endif

#include <stdlib.h>

// Migration to HP-UX 11.0/32 bits
// The following macro replaces all size_t expressions that are 11/32-safe
// UX11-32MIGR : CrCh275 : NONE
#define SIZE_T size_t


/*
__________________________________________________________________________

        C L A S S     B u f f e r A l l o c a t o r
__________________________________________________________________________
*/

/**
 * Allocates and free data buffers chained in PCA messages.
 *
 * This class is an abstract base class to be derived by user to define its
 * own allocator.
 * Default implementation of this class allocates and frees memory using
 * the new and delete operator.
 *
 * @short Data buffer allocation.
 */

class PCA_BufferAllocator {
public:

   /**
    * Default constructor.
    */
   PCA_BufferAllocator();
   
   /**
    * Virtual destructor.
    */
   virtual ~PCA_BufferAllocator();

   /**
    * Data buffer allocation.
    *
    * Allocates a data buffer depending on the requested size.
    * The new buffer size may be smaller or equal or greater than the requested
    * one, depending on allocator implementation and the managed memory pool.
    *
    * @param P_size holds the requested size in byte of the buffer, returns the
    *               actual size of the allocated buffer, or 0
    * @return pointer to the new data buffer, or NULL in case of failure.
    * @see #free
    */
   virtual void* alloc(SIZE_T& P_size);

   /**
    * Buffer release.
    *
    * Free a data buffer previously allocated by alloc().
    *
    * @param P_buffer pointer to the data buffer to be released
    * @see #alloc
    */
   virtual void free(void* P_buffer);


private:
   // = Disallow these operations.
   PCA_BufferAllocator &operator= (const PCA_BufferAllocator &);
   PCA_BufferAllocator (const PCA_BufferAllocator &);
};


#undef SIZE_T
#endif // __BUFFERALLOCATOR_H
