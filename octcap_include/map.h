/**
 * @file map.h
 * @author GDIC MAP Development team
 *
 * @brief  HP OpenCall MAP API
 * 
 @verbatim

 %name: tcap.h %

 Copyright (c) 2003 Hewlett-Packard Company, All Rights Reserved.
 RESTRICTED RIGHTS LEGEND Use, duplication, or disclosure by the U.S.
 Government is subject to restrictions as set forth in sub-paragraph
 (c)(1)(ii) of the Rights in Technical Data and Computer Software
 clause in DFARS 252.227-7013.

 Hewlett-Packard Company
 3000 Hanover Street
 Palo Alto, CA 94304 U.S.A.
 Rights for non-DOD U.S. Government Departments and Agencies are as
 set forth in FAR 52.227-19(c)(1,2).

 @endverbatim
 */

/** 
 * @mainpage Overview of OpenCall MAP API
 * @section  MAP Introduction 
 *
 * OpenCall MAP API implements a framework for exchange  MAP USSD messages.
 * Following versions of GSM MAP standards are supported
 *
 * - ETSI 300 599: December 1995 (GSM 09.02 version 4.12.0) - MAP2
 *
 * OpenCall MAP API contains MAP provider layer, MAP encoders and decoders 
 * and an API to use the services provided by MAP layer.
 *
 * The MAP API has to be used along with HP OC SS7 TCAP version 3.1
 *
 * OpenCall MAP API package also consists of sample applications
 * that demonstrate the use of MAP API.
 *
 * @section map_overview_entities Entities
 *
 * Throughout the OCSS7 MAP API manual, there are multiple references to the
 * following software entities:
 *
 * - @c Application (App)
 * - @c Library (Lib)
 * - @c Dialog (Dlg)
 * - @c Primitive (Prim)
 * - @c Component (Comp)
 *
 * An  @c  Application  generally  refers  to MAP  user-code,  that  is,  code
 * developed on top of the MAP API. It refers to all user-developed aspects.
 *
 * The @c Library is the counterpart of  the @c Application ; it refers to code
 * within the MAP API.
 *
 * A @c Dialog is the @c Application view of a TCAP transaction (for a TR-user)
 * or TCAP Dialog (for a TC-user), as defined by the SS7 protocol.  A @c Dialog
 * is fully defined by a ::map_dialog_handle_t 
 *
 * During a @c Dialog , MAP  users exchange @e messages.  Each MAP message is
 * made  up   of  a  @e   primitive, plus  a @c Component.  The type of 
 * @c  Components  that can be  embedded in  a primitive  depends on  the primitive
 * type. 
 * @see map_primitive
 *
 *
 *
 * @section map_overview_dist Distribution
 *
 * @subsection map_overview_dist_topo Topologies
 *
 * OCSS7 MAP is a typical OCSS7 TCAP application. Please refer to the
 * TCAP application guide for deails on application topologies.
 *
 *
 * @section map_using_map_library Using OCSS7 MAP Library
 *
 *
 * @subsection map_overview_lib_init Library Initialization
 * A MAP user application will call MAP_init()function with appropriate
 * function parameters to initialize the library.  This should be the
 * first call to the library. Without calling this function any other
 * MAP API calls will not succeed.
 *
 * @subsection map_overview_cnx_mgt Connection Management
 * After Library initialization, MAP user application should
 * connect to the TCAP provider. This call should precede any
 * send/recv calls to the MAP library.  MAP user will directly
 * call TCAP related call @c TCX_open() API function to establish
 * a TCAP connection.  MAP user may disconnect the connection
 * to the stack before shutting down. The TCAP API function 
 * TCX_close() should be used for this purpose.  Whenever user
 * disconnects from the stack, it is mandatory that user shall
 * call the MAP API  MAP_flush() to cleanup all the dialog
 * specific data related to that connection. Failure to do may
 * result in unpredictable behavior.
 *
 * @subsection map_overview_send_rcv Sending and Receiving
 * Send and receive follows the typical HP Opencall select based 
 * I/O scheduling Following code demonstrates a typical server
 * side code:
 *
 * @code
 *      TCX_select_mask();
 *      // No user code here
 *      select(); 
 *      // No user code here
 *      TCX_cnx_handler();
 *      if(cnx_id active) {
 *          MAP_recv() ; // get the message 
 *          // process the message
 *          // application specific code goes here.
 *          MAP_send() ; // send the response
 *      }
 * @endcode
 *
 * @subsection map_overview_dlg_mgt Dialog management
 * Each MAP_OPEN_REQ will open a new dialog for MAP user. This will directly
 * map to a new TCAP dialog.  As in TCAP we will have user and a provider
 * dialog id's associated with each dialog. 
 *
 * MAP library uses dialog handle to uniquely identify a dialog. The library also
 * provides a placeholeder (in map_primitive) for user to keep dialog specific
 * data in a field called user_opaque.
 * 
 * - <B>Provider dialog handle:</B>
 *   .
 *   Allocated and used by the MAP library. This will be allocated at the beginning
 *   of every new dialog (OPEN_REQ or OPEN_IND). A successful call to MAP_send()
 *   will update the MAP primitive structure to return the dialog handle which
 *   should be used in subsequent call to the library.

 * - <B>User dialog handle(user opaque):</B>
 *   .
 *   Allocated and used by API user. MAP library will not look into this value.
 *   This could typically be a pointer to a dialog specific user data structure.
 *   Once passed to the library at the beginning of new dialog or during the first
 *   response to an incoming dialog, this value will be passed to the application
 *   along with any incoming primitive. The user dialog handle enables the user
 *   application to have a very quick way of locating dialog specific data structure.
 *
 *
 * @subsection map_overview_error_handling Error Handling
 *
 * Upon any unsuccessful opration, MAP API functions will return MAP_FAILURE or any other 
 * specific error as described in each API function's documention.
 *
 * @c map_errno variable will be set to indicate the exact cause of the error.
 *
 * There are following special values for map_errno as defined below.
 *
 * @c MAP_TCAP_INTERNAL
 *     The error was in underlying TCAP layer, check 
 *     tcap_errno for further details.
 *  
 *  MAP_error_str() can be called to get a string describing the error.
 *
 * @subsection map_overview_congestion Congestion handling.
 * 
 *  When there is TCAP congestion on underlying TCAP connection, TCAP API
 *  calls would fail with errno TCX_SEND_FULL or TCE_API_BUSY.
 *  In this case, MAP API will fail with map_errno set to MAP_TCAP_INTERNAL.
 *  Application is supposed follow the TCAP congetion control mechanism
 *  by slowing down sending till select() call indicates the connection 
 *  can be written on. Refer to TCAP developers Guide for more details.
 *
 * @subsection map_overview_tcap_prim_pass TCAP Primitive pass through.
 *
 *  Since MAP API does not handle all the TCAP primitive there is pass through 
 *  mode for receiving TCAP primitives that are not handled by 
 *  MAP layer, such as TCAP HA and statistics primitives. 
 *  When ever such primitive is recieved by the MAP layer the primitive is forwarded
 *  to MAP user with map_primitive_type set to MAP_TCAP_PRIMITIVE. 
 *  User can access the complete TCAP primitve by using the macro
 *  MAP_P_TCAP_PRIM(prim) where prim is a pointer to map_primitive_t.
 */



