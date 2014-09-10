/***********************************************************
*
* 
*
* $Source: /7UP/code/tcapEnvironment/TCAP_common.h $
* $Revision: 5.6 $
* 
* 
***********************************************************/
/*
  ======================================================================
 |                     COMMOM TCAP API include file                     |
 |                                                                      |
 |               ANSI / CCITT BLUE BOOK / CCITT WHITE BOOK              |
 |                                                                      |
 | HEWLETT PACKARD SS7                                                  |
 | (c) Copyright 1994, Hewlett-Packard Company, all rights reserved     |
 |                                                                      |
  ======================================================================
*/

#include "TCAP_errors.h"

#ifndef TCAP_COMMON_H
#define TCAP_COMMON_H

#define MAX_U_ABORT_LEN            200
#define MAX_PARAMETER_LEN          240

#define MAX_DIGITS                  30
#define MAX_FIELD                  100

#define TC_BOOL                    int
#define TC_NO                        0
#define TC_YES                       1

#define NO_TIMER            0xFFFFFFFF

#define NO_COMPONENTS           999999
#define IMMEDIATE_REPORT             0
#define STOP_REPORT                 -1
#define STATS_ONLY                  -1

#ifdef _WIN32
#  include "ainCommon.h"
#  ifndef HP_DLL_IF
#    define HP_DLL_IF __declspec(dllimport)
#  endif
#else
#ifndef HP_DLL_IF
#define HP_DLL_IF 
#endif
#endif /* _WIN32 */

extern tc_error_code tc_errno ;
extern HP_DLL_IF char* tc_error_text[] ;

/*----------------------------------------------------------------------
 |                        TC_OPEN parameters                           |
 ----------------------------------------------------------------------*/

typedef enum InstanceStatus {
  STANDBY_INSTANCE_STATUS = 2,
  ACTIVE_INSTANCE_STATUS  = 3
} InstanceStatus;

typedef struct tc_service_parms_struct {

  int           ssn;                        /*        subsystem number */
  char          * SS7_name;                 /*               host name */
  TC_BOOL       enable_comp_layer;          /*  enable component layer */
  TC_BOOL       backup;                     /*        CL set as backup */
  TC_BOOL       active;                     /*  disable receipt of new
                                                    incoming dialogues */
 } tc_service_parms;

/*----------------------------------------------------------------------
 |                      PRIMITIVES definitions                         |
 ----------------------------------------------------------------------*/

typedef struct tc_sce_quality_struct {

  TC_BOOL         optional_parameter; 
  /* This parameter must be set to either TC_YES or TC_NO.
     You can set it to TC_YES to use default quality parameters.
     In this case the following return_option and sequence_control
     parameters are ignored.  
     You must set it to TC_NO if you want to control either the
     sequence_control or the return_option parameters below
     */

  TC_BOOL         return_option;     /* default : TC_NO */
  unsigned char   sequence_control;        /*      0: no sequence (default) */
                                           /* 1..255: sequence number */
 } tc_sce_quality;


/*----------------------------------------------------------------------
 |                    GLOBAL TITLE related parameters                  |
 ----------------------------------------------------------------------*/

