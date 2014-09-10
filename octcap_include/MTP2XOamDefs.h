/*=====================================================================
|            
|                		MTP2XOamDefs.h
|                               --------------
|
| Type definitions for the extended level 2 Oam interface
|
| $Source: /7UP/code/level2_sft/MTP2XOamDefs.h $
| $Revision: 5.2 $
| $Date: 1998/11/25 17:17:58 $
| HEWLETT PACKARD SS7
| (c) Copyright 1993, Hewlett-Packard Company, all rights reserved
|
=====================================================================*/

#ifndef MTP2X_OAM_API_H 
#define MTP2X_OAM_API_H

#ifdef __linux__

#ifndef MAX_TSCS
#define MAX_TSCS	8
#endif

#else

#ifndef MAX_TSCS
#define MAX_TSCS	256
#endif

#endif //__linux__

#ifdef __linux__

#ifndef MAX_TSUS
#define MAX_TSUS	8
#endif

#else

#ifndef MAX_TSUS
#define MAX_TSUS	32
#endif

#endif //__linux__

#ifndef MAX_TSU_SLOTS
#define MAX_TSU_SLOTS 5
#endif

#ifndef MAX_TSU_FANS
#define MAX_TSU_FANS	6
#endif

#ifndef MAX_TSU_DCS
#define MAX_TSU_DCS	2
#endif

/* Oam commands that may be sent to the interface - the new command
   wrt the L2Oam implementation is get_active_hostname. */

typedef enum {
   MTP2X_get_status,          /* get status of a siu object         */
   MTP2X_get_sillib_status,   /* get status of a siu box            */
   MTP2X_test,                /* test acces to a siu box            */
   MTP2X_reload,              /* reserved : reload a siu box after a power off */
   MTP2X_get_active_hostname, /* get the active hostname */
	MTP2X_tsu_status,				/* get status of a TSU */
	MTP2X_tsc_status,				/* get status of a TSC */
	MTP2X_tscs_status,			/* get the status of all TSCs configured */
   MTP2X_tsus_status,			/* get the status of all TSUs configured */
   MTP2X_get_hw_type          /* get the hardware type */
} MTP2XOamCmd ;    


/* Oam type for notification....................................... */

typedef enum {
   MTP2X_siu_state,        /* SIU state, as seen by the SIU stack entity */
   MTP2X_sillib_state,     /* SIU sillib state, as seen by the Subsys entity */
   MTP2X_active_hostname,  /* Stack active hostname  */	 
	MTP2X_tsu_state,			/* TSU state */
	MTP2X_tsc_state,			/* TSC state */
	MTP2X_tscs_states,		/* TSCs states */
   MTP2X_tsus_states,		/* TSUs states */
   MTP2X_error,            /* Error during a command */
   MTP2X_hw_type           /* Hardware type */
} MTP2XOamNotifType ;    


/* The new SIU sillib state, as seen by the L2Subsys stack entity - this is
   a type equivalent to the sillib internal type status_t - it is however
   preferable not to use this type, which would introduce dependencies on the
   sillib and SS7 driver implementations */

typedef enum {
  MTP2X_S_UNKNOWN,       /* siu not configured */
  MTP2X_S_OFFLINE,       /* siu offline, must be downloaded */
  MTP2X_S_ONLINE,        /* siu OK */
  MTP2X_S_ERROR,         /* siu in error state */
  MTP2X_S_NOTRESPONDING, /* siu not responding */
  MTP2X_S_TIMEOUTED,     /* siu heartbeat timeout expired */
  MTP2X_S_STANDBY,       /* siu in standby state */
  MTP2X_S_NONCONFIGURED  /* siu not configured in the ss7.config */
} MTP2Xsillibstate;

typedef enum {
	MTP2X_TSU_NOT_RESPONDING, 
	MTP2X_TSU_OUT_OF_SERVICE, 
	MTP2X_TSU_BROKEN,
   MTP2X_TSU_BOOTING, 
	MTP2X_TSU_FATALERR, 
	MTP2X_TSU_CONFIGURING, 
	MTP2X_TSU_ACTIVE,
	MTP2X_TSU_DEGRADED,
	MTP2X_TSU_NONCONFIGURED
} MTP2Xtsustate;

typedef enum {
	MTP2X_TSC_FAILED, 
	MTP2X_TSC_INITIALISING, 
	MTP2X_TSC_ACTIVE,
   MTP2X_TSC_DOWNLOADING, 
	MTP2X_TSC_DIAGNOSING, 
	MTP2X_TSC_UPLOADING,
   MTP2X_TSC_DISABLED,
	MTP2X_TSC_NONCONFIGURED
} MTP2Xtscstate;

typedef enum {
	MTP2X_FAN_FAIL,
	MTP2X_FAN_OK
} MTP2Xfanstate;

typedef enum {
	MTP2X_DC_FAIL,
	MTP2X_DC_OK
} MTP2Xdcstate;

typedef enum {
	MTP2X_SIU,
	MTP2X_TSC,     /* Tscs on host */
	MTP2X_TSU_TSC	/* Tscs on Tsu */
}MTP2Xhwtype;

/* Oam parameter for notification.................................. */
typedef struct {
	int tscId;		
	MTP2Xtscstate state;
} MTP2XOamTscInTsuInfo;

typedef struct {
	int tsuId;
	MTP2Xtscstate state;
}MTP2XOamTscInfo;

typedef enum {
   MTP2X_get_req,            /* response to a get_tsu_state */
   MTP2X_tsu_state_change,   /* a TSU state change */
   MTP2X_fan_state_change,   /* a fan state change */
   MTP2X_dc_state_change,    /* a dc state change */
   MTP2X_double_fan_failure  /* double fan failure */
} MTP2Xreason;

typedef struct {
   MTP2Xreason					notif_reason;
	MTP2Xtsustate     	  	state;
	MTP2XOamTscInTsuInfo   	tscs[MAX_TSU_SLOTS];
	MTP2Xfanstate           fans_state[MAX_TSU_FANS];
	MTP2Xdcstate            DCs_state[MAX_TSU_DCS];
} MTP2XOamTsuInfo;

typedef union {
	L2OamState       	siu_state;		/* stack SIU status  */
	MTP2Xsillibstate 	sillib_state;	/* sillib SIU status */
	MTP2XOamTsuInfo	tsu_info;		/* TSU status */
	MTP2XOamTscInfo	tsc_info;		/* TSC status and the corresponding tsuId*/
	MTP2Xtscstate		tsc_list[MAX_TSCS];	/* list of all tscs states */
	MTP2XOamTsuInfo	tsu_list[MAX_TSUS];	/* list of all tsus states */
	/* The hostname of the active stack */
	char 					active_hostname[MAXLEN_HOSTNAME]; 
	L2OamFailure      failure_cause; /* cause of failure for error report notif  */
	MTP2Xhwtype       hw_type;       /* hardware type */
} MTP2XOamNotifParms;    


/* Functions prototypes ........................................... */

#ifdef __cplusplus
extern "C" {
#endif
   
int MTP2X_oamcmd (int		 	cnxId,
		  struct timeval	*time,
		  void 			*context,
		  MTP2XOamCmd		command,
		  L2OamAddress		address);


int MTP2X_oamrecv (int			cnxId,
		   struct timeval	*time,
		   void 		**context,
		   L2OamAddress	        address,
		   MTP2XOamNotifType	*notif,
		   MTP2XOamNotifParms	*notifstruct);

#ifdef __cplusplus
}
#endif

#endif
/*********************** DEFINITIONS END ****************************/
