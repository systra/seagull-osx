/* use objc-mode with (x)emacs -*- objc -*- */
/**
 * @file sccp/sccpOamDefs.h
 * @brief definitions of global variable types used in the SCCP OAM object
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef SCCP_OAM_API_H
#define SCCP_OAM_API_H

#include "ainCommon.h"

#ifdef _WIN32
#ifndef HP_DLL_IF
#  define HP_DLL_IF __declspec(dllimport)
#endif
#else
#  define HP_DLL_IF
#endif

#ifndef UBOOL_DEFINED
#define UBOOL_DEFINED
typedef enum { no, yes } ubool;
#endif

/* Priority associated to a destination for a Global Title translation
   is on range [1..100], so we need 3 digits to store it */
#define NBDIGITS_PRIORITY       3

#define SCCPMAXOBJINMSG     1

/* Oam commands that may be sent to the interface */

typedef enum {
                       /* prefix SO_ signifies `Sccp Oam' */
  SO_ADD,              /* add an object */
  SO_REMOVE,           /* remove an object */
  SO_ACTIVATE,         /* activate an object */
  SO_DEACTIVATE,       /* deactivate an object */
  SO_LOCK,             /* request exlusive write access */
  SO_UNLOCK,           /* relinquish exlusive write access */

  SO_RESETCONF,        /* reset the entire sccp configuration */
  SO_DUMPCONF,         /* request sccp configuration dump */
  SO_GET_TRANSLATIONS, /* request address translations */
  SO_GET_BACKUP,       /* request to get backup value */
  SO_MODIFY_BACKUP,    /* request to modify peer value */
  SO_RESERVED1,        /* for compatibility with Venus */
  SO_RESERVED2,        /* for compatibility with Venus */
  SO_SET_VALUE,        /* set mode of a remote user */
  SO_GET_VALUE,         /* get mode of a remote user */
  /* GREhp12674 2001/06/29 NZa.To configure a PC/SSN as concerned */
  SO_ADD_CONCERNED,     /* add a Concerned user */
  SO_REMOVE_CONCERNED   /* remove a Concerned user */
}SccpOamCmd ;

/*We added two concerned users commands*/
#define NB_SO_CMD 17  /* To be modified if the above enum is modified */

/* Structure for Oam command parameters */

typedef struct {

  float   value;   /* numeric parameter value */
  char   *sValue;  /* string value */

}SccpCmdParms;

/* Oam Statistics types (and config changes!) */
/* These represent a subset of the statistics described in Q 791 tables 7-9. */

typedef enum {
                        /* prefix SO_ signifies `Sccp Oam' */
  SO_STATE,             /* state of an object */
  SO_UDT_COUNT_TX,      /* Transmitted Unitdata traffic count */
  SO_UDT_COUNT_RX,      /* Received Unitdata traffic count */
  SO_UDTS_COUNT_TX,     /* Transmitted Unitdata service count */
  SO_UDTS_COUNT_RX,     /* Received Unitdata service count */
  SO_RTG_FAILURE_COUNT, /* Routing failure count */

  SO_UDT_GAUGE_TX,      /* Transmitted Unitdata traffic gauge */
  SO_UDT_GAUGE_RX,      /* Received Unitdata traffic gauge */
  SO_UDTS_GAUGE_TX,     /* Transmitted Unitdata service gauge */
  SO_UDTS_GAUGE_RX,     /* Received Unitdata service gauge */
  SO_RTG_FAILURE_GAUGE, /* Routing failure gauge */

  SO_TRANS_REQ_COUNT,   /* Translation request count */
  SO_TRANS_REQ_GAUGE,   /* Translation request gauge */
  SO_NOTIF,             /* notification of failure or exec */
                        /* indications due to config changes */
  SO_ADDED,             /* added an object */
  SO_REMOVED,           /* removed an object */
  SO_ACTIVATED,         /* activated an object */
  SO_DEACTIVATED,       /* deactivated an object */
  SO_LOCKED,            /* exclusive write access set */
  SO_UNLOCKED,          /* relinquished exclusive write access*/

  SO_CONFRESET,         /* entire sccp configuration is reset */
  SO_TRANSLATION_VALUE, /* translation value */
  SO_BACKUP_VALUE,      /* peer value */
  SO_VALUE,             /* mode of a remote sp */
                        /* Connection Oriented statistics */
  SO_DT1_COUNT_TX,      /* Transmitted DT1 traffic count */
  SO_DT1_COUNT_RX,      /* Received DT1 traffic count */
  SO_CR_COUNT_TX,       /* Transmitted CR traffic count */
  SO_CR_COUNT_RX,       /* Received CR traffic count */
  SO_CREF_COUNT_TX,     /* Transmitted CREF traffic count */
  SO_CREF_COUNT_RX,     /* Received CREF traffic count */
  SO_ERR_COUNT_TX,      /* Transmitted ERR traffic count */
  SO_ERR_COUNT_RX,      /* Received ERR traffic count */
  SO_GLOBAL_COUNT_TX,   /* Global traffic transmitted count */
  SO_GLOBAL_COUNT_RX,   /* Global traffic received count */
  SO_DT1_GAUGE_TX,      /* Transmitted DT1 traffic gauge */
  SO_DT1_GAUGE_RX,      /* Received DT1 traffic gauge */
  SO_CR_GAUGE_TX,       /* Transmitted CR traffic gauge */
  SO_CR_GAUGE_RX,       /* Received CR traffic gauge */
  SO_CREF_GAUGE_TX,     /* Transmitted CREF traffic gauge */
  SO_CREF_GAUGE_RX,     /* Received CREF traffic gauge */
  SO_ERR_GAUGE_TX,      /* Transmitted ERR traffic gauge */
  SO_ERR_GAUGE_RX,      /* Received ERR traffic gauge */
  SO_GLOBAL_GAUGE_TX,   /* Global traffic transmitted gauge */
  SO_GLOBAL_GAUGE_RX,   /* Global traffic received gauge */

}SccpOamStat;

