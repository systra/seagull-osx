/*=====================================================================
|            
|                L2OamDefs.h
|                               -----------
|
| Type definitions for the level 2 Oam interface
|
| $Source: /7UP/code/level2_sft/L2OamDefs.h $
| $Revision: 4.0 $
| $Date: 1997/12/19 08:23:40 $
| HEWLETT PACKARD SS7
| (c) Copyright 1993, Hewlett-Packard Company, all rights reserved
|
=====================================================================*/

#ifndef MTPL2_OAM_API_H 
#define MTPL2_OAM_API_H

/* Oam commands that may be sent to the interface */

typedef enum {
             get_status,      /* get status of a siu box            */
             test,            /* test acces to a siu box            */
             reload           /* reserved : reload a siu box after a power off */

             }L2OamCmd ;    

/* Structure for Oam command parameters............................ */

typedef struct {
        
               int    Reserved;/* Reserved for future use           */

               }L2OamCmdParms;


/* Oam Object types................................................ */

typedef enum {

             siuObject       /* Siu box number                      */

             }L2OamObject ;    

/* Oam State types................................................. */

typedef enum {

             l2nonConfigured,/* Non existing siu                    */
             l2active,       /* active state                        */
             l2outOfSce,     /* Power down or SCSI bus problem      */
             l2standby,      /* Standby state                       */
             l2standbyOutOfSce/* Out-of-service and standby          */

             }L2OamState ;    

/* Oam Object address definition................................... */

#define L2MAXADDRLEVEL   1
#define MAXSIUS		16

/* Object address identification: -                
       (address identifying object is kept in an array {eg addr[]}
        as follows)

        object type        addr[0]
        -------------------------------
        siu                     Siu number
*/
typedef int L2OamAddress[L2MAXADDRLEVEL] ;

/* Oam Failure types..........................................
   Used for notifying failure due to operations or events via 
   OAM interface 
*/
typedef enum {

             L2_EXECUTED = 0,      /* no failure: command executed  */
             L2_ILLEGAL_OPERATION, /* impossible command            */
             L2_OBJECT_NOT_FOUND   /* no such object with specified
                                                    siu number      */

             }L2OamFailure;

/* Oam type for notification....................................... */

typedef enum {

             l2_object_state,        /* Object state                */
             l2_error                /* error during a command      */

             }L2OamNotifType ;    

/* Oam parameter for notification.................................. */

typedef union
        {

         L2OamState   state;      /* contains state of object       */
         L2OamFailure failure_cause;/* cause of failure for error
                                                      report notif  */

        }L2OamNotifParms ;    


/* Functions prototypes ........................................... */

#ifdef __cplusplus
extern "C" {
#endif
   
int MTPL2_oamcmd (int		 	cnxId,
		  struct timeval	*time,
		  void 			*context,
		  L2OamObject		object,
		  L2OamAddress		address,
		  L2OamCmd		command,
		  L2OamCmdParms		*cmdParms);


int MTPL2_oamrecv (int		 	cnxId,
		   struct timeval	*time,
		   void 		**context,
		   L2OamObject		*object,
		   L2OamAddress		address,
		   L2OamNotifType	*notif,
		   L2OamNotifParms	*notifstruct);

#ifdef __cplusplus
}
#endif

#endif
/*********************** DEFINITIONS END ****************************/
