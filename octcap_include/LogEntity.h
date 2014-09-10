/***********************************************************
*
* $Header: /GANGA/Supportability/CSUPP/code/OC_FA_LogId/LogEntity.h 1.7 2003-11-18 14:49:46+05:30 sudhav Exp $
*
* $Source: /GANGA/Supportability/CSUPP/code/OC_FA_LogId/LogEntity.h $
* $Revision: 1.7 $
* $Locker:  $
* 
***********************************************************/
#ifndef LOGENTITYFMT
#define LOGENTITYFMT
 



/* catalog message id definitions                                       */
/*                                                                      */
/*      WARNING !!!!!!!                                                 */
/*                                                                      */
/*      findmsg(1) must be used to generate the formatter.msg file      */
/*      automatically                                                   */
/*                                                                      */
/*      The following syntax is mandatory:                              */
/*              " message string in catalog "    catgets n              */              
/*             where n will be the msg ID in the catalog                */
/*                                                                      */
/*      findmsg subsys_TTL_fmt.h > formatter.msg                        */

#undef NL_SETN
#define NL_SETN 4       /* TTL_GENERIC_LOGENTITY special for findmsg(1) to find the catalog set number */
/*  ------ define ---------------id in catalog-------message in catalog -----------------------------------tag to find the ID---*/

/* Never ever change the value of the following id. */ 
#ifndef TTL_GENERIC_LOGENTITY
#define TTL_GENERIC_LOGENTITY           1       /* Reserved  for TTL*/
#endif
#ifndef TTL_FA_ID
#define TTL_FA_ID                       2
#endif
#ifndef TTL_TRACE_KIND
#define TTL_TRACE_KIND                  3  
#endif  
#ifndef TTL_FORMATTER_MSGSET_ID
#define TTL_FORMATTER_MSGSET_ID         4
#endif  



/*  ------ define ---------------id in catalog-------message in catalog -----------------------------------tag to find the ID---*/

#define FT_LOGENTITY                    20      /* "FT_LOGENTITY"                                         catgets 20 */  
#define EH_LOGENTITY                    21      /* "EH_LOGENTITY"                                         catgets 21 */  
#define MIB_LOGENTITY                   22      /* "MIB_LOGENTITY"                                        catgets 22 */  
#define SS7_LOGENTITY                   23      /* "SS7_LOGENTITY"                                        catgets 23 */  
#define UTIL_LOGENTITY                  24      /* "UTIL_LOGENTITY"                                       catgets 24 */  
#define DDL_LOGENTITY                   25      /* "DDL_LOGENTITY"                                        catgets 25 */  
#define SMS_LOGENTITY                   26      /* "SMS_LOGENTITY"                                        catgets 26 */  
#define SCE_LOGENTITY                   27      /* "SCE_LOGENTITY"                                        catgets 27 */  
#define MB_LOGENTITY                    28      /* "MB_LOGENTITY"                                         catgets 28 */  
#define PPP_LOGENTITY                   29      /* "PPP_LOGENTITY"                                        catgets 29 */ 
#define BF_LOGENTITY                    30      /* "BF_LOGENTITY"                                         catgets 30 */
#ifndef ISUP_LOGENTITY          /* conflict with TUP_LOGENTITY
                                   (see IsupInternCommon.h) */
#define ISUP_LOGENTITY                  31      /* "ISUP_LOGENTITY"                                       catgets 31 */
#endif /* !ISUP_LOGENTITY */
#define NAL_LOGENTITY                   32      /* "NAL_LOGENTITY"                                        catgets 32 */
#define SIL_LOGENTITY                   33      /* "SIL_LOGENTITY"                                        catgets 33 */
#define DSS_LOGENTITY                   34      /* "DDS_LOGENTITY"                                        catgets 34 */
#define MSGLIB_LOGENTITY                35      /* "MSGLIB_LOGENTITY"                                     catgets 35 */
#define MSGLIB_CONFIG_LOGENTITY         36      /* "MSGLIB_CONFIG_LOGENTITY"                              catgets 36 */
#define TUP_LOGENTITY                   37      /* "TUP_LOGENTITY"                                        catgets 37 */
#define SUAAS_LOGENTITY                 38      /* "SUAAS_LOGENTITY"                                      catgets 38 */
#define OCMP_MGT_SERVER_LOGENTITY       39      /* "OCMP_MGT_SERVER_LOGENTITY                             catgets 39 */


