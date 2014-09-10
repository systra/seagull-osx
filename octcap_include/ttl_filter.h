/**
 * @file ttl_filter.h
 */

#ifndef _TTLFILTER_H
#define _TTLFILTER_H

#include <TtlBase.h>
#include <ocNettl.h>

#ifdef _WIN32
#  ifndef HPAIN_TTLAPI
#      define HPAIN_TTLAPI __declspec(dllimport)
#  endif
#else
#ifndef HPAIN_TTLAPI
#define HPAIN_TTLAPI extern
#endif
#endif /* _WIN32 */

/**************************************************************************
 * Different Levels for Tracing
 **************************************************************************/

#define TTL_C_maxBuffer           100
#define TTL_C_printoutStringSize   63

#define TTL_C_success               0

/*The following definition has been moved to libTTLBase/TtlBase.h
 * Fix GREhp33853
 * the following typedef has been included for backward compatibility
 */
/*typedef  TTL_T_functionalArea    COM_T_functionalArea;*/

#define COM_E_FA_default         COM_E_FA_toBeDefined_1

/*
 *	LOG Entities definition and catalog set id affectation
 */

/*  FA already defined, 	MsgSetIds range from 20 to .... */

#define     FT_LOGENTITY	20	/* FT_LIB 	*/
#define     EH_LOGENTITY  	21	/* EH_LIB	*/
#define     MIB_LOGENTITY 	22	/* MIB_LIB	*/
#define     SS7_LOGENTITY 	23	/* SS7_LIB 	*/
#define     UTIL_LOGENTITY	24	/* UTIL_LIB	*/
#define     DDL_LOGENTITY	25	/* DDL_LIB	*/
#define     SMS_LOGENTITY	26	/* SMS_LIB	*/
#define     SCE_LOGENTITY	27	/* SCE		*/
#define     MB_LOGENTITY	28	/* MB_LIB	*/
#define     PPP_LOGENTITY	29	/* PPP_LIB	*/
#define	    BF_LOGENTITY	30	/* Babel fish lib */
#define	    ISUP_LOGENTITY	31	/* ISUP lib     */
#define	    NAL_LOGENTITY	32      /* NAL for MASH lib */
#define	    SIL_LOGENTITY	33      /* SIL_LIB      */

/**************************************************************************
*
*  The "reserved" enums must NOT be changed!
*
*  The "toBeDefined" enums are for each executable.  For example, the
*  SLEE group would do something like:
*
*    #define SLE_C_FA_general     COM_E_FA_toBeDefined_1
*    #define SLE_C_FA_callCollect COM_E_FA_toBeDefined_2
*    #define SLE_C_FA_smsHandler  COM_E_FA_toBeDefined_3
*    #define SLE_C_FA_dataBase    COM_E_FA_toBeDefined_4
*    #define SLE_C_FA_...         COM_E_FA_toBeDefined_...
*    }
*
*  for their own needs, as appropriate.
*
**************************************************************************/

/**************************************************************************
*
*  The following are the starting points for each group to define
*  specific types of data structures that will be dumped.  This can be
*  used either for post-processing filters (the DTRACE type will be
*  printed out by the DTRACE macro), or for some other uses.
*
**************************************************************************/

#define  TTL_C_DTRACE_MASK            0x000fffff
#define  TTL_C_DTRACE_SCP_firstType   0x00010000
#define  TTL_C_DTRACE_SLEE_firstType  0x00020000
#define  TTL_C_DTRACE_7UP_firstType   0x00030000
#define  TTL_C_DTRACE_SCE_firstType   0x00040000
#define  TTL_C_DTRACE_NMGR_firstType  0x00050000

/**************************************************************************
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
*   SLE_E_callStruct,myPtr,10)
*
**************************************************************************/

/**************************************************************************
*
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
*
**************************************************************************/

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

OC_API unsigned int    COM_isEnableLog[];
OC_API unsigned int    TTL_V_subsysId;
OC_API int             TTL_V_NTRACE_Config[];

