/***********************************************************
*
* 
* $Source: /7UP/code/tcapExtLibs/TCAP_ext.h $
* $Revision: 6.0 $
* 
* 
***********************************************************/
/*
  ======================================================================
 |                          TCAP API include file                       |
 |                         Special version for GDI                      |
 |                                                                      |
 |                                                                      |
 | HEWLETT PACKARD SS7                                                  |
 | (c) Copyright 1997, Hewlett-Packard Company, all rights reserved     |
 |                                                                      |
  ======================================================================
*/


#ifndef TCAP_EXT
#define TCAP_EXT

/* TCAP API version management and backward compatibility  */

/* ANSI */
#if defined (TCAP_ANSI90) || defined (TCAP_ANSI)
# if defined (TCAP_API100) 
#  define _TCAP_ANSI 199001L
# else
#  define _TCAP_ANSI 199601L
# endif

/* ITU WHITE */
#elif defined (TCAP_WHITE)
# define _TCAP_ITU 199201L

/* ITU BLUE */
#else 
# define _TCAP_ITU 198801L
#endif 

#ifdef _TCAP_ANSI
# include "TCAP_ansi.h"
#else 
# include "TCAP_ccitt.h"
#endif

#include "ss7_if.h"

#define GDI_SSN 256
/* special local SSN for access to GDI transport is currently 256 */

#define GDI_MAX_PARAMETER_LEN  4000
#define GDI_MAX_TC_TOTAL_LENGTH 4000

#define MAX_TC_EXT_PARAMETER_LEN 2000
#define MAX_TC_EXT_TOTAL_LENGTH 2000

typedef enum tcx_sccp_service_enum {
  /* regular sccp service with 256 bytes data segment */
  TCX_SCCP_SERVICE_REGULAR       = 0x0000,
  /* sccp with ITU WB capabilities */
  TCX_SCCP_SERVICE_ITU_WB        = 0x0001,
  /* sccp with ANSI 96 Extended Messages capabilities (without ISNI) */
  TCX_SCCP_SERVICE_ANSI96_NOISNI = 0x0002,
  /* TCAP traffic only(no SCCP management) */
  TCX_SCCP_NO_MGT                = 0x0100,
  /* no traffic, SCCP management only */
  TCX_SCCP_MGT_ONLY              = 0x0200
} tcx_sccp_service ;

typedef struct tcx_buffer_struct {
  int    max_length;     /* the size of the buffer pointed to by bufferp */
  int    actual_length;  /* the length of user data in the buffer */
  char*  bufferp;        
  /* pointer to the user data buffer, i.e a buffer allocated by the user.
     DO NOT change the value of this pointer */
} tcx_buffer;


typedef struct tcx_component_struct {
  struct tcx_component_struct* next_component; /* next in chain */
  tc_component_type            c_type;         /* component type */
  int                          op_class;       /* operation class  1..4 */
  int                          invoke_id;      /* -1= absent */
#ifndef _TCAP_ANSI
  int                          linked_id;      /* optional: -1= absent */
#else /* _TCAP_ANSI */
  int                          correlation_id; /* optional: -1= absent */
#endif /* _TCAP_ANSI */
  tc_operation                 operation;      /* operation code */
  struct timeval               timer;          /* operation timeout value */
  tc_error                     error;          /* error code (error component)*/
  tc_pcode                     problem_code;   /* reject code */
#ifdef _TCAP_ANSI
  tc_parm_type                 parameter_type; /* SEQUENCE_TYPE or SET_TYPE */
#endif /* _TCAP_ANSI */
  tcx_buffer*                  parameter;      /* pointer to a data buffer  */
} tcx_component;


typedef enum tcx_sccp_class_enum {
  TCX_SCCP_CLASS0 = 0,
  TCX_SCCP_CLASS1 = 1
} tcx_sccp_class;

typedef enum tcx_importance_enum {
  TCX_IMPORTANCE_LOW    =0,
  TCX_IMPORTANCE_MEDIUM =1,
  TCX_IMPORTANCE_HIGH   =2
} tcx_importance;