typedef enum {

              tc_no_gt    = 0,
              tc_gt_type1 = 1,
              tc_gt_type2 = 2,
              tc_gt_type3 = 3,
              tc_gt_type4 = 4

             } tc_gt_indicator;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              tc_t_unused          = 0,
              tc_t_internetwork    = 1,
              tc_t_networkspecific = 254

             } tc_translation;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              tc_unknown_num         = 0,
              tc_num_isdn            = 1,
              tc_num_userdata        = 3,
              tc_num_telex           = 4,
              tc_num_maritime_mobile = 5,
              tc_land_mobile         = 6,
              tc_isdn_mobile         = 7

             } tc_numbering_plan;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              tc_unknown_encode = 0,
              tc_bcd_odd        = 1,
              tc_bcd_even       = 2

             } tc_encoding_scheme;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              tc_subscriber_nb    = 1,
              tc_national_nb      = 3,
              tc_international_nb = 4

             } tc_address_nature;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct  {

   TC_BOOL             routeOnGt;     /* TC_YES: GT is used for routing */
   tc_gt_indicator     gtIndicator;   /*              global title type */
   tc_translation      translation;
   tc_numbering_plan   numbering;
   tc_encoding_scheme  encoding;
   tc_address_nature   nature;
   char                digit [MAX_DIGITS];

  } tc_global_title;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum { BASIC, PREARRANGED } tc_termination_type;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              TC_NOTRANSLATION_NATURE,
              TC_NOTRANSLATION_SPECIFIC,
              TC_SUBSYSTEM_CONGESTION,
              TC_SUBSYSTEM_FAILURE,
              TC_UNEQUIPPED_USER,
              TC_NETWORK_FAILURE,
              TC_NETWORK_CONGESTION,
              TC_UNQUALIFIED

             } tc_transport_return_reason;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {                  /* SCCP Point Code status */

              SCCP_INAC,
              SCCP_CONGESTED,
              SCCP_ACCESSIBLE,
              SCCP_RESTARTING,
              SCCP_UNCONGESTED

             } tc_status_pc;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {                        /*    SCCP User status */

              SCCP_UIS,               /*     User in service */
              SCCP_UOS                /* User out of service */

             } tc_status_user;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

         SCCP_GRANTED_WITHDRAWAL, /*    "granted" N_COORD confirmation  */
         SCCP_DENIED_WITHDRAWAL,  /*      "denied" N_COORD confirmation */
         SCCP_NO_PEER             /* no backup is configured, gracefull
                                                withdrawal is processed */
        } tc_confirm_status;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              SCCP_MULTINDUNKNOWN    = 0,
              SCCP_MULTINDSOLITARY   = 1,
              SCCP_MULTINDDUPLICATED = 2

             } tc_smi;


/*-------------------------------------------------------------------------
 |                      TC_CONTROL parameters                             |
 -------------------------------------------------------------------------*/