/* Oam Report types */

typedef enum {
  /* prefix SO_ signifies `Sccp Oam' */
  SO_IMMEDIATE,           /* once only immediate rep   */
  SO_PERIODIC,            /* permanent periodic report */
  SO_OCCURRENCE,          /* report on occurrence      */
  SO_STOP_REPORTS,        /* stop reporting            */
  SO_STOP_ALL_REPORTS     /* stop all reporting        */

}SccpOamReport ;

/* Oam Object types */

typedef enum {

  SO_SCCP,          /* Local SCCP (Local SP) object    */
  SO_LOCAL_USER,    /* Local User (AUP) object         */
  SO_REMOTE_USER,   /* Remote User (AUP) object        */
  SO_REMOTE_SP,     /* Remote Signalling point object  */
  SO_FAILED_DEST,   /* Basket for unused primitives    */
  SO_GT_TRANSLATOR, /* Gloabal Title Translator object */
  SO_VIRTUAL_USER   /* Virtual User (AUP) object       */

}SccpOamObject ;

/* Oam State types */

typedef enum {

  SO_INSERVICE,   /* available state from RemoteNode   */
  SO_OUTOFSERVICE,/* unavailable state                 */
  SO_RESTARTING,  /* MTP restarting state from SCCP    */
  SO_CONGESTED,   /* MTP congested state from SCCP     */
  SO_UNCONGESTED, /* MTP uncongested state from SCCP   */
  SO_AVAILABLE,   /* SCCP available state              */
  SO_UNAVAILABLE, /* SCCP unavailable state            */
  SO_STOPPED,     /* SCCP disabled by the OAM          */
						      
  SO_UNDEFINED    /* no state defined                  */

}SccpOamState ;

/* Oam Parameter types. */

typedef enum {

  TIMER_1,
  TIMER_2
  /* etc, etc etc */

}SccpParm;

/* Union for parameter values */
#define MAXSTRING   80

typedef struct {

  int   intParm;
  char  strParm[MAXSTRING];
  /*float floatParm;*/

}SccpParmValue ;

/* Oam Object address definition */

#define SCCPMAXADDRLEVEL   2

/*
HP internal reserved comment line
@if not $_hp_reserved_s
*/

/* Object address identification: -
           (address identifying object is kept in an array {eg addr[]}
                as follows)

                object type             addr[1]         addr[0]
                -----------------------------------------------
                SO_SCCP                 -               Local PC
                SO_LOCAL_USER           SSN             Local PC
                SO_REMOTE_USER          SSN             DPC
                SO_REMOTE_SP            -               DPC
                SO_VIRTUAL_USER         SSN             VPC
*/
typedef int SccpOamAddress[SCCPMAXADDRLEVEL] ;

/*
hp reserved internal comment
@endif
*/