#ifndef _MAP_H
#define _MAP_H

#include <sys/select.h>

/* system dependencies */
#ifndef MAP_API
# ifdef _WIN32
#  define MAP_API        __declspec(dllimport) /**< @internal */
# else /* !_WIN32 */
#  define MAP_API        extern          /**< @internal */
# endif/* !_WIN32 */
#endif /* !MAP_API */


/* MAP/TCAP dependencies */
#include <TCAP_ext.h>

/** 
 * @defgroup map_types MAP constants and types.
 * @{
 */

/**
 * @def MAP_MAX_DATA_LENGTH
 *
 * @brief Maximum data length.
 *
 * Maximum data length that can be accomodated in map_octet_string_t.
 *
 * @see map_octet_string_t
 * @see MAP
 */
#define MAP_MAX_DATA_LENGTH	160

/**
 * @def MAP_MAX_ADDR_LENGTH
 *
 * @brief Maximum address length.
 *
 * Maximum address length that can be accomodated in map_address_string_t.
 *
 * @see map_address_string_t
 */
#define MAP_MAX_ADDR_LENGTH	20

/**
 * @def ACN_VERSION2_STR
 *
 * @brief the ACN version 2 string.
 */
#define ACN_VERSION2_STR	"networkUnstructuredSsContext-v2"

/**
 * @def ACN_NOT_SUPPORTED
 *
 * @brief the string used when the library does not support an ACN.
 */
#define ACN_NOT_SUPPORTED 	"unknownApplicationContext"

/**
 * @enum map_boolean
 * @brief Boolean constants.
 */
typedef enum map_boolean {
    MAP_FALSE, /**< Boolean false */
    MAP_TRUE   /**< Boolean true  */
} map_boolean_t ;
/**
 * @typedef map_boolean_t
 * @see map_boolean
 */

/** 
 * @enum map_yes_no
 * @brief Truth constants.
 */
typedef enum map_yes_no {
    MAP_NO, /**< MAP_NO = 0 */
    MAP_YES /**< MAP_YES = 1 */
} map_yes_no ;
/**
 * @typedef map_yes_no
 * @see map_yes_no
 */

/**
 * @def MAP_P_TYPE
 * @brief access the primitive type member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_TYPE(prim)           ((prim)->ptype)

/**
 * @def MAP_P_D_ADDR
 * @brief access the destination address member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_D_ADDR(prim)         ((prim)->_prim.open.daddr)

/**
 * @def MAP_P_O_ADDR
 * @brief access the originating address member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_O_ADDR(prim)         ((prim)->_prim.open.oaddr)

/**
 * @def MAP_P_ORIG_REF
 * @brief access the originating reference member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_ORIG_REF(prim)    ((prim)->_prim.open.oref)

/**
 * @def MAP_P_DEST_REF
 * @brief access the destination reference member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_DEST_REF(prim)    ((prim)->_prim.open.dref)

/**
 * @def MAP_P_USER_OPAQUE
 * @brief access the user opaque member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_USER_OPAQUE(prim)    ((prim)->user_opaque)

/**
 * @def MAP_P_DIALOG_HANDLE
 * @brief access the dialog handle member of map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_DIALOG_HANDLE(prim)  ((prim)->dlg_handle)

/**
 * @def MAP_P_DELIMITER
 * @brief access the delimiter of member map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_DELIMITER(prim)      ((prim)->delimiter)

/**
 * @def MAP_OPEN
 * @brief access the map_open_t member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_OPEN(prim)             ((prim)->_prim.open)

/**
 * @def MAP_CLOSE
 * @brief access the map_close_t member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_CLOSE(prim)            ((prim)->_prim.close)

/**
 * @def MAP_UABORT
 * @brief access the map_u_abort_t member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_UABORT(prim)           ((prim)->_prim.uabort)

/**
 * @def MAP_PABORT
 * @brief access the map_p_abort_t member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_PABORT(prim)           ((prim)->_prim.pabort)

/**
 * @def MAP_NOTICE
 * @brief access the map_notice_t member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_NOTICE(prim)           ((prim)->_prim.notice)

/**
 * @def MAP_P_TCAP_PRIM
 * @brief access the map_tcap_prim member of the map_primitive_t structure.
 * @see map_primitive
 */