#define SLEE_TCAP_IF_LOGENTITY          50      /* "SLEE_TCAP_IF_LOGENTITY"                       catgets 50 */  
#define SLEE_external_channel_LOGENTITY 51      /* "SLEE_external_channel_LOGENTITY"              catgets 51 */  
#define SLEE_call_context_LOGENTITY     52      /* "SLEE_call_context_LOGENTITY"                  catgets 52 */  
#define SLEE_interpreter_LOGENTITY      53      /* "SLEE_interpreter_LOGENTITY"                   catgets 53 */  
#define SLEE_handler_LOGENTITY          54      /* "SLEE_handler_LOGENTITY"                       catgets 54 */  
#define SLEE_MsgSet_LOGENTITY           55      /* "SLEE_MsgSet_LOGENTITY"                        catgets 55 */  
#define SLEE_SMS_API_LOGENTITY          56      /* "SLEE_SMS_API_LOGENTITY"                       catgets 56 */  
#define SLEE_scheduler_LOGENTITY        57      /* "SLEE_scheduler_LOGENTITY"                     catgets 57 */  
#define SLEE_MIB_handler_LOGENTITY      58      /* "SLEE_MIB_handler_LOGENTITY"                 catgets 58 */  
#define SLEE_Standby_handler_LOGENTITY  59      /* "SLEE_Standby_handler_LOGENTITY"             catgets 59 */  

#define SLEE_animator_LOGENTITY         60      /* "SLEE_animator_LOGENTITY"                    catgets 60 */  
#define SLEE_DB_LOGENTITY               61      /* "SLEE_DB_LOGENTITY"                          catgets 61 */  
#define SLEE_AsnNokia_LOGENTITY         62      /* "SLEE_AsnNokia_LOGENTITY"                    catgets 62 */  
#define SLEE_AsnFujitsu_LOGENTITY       63      /* "SLEE_AsnFujitsu_LOGENTITY"                  catgets 63 */  
#define SLEE_EventMgr_LOGENTITY         64      /* "SLEE_EventMgr_LOGENTITY"                    catgets 64 */
#define SLEE_SCE_tracing_LOGENTITY      65      /* "SLEE_SCE_tracing_LOGENTITY"                 catgets 65 */
#define SLEE_SmsHandler_LOGENTITY       66      /* "SLEE_SmsHandler_LOGENTITY"                  catgets 66 */
#define SLEE_Bulkop_LOGENTITY           67      /* "SLEE_Bulkop_LOGENTITY"                      catgets 67 */  
#define SLEE_DataBaseMib_LOGENTITY      68      /* "SLEE_DataBaseMib_LOGENTITY"                 catgets 68 */  
#define SLEE_MIBSYNC_LOGENTITY          69      /* "SLEE_MIBSYNC_LOGENTITY"                     catgets 69 */

#define Licensing_LOGENTITY             70      /* "Licensing_LOGENTITY"                        catgets 70 */
#define SQLACCESS_LOGENTITY             71      /* "SQLACCESS_LOGENTITY"                        catgets 71 */

/* for new licensing fwk (f.pagani) */
#define LICENSING_FWK_LOGENTITY         73      /* "LICENSING_FWK_LOGENTITY"                    catgets 73 */

#define PINS_LOGENTITY                  79      /* "PINS_LOGENTITY"                             catgets 79 */

#define evtHandler_LOGENTITY            80      /* "evtHandler_LOGENTITY"                         catgets 80 */  
#define diskLogger_LOGENTITY            81      /* "diskLogger_LOGENTITY"                         catgets 81 */ 
#define alarmHandler_LOGENTITY          82      /* "alarmHandler_LOGENTITY"                       catgets 82 */ 
#define printLogger_LOGENTITY           83      /* "printLogger_LOGENTITY"                        catgets 83 */ 
#define FTController_LOGENTITY          84      /* "FTController_LOGENTITY"                       catgets 84 */ 
#define ss7StackWatcher_LOGENTITY       85      /* "ss7StackWatcher_LOGENTITY"                    catgets 85 */ 
#define resourceWatcher_LOGENTITY       86      /* "resourceWatcher_LOGENTITY"                    catgets 86 */ 
#define OCResourceFmk_LOGENTITY         87      /* "OCResourceFmk_LOGENTITY"                      catgets 87 */ 


