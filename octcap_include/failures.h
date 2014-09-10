/*=====================================================================
|
|                               mtpFailures.h
|
| Failure causes for SS7 platform
|
| 
| $Source: /7UP/code/level3/mtpFailures.h $
| $Revision: 5.6.1.3 $
| $Date: 2001/04/23 08:03:36 $
| 
|
| HEWLETT PACKARD SS7
| (c) Copyright 1991, Hewlett-Packard Company, all rights reserved
======================================================================*/

#ifndef MTPL3_FAILURES_H
#define MTPL3_FAILURES_H

typedef enum
{
	  NO_FAILURE              = -1,
	  /* level2 failures */
	  ALIGNMENT_FAILED        = 0,
	  REMOTE_OS               = 1,
	  HIGH_ERROR_RATE         = 2,
	  UNREASONABLE_SU         = 3,
	  UNREASONABLE_BSN        = 4,
	  EXCESSIVE_ACK_DELAY     = 5,
	  UNREASONABLE_FIB        = 6,
	  CONGESTION_TOO_LONG     = 7,
	  LEVEL1_LOOP             = 8,
	  LEVEL1_CLOCK            = 9,
	  FLAG_STREAM_TOO_LONG    = 10,
	  RPROC_OUTAGE,

	  LINK_NOT_INAC, /* separation flag */
	  /* level2 failure which inactive link */
	  SILT_FD_LOCKED,
	  SILT_FIRMWARE_NOT_RESPONDING,
	  LINK_TEST_FAILED,
	  LEVEL2_HW_FAILURE,

	  /* level3 failures */
	  ILLEGAL_CONFIGURATION,
	  MGT_INACTIVATED,
	  PARENT_OBJECT_INACTIVE,

	  /* Discard causes */
	  LINK_CONGESTION         = 20,
	  DECODING_ERROR,
	  UNKNOWN_DPC,
	  NO_TRANSFER_FUNCTION,
	  LOCAL_UP_UNAVAILABLE,

	  /* linkset failures */
	  ALL_LINKS_FAILED=25,

	  /* Remote destination inaccessibility reasons */
	  NO_LOCAL_RESSOURCES,
	  TRANSFER_PROHIBITED,

	  /* Configuration errors */
	  OAM_OBJECT_UNKNOWN,
	  LOCAL_PC_ALREADY_SET,
	  OAM_OBJECT_NOT_FOUND     = 30,
	  PARAMETER_NOT_FOUND,
	  PARAMETER_WRONG_VALUE,
	  PARAMETER_NOT_SET,
	  PARAMETER_TYPE_ERROR,
	  OAM_OBJECT_NOT_INACTIVE,
	  OAM_ILLEGAL_OPERATION,
	  OAM_OBJECT_EXISTS,
	  ILLEGAL_PDN,
	  PDN_ALREADY_IN_USE,
	  LINK_CONFIGURATION_ERROR = 40,
	  NO_MORE_ROUTE_AVAIL,
	  DPC_UNAVAIL_MSU_DISCARDED,
	  DPC_INACTIVE_MSU_DISCARDED,
	  DPC_CONGESTED_MSU_DISCARDED,
	  DPC_LS_CAUSE,                    /* linkset avail or failed                    */
	  DPC_TF_CAUSE,                    /* TFP or TFA received                        */
	  DPC_ROUTE_RESTARTED,             /* a route restarted                          */
	  DPC_LS_ACTIVE,                   /* a Linkset becomes active                   */
	  DPC_IS_INACTIVE,                 /* DPC is in inactive state                   */
	  DPC_RESTRICT_END        = 50,    /* End of restriction for a route             */
	  DPC_START_CAUSE,                 /* Start Dpc                                  */
	  SOFTWARE_FAILURE,

	  /* Link inhibit causes */
	  LOCAL_INHIBIT,                   /* link inhibited by local management          */
	  REMOTE_INHIBIT,                  /* link inhibited by remote MTP                */
	  BOTH_INHIBIT,                    /* link inhibited by both                      */

	  /* Link inhibit deny causes */
	  INHIBIT_DENIED_LOCAL,            /* local link inhibit refusal                  */
	  INHIBIT_DENIED_REMOTE,           /* remote link inhibit refusal                 */
	  FORCED_UNINHIBIT_LOCAL,          /* local forced link uninhibit                 */
	  FORCED_UNINHIBIT_REMOTE,         /* remote forced link uninhibit                */

	  PDN_NOT_ALLOWED         = 60,    /* pdn not allowed for this className          */
	  LINK_NOT_ALLOWED,                /* LinkId not allowed for this className       */
	  LINK_NOT_CONFIGURED,             /* LinkId not configured                       */
	  LINK_ERROR_CONFIGURATION,        /* No information get for this link, API error */
	  LINK_ALREADY_USED,               /* LinkId already used                         */

	  ROUTE_TEST_OK           = 65,    /* routing test successfull                    */
	  ROUTE_TEST_FAILED       = 66,    /* routing test failed                         */
	  ROUTE_TEST_LOCKED       = 67,    /* routing test locked                         */

	  INHIBIT_NOT_SUPPORTED   = 70,    /* Link inhibit not supported (TTC error)      */
	  ROUTE_TEST_NOT_SUPPORTED= 71,    /* Routing test not supported (all except TTC) */

	  ILLEGAL_DPC_VALUE       = 80,    /* DPC value is against (ANSI) numbering rules */

	  VPC_IN_USE              = 81,    /* At least one VU is connected to the VPC     */
	  TOO_MANY_VPC            = 82,    /* Max number of VPC already reached           */
	  VPC_NOT_AVAILABLE       = 83,    /* VPC feature not available                   */

	  /* API error causes (send from user to SS7 system */
	  ERRAPIOBJECT            = 100,   /* object does not exist                       */
	  ERRAPINOTIF,                     /* Notication type does not exist              */
	  ERRAPIPRIORITY,                  /* Illegal priority number                     */
	  ERRAPICMD,                       /* Illegal command                             */
	  ERRAPIREPORT,                    /* Illegal type of report                      */
	  ERRAPICANTLOCK          = 105,   /* Cannot lock OAM interface                   */

	  /* IPC server errors */
	  EAPIGETSCENAME,                  /* Cannot get service name                     */
	  EAPIBIND,                        /* bind fail                                   */
	  EAPILISTEN,                      /* listen fail                                 */
	  EAPIACCEPT,                      /* accept fail                                 */
	  EAPILINGER              = 110,   /* cannot linger                               */

	  /* SifMgr error */
	  EAPISIFMGR_ERROR,                /* unknown message header                      */
	  EAPISIFMGR_INTERNAL,             /* not used                                    */

	  /* Sif error */
	  EAPISIFINTERNAL,                 /* Call to Proxy failed                        */

	  /* ProxyMTP error */
	  EAPIILLIND,                      /* Illegal indication defintion                */
	  EAPIMTP_INTERNAL        = 115,   /* Illegal message header                      */
	  EAPIILLDPCSTAT,                  /* Illegal DPC status                          */

	  /* ProxyOAM error */
	  EAPIOAM_INTERNAL,                /* Illegal msg header received from API        */
	  EAPIILL_CMD,                     /* Illegal command from API                    */
	  EAPIOBJECT_NOT_FOUND,            /* must be MTP, LINK, or ROUTE                 */
	  EAPIREPORT_NOT_FOUND    = 120,   /* type of report unknown                      */
	  EAPIILLOBJECT,                   /* OAM send to Proxy an illegal object         */
	  EAPIILLNOTIF,                    /* Illegal notif received from OamIf           */
	  EAPIRESET_FAILED,                /* MTP reset has failed                        */

	  /* ProxyGEN error */
	  EAPISCE_INTERNAL,                /* Illegal message header                      */
	  EAPIVERSION                      /* Library not compatible with stack           */
} FailureCause;

extern char * failureName();

#endif /* MTPL3_FAILURES_H */