typedef struct tcx_sccp_service_quality_struct {
  TC_BOOL         use_default_values;
  /*  This parameter must be set to either TC_YES or TC_NO.  You can
     set it to TC_YES to use default quality parameters.  In this case
     the following sccp_return_option, sccp_service_class &
     sccp_sequence_control parameters are ignored. 
     */
  
  TC_BOOL         sccp_return_option; 
  /* default: TC_NO .  In the default case the stack does not send
     TC_notice messages back to the application in case of problems */

  TC_BOOL       sccp_use_extended_data;
  /* default: TC_NO . By default SCCP is using XUDT message to
     transport TCAP transactions only if data cannot fit in UDT
     message and has to be segmented. If the application wants to
     force the use of XUDT messages for all TCAP transcations
     whatever the data size, this parameter should be set to
     TC_YES.  */

  tcx_sccp_class  sccp_service_class; 
  /* default: TCX_SCCP_CLASS0  By default, the SCCP class 0 is
     used. Remember that this means that there is no guarantee of
     sequential delivery of TCAP messages to the remote. If this must
     be guaranteed, use the SCCP class 1, and make sure to use
     different sccp_sequence_control values for different TCAP
     transactions (otherwise all the TCAP messages are sent over a
     same SS7 link).  */

  tcx_importance        sccp_importance;
  /* default: TCX_IMPORTANCE_LOW.
     This parameter is reserved for a future use to indicate the 
     importance of the message. It is currently ignored by the 
     SCCP layer. */

  unsigned char   sccp_sequence_control;  
  /* 0..255: sequence number - only relevant for class 1 */

} tcx_sccp_service_quality;
/* tcx_sccp_service_quality allows the user to specify in clear the
   requested sccp class */


typedef enum tcx_transport_return_reason_enum {
  TCX_NOTRANSLATION_NATURE,
  TCX_NOTRANSLATION_SPECIFIC,
  TCX_SUBSYSTEM_CONGESTION,
  TCX_SUBSYSTEM_FAILURE,
  TCX_UNEQUIPPED_USER,
  TCX_NETWORK_FAILURE,
  TCX_NETWORK_CONGESTION,
  TCX_UNQUALIFIED,
  TCX_ERRORIN_TRANSPORT,
  TCX_ERRORIN_LOCAL_PROCESSING,
  TCX_NODEST_REASSEMBLY,
  TCX_SCCP_FAILURE,
  TCX_SCCP_HOP_VIOLATION,
  TCX_SEGMENTATION_NOTSUPPORTED,

  TCX_GDI_TASK_REFUSED = 100,
  TCX_GDI_UNAUTHORIZED_REQUEST,
  TCX_GDI_QUEUE_FULL,
  TCX_GDI_RESULT_TOO_LONG,
  TCX_GDI_SYSTEM_NOT_RESPONDING,
  TCX_GDI_GENERAL_FAILURE,
  TCX_GDI_TIMER_EXPIRED,
  TCX_GDI_INCOMPATIBLE_VERSION,

  TCX_SEGMENTATION_FAILURE = 249,
  TCX_INVALID_ISNI_ROUTING_RQ,     /* reserved for future use */
  TCX_UNAUTHORIZED_MESSAGE,        /* reserved for future use */
  TCX_MESSAGE_INCOMPATIBILITY,     /* reserved for future use */
  TCX_ISNI_CONSTR_ROUTING_ERROR,   /* reserved for future use */
  TCX_ISNI_REDUNDANT_ROUTING,      /* reserved for future use */
  TCX_ISNI_IDENTIFY_ERROR          /* reserved for future use */

} tcx_transport_return_reason;


struct tcx_abort_struct          /*  For STAT_ABORT_RECEIVED/SENT */
{               
  int value;                     /*             Number of P_ABORT */
  tc_p_abort_cause  p_abort;     /*        for this P_ABORT cause */
} ;

struct tcx_reject_struct         /*     For STAT_REJECT_RECV/SENT */
{                 
  int value;                     /*              Number of REJECT */
  tc_pb_identifier p_identifier; /*          for this REJECT type */
  tc_pb_code  p_code;            /*          and this REJECT code */
} ;

