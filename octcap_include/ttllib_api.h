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
 * @file MASH_gen_inc/ttllib_api.h
 * @brief common kernel TTL API between the 'Base TTL' and the 'Signaling TTL'
 *
 * TTL stands for "Telecom Tracing & Logging", the one & unique way of logging
 * LOGs & TRACEs by hp Opencall
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _TTLLIB_API_H
#define _TTLLIB_API_H

#if defined(__KERNEL__) || defined(_KERNEL)

#ifdef __cplusplus
extern "C" {
#endif

#include <ttllib_types.h>		/* SI_ttl_masks_t */

	typedef enum {
		TTL_E_LOG_INFORMATIVE = 0x00000001,
		TTL_E_LOG_WARNING = 0x00000002,
		TTL_E_LOG_ERROR = 0x00000004,
		TTL_E_LOG_DISASTER = 0x00000008
	} TTL_T_LogLevel;

/*******************************************************************/
/*	Enums and Macros for TTL_log function (ease of use )       */
/*******************************************************************/

	typedef enum {
		TTL_E_SAME_THREAD = 0,
		TTL_E_NEW_THREAD = 1,
		TTL_E_NO_THREAD = 2
	} TTL_T_threadControl;

/**************************************************************************/
/**
** The elipsis in TTL_log is a list of tuples made of a
** TTL_T_LOG_ARGTYPE and the corrresponding type variable followed by
** TTL_E_LOG_ARGTYPE_END and the line (int) and file string (char*)
**/
/**************************************************************************/

	typedef enum {
		TTL_E_LOG_ARGTYPE_END = -1,
		TTL_E_LOG_ARGTYPE_INT = 0,	/* argument must be int */
		TTL_E_LOG_ARGTYPE_STR = 1	/* argument must be char* */
	} TTL_T_LOG_ARGTYPE;

/*
 * public data & API
 */

	void SI_Lock_ttl_access (void);
	void SI_Unlock_ttl_access (void);
	int SI_ttl_init_masks (char *P_classname, SI_ttl_masks_t * P_masks);
	int SI_ttl_check (int P_id, int P_level, int P_funcArea);
	void SI_ttl_log_user (TTL_T_LogLevel P_level,
			      TTL_T_threadControl P_threadType,
			      int P_msgSetId, int P_msgId, ...);
	void SI_ttl_log (int P_id, TTL_T_LogLevel P_level,
			 TTL_T_threadControl P_threadType,
			 int P_msgSetId, int P_msgId, ...);
	void SI_ttl_vlog (TTL_T_LogLevel P_level,
			  TTL_T_threadControl P_threadType,
			  int P_msgSetId, int P_msgId, va_list L_args);
	void SI_ttl_trace (int P_level, int P_funcArea, const char *P_str,
			   int P_line, const char *P_file);
	void SI_ttl_vsprintf (char *P_out, char *P_fmt, va_list P_args);
	char *SI_ttl_sprintf (char *P_fmt, ...);
	char *SI_ttl_Kernel_sprintf (char *P_fmt, ...);

#ifdef __cplusplus
}				/* extern "C" */
#endif
#endif				/* __KERNEL__ || _KERNEL */
#endif				/* _TTLLIB_API_H */