typedef enum {

	/* Command related to the memory managment: */
	/* Set the maximum memory size allowed for the tcap API. */
	SET_API_MEMORY_SYZE ,

	/* Commands related to IPC communication with TCAP process */
	/* Copy the current connection infos (  low  and  high  transit */
	/* time  and  tx/rx buffer sizes ) to the field cnx_info of the */
	/* structure tc_control_parms. */
	GET_CONNECTION_INFO,
	/* Bufferize messages sent with TC_send locally  in  API.  This */
	/* allow  performances  optimisation especially by reducing the */
	/* number of IPC system calls. Buffering should be done as soon */
	/* as the application requires high message throughput. To send */
	/* the buffer, it's necessary to use a OUT_BUFFER_FLUSH */
	/* or OUT_BUFFER_FLUSH_COND command. */
	OUT_BUFFER_BLOCK,
	/* Flush message buffer automatically  after  each  TC_send  or
					TL_send call. */
	OUT_BUFFER_DONT_BLOCK,
	/* Flush message buffer. Set OUT_BUFFER_BLOCK first. */
	OUT_BUFFER_FLUSH,
	/* Flush message buffer  only  if  one  of  the  two  following
		conditions is met:
			- OUT_BUFFER is full.
			- The transit time of the  oldest  message  stored  in
				buffer  has been exceeded. The transit time value is in
				a range between a low transit time and a  high  transit
				time.  Low transit time is the value available with low
				traffic, high transit time with high traffic. */
	OUT_BUFFER_FLUSH_COND,
	/* Set the size of the IPC  transmit  buffer.   Use  the  value
		member  of  tc_control_parms.  Maximum  size is 65535 bytes.
		Default value is 8000 bytes. */
	OUT_IPC_BUFFER_SIZE,
	/* Set the size of the  IPC  received  buffer.  Use  the  value
		member  of  tc_control_parms.   Maximum size is 65535 bytes.
		Default value is 8000 bytes. */
	IN_IPC_BUFFER_SIZE,
	/* Set the  delay  of  queing  messages  in  OUT_BUFFER  before
		transmission  with  IPC  with  a minimum throughput. Unit is
		microseconds. Refer to OUT_BUFFER_FLUSH_COND parameter.  Use
		the value member of tc_control_parms Default value is 20 000
		microseconds. */
	LOW_TRANSIT_TIME,
	/* Set the  delay  of  queing  messages  in  OUT_BUFFER  before
		transmission  with  IPC  with  a maximum throughput. Unit is
		microseconds. Refer to OUT_BUFFER_FLUSH_COND parameter.  Use
		the  value  member  of tc_control_parms Default value is 100
		000 microseconds. */
	HIGH_TRANSIT_TIME,

	/* Facilities for dialogue and components handling: */
	/* Set the reject time used by the  component  sublayer  during
		the  "wait  for  reject"  time  at  the  end of a successful
		operation.   When  the  reject   timer   is   expired,   the
		corresponding  invoke  ID  is released and can be reused for
		another operation. */
	SET_REJECT_TIME,
	/* Set the active flag to  TC_NO  when  the  TC_user  needs  to
		disconnect  smoothly without loosing last incoming messages.
		Receives last messages related to opened  transactions,  but
		do not receive new transactions. */
	DESACTIVATE,
	/* Set the active flag to TC_YES. See previous command. */
	ACTIVATE,
	/* Requests  allocation  by  the  TCAP  API  of  one  or  more
		components in a component list. Set the number of components
		to allocate in comp_num field of  the  component  structure.
		The  result  is comp_ptr member of component which returns a
		pointer to the first component of the list. */
	GET_COMPONENTS_LIST,
	/* frees  a  list  of  components.  Set  component  member  of
		tc_control_parms  with  a  pointer to the first component of
		the list to freed. */
	FREE_COMPONENTS,

	/* The following commands do not return an immediate result after the call.
 The result is returned by means of MGT indications, got with TC_recv  call.
 These  statistics  fully  comply  with  Q752  CCITT  recommendation.   Some
 statistic  requests  trigger   a   multiple   report   containing   several
 notifications  (e.g.  one  per  P_ABORT  cause for the STAT_ABORT_SENT/RECV
 statistic requests). In this case, and to allow the TC_user  to  know  when
 the report is finished, a special notification stats_end is sent at the end
 of the report. 

	 Active  transactions  count.   The  field  period_value  of
		tc_control_parms sets the period of the statistic. */
	STAT_ACTIVE_TRANSACTIONS,
	/* Active transactions count which have been killed  internally
		by  TCAP.   The  field period_value of tc_control_parms sets
		the period of the statistic. */
	STAT_TRANSACTIONS_KILLED_BY_TIMER,
	/* TCAP users load. Returns  several  notifications,  with  the
		User  number,  its  SSN,  and  the average tcap messages per
		seconds.  The field period_value  of  tc_control_parms  sets
		the  period  of the statistic (multiple notifications report
		with stats_end indication). */
	STAT_USER_LOAD,
	/* Total number of TCAP messages sent.  The field  period_value
		of tc_control_parms sets the period of the statistic. */
	STAT_NODE_MSG_SENT,
	/* Total  number  of  TCAP  messages  received.    The   field
		period_value  of  tc_control_parms  sets  the  period of the
		statistic. */
	STAT_NODE_MSG_RECV,
	/* Protocol error in transaction portion   received  (P_ABORT).
		The  field  period_value of tc_control_parms sets the period
		of  the  statistic  (multiple  notifications   report   with
		stats_end indication). */
	STAT_ABORT_RECEIVED,
	/* Protocol error in transaction portion sent  (P_ABORT).   The
		field  period_value  of  tc_control_parms sets the period of
		the statistic (multiple notifications report with  stats_end
		indication). */
	STAT_ABORT_SENT,
	/* Protocol  error  detected  in  component  portion   (reject
		received).  The  field period_value of tc_control_parms sets
		the period of the statistic. (multiple notifications  report
		with stats_end indication). */
	STAT_REJECT_RECV,
	/* Protocol error detected in component portion (reject  sent).
		The  field  period_value of tc_control_parms sets the period
		of  the  statistic.  (multiple  notifications  report   with
		stats_end indication). */
	STAT_REJECT_SENT,
	/* Protocol error detected  by  the  remote  application  (user
		reject received). The field period_value of tc_control_parms
		sets the period of the  statistic.  (multiple  notifications
		report with stats_end indication). */
	STAT_U_REJECT_RECV,
	/* Protocol error  detected  by  the  local  application  (user
		reject  sent).  The  field  period_value of tc_control_parms
		sets the period of the  statistic.  (multiple  notifications
		report with stats_end indication). */
	STAT_U_REJECT_SENT,
	/* Number of component received. */
	STAT_COMPONENT_RECV,
	/* Number of component sent. */
	STAT_COMPONENT_SENT,
	/* Reset statistics counters. */
	RESET_STATS,

	/* flush component */
	/* This command will flush all pending components for the transaction 
		indicated by UID, PID for a given connexion id. 
		*/
	FLUSH_COMPONENTS,
	stats_end   

 } tc_control_c;

