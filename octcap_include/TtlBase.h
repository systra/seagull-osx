/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License v2 as published by the Free Software Foundation; only
 *  version 2 of the License is valid for this software, unless
 *  explicitly otherwise stated.
 *
 *  This software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License v2 along with this program; if not, write to the
 *  Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 *  MA 02139, USA.
 */

/**
 * @file libTTLBase/TtlBase.h
 * @brief internal TTL API for choosing the logging back-end
 *
 * TTL stands for "Telecom Tracing & Logging", the one & unique way of logging
 * LOGs & TRACEs byb hp Opencall
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _TTLBASE_H
#define _TTLBASE_H

#if !defined(_KERNEL)
#include <octtl_aux.h>
#endif /* !_KERNEL */

#if defined(__linux__) && defined(__KERNEL__)
/******************************************************************
*
* Ttlbase.h: header file for tracing and logging thru
*            TtlBase framework
* embTtl.h: header file for tracing and logging thru
*            ttllib/tscttl framework
* ttllibapi.h: common API between TtlBase and ttllib modules
*
******************************************************************/
#include <ttllib_api.h>
#endif /* __linux__ && __KERNEL__ */

/*
 * logTrace
 */

#ifdef _WIN32
#  ifndef HPAIN_TTLAPI
#      define HPAIN_TTLAPI __declspec(dllimport)
#  endif
#else
#  ifndef HPAIN_TTLAPI
#define HPAIN_TTLAPI extern
#  endif
#endif

#ifndef OC_API
#define OC_API extern
#endif


#ifndef HPAIN_TTLAPI
#define HPAIN_TTLAPI OC_API
#endif

#if defined(_KERNEL)
/*
 * Expose the below functions to other modules
 */
int TTL_initialize (void);
void TTL_cleanup (void);
#endif  /* !_KERNEL */


/******************************************************************/
/**
** TraceLog format definition.
** 1) Standard netTL Header (COMMON)
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
** 2) Standard TTL Header (PRIVATE)
** -  LogEntity  (Log Only) What we call a Functionnal Area (FA)
**    (see in the formater the function TTL_decode_logEntity,
**     which translate the FA in an idenfier of a Message Set)
** - Functionnal Are (Trace Only)
** - MessageSet (related to the FA)
** - Message Id.
** - File, Line, and TypeId.
**
**
** 3)  Log Message or Trace String
** - text (only for Trace)
** - <Info Type>: (STR|INT|END) for Log  | ( pointeur to string.| Value)
**
** 4)  string parameters if present (log Only)
**
**/
/*******************************************************************/

/*******************************************************************/
/**
**  subsystem definition for the OpenCall Products.
**  This Id are managed by the ISO lab in Bengallor.
**/
/*******************************************************************/
/*
 use  TELECOM_SCP as subsystem
*/

#if defined(_KERNEL) || defined (__TANDEM)
/* WARNING !!! the theorical limitations is NL_TESTMAX in limits.h (8192).
   We reduce that to 2k */
#define TTL_C_MAX_LOG_MSG_LENGTH 	2048

/* WARNING !!! it is the length of a formatted string msg + args)*/
#ifndef TTL_C_MAX_TRACE_MSG_LENGTH
#define TTL_C_MAX_TRACE_MSG_LENGTH 	2048
#endif

/* Name of the tracing process */
#define TTL_C_MAX_TRACE_PROCESS_NAME  	512

/* Max no of trace messages for all threads used in TTLXX_vsprintf */
#define SIZE_MAX_MSG (TTL_C_MAX_TRACE_MSG_LENGTH - TTL_C_MAX_TRACE_PROCESS_NAME)
#define MAX_NUMBER_CONCURRENT_TRACE_MSG 20000
#define TRACE_LOCK_ORDER SPL_LOCK_ORDER

OC_API char TTL_V_SCP_M_INIT_ProcessName[TTL_C_MAX_TRACE_PROCESS_NAME];

#endif /* _KERNEL */

#if defined (__TANDEM)
#define _POSIX_PATH_MAX 127
#define TTL_LOG_ENTITY_SID 4
#endif

#ifdef TTLBASE_LEGACY_API
/*
* WARNING: DEPRECATED
* the following typedef has been included for backward compatibility
* definition of COM_T_logLevel as  TTL_T_TraceLevel
*/
typedef TTL_T_TraceLevel COM_T_logLevel;
#endif /* TTLBASE_LEGACY_API */

