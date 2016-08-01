/**
 * @file CAND_if.h
 * @brief CAN Driver: public interface of CAN module for driver layer. 
 * @author Gianpiero Lenta - Bitron S.p.A. / Carmine Celozzi - Akhela S.r.l.
 * @date 23 may 2012 / 20 november 2014
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
| 23/05/12   0.1  GIL     First derivative from Tesla (125K)
|-----------------------------------------------------------------------------
| 18/09/12   0.2  GIL     Second draft: UDS integration
|-----------------------------------------------------------------------------
| 28/09/12   0.3  GIL     Third draft: added confirmation function, indication
|                         function and timeout function
|-----------------------------------------------------------------------------
| 12/04/13   0.4  GIL     Completely driver rewrite
|-----------------------------------------------------------------------------
| 25/06/13   0.5  GIL     Creato layer NETP(timeout monitor)
|-----------------------------------------------------------------------------
| 01/11/13   0.6  GIL     Can Wire failure management (fixing transceiver driver)
|-----------------------------------------------------------------------------
| 08/11/13   0.7  GIL     Finish node Mute and Bus off
|-----------------------------------------------------------------------------
| 06/10/14   1.0  CC      Porting first release to new architecture for TESLA
|                         project
|-----------------------------------------------------------------------------
| 20/10/14   1.1  CC      Inserted some bug fixing and module optimization
|-----------------------------------------------------------------------------
| 20/11/14   2.0  CC      Platform official release (complete redesign)
|-----------------------------------------------------------------------------
| 18/02/15   2.1  CC      Inserted the routine CAND_GetBusWakeUp used, when the
|                         transceiver is in sleep, to check the wakeup CAN bus
|-----------------------------------------------------------------------------
*/

#ifndef CAND_IF_H_
#define CAND_IF_H_

#include "CAND_CfgIf.h"

#ifdef CAND_IF_OWNER
	#define CAND_EXTERN
#else
	#define CAND_EXTERN		extern
#endif

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define CAND_DRV_PSG_MSG_NMB        ((uint8_t)CAND_TX_MSG_NMB+(uint8_t)CAND_RX_MSG_NMB)


/*______ G L O B A L - T Y P E S _____________________________________________*/

/* TODO SGR - OK */
/* TJA transceiver operating state*/
typedef enum CAND_TransceiverOpState_e
{
  CAND_TS_PON = 0,
  CAND_TS_NORMAL,
  CAND_TS_STBY,
  CAND_TS_GOTO_SL
}CAND_TransceiverOpState_t;

/* TODO SGR - OK */
typedef enum CAND_CanHwErrStatus_e
{
  CAND_HW_NO_ERR      = 0x00,
  CAND_HW_STUFF_ERR   = 0x01,
  CAND_HW_FORM_ERR    = 0x02,
  CAND_HW_ACK_ERR     = 0x03,
  CAND_HW_RECBIT_ERR  = 0x04,
  CAND_HW_DOMBIT_ERR  = 0x05,
  CAND_HW_CRC_ERR     = 0x06,
  CAND_HW_UND_ERROR   = 0x07
}CAND_CanHwErrStatus_t;

/* TODO SGR OK */
/* Mailbox handler */
typedef enum CAND_MailBoxHnd_e
{
  CAND_MAILBOX_0_HND = 0,
  CAND_MAILBOX_1_HND,
  CAND_MAILBOX_2_HND,
  CAND_MAILBOX_3_HND,
  CAND_MAILBOX_4_HND,
  CAND_MAILBOX_5_HND,
  CAND_MAILBOX_6_HND,
  CAND_MAILBOX_7_HND,
  CAND_MAILBOX_8_HND,
  CAND_MAILBOX_9_HND,
  CAND_MAILBOX_10_HND,
  CAND_MAILBOX_11_HND,
  CAND_MAILBOX_12_HND,
  CAND_MAILBOX_13_HND,
  CAND_MAILBOX_14_HND,
  CAND_MAILBOX_15_HND,
  CAND_MAILBOX_NMB
}CAND_MailBoxHnd_t;

/* TODO SGR OK */
/* diagnose request type */
typedef enum
{
  CAND_NO_DIAG_REQ = 0,
  CAND_FUNCTIONAL_DIAG_REQ,
  CAND_PHYSICAL_DIAG_REQ
}CAND_DiagType_t;

/* TODO SGR OK */
typedef enum
{
  CAND_EVT_TX_SUCCESS = 1,
  CAND_EVT_WRONG_DIR,
  CAND_EVT_TE_NOT_EXPIRED,
  CAND_EVT_DEAD_BAND_ATTEMPT,
  CAND_EVT_WRONG_MSG,
  CAND_EVT_BUS_OFF,
  CAND_EVT_FRAMEBUS_BUSY,
  CAND_EVT_UDS_SUSPENDED
}CAND_EvTx_t;


/* Ecu cold start state (pag. 49 Applications hints TJA1055T) */
typedef enum
{
  CAND_WUP_NONE = 0,
  CAND_WUP_1,      /* Power ON & wake up set : system start up &  wake up handling */
  CAND_WUP_2,      /* No Power ON & wake up  : wake up from sleep wake up handling */
  CAND_WUP_3,      /* Power ON & wake up     : only system start up                */
  CAND_WUP_4       /* Power ON & wake up     . no actions                          */
}CAND_WakeUpState_t;


