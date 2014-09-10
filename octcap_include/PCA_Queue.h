// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: Provides queue of messages, with two levels watermark.
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Queue.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Queue.h $
//       $Revision: 1.9 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_QUEUE_H)
#define __PCA_QUEUE_H

#ifndef __GNUC__
#if __cplusplus <= 199707L
typedef int bool;
#endif
#endif /* __GNUC__ */


/*
__________________________________________________________________________

              C L A S S    P C A _ Q u e u e
__________________________________________________________________________
*/

class PCA_Message;
class PCA_QueueImpl;

/**
 * Provides queue of messages, with two levels watermark.
 *
 * The queue is said "overflowed" when its filling exceeds the high watermark.
 * It returns from this state when its filling drops to or below the low watermark
 *
 * @short Queue of messages with two levels watermark.
 */
class PCA_Queue {
   friend class PCA_QueueImpl;

public:

   /**
     * Macro-Constructor.
     *
     * Builds a parameterized queue object.
     * 0<=P_lowWatermark<=P_highWatermark<size
     *
     * @param P_size size of the queue
     * @param P_highWatermark threshold for overflow condition
     * @param P_lowWatermark threshold for overflow condition completion
     * @return pointer to the new queue if the operation succeded, or NULL
     */
   static PCA_Queue* create(
      unsigned P_size, unsigned P_highWatermark, unsigned P_lowWatermark
   );

   /**
     * Destructor.
     *
     * Destroys the queue object, together with all pending messages
     */
   ~PCA_Queue();

   /**
     * Puts a message at the tail of the queue.
     *
     * Precondition: queue is not full
     *
     * @param P_message message to be pushed
     * @see #get
     * @see #isFull
     */
   void put(PCA_Message* P_message);

   /**
     * Gets the the message from the head of the queue.
     *
     * Precondition: queue is note empty
     *
     * @return retrieved message
     * @see #put
     * @see #unget
     * @see #isEmpty
     */
   PCA_Message* get();

   /**
     * Puts back a message at the head of the queue.
     *
     * Precondition: last action on the queue retrieved the message
     *
     * @see #get
     */
   void unget();

   /**
     * Delete all pending messages in the queue.
     */
   void flush();

   /**
     * Is queue overflowed ?
     *
     * The queue is said to be overflowed if its filling did not drop back
     * the low watermark threshold since it last exceeded the high watermark
     *
     * @return true if overflowed, false otherwise.
     */
   bool isOverflowed();

   /**
     * Obsolete isOverflown function,
     *
     * This function is OBSOLETE.
     * It is provided only for compatibility needs
     * and is no more supported.
     * Do prefer the previous one.
     *
     * @return true if overflowed, false otherwise.
     */
   bool isOverflown() { return(isOverflowed()); };

   /**
     * Is queue empty ?
     *
     * @return true if empty, false otherwise.
     * @see #get
     */
   bool isEmpty();

   /**
     * Is the queue full ?
     *
     * @return true if full, false otherwise.
     * @see #put
     */
   bool isFull();

   /**
     * Number of messages in the queue.
     *
     * @return see definition
     */
   unsigned getSize();


protected:
   /**
     * Constructor
     *
     * Builds a queue object (called by macro-constructor)
     * User should call the macro-constructor instead
     */
   PCA_Queue();

   /**
     * Initialization (called by macro-constructor)
     *
     * Initializes a queue object, with its size and watermark parameters
     *
     * @param P_size size of the queue
     * @param P_highWatermark threshold for overflow condition
     * @param P_lowWatermark threshold for overflow condition completion
     * @param P_autoFlowControl flag driving automatic flow control management
     * @return 0 if operation succeeded, 1 otherwise
     */
   int init(
      unsigned P_size, unsigned P_highWatermark, unsigned P_lowWatermark,
      bool P_autoFlowControl
   );


private:
   /**
     * Implementation of the server
     */
   PCA_QueueImpl* const impl;

   /**
     * Effective C++
     *
     * To prevent public copy ctor usage: no implementation
     */
   PCA_Queue(const PCA_Queue&);

   /**
     * Effective C++
     *
     * To prevent public operator= usage: no implementation
     */
   PCA_Queue& operator=(const PCA_Queue&);
};

#endif // __PCA_QUEUE_H

