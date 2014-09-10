/***********************************************************
*
* 
*
* $Source: /7UP/code/level3/mtpOamDefs.h $
* $Revision: 6.1 $
* 
* 
***********************************************************/

#ifndef MTPL3_OAM_API_H
#define MTPL3_OAM_API_H

/*-----------------------------------------------------------------------------

   Oam common definitions
   Mtp Oam objects

   History

   Rev.    Auth. Date     Modifications

   ??      JMR   93/03/05 Add the statuses and commands for the link inhibit
   5.4.2.1 JCR   00/11/27 VPC implementation.
   5.4.2.2 JCR   Improve comments.
   5.4.2.3 JCR   VPC feature option.

-----------------------------------------------------------------------------*/

#ifdef _WIN32
#ifndef HP_DLL_IF
#  define HP_DLL_IF __declspec(dllimport)
#endif
#else
#  define HP_DLL_IF
#endif

/* --------
   CHANGE THIS FILE WITH CAUTION: ALL CHANGES MADE HERE SHOULD BE
   REPORTED IN ss7_if.h WHICH IS THE API INTERFACE DEFINITION FILE.
   -------- */

#define MAXADDRLEVEL    3
#define MAXMSGLEN       1000
#define MAXPSTRING      50
#define MTPMAXOBJINMSG  1 

#define MAX_OAM_MSG_LEN 500

#ifndef UBOOL_DEFINED
#define UBOOL_DEFINED
typedef enum { no, yes } ubool;
#endif

#ifndef NB_MAX_LOCAL_ALIAS
#define NB_MAX_LOCAL_ALIAS 4
#endif

/* JCR 00/11/27 - VPC implementation */
#ifndef NB_MAX_VPC
#define NB_MAX_VPC 16
#endif

/* JCR 00/11/27 - VPC implementation 
   change UNUSED_ALIAS_SLOT to UNUSED_SLOT */
#ifndef UNUSED_SLOT
#define UNUSED_SLOT -1
#endif

/* For TTC: Defines whether a linkset is an A-linkset or B-linkset */
/* For all other standards it is not applicable (always TYPE_NA)   */

#define LINKSET_TYPE_NA -1
#define LINKSET_TYPE_A   0
#define LINKSET_TYPE_B   1

/*-------------------------------
  Definition of system objects
 -------------------------------*/

typedef enum
{
  mtp,
  links,
  linkset,
  destination,
  route,

  /* Types added for CLUSTER_ROUTING
     They are not used in ITU-T (ANSI only) */
  cluster,
  network,
  cluster_route,
  network_route,

  /* Types added for ALIASING */
  alias,
  local_alias,
  constituent,

  /* Types added for Virtual Point Code */
  virtual_pc,
  virtual_user

} MtpOamObject;

/*-------------------------------------------------------------------------
| Definition of an ADDRESS:
|   ObjAddr [0] is the mtp address
|   ObjAddr [1] is the linkset or destination or local alias or vpc address
|   ObjAddr [2] is the link address or route address (=linkset)
|   When specifiying a 'mtp' object, ObjAddr [0] must be set.
|   When specifiying a 'linkset' object or 'destination' object, ObjAddr[0]
|     and ObjAddr [1] must be set.
|   When specifiying a 'link' object or a route object, ObjAddr[0],
|     ObjAddr [1], ObjAddr [2]  must be set.
-------------------------------------------------------------------------*/

typedef int MtpOamAddress [MAXADDRLEVEL];

/*--------------------------------------------------------------
| Definition of PARAMETERS available for MTP, LINK, LINKSET
| DESTINATION and ROUTE objects.
--------------------------------------------------------------*/

typedef enum
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | Configurable parameters for MTP object only
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  mtp_local_pc   = 0,         /* Local point code                      */
  mtp_NI         = 1,         /* Network Indicator                     */
  mtp_timer1     = 2,         /* Timers 1-17 as defined in CCITT Q704  */
  mtp_timer2     = 3,
  mtp_timer3     = 4,
  mtp_timer4     = 5,
  mtp_timer5     = 6,
  mtp_timer6     = 7,

  mtp_timer8     = 9,

  mtp_timer10    = 11,
  mtp_timer11    = 12,
  mtp_timer12    = 13,
  mtp_timer13    = 14,
  mtp_timer14    = 15,
  mtp_timer15    = 16,
  mtp_timer16    = 17,
  mtp_timer17    = 18,
  mtp_timer18    = 19,
  mtp_timer19    = 20,
  mtp_timer20    = 21,
  mtp_timer21    = 22,
  mtp_timer22    = 23,
  mtp_timer23    = 24,

  /* ANSI 96 timers */
  mtp_timer24    = 25,
  mtp_timer25    = 26,
  mtp_timer26    = 27,
  mtp_timer27    = 28,
  mtp_timer28    = 29,

  mtp_t1_q707    = 30,
  mtp_t2_q707    = 31,
  mtp_t10_q707   = 32,

  /* ANSI 96 timers */
  mtp_timer29    = 33,
  mtp_timer30    = 34,
  mtp_timer31    = 35,
  mtp_timer32    = 36,

  mtp_transfer   = 37,       /* not Implemented */
  mtp_dpc_filter = 38,       /* not Implemented */

  mtp_standard   = 39,       /* Standard (ANSI, ITU-WB or BB) of MTP */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | Configurable parameters for LINK object only
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  link_pdn       = 40,       /* Physical link number */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | Configurable parameters for DESTINATION, CLUSTER
    | and NETWORK objects only
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  dpc_STP        = 55,       /* Adjacent point is a Signalling
				transfer point (STP) or a signaling
				point (SP) */
  dpc_gateway    = 56,       /* Destination is a gateway to other
				networks (route NI!= mtp_NI) */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | Configurable parameters for ROUTE, C_ROUTE and
    | N_ROUTE objects only
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  route_priority = 60,       /* Return route priority */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | Configurable parameters for LINKSET object only
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  linkset_ab_bit = 71,       /* Linkset type only available for TTC */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | VPC feature
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  vpc_feature    = 80        /* VPC feature option */

} MtpOamConfParmType;