#define HPSS7_LOGENTITY                 90      /* "HPSS7_LOGENTITY"                              catgets 90 */ 
#define SS7OAMTOOL_LOGENTITY            91      /* "SS7OAMTOOL_LOGENTITY"                         catgets 91 */
#define ss7Switcher_LOGENTITY           95      /* "ss7Switcher_LOGENTITY"                        catgets 95 */ 
#define ss7Waiter_LOGENTITY             96      /* "ss7Waiter_LOGENTITY"                          catgets 96 */ 

#define modLog_LOGENTITY                100     /* "modLog_LOGENTITY"                             catgets 100 */
#define modPrint_LOGENTITY              101     /* "modPrint_LOGENTITY"                           catgets 101 */ 
#define modAlarm_LOGENTITY              102     /* "modAlarm_LOGENTITY"                           catgets 102 */ 
#define evtDisp_LOGENTITY               103     /* "evtDisp_LOGENTITY"                            catgets 103 */ 
#define FTMonitor_LOGENTITY             104     /* "FTMonitor_LOGENTITY"                          catgets 104 */ 
#define oamTool_LOGENTITY               105     /* "oamTool_LOGENTITY"                            catgets 105 */ 
#define HPRMON_LOGENTITY                106     /* "HPRMON_LOGENTITY"                             catgets 106 */ 
#define SS7DIAG_LOGENTITY               107     /* "SS7DIAG_LOGENTITY"                            catgets 107 */
#define SNMPAGENT_LOGENTITY             108     /* "SNMPAGENT_LOGENTITY"                          catgets 108 */

#define MIB_AGENT_LOGENTITY             110     /* "MIB_AGENT_LOGENTITY"                          catgets 110 */
#define SG_OC_LOGENTITY                 111     /* "SG_OC_LOGENTITY"                              catgets 111 */
#define MIBREP_LOGENTITY                112     /* "MIBREP_LOGENTITY"                             catgets 112 */
#define TCAP_SNMP_AGENT_LOGENTITY       113     /* "TCAP_SNMP_AGENT_LOGENTITY"                    catgets 113 */
#define SS7View_LOGENTITY               120     /* "SS7View_LOGENTITY"                            catgets 120 */

#define oc_tsc_bridge_LOGENTITY         130     /* "oc_tsc_bridge_LOGENTITY"                      catgets 130 HR */


#define Ed_C_DebugLogEntity             140     /* "Ed_C_DebugLogEntity"                          catgets 140 */
#define Ed_C_GraphicsLogEntity          141     /* "Ed_C_GraphicsLogEntity"                       catgets 141 */
#define Ed_C_PrintLogEntity             142     /* "Ed_C_PrintLogEntity"                          catgets 142 */
#define Ed_C_ReaderLogEntity            143     /* "Ed_C_ReaderLogEntity"                         catgets 143 */
#define Ed_C_TranslateLogEntity         144     /* "Ed_C_TranslateLogEntity"                      catgets 144 */
#define Ed_C_MainLogEntity              145     /* "Ed_C_MainLogEntity"                           catgets 145 */

#define SMS_C_DB_MrgLogEntity           150     /* "SMS_C_DB_MrgLogEntity"                        catgets 150 */
#define SMS_C_MainLogEntity             151     /* "SMS_C_MainLogEntity"                          catgets 151 */
#define SMS_C_DM_LogEntity              152     /* "SMS_C_DM_LogEntity"                           catgets 152 */
#define SMS_C_FM_LogEntity              153     /* "SMS_C_FM_LogEntity"                           catgets 153 */
#define SMS_C_SwitchM_LogEntity         154     /* "SMS_C_SwitchM_LogEntity"                      catgets 154 */
#define SMS_C_LogBrowserLogEntity       155     /* "SMS_C_LogBrowserLogEntity"                    catgets 155 */
#define SMS_C_RunExeLogEntity           156     /* "SMS_C_RunExeLogEntity"                        catgets 156 */

