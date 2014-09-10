/***********************************************************
*
* 
*
* $Source: /7UP/code/tcapEnvironment/TCAP_ansi.h $
* $Revision: 4.6 $
* 
* 
***********************************************************/
/*
  ======================================================================
 |                          TCAP API include file                       |
 | 		                version ANSI                            |
 |                                                                      |
 |                                                                      |
 | HEWLETT PACKARD SS7                                                  |
 | (c) Copyright 1994, Hewlett-Packard Company, all rights reserved     |
 |                                                                      |
  ======================================================================
*/

#ifndef TCAP_ANSI_H
#define TCAP_ANSI_H

#ifndef _WIN32
#       include <time.h>
#       include <sys/types.h>
#endif /* _WIN32 */
#include "TCAP_common.h"

/*----------------------------------------------------------------------
 |                       COMPONENT types                               |   
 ----------------------------------------------------------------------*/

typedef enum {    

               TC_INVOKE_L, 
               TC_INVOKE_NL,
               TC_RESULT_L, 
               TC_RESULT_NL,
               TC_U_ERROR,
               TC_L_CANCEL, 
               TC_U_CANCEL,
               TC_L_REJECT, 
               TC_R_REJECT, 
               TC_U_REJECT

             } tc_component_type;



/*~~~~~~~~~~~~~~~~~~~~~ PARAMETER types and structure ~~~~~~~~~~~~~~~~~~*/
/*
HP reserved comment
@if not $_hp_reserved_t
*/

typedef enum { SET_TYPE, SEQUENCE_TYPE } tc_parm_type;

/*
@endif
 */

/*~~~~~~~~~~~~~~~~ OPERATION / ERROR  types and structure ~~~~~~~~~~~~~~*/

typedef enum { NATIONAL, PRIVATE } tc_type;

typedef struct tc_error_struct
           {
            tc_type         tag;
            unsigned char   code;

           } tc_error;

typedef struct tc_operation_struct
           {
            tc_type         tag;
            unsigned char   op_family;
            unsigned char   op_specifier;

           } tc_operation;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ REJECT types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {
 
              GENERAL, 
              INVOKE,
              RETURN_RESULT,
              RETURN_ERROR,
              TRANSACTION_PORTION

             } tc_pb_identifier;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ REJECT causes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum {

              UNRECOG_COMPONENT, 
              INCORRECT_COMPONENT_PORTION,
              BADLY_STRUCTURED_COMPONENT_PORTION,
              DUPLICATE_INVOKE_ID,
              UNRECOGNIZED_OPERATION_CODE,
              INCORRECT_PARAMETER,
              UNRECOGNIZED_CORRELATION_ID,/* For the "Return Result" and
					     "Return Error" Problem Types,
					     this value corresponds to the
					     "Unassigned Correlation ID"
					     Problem Specifer in TCAP ANSI 96 */
              UNEXPECTED_RETURN_RESULT,
              UNEXPECTED_RETURN_ERROR,
              UNRECOGNIZED_ERROR,
              UNEXPECTED_ERROR,
              UNRECOGNIZED_PACKAGE_TYPE,
              INCORRECT_TRANSACTION_PORTION,
              BADLY_STRUCTURED_TRANSACTION_PORTION,
              UNRECOGNIZED_TRANSACTION_ID,/* This value corresponds to the 
					     "Unassigned Responding Transaction
					     ID" Problem Specifier in
					     TCAP ANSI 96*/
              INCORRECT_COMPONENT_CODING

             } tc_pb_code;

#define UNASSIGNED_CORRELATION_ID UNRECOGNIZED_CORRELATION_ID
#define UNASSIGNED_RESPONDING_TRANSACTION_ID UNRECOGNIZED_TRANSACTION_ID


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ REJECT structure ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct tc_pcode_struct
           {
            tc_pb_identifier    identifier;
            tc_pb_code          code;

           } tc_pcode;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ADDRESS types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum { 
               DEFAULT_LPC,
               DPC,
               DPC_SSN,
               GT,
               GT_SSN,
               GT_DPC,
               GT_DPC_SSN,
               SSN,
               NO_TC_ADDRESS

             } tc_address_type;

/*----------------------------------------------------------------------
 |                    ADDRESS structure                                |
 ----------------------------------------------------------------------*/

