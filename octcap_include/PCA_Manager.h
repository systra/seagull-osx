// begin_is
//----------------------------------------------------------------------------
//
//                               MODULE   PLUGIN_CommApi
//                               -----------------------
//
//
//  PURPOSE: This class provides initialization and execution interface
//           for the plug-in communication API
//
//  NOTES and CAUTIONS:
//
//  FILE : PCA_Manager.h
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
//       $Source: /SLEE/code/PLUGIN_CommApi/PCA_Manager.h $
//       $Revision: 1.11 $
//       
//----------------------------------------------------------------------------
// end_is

#if !defined(__PCA_MANAGER_H)
#define __PCA_MANAGER_H

#if defined(__GNUG__) && (__GNUC__>=3)
using namespace std;
#endif /* !__GNUG__ || (__GNUC__ < 3) */

#include <Select.h>     // For select(2)'s fd_set declaration

#if (__cplusplus >= 199707L  || __GNUG__)
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

/*
__________________________________________________________________________

              C L A S S    P C A _ M a n a g e r
__________________________________________________________________________
*/

/**
 * This class provides initialization and execution interface for the 
 * plug-in communication API (PCA). In addition it performs resolution between
 * plug-in logical names and physical connection specific names.
 *
 * This class is needed only if the PCA API is used in a stand alone way.
 * NEVER use it in a plug-in because all functions are already called
 * internaly by the PluginContainer.
 *
 * This is a singleton class.
 *
 * @short Initialization and execution of the communication API
*/

class PCA_Manager {
public:
   /**
    * Get the single instance of the class.
    *
    * Only one instance of PCA_Manager exists in the process. This
    * instance is automatically created the first time the instance()
    * method is called.
    *
    * @return the single instance of the PCA_Manager class.
    */
   static PCA_Manager* instance(); 


   /**
    * API main mode.
    *
    * Defines if the major part of the PCA API will be server or
    * client connections. It can take the values:
    *                  @li SERVER for a process with predominantly
    *                                     server connections.
    *                  @li CLIENT for a process with predominantly
    *                                     client connections.
    */
   enum ApiMode { CLIENT, SERVER };


   /**
    * Initialize the API.
    *
    * This method must be called prior to any call to the other
    * methods of the class, or of the API.
    * It initializes the underlying communication module.
    * 
    * The status is updated as following:
    *    @li NO_ERROR - the operation completed successfully
    *    @li ... - ...
    *
    * @param P_mode indicates if the major part of the API will be server or
    *               client connections. 
    * @param P_nChans the maximum number of channels that will be available
    *                 for the server and client connections in the process.
    * @param P_bPerC the number of buffers taken from the buffers pool for a new
    *                channel for the transmit and receive sides.
    * @param P_bSize the size of buffers allocated and used by the channels.
    * @param P_messagePoolSize size of message related pools
    * @param P_bufferPoolSize size of data buffer related pools
    * @param P_status the status to check to know if the method succeeded or not
    */
   void init(
      ApiMode P_mode, int P_nChans, int P_bPerC, int P_bSize,
      unsigned P_messagePoolSize, unsigned P_bufferPoolSize,
      PCA_Status& P_status
   );

   /**
    * Register a plug-in name for address resolution.
    *
    * Plug-in server and clients are identified by a plug-in name which format
    * is "serviceName@processName". This name is independant from the underlying
    * physical connection
    * When a connection is requested the plug-in name must be translated into
    * the physical connection aware name of the server.
    * When a connection request is received the physical connection name must be
    * translated into the plug-in name of the client.
    * This function is used at initialization time to setup <plug-in name,
    * physical connection name> associations for further name resolution
    *
    * @param P_pluginName high level name of the server: serviceName@processName
    * @param P_phyName low level name of the server:
    *                  for TCP/IP this is tcpServiceName@ipHostAddress
    * @param P_status result of the operation
    */
   void registerName(
      const Str& P_pluginName, const Str& P_phyName,
      PCA_Status& P_status
   );

   /**
    * Update select(2) masks with the file descriptors managed within the API.
    *
    * The correct bits are set in the masks for all the file descriptors used
    * in the managed Physical Connections. If the caller does not wish to use
    * a particular mask, then the parameter may be passed as 0.
    *
    * The user maximum fd that is set in the masks should be passed as
    * P_maxFds parameter.
    *
    * @param P_maxFd the maximum fd set in the masks before the call
    * @param P_rm read fds mask
    * @param P_wm write fds mask
    * @param P_em exception fds mask
    * @return the maximum fd set in the masks.
    */
   int selectMasks(int P_maxFd, fd_set* P_rm, fd_set* P_wm, fd_set* P_em);

   /**
    * Handle all select(2) activity related to the Physical Connections.
    *
    * Must be called after select(2) is called.
    *
    * @param P_nfds the total number of bits set in the bit mask as returned
    *               by select(2)
    * @param P_rm read fds mask
    * @param P_wm write fds mask
    * @param P_em exception fds mask
    * @return 0 if success and -1 if failure
    */
   int connectionHandler(int P_nfds, fd_set* P_rm, fd_set* P_wm, fd_set* P_em);


private:
   PCA_Manager();
   ~PCA_Manager();

   static PCA_Manager* _instance;
};



#endif // __PCA_MANAGER_H