#if !defined(__linux__) || !defined(__KERNEL__)
/*******************************************************************/
/**    TTL_T_LogLevel represent the severity of the Log.	   */
/*******************************************************************/

typedef enum {
	TTL_E_LOG_INFORMATIVE = 0x00000001,
	TTL_E_LOG_WARNING = 0x00000002,
	TTL_E_LOG_ERROR = 0x00000004,
	TTL_E_LOG_DISASTER = 0x00000008
} TTL_T_LogLevel;

/*******************************************************************/
/**    TTL_T_threadControl .
**/
/*******************************************************************/

typedef enum {
	TTL_E_SAME_THREAD = 0,
	TTL_E_NEW_THREAD = 1,
	TTL_E_NO_THREAD = 2
} TTL_T_threadControl;

/*******************************************************************/
/**
** The elipsis in TTL_log is a list of tuples made of a
** TTL_T_LOG_ARGTYPE and the corrresponding type variable followed by
** TTL_E_LOG_ARGTYPE_END and the line (int) and file string (char*)
**/
/*******************************************************************/

typedef enum {
	TTL_E_LOG_ARGTYPE_END = -1,
	TTL_E_LOG_ARGTYPE_INT = 0,	/* argument must be int */
	TTL_E_LOG_ARGTYPE_STR = 1	/* argument must be char* */
} TTL_T_LOG_ARGTYPE;
#endif /* !__linux__ || !__KERNEL__ */

/*
** trace level is an enum 0..31 for implementation reasons
*/

/**************************************************************************/
/**  Different Levels for Tracing (Trace filtering element)               */
/**  definition of 8 Level.						  */
/**************************************************************************/

typedef enum {

	COM_E_LL_FUNCTION = 0x10000000,	/* Function (or method) flow;
					   entry, middle
					   and/or exit: Verbose */
	COM_E_LL_MEMORY = 0x01000000,	/* Heap memory allocation/deallocation;
					   for data structures: Limited */
	COM_E_LL_OBJECTS = 0x00100000,	/* Object instantiation/destruction:
					   Verbose */
	COM_E_LL_ERROR = 0x00010000,	/* Exception handling path (exception
					   was detected): Limited */
	COM_E_LL_WARNING = 0x00001000,	/* Warning */

	COM_E_LL_INFOFLOW1 = 0x00000100,	/* Message/PDU/Event
						   flow through
						   (basic level): Limited */
	COM_E_LL_INFOFLOW2 = 0x00000200,	/* Message/PDU/Event
						   flow through
						   (full level): Verbose */
        /* Fix GREhp33417  */
        COM_E_LL_INFOFLOW3 = 0x00000400,   /* Message/PDU/Event flow through 
                                          (full level): Verbose 
                                          In M3UA this level is for :
                                          ASPSM, ASPTM, MGMT, RKM  messages */
	COM_E_LL_STATES = 0x00000010,	/* State changes:
					   Verbose */
	COM_E_LL_STARTUP = 0x00000001,	/* Initialization or other startup
					   stateuses (for example, config info)
					   :Verbose (but limited in time) */
	lgend
} TTL_T_TraceLevel;



/**********************************************************/
/* Following trace levels are emitted by the Hardware.    */
/* 'ttllib' and 'tscttl' only understand these values.    */
/* They are later transformed into levels understandable  */
/* the nettl API.                                         */
/* Since the levels were changed from the 'old'           */
/* supportability to                                      */
/* the 'new' supportability framework, a new matching is  */
/* needed.                                                */
/**********************************************************/

#define MASH_COM_E_LL_FUNCTION     0
#define MASH_COM_E_LL_MEMORY       1
#define MASH_COM_E_LL_OBJECTS      2
#define MASH_COM_E_LL_ERROR        3
#define MASH_COM_E_LL_INFOFLOW1    4
#define MASH_COM_E_LL_INFOFLOW2    5
#define MASH_COM_E_LL_STATES       6
#define MASH_COM_E_LL_STARTUP      7