struct tcx_u_load_struct         /*            For STAT_USER_LOAD */
{          
  int user_id;                   /*    User identification number */
  int ssn;                       /*              Subsystem number */
  int load;                      /*           Number of TCmsg/sec */
} ;

union tcx_p_union
{
  int                      value;   /*         All statistics result */
  
  struct tcx_abort_struct  abort;

  struct tcx_reject_struct reject;
  
  struct tcx_u_load_struct u_load;
} ;

/*~~~~~~~~~~~~~~~~~~~~~~~   MGT parameters  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct tcx_stat_struct
{
  tc_control_c      stat_type;         /* Statistic type identification */
#ifdef __LP64__
  int                 context;         /* request number identification */
#else
  void              * context;         /* request number identification */
#endif
  union tcx_p_union p;
} ;

/*~~~~~~~~~~~~~~~~~~~   SCCP_PC_STATUS parameters  ~~~~~~~~~~~~~~~~~~~~~*/
struct tcx_pcstatus_struct
{
  tc_status_pc    status;               /*    Status of the destination */
  int             destConcerned;        /*  PC of concerned destination */
} ;

/*~~~~~~~~~~~~~~~~~~~  SCCP_USER_STATUS parameters ~~~~~~~~~~~~~~~~~~~~~*/
struct tcx_ustatus_struct
{
  int             affectedSSN;         /*            Subsystem number   */
  int             associatedPC;        /*       signalling point code   */
  tc_status_user  status;              /*    status of concerned user   */
} ;

/*~~~~~~~~   SCCP_N_COORD or SCCP_N_COORD_RES parameters ~~~~~~~~~~~~~~~*/
struct tcx_ncoord_struct        /* for SCCP_N_COORD or SCCP_N_COORD_RES */
{        
  int               affectedSSN;       /*           Subsystem number    */
  int               associatedPC;      /*      signalling point code    */
  tc_confirm_status status;            /*  for SCCP_N_COORD_RES only,
                                           use to confirm withdraw      */
  tc_smi            multInd;           /* for SCCP_N_COORD_RES only,
                                        Subsystem multiplicity indicator*/
};

typedef  union tcx_primitive_option {
  tc_u_abort                    u_abort_cause;  
  tc_termination_type           termination_type;
  tcx_transport_return_reason   report_cause;
  tc_p_abort_cause              p_abort_cause;

  /*~~~~~~~~~~~~~~~~~~~~~~~   MGT parameters  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  struct tcx_stat_struct        tc_stat ;

  /*~~~~~~~~~~~~~~~~~~~   SCCP_PC_STATUS parameters  ~~~~~~~~~~~~~~~~~~~~~*/
  struct tcx_pcstatus_struct    tc_pcstatus;

  /*~~~~~~~~~~~~~~~~~~~  SCCP_USER_STATUS parameters ~~~~~~~~~~~~~~~~~~~~~*/
  struct tcx_ustatus_struct     tc_ustatus;

  /*~~~~~~~~   SCCP_N_COORD or SCCP_N_COORD_RES parameters ~~~~~~~~~~~~~~~*/
  struct tcx_ncoord_struct      tc_ncoord;
} tcx_primitive_option;


/* the extended primitive structure definition */

typedef struct tcx_primitive_struct {  
 tc_primitive_type        p_type;               /* Primitive type           */
 tcx_sccp_service_quality service_quality;      /* Service quality          */
 tc_address               d_address;            /* destination address      */
 tc_address               o_address;            /* originating address      */
 unsigned int             user_dialogue_id;     /* user dialogue identifier */
 unsigned int             provider_dialogue_id; /* TCAP dialogue identifier */

/* Only available in ANSI 96 and ITU White Book standards */
#if (defined _TCAP_ITU) || (_TCAP_ANSI >= 199601L) 
 tc_dialog_portion        dialog_portion;       /* Dialogue Portion         */
#endif 

 tcx_primitive_option     tc_primitive_option;  /* primitive type related
                                                   options                  */
} tcx_primitive;


