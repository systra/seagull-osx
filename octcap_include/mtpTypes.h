/***********************************************************
*
* 
*
* $Source: /7UP/code/level3/mtpTypes.h $
* $Revision: 6.1 $
* 
* 
***********************************************************/

#ifndef MTPL3_API_H
#define MTPL3_API_H

/*------------------
  SIO decomposition
 ------------------*/
typedef struct
{
	unsigned int SI: 4;           /* Service indicator */
	unsigned int msg_priority: 2; /* spare for ITU-T, msg priority for ANSI */
	unsigned int NI: 2;           /* Network Indicator */

} sio_struct;

/*-----------------------------------------------
  Destination definition for Bellcore addresses
 ----------------------------------------------- */
typedef struct
{
	unsigned char spare: 6;

	/* Flags added for CLUSTER_ROUTING */
	unsigned char networkFlag: 1;  /* meaningless for ITU-T, so spare always set to 0 */
	unsigned char clusterFlag: 1;  /* meaningless for ITU-T, so spare always set to 0 */

	unsigned char netwk_id;
	unsigned char netwk_mb;
	unsigned char cluster_mb;

} dpc_struct;

/*---------------------------------
 Causes for mtp status indication
 ---------------------------------*/

typedef enum
{
	dpc_congested,
	dpc_uncongested,
	mtp_available,
	mtp_unavailable,
	mtp_congested,
	mtp_uncongested,
	mtp_restarting,
	upu_unavailable,
	mtp_cnx_error,
   mtp_router_updated

} mtp_status_cause;

/*---------------------------------
  Structure for mtp status, used as data
  --------------------------------*/

typedef struct
{
  mtp_status_cause  cause;
  union
  {
    int               congLevel; /* Significant only for DPC_STATUS(congested) */
    int               UPUcause;  /* Significant only for DPC_STATUS(upu)       */
  }                 intVal;
} mtp_status_parms;

/*------------------
  Types of primitive
 ------------------*/

typedef enum
{
	mtp_transfer_req,
	mtp_transfer_ind,
	mtp_status_ind,
	mtp_resume_ind,
	mtp_pause_ind,
   /* MV - primitive to acknowledge DataStore action completion  */
   mtp_updateRouter_ind
} mtp_primit;


/* Functions prototypes */

#ifdef __cplusplus
extern "C" {
#endif
   
int MTPL3_recv (
	int             cnxId,
	struct timeval *time,
	int            *opc,
	int            *dpc,
	int            *sls,
	unsigned char  *sio,
	mtp_primit     *primitive,
	int            *datalen,
	char           *data);

int MTPL3_send (
	int             cnxId,
	struct timeval *time,
	int             opc,
	int             dpc,
	int             sls,
	unsigned char   sio,
	int             priority,
	mtp_primit      primitive,
	int             datalen,
	char           *data);

#ifdef __cplusplus
}
#endif

#endif /* MTPL3_API_H */
 