/**************************************************************************/
/**
** Type TTL_T_logEntity and TTL_T_functionalArea
**
** TTL_T_logEntity    ........... for Logs
** TTL_T_functionalArea ......... for Traces
**
** both types for a given platform should be defined in a unique include
** file as an enum type or a set of defines.
** logEntity value must be equal to the nls catalog message set for the
** netfmt OC formater
** functionalArea should be contiguous for memrory space reasons
**
**
** for an example of #define of ainCommon.h
** or /SLEE/code/IC32_GenericServices/sleecommon.h
** and also in ttlCommon.h.
**
** In subssystem.h we can see:
** #define SUBSYS_TOTO_C_FA_X   16
** #define SUBSYS_TOTO_C_FA_Y   17
**
** in the legacy the FA are limited to 32.
** for each bit the possible values are 1,2,4,8
** and there are 8 fields. (4x8=32)
**
**/
/**************************************************************************/

typedef unsigned int TTL_T_logEntity;	/* int32_t */
typedef unsigned int TTL_T_functionalArea;

/* Definition of COM_T_functionalArea 
*  Definition moved from libTTL/ttl_filter.h to libTTLBase/TtlBase.h
*  Fix GREhp33853
*/

typedef  TTL_T_functionalArea    COM_T_functionalArea;

#ifdef __cplusplus
extern "C" {
#endif
OC_API int ttl_priv_m_test_trace_flag(TTL_T_TraceLevel P_level, TTL_T_functionalArea P_funcArea);
OC_API char * TTL_sprintf (const char *P_fmt, ...);
#ifdef __cplusplus
}
#endif

/** default FA. do not use **/
#define COM_E_FA_default         COM_E_FA_toBeDefined_1

#ifndef TTL_M_INT
#define TTL_M_INT(P_integerValue)    TTL_E_LOG_ARGTYPE_INT, P_integerValue
#endif /* TTL_M_INT */

#ifndef TTL_M_STR
#define TTL_M_STR(P_string)          TTL_E_LOG_ARGTYPE_STR, P_string
#endif /* TTL_M_STR */

#ifndef TTL_M_EOA
#define TTL_M_EOA TTL_E_LOG_ARGTYPE_END, __LINE__, __FILE__
#endif /* TTL_M_EOA */


/**************************************************************************/
/**
** TTL_trace interface
**
**  JMB: what about the line and file in Java.
**  can define enum for P_line/Pfile.
**   need to modify formater if we change the intof line in string !
**/
/**************************************************************************/

/* aCC compiler does not handle interface C function
** unless they are declared with extern "C" before
** just as below
*/

#ifdef __cplusplus
extern "C" {
#endif

	OC_API
	    void TTL_trace (TTL_T_TraceLevel P_level,
			    TTL_T_functionalArea P_funcArea,
			    const char *P_str, int P_line, const char *P_file);

	 OC_API
	    void TTL_log (TTL_T_LogLevel P_level,
			  TTL_T_threadControl P_threadType,
			  TTL_T_logEntity P_msgSetId, int P_msgId, ...);


	 OC_API
	    void TTL_priv_log (TTL_T_LogLevel P_level,
			  TTL_T_threadControl P_threadType,
			  TTL_T_logEntity P_msgSetId, int P_msgId, char **P_privParams, int P_numParams);

#ifdef __cplusplus
}
#endif

/* Defines */
#define TTL_C_MAX_LOG_STR_LEN       255	/* log argument string type
					   max length */
#define TTL_C_TEMPBUF_SIZE	    512	/* buf used to assemble "msg not found
					   in catalog: catlog name, path ... */
#define TTL_C_MAX_NUMBER_OF_LOG_ARG 9	/* max number of args which can
					   be passed in TTL_log call including
					   the TTL_M_EOA (last arg) */
#define TTL_C_FILESIZE              255	/* file name paased in log call
					   __FILE__ length */
#define TTL_C_MAX_BUF 		    20	/* number of iovec structure */
#ifndef TTL_GENERIC_LOGENTITY
#define TTL_GENERIC_LOGENTITY 	    1	/* Reserved  for TTL */
#endif				/* TTL_GENERIC_LOGENTITY */
#define TTL_LOG_TAG_STRING_ID	    20	/* LOG tag message ID in catalog */
#define TTL_TRACE_NO_TIME_STAMP     0
#define TTL_TIME_STAMP_REAL         1
#define TTL_TIME_STAMP_RELATIVE     2
#define TTL_TRACE_TAG_LEN           41	/* 37 when using short format */
#define TTL_TRACE_TEXT_LEN          39	/* short format text length */
#define TTL_TIME_STR_START          11
#define TTL_TIME_STR_END            19
#define TTL_TRACE_MAX_FORMAT_DEF    256
#define TTL_NOS_TRACE_OP_CONFIG     10
#define TTL_HEX_LINE_LENGTH    	    61
#define TTL_PRINTF_TRACE_MAX_LENGTH 30

