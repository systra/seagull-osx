// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_Common
//                               ----------------------
//
//
//  PURPOSE: Define Plug-in common data and tools
//
//  NOTES and CAUTIONS:
//
//  FILE : PLUGIN_Common.h
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
//       $Source: /SLEE/code/PLUGIN_Common/PLUGIN_Common.h $
//       $Revision: 1.5 $
//       
//----------------------------------------------------------------------------
// end_is


#ifndef __PLUGIN_COMMON_H
#define __PLUGIN_COMMON_H

/**
 * Define Plug-in common data and tools
 *
 * @short Plug-in common data and tools
 */
class PLUGIN {
public:
   //--------------------------------------------------------------------------
   // Process states as reported to and by the Fault Tolerant Controller
   //--------------------------------------------------------------------------
  
   /**
    * Definition of Plug-in container HA FSM states 
    */
   enum ProcessState {
      FTC_UNKNOWN=0,
      FTC_DOWN,
      FTC_BOOTING,
      FTC_COLD_STANDBY,
      FTC_SYNCHRONISING,
      FTC_HOT_STANDBY,
      FTC_SWITCHING,
      FTC_STOPPING,
      FTC_ACTIVE,
      FTC_MIXED,
      FTC_INVALID_STATE
   };

   /**
    * Convert a HA FSM state in text.
    *
    * @param P_state the HA FSM state to convert
    * @return a pointer to the text of the HA FSM state
    */
   static char* string(ProcessState P_state)
   {
      switch (P_state) {
         case FTC_UNKNOWN:       return "UNKNOWN";
         case FTC_DOWN:          return "DOWN";
         case FTC_BOOTING:       return "BOOTING";
         case FTC_COLD_STANDBY:  return "COLD STANDBY";
         case FTC_SYNCHRONISING: return "SYNCHRONISING";
         case FTC_HOT_STANDBY:   return "HOT STANDBY";
         case FTC_SWITCHING:     return "SWITCHING";
         case FTC_STOPPING:      return "STOPPING";
         case FTC_ACTIVE:        return "ACTIVE";
         case FTC_MIXED:         return "MIXED";
         case FTC_INVALID_STATE: return "INVALID";
         default:                return "ERROR";
      }
   }
};

#endif // __PLUGIN_COMMON_H

