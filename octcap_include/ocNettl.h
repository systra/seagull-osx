/**
 * @file ocNettl.h
 * @brief TTL interface
 */

#ifndef _OCNETTL_H
#define _OCNETTL_H

/* ANSI C headers */
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#ifndef _HPUX_SOURCE
#define _HPUX_SOURCE
#endif /* _HPUX_SOURCE */
#include <sys/time.h>
#if defined (__hpux)
#include <sys/stdsyms.h>
#endif
#endif

#ifdef _WIN32
#  ifndef HPAIN_TTLAPI
#      define HPAIN_TTLAPI __declspec(dllimport)
#  endif
#else
#define HPAIN_TTLAPI extern
#endif /* _WIN32 */

/* Opencall headers */
#include <TtlBase.h>


/**************** This is an LogId where we store all the FA's name **********/
/**************** Never change the value                            **********/
#define TTL_FA_LIST 2 

/******************************************************************/
/** 
** TraceLog format definition.  
** 1) Standard netTL Header (COMMON 
**  
** In the nettl natif header: 
** - time stamp (automatic)
** - process Id (automatic)
** - Device Id (not used)
** - Connection Id (not used) 
** - subssystem (TELECOM_SCP) 
** - Log Class (WARNING|INFO|ERROR|DISASTER)
** - Path ID (not used)
** - Log Sequence (automatic)  
** 
** 2) Standard TTL Header (PERSO)
** -  LogEntity  (Log Only) What we call a Functionnal Area (FA) 
**    (see in the formater the function TTL_decode_logEntity, 
**     wich translate 
**    the FA in an idenfier of a Message Set) 
** - Functionnal Are (Trace Only) 
** - MessageSet (related to the FA) 
** - Message Id.  
** - File, Line, and TypeId. 
**  
** 
** 3)  Log Message or Trace String
** - text (only for Trace) 
** - <Info Type>: (STR INT END) for Log  ( pointeur to string. Value)  
** 
** 4)  string parameters if present (log Only) 
**  
**/
/*******************************************************************/

/*******************************************************************/
/** 
**  subsystem definition for the OpenCall Products. 
**  This Id are managed by the ISO lab in Bengalore.
**/
/*******************************************************************/

/*******************************************************************/
/**    TTL_T_LogLevel represent the severity of the Log.
**/      
/*******************************************************************/

/**************************************************************************/
/**
** TTL_log interface
** 
**  JMB: what about the line and file in Java. 
**  How the prototype will gather the method and object. 
**  Shall we define an other fcuntion for Java ??  
**  shal we expose a lower interace (same level as TTL_trace)*/
/**************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* cctb#592: Changed the prototype to avoid Warning 829 */
OC_API
void TTL_ntrace( int P_level,
                 int P_funcArea,
                 int P_trace_id,
                 const char *P_str,
                 int *P_trace_count,
                 int *P_total_count,
                 int P_line,
                 const char *P_file );

/*******************************************************************/
/*  DESCRIPTION:  An enhanced version of TTL_trace   allowing      */
/*                                                                 */
/*                b) a scaling factor allowing the user to pass    */
/*                   a parameter which is used to scale that       */
/*                   particular trace; that is, the trace is only  */
/*                   output once for the 'scale' number of times   */
/*                   the program passes this point.                */
/*                                                                 */
/*******************************************************************/
/* cctb#592: Changed the prototype to avoid Warning 829 */
OC_API
void TTL_dtrace( int P_level,
                 int P_funcArea,
                 const char *P_str,
                 int P_typeId,
                 const void *P_dataPtr,
                 int P_dataLen,
                 int P_line,
                 const char *P_file );

/*************************************************************************/
/*  DESCRIPTION: calls nettl to record                                   */
/*               a trace from source code. Allow data "dumping"          */
/*                                                                       */
/*  USES:         Externally                                             */
/*                                                                       */
/*  PARAMETERS: P_level: trace level                                     */
/*              P_funcArea: functional area                              */
/*              P_str: expression to be printed or recorded              */
/*              P_typeId: data type Id (to be dumped)                    */
/*              P_dataPtr: Ptr to the datat to be dumped                 */
/*              P_dataLen: length of the data to be dumped               */
/*************************************************************************/

