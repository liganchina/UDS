/**
 * @file NETP_if.h
 * @brief NETwork Presentation: public interface of network module for the 
 * presentation layer.
 * @n The main module features/services are:
 * @li Multi DBC management according to MSM ECU type
 * @li API to send the event CAN messages by applicative
 * @li API to send the event CAN messages by diagnosis applicative (UDS)
 * @li Configuration table to send the periodic CAN messages automatically
 * @li Configuration table to notify the sending message by confirmation callback
 * @li Configuration table to filter the event messages near periodic messages
 * sending. This strategy, call MTBE, can be enabled/disabled by the configuration
 * define NETP_MTBE_STRATEGY
 * @li Configuration table to manage the diagnosis recovery for absent/faulty state.
 * This service can be enabled/disabled by the configuration define NETP_TIMEOUT_SERVICE.
 * @li Electrical and network diagnosis with own recovery
 * </ul>
 *
 * @version 2.1
 * @author Gianpiero Lenta (Bitron S.p.A.) - Carmine Celozzi (Akhela S.r.l.)
 * @date 23 may 2012 / 20 october 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 05/06/13   0.1  GIL     First derivative from Tesla (125K)
|-----------------------------------------------------------------------------
| 07/11/13   0.2  GIL     - Node Mute and bus off management
|                         - Fixing some MISRA C rule
|                         - Timeout Inhibition changed
|-----------------------------------------------------------------------------
| 06/01/14   0.3  GIL     Bit6(Test Not Completed this Monitorung Cycle) 
|                         management
|-----------------------------------------------------------------------------
| 06/10/14   1.0  CC      Porting first release to new architecture for TESLA
|                         project
|-----------------------------------------------------------------------------
| 20/10/14   1.1  CC      Inserted some bug fixing and module optimization
|-----------------------------------------------------------------------------
| 04/11/14   1.2  CC      New design to align this module to new CAND module.
|                         The main features inserted are:
|                         - Multi DBC management according to MSM ECU type
|                         - Configuration table to send the periodic CAN  
|                           messages automatically
|                         - Configuration table to notify the sending message 
|                           by confirmation callback
|                         - Configuration table to filter the event messages 
|                           near periodic messages sending. This strategy, 
|                           call MTBE, can be enabled/disabled by the   
|                           configuration define NETP_MTBE_STRATEGY
|-----------------------------------------------------------------------------
| 20/11/14   2.0  CC      Platform official release (complete redesign)
|-----------------------------------------------------------------------------
| 17/02/15   2.1  CC      Inserted the filter in NET_ON to send the applicative
|                         periodic messages
|-----------------------------------------------------------------------------
| 03/06/15   2.2  CC      Improvment about call of indication callback
|-----------------------------------------------------------------------------
| 04/11/15   2.3  DC      Improvements of absent\faulty network fail management
|-----------------------------------------------------------------------------
*/

#ifndef __NETP_IF_H
#define __NETP_IF_H

#ifdef NETP_IF_OWNER
	#define NETP_EXTERN
#else
	#define NETP_EXTERN		extern
#endif

#include "NETP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/**
 * Enumerative containing the RX messages status.
 * Each state is maintained until will occur the next state change.
 */
typedef enum NETP_MsgStatus_e
{
  /**@{*/
  NETP_MSG_INIT_MONITOR = 0,  /**< Initialization state */
  NETP_MSG_NOT_RECEIVED,      /**< This state is detectable only if the
                                *  message has a configured timeout elapsed */
  NETP_MSG_RECEIVED           /**< This state is updated at every message received */
  /**@}*/
}NETP_MsgStatus_t;

/**
 * Enumerative containing the Communication Type attribute.
 * This tag allows the management of some applicative and diagnostic services.
 * In fact it's an attribute must to be used to configure the field "ComType"
 * present in the look-up tables of the RX and TX messages. 
 * 
 * [Ex]: By this field is possible set the current Communication Type to
 * inhibit the timeout management of the Rx messages during the TP is in run.
 */
typedef enum NETP_ComType_e
{
  /**@{*/
  NETP_CCT_NONE_MSG   = 0x00U,  /**< Communication type of none message */
  NETP_CCT_NORMAL_MSG = 0x01U,  /**< Communication type of a normal message */
  NETP_CCT_NWM_MSG    = 0x02U,  /**< Communication type of a message of network management */
  NETP_CCT_APPL_MSG   = 0x03U,  /**< Communication type of applicative message */
  NETP_CCT_DIAG_MSG   = 0x04U,  /**< Communication type of a diagnostic message */
  NETP_CCT_ALL_MSG    = 0x07U   /**< Communication type of a generic message */
  /**@}*/
}NETP_ComType_t;



typedef enum NETP_NetStatus_e
{
  NETP_NET_OFF = 0,
  NETP_NET_ON
}NETP_NetStatus_t;


/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Initialization routine for network module of the presentation layer.
 * @author Gianpiero Lenta - Bitron S.p.A. / Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NETP_EXTERN void NETP_Init(void);