#define TTL_D_TRACE_MASK          SUBSYSTEM_BITS
#define TTL_D_TRACE_FUNCTION      0x00000001
#define TTL_D_TRACE_MEMORY        0x00000002
#define TTL_D_TRACE_OBJECTS       0x00000004
#define TTL_D_TRACE_ERROR         0x00000008

/* Fix GREhp33417
** Adding WARNING level */
#define TTL_D_TRACE_WARNING       0x00000100

#define TTL_D_TRACE_INFOFLOW1     0x00000010
#define TTL_D_TRACE_INFOFLOW2     0x00000020

/* Fix GREhp33417
** Adding INFOFLOW3 level */
#define TTL_D_TRACE_INFOFLOW3     0x00000200

#define TTL_D_TRACE_STATES        0x00000040
#define TTL_D_TRACE_STARTUP       0x00000080


#ifdef COCA_WIN32
/* Library entry point */
OC_API BOOL libTTL_DllMain (HANDLE hInst,
			    ULONG ul_reason_for_call, LPVOID lpReserved);
#endif /* COCA_WIN32 */

/*
**
** filtering
**
*/

/* limitation of the FA available no overlay  */
#define TTL_C_MAX_NUMBER_OF_TTL_FA 2048


/*
** WARNING: NEVER EVER ACCESS THE VARIABLE ABOVE DIRECTLY
*/

/*******************************************************************/
/*  TTL_M_TRACE(P_level,P_funcArea,P_exp)                          */
/* 								   */
/* DESCRIPTION :						   */
/* TTL_M_TRACE  call NetTL to record a trace message from source   */
/* code. Before to call NetTL TTL_M_TRACE checks that tracing is   */
/* enabled for the specified trace level and functional area.      */
/*								   */
/* PARAMETERS :							   */
/*								   */
/* P_level : to be chosen among TTL_T_TraceLevel values		   */
/* example : COM_E_LL_ERROR					   */
/*								   */
/* P_funcArea :  : to be chosen among values defined in FA.def     */
/* example : OCMP_FA_TRANSPORT					   */
/*								   */
/* P_exp : P_exp is an expression between parenthesis  that could  */
/* be passed to a printf. 					   */
/* example : ("MIB_comStatus  P_comId= %d  not found\n ", P_comId) */
/*                                                                 */
/*******************************************************************/

extern unsigned int TTL_V_filter[];
#ifndef TTL_PRIV_M_TEST_TRACE_FLAG
#define TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
   if ( (TTL_V_filter[P_funcArea]) & (P_level))
#endif

#ifndef TTL_M_TRACE
#define TTL_M_TRACE(P_level,P_funcArea,P_exp)  \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG((P_level), P_funcArea) \
    { \
	  char *L_str;  \
          L_str = (char*)TTL_sprintf P_exp; \
          TTL_trace((P_level), P_funcArea, (const char*)L_str, __LINE__, (const char*)__FILE__); \
    } \
} while(0)
#endif				/* !TTL_M_TRACE */

/*
   TTL_M_TEST_TRACE_FLAG previously wrongly (because of new supportability)
   defined in uxEnvironnement/logger.h
*/

/* Fix: GREhp30032 */
#ifndef TTL_M_TEST_TRACE_FLAG
#define TTL_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
        (ttl_priv_m_test_trace_flag(P_level, P_funcArea))
#endif


/*
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
** never ever dereference any of the structure fields.
** this is to be used for memory allocation only
** and passed as an abstract
** object to the nettl filter component.
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
*/
#define TTL_E_MAX_IOCTLFILTER   10
typedef struct {
	TTL_T_TraceLevel level;
	TTL_T_functionalArea funcArea;
} TTL_T_traceFilterItem;

typedef enum { TTL_E_ENABLE, TTL_E_DISABLE } TTL_Ioctl_Operation;

typedef struct {
	TTL_Ioctl_Operation operation;
	unsigned int nbItems;
	TTL_T_traceFilterItem filters[TTL_E_MAX_IOCTLFILTER];
} TTL_T_filterIoctl;
/*
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
** never ever dereference any of the structure fields defined above.
** WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
*/

#define TTL_E_OPIOCTL    (_IOW('O', 0, TTL_T_filterIoctl))
#define TTL_E_TEST_LOG   (_IOW('O', 1, int))
#define TTL_E_TEST_TRACE (_IOW('O', 2, int))