OC_API
void TTL_ndtrace( int P_level,
                  int P_funcArea,
                  int P_trace_id,
                  char *P_str,
                  const void *P_dataPtr,
                  int P_dataLen,
                  int P_element_size,
                  int *P_trace_count,
                  int *P_total_count,
                  int P_line,
                  char *P_file );

/*************************************************************************/
/*  DESCRIPTION: combination of TTL_ntrace  nd TTL_dtrace                */
/*************************************************************************/

OC_API
void TTL_ittrace( int P_level,
                  int P_funcArea,
                  int P_trace_id,
                  int *P_trace_count,
                  int *P_total_count,
                  int P_line,
                  char *P_file );

/************************************************************************/
/*                                                                      */
/*  DESCRIPTION :  This trace initialises a static global variable      */
/*     (that is visible)                                                */
/*     within the source file where this inlude file included)          */
/*     with the current time. The TTL_M_RTTRACE then read the           */
/*     timer and displays the total time and elapased timer             */
/*     relative to this start time.                                     */
/*                                                                      */
/************************************************************************/

OC_API
void TTL_rttrace( int P_level,
                  int P_funcArea,
                  int P_trace_id,
                  int *P_trace_count,
                  int *P_total_count,
                  int P_line,
                  char *P_file );

#ifdef __cplusplus
}
#endif

/*
** WARNING: DEPRECATED
** the following typedef has been included for backward compatibility
*/
#define TTL_Alarm   TTL_log

OC_API
char *TTL_sprintf(const char *P_fmt, ...);

/*****************************************************************************/
/*                                                                           */
/* char * trimSpaces(char * s)                                               */
/*                                                                           */
/*                                                                           */
/* DESCRIPTION: Used to trim leading and trailing white-space characters     */
/*                                                                           */
/* INPUTS: Gets a String as Input                                            */
/*                                                                           */
/* OUTPUT: Returns the trimmed String as Output                              */
/*                                                                           */
/*****************************************************************************/

char * trimSpaces(char *s);

/*****************************************************************************/
/*                                                                           */
/* int TTL_REGISTER_FA (const char * faName, const int faId)                 */
/*                                                                           */
/*                                                                           */
/* DESCRIPTION: Used to Register new Functional Areas                        */
/* Updates FA_BY_NAME_INT structure with the details of the new FA           */
/*                                                                           */
/* INPUTS: faName => Name of the new Functional Area                         */
/*         faId   => Id assigned to the new FA (via FA Assignment procedure  */
/*                                                                           */
/* OUTPUT: Returns faId of the faName if the faName did not occur previously */
/*         Returns -1 if either faName or faId is not unique                 */
/*         Returns -1 if faId is < 0  or faId > 2047                         */
/*         Returns -1 if faName is NULL                                      */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

OC_API
int TTL_REGISTER_FA (const char * faName, const int faId);

#ifdef __cplusplus
}
#endif
	
/*****************************************************************************/
/* TTL_M_DTRACE  (P_level,P_funcArea,P_str,P_typeId,P_dataPtr,P_dataLen)     */
/* TTL_M_NTRACE  (P_level, P_funcArea, trace_id, P_exp)			     */
/* TTL_M_NDTRACE (P_level,P_funcArea,trace_id,descr,addr,length,element_size)*/
/* TTL_M_ITTRACE  (P_level, P_funcArea, trace_id)			     */
/* TTL_M_RTTRACE (P_level, P_funcArea, trace_id)			     */
/*****************************************************************************/