/**
 * @brief Initialization routine of the network module.
 * It initialize every resources except communication control type and DBC configurations.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NETP_EXTERN void NETP_Restore(void);

/**
 * @brief Manage the send request of the periodic TX messages. The messages
 * of type periodic (P) must be configured in the look-up table NETP_TxNetMonitor.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NETP_EXTERN void NETP_PeriodicMsgMgmt(void);
 
 
NETP_EXTERN PRES_Fault_t NETP_GetAbsentFaultyStatus(NETP_Af_t AbsFaulty);
 
 
NETP_EXTERN void NETP_ApplMsgSendingMgmt(void);
 
/*----------------------------------------------------------------------------*/
/*Name : NETP_ClearDtcEvent                                                   */
/*Role : Align Diagnose network and DTC after a clear all DTC                 */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_ClearDtcEvent(void);

/*----------------------------------------------------------------------------*/
/*Name : CAND_MonitorRxPeriod                                                  */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : must be called @10ms (polling)                              */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_MonitorRxPeriod(void);

/*----------------------------------------------------------------------------*/
/*Name : NETP_ManageNodeMute                                                  */
/*Role : Manage node mute condition                                           */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_ManageNodeMute(void);

/*----------------------------------------------------------------------------*/
/*Name : NETP_RxEvtMgmt                                             */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : must be called @ event                                      */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_RxEvtMgmt(void);

/*----------------------------------------------------------------------------*/
/*Name : CAND_GetRxStatus                                                     */
/*Role :  Get rx status                                                       */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN NETP_MsgStatus_t NETP_GetRxStatus(CAND_RxMsgName_t RxMsgName);

/*----------------------------------------------------------------------------*/
/*Name : NETP_EnableRxMsgTOutMng                                              */
/*Role : Enable rx message timeout when network management is ON              */
/*Interface : called by network management                                    */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_EnableRxMsgTOutMng(void);

/*----------------------------------------------------------------------------*/
/*Name : NETP_DisableRxMsgTOutMng                                             */
/*Role : Disable rx message timeout when network management is OFF            */
/*Interface : called by network management                                    */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_DisableRxMsgTOutMng(void);


/*----------------------------------------------------------------------------*/
/*Name : NETP_SetCommCtrlTypeRx                                               */
/*Role : Set Communication control type rx (UDS service 28)                   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_SetCommCtrlTypeRx(NETP_ComType_t comt);

/*----------------------------------------------------------------------------*/
/*Name : NETP_SetCommCtrlTypeTx                                               */
/*Role : Set Communication control type tx (UDS service 28)                   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN void NETP_SetCommCtrlTypeTx(NETP_ComType_t comt);

/*----------------------------------------------------------------------------*/
/*Name : NETP_GetCommCtrlTypeTx                                               */
/*Role : Get Communication control type tx (UDS service 28)                   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN NETP_ComType_t NETP_GetCommCtrlTypeTx(void);

/*----------------------------------------------------------------------------*/
/*Name : NETP_GetCommCtrlTypeRx                                               */
/*Role : Get Communication control type rx (UDS service 28)                   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN NETP_ComType_t NETP_GetCommCtrlTypeRx(void);

/*----------------------------------------------------------------------------*/
/*Name : NETP_GetMonitorStatus                                                */
/*Role : Get Nept monitoring status (ON/OFF)                                  */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
NETP_EXTERN PRES_State_t NETP_GetMonitorStatus(void);


/*----------------------------------------------------------------------------*/
/*Name : NETP_KeyStsChanged                                                   */
/*Role : Force re-testing of network message after KEY-ON Event               */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
extern void NETP_KeyStsChanged(PRES_KeyStatus_t KeyStatus);

NETP_EXTERN PRES_ResSts_t NETP_SendMsgReq(CAND_TxMsgName_t MsgName);
NETP_EXTERN PRES_ResSts_t NETP_SendDiagMsg(CAND_TxMsgName_t MsgName, uint8_t Dlc);

NETP_EXTERN void NETP_TxEvtMgmt(void);

NETP_EXTERN void NETP_EnableRxTimeout(bool_t Enable);


NETP_EXTERN void NETP_NotifyNetSts(NETP_NetStatus_t NetSts);


/**
 * @brief  Public function for Manage message received status
 * @return message received status
 */
NETP_EXTERN PRES_Fault_t NETP_GetMsgDiag(CAND_RxMsgName_t RxMsgName);

/**
 * @brief  Public function for ManageNetwork fault (e.g.) bud off, mute, electric fail,faulty
 * @return type of fault
 */
NETP_EXTERN PRES_Fault_t NETP_GetCanDiag(NETP_CanDTC_t diagSym);


/**
 * @brief  Public function returning if the condition fot timeout monitor are fulfilled
 * @return S_ON = fulfilled, S_OFF = not fulfilled
 */

NETP_EXTERN PRES_State_t NETP_GetCanDiagState(NETP_CanDTC_t diagSym);


#endif /* end __NETP_IF_H */

/*______ E N D _____ (NETP_if.h) _____________________________________________*/
