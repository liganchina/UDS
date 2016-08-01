/**
 * @file UARTD_if.h
 * @brief LIN Driver: public interface of UART module for driver layer. 
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

#ifndef UARTD_IF_H_
#define UARTD_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef UARTD_IF_OWNER
 #define UARTD_EXTERN
#else
 #define UARTD_EXTERN  extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UARTD_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/
/* Uart module state machine */
typedef enum
{
  UARTD_SLEEP = 0,  /* Sleep state */
  UARTD_IDLE,	    /* Idle state (on, waiting to send) */
  UARTD_TG_BF,	    /* Transmitting Break Field  */
  UARTD_TG_DATA,    /* Trasmitting data */
  UARTD_MAX_STATUS
} UARTD_Status_t;

/* Uart hardware errors */
typedef enum
{
  UARTD_NO_ERROR = 0,           
  UARTD_ERR_TX_OVERRUN,
  UARTD_ERR_HW_OVERRUN,         /* Overrun error */ 
  UARTD_ERR_FRAMING,            /* Framing error (no stop bit detected) */
  UARTD_ERR_PARITY,             /* Parity error */
  UARTD_ERR_DATA_CONS,          /* Data consistency error */
  UARTD_ERR_RESP_PREP,
  UARTD_ERR_CHECKSUM,
  UARTD_ERR_ID_PARITY,
  UARTD_ERR_GENERIC,
  UARTD_SHORT_CIRCUIT_LOW,       /* Set short circuit to Ground */
  UARTD_SHORT_CIRCUIT_HIGH,      /* Set short circuit to Vbat */
  UARTD_ERR_MAX
} UARTD_HwErrorStatus_t;

/* Managemet of Sleep mode */
typedef enum
{
  UARTD_POWEROFF,
  UARTD_RECEPTION_TASK_ON
} Uartd_SleepMode_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the UARTD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
UARTD_EXTERN void UARTD_Init(void);

/**
 * @brief This function enables the UART module of uC.
 * @param uint8_t, Uart channel number
 * @return void
 */
UARTD_EXTERN void UARTD_WakeUp(uint8_t chn_hnd);

/**
 * @brief This function disables the UART module of uC.
 * @param uint8_t, Uart channel number
 * @return void
 */
UARTD_EXTERN void UARTD_GoToSleep(uint8_t chn_hnd);

/**
 * @brief This function reads n bytes from the reception buffer.
 * @param Uart channel number, pointer to data buffer, number of bytes to read
 * @return uint8_t, Number of read bytes
 * @note Head on first element to read; T over last element to read.
 */
UARTD_EXTERN uint8_t UARTD_ReadBuffer(uint8_t chn_hnd, uint8_t *rxBuffer, 
                                      uint8_t len);

/**
 * @brief This function sends n bytes from the transmission buffer.
 * @param Uart channel number, pointer to data buffer, number of bytes to send
 * @return Void
 * @note Head on first element to send; T over last element to send.
 */
UARTD_EXTERN void UARTD_SendBuffer(uint8_t chn_hnd, uint8_t *txBuffer, 
                                   uint8_t len);

/**
 * @brief This function reads the first byte in the reception buffer.
 * @param uint8_t, Uart channel number
 * @return uint8_t, Byte read
 * @note If no byte is available in the reception buffer, 0 is returned.
 */
UARTD_EXTERN uint8_t UARTD_ReadByte(uint8_t chn_hnd);

/**
 * @brief This function sends a byte.
 * @param uint8_t, Uart channel number, uint8_t, byte to send
 * @return Void
 */
UARTD_EXTERN void UARTD_SendByte(uint8_t chn_hnd, uint8_t byteToSend);

/**
 * @brief Returns whether there are non-read bytes in the reception buffer.
 * @param uint8_t, Uart channel number
 * @return Boolean
 */
UARTD_EXTERN bool_t UARTD_IsDataReceived(uint8_t chn_hnd);

/**
 * @brief Returns the number of non-read bytes in the reception buffer.
 * @param uint8_t, Uart channel number
 * @return uint8_t, Number of bytes in buffer
 */
UARTD_EXTERN uint8_t UARTD_GetNumberOfRxBytes(uint8_t chn_hnd);

/**
 * @brief This function is used to start sending a LIN break field (BF).
 * @param uint8_t, Uart channel number
 * @return Void
 */
UARTD_EXTERN void UARTD_SendBreak(uint8_t chn_hnd);

/**
 * @brief This function returns whether a break field has been received.
 * @param uint8_t, Uart channel number
 * @return Boolean
 * @note True is returned until the current frame ends.
 */
UARTD_EXTERN bool_t UARTD_IsBreakReceived(uint8_t chn_hnd);

/**
 * @brief This function is used to start sending a LIN wakeup signal (WU).
 * @param uint8_t, Uart channel number
 * @return void
 */
UARTD_EXTERN void UARTD_SendWakeUp(uint8_t chn_hnd);

/**
 * @brief This function is used to reset break field value.
 * @param uint8_t, Uart channel number
 * @return void
 */
UARTD_EXTERN void UARTD_ResetBreakFieldLen(uint8_t chn_hnd);

/**
 * @brief This function informs on a bus signal reception.
 * @param Uart channel number
 * @return Boolean
 */
UARTD_EXTERN bool_t UARTD_GetBusSignalRequest(uint8_t chn_hnd);

/**
 * @brief This function informs on a slave wakeup signal reception.
 * @param uint8_t, Uart channel number
 * @return Boolean
 */
UARTD_EXTERN bool_t UARTD_GetBusWakeUpRequest(uint8_t chn_hnd);

/**
 * @brief Return if IUT has received a new signal on bus (for s.c. detection)
 * @param uint8_t, Uart channel number
 * @return boolean
 */
UARTD_EXTERN bool_t UARTD_GetBusActivity(uint8_t chn_hnd);

/**
 * @brief This function set a short circuit error.
 * @param uint8_t, Uart channel number
 * @return void
 */

UARTD_EXTERN void UARTD_SetShortCircuitError(uint8_t chn_hnd);

/**
 * @brief This function returns the status of the module.
 * @param uint8_t, Uart channel number
 * @return UARTD_Status_t
 */
UARTD_EXTERN UARTD_Status_t UARTD_GetStatus(uint8_t chn_hnd);

/**
 * @brief This function returns the last error status of the module.
 * @param uint8_t, Uart channel number
 * @return UART_HwErrorStatus_t
 */
UARTD_EXTERN UARTD_HwErrorStatus_t UARTD_GetDiag(uint8_t chn_hnd);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* UARTD_IF_H_ */

