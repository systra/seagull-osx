/*=====================================================================
|
|                           Error codes for SS7 API
|
| $Source: /7UP/code/libss7ifctl/ss7errors.h $ 
| $Revision: 6.0 $ 
| $Date: 2001/11/07 15:11:52 $
|
| HEWLETT PACKARD SS7
| (c) Copyright 1991, Hewlett-Packard Company, all rights reserved
======================================================================*/

#ifndef SS7_ERRORS_H
#define SS7_ERRORS_H

typedef enum {

  EAPINOERROR = 0      ,     /* no API error                                     */

  EAPINOCONFIG = 1     ,     /* Failed to find config file                       */
  EAPIBADCONFIG        ,     /* Configuration found was bad                      */

  EAPICONNECT          ,     /* Cannot establish connection with SS7             */
  EAPIFAILCNX          ,     /* Connection establishment failed                  */
  EAPICNXCLOSED        ,     /* (=5) Connection has been closed by remote        */

  EAPICLOSEFAIL        ,     /* cannot send close msg to remote                  */

  EAPIILLCALL          ,     /* Illegal call for this service desc               */
  EAPIILLTYPE          ,     /* Illegal type of service requested                */

  EAPIILLVALUE = 10    ,     /* Illegal value                                    */
  EAPIILLCTRL          ,     /* Illegal interface control command                */

  EAPIDATALEN          ,     /* data length too big                              */
  EAPISENDFULL         ,     /* API send buffers are full                        */
  EAPIMEMORYERROR      ,     /* no more memory -> malloc has failed              */

  EAPIINTERNALMTP      ,     /* (=15) Internal MTP error                         */
  EAPIINTERNALSCCP     ,     /* Internal SCCP error                              */
  EAPIINTERNALOAM      ,     /* Internal OAM error                               */
  EAPIINTERNALSCE      ,     /* Internal service error                           */
  EAPIINTERNALTCAP     ,     /* Internal TCAP error                              */

  EAPIPRIMITIVE        ,     /* (=20) wrong primitive in mtpsend                 */
  EAPIILLPROCESS       ,     /* WARNING: error reserved for HP internal use !    */
  EAPIBUSY             ,     /* Switchover in process                            */

  EAPIMAXUSERS         ,     /* Maximum number of users exceeded                 */
  EAPICNXID            ,     /* Bad connection id                                */
  EAPIBADVERSION       ,     /* Service version not compatible with Stack        */
  EAPINOSSN            ,     /* The SSN has not been configured                  */
  EAPIALRDYINUSE       ,     /* SSN or SI already in use (local or virtual user) */
  EAPINOSERVICE        ,     /* Service not supported by the Stack               */
  EAPINOTSUPPORTED     ,     /* functionality not supported                      */
  EAPINOTINITIALIZED   ,     /* (=30) API not initialized                        */
  EAPIDISABLED         ,     /* Connection is deactivated by Stack               */

  EAPIMAXSYNCCNX       ,     /* Max number of synchro cnx exceeded               */
  EAPIMAXSYNCPROC      ,     /* Max of synchro processes exceeded                */
  EAPIMAXPROC          ,     /* Max number of connected processes exceeded       */
  EAPIMAXCOMMONCNX     ,     /* Max nb of common (nor sync nor monitor) cnx      */
  EAPIMAXMONITOR       ,     /* Max number of SS7 Monitors exceeded              */
  EAPIMAXAPPLI         ,     /* Max number of primary application exceeded       */
  EAPIAPLLINULL        ,     /* Structute ss7_additional_cnx_info that 
                                contains the application Id is NULL              */
  EAPIMTPSERVICEINUSE  ,     /* The user is trying to connect the 
                                RoutedMtpService although the MtpService is
                                already created and connected                    */
  EAPINOVU                   /* The VU has not been configured                   */
} ss7_error_code;

#endif