/*----------------------------------------------------------------------
| Notifications types for OAMRECV and OAMSTAT
----------------------------------------------------------------------*/

typedef enum
{
  nostat = -1,            /* for internal use only                */

  /*------------------
    notifs for OAMRECV and OAMSTAT
    ------------------*/
  object_state,           /* Object state                         */
  traffic_gauge,          /* Msu per seconds                      */
  traffic_count,          /* Msu count                            */
  failure_gauge,          /* % of time in deactivated state       */
  failure_count,          /* Number of object failures            */
  congestion_count,       /* Number of congestion start           */
  congestion_gauge,       /* % of time in congested state         */
  rx_byte_count,          /* received SIO+SIF bytes for a link    */
  tx_byte_count,          /* transmitted SIO+SIF bytes for a link */

  discarded_msu,          /* Discarded msus                       */
  su_error_count,         /* Signal unit in error                 */
  rx_load_average,        /* Receipt load average                 */
  tx_load_average,        /* Emit load average                    */
  retransmitted_count,    /* Signal Unit restransmitted           */
  SNMlogging,             /* start SNM logging                    */

  /*------------------
    notifs for OAMRECV
    ------------------*/
  parm_value_int,         /* Integer configuration value          */
  parm_value_str,         /* string configuration value           */
  conf_objects,           /* lists of all available LINK, LINKSET,
			     MTP, and ROUTE configured inside MTP */
  unused,                 /* Reserved                             */
  error                   /* error during a command               */

} MtpOamNotifType;

/*----------------------------------------------------------------------
| Type of report occurence for OAMSTAT
----------------------------------------------------------------------*/

typedef enum
{
  report,
  report_period,
  report_onocc,
  stop_report

} MtpOamReportOcc;

/*----------------------------------------------------------------------
| Structure parameter for OAMSTAT
----------------------------------------------------------------------*/

typedef struct
{
  ubool           reset;      /* set or reset a statistic                      */
                              /* when yes the already existing statistic       */
                              /* counter is reset to the 0 value               */
  MtpOamReportOcc rep_occur;  /* type of report                                */
  int             period;     /* period                                        */
  ubool           reset_auto; /* reset to 0 the statistic counter after report */

} MtpOamStParms ;

/*----------------------------------------------------------------------
| Commands definition for OAMCMD
----------------------------------------------------------------------*/

typedef enum
{
	activate     = 0,
	deactivate   = 1,
	add          = 2,
	del          = 3,
	inhibit      = 6,
	uninhibit    = 7,
	get_value    = 8,
	set_value    = 9,
	reset        = 10,
	set_pcvalue  = 11,
	get_pcvalue  = 12,
	get_conf     = 13,
	lock_oam     = 14,
	test_routing = 15

} MtpOamCmd;

#define MTP_OAM_CMD_STR(cmd) \
( (cmd) == activate       ? "activate"       : \
  (cmd) == deactivate     ? "deactivate"     : \
  (cmd) == add            ? "add"            : \
  (cmd) == del            ? "del"            : \
  (cmd) == inhibit        ? "inhibit"        : \
  (cmd) == uninhibit      ? "uninhibit"      : \
  (cmd) == test_routing   ? "test_routing"   : \
  (cmd) == get_value      ? "get_value"      : \
  (cmd) == set_value      ? "set_value"      : \
  (cmd) == reset          ? "reset"          : \
  (cmd) == set_pcvalue    ? "set_pcvalue"    : \
  (cmd) == get_pcvalue    ? "get_pcvalue"    : \
  (cmd) == get_conf       ? "get_conf"       : \
  (cmd) == lock_oam       ? "lock_oam"       : \
  "*** Bad OAM command ***" )

/*----------------------------------------------------------------------
  | Structure parameter for OAMCMD
  ----------------------------------------------------------------------*/

typedef struct
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | field for SET_VALUE, GET_VALUE commands
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  MtpOamConfParmType prid;        /*-- parameter identifier */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | field for SET_VALUE, SET_PCVALUE commands
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  int int_val;                    /*-- integer value */
  char str_val[MAXPSTRING];       /*-- string value (unused) */

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    | field for ADD command with route_object
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  int route_priority;             /* priority 1 or 2  */

} MtpOamCmdParms;

