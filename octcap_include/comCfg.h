/**
 * @file comCfg.h
 * @brief Public API - Common routines used for parsing global.conf
 *
 * @author RK
 * @author Hewlett-Packard Company
 * @author Opencall Business Unit
 *
 * @verbatim
Copyright (c) 1996 Hewlett-Packard Company, All Rights Reserved.  RESTRICTED
RIGHTS LEGEND Use, duplication, or disclosure by the U.S. Government is
subject to restrictions as set forth in sub-paragraph (c)(1)(ii) of the
Rights in Technical Data and Computer Software clause in DFARS 252.227-7013.

			  Hewlett-Packard Company
			    3000 Hanover Street
			 Palo Alto, CA 94304 U.S.A.
Rights for non-DOD U.S. Government Departments and Agencies are as set forth
			 in FAR 52.227-19(c)(1,2).
 * @endverbatim
 */

#ifndef	_COMCFG_H
#define	_COMCFG_H


#include <ainCommon.h>
#ifdef COCA_WIN32
#include <windows.h>
#endif /* COCA_WIN32 */

#define COM_C_MAXLEN_PATHNAME		127
#define COM_C_MAXLEN_VALUE		127

/* ---------------------------------- */
/* unbundeled form HP-AIN/cfgCommon.h */

#define CFGCOM_C_MAXLEN_KEYNAME 	32
#define CFGCOM_D_CLASS_PATHS      	"Paths"
#define CFGCOM_D_KEY_CONFIG         	"config"
#define CFGCOM_D_KEY_BINS           	"bins"
#define CFGCOM_D_KEY_MISC           	"misc"
#define CFGCOM_D_KEY_LOGS           	"logs"
#define CFGCOM_D_KEY_TTL            	"ttl"
#define CFGCOM_D_KEY_TMP            	"tmp"

/*
 * CFGCOM_D_MAX_HOSTS -- maximum number of hosts in a single opencall cluster.
 * this value is used by the MsgLib internal buffers allocation, but not by
 * 'comCfg'.
 */
#define CFGCOM_D_MAX_HOSTS		32


#define CFGCOM_D_CLASS_FTC		"FT_Controller"

/* Common key names */
/* System ids */
#define CFGCOM_D_KEY_SYSTEMID		"SystemId_"
#define CFGCOM_D_KEY_PLATFORMID		"PlatformId"

/* Addressing info for all HA services */
#define CFGCOM_D_KEY_HOST_ADDRESS	"Host_Address_"
#define CFGCOM_D_KEY_HOST_ADDRESS_ALL	"Host_Address_*"
#define CFGCOM_D_KEY_FT_PORT   		"FTPortName"
#define CFGCOM_D_KEY_FT2_PORT		"FT2PortName"

/* MIB Addressing for all MIB API processes */
#define CFGCOM_D_KEY_MIB_PORT		"MibPortName"
#define CFGCOM_D_KEY_MIB_AGT_PORT	"AgentPortName"

/* Type db/MibSchemaDB */
#define CFGCOM_D_KEY_TYPEDB_DIR	        "TypeDB_Directory"
#define CFGCOM_D_CLASS_SYSTEM		"System_Configuration"

#define CFGCOM_D_CLASS_MIB_AGENT	"Mib_Agent"
#define CFGCOM_D_CLASS_TYPEDB	        "Type_DB"

#ifdef __cplusplus
extern "C" {
#endif

    /* Structure used by helper function to parse config file info for ha service addressing */
#define MAX_SERVICEINFO_HOSTS   2 	/* Move to .h when we need more than 2 */
typedef struct {
  int nHosts;         /* number of host found */
  int myHost;         /* index of myHost in the array */
  char *hosts[MAX_SERVICEINFO_HOSTS];     /* list of host found */
  char *services[MAX_SERVICEINFO_HOSTS];  /* list of service found (linked to list of host) */
  char *hb_service;   /* legacy service port */
  char *mib_service;  /* legacy mib_service port */ 
    
} COM_T_service_info;
    

    /* Saturn FDR type */
typedef struct {
  int nHosts;                                  /* number of host found */
  int myHost;                                  /* index of myHost in the array */
  int peerHost;                                /* index of the peer host in  the array */
  char hosts[MAX_SERVICEINFO_HOSTS][MAXLEN_HOSTNAME];              /* list of host found */
  char services[MAX_SERVICEINFO_HOSTS][MAXLEN_SERVICENAME];        /* SO server service */
  char SOSO_services[MAX_SERVICEINFO_HOSTS][MAXLEN_SERVICENAME];   /* SO-SO service for subftc */
  char hb_services[MAX_SERVICEINFO_HOSTS][MAXLEN_SERVICENAME];     /* ftc-ftc hb service */
  char mib_services[MAX_SERVICEINFO_HOSTS][MAXLEN_SERVICENAME];    /* mib server service */
  int systemIds[MAX_SERVICEINFO_HOSTS];                            /* system id */
} COM_T_xservice_info;

/**
 * @fn COM_gethostname
 * @brief HP-UX gethostname(3) wrapper
 * 
 * Pick the NQDN of the surrent system (Non Qualified Domain Name), as HP-UX
 * does.
 * 
 * @see gethostname(3)
 */
extern int	COM_gethostname( char* /*host*/ , const size_t /*len*/ );

/**
 * @fn COM_getfqdn
 * @brief UNIX gethostname(3) wrapper
 * 
 * Pick the FQDN of the surrent system (Non Qualified Domain Name), as every
 * UNIX system (but HP-UX) do.
 * 
 * @see gethostname(3)
 */
extern int	COM_getfqdn( char* /*host*/ , const size_t /*len*/ );
extern char *COM_get_my_thread_hostent(char *,int);

extern COM_T_service_info *COM_get_service_info(int cfg_id, const char *classname);
int COM_xget_service_info(COM_T_xservice_info *si, int cfg_id, const char *classname); 
extern int COM_get_system_id(void);
extern int COM_get_system_id_host(char *host);
extern int COM_get_platform_id(void);
extern char * COM_get_mib_port_name(char *classname);
extern char * COM_xget_mib_port_name(int P_sysId, char *classname) ; 
extern char *COM_get_filepath(int cfgId, char *classname, char *key);
extern char *COM_get_TB_dir(void);
extern char *COM_find_right_mib_service(int systemId, char *entityClassName);
extern char *COM_whichPathFor( char *P_keyName );
extern int	COM_get_hosts (char *hosts[], int n_hosts);

#define COM_XGET_MAXVALUES 10

#ifdef _USE_RESOURCE_LOCATOR
	/* NCA: CutValues has been moved to ConfigLib */
	#define COM_CutValues(a) CFG_CutValues(a);
	extern int CFG_CutValues(char value[][COM_C_MAXLEN_VALUE], const char*, const int);
#else
	extern char *CFG_get_hpain_root(void);
	int CFG_CutValues(char value[][COM_C_MAXLEN_VALUE], const char*, const int);
#endif /* _USE_RESOURCE_LOCATOR */

#ifdef COCA_WIN32
/* Library entry point */
extern BOOL libComCfg_DllMain (HANDLE hInst, 
                            ULONG ul_reason_for_call,
                            LPVOID lpReserved);
#endif


#ifdef __cplusplus
}   /* extern "C" */
#endif


#endif /* COMCFG_H */
