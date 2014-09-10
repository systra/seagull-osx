/***********************************************************
*
* 
*
* $Source: /7UP/code/level3/mtpDefs.h $
* $Revision: 5.7 $
* 
* 
***********************************************************/

#ifndef MTPL3_DEFS_INCLUDED
#define MTPL3_DEFS_INCLUDED

/* Mtp user parts					*/
/* defines all the supported user parts */

/* --------
	CHANGE THIS FILE WITH CAUTION: ALL CHANGES MADE HERE SHOULD BE 
	REPORTED IN SS7_IF.H WHICH IS THE API INTERFACE DEFINITION FILE 
	-------- */

typedef enum
{
	SCCP_USER    = 3,
	ISUP_USER    = 5,
	TUP_USER     = 4,
	DATA_USER1   = 6,
	DATA_USER2   = 7,
	MTPT_USER    = 8,
	USER_SPARE2  = 2,
	USER_SPARE9  = 9,
	USER_SPARE10 = 10,
	USER_SPARE11 = 11,
	USER_SPARE12 = 12,
	USER_SPARE13 = 13,
	USER_SPARE14 = 14,
	USER_SPARE15 = 15
} UserPart;


/* enum for MTP_STATUS primitives			*/

typedef enum
{
	/*------ Remote Node status change ------*/
	DpcAvailable,
	DpcUnavailable, 
	DpcCongested, 
	DpcUncongested,
	/*------ Local MTP availability status ------*/
	MtpAvailable,      /* Mtp Normal state */
	MtpUnavailable,    /* Mtp has been shutdown */
	MtpCongested,      /* Temporary difficulties to process Msus */
	MtpUncongested,    /* Back to normal state */
	MtpRestarting,     /* Mtp underging restart procedure */
	UpuUnavailable,    /* Remote User Part Unavailable */
	/*------ New types added for CLUSTER_ROUTING -------*/
	/*------ Remote Cluster/Network status change ------*/
	ClusterAvailable,
	ClusterUnavailable,
	ClusterCongested,
	ClusterUncongested,
	NetworkAvailable,
	NetworkUnavailable,
	NetworkCongested,
	NetworkUncongested,
   /* MV - Mtp Router, for distributed isup, acknowledgement */
   MtpRouterUpdated
} MtpStatus;

/* Definition of all MTP standards supported by HP OC SS7 platform */

typedef enum
{
	UNDEFINED_STANDARD = 0x00,        /* Unitialized value */
	ITU_BLUE           = 0x01,        /* ITU-T Blue Book */
	ITU_WHITE          = 0x02,        /* ITU-T White Book */
	ITU_CHINA          = 0x03,        /* Chinese MTP variant of ITU-T */
	TTC                = 0x04,        /* Japanese TTC (based on ITU-T) */
	NTT                = 0x05,        /* Japanese NTT (based on ITU-T) */
	ANSI_88            = 0x11,        /* ANSI 88 */
	ANSI_91            = 0x12,        /* ANSI 91 (Not used yet) */
	ANSI_96            = 0x13         /* ANSI 96 (Only MTP restart so far) */   
} MtpStandard;


/* enum for MTP primitives */
typedef enum
{
	MtpTransferReq,
	MtpTransferInd,
	MtpStatusInd
}  mtp_primitive;


// Parameters for MTP_TRANSFER_INDICATIONS and MTP_STATUS
// when issuing an indication to an user the MTP interface calls the user method
// with 2 parameters:
// 1- a parameter of type INDICATION telling whether it is a MTP_STATUS or
// a MTP_TRANSFER_INDICATION.
// 2- a parameter of type MtpIndicationParms * giving relevant information
// associated with that indication

typedef struct
{
	int         DPC;
	int         OPC;       // significant only for MTP_TRANSFER_INDICATION
	int         NI;        // significant only for MTP_TRANSFER_INDICATION
	int         SI;        // significant only for MTP_TRANSFER_INDICATION
	int         SLS;       // significant only for MTP_TRANSFER_INDICATION
	Buffer    * data;      // significant only for MTP_TRANSFER_INDICATION
	MtpStatus   DPCStatus; // significant only for MTP_STATUS
#ifdef ANSI88 
	int	    congLevel; // Significant only for DPC_STATUS(congested)
#endif
	int         UPUcause;  // Significant only for DPC_STATUS(upu)
} MtpIndicationParms;

#endif /* MTPL3_DEFS_INCLUDED */