/*************************************************************************/
/*  TTL_M_DTRACE(P_level,P_funcArea,P_str,P_typeId,P_dataPtr,P_dataLen)  */
/*                                                                       */
/*                                                                       */
/*  DESCRIPTION: call either printf functions or nettl to record         */
/*               a trace from source code. Allow data "dumping"          */
/*                                                                       */
/*  USES:         Externally                                             */
/*                                                                       */
/*  PARAMETERS: P_level: trace level                                     */
/*              P_funcArea: functional area                              */
/*              P_str: expression to be printed or recorded              */
/*              P_typeId: data type Id (to be dumped)                    */
/*              P_dataPtr: Ptr to the datat to be dumped                 */
/*              P_dataLen: length of the data to be dumped               */
/*************************************************************************/
#ifndef TTL_M_DTRACE
#define TTL_M_DTRACE(P_level,P_funcArea,P_str,P_typeId,P_dataPtr,P_dataLen) \
do { \
  TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
  { \
    TTL_dtrace(P_level, P_funcArea, P_str, P_typeId, P_dataPtr, P_dataLen, \
               __LINE__, __FILE__); \
  } \
} while(0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_DTRACE */

/*******************************************************************/
/*  TTL_M_NTRACE (P_level, P_funcArea, trace_id, P_exp)            */
/*                                                                 */
/*  DESCRIPTION:  An enhanced version of TTL_M_TRACE allowing      */
/*                                                                 */
/*                b) a scaling factor allowing the user to pass    */
/*                   a parameter which is used to scale that       */
/*                   particular trace; that is, the trace is only  */
/*                   output once for the 'scale' number of times   */
/*                   the program passes this point.                */
/*                                                                 */
/*  PARAMETERS:                                                    */
/*                                                                 */
/*******************************************************************/
#ifndef TTL_M_NTRACE
#define TTL_M_NTRACE(P_level, P_funcArea, trace_id, P_exp) \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
    { \
        static int trace_count = 0 ; \
        static int total_count = 0 ; \
        char *L_str; \
        L_str = (char*)TTL_sprintf P_exp; \
        TTL_ntrace(P_level, P_funcArea, trace_id, L_str, &trace_count, \
                   (int*)&total_count, __LINE__, __FILE__); \
    } \
} while(0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_NTRACE */

/* TRACE IDENTITIES -------- use with TTL_M_NTRACE----------------------------*/
/*                                                                            */
/* Identities used to uniquely identify each trace when required.             */
/* This can be used to configure the NTRACE as required.                      */
/*                                                                            */
/* Here is an example from Slee:                                              */
/*                                                                            */
/*      #define SLE_C_TID_smscreate        COM_C_TRACE_ID_01                  */
/*      #define SLE_C_TID_smscreate_1      COM_C_TRACE_ID_02                  */
/*      #define SLE_C_TID_trace_test_1     COM_C_TRACE_ID_03                  */
/*      #define SLE_C_TID_trace_test_2     COM_C_TRACE_ID_04                  */
/*                                                                            */
/* Then in your debug.conf file, your can affect a sampling value for each Id */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*******************************************************************/
/*                                                                 */
/* MACRO: TTL_M_NDTRACE(P_level, P_funcArea, trace_id, descr,      */
/*                      addr, length, element_size)                */
/*                                                                 */
/*  Parameters                                                     */
/*  ==========                                                     */
/*  P_level      as before                                         */
/*                                                                 */
/*  P_funcArea  as before                                          */
/*                                                                 */
/*  Scale        A scaling factor defining how often a trace is to */
/*               be output.                                        */
/*                                                                 */
/*  Tag          See NTRACE                                        */
/*                                                                 */
/*  Descr        Description of what is being output               */
/*                                                                 */
/*  Addr         The address of the item to be dumped              */
/*                                                                 */
/*  Length       The size of the elements to be dumped             */
/*                                                                 */
/*  Element_size The number of elements to be dumped               */
/*                                                                 */
/*******************************************************************/
#ifndef TTL_M_NDTRACE
#define TTL_M_NDTRACE(P_level, P_funcArea, trace_id, descr, addr, length, \
                      element_size) \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
    { \
        static int trace_count = 0 ; \
        static int total_count = 0 ; \
        char *L_str; \
        L_str = (char*)TTL_sprintf descr; \
        TTL_ndtrace(P_level, P_funcArea, trace_id, L_str, (const void*)addr, length, \
                    element_size, &trace_count, &total_count, \
                    __LINE__, __FILE__); \
    }\
} while(0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_NDTRACE */

/*******************************************************************/
/*                                                                 */
/* MACRO: TTL_M_ITTRACE(P_level, P_funcArea, trace_id)          */
/*                                                                 */
/*  Description                                                    */
/*  ===========                                                    */
/*                                                                 */
/*     This trace initialises a static global variable (that is,   */
/*     visable)                                                    */
/*     within the source file where this inlude file included)     */
/*     with the current time. The TTL_M_RTTRACE then read the      */
/*     timer and displays the total time and elapased timer        */
/*     relative to this start time.                                */
/*                                                                 */
/*  Parameters                                                     */
/*  ==========                                                     */
/*                                                                 */
/*     P_level, P_funcArea,      as for SCP_M_TRACE                */
/*                                                                 */
/*     trace_id     used to configure the frequency of             */
/*                  initialisation of                              */
/*                  timers, to synchronize them with               */
/*                 for example) SCP_M_NTRACE                       */
/*                                                                 */
/*******************************************************************/
#ifndef TTL_M_ITTRACE
#define TTL_M_ITTRACE(P_level, P_funcArea, trace_id) \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
    { \
        static int trace_count = 0 ; \
        static int total_count = 0 ; \
        TTL_ittrace(P_level, P_funcArea, trace_id, &trace_count, \
                    &total_count, __LINE__, __FILE__); \
    } \
} while(0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_ITTRACE */

#ifndef TTL_M_RTTRACE
#define TTL_M_RTTRACE(P_level, P_funcArea, trace_id) \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
    { \
        static int trace_count = 0 ; \
        static int total_count = 0 ; \
        TTL_rttrace(P_level, P_funcArea, trace_id, &trace_count, \
                    &total_count, __LINE__, __FILE__); \
    } \
} while(0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_RTTRACE */

/*
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
** never ever dereference any of the structure fields.
** this is to be used for memory allocation only 
** and passed as an abstract
** object to the nettl filter component.
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
*/

#define MAX_ioctlFilter   10

/*
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
** never ever dereference any of the structure fields defined above.
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
*/

/************************************************/
/* ttl configuration				*/	
/* table, function related to the storage 	*/
/* of trace configuration in unix C user space  */
/************************************************/

/*******************************************************/
/* no longer in libTTLBase 			       */
/*******************************************************/

/*
OC_API
FILE *TTL_V_DEV_NULL_stream_fd;

OC_API
int TTL_V_SCP_M_INIT_Debug ;      

OC_API
int TTL_V_SCP_M_INIT_has_not_run ;  
*/



/*************************************************************/
/* Major interface to load the filter                        */
/* this function is able to manage legacy and load the filter*/
/* even if tIe old method is used in the debug.conf          */
/* in this case, only the 32 first FA are loaded 	     */ 
/* we do not manage both mode. 				     */
/*************************************************************/
OC_API void scp_m_init(const char* P_class);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
OC_API void scp_m_init_new(const char* P_class);

OC_API void TTL_M_INIT(const char* P_class);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/************************************************************************/
/*
* TTL_C_FA_DEFAULT_MASK:
*
*  If the DEBUG compile flag is set, the default behaviour is to turn
*  everything on.  You can override this default behaviour either by
*  explicitly setting the different masks (via a configuration file, for
*  example), or by defining TTL_C_FA_DEFAULT_MASK before including this
*  file.
*
* TTL_M_TRACE:
*
*  This macro can be called to trace, based on a Trace Level mask and a
*  Functional Area mask.
*
*  The current behaviour is to call printf with some pre-defined
*  strings and the printf parameters you supply.  This will eventually
*  be changed to work with nettl.
*
* TTL_M_DTRACE:
*
*  This macro can be called to trace based on a Trace Level mask and a
*  Functional Area mask.
*
*  The current behaviour is to call printf with some pre-defined
*  strings, the string you supply, and a hex dump of the data structure
*  passed in.  This will eventually be changed to work with nettl.
*/
/************************************************************************/

/********************************* to manage legacy *********************/

/************************************************************************
*
*  The following are the starting points for each group to define
*  specific types of data structures that will be dumped.  This can be
*  used either for post-processing filters (the DTRACE type will be
*  printed out by the DTRACE macro), or for some other uses.
*
*************************************************************************/

#define  TTL_C_DTRACE_MASK            0x000fffff
#define  TTL_C_DTRACE_SCP_firstType   0x00010000
#define  TTL_C_DTRACE_SLEE_firstType  0x00020000
#define  TTL_C_DTRACE_7UP_firstType   0x00030000
#define  TTL_C_DTRACE_SCE_firstType   0x00040000
#define  TTL_C_DTRACE_NMGR_firstType  0x00050000

/************************************************************************
*
*  For example, the SLEE group would do something like:
*
*  typedef enum {SLE_E_callStruct = COM_C_DTRACE_SLEE_firstType,
*    SLE_E_otherStruct,
*    SLE_E_FA_...
*    }
*
*  in order to define their internal data structure types.
*  You can then invoke the tracer via a line such as:
*   TTL_M_DTRACE(COM_E_LL_FUNCTION,SLE_C_FA_general,"toto",
*                SLE_E_callStruct,myPtr,10)
*
*************************************************************************/

#ifdef DEBUG
/*
 * should not enable undefined and reserved bits for funcArea here !!
 */
#ifndef TTL_C_FA_DEFAULT_MASK
#define TTL_C_FA_DEFAULT_MASK 0xffffffff
#endif /* TTL_C_FA_DEFAULT_MASK */
#else
#ifndef TTL_C_FA_DEFAULT_MASK
#define TTL_C_FA_DEFAULT_MASK 0
#endif /* TTL_C_FA_DEFAULT_MASK */
#endif /* DEBUG */
#ifdef __cplusplus
extern "C" {
#endif

OC_API unsigned int TTL_V_subsysId;

#ifdef __cplusplus
}
#endif

typedef enum {
	COM_C_TRACE_ID_00,  /* reserved */
	COM_C_TRACE_ID_01,
	COM_C_TRACE_ID_02,
	COM_C_TRACE_ID_03,
	COM_C_TRACE_ID_04,
	COM_C_TRACE_ID_05,
	COM_C_TRACE_ID_06,
	COM_C_TRACE_ID_07,
	COM_C_TRACE_ID_08,
	COM_C_TRACE_ID_09,
	COM_C_TRACE_ID_10,

	COM_C_TRACE_ID_11,
	COM_C_TRACE_ID_12,
	COM_C_TRACE_ID_13,
	COM_C_TRACE_ID_14,
	COM_C_TRACE_ID_15,
	COM_C_TRACE_ID_16,
	COM_C_TRACE_ID_17,
	COM_C_TRACE_ID_18,
	COM_C_TRACE_ID_19,
	COM_C_TRACE_ID_20,

	COM_C_TRACE_ID_21,
	COM_C_TRACE_ID_22,
	COM_C_TRACE_ID_23,
	COM_C_TRACE_ID_24,
	COM_C_TRACE_ID_25,
	COM_C_TRACE_ID_26,
	COM_C_TRACE_ID_27,
	COM_C_TRACE_ID_28,
	COM_C_TRACE_ID_29,
	COM_C_TRACE_ID_30,

	COM_C_TRACE_ID_31,
	COM_C_TRACE_ID_32,
	COM_C_TRACE_ID_33,
	COM_C_TRACE_ID_34,
	COM_C_TRACE_ID_35,
	COM_C_TRACE_ID_36,
	COM_C_TRACE_ID_37,
	COM_C_TRACE_ID_38,
	COM_C_TRACE_ID_39,
	COM_C_TRACE_ID_40, 
	COM_C_TRACE_ID_41,
	COM_C_TRACE_ID_42,
	COM_C_TRACE_ID_43,
	COM_C_TRACE_ID_44,
	COM_C_TRACE_ID_45,
	COM_C_TRACE_ID_46,
	COM_C_TRACE_ID_47,
	COM_C_TRACE_ID_48,
	COM_C_TRACE_ID_49,
	COM_C_TRACE_ID_50,

	COM_C_TRACE_ID_SIZE
} COM_T_TRACE_ID ;

/*following chapter has been added for binary compatibility reasons */

/* -------------------------------------------------------------------- */
/* BEGINNING OF CIRCULAR BUFFER IMPLEMENTATION                          */
/* -------------------------------------------------------------------- */

/* *** C
// --------------------------------------------------------------------
// TTL_C_maxBuffer is the maximum allowed circular buffer for one process.
// TTL_C_printoutStringSize is the size of output string given by the caller
// when allocating a new circular buffer.
// On error, all routines return TTL_C_error.
// --------------------------------------------------------------------
****** */

typedef int TTL_T_histId;

/* Number of entries is fixed ( no allocation   */
/* while process is running ).                  */
#define TTL_C_maxBuffer            100
#define TTL_C_printoutStringSize    63

/* Return values.                               */
#define TTL_C_error                 -1
#define TTL_C_success                0

#ifdef __cplusplus
extern "C" {
#endif

/* *** C
// ----------------------------------------------------------
// TTL_circBuffAlloc :
//   Allocates a circular buffer of P_nbOfRecords records, each one being
//   of P_sizeOfRecord+TTL_V_sizeOfTimeStamp size. P_string allows for more
//   friendly printout and/or dump analysis. This string is truncated if needed
//   to fit in TTL_V_printoutStringSize. An identifier TTL_T_histId is returned,
//   which should be used in any forthcoming call.
// ----------------------------------------------------------
****** */

#if defined (__STDC__) || defined (__cplusplus)
TTL_T_histId TTL_circBuffAlloc ( size_t, int, const char* );
#else
TTL_T_histId TTL_circBuffAlloc ( );
#endif

/* *** C
// ----------------------------------------------------------
// TTL_circBuffWrite :
//   Will write  P_record in the circular  buffer  identified by histId.
//   It is the user's responsability to provide the correct kind of record for
//   the named  buffer.  A timestamp is added by TTL.
//   NO CONTROL is done on sizeof P_record. It is the user's
//   responsability to ensure that P_record fits in the allocated buffer.
//   An error on size will lead to a memory fault (and death of process).
// ----------------------------------------------------------
****** */

#if defined (__STDC__) || defined (__cplusplus)
int TTL_circBuffWrite ( TTL_T_histId, void*, size_t );
#else
int TTL_circBuffWrite ( );
#endif

/* *** C
// ----------------------------------------------------------
// TTL_circBuffFlush :
//   Will flush to nettl/screen the circular buffer named by histId.
//   If histId == 0, all circular buffers managed by TTL will be flushed.
// ----------------------------------------------------------
****** */

#if defined (__STDC__) || defined (__cplusplus)
int TTL_circBuffFlush ( TTL_T_histId );
#else
int TTL_circBuffFlush ( );
#endif

/* *** C
// ----------------------------------------------------------
// TTL_circBuffFree :
//    release allocated circular buffer. If histId == 0, all
//    circular buffers managed by TTL will be released.
// ----------------------------------------------------------
****** */

#if defined (__STDC__) || defined (__cplusplus)
int TTL_circBuffFree ( TTL_T_histId );
#else
int TTL_circBuffFree ( );
#endif

/* *** C
// ----------------------------------------------------------
// TTL_circBuffGetPtr :
//   Allow symbolic dumping by xdb of the buffer on the live
//   system or core dump.
// ----------------------------------------------------------
****** */

#if defined (__STDC__) || defined (__cplusplus)
void *TTL_circBuffGetPtr ( TTL_T_histId );
#else
void *TTL_circBuffGetPtr ( );
#endif

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
/* END OF CIRCULAR BUFFER IMPLEMENTATION                                */
/* -------------------------------------------------------------------- */

#endif /* _OCNETTL_H */