#define   MAP_P_TCAP_PRIM(prim)        ((prim)->_prim.tcap_prim)


/**
 * @def MAP_M_USSD_REQ_DCS
 * @brief access the DCS field of the map_ussd_arg_t structure.
 * @see map_ussd_arg_t
 * @see map_message_t
 */
#define   MAP_M_USSD_REQ_DCS(msg)       ((msg)->_msg.ussd_arg.ussd_data_coding_scheme)

/**
 * @def MAP_M_USSD_REQ_STRING
 * @brief access the ussd string field of the map_ussd_arg_t structure.
 * @see map_ussd_arg_t
 * @see map_message_t
 */
#define   MAP_M_USSD_REQ_STRING(msg)    ((msg)->_msg.ussd_arg.ussd_string)

/**
 * @def MAP_M_USSD_REQ_MSISDN
 * @brief access the MSISDN field of the map_ussd_arg_t structure.
 * @see map_ussd_arg_t
 * @see map_message_t
 */
#define   MAP_M_USSD_REQ_MSISDN(msg)    ((msg)->_msg.ussd_arg.msisdn)

/**
 * @def MAP_M_USSD_REQ_ALERTING_PATTERN
 * @brief access the "alerting pattern" field of the map_ussd_arg_t structure.
 * @see map_ussd_arg_t
 * @see map_message_t
 */
#define   MAP_M_USSD_REQ_ALERTING_PATTERN(msg)    ((msg)->_msg.ussd_arg.alerting_pattern)

/**
 * @def MAP_M_USSD_RES_DCS
 * @brief access the DCS field of the map_ussd_res_t structure.
 * @see map_ussd_res_t
 * @see map_message_t
 */
#define   MAP_M_USSD_RES_DCS(msg)       ((msg)->_msg.ussd_res.ussd_data_coding_scheme)

/**
 * @def MAP_M_USSD_RES_STRING
 * @brief access the ussd string field of the map_ussd_res_t structure.
 * @see map_ussd_res_t
 * @see map_message_t
 */
#define   MAP_M_USSD_RES_STRING(msg)    ((msg)->_msg.ussd_res.ussd_string)

/**
 * @def MAP_M_USSD_RES_RESULT
 * @brief access the result field of the map_ussd_res_t structure.
 * @see map_ussd_res_t
 * @see map_message_t
 */
#define   MAP_M_USSD_RES_RESULT(msg)    ((msg)->_msg.ussd_res.result)

/**
 * @def MAP_M_USSD_RES_UERROR
 * @brief access the user error field of the map_ussd_res_t structure.
 * @see map_ussd_res_t
 * @see map_message_t
 */
#define   MAP_M_USSD_RES_UERROR(msg)    ((msg)->_msg.ussd_res.user_error)

/**
 * @def MAP_M_USSD_RES_PERROR
 * @brief access the provider error field of the map_ussd_res_t structure.
 * @see map_ussd_res_t
 * @see map_message_t
 */
#define   MAP_M_USSD_RES_PERROR(msg)    ((msg)->_msg.ussd_res.provider_error)

/**
 * MAP errno
 * @see map_error
 */
extern int map_errno;

/**
 * @enum map_result
 * @brief The result of an operation.
 *
 * The MAP library uses these constants to describe the result of any operation.
 */
typedef enum map_result {
    MAP_FAILURE = -1,     /**< Failure */
    MAP_SUCCESS,          /**< Success */
    MAP_NO_MESSAGES,      /**< Used by ::MAP_recv, No message has been received */
    MAP_NO_MORE_MESSAGES, /**< Used by ::MAP_recv, A message has been received, but there are no more messages */
    MAP_MORE_MESSAGES     /**< Used by ::MAP_recv, A message has been received, and there are more messages */
}map_result;
/**
 * @typedef map_result
 * @see map_result
 */

/**
 * @struct map_octet_string
 * @brief Encapsulates octet data of arbitrary length.
 */
typedef struct map_octet_string {

    /**
     * @a data_length
     *
     * The size of the data in bytes.
     *
     * @note a value of 0, implies that there is no data.
     */
    unsigned short data_length; /**< data_length, the size of the data in bytes. */

    /**
     * @a data_value
     *
     * An array to hold the data(max size = MAP_MAX_DATA_LENGTH).
     *
     * @see MAP_MAX_DATA_LENGTH
     */
    unsigned char  data_value[MAP_MAX_DATA_LENGTH];
}map_octet_string_t;
/**
 * @typedef map_octet_string_t
 * @see map_octet_string
 */

/**
 * @struct map_octet
 * @brief Used to store one octet of data.
 * @see map_octet_string
 */
typedef struct map_octet {

    /**
     * @a is_pres
     *
     * Indicates the presence of data. ::MAP_FALSE indicates no data.
     *
     * @see map_boolean
     */
    map_boolean_t  is_pres;

    /**
     * @a value
     *
     * The data.
     */
    unsigned char  value;
}map_octet_t;
/**
 * @typedef map_octet_t
 * @see map_octet
 */

/**
 * @struct map_address_string
 * @brief Encapsulates a MAP address string.
 */