#define DDL_C_CompilerLogEntity         160     /* "DDL_C_CompilerLogEntity"                      catgets 160 */
#define DDL_C_API_LogEntity             161     /* "DDL_C_API_LogEntity"                          catgets 161 */

#define SEL_C_CompilerLogEntity         170     /* "SEL_C_CompilerLogEntity"                      catgets 170 */
#define SIM_C_TelLogEntity              180     /* "SIM_C_TelLogEntity"                           catgets 180 */
#define SIM_C_TelsimLogEntity           181     /* "SIM_C_TelsimLogEntity"                        catgets 181 */
#define SIM_C_SwitchLogEntity           182     /* "SIM_C_SwitchLogEntity"                        catgets 182 */

#define OCMP_PLATFORM_LOGENTITY         200     /* "OCMP_PLATFORM_LOGENTITY"                      catgets 200 */
#define OCMP_SERVICE_LOGENTITY          201     /* "OCMP_SERVICE_LOGENTITY"                       catgets 201 */
#define OCMP_SIGNALING_LOGENTITY        202     /* "OCMP_SIGNALING_LOGENTITY"                     catgets 202 */
#define OCMP_TRANSPORT_LOGENTITY        203     /* "OCMP_TRANSPORT_LOGENTITY"                     catgets 203 */
#define OCMP_CONFIG_LOGENTITY           204     /* "OCMP_CONFIG_LOGENTITY"                        catgets 204 */
#define OCMP_HW_LOGENTITY               205     /* "OCMP_HW_LOGENTITY"                            catgets 205 */
#define OCMP_STREAMER_LOGENTITY         206     /*"OCMP_STREAMER_LOGENTITY"                       catgets 206*/
#define OCMP_VXML_LOGENTITY             207     /*"OCMP_VXML_LOGENTITY"                           catgets 207*/

#define IPCENTREX_LOGENTITY             210     /* "IPCENTREX_LOGENTITY"                          catgets 210 */
#define IP_CENTREX_LOGENTITY            211     /* "IP_CENTREX_LOGENTITY"                         catgets 211 */

#define H323SG_LOGENTITY                250     /* "H323SG_LOGENTITY"                             catgets 250 */
#define MSPA_LOGENTITY                  251     /* "MPSA_LOGENTITY"                               catgets 251 */
#define H323GK_LOGENTITY                252     /* "H323GK_LOGENTITY"                             catgets 252 */

#define CCS_PROXY_LOGENTITY             260     /* "CCS_PROXY_LOGENTITY"                          catgets 260 */ 

#define REP_MGR_LOGENTITY               270     /* "REP_MGR_LOGENTITY"                            catgets 270 */
#define TCP_CNX_MGR_LOGENTITY           271     /* "TCP_CNX_MGR_LOGENTITY"                        catgets 271 */

#define EVENT2_TRAP_EXT_LOGENTITY       280     /* "EVENT2_TRAP_EXT_LOGENTITY"                   catgets 280 */

#define ECI_SIG_ISUP_PI_LOGENTITY       300     /* "ECI_SIG_ISUP_PI_LOGENTITY"                    catgets 300 */
#define ECI_SIG_ISDN_Stack_LOGENTITY    301     /* "ECI_SIG_ISDN_Stack_LOGENTITY"                 catgets 301 */
#define ECI_SIG_TDAX_PI_LOGENTITY       302     /* "ECI_SIG_TDAX_PI_LOGENTITY"                    catgets 302 */
#define ECI_SIG_OAM_LOGENTITY           303     /* "ECI_SIG_OAM_LOGENTITY"                        catgets 303 */
#define ECI_SIG_GEN_PI_LOGENTITY        304     /* "ECI_SIG_GEN_PI_LOGENTITY"                     catgets 304 */


/**** Helene  Log Entities ****/

#define TDI_LOGENTITY                   305     /* "TDI_LOGENTITY"                                catgets 305 */


/**** Helene  Log Entities ****/

#define MAP_API_LOGENTITY               310     /* "MAP_API_LOGENTITY"                            catgets 310 */


/**** SIP Log Entities ****/