/*----------------------------------------------------------------------
| Object state for OAMRECV
----------------------------------------------------------------------*/

typedef enum
{
  inactive,             /*             deactivated by management */
  normal,               /*               Normal in service state */
  out_of_service,       /*               Stopped or failed state */
  deleted,              /*                 not existing any more */
  congested,            /*                      Congestion state */
  restricted,           /*                     Restriction state */
  restarting,           /*                      Restarting state */

  /*~~~~~~~  link inhibition states ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  inhibited,            /*         link inhibited and in service */
  inhibited_OS,         /*     link inhibited and Out of service */
  inhibited_inactive    /*           link inhibited and inactive */

} MtpOamState;

#define MTP_OAM_STATE_STR(state) \
( (state) == inactive           ? "inactive"           : \
  (state) == normal             ? "normal"             : \
  (state) == out_of_service     ? "out_of_service"     : \
  (state) == deleted            ? "deleted"            : \
  (state) == congested          ? "congested"          : \
  (state) == restricted         ? "restricted"         : \
  (state) == restarting         ? "restarting"         : \
  (state) == inhibited          ? "inhibited"          : \
  (state) == inhibited_OS       ? "inhibited_OS"       : \
  (state) == inhibited_inactive ? "inhibited_inactive" : \
  "*** Bad OAM state ***" )

/*----------------------------------------------------------------------
| Description of an object as returned in 'MtpOanConfSet' structure
----------------------------------------------------------------------*/

typedef struct
{
  MtpOamObject     obj_type;        /*            type of object */
  MtpOamAddress    address;         /*            object address */
  MtpOamState      state;           /*             object status */
  int              priority;        /* priority (for ROUTE only) */

} MtpOamObjList;

/*----------------------------------------------------------------------
| Structure for parameter configuration in OAMRECV with GET_VALUE
| notification.
----------------------------------------------------------------------*/

typedef struct
{
  MtpOamConfParmType      prid;           /* parameter identifier */
  union
    {
      int     pr_value;                    /*        integer value */
      char    pr_string [ MAXPSTRING ];    /*         string value */
    } pvalue;

} MtpOamConfParm ;

/*----------------------------------------------------------------------
| Structure to get configured object in OAMRECV with CONF_OBJECTS.
----------------------------------------------------------------------*/

typedef struct
{
  int           msg_num;                        /*                           message number */
  ubool         last_msg;                       /* last message for CONF_OBJECTS indication */
  int           number_of_objects;              /*        number of objects in this message */
  MtpOamObjList object_table[ MTPMAXOBJINMSG ]; /*                             object table */

} MtpOamConfSet;

typedef struct
{
  int DPC;
  int OPC;
  int H1H0;
  int SLC;
  union
    {
      int BSNT;
      int CBcode;
      int remotePC;
    } parameter;

    int UPid;

} SNMdefs;

/*----------------------------------------------------------------------
| Structure to get status, statistics and failure cause results in
| OAMRECV with OBJECT_STATE, TRAFFIC_GAUGE/COUNT, FAILURE_GAUGE/COUNT,
| CONGESTION_GAUGE/COUNT, RX/TXBYTE_COUNT, DISCARDED_MSU, SU_ERROR_COUNT,
| RX/TX_LOAD_AVERAGE, RETRANSMITTED_COUNT, SNMLOGGING, ERROR notifications.
----------------------------------------------------------------------*/

typedef struct
{
  MtpOamState     status;                /*    object state */
  float           stat_value;            /* statistic value */
  FailureCause    failure_cause;         /*     error cause */
  SNMdefs         snm;                   /*       SNM infos */

}  MtpOamNotifStruct;

/*----------------------------------------------------------------------
| Union for a generic received. notifstruct of OAMRECV call is
| a pointer to this union.
----------------------------------------------------------------------*/

typedef union
{
  MtpOamConfParm     confp;
  MtpOamConfSet      setp;
  MtpOamNotifStruct  notifp;

} MtpOamRecvStruct;


/* functions protoypes */

#ifdef __cplusplus
extern "C" {
#endif
	
HP_DLL_IF int MTPL3_oamcmd (int                   cnxId,
                            struct timeval        *time,
                            void                  *context,
                            MtpOamObject          object,
                            MtpOamAddress         address,
                            MtpOamCmd             command,
                            MtpOamCmdParms        *cmdParms);


HP_DLL_IF int MTPL3_oamrecv (int                  cnxId,
                             struct timeval       *time,
                             void                 **context,
                             MtpOamObject         *object,
                             MtpOamAddress        address,
                             MtpOamNotifType      *notif,
                             MtpOamRecvStruct     *notifstruct);

HP_DLL_IF int MTPL3_oamstat (int                  connection_id,
                             struct timeval       *time,
                             void                 *context,
                             MtpOamObject         object,
                             MtpOamAddress        address,
                             MtpOamNotifType      statistic,
                             MtpOamStParms        *statparms);
                        

#ifdef __cplusplus
}
#endif

#endif /* MTPL3_OAM_API_H */
