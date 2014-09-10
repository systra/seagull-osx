// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_ExecApi
//                               -----------------------
//
//
//  PURPOSE: PIC Plug-in execution interface.
//
//  NOTES and CAUTIONS:
//
//  FILE : PIC_PluginExe.h
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
//       $Source: /SLEE/code/PLUGIN_ExecApi/PIC_PluginExe.h $
//       $Revision: 1.7 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PIC_PLUGIN_EXE_H)
#define __PIC_PLUGIN_EXE_H

#ifdef __GNUC__
#include<sys/select.h>
#else
#include <Select.h>
#endif /* __GNUC__ */

class PIC_PluginHA;

/*
__________________________________________________________________________

              C L A S S    P I C _ P l u g i n E x e
__________________________________________________________________________
*/


/**
 * PIC Plug-in execution interface class.
 *
 * This class is a set of virtual members that are intended to be re-fined
 * by the plug-in developer to implement the scheduling interface of the
 * plug-in.
 * An instance of a user plug-in class derived from this class must
 * be declared in the structure pointed by the argument of the user-defined
 * piSetup() function.
 *
 * @short Plugin execution interface.
 */
class PIC_PluginExe {
public:
   /**
    * Plug-in termination mode (unused).
    *
    * Values have the following meaning:
    *    @li ABORT - plug-in is to terminate immediately
    *    @li TERMINATE - plug-in termination is requested
    *
    * @see #close
    */
   enum TerminationType { ABORT = 0, TERMINATE };

   /**
    * Plug-in processing state.
    *
    * Values have the following meaning:
    *    @li EMPTY - plug-in lets the scheduler choose (should not be used)
    *    @li IDLE - plug-in has no processing left to do
    *    @li PROCESSING - plug-in request processing time
    *
    * @see #pendingRequest
    * @see #processRequest
    */
   enum RequestState { EMPTY = 0, IDLE, PROCESSING };

   /**
    * Destructor.
    */
   virtual ~PIC_PluginExe();

public:
// +-------------------------------------------------------------------------+
// + The following functions are intended to be specialized for each plug-in +
// +-------------------------------------------------------------------------+

   /**
    * Initialization.
    *
    * Intializes the plug-in.
    * The L_configf parameter is reserved for future use.
    * Default implementation is NOP.
    *
    * @param L_configf configuration file code (Not a file descriptor)
    * @return 0 if operation suceeds, -1 otherwise
    */
   virtual int init(const int P_configf);

   /**
    * Closes a plug-in.
    *
    * Default implementation is NOP.
    *
    * @param P_mode termination mode, whether plugin must complete immediately
    *               or not
    */
   virtual void close(TerminationType P_mode);

   /**
    * Update select(2) masks with the file descriptors managed by the plug-in.
    *
    * The correct bits are set in the masks for all the file descriptors used
    * in the managed Physical Connections. If the caller does not wish to use
    * a particular mask, then the parameter may be passed as 0.
    *
    * The user maximum fd that is set in the masks should be passed as
    * P_maxFds parameter.
    * Default implementation is NOP.
    *
    * @param P_maxFd the maximum fd set in the masks before the call
    * @param P_rm read fds mask
    * @param P_wm write fds mask
    * @param P_em exception fds mask
    * @param P_timeout maximum inactivity delay
    * @return the maximum fd set in the masks.
    */
   virtual int selectMasks(
      const int P_maxFd, fd_set* P_rm, fd_set* P_wm, fd_set* P_em,
      struct timeval* P_timeout
   );

   /**
    * Acknowledeges select(2) activity related to the plug-in.
    *
    * This function is called after select(2) returns.
    * It is intended to perform the minimum amount of work to acknowledge
    * plug-in privates file descriptors.
    * The actual processing of these events will be performed later in
    * processRequest().
    * Default implementation is NOP.
    *
    * @param P_nfds the total number of bits set in the bit mask as returned
    *               by select(2)
    * @param P_rm read fds mask
    * @param P_wm write fds mask
    * @param P_em exception fds mask
    * @return the number of file descriptors left to process
    * @see #processRequest
    */
   virtual int connectionHandler(
      const int P_nfds, fd_set* P_rm, fd_set* P_wm, fd_set* P_em
   );

   /**
    * Activity status of the plug-in.
    *
    * Once plug-in is initialized, this function returns IDLE if the plug-in
    * has no processing left, or PROCESSING if it requires processing time
    * from the scheduler.
    * Default implementation returns EMPTY.
    *
    * @return see above
    */
   virtual RequestState pendingRequest();

   /**
    * Process an amount of work.
    *
    * This function is called by the PIC scheduler to request the plug-in to
    * process an amount of work.
    * Default implementation is NOP and returns EMPTY.
    *
    * @param P_nRequests size of the task. Plug-in developer is responsible to
    *                    define the "request" granularity, so that it meets
    *                    HA constraints
    * @return new activity status as defined in pendingRequest()
    * @see #pendingRequest
    * @see #connectionHandler
    */
   virtual RequestState processRequest(const int P_nRequests);

   /**
    * Inform Plugin when PIC reloads its trace level.
    *
    * This method is called by the PIC scheduler when PIC traces levels are 
    * updated (SIGINT caught).
    * Default implementation is NOP.
    */
   virtual void setTrace();

protected:
   /**
    * Constructor.
    *
    * Protected because PIC_pluginExe object is intended to be inherited by the
    * plug-in execution implementation class.
    *
    */
   PIC_PluginExe();

private:
};



/**
 * Version of the API
 * Checked by the PIC at load time
 * Actually we use an AWFULL hack: the version string is appended to piSetup()
 * function name !
 *
 * Since compatibility between the PCA and the PIC API is broken 
 * with the aCC migration, the plugin API version number
 * evolves from 00000001 to 00000002
 *
 */
#define PIC_PLUGIN_VERSION(s) s## \
   00000003  // <<< Version number - WARNING: heading '0' are meaningful

#define piSetup PIC_PLUGIN_VERSION(piSetup) // The HACK !
#define piMibSetup PIC_PLUGIN_VERSION(piMibSetup) // The HACK !


/**
 * Plug-in interface structure.
 *
 * This structure is used for the declaration of PIC interfaces implemented
 * by the plug-in.
 * A pointer to this structure is passed as argument to the user-defined
 * piSetup()function.
 * Pointer members hold implemented PIC interfaces (default=0).
 *
 * @see #PIC_PluginExe
 * @see #PIC_PluginHA
 */
 struct PIC_PluginInterface {
           PIC_PluginExe* pluginExe;
           PIC_PluginHA* pluginHA;
        };

/**
 * Plug-in main entry-point.
 *
 * This function is to be defined for each plug-in.
 * It must declare the plug-in execution interface object
 * in its PIC_PluginInterface* argument.
 * It can declare a plug-in HA interface object
 * in its PIC_PluginInterface* argument.
 *
 * @param P_pluginInterface pointer to the plug-in interface structure
 * @return 0 on completion, other value on error
 */
extern "C" int piSetup(PIC_PluginInterface *P_pluginInterface);

/**
 * Plug-in optional MIB entry-point.
 *
 * This function can be defined in the plug-in.
 * It will be called after the piSetup function if the PIC
 * supports this feature.
 *
 * @return 0 on completion, other value on error
 */
extern "C" int piMibSetup(void);


#endif // __PIC_PLUGIN_EXE_H