/* PROTOTYPES AND PARAMETER STRUCTURES*/

typedef int tcx_cnxid;

typedef enum tcx_appid_mode_enum {TCX_CNX_OVERWRITE=0} tcx_appid_mode;

typedef enum tcx_tcap_service_enum {
	TCX_TCAP_STD=0x0000,
	TCX_TCAP_ANSI96=0x1000
} tcx_tcap_service;

#define TCX_TCAP_ANSI90 TCX_TCAP_STD
#define TCX_TCAP_ITU92 TCX_TCAP_STD
#define TCX_TCAP_ITU88 TCX_TCAP_STD

typedef struct tcx_application_info_struct {
   tcx_appid_mode  mode;
   int         application_id;
   int         instance_id;
} tcx_application_info;

#ifndef NOPROTOTYPE
#ifdef __cplusplus
extern "C" {
#endif

/* TCX_open gives access to the TCAP component sub-layer or 
   transaction sub-layer */

  HP_DLL_IF
  tcx_cnxid TCX_open (
                      /* SS7 class name */
                      char*               SS7_name,
                      /* id of the requested TCAP service */
                      tcx_tcap_service       tcap_service_id,
                      /* subsystem number */
                      int                    ssn,
                      /*  enable component layer */
                      TC_BOOL                enable_comp_layer, 
                      /* TC_YES means that dialogues are accepted */
                      TC_BOOL                active, 
                      /* must be null if no application info is provided */
                      tcx_application_info*  appli_info, 
                      /* kind of sccp service requested */
                      tcx_sccp_service       sccp_service_kind,
                      /* connection timeout */
                      struct timeval        *timeout
                      );

  HP_DLL_IF
  tcx_cnxid TCX_tool_open (
                      /* SS7 class name */
                      char*               SS7_name,
                      /* id of the requested TCAP service */
                      tcx_tcap_service       tcap_service_id,
                      /* subsystem number */
                      int                    ssn,
                      /*  enable component layer */
                      TC_BOOL                enable_comp_layer, 
                      /* TC_YES means that dialogues are accepted */
                      TC_BOOL                active, 
                      /* must be null if no application info is provided */
                      tcx_application_info*  appli_info, 
                      /* kind of sccp service requested */
                      tcx_sccp_service       sccp_service_kind,
                      /* connection timeout */
                      struct timeval        *timeout,
                      /* Type of process: ORDINARY MONITOR or SYNCHRO */
                      ss7up_proc_type       procType
                      );

  HP_DLL_IF
  int TCX_close(tcx_cnxid cnx_id);

/* Memory management of tcx_component structures */

/* TCX_alloc_component returns no_of_components chained tcx_component
   structures in the pointer comp_listp. 
   Note that the parameter field of each tcx_component structure is set
   to NULL. It is the responsibility of the user to allocate a TCX_buffer
   structure, if this field must be assigned a value.
   This function returns 0 when it succeeds and -1 when it fails.
   In this case, the tc_errno variable is set to one of the following:

   TCE_ILLEGAL_VALUE  The comp_listp parameter is NULL

   TCE_MEMORY_ERROR   No more memory is available
*/
  HP_DLL_IF
  int TCX_alloc_component(tcx_component** comp_listp,
                          unsigned int    nb_of_components);

/* TCX_free_components frees the list of chained components passed in
   the component parameter. It also frees all the tcx_buffer structures
   pointed to by the parameter field of each returned component (if not
   NULL).This function returns 0 when it succeeds and -1 when it fails.
   In this case, the tc_errno variable is set to one of the following:

   TCE_ILLEGAL_VALUE  One of the structures of type tcx_component or 
                      tcx_buffer is malformed (a possible error is that 
                      a parameter field of one of the components has been 
                      over-written, and is no longer equal to NULL or 
                      pointing to a tcx_buffer structure).
*/
  HP_DLL_IF
  int TCX_free_components(tcx_component* comp_list); 


/* Same error as for TCX_free_components.
   Note that the behaviour of TCX_flush_components is to free all the 
   tcx_components still allocated by the TCAP lib for the transaction 
   identified by the couple (uid,pid).
   As for TCX_free_component, all the tcx_buffer structures pointed to 
   by the parameter field of each component are freed as well.
*/
  HP_DLL_IF
  int TCX_flush_components(tcx_cnxid cnx_id, int uid, int pid);


/* TCX_alloc_buffer returns one buffer of type tcx_buffer big enough to
   store the number of bytes given in the size parameter.
   This function returns 0 when it succeeds and -1 when it fails. 
   In this case, the tc_errno variable is set to one of the following:

   TCE_ILLEGAL_VALUE  The buffer parameter is NULL

   TCE_MEMORY_ERROR   No more memory is available
*/
  HP_DLL_IF
  int TCX_alloc_buffer(tcx_buffer** buffer_listp,
                       unsigned int size);   /* requested size of buffer */


/* TCX_free_buffer frees a structure of type tcx_buffer.
   This function returns 0 when it succeeds and -1 when it fails. 
   In this case, the tc_errno variable is set to one of the following:

   TCE_ILLEGAL_VALUE  The buffer parameter is corrupted or has already
                      been freed (i.e. attempt to free twice the same buffer)
*/
  HP_DLL_IF
  int TCX_free_buffer(tcx_buffer* bufferp);


/* On the out-going side: */

  HP_DLL_IF
  int TCX_put_component (tcx_cnxid      cnx_id,
                         int            user_dialogue_id,
                         int            provider_dialogue_id,
                         tcx_component* componentp);

  HP_DLL_IF
  int TCX_send (tcx_cnxid       cnx_id,
                struct timeval* time,
                tcx_primitive*  primitive,
                tcx_component*  comp_list);

  HP_DLL_IF
  int TLX_send (tcx_cnxid       cnx_id,
                struct timeval* time,
                tcx_primitive*  primitive,
                char*           component_table,
                int             length);


/* On the in-going side: */

  HP_DLL_IF
  int TCX_recv (tcx_cnxid         cnx_id,
                struct timeval*   time,
                tcx_primitive*    primitive,
                tcx_component**   comp_listp, 
                int*              more_message);


  HP_DLL_IF
  int TCX_get_component (tcx_cnxid       cnx_id, 
                         unsigned int    user_dialogue_id,
                         unsigned int    provider_dialogue_id,
                         tcx_component** componentp);
  

  HP_DLL_IF
  int TLX_recv (tcx_cnxid       cnx_id,
                struct timeval* time,
                tcx_primitive*  primitive,
                char*           component_table,
                int*            more_message);

/* Connections and statistics management */
  HP_DLL_IF
  int TCX_control(int                 connection_id, 
                  void              * context,
                  tc_control_c        command,
                  tc_control_parms 	* parameter);

#ifndef _WIN32

  HP_DLL_IF
  int  TCX_cnx_handler(int     num_fd,
                       fd_set  * read_mask,
                       fd_set  * write_mask,
                       fd_set  * exception_mask,
                       int     * num_cnx,
                       int     * cnx_ids );

  HP_DLL_IF
  int  TCX_select_mask(int             maxFd,
                       fd_set          * read_mask,
                       fd_set          * write_mask,
                       fd_set          * exception_mask,
                       struct timeval  ** time);
#else

  HP_DLL_IF 
  int TC_startup(tc_startup_parameter * param);

  HP_DLL_IF 
  int TC_cleanup( void );

  HP_DLL_IF
  int TC_postWaitForMultipleObjects (int      numHdl,
                                     HANDLE * hdlTab,
                                     int      wfmoRet,
                                     int      maxCnx,
                                     int    * numCnx,
                                     int    * cnxIdsTab);
   HP_DLL_IF
   int TC_preWaitForMultipleObjects (int    * numHdl,
                                     int      maxHdl,
                                     HANDLE * hdlTab,
                                     int    * time);
#endif /* _WIN32 */

#ifdef __cplusplus
}
#endif
#endif

#endif
