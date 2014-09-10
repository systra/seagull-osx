// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_ExecApi
//                               -----------------------
//
//
//  PURPOSE: PIC plug-in HA interface.
//
//  NOTES and CAUTIONS:
//
//  FILE : PIC_PluginHA.h
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
//       $Source: /SLEE/code/PLUGIN_ExecApi/PIC_PluginHA.h $
//       $Revision: 1.3 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PIC_PLUGIN_HA_H)
#define __PIC_PLUGIN_HA_H

#include <PLUGIN_Common.h>


/*
__________________________________________________________________________

              C L A S S    P I C _ P l u g i n H A
__________________________________________________________________________
*/

class PIC_PluginHAImpl;

/**
 * PIC plug-in HA interface class.
 *
 * This class is divided into virtual members that are intended to be re-fined
 * by the plug-in developer to implement the HA interface of the
 * plug-in, and non virtual members that offer some HA services to the
 * plug-in.
 * An instance of a user plug-in class derived from this class can
 * be declared in the structure pointed by the argument of the user-defined
 * piSetup() function.
 *
 * @short Plugin HA interface.
 */
class PIC_PluginHA {
public:

   /**
    * State completion type.
    *
    * Defines the completion types of an HA FSM state.
    * Values have the following meaning:
    *    @li PENDING - The HA FSM state will not terminate automatically.
    *    @li DONE - The HA FSM state will terminate automatically.
    *    @li SYNC - The HA FSM state will terminate with need of synchronization.
    *
    * The PENDING state completion type is only possible if the current
    * HA FSM state is a plug-in driven state like FTC_SWITCHING,
    * FTC_SYNCHRONISING or FTC_STOPPING.
    * The SYNC state completion type is only possible if the current
    * HA FSM state is FTC_STOPPING.
    *
    * If the current HA FSM state is FTC_STOPPING the next one will be:
    *    @li FTC_HOT_STANDBY - with a DONE state completion type.
    *    @li FTC_COLD_STANDBY - with a SYNC state completion type.
    *
    * @see #newState
    * @see #stateCompleted
    */
   enum StateCompletionType { PENDING=0 , DONE, SYNC };

   /**
    * Destructor.
    */
   virtual ~PIC_PluginHA();

public:
// +-------------------------------------------------------------------------+
// + The following functions are intended to be specialized for each plug-in +
// +-------------------------------------------------------------------------+

   /**
    * Notifies the plug-in about a HA FSM state transition.
    *
    * FTC_BOOTING and FTC_DOWN HA FSM states are not notified by this
    * function but by init and close functions of the PIC_PluginExe class.
    *
    * The PIC will manage the next HA FSM state transition after newState
    * function returns depending on the returned plug-in state completion
    * type.
    * The PENDING state completion type can only be returned if the current
    * HA FSM state is a plug-in driven state like FTC_SWITCHING,
    * FTC_SYNCHRONISING or FTC_STOPPING.
    * The SYNC state completion type can only be returned if the current
    * HA FSM state is FTC_STOPPING.
    * 
    * Default implementation returns DONE.
    *
    * @param P_newState requested new HA FSM state
    * @return plug-in state completion type
    * @see #getState
    * @see #stateCompleted
    * @see #fault
    * @see PIC_PluginExe#init
    * @see PIC_PluginExe#close
    */
   virtual StateCompletionType newState(const PLUGIN::ProcessState P_newState);

   /**
    * Set the state completion type for a plug-in driven HA FSM state.
    *
    * This function can only be used if the current state completion type
    * is PENDING.
    * State completion type can be set to DONE for all plug-in driven
    * HA FSM states or to SYNC for FTC_STOPPING HA FSM state.
    *
    * @param P_stateCompletionType the state completion type to set
    * @see #newState
    */
   void stateCompleted(const StateCompletionType P_stateCompletionType=DONE);

public:
// +-------------------------------------------------------------------+
// + The following functions are made available to the plug-in writter +
// +-------------------------------------------------------------------+

   /**
    * Get the current HA FSM state.
    *
    * @return current HA FSM state
    * @see #newState
    */
   PLUGIN::ProcessState getState() const;

   /**
    * Notifies the PIC about an internal failure.
    *
    * Calling this function makes the whole PIC go down.
    * If PIC process is HA, this triggers a switch-over of the platform.
    * The next HA FSM state will be FTC_DOWN.
    *
    * @see PIC_PluginExe#close
    */
   void fault();


protected:
   /**
    * Constructor.
    *
    * Protected because PIC_pluginHA object is intended to be inherited by the
    * plug-in HA implementation class.
    *
    * @see PIC_PluginExe#piSetup
    */
   PIC_PluginHA();


private:
   /**
     * Implementation of the PIC_pluginHA.
     */
   PIC_PluginHAImpl* const impl;

};

#endif // __PIC_PLUGIN_HA_H