typedef struct tc_address_struct {

            tc_address_type    type;             /* ETSI T/S 43-05 */
            int                pc_value;
            unsigned int       ssn;
            tc_global_title    gt;

          } tc_address ;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ P_ABORT causes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum { 

               TC_UNRECOG_PKG_TYPE,
               TC_INCORRECT_TRANS_PORTION,
               TC_BAD_STRUCTURED_TRANS_PORTION,
               TC_UNRECOG_TRANSACTION_ID,/* == Unassigned Responding 
					    TransactionID in TCAP ANSI96 
					    standard */
               TC_PERM_TO_RELEASE_PROBLEM,
               TC_RESOURCE_UNAVAILABLE ,
	       TC_UNRECOG_DLG_PORTION_ID,
	       TC_BADLY_STRUCT_DLG_PORTION,
	       TC_MISSING_DLG_PORTION,
	       TC_INCONSISTENT_DLG_PORTION

             } tc_p_abort_cause;

#define TC_UNASSIGNED_RESPONDING_TRANSACTION_ID TC_UNRECOG_TRANSACTION_ID


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ U_ABORT struture ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
HP reserved comment
@if not $_hp_reserved_t
*/

typedef struct tc_u_abort_struct
           {
            int              length;
            unsigned char    datas[MAX_U_ABORT_LEN];

           } tc_u_abort;

/*
@endif
 */

/*----------------------------------------------------------------------
 |                     PRIMITIVE types                                 |
 ----------------------------------------------------------------------*/

typedef enum {

              TC_UNI,
              TC_QUERY_W_PERM,TC_QUERY_WO_PERM,
              TC_CONV_W_PERM,TC_CONV_WO_PERM,
              TC_RESPONSE,
              TC_U_ABORT, TC_P_ABORT,
              TC_NOTICE,
              MGT, SCCP_USER_STATUS, SCCP_PC_STATUS, 
              SCCP_N_COORD, SCCP_N_COORD_RES,
              NO_PRIMITIVE,
              SWITCH_STARTED, SWITCH_DONE

             } tc_primitive_type;

/* TCAP-ANSI96 standard (Dialogue Portion) */

typedef enum {INT_TYPE, OID_TYPE} tc_tag_type; 

typedef struct tc_tag_data_struct {
  tc_tag_type tag;
  int length;
  char data [MAX_FIELD];
} tc_tag_data;


typedef struct tc_data_struct {
  int length;
  char data [MAX_FIELD];
} tc_data;

typedef struct tc_dialog_portion_struct{
    /* indicates that dialogue information are present in the primitive   */
  TC_BOOL dlg_info_present;

    /* identifier of the application context ( set of A.S.E ) proposed    */
    /* by the dialogue initiator or by the dialogue responder.            */
    /* length = 0 means absent.                                           */
  tc_tag_data application_context_name;
  
    /* information which can be exchanged between TC_users independently  */
    /* from the remote operation service (length = 0 means absent).       */
    /* user_information contents is completely transparent to HP SS7      */
    /* TCAP, but should be formatted according to the paragraph 4.8 	  */
    /* of the chapter T1.114.3 of the ANSI T1.114-1996 recommendation     */
  tc_data user_information;

  tc_tag_data security_information;
  tc_data confidentiality_information;
  
    /* indicates wether a dialogue is aborted because the received appli- */
    /* cation context name is not supported and no alternative can be     */
    /* proposed or because of any other user problem.                     */
} tc_dialog_portion;

/* Macros to access dialog_portion parameters */

#define TC_P_DLG_INFO_PRESENT(aStruct) \
        ((aStruct)->dialog_portion.dlg_info_present)
#define TC_P_DLG_PORTION_APP_CONTEXT(aStruct) \
        ((aStruct)->dialog_portion.application_context_name)
#define TC_P_DLG_PORTION_USER_INFO(aStruct) \
        ((aStruct)->dialog_portion.user_information)
#define TC_P_DLG_PORTION_SECURITY_INFO(aStruct) \
         ((aStruct)->dialog_portion.security_information)
#define TC_P_DLG_PORTION_CONFIDENTIALITY_INFO(aStruct) \
         ((aStruct)->dialog_portion.confidentiality_information)

#endif /* TCAP_ANSI_H */