typedef struct map_address_string {
    /**
     * @a length
     *
     * The size of the data in bytes.
     *
     * @note a value of 0, implies that there is no data.
     */
    unsigned short length;

    /**
     * @a value
     *
     * An array to hold the data(max size = MAP_MAX_DATA_LENGTH).
     *
     * @see MAP_MAX_DATA_LENGTH
     */
    unsigned char  value[MAP_MAX_ADDR_LENGTH];
}map_address_string_t;

/**
 * @def map_address_t
 * @brief MAP address, same as TCAP address.
 */
#define map_address_t tc_address /* From TCAP API */

/**
 * @typedef map_invoke_id
 */
typedef int map_invoke_id;

/**
 * @typedef map_linked_id
 */
typedef int map_linked_id;

/**
 * @enum map_version
 *
 * @brief MAP version to be used in a dialogue.
 */
typedef enum  map_version {
    MAP_PHASE1 = 0x01,     /**< MAP_PHASE1 */
    MAP_PHASE2 = 0x02,     /**< MAP_PHASE2 */
    MAP_PHASE2plus = 0x04, /**< MAP_PHASE2plus */
    MAP_PHASE3 = 0x08      /**< MAP_PHASE3 */
} map_version_t ;
/**
 * @typedef map_version_t
 * @see map_version
 */

/**
 * @enum map_error
 *
 * @brief MAP error values.
 *
 * Lists all possible errors which can be set in ::map_errno by the
 * MAP library.
 * The  application can  obtain a  C-like printable  string from  these error
 * codes using ::MAP_error_str .
 *
 * @see MAP_error_str
 * @see map_errno
 */
typedef enum map_error {
    MAP_ERROR_BEGIN,            /**< Invalid and unused */
    MAP_MEMORY_ERROR,           /**< Memory error, mostly with malloc */
    MAP_HASH_ERROR,             /**< Error in the internal hash table */
    MAP_INVALID_CNX_ID,         /**< Invalid connection-id */
    MAP_INT_ERR,                /**< Internal error in the MAP library*/
    MAP_NULL_COMPONENT,         /**< NULL component */
    MAP_NOT_INITIALIZED,        /**< MAP library not initialized */
    MAP_INVALID_ARGS,           /**< Invalid arguments passed */
    MAP_INVALID_DLG,            /**< Invalid MAP dialog */
    MAP_INVALID_DLG_STATE,      /**< Invalid dialog state */
    MAP_INVALID_PRIM,           /**< Invalid MAP primitive */
    MAP_INVALID_MSG,            /**< Invalid MAP message */
    MAP_VERSION_MISMATCH,       /**< MAP version mismatch */
    MAP_OSS_ENCODE_ERR,         /**< Error in OSS encode api */
    MAP_OSS_DECODE_ERR,         /**< Error in OSS decode api */
    MAP_SERVICE_NOT_SUPPORTED,  /**< MAP service not supported */
    MAP_DUPLICATE_INVOKE_ID,    /**< Duplicate invoke id */
    MAP_TCAP_INTERNAL,          /**< TCAP error, look at tc_errno */
    MAP_LICENSE_ERR,            /**< Invalid MAP license */
    MAP_ERROR_END               /**< Invalid and unused */
} map_error;
/**
 * @typedef map_error
 * @see map_error
 */

/**
 * @typedef map_ussd_data_coding
 * @brief USSD Data Coding Scheme parameter
 * @see map_octet_t
 */
typedef map_octet_t map_ussd_data_coding;

/**
 * @struct map_ussd_arg
 * @brief Encapsulates a MAP USSD Request.
 * @see map_message_t
 */
typedef struct  map_ussd_arg {
    /**
     * @a ussd_data_coding_scheme
     *
     * USSD data coding scheme.
     */
    map_ussd_data_coding  ussd_data_coding_scheme;

    /**
     * @a ussd_string
     *
     * Contains information of alphabet and 
     * language used for unstructured information
     */
    map_octet_string_t 		ussd_string;

    /**
     * @a alerting_pattern
     *
     * The alerting pattern
     */
    map_octet_t                 alerting_pattern ;

    /**
     * @a msisdn
     *
     * Contains string of unstructured information 
     * in an USSD  operation 
     */
    map_address_string_t  msisdn;
}map_ussd_arg_t;
/**
 * @typedef map_ussd_arg_t
 * @see map_ussd_arg
 */

/**
 * @enum map_user_error
 * @brief Describes the user errors that can be used in a USSD response.
 * @see map_ussd_res
 */
typedef enum map_user_error {
    MAP_USER_ERROR_NOT_PRESENT,           /**< Not present */
    MAP_USER_ERROR_SYSTEM_FAILURE,        /**< System failure */
    MAP_USER_ERROR_DATA_MISSING,          /**< Data missing */
    MAP_USER_ERROR_UNEXPECTED_DATA_VALUE, /**< Unexpected data value */
    MAP_USER_ERROR_CALL_BARRED,           /**< Call barred */
    MAP_USER_ERROR_UNKNOWN_ALPHABET,      /**< Unknown alphabet */
    MAP_USER_ERROR_RESOURCE_LIMITATION,   /**< Resource limitation */
    MAP_USER_ERROR_INITIATING_RELEASE     /**< Initiating release */
}map_user_error;
/**
 * @typedef map_user_error
 * @see map_user_error
 */

/**
 * @enum map_prov_error
 * @brief Describes the provider errors that can be used in a USSD response.
 * @see map_ussd_res
 */
