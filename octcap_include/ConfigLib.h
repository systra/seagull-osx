/***********************************************************
*
* 
*
* $Source: /7UP/code/ConfigLib/inc/ConfigLib.h $
* $Revision: 6.4 $
* 
* 
***********************************************************/
/*
// Filename: configlib.h
// Creation date: 7/1/93
// Creator: BW
// Purpose:	Exported header file for configuration library API
*/

#ifndef CONFIGLIB_H
#define CONFIGLIB_H

/* Required files */
#ifdef COCA_WIN32
#include <windows.h>
#endif /* COCA_WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
#ifndef _USE_RESOURCE_LOCATOR
	#define ENVIRON_HP_AIN_ROOT "HP_AIN_ROOT"
#endif /* _USE_RESOURCE_LOCATOR */
#define ENVIRON_CFG_FILE "HP_AIN_CONFIG_FILE"

#ifdef COCA_WIN32
	#define DEFAULT_GLOBAL_FILENAME "config\\global.conf"		/* Note that $HP_AIN_ROOT is added to start of this */
	#define DEFAULT_LOCAL_FILENAME ".\\global.conf"
	/* 
		Warning : DEFAULT_HP_AIN_ROOT is made of SystemDrive environment variable.
				  To get the true path, you must transform DEFAULT_HP_AIN_ROOT with 
				  ExpandEnvironmentStrings first.
	*/
	#define DEFAULT_HP_AIN_ROOT "%SystemDrive%\\Program Files\\Hewlett-Packard\\HP-AIN\\"
#else
	#ifndef _USE_RESOURCE_LOCATOR
		#define DEFAULT_GLOBAL_FILENAME "config/global.conf"		/* Note that $HP_AIN_ROOT is added to start of this */
		#define DEFAULT_LOCAL_FILENAME "./global.conf"
		#define DEFAULT_HP_AIN_ROOT	"/opt/HP-AIN/"
	#else
		#define DEFAULT_GLOBAL_FILENAME "/etc/opt/OC/platform/global.conf"
		#define DEFAULT_HP_AIN_ROOT	"/opt/OC/"
	#endif /* _USE_RESOURCE_LOCATOR */
#endif

#define MAXLEN_CLASSNAME	80
#define MAXLEN_KEYNAME		80
#define MAXLEN_KEY			255
#define CFG_C_MAXLEN_VALUE	127


/* Types and structures */

    
/* API functions */
#define CFGCOM_D_SEPARATORS  " ,"        /* separators used on a config line */

    
#ifdef _USE_RESOURCE_LOCATOR
	int CFG_CutValues(char value[][CFG_C_MAXLEN_VALUE], const char*, const int);
#else
	char *CFG_get_hpain_root(void);
#endif /* _USE_RESOURCE_LOCATOR */
int CFG_init(char *);
int CFG_close(int);
int CFG_get_classes(int, const char *, int, char **);
int CFG_get_key_value(int, const char *, const char *, int, char **, char **);
int CFG_set_key_value(int, char *, int, char **, char **);

/* Error returns */

extern int cfg_errno;


#define CFG_NOFILE			1	/* Could not find, or fstat file */
#define CFG_PERM			2	/* Found file, but could not open for reading */
#define CFG_NOSUCHNAME		3	/* Could not find class or key value in file */
#define CFG_NOTINITIALISED	4	/* CFG_init not done for this id */
#define CFG_BADFILE			5	/* General error in parsing a line in the file (only if no specific error) */
#define CFG_NOCLASSES		6	/* No class sections found in file */
#define CFG_DUPCLASS		7	/* Duplicate class name found in file */
#define CFG_EMPTYFILE		8	/* File had zero length */
#define CFG_NOMEM			9	/* Malloc failed */
#define CFG_READERROR		10	/* file system error loading file */
#define CFG_KEYWITHNOCLASS	11	/* A valid key line was found outwith a class section */

#ifdef COCA_WIN32
/* Library entry point */
extern BOOL ConfigLib_DllMain (HANDLE hInst, 
                            ULONG ul_reason_for_call,
                            LPVOID lpReserved);
#endif 

#ifdef __cplusplus
}	/* extern "C" */
#endif


#endif  /* CONFIGLIB_H */