#ifdef __GNUC__
#include <sys/time.h>
#endif /* __GNUC__ */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef union tc_control_parms_struct{

  /*~~~~~~~~~~~~~~~~ OUT_BUFFER relative commands ~~~~~~~~~~~~~~~~~~~~*/
  int            value;

  /*~~~~~~~~~~~~~~~~ reject timer for operation   ~~~~~~~~~~~~~~~~~~~~*/
  struct timeval timer;


  /*~~~~~~~~~~~~~~~~ Statistics request ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*  units: seconds. 0 means immediate report, -1 means stop report  */

  int period_value;


  /*~~~~~~~~~~~~~~~~ request memory allocation ~~~~~~~~~~~~~~~~~~~~~~~*/
  /*       for GET_COMPONENT_LIST / FREE_COMPONENTS commands          */

  struct component_struct
     {
      struct tc_component * comp_ptr;
      int                 comp_num;

     } component;

  /*~~~~~~~~~~~~~~~~ connection information ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  struct cnx_info_struct
     {
      int low_transit_time;
      int high_transit_time;
      int tx_buffer_size;
      int rx_buffer_size;

     } cnx_info;
	
	/* transaction identifiers */
	struct TransactionIdsStruct {
		unsigned int userId;
		unsigned int providerId;
		} transactionIds ;

} tc_control_parms;

#ifdef _WIN32
/*-------------------------------------------------------------------------
 |                      TC_STARTUP parameters                             |
 -------------------------------------------------------------------------*/
typedef int tc_startup_parameter;
#endif /* _WIN32 */

/*----------------------------------------------------------------------
 |           MACROS for access to the tc_primitive structure           |
 ----------------------------------------------------------------------*/

#define TC_P_TYPE(aStruct)        ((aStruct)->p_type)
#define TC_P_SCE_QUALITY(aStruct) ((aStruct)->service_quality)
#define TC_P_D_ADDR(aStruct)      ((aStruct)->d_address)
#define TC_P_O_ADDR(aStruct)      ((aStruct)->o_address)
#define TC_P_USER_ID(aStruct)     ((aStruct)->user_dialogue_id)
#define TC_P_PROVIDER_ID(aStruct) ((aStruct)->provider_dialogue_id)

#define TC_P_UABORT(aStruct) \
    ((aStruct)->tc_primitive_option.u_abort_cause)
#define TC_P_TERMINATION(aStruct) \
    ((aStruct)->tc_primitive_option.termination_type)
#define TC_P_REPORT(aStruct) \
    ((aStruct)->tc_primitive_option.report_cause)
#define TC_P_PABORT(aStruct) \
    ((aStruct)->tc_primitive_option.p_abort_cause)

#define TC_P_STAT_TYPE(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.stat_type)
#define TC_P_CONTEXT(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.context)
#define TC_P_STAT_VALUE(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.value)
#define TC_P_NUM_P_ABORT(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.abort.value)
#define TC_P_P_ABORT_CAUSE(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.abort.p_abort)
#define TC_P_NUM_REJECT(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.reject.value)
#define TC_P_P_REJECT_CAUSE(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.reject.p_code)

#define TC_P_P_REJECT_IDENTIFIER(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.reject.p_identifier)
#define TC_P_USER_ID_ID(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.u_load.user_id)
#define TC_P_USER_ID_SSN(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.u_load.ssn)
#define TC_P_USER_ID_LOAD(aStruct) \
    ((aStruct)->tc_primitive_option.tc_stat.p.u_load.load)

#define TC_P_PC_STATUS(aStruct) \
    ((aStruct)->tc_primitive_option.tc_pcstatus.status)
#define TC_P_DESTINATION(aStruct) \
    ((aStruct)->tc_primitive_option.tc_pcstatus.destConcerned)
#define TC_P_AFFSSN(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ustatus.affectedSSN)
#define TC_P_ASSPC(aStruct)  \
    ((aStruct)->tc_primitive_option.tc_ustatus.associatedPC)
#define TC_P_USER_STATUS(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ustatus.status)
#define TC_P_NCOORD_AFFSSN(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ncoord.affectedSSN)
#define TC_P_NCOORD_ASSPC(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ncoord.associatedPC)
#define TC_P_NCOORD_STATUS(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ncoord.status)
#define TC_P_NCOORD_SMI(aStruct) \
    ((aStruct)->tc_primitive_option.tc_ncoord.multInd)

   
#endif /* TCAP_COMMON_H */
