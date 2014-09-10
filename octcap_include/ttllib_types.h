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

#ifndef _cctb_1_ttllib_types_h_H
#define _cctb_1_ttllib_types_h_H

#define lint 

#ifndef lint
static char    *_cctb_1_ttllib_types_h = "@(#) %filespec: ttllib_types.h~1 %  (%full_filespec: ttllib_types.h~1:incl:cctb#1 %)";
#endif


/*                               -*- Mode: C -*-
 *
 *  (c) Copyright Hewlett-Packard Company 2002, 2003
 *  All Rights Reserved
 */

/**
 * @file libTTLBase/ttllib_types.h
 * @brief common kernel TTL API between the 'Base TTL' and the 'Signaling TTL'
 *
 * TTL stands for "Telecom Tracing & Logging", the one & unique way of logging
 * LOGs & TRACEs by hp Opencall
 *
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 */

#ifndef _TTLLIB_TYPES_H
#define _TTLLIB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Type for passing trace and log masks about */
typedef struct {
	unsigned int trace_masks[8];	/* One element per level */
	unsigned int log_mask;	/* bit: 0-info, 1-warning,
				   2-error, 3-disaster */
} SI_ttl_masks_t;

/*
 * Below definations were conflicting with the one in TTLformatter
 * and ttlRecover, this is made common here in one place.
 * this forces TTLformatter and ttlRecover to include this header file.
 */
typedef enum {
	TTL_E_last = -1,
	TTL_E_integ,
	TTL_E_uInteg,
	TTL_E_string
} TTL_T_paramId_t;
typedef TTL_T_paramId_t TTL_T_paramId;

typedef struct {
	TTL_T_paramId_t param_type; /* integer or string */
	int value_of_int;	/* if integer its value */
	unsigned int param_offset; /* offset of string */
	int param_length;	/* length of string */
} TTL_T_parameter_header_t;
typedef TTL_T_parameter_header_t TTL_T_parameter_header;

#define TTL_C_MAX_LOG_STR_LEN       255	/* log argument string type
					   max length */
typedef struct {
	TTL_T_paramId_t paramId;
	int paramSize;
	union {
		int iParam;
		unsigned int uParam;
		/* null terminated string */
		char strParam[TTL_C_MAX_LOG_STR_LEN];
	} param;
} TTL_T_param_t;
typedef TTL_T_param_t TTL_T_param;

#ifdef __cplusplus
}				/* extern "C" */
#endif
#endif				/* _TTLLIB_TYPES_H */

#endif