#define SIPNETWORK_LOGENTITY            320     /* "SIPNETWORK_LOGENTITY"                         catgets 320 */
#define SIPSERVICE_LOGENTITY            321     /* "SIPSERVICE_LOGENTITY"                         catgets 321 */
#define SIPPLUGIN_LOGENTITY             322     /* "SIPPLUGIN_LOGENTITY"                          catgets 322 */


/**** Calypso Log Entities ****/

#define HP_M3UA_LOGENTITY               401     /* "HP_M3UA_LOGENTITY"                            catgets 401 */
#define M3UA_PROTOCOL_LOGENTITY         402     /* "M3UA_PROTOCOL_LOGENTITY"                      catgets 402 */
#define M3UA_OAM_LOGENTITY              403     /* "M3UA_OAM_LOGENTITY"                           catgets 403 */
#define LICENSING_MGR_LOGENTITY         404     /* "LICENSING_MGR_LOGENTITY"                      catgets 404 */
#define SCTP_API_LOGENTITY              405     /* "SCTP_API_LOGENTITY"                           catgets 405 */
#define M3UA_HA_MGR_LOGENTITY           406     /* "M3UA_HA_MGR_LOGENTITY"                        catgets 406 */
#define XML_NWK_CONFIG_LOGENTITY        407     /* "XML_NWK_CONFIG_LOGENTITY"                     catgets 407 */


/**** SMP Log Entity ****/

/* For SMP tests entity */
#define SMSTL_C_smptest_LOGENTITY       500     /* "SMSTL_C_smptest_LOGENTITY"                  catgets 500 */
/* SmsTL entity */
#define SMSTL_C_tl_LOGENTITY            501     /* "SMSTL_C_tl_LOGENTITY"                       catgets 501 */
/* Audit entity */
#define SMSTL_C_au_LOGENTITY            502     /* "SMSTL_C_au_LOGENTITY"                       catgets 502 */
/* Conv entity */
#define SMSTL_C_conv_LOGENTITY          503     /* "SMSTL_C_conv_LOGENTITY"                     catgets 503 */
/* Convdb entity */
#define SMSTL_C_db_LOGENTITY            504     /* "SMSTL_C_db_LOGENTITY"                       catgets 504 */
/* OraCx entity */
#define SMSTL_C_dbx_LOGENTITY           505     /* "SMSTL_C_dbx_LOGENTITY"                      catgets 505 */
/* DownPropAgent entity */
#define SMSTL_C_down_LOGENTITY          506     /* "SMSTL_C_down_LOGENTITY"                     catgets 506 */
/* NMcli entity */
#define SMSTL_C_nm_LOGENTITY            507     /* "SMSTL_C_nm_LOGENTITY"                       catgets 507 */
/* Delta entity */
#define SMSTL_C_sg_LOGENTITY            508     /* "SMSTL_C_sg_LOGENTITY"                       catgets 508 */
/* StatApplicator entity */
#define SMSTL_C_st_app_LOGENTITY        509     /* "SMSTL_C_st_app_LOGENTITY"                   catgets 509 */


/***********************************************************
**  Commented the below lines for Hyperion Merge
**
** 
** Up and Stat Regulators come from the same Module
** We use the same Id.
** Regulators entity (StatRegulator)
** Regulators entity (UpRegulator) 
**
** End Comment
************************************************************/

/* Up and Stat Regulators come from the same Module, but using the same Id
 * breaks the recent Linux gencat */