#ifndef NOEXPORTEDFUNC
/*--------------------------------------------------------------------
** WARNING : do not modify the ifndef above and matching endif
**
** The following area defines the exported functions
**--------------------------------------------------------------------
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
**-function---------------------------------------------------------------
**
** void TTL_F_InitFilter
**
**  DESCRIPTION : sets 0 everywhere in TTL_V_Filter
**
** ------------------------------------------------------------------------
*/
	OC_API void TTL_F_InitFilter (void);

/*
**-function---------------------------------------------------------------
**
** void TTL_F_enableTraceAllFa(TTL_T_TraceLevel P_level)
**
**  DESCRIPTION : for a given Trace Level, enable tracing of all
**                Functional Areas
**
**  PARAMETER :
**     P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_ERROR
**
** ------------------------------------------------------------------------
*/
	OC_API void TTL_F_enableTraceAllFa (TTL_T_TraceLevel P_level);

/* -function---------------------------------------------------------------
**
** void TTL_F_disableTraceAllFa(TTL_T_TraceLevel P_level)
**
**  DESCRIPTION : for a given Trace Level, disable tracing of all
**                Functional Areas
**
**  PARAMETER :
**     P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_ERROR
**
** ------------------------------------------------------------------------
*/
	OC_API void TTL_F_disableTraceAllFa (TTL_T_TraceLevel P_level);

/* -function---------------------------------------------------------------
**
** TTL_F_enableTraceManyFa
**
**  DESCRIPTION : enable a level of trace for a set of funcArea
**
**
** PARAMETERS :
**   P_level : to be chosen among TTL_T_TraceLevel values
**   example : COM_E_LL_INFOFLOW1
**
**   P_nbFa : number of elements of the following array
**
**   P_funcAreaTable[] : array of F.As for which we want to enable
**                       specific Trace Level
**
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_enableTraceManyFa (TTL_T_TraceLevel P_level, int P_nbFa,
					  TTL_T_functionalArea
					  P_funcAreaTable[]);

/* -function---------------------------------------------------------------
**
** TTL_F_disableTraceManyFa
**
**  DESCRIPTION : disable a level of trace for a set of funcArea
**
**
** PARAMETERS :
**   P_level : to be chosen among TTL_T_TraceLevel values
**   example : COM_E_LL_INFOFLOW1
**
**   P_nbFa : number of elements of the following array
**
**   P_funcAreaTable[] : array of F.As for which we want to enable
**                       specific Trace Level
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_disableTraceManyFa (TTL_T_TraceLevel P_level, int P_nbFa,
					   TTL_T_functionalArea
					   P_funcAreaTable[]);

/* -function---------------------------------------------------------------
**
** void TTL_F_enableTrace(TTL_T_TraceLevel P_level,
**
**  DESCRIPTION :  enable tracing for a specific FA at a specific Trace Level
**
**  PARAMETERS :
**    P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_INFOFLOW1
**
**   P_funcArea :  : to be chosen among values defined in FA.def
**    example : OCMP_FA_HARDWARE
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_enableTrace (TTL_T_TraceLevel P_level,
				    TTL_T_functionalArea P_funcArea);

/* -function--------------------------------------------------------------
**
** void TTL_F_disableTrace(TTL_T_TraceLevel P_level
**                         TTL_T_functionalArea P_funcArea);
**
**  DESCRIPTION :  prevent tracing for a specific FA at a specific Trace Level
**
**  PARAMETERS :
**    P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_INFOFLOW1
**
**   P_funcArea :  : to be chosen among values defined in FA.def
**    example : OCMP_FA_HARDWARE
**
** ------------------------------------------------------------------------
*/

	 OC_API
	    void TTL_F_disableTrace (TTL_T_TraceLevel P_level,
				     TTL_T_functionalArea P_funcArea);

