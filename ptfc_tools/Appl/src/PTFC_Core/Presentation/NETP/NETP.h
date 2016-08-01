/**
 * @file NETP.h
 * @brief NETwork Presentation: private interface of network module for the 
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
*/

#ifndef __NETP_H
#define __NETP_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "PRES_if.h"
#include "NETP_cbk.h"

/* Module inhibition filter */
#ifdef __NETP_IS_PRESENT__

#include "NETP_config.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Defines the Node Mute silence time as required by FIAT NORM 9009 Ed.3 */
#define NETP_MUTE_SILENCE_TIME        (1500U / 10U) /* T_silence = 1,5s */


/*______ G L O B A L - T Y P E S _____________________________________________*/


typedef enum NETP_TxType_e
{
  NETP_TX_P = 0,
  NETP_TX_E,
  NETP_TX_PE
}NETP_TxType_t;

typedef enum NETP_EnRxMsgTOutMng_e
{
  NETP_TOUT_MNG_DISABLE   = 0x00,
  NETP_TOUT_MNG_ENABLE    = 0x01
}NETP_EnRxMsgTOutMng_t;


typedef struct NETP_RxStatus_s
{
  u16  ElapsedTime;
  NETP_MsgStatus_t MsgStatus;
}NETP_RxStatus_t;


typedef struct NETP_RxNetMonitor_s
{
  NETP_ComType_t    ComType;              /* Timeout enable via UDS comm control service */
  void              (*IndCbk)(void);      /* Indication callback */
  uint16_t          RxMsgTimeOut;         /* Timeout counter */
  void              (*RecCbk)(void);      /* Recovery callback */
  NETP_Af_t         AbsentFaultyEnable;   /* Absent faulty check enable */
  bool_t            DiagKeyOffEnable;     /* Enable the diagnosis management in key off */
}NETP_RxNetMonitor_t;




/* TODO SGR - OK */
typedef struct NETP_TxNetMonitor_s
{
  NETP_ComType_t    ComType;            /* Timeout enable via UDS comm control service */
  NETP_TxType_t     TxType;             /* Transmition Type */
  uint16_t          Period;             /* Time period between two periodic transmission*/
  uint16_t          Mtbe;               /* Minimum time between events */
  void             (*ConfCbk)(void);    /* Confirmation callback */
}NETP_TxNetMonitor_t;




/*______ G L O B A L - D A T A _______________________________________________*/

extern const NETP_TxNetMonitor_t NETP_TxNetMonitor[CAND_TX_MSG_NMB];

#ifdef NETP_TIMEOUT_SERVICE
  extern const NETP_RxNetMonitor_t NETP_RxNetMonitor[CAND_RX_MSG_NMB];
#endif

extern const NETP_TxNetMonitor_t *NETP_TxNetMonitorPtr;
extern const NETP_RxNetMonitor_t *NETP_RxNetMonitorPtr;

#ifdef __CMMD_MULTI_DBC__
/* MSM model type */
extern uint8_t NETP_MsmEcuType;
#endif


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S _____________*/

void NETP_InitTimeout(NETP_ComType_t ComType);

/*----------------------------------------------------------------------------*/
/*Name : NETP_GetMuteStatus                                                   */
/*Role : Get Mute status                                                      */
/*Interface : return TRUE if Mute DTC is present                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool_t NETP_GetMuteStatus(void);


/*----------------------------------------------------------------------------*/
/*Name : NETP_GetBcmAbsentaFaultyStatus                                       */
/*Role : Get absent/faulty status from BCM Node                               */
/*Interface : return status of BCM node : absent/faulty/no fault/not tested   */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
PRES_Fault_t NETP_GetBcmAbsentaFaultyStatus(void);


#endif /* end __NETP_IS_PRESENT__ */

#endif /* end __NETP_H */