/*______ G L O B A L - M A C R O S ___________________________________________*/

/* Apply to message ID to define standard or extended ID */
#define CAND_STD_ID(id)     ((u32)((u32)((id) & (0x000007FFU)) << 18U))
#define CAND_EXT_ID(id)     ((u32)((u32)((id) & (0x1FFFFFFFU)) | 0x80000000U))


/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief General Init of CAN module
 *
 */
CAND_EXTERN void CAND_Init(void);

/**
 * @brief  Put can module in power off
 * @return None
 */
CAND_EXTERN void CAND_PwrOff(void);

/**
 * @brief  Transmit a CAN message
 * \n DO
 * \n [Check if bus off]
 * \n [Check if driver or passenger]
 * \n [Check if MsgHandle is coherent]
 * \n ...
 * \n OD
 * @param MsgHandle Handle of message to be transmitted
 * @return the result of transmission
 */
CAND_EXTERN CAND_EvTx_t CAND_SendMsg(CAND_TxMsgName_t TxMsgName, uint8_t Dlc);


CAND_EXTERN uint8_t CAND_GetStartScanTxMsg(void);

CAND_EXTERN uint8_t CAND_GetStopScanTxMsg(void);

CAND_EXTERN uint8_t CAND_GetStartScanRxMsg(void);

CAND_EXTERN uint8_t CAND_GetStopScanRxMsg(void);


/**
 * @brief  Check the bus off state of CAN controller
 * @return TRUE if bus off occours.
 */
CAND_EXTERN u08 CAND_GetBusOffState(void);

/**
 * @brief  Check the wire failure of CAN controller
 * @return TRUE if wire failure occours.
 */
CAND_EXTERN u08 CAND_GetWireFailureState(void);

/**
 * @brief  Force the wire failure on CAN controller
 * @return void
 */
CAND_EXTERN void CAND_SetWireFailureState(bool_t value);

/**
 * @brief  Check the Error Passive failure of CAN controller
 * @return TRUE if Error Passive failure occours.
 */
CAND_EXTERN u08 CAND_GetErrorPassiveState(void);

/**
 * @brief  Check the Error Active failure of CAN controller
 * @return TRUE if Error Active failure occours.
 */
CAND_EXTERN u08 CAND_GetErrorActiveState(void);

/**
 * @brief  Check the Error Warning failure of CAN controller
 * @return TRUE if Error Warning failure occours.
 */
CAND_EXTERN u08 CAND_GetErrorWarningeState(void);

/**
 * @brief  Check the wake up condition of tranceiver
 * @return wake up condition of tranceiver
 */
CAND_WakeUpState_t CAND_GetWakeUpState(void);

/**
 * @brief  Check the tranceiver operational state
 * @return tranceiver operational state
 */
CAND_TransceiverOpState_t CAND_GetTransceiverOpState(void);

/**
 * @brief  Get the lenght of message received
 * @param  MsgHandle Handle of mailbox
 * @return the DLC of message received
 */
CAND_EXTERN u08 CAND_GetMailBoxLen(CAND_RxMsgName_t TxMsgName);

/**
 * @brief  Get the HW (network) status
 * @return HW statur error type
 */
CAND_EXTERN CAND_CanHwErrStatus_t CAND_NetworkGetHwErrStatus(void);

/**
 * @brief  Get Dlc Correct Flag
 * @
 */
CAND_EXTERN bool_t CAND_GetDlcCorrectFlag(CAND_RxMsgName_t MsgIdx);


CAND_EXTERN bool_t CAND_CheckTxMsgRdy(CAND_TxMsgName_t MsgIdx);


CAND_EXTERN bool_t CAND_CheckRxMsgRdy(CAND_RxMsgName_t MsgIdx);


CAND_EXTERN bool_t CAND_CheckRxMsgEvt(CAND_RxMsgName_t MsgIdx);



/**
 * @brief  Public function for Manage CAN error (warning, active, passive)
 * @return no erturn value
 */
CAND_EXTERN void CAND_ManageCANError(void);

/**
 * @brief  Public Get method returning diag type
 * @return diag type :phys or funct
 */
CAND_EXTERN CAND_DiagType_t CAND_GetDiagType(void);

/**
 * @brief  Public Set method to notify the diag type current
 * @return diag type :phys or funct
 */
CAND_EXTERN void CAND_SetDiagType(CAND_DiagType_t DiagType);

/**
 * @brief  Public Set method initializing diag type
 */
CAND_EXTERN void CAND_InitDiagType(void);


#ifdef __CMMD_MULTI_DBC__
CAND_EXTERN uint8_t CAND_GetMsmEcuType(void);
#endif

/**
 * @brief Read the level of CAN RxD pin to determine the bus status.
 * This check is possible only before of tranceiver initialization.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return uint8_t
 * @retval 0x00: bus is in sleep
 * @retval 0x01: bus is in wakeup
 * @retval 0x0FF: not possible check the bus
 */
CAND_EXTERN uint8_t CAND_GetBusWakeUp(void);


#endif /* CAND_IF_H_ */