/* -function---------------------------------------------------------------
**
** TTL_F_enableTraceIoctl
**
**  DESCRIPTION : same as enableTrace but sets the ioctl rather than
**                the filter itself
**
**
**  PARAMETERS :
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**  P_level : to be chosen among TTL_T_TraceLevel values
**    example : COM_E_LL_INFOFLOW1
**
**  P_funcArea : to be chosen among values defined in FA.def
**   example : OCMP_FA_HARDWARE
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_enableTraceIoctl (TTL_T_filterIoctl * P_ioctl,
					 TTL_T_LogLevel P_level,
					 TTL_T_functionalArea P_funcArea);

/* -function---------------------------------------------------------------
**
** TTL_F_disableTraceIoctl
**
**  DESCRIPTION : same as disableTrace but sets the ioctl rather than
**                the filter itself
**
**
**  PARAMETERS :
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**  P_level : to be chosen among TTL_T_TraceLevel values
**    example : COM_E_LL_INFOFLOW1
**
**  P_funcArea : to be chosen among values defined in FA.def
**   example : OCMP_FA_HARDWARE
**
** ------------------------------------------------------------------------
*/
	void TTL_F_disableTraceIoctl (TTL_T_filterIoctl * P_ioctl,
				      TTL_T_LogLevel P_level,
				      TTL_T_functionalArea P_funcArea);

/* -function---------------------------------------------------------------
**
** TTL_F_enableTraceManyFaIoctl
**
**  DESCRIPTION : same as enableTraceManyFa but sets the ioctl rather than
**                the filter itself. The funcArea table must not have more than
**                TTL_E_MAX_IOCTLFILTER items, other items are  ignored.
**
**  PARAMETERS :
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**    P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_INFOFLOW1
**
**   P_nbItems : number of elements of the following array
**
**   P_funcAreaTable[] : array of F.As for which we want to enable
**                       specific Trace Level
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_enableTraceManyFaIoctl (TTL_T_filterIoctl * P_ioctl,
					       TTL_T_LogLevel P_level,
					       int P_nbItems,
					       TTL_T_functionalArea
					       P_funcAreaTable[]);

/* -function---------------------------------------------------------------
**
** TTL_F_disableTraceManyFaIoctl
**
**  DESCRIPTION : same as disableTraceManyFa but sets the ioctl rather than
**                the filter itself. The funcArea table must not have more than
**                TTL_E_MAX_IOCTLFILTER items, other items are  ignored.
**
**  PARAMETERS :
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**    P_level : to be chosen among TTL_T_TraceLevel values
**     example : COM_E_LL_INFOFLOW1
**
**   P_nbItems : number of elements of the following array
**
**   P_funcAreaTable[] : array of F.As for which we want to enable
**                       specific Trace Level
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_disableTraceManyFaIoctl (TTL_T_filterIoctl * P_ioctl,
						TTL_T_LogLevel P_level,
						int P_nbItems,
						TTL_T_functionalArea
						P_funcAreaTable[]);

/* -function---------------------------------------------------------------
**
** TTL_F_enableTraceManyIoctl
**
**  DESCRIPTION : enable trace for a set of funcArea, level tuples.
**  The funcArea table must not have more than TTL_E_MAX_IOCTLFILTER items,
**  other items are  ignored.
**
**  PARAMETERS :
**
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**    P_nbItems : number of elements of the following array
**
**    P_filterItem[] : array of tuples TTL_T_tracefilterItem
**
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_enableTraceManyIoctl (TTL_T_filterIoctl * P_ioctl,
					     int P_nbItems,
					     TTL_T_traceFilterItem
					     P_filterItem[]);

/* -function---------------------------------------------------------------
**
** TTL_F_disableTraceManyIoctl
**
**  DESCRIPTION : disable trace for a set of funcArea, level tuples.
**  The funcArea table must not have more than TTL_E_MAX_IOCTLFILTER items,
**  other items are ignored.
**
**  PARAMETERS :
**
**    P_ioctl : pointer to a TTL_T_filterIoctl structure
**
**    P_nbItems : number of elements of the following array
**
**    P_filterItem[] : array of tuples TTL_T_tracefilterItem
**
** ------------------------------------------------------------------------
*/
	 OC_API
	    void TTL_F_disableTraceManyIoctl (TTL_T_filterIoctl * P_ioctl,
					      int P_nbItem,
					      TTL_T_traceFilterItem
					      P_filterItem[]);

/* -function---------------------------------------------------------------
**
** TTL_F_execIoctl
**
**  DESCRIPTION : Runs filter table effective update.
**  in case of error, the error is logged in nettl.
**  returns an errno
**
** ------------------------------------------------------------------------
*/
	OC_API int TTL_F_execIoctl (TTL_T_filterIoctl * P_ioctl);

#ifdef __cplusplus
}
#endif
#endif				/* NOEXPORTEDFUNC */
#endif				/* _TTLBASE_H */