typedef enum map_prov_error {
    MAP_PROV_ERROR_NOT_PRESENT,                 /**< Not present */
    MAP_PROV_ERROR_DUP_INVOKE_ID,               /**< Duplicate Invode id */
    MAP_PROV_ERROR_NOT_SUPPORTED_SERVICE,       /**< Service unsupported */
    MAP_PROV_ERROR_MISTYPED_PARAM,              /**< Mistyped parameter */
    MAP_PROV_ERROR_RESOURCE_LIMITATION,         /**< Resource limitation */
    MAP_PROV_ERROR_INITIATING_RELEASE,          /**< Initiating release */
    MAP_PROV_ERROR_UNEXPECTED_RESP,             /**< Unexpected response */
    MAP_PROV_ERROR_SERVICE_COMPLETION_FAIL,     /**< Service completion failure */
    MAP_PROV_ERROR_NO_RESP_FROM_PEER,           /**< No response from peer */
    MAP_PROV_ERROR_INVALID_RESP_RCVD            /**< Invalid response reveived */
} map_prov_error;
/**
 * @typedef map_prov_error
 * @see map_prov_error
 */

/**
 * @struct map_ussd_res
 * @brief Encapsulates a MAP USSD Response.
 * @see map_message_t
 */
typedef struct  map_ussd_res {
    /**
     * @a ussd_data_coding_scheme
     *
     * USSD data coding scheme.
     */
    map_ussd_data_coding ussd_data_coding_scheme;

    /**
     * @a ussd_string
     *
     * Contains information of alphabet and 
     * language used for unstructured information
     */
    map_octet_string_t ussd_string;

    /**
     * @a result
     *
     * Contains the result of the operation.
     * @see map_result
     */
    map_result result;  

    /**
     * @a user_error
     *
     * The following field will be used only for Unsuccessful response.
     * @see map_user_error
     */
    map_user_error user_error;

    /**
     * @a provider_error
     *
     * The following field will be used only for Unsuccessful response.
     * @see map_prov_error
     */
    map_prov_error provider_error;
}map_ussd_res_t;

/**
 * @typedef map_cnxid_t
 * @brief MAP connection-id, same as TCAP connection-id(tcx_cnxid).
 */
typedef int map_cnxid_t;

/**
 * @enum map_message_type
 * @brief Defines the MAP message types.
 * @see map_message_t
 */
typedef enum map_message_type {
    MAP_MESSAGE_TYPE_BEGIN,                 /**< Invalid and unused. */
    MAP_PROCESS_UNSTRUCTURED_SS_REQUEST,    /**< USSD Request */
    MAP_PROCESS_UNSTRUCTURED_SS_RESPONSE,   /**< USSD Response */
    MAP_PROCESS_UNSTRUCTURED_SS_INDICATION, /**< USSD Indication */
    MAP_PROCESS_UNSTRUCTURED_SS_CONFIRM,    /**< USSD Confirmation */
    MAP_MESSAGE_TYPE_END,                   /**< Invalid and unused. */
}map_message_type_t;
/**
 * @typedef map_message_type_t
 * @see map_message_type
 */

/**
 * @struct map_message
 * @brief MAP message structure.
 *
 * The MAP library provides the structure map_message to build a MAP message.
 * The MAP library will encode this structure and populate it into a TCAP
 * component.
 *
 * @see map_primitive
 */
typedef struct map_message {
    /**
     * @a next_msg
     *
     * Points to the next MAP message. This field is used internally
     * by the MAP library, and should not be used by the application.
     */
    struct map_message* next_msg;

    /**
     * @a mtype
     *
     * The MAP message type.
     * 
     * @see map_message_type
     */
    map_message_type_t  mtype;

    /**
     * @a invoke_id
     *
     * The TCAP invoke id.
     *
     * @see map_invoke_id
     */
    map_invoke_id       invoke_id;

    /**
     * @a linked_id
     *
     * The linked id.
     *
     * @see map_linked_id
     */
    map_linked_id       linked_id;

    union msg {
        map_ussd_arg_t  ussd_arg; /**< USSD request.  */
        map_ussd_res_t  ussd_res; /**< USSD response. */
    }_msg;                        /**< The message component. */

    /**
     * @a version
     *
     * The MAP version. The library currently supports MAP_PHASE2.
     *
     * @see map_version_t
     */
    map_version_t   version;
} map_message_t;
/**
 * @typedef map_message_t
 * @see map_message
 */

/**
 * @enum map_primitive_type
 *
 * @brief MAP primitive type constants.
 *
 * @see map_primitive
 */
typedef enum map_primitive_type {
    MAP_PRIM_TYPE_BEGIN, /**< Invalid and unused */
    MAP_UNKNOWN_PRIM,    /**< Unknown primitive */
    MAP_OPEN_REQ,        /**< Open request */
    MAP_OPEN_IND,        /**< Open indication */
    MAP_OPEN_RES,        /**< Open response */
    MAP_OPEN_CNF,        /**< Open confirmation */
    MAP_CLOSE_REQ,       /**< Close request */
    MAP_CLOSE_IND,       /**< Close indication */
    MAP_USER_PRIM,       /**< User primitive */
    MAP_U_ABORT_REQ,     /**< User Abort request */
    MAP_U_ABORT_IND,     /**< User Abort indication */
    MAP_P_ABORT_IND,     /**< Provider Abort indication */
    MAP_NOTICE_IND,      /**< Notice indication */
    MAP_TCAP_PRIM,       /**< TCAP management primitive */
    MAP_PRIM_TYPE_END    /**< Invalid and unused. */
} map_primitive_type_t;
/**
 * @typedef map_primitive_type_t
 * @see map_primitive_type
 */

/**
 * @typedef map_specific_info_t
 *
 * @brief Specific Information parameter. Currently unsupported in the library.
 */
typedef int map_specific_info_t;


/**
 * @enum map_refuse_reason
 * @brief Values for the refuse reason parameter in the map_open primitive.
 * @see map_open_t
 */
