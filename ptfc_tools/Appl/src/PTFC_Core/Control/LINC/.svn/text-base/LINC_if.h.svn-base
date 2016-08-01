/**
 * @file LINC_if.h
 * @brief LIN control: source code of LIN module for control layer. 
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/

#ifndef LINC_IF_H_
#define LINC_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef LINC_IF_OWNER
 #define LINC_EXTERN
#else
 #define LINC_EXTERN  extern
#endif

#ifdef __LINC_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/
/* LINC module states for slave task */
typedef enum
{
  LINC_SLEEP = 0,   /* Sleep state */
  LINC_WAKE_UP,     /* WakeUp trasmitting state */
  LINC_IDLE,        /* Idle state (on, waiting to send) */
  LINC_BF_RD,       /* Break Field Received */
  LINC_SF_RD,       /* Synchronization Field Received */
  LINC_RG_DATA,     /* Receiving data */
  LINC_ERROR,       /* Error state */
  LINC_MAX_STATUS
} LINC_Status_t;

/* Frame status */
typedef enum
{
  LINC_NO_FAULT = 0,
  LINC_ERROR_RESPONSE,
  LINC_ERROR_TIMEOUT_RESPONSE,
  LINC_ERROR_GENERIC_HW,
  LINC_MAX_FRAME_STATUS
} LINC_FrameError_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the LINC driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
LINC_EXTERN void LINC_Init(void);

/**
 * @brief Send required buffer as a LIN response
 * @param Frame Handle, Tx buffer pointer, length of buffer
 * @return void
 * @note
 */
LINC_EXTERN void LINC_PutMessage(LINC_MessageMap_t MsgHandle, 
                                 uint8_t *DataBuf, uint8_t len);

/**
 * @brief Returns data received as LIN response
 * @param Frame Handle, Rx buffer pointer, maximum length of buffer
 * @return uint8_t
 * @note
 */
LINC_EXTERN uint8_t LINC_GetMessage(LINC_MessageMap_t MsgHandle, 
                                    uint8_t *DataBuf, uint8_t len);

/**
 * @brief Read frame status form frame
 * @param Frame Handle
 * @return LINC_FrameError_t
 * @note
 */
LINC_EXTERN LINC_FrameError_t LINC_GetMessageStatus(LINC_MessageMap_t MsgHandle);

/**
 * @brief Read frame error count on frame
 * @param Frame Handle
 * @return uint8_t
 * @note
 */
LINC_EXTERN uint8_t LINC_GetMessageErrorCount(LINC_MessageMap_t MsgHandle);

/**
 * @brief Reset frame error type and frame
 * @param Frame Handle
 * @return uint8_t
 * @note
 */
LINC_EXTERN void LINC_ResetMessageError(LINC_MessageMap_t MsgHandle);

/**
 * @brief Set error type and increase error counter into selected frame
 * @param Frame Handle
 * @return void
 * @note
 */
LINC_EXTERN void LINC_SetMessageError(LINC_MessageMap_t MsgHandle);

/**
 * @brief Set request to send of sporadic frame
 * @param Frame Handle
 * @return void
 * @note
 */
LINC_EXTERN void LINC_SetMessageSprRequest(LINC_MessageMap_t MsgHandle);

/**
 * @brief Wake up transceiver and UART
 * @param channel index
 * @return void
 * @note
 */
LINC_EXTERN void LINC_WakeUp(uint8_t chn_hnd);

/**
 * @brief Send Go to sleep command to transceiver and UART
 * @param channel index
 * @return void
 * @note
 */
LINC_EXTERN void LINC_GoToSleep(uint8_t chn_hnd);

/**
 * @brief Indicates the reception of wake up signal from slave node
 * @param channel index
 * @return boolean
 * @note
 */
LINC_EXTERN bool LINC_GetBusWakeUpRequest(uint8_t chn_hnd);

/**
 * @brief Indicates the reception of signal from bus
 * @param channel index
 * @return boolean
 * @note
 */
LINC_EXTERN bool LINC_GetBusSignalRequest(uint8_t chn_hnd);

/**
 * @brief Indicates the confirm of signal reception from bus
 * @param channel index
 * @return boolean
 * @note
 */
LINC_EXTERN bool LINC_GetBusSignalRequestConfirmed(uint8_t chn_hnd);

/**
 * @brief Return LINC status
 * @param channel index
 * @return LINC_Status_t
 * @note
 */
LINC_EXTERN LINC_Status_t LINC_GetStatus(uint8_t chn_hnd);


/**
 * @brief Get UARTD Error state
 * @param channel index
 * @return UARTD_HwErrorStatus_t
 * @note
 */
#ifdef __UARTD_IS_PRESENT__
  LINC_EXTERN UARTD_HwErrorStatus_t LINC_GetDiag(uint8_t chn_hnd);
#endif

/**
 * @brief Send identifier
 * @param channel index, Frame Handle
 * @return void
 * @note
 */
LINC_EXTERN void LINC_PutHeader(uint8_t chn_hnd, LINC_MessageMap_t MsgHandle);

/**
 * @brief This function handles the reception and transmission of the frame
 * @return void
 * @note
 */
LINC_EXTERN void LINC_ReceptionTask(uint8_t chn_hnd);




/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* __LINC_IS_PRESENT__ */

#endif /* LINC_IF_H_ */