/* Oam Failure types
   Used for notifying failure due to operations or events via OAM interface
*/
typedef enum
{

  SO_EXECUTED = 0,            /* no failure: command executed              */
                              /* failure definitions for config commands   */
  SO_ILLEGAL_OPERATION,       /* impossible command                        */
  SO_OBJECT_NOT_FOUND,        /* no such object with specified ssn         */
  SO_OBJECT_EXISTS,           /* object with specified ssn exists already  */
  SO_REPEATED_COMMAND,        /* command already done!                     */
  SO_PERMISSION_DENIED,       /* not allowed to send config commands       */
  SO_DELETE_ALL_REMOTE_USERS, /* delete all managed remote users           */
                              /* to be able to delete the rempte SP        */
  SO_IMPOSSIBLE_DPC,          /* dpc of remoteSp = LocalPC not allowed!    */
  SO_NO_ACKNOWLEDGE,          /* no response to a command "FATAL ERROR"    */
  SO_ALREADY_LOCK,            /* Locked user tried to lock again           */
  SO_ALREADY_UNLOCK,          /* Locked user tried to lock again           */
  SO_ERROR_ON_CONFIG,         /* strange error on synchronize              */
                              /* failure due to a  statistics request      */
  SO_NO_SUCH_REPORT,          /* illegal report type!                      */
  SO_ILLEGAL_PERIOD,          /* requested period out of range not allowed */
  SO_REPEATED_REQUEST,        /* same periodic statistics already running! */
  SO_ILLEGAL_STATISTIC,       /* not implemented statistics !              */
  SO_ILLEGAL_REQUEST,         /* impossible request                        */
  SO_ILLEGAL_REPORT,          /* not allowed report type for statistic req */
  SO_NO_SUCH_OBJECT,          /* unknkown object to be monitored           */

  SO_FATAL_SYSTEM_ERROR,      /* fatal error while gathering statistics!   */

  SO_PRIORITY_EXISTS,         /* obj with specified priority already exists*/
  SO_UNCONFIGURED_VPC         /* corresponding VPC is not configured       */

}SccpOamFailure;

/* Oam structure for notification */

typedef struct
{

  SccpOamStat statistic;   /* type of statistic carried               */
  SccpOamObject  object;   /* type that notification is for           */
  SccpOamAddress address;  /* array containg object address info      */
  SccpOamState   state;    /* contains state of object if relevant    */
  float          value;    /* contains statistic value  if relevant   */
  char  sValue[MAXSTRING]; /* contains string stat value              */
  SccpOamFailure failure;  /* cause of failure for error report notif */

}SccpOamNotif ;

/* Oam notification type definition */

typedef enum {
  sccp_notif,
  sccp_config

}SccpOamInfoType;

/* Oam structure for statistic parameter */

typedef struct {

  ubool        reset;      /* set or reset a statistic     */
                           /* when yes the already existing*/
                           /* statistic counter is reset to*/
                           /* the 0 value                  */
  SccpOamReport rep_type;  /* type of report               */
  int          value;      /* period                       */
  ubool        reset_auto; /* reset to 0 the statistic     */
  /* counter after report         */

}SccpOamStParms;

/* Oam structure describing an SCCP Oam Object */

typedef struct
{

  SccpOamObject  obj_type; /* type of object             */
  SccpOamAddress address;  /* identification of object   */
  SccpOamState   state;    /* current state of object    */
  int            parm;     /* parameter                  */

} SccpOamObjDesc;

/* Oam structure for configuration notification */

typedef struct
{

  int    number_of_objects;      /* number of spaces used in record */
                                 /*  table                          */
  SccpOamObjDesc object_table[SCCPMAXOBJINMSG];/* table of objects  */

} SccpConfSet;

/* Structure containing information in an Oam primitive handled in the SCCP
   internaly (as result of a command sent before)                          */

typedef struct
{

  void *         entityId;    /* pointer to the affected entity   */
  SccpOamObject  so_object;   /* object type of a protocol entity */
  SccpOamAddress so_obj_addr; /* address of the protocol entity   */
  SccpOamState   so_obj_state;    /* current state of object    */
  int            parm_id;     /* parameter identifier */
  SccpParmValue  parm_value;  /* parameter value */

}SO_PRIMIT_PARMS;

/*=============================== PROTOTYPING ==============================*/

#ifndef NOPROTOTYPE

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  HP_DLL_IF int SCCP_oamcmd (int            cnxId,
			     struct timeval *time,
			     void           *context,
			     SccpOamObject  object,
			     SccpOamAddress address,
			     SccpOamCmd     command,
			     SccpCmdParms   *cmdparms);

  HP_DLL_IF int SCCP_oamrecv (int                   cnxId,
			      struct timeval        *time,
			      void                  **context,
			      SccpOamInfoType       *notiftype,
			      char                  *notifstruct);

  HP_DLL_IF int SCCP_oamstat (int                   cnxId,
			      struct timeval        *time,
			      void                  *context,
			      SccpOamObject         object,
			      SccpOamAddress        address,
			      SccpOamStat           statistic,
			      SccpOamStParms        *statparms);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* NOPROTOTYPE */

#endif /* SCCP_OAM_API_H */
/*********************** DEFINITIONS END **********************************/