typedef enum map_refuse_reason
{
    MAP_APP_CONTEXT_NOT_SUPPORTED,              /**< Application context not supported */
    MAP_INVALID_DEST_REF,                       /**< Invalid destination reference */
    MAP_INVALID_ORIG_REF,                       /**< Invalid origination reference */
    MAP_NO_REASON_GIVEN,                        /**< No reason */
    MAP_REMOTE_NODE_UNREACHABLE,                /**< Not supported */
    MAP_POTENTIAL_VERSION_INCOMPATIBILITY,      /**< Potential version incompatibility */
    MAP_SECURE_TRANSPORT_NOT_POSSIBLE,          /**< Not supported */
    MAP_TRANSPORT_PROTECTION_INADEQUATE         /**< Not supported */
}map_refuse_reason_t;
/**
 * @typedef map_refuse_reason_t
 * @see map_refuse_reason
 */

/**
 * @enum map_provider_reason
 * @brief Values for the provider abort reason parameter in the map_open primitive.
 * @see map_open_t
 */
typedef enum map_provider_reason {
    MAP_PROVIDER_MALFUNCTION,   /**< Provider malfunction */
    MAP_DLG_RELEASED,           /**< Dialog released */
    MAP_RESOURCE_LIMIT,         /**< Resource limitation */
    MAP_MAINTENANCE,            /**< Maintenance */
    MAP_VERSION_INCOMPAT,       /**< Version incompatibility */
    MAP_ABNORMAL_DIALOG,        /**< Abnormal dialog */
    MAP_UNKNOW_REASON           /**< Unknown reason */
}map_provider_reason_t;
/**
 * @typedef map_provider_reason_t
 * @see map_provider_reason
 */

/**
 * @struct map_open_t
 *
 * @brief This structure describes the MAP_OPEN primitive.
 *
 * @see map_primitive
 */
typedef struct {
    map_octet_string_t    	aname;   /**< Application Context Name */
    map_address_t		daddr;   /**< Destination Address */
    map_address_string_t 	dref;    /**< Destination Reference */
    map_address_t		oaddr;   /**< Originating Address */
    map_address_string_t   	oref;    /**< Originating Reference */
    map_octet_string_t   	sinfo;   /**< Specific Information */
    map_address_t         	raddr;   /**< Responding Address */
    int               	        result;  /**< MAP_SUCCESS or MAP_FAILURE */
    map_refuse_reason_t    	reasons; /**< Refuse Reason */
    map_provider_reason_t  	error;   /**< Provider Error */
} map_open_t;

/**
 * @enum map_release_method
 * @brief Values for the release method parameter.
 * @see map_close_t
 */
typedef enum map_release_method {
    MAP_NORMAL_RELEASE,  /**< Normal release */
    MAP_PRE_ARRANGED_END /**< Prearranged release */
} map_release_method_t;
/**
 * @typedef map_release_method_t
 * @see map_release_method
 */

/**
 * @struct map_close_t
 *
 * @brief This structure describes the MAP_CLOSE primitive.
 *
 * @see map_primitive
 */
typedef struct {
    /**
     * @a method
     *
     * The release method.
     *
     * @see map_release_method
     */
    map_release_method_t      method;

    /**
     * @a sinfo
     *
     * Specific Information. Currently not supported.
     */
    map_specific_info_t       sinfo; 
} map_close_t;

/**
 * @enum map_user_reason
 *
 * @brief Values for the user reason parameter of the User Abort primitive.
 *
 * @see map_u_abort
 */
typedef enum map_user_reason {
    MAP_RESOURCE_CONGESTION,  /**< Resource congestion */
    MAP_RESOURCE_UNAVAIL,     /**< Resource unavailable */
    MAP_APP_PROCEDURE_CANCEL, /**< Application procedure cancellation */
    MAP_PROCEDURE_ERROR       /**< Procedure error */
} map_user_reason_t;
/**
 * @typedef map_user_reason_t
 * @see map_user_reason
 */

/**
 * @enum map_user_reason
 *
 * @brief Values for the diagnostic parameter of the User Abort primitive.
 *
 * @see map_u_abort
 */
typedef enum map_diag_info {
    MAP_SHORT_TERM_PROB,        /**< Short term problem */
    MAP_LONG_TERM_PROB,         /**< Long term problem */
    MAP_HANDOVER_CANCEL,        /**< Handover cancellation */
    MAP_RADIO_RELEASE,          /**< Radio release */
    MAP_NETWORK_PATH_RELEASE,   /**< Network path release */
    MAP_CALL_RELEASE,           /**< Call release */
    MAP_ASSOC_PROC_FAILURE,     /**< Associated process failure */
    MAP_TANDEM_DIALOG_RELEASE,  /**< Tandem dialog release */
    MAP_REMOTE_OP_FAIL,         /**< Remote operation failure */
    MAP_UNKNOWN_DIAG_INFO       /**< Unknown dialog information */
} map_diag_info_t;
/**
 * @typedef map_diag_info_t
 * @see map_diag_info
 */

/**
 * @struct map_u_abort
 *
 * @brief Structure that describes the MAP User Abort primitive.
 *
 * @see map_primitive
 */
typedef struct map_u_abort {
    /**
     * @a ureason
     * 
     * User reason parameter.
     *
     * @see map_user_reason_t
     */
    map_user_reason_t     ureason;

    /**
     * @a dinfo
     *
     * Diagnostic Information parameter
     *
     * @see map_diag_info_t
     */
    map_diag_info_t       dinfo;

    /**
     * @a sinfo
     *
     * Specific Information. Currently not supported.
     */
    map_specific_info_t   sinfo;
} map_u_abort_t;
/**
 * @typedef map_u_abort_t
 * @see map_u_abort
 */