#ifdef __cplusplus
}
#endif

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
/*  		P_typeId: data type Id (to be dumped)                    */
/*		P_dataPtr: Ptr to the datat to be dumped                 */
/*		P_dataLen: length of the data to be dumped               */
/*************************************************************************/
#ifndef TTL_M_DTRACE
#define TTL_M_DTRACE(P_level,P_funcArea,P_str,P_typeId,P_dataPtr,P_dataLen) \
do { \
  TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
  { \
    TTL_dtrace(P_level, P_funcArea, P_str, P_typeId, P_dataPtr,P_dataLen, \
               __LINE__, __FILE__); \
  } \
} while (0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_DTRACE */

/*******************************************************************/
/*  TTL_M_NTRACE (P_level, P_funcArea, trace_id, P_exp)         */
/*                                                                 */
/*  DESCRIPTION:  An enhanced version of TTL_M_TRACE allowing      */
/*                                                                 */
/*             	  b) a scaling factor allowing the user to pass    */
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
        static int    trace_count = 0 ; \
        static int    total_count = 0 ; \
		char *L_str; \
        L_str = TTL_sprintf P_exp; \
		TTL_ntrace(P_level, P_funcArea, trace_id, L_str, \
                           &trace_count, &total_count, __LINE__, __FILE__); \
    } \
} while (0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_NTRACE */

/* TRACE IDENTITIES -------- use with TTL_M_NTRACE----------------------------*/
/*									      */
/*Identities used to uniquely identify each trace when required.  This can be */
/*     used to configure the NTRACE as required.			      */
/*									      */
/*Here is an example from Slee:						      */
/*									      */
/*	#define SLE_C_TID_smscreate        COM_C_TRACE_ID_01		      */
/*	#define SLE_C_TID_smscreate_1      COM_C_TRACE_ID_02		      */
/*	#define SLE_C_TID_trace_test_1     COM_C_TRACE_ID_03		      */
/*	#define SLE_C_TID_trace_test_2     COM_C_TRACE_ID_04		      */
/*									      */
/*Then in your debug.conf file, your can affect a sampling value for each Id. */
/*									      */
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
        static int    trace_count = 0 ; \
        static int    total_count = 0 ; \
        char *L_str; \
        L_str = TTL_sprintf descr; \
        TTL_ndtrace(P_level, P_funcArea, trace_id, L_str, addr, length, \
                    element_size, &trace_count, &total_count, __LINE__, \
                    __FILE__); \
    }\
} while (0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_NDTRACE */

/*******************************************************************/
/*                                                                 */
/* MACRO: TTL_M_ITTRACE(P_level, P_funcArea, trace_id)             */
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
        static int    trace_count = 0 ; \
        static int    total_count = 0 ; \
	TTL_ittrace(P_level, P_funcArea, trace_id, &trace_count, \
                    &total_count, __LINE__, __FILE__); \
    } \
} while (0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_ITTRACE */

#ifndef TTL_M_RTTRACE
#define TTL_M_RTTRACE(P_level, P_funcArea, trace_id) \
do { \
    TTL_PRIV_M_TEST_TRACE_FLAG(P_level, P_funcArea) \
    { \
        static int    trace_count = 0 ; \
        static int    total_count = 0 ; \
        TTL_rttrace(P_level, P_funcArea, trace_id, &trace_count, \
                    &total_count, __LINE__, __FILE__); \
    } \
} while (0)

/*
 * the following typedef has been included for backward compatibility
 */
#endif /* TTL_M_RTTRACE */

/**********************************************************************
 *
 *		Function Declaration
 **********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)
#ifndef _WIN32

OC_API void ttlx_m_init(const char *e_name);

#endif /* _WIN32 */

OC_API void TTL_trace(TTL_T_TraceLevel P_level,
		      TTL_T_functionalArea P_funcArea,
		      const char *P_str, int P_line, const char *P_file);

OC_API void TTL_dtrace(int P_level, int P_funcArea, const char *P_str, int P_typeId,
		       const void *P_dataPtr, int P_dataLen, int P_line,
		       const char *P_file);

OC_API void TTL_ntrace(int P_level, int P_funcArea, int P_trace_id, const char *P_str,
		       int *P_trace_count, int *P_total_count, int P_line,
		       const char *P_file);

OC_API void TTL_ndtrace(int P_level, int P_funcArea, int P_trace_id,
			char *P_str, const void *P_dataPtr, int P_dataLen,
			int P_element_size, int *P_trace_count,
			int *P_total_count, int P_line, char *P_file);

OC_API void TTL_ittrace(int P_level, int P_funcArea, int P_trace_id,
			int *P_trace_count, int *P_total_count, int P_line,
			char *P_file);

OC_API void TTL_rttrace(int P_level, int P_funcArea, int P_trace_id,
			int *P_trace_count, int *P_total_count, int P_line,
			char *P_file);

OC_API void TTL_log(TTL_T_LogLevel P_level, TTL_T_threadControl P_threadType,
		    TTL_T_logEntity P_msgSetId, int P_msgId, ...);

OC_API void TTL_priv_log(TTL_T_LogLevel P_level, TTL_T_threadControl P_threadType,
		    TTL_T_logEntity P_msgSetId, int P_msgId, char **P_privParams, int P_numParams);

#ifdef __cplusplus
}
#endif

#else	/* not __STDC__ nor C++ */

/* K&R declarations to cope with Message Set
   (compiled with acc DSET compiler) */
#ifndef _WIN32
OC_API void ttlx_m_init();
#endif /* _WIN32 */

#endif /* __STDC__  or C++*/

#endif /* _TTLFILTER_H */