#define SMSTL_C_st_reg_LOGENTITY        510     /* "SMSTL_C_regulators_LOGENTITY"               catgets 510 */
#define SMSTL_C_up_reg_LOGENTITY        SMSTL_C_st_reg_LOGENTITY
/* Distributor entity */
#define SMSTL_C_up_dist_LOGENTITY       511     /* "SMSTL_C_up_dist_LOGENTITY"                  catgets 511 */
/* Applicator entity */
#define SMSTL_C_up_app_LOGENTITY        512     /* "SMSTL_C_up_app_LOGENTITY"                   catgets 512 */
/* Cli entity */
#define SMSTL_C_cli_LOGENTITY           513     /* "SMSTL_C_cli_LOGENTITY"                      catgets 513 */
/* DBPlim entity */
#define SMSTL_C_dbp_LOGENTITY           514     /* "SMSTL_C_dbp_LOGENTITY"                      catgets 514 */
/* ConvProp entity */
#define SMSTL_C_convprop_LOGENTITY      515     /* "SMSTL_C_convprop_LOGENTITY"                 catgets 515 */
/* License entity */
#define SMSTL_C_li_LOGENTITY            516     /* "SMSTL_C_li_LOGENTITY"                       catgets 516 */
/* Overload entity */
#define SMSTL_C_ovl_LOGENTITY           517     /* "SMSTL_C_ovl_LOGENTITY"                      catgets 517 */
/* SgTrans entity */
#define SMSTL_C_sgtrans_LOGENTITY       518     /* "SMSTL_C_sgtrans_LOGENTITY"                  catgets 518 */
/* SgAccess entity */
#define SMSTL_C_sgaccess_LOGENTITY      519     /* "SMSTL_C_sgaccess_LOGENTITY"                 catgets 519 */
/* Inst entity */
#define SMSTL_C_inst_LOGENTITY          520     /* "SMSTL_C_inst_LOGENTITY"                     catgets 520 */
/* SgCreate entity */
#define SMSTL_C_sgcreate_LOGENTITY      521     /* "SMSTL_C_sgcreate_LOGENTITY"                 catgets 521 */
/* SMPProcess entity */
#define SMSTL_C_smp_proc_LOGENTITY      522     /* "SMSTL_C_smp_proc_LOGENTITY"                 catgets 522 */



/*** End SMP Log Entity ***/


#define Scheduler_LOGENTITY             701     /* "Scheduler_LOGENTITY"                          catgets 701 */

#define PPP_V2_SCPDB_LOGENTITY          729     /* "PPP_V2_SCPDB_LOGENTITY"                       catgets 729 */
#define SLEE_V2_Standby_handler_LOGENTITY   759 /* "SLEE_V2_Standby_handler_LOGENTITY"            catgets 759 */
#define SLEE_V2_DB_LOGENTITY            761     /* "SLEE_V2_DB_LOGENTITY"                         catgets 761 */
#define SLEE_V2_SmsHandler_LOGENTITY    766     /* "SLEE_V2_SmsHandler_LOGENTITY"                 catgets 766 */
#define SLEE_V2_Bulkop_LOGENTITY        767     /* "SLEE_V2_Bulkop_LOGENTITY"                     catgets 767 */
#define SLEE_V2_DataBaseMib_LOGENTITY   768     /* "SLEE_V2_DataBaseMib_LOGENTITY"                catgets 768 */

#define XMLCONFIGLIB_LOGENTITY          970     /* "XMLCONFIGLIB_LOGENTITY "                     catgets 970 */

#define SUPPORTABILITY_LOGENTITY        998     /* "SUPPORTABILITY_LOGENTITY"                     catgets 998 */
#define TEST_TTL_LOGENTITY              999     /* "TEST_TTLLOGENTITY"                            catgets 999 */

#define LCI_Generic                     1000    /* "LCI_Generic"                                  catgets 1000 */
#define TTL_CAUSE                       1001    /* "Cause"                                        catgets 1001 */
#define TTL_ACTION                      1002    /* "Action"                                       catgets 1002 */

