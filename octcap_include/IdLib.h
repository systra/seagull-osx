/***********************************************************
*
* 
*
* $Source: /7UP/code/IdLib/inc/IdLib.h $
* $Revision: 4.1 $
* 
* 
***********************************************************/
/*
// Filename: IdLib.h 
// Creation date: 22/2/94
// Creator: BW
// Purpose:	Generate unique integers
*/

#ifndef IDLIB_H
#define IDLIB_H

/* Required files */
#include "ainCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define ID_INVALID_ID	-1
#define ID_MIN_ID		0
#define ID_MAX_ID		0x7ffffffe

/* Types and structures */

typedef int ID_UniqueId;

/* API functions */

extern ID_UniqueId ID_get_id(void);
extern char *ID_id_to_str(ID_UniqueId id);
extern ID_UniqueId ID_str_to_id(char *str);

/* Error returns */
extern int id_errno;

#define ID_ERR_BAD_STR	1
#define ID_ERR_BAD_ID	2

#ifdef __cplusplus
}	/* extern "C" */
#endif

#endif  /* IDLIB_H */
