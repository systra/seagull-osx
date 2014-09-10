// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_Message
//                               -----------------------
//
//
//  PURPOSE: Obsolete default Allocator for data buffers chained in PCA messages.
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_MallocBufferAllocator.h
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
//       $Source: /SLEE/code/PLUGIN_Message/PCA_MallocBufferAllocator.h $
//       $Revision: 1.8 $
//       
//----------------------------------------------------------------------------
// end_is

#ifndef __MALLOCBUFFERALLOCATOR_H
#define __MALLOCBUFFERALLOCATOR_H


#include "PCA_BufferAllocator.h"

/*
__________________________________________________________________________

         C L A S S    M a l l o c B u f f e r A l l o c a t o r
__________________________________________________________________________
*/

/**
 * Obsolete default Allocator for data buffers chained in PCA messages.
 * Allocates and free data buffers chained in PCA messages.
 *
 * This class is OBSOLETE.
 * It is provided only for compatibility needs
 * and is no more supported.
 * Do prefer the default implementation of the PCA_BufferAllocator class.
 *
 * @short Old default data buffer allocation.
 */

class PCA_MallocBufferAllocator : public PCA_BufferAllocator {
public:
   /**
    * Constructor.
    */
   PCA_MallocBufferAllocator() {};
	
   /**
    * Destructor.
    */
   ~PCA_MallocBufferAllocator() {};
};


#endif // __MALLOCBUFFERALLOCATOR_H