/**
 * @enum map_source
 *
 * @brief Values for the Source parameter of the Provider Abort primitive.
 *
 * @see map_p_abort
 */
typedef enum map_source {
    MAP_PROVIDER,        /**< Provider */
    MAP_TC_PROVIDER,     /**< TCAP */
    MAP_NETWORK_SERVICE, /**< Network service */
    MAP_UNKNOWN_SOURCE   /**< Unknown source */
} map_source_t;
/**
 * @typedef map_source_t
 * @see map_source
 */

/**
 * @struct map_p_abort
 *
 * @brief Structure that describes the MAP Provider Abort primitive.
 *
 * @see map_primitive
 */
typedef struct map_p_abort {
    /**
     * @a preason
     *
     * The provider reason.
     *
     * @see map_provider_reason_t
     */
    map_provider_reason_t   preason;

    /**
     * @a psource
     *
     * The abort source.
     *
     * @see map_source_t
     */
    map_source_t            psource;
} map_p_abort_t;

/**
 * @enum map_problem_diag
 * @brief Problem diagnostic parameter of the MAP Notice primitive.
 * @see map_notice_t
 */
typedef enum map_problem_diag {
    MAP_ABNORMAL_PEER_EVENT_DETECT, /**< Abnormal event detected by the peer */
    MAP_RESPONSE_PEER_REJECT,       /**< Response rejected by the peer */
    MAP_ABNORMAL_PEER_EVENT_RECV,   /**< Abnormal event received from the peer */
    MAP_CANT_DELIVER_PEER,          /**< Message cannot be delivered to the peer */
} map_problem_diag_t;
/**
 * @typedef map_problem_diag_t
 * @see map_problem_diag
 */

/**
 * @struct map_notice_t
 *
 * @brief Structure that describes the MAP Notice primitive.
 *
 * @see map_primitive
 */
typedef struct {
    /**
     * @a diag
     *
     * Problem diagnostic parameter.
     *
     * @see map_problem_diag_t
     */
    map_problem_diag_t    diag;
} map_notice_t;

/**
 * @def MAP_DIALOG_NEW
 *
 * The value of the dialog handle should be set to this value
 * to specify the creation of a new dialog to the MAP library.
 *
 * @see map_primitive
 */
#define MAP_DIALOG_NEW 0

/**
 * @typedef map_dialog_handle_t
 * @see map_primitive
 */
typedef long map_dialog_handle_t;

/**
 * @typedef map_user_opaque_t
 * @see map_primitive
 */
typedef long map_user_opaque_t;

/**
 * @def map_open
 * @brief access the map open primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_open       _prim.open

/**
 * @def map_close
 * @brief access the map close primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_close      _prim.close

/**
 * @def map_uabort
 * @brief access the map user abort primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_uabort     _prim.uabort

/**
 * @def map_pabort
 * @brief access the map provider abort primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_pabort     _prim.pabort

/**
 * @def map_notice
 * @brief access the map notice primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_notice     _prim.notice

/**
 * @def map_tcap_prim
 * @brief access the tcap primitive of the map_primitive_t structure.
 * @see map_primitive
 */
#define map_tcap_prim  _prim.tcap_prim

/**
 * @struct map_primitive
 *
 * @brief The MAP primitive structure.
 *
 * This structure describes the MAP primitive.
 *
 * @see map_message_t
 */
typedef struct map_primitive {
    
    /**
     * @a next
     *
     * Points to the next primitive. This field is used internally
     * by the MAP library, and should not be used by the application.
     */
    struct map_primitive* next;

    /**
     * @a ptype
     *
     * The MAP primitive type.
     *
     * @see map_primitive_type_t
     */
    map_primitive_type_t  ptype;

    /**
     * @a user_opaque
     *
     * The User opaque parameter. This parameter is transparent to the
     * library. Any value set here by the application, will be passed 
     * back to the application.
     *
     * @see map_user_opaque_t
     */
    map_user_opaque_t     user_opaque;

    /**
     * @a dlg_handle
     * 
     * The dialog handle of the primitive.
     * To create a new dialog, set the value of this parameter to ::MAP_DIALOG_NEW
     *
     * @see map_dialog_handle_t
     */
    map_dialog_handle_t   dlg_handle;

    /**
     * @a delimiter
     *
     * If set to 0, the associated components will not be transmitted
     * by the library. If set to 1, all the associated components will be
     * immediately transmitted.
     */
    int                   delimiter;

    /**
     * @a daddr
     *
     * Destination address.
     *
     * @see map_address_t
     */
    map_address_t         daddr;

    /**
     * @a oaddr
     *
     * Origination address.
     *
     * @see map_address_t
     */
    map_address_t         oaddr;

    union prim {
        map_open_t      open;           /**< MAP Open primitive */
        map_close_t     close;          /**< MAP Close primitive */
        map_u_abort_t   uabort;         /**< MAP User Abort primitive */
        map_p_abort_t   pabort;         /**< MAP Provider Abort primitive */
        map_notice_t    notice;         /**< MAP Notice primitive */
        tcx_primitive   tcap_prim;      /**< TCAP management primitive */
    }_prim;                             /**< MAP primitive */

    /**
     * @a version
     *
     * The MAP version. The library currently supports MAP_PHASE2.
     *
     * @see map_version_t
     */
    map_version_t   version ;  /* Only V2 is supported */
} map_primitive_t ;

/**
 * @} map_types
 */

/** 
 * @defgroup map_func MAP library functions 
 * @{
 */