#define USER_LogEntity1         1101    /* "USER_LogEntity1"             catgets 1101 */
#define USER_LogEntity2         1102    /* "USER_LogEntity2"             catgets 1102 */
#define USER_LogEntity3         1103    /* "USER_LogEntity3"             catgets 1103 */
#define USER_LogEntity4         1104    /* "USER_LogEntity4"             catgets 1104 */
#define USER_LogEntity5         1105    /* "USER_LogEntity5"             catgets 1105 */
#define USER_LogEntity6         1106    /* "USER_LogEntity6"             catgets 1106 */
#define USER_LogEntity7         1107    /* "USER_LogEntity7"             catgets 1107 */
#define USER_LogEntity8         1108    /* "USER_LogEntity8"             catgets 1108 */
#define USER_LogEntity9         1109    /* "USER_LogEntity9"             catgets 1109 */
#define USER_LogEntity10        1110    /* "USER_LogEntity10"            catgets 1110 */
#define USER_LogEntity11        1111    /* "USER_LogEntity11"            catgets 1111 */
#define USER_LogEntity12        1112    /* "USER_LogEntity12"            catgets 1112 */
#define USER_LogEntity13        1113    /* "USER_LogEntity13"            catgets 1113 */
#define USER_LogEntity14        1114    /* "USER_LogEntity14"            catgets 1114 */
#define USER_LogEntity15        1115    /* "USER_LogEntity15"            catgets 1115 */
#define USER_LogEntity16        1116    /* "USER_LogEntity16"            catgets 1116 */
#define USER_LogEntity17        1117    /* "USER_LogEntity17"            catgets 1117 */
#define USER_LogEntity18        1118    /* "USER_LogEntity18"            catgets 1118 */
#define USER_LogEntity19        1119    /* "USER_LogEntity19"            catgets 1119 */
#define USER_LogEntity20        1120    /* "USER_LogEntity20"            catgets 1120 */
#define USER_LogEntity21        1121    /* "USER_LogEntity21"            catgets 1121 */
#define USER_LogEntity22        1122    /* "USER_LogEntity22"            catgets 1122 */
#define USER_LogEntity23        1123    /* "USER_LogEntity23"            catgets 1123 */
#define USER_LogEntity24        1124    /* "USER_LogEntity24"            catgets 1124 */
#define USER_LogEntity25        1125    /* "USER_LogEntity25"            catgets 1125 */
#define USER_LogEntity26        1126    /* "USER_LogEntity26"            catgets 1126 */
#define USER_LogEntity27        1127    /* "USER_LogEntity27"            catgets 1127 */
#define USER_LogEntity28        1128    /* "USER_LogEntity28"            catgets 1128 */
#define USER_LogEntity29        1129    /* "USER_LogEntity29"            catgets 1129 */
#define USER_LogEntity30        1130    /* "USER_LogEntity30"            catgets 1130 */
#define USER_LogEntity31        1131    /* "USER_LogEntity31"            catgets 1131 */
#define USER_LogEntity32        1132    /* "USER_LogEntity32"            catgets 1132 */
#define USER_LogEntity33        1133    /* "USER_LogEntity33"            catgets 1133 */
#define USER_LogEntity34        1134    /* "USER_LogEntity34"            catgets 1134 */
#define USER_LogEntity35        1135    /* "USER_LogEntity35"            catgets 1135 */
#define USER_LogEntity36        1136    /* "USER_LogEntity36"            catgets 1136 */
#define USER_LogEntity37        1137    /* "USER_LogEntity37"            catgets 1137 */
#define USER_LogEntity38        1138    /* "USER_LogEntity38"            catgets 1138 */
#define USER_LogEntity39        1139    /* "USER_LogEntity39"            catgets 1139 */
#define USER_LogEntity40        1140    /* "USER_LogEntity40"            catgets 1140 */
#define USER_LogEntity41        1141    /* "USER_LogEntity41"            catgets 1141 */
#define USER_LogEntity42        1142    /* "USER_LogEntity42"            catgets 1142 */
#define USER_LogEntity43        1143    /* "USER_LogEntity43"            catgets 1143 */
#define USER_LogEntity44        1144    /* "USER_LogEntity44"            catgets 1144 */
#define USER_LogEntity45        1145    /* "USER_LogEntity45"            catgets 1145 */
#define USER_LogEntity46        1146    /* "USER_LogEntity46"            catgets 1146 */
#define USER_LogEntity47        1147    /* "USER_LogEntity47"            catgets 1147 */
#define USER_LogEntity48        1148    /* "USER_LogEntity48"            catgets 1148 */
#define USER_LogEntity49        1149    /* "USER_LogEntity49"            catgets 1149 */
#define USER_LogEntity50        1150    /* "USER_LogEntity50"            catgets 1150 */
#define USER_LogEntity51        1151    /* "USER_LogEntity51"            catgets 1151 */
#define USER_LogEntity52        1152    /* "USER_LogEntity52"            catgets 1152 */
#define USER_LogEntity53        1153    /* "USER_LogEntity53"            catgets 1153 */
#define USER_LogEntity54        1154    /* "USER_LogEntity54"            catgets 1154 */
#define USER_LogEntity55        1155    /* "USER_LogEntity55"            catgets 1155 */
#define USER_LogEntity56        1156    /* "USER_LogEntity56"            catgets 1156 */
#define USER_LogEntity57        1157    /* "USER_LogEntity57"            catgets 1157 */
#define USER_LogEntity58        1158    /* "USER_LogEntity58"            catgets 1158 */
#define USER_LogEntity59        1159    /* "USER_LogEntity59"            catgets 1159 */
#define USER_LogEntity60        1160    /* "USER_LogEntity60"            catgets 1160 */
#define USER_LogEntity61        1161    /* "USER_LogEntity61"            catgets 1161 */
#define USER_LogEntity62        1162    /* "USER_LogEntity62"            catgets 1162 */
#define USER_LogEntity63        1163    /* "USER_LogEntity63"            catgets 1163 */
#define USER_LogEntity64        1164    /* "USER_LogEntity64"            catgets 1164 */
#define USER_LogEntity65        1165    /* "USER_LogEntity65"            catgets 1165 */
#define USER_LogEntity66        1166    /* "USER_LogEntity66"            catgets 1166 */
#define USER_LogEntity67        1167    /* "USER_LogEntity67"            catgets 1167 */
#define USER_LogEntity68        1168    /* "USER_LogEntity68"            catgets 1168 */
#define USER_LogEntity69        1169    /* "USER_LogEntity69"            catgets 1169 */
#define USER_LogEntity70        1170    /* "USER_LogEntity70"            catgets 1170 */
#define USER_LogEntity71        1171    /* "USER_LogEntity71"            catgets 1171 */
#define USER_LogEntity72        1172    /* "USER_LogEntity72"            catgets 1172 */
#define USER_LogEntity73        1173    /* "USER_LogEntity73"            catgets 1173 */
#define USER_LogEntity74        1174    /* "USER_LogEntity74"            catgets 1174 */
#define USER_LogEntity75        1175    /* "USER_LogEntity75"            catgets 1175 */
#define USER_LogEntity76        1176    /* "USER_LogEntity76"            catgets 1176 */
#define USER_LogEntity77        1177    /* "USER_LogEntity77"            catgets 1177 */
#define USER_LogEntity78        1178    /* "USER_LogEntity78"            catgets 1178 */
#define USER_LogEntity79        1179    /* "USER_LogEntity79"            catgets 1179 */
#define USER_LogEntity80        1180    /* "USER_LogEntity80"            catgets 1180 */
#define USER_LogEntity81        1181    /* "USER_LogEntity81"            catgets 1181 */
#define USER_LogEntity82        1182    /* "USER_LogEntity82"            catgets 1182 */
#define USER_LogEntity83        1183    /* "USER_LogEntity83"            catgets 1183 */
#define USER_LogEntity84        1184    /* "USER_LogEntity84"            catgets 1184 */
#define USER_LogEntity85        1185    /* "USER_LogEntity85"            catgets 1185 */
#define USER_LogEntity86        1186    /* "USER_LogEntity86"            catgets 1186 */
#define USER_LogEntity87        1187    /* "USER_LogEntity87"            catgets 1187 */
#define USER_LogEntity88        1188    /* "USER_LogEntity88"            catgets 1188 */
#define USER_LogEntity89        1189    /* "USER_LogEntity89"            catgets 1189 */
#define USER_LogEntity90        1190    /* "USER_LogEntity90"            catgets 1190 */
#define USER_LogEntity91        1191    /* "USER_LogEntity91"            catgets 1191 */
#define USER_LogEntity92        1192    /* "USER_LogEntity92"            catgets 1192 */
#define USER_LogEntity93        1193    /* "USER_LogEntity93"            catgets 1193 */
#define USER_LogEntity94        1194    /* "USER_LogEntity94"            catgets 1194 */
#define USER_LogEntity95        1195    /* "USER_LogEntity95"            catgets 1195 */
#define USER_LogEntity96        1196    /* "USER_LogEntity96"            catgets 1196 */
#define USER_LogEntity97        1197    /* "USER_LogEntity97"            catgets 1197 */
#define USER_LogEntity98        1198    /* "USER_LogEntity98"            catgets 1198 */
#define USER_LogEntity99        1199    /* "USER_LogEntity99"            catgets 1199 */
#define USER_LogEntity100       1200    /* "USER_LogEntity100"           catgets 1200 */


#undef NL_SETN

#endif /* LOGENTITY */