/**
 * @brief Setup resources and intialize the MAP library.
 *
 * This function intializes the MAP library. 
 * This is the first MAP API call that an application needs to call.
 * The application can call this function only once during its lifetime.
 * The resources allocated will be released only during process termination.
 *
 * @param map_ver  MAP version as specified in map_version_t
 *
 * @param ttl_class_name the TTL class name to be used for tracing
 *
 * @return MAP_SUCCESS or MAP_FAILURE
 *
 * @see MAP_flush
 * @see map_version_t
 */
MAP_API int
MAP_init (int map_ver, char* ttl_class_name, ...);


/**
 * @brief Frees all resources for the specified connection-id.
 *
 * This function frees up all the resources assoicated with the
 * specified connection-id.
 *
 * @param cnx the tcap connection-id
 *
 * @return MAP_SUCCESS or MAP_FAILURE
 *
 * @see MAP_init
 */
MAP_API int
MAP_flush (map_cnxid_t cnx);

/**
 * @brief Builds and transmits a MAP message.
 *
 * This function builds and transmits a MAP message using TCAP. The application
 * must have previously registered as a new TCAP user to the SS7 platform. The
 * @a primitive parameter specifies the MAP primitive that will be used to send components
 * to a remote MAP user.<BR>
 * For congestion handling, please refer to the Congestion Handling section in the MAP Overview.
 *
 * @param cnx MAP communication end point to be used to send this message. This will be the TCAP connection-id. 
 *
 * @param timeo reserved for future use. MUST be set to NULL. 
 *
 * @param  primitive MAP primitive that needs to be sent.
 *
 * @param  msg  MAP message that needs to be sent.
 *
 * @param flags Not supported. MUST be set to 0.
 *
 * @return MAP_SUCCESS or MAP_FAILURE
 *
 * @see MAP_recv
 * @ref index
 */
MAP_API int
MAP_send ( map_cnxid_t         cnx,
	   struct timeval*     timeo,
	   map_primitive_t*    primitive,
	   map_message_t*      msg,
	   int                 flags );

/**
 * @brief Receives a TCAP message or a management primitive.
 *
 * This  function recieves a MAP message with its components
 * decoded. If required it allocates memory for the map message.
 * A call to this function returns a single MAP message/primitive.
 * The return value will specify if there are more messages to be
 * retrieved.<BR>
 * For congestion handling, please refer to the Congestion Handling section in the MAP Overview.
 *
 * @param cnx MAP communication endpoint from which the message should 
 * be recieved. This will be the TCAP connection-id.
 *
 * @param timeo reserved for future use. MUST be set to NULL.
 *
 * @param prim pointer to a MAP primitive structure. The structure will be 
 * filled by the library.
 *
 * @param msg pointer to the memory location where the map message stucture 
 * is allocated. If msg points to a null value, memory will be allocated by 
 * the library. After consuming the message, MAP_msg_free() function can be 
 * called to free this memory.
 *
 * @param flags Not supported. MUST be set to 0.
 *
 * @retval MAP_FAILURE          - check map_errno
 * @retval MAP_NO_MESSAGES      - no message received
 * @retval MAP_NO_MORE_MESSAGES - message has been received, but there are no more messages
 * @retval MAP_MORE_MESSAGES    - message has been received, and there are more messages
 *
 * @see MAP_send
 * @see MAP_msg_free
 * @ref index
 */
MAP_API int
MAP_recv ( map_cnxid_t         cnx,
	   struct timeval*     timeo,
	   map_primitive_t*    prim,
	   map_message_t**     msg,
	   int                 flags );
	   
/**
 * @brief Allocate a map message structure.
 *
 * This functions allocates a MAP message structure. The allocated message
 * can be freed by calling MAP_msg_free.
 *
 * @return Allocated message structure. NULL if the allocation fails.
 *
 * @see MAP_msg_free
 */
MAP_API map_message_t *
MAP_msg_alloc(void);


/**
 * @brief Free a MAP message structure
 *
 * This function frees a message structure that was previously allocated
 * by MAP_msg_alloc() function.
 *
 * @param msg pointer to the message structure. This should be a value that
 * was returned by MAP_msg_alloc().
 *
 * @return MAP_SUCCESS or MAP_FAILURE
 *
 * @see MAP_msg_alloc
 */
MAP_API int
MAP_msg_free(map_message_t *msg);

/**
 * @} map_func
 */

/** 
 * @defgroup map_util MAP utility functions
 * @{
 */

/**
 * @brief Get a string representing the MAP message type.
 *
 * This function can be used to get a string that represents the MAP message type.
 *
 * @param m_type a map_message_type_t value
 *
 * @return a string representing the map message type
 *
 * @see MAP_primitive_str
 * @see MAP_error_str
 * @see map_message_type_t
 */
const char *
MAP_msg_str(map_message_type_t m_type);

/**
 * @brief Get a string representing the MAP primitive type.
 *
 * This function can be used to get a string that represents the MAP primitive type.
 *
 * @param p_type a map_message_type_t value
 *
 * @return a string representing the map primitive type
 *
 * @see MAP_msg_str
 * @see MAP_error_str
 * @see map_primitive_type_t
 */
const char *
MAP_primitive_str(map_primitive_type_t p_type);

/**
 * @brief Get a string describing a MAP error.
 *
 * This function can be used to get a string that describes a MAP error.
 *
 * @param err a map_error value
 *
 * @return a string representing the the map message type
 *
 * @see MAP_msg_str
 * @see MAP_primitive_str
 * @see map_error
 */
const char *
MAP_error_str(map_error err);


/**
 * @} map_util
 */

#endif /* _MAP_H */

