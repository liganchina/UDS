/**
 * @file LINP_config.c
 * @brief LIN presentation: source code of LIN module for presentation layer. 
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

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINP.h"
#include "LINP_config.h"

/* Module inhibition filter */
#ifdef __LINP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef enum
{
  ERROR_BIT_ACTIVE,
  NO_RESPONSE
} Private_Data_t;

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

void LINP_CMD_MEMORY_Recovery(void);


/*______ G L O B A L - D A T A _______________________________________________*/

/* Schedule Table 1 */
#define LINP_SCHED_TAB_LEN_1      2

/* Frame error counter (ms) */
static uint16_t Linp_cmdAuthErrorCount = 0u;
static uint16_t Linp_cmdMemErrorCount  = 0u;

static PRES_Fault_t Linp_PrivateData[2];
static bool_t Linp_ResponseFromSlave = FALSE;

/* Flag for recovery callback enable */
static bool Linp_St1Fr1CbkEnable = TRUE;
static bool Linp_St1Fr2CbkEnable = TRUE;
const Linp_message_st_t Linp_Schedule_1[LINP_SCHED_TAB_LEN_1] =
{
  /* Message 1 */
  {
    LINC_CMD_AUTH,              /* Frame Id */
    20U,                        /* Slot time (ms) */
    2500U,                      /* Set time out response (ms) */
    &Linp_cmdAuthErrorCount,    /* Error counter (ms)   */
    &Linp_St1Fr1CbkEnable,      /* Recovery callback enable */
    NULL                        /* Callback after timeout */
  },
  /* Message 2 */
  {
    LINC_CMD_MEMORY,            /* Frame Id */
    20U,                        /* Slot time (ms) */
    2500U,                      /* Set time out response (ms) */
    &Linp_cmdMemErrorCount,     /* Error counter (ms)   */
    &Linp_St1Fr2CbkEnable,      /* Recovery callback enable */
    &LINP_CMD_MEMORY_Recovery   /* Callback after timeout */
  },    

  /* Other messages may be defined */
};


/* Message Map */
const Linp_sched_tab_st_t Linp_SchTab[LINP_SCHED_TAB_NUM] =
{  
  {Linp_Schedule_1, LINP_SCHED_TAB_LEN_1},  /* Sched tab 1 */
};


/*--------------------------------------------------------------------*/
/* Message Recovery                                                   */
/*--------------------------------------------------------------------*/

/**
 * @brief This function set the recovery values for a missing message.
 * @return void
 */
void LINP_CMD_MEMORY_Recovery(void)
{
  LINC_cmdMemory_t recoveryValues;

  recoveryValues.Error_Bit_Memory = LINC_NO_ERROR_BIT;
  recoveryValues.memoryGenDefect  = LINC_PANEL_DEFECT;
  recoveryValues.selectedMemory   = LINC_NO_MEM;
  recoveryValues.spareBits        = 0U;

  /* Set vaules into internal reception buffer */
  LINC_PutMessage(LINC_CMD_MEMORY, (uint8_t*)&recoveryValues, LINC_CMD_MEMORY_LEN);
  
  /* Set private data for DTC report */
  Linp_PrivateData[NO_RESPONSE] = PRES_MSG_NOT_RECEIVED;
  
  /* No response from LIN Slave keyboard */
  Linp_ResponseFromSlave = FALSE;
}


/**
 * @brief This function sets Authorization signal for CMD_Authorizations_LIN message.
 * @return void
 */
void LINP_setAuthorization(LINC_PanelAuth_t auth)
{
  LINC_cmdAuth_t dataBytes;
  
  dataBytes.authMemoryPanel = auth;
  
  /* Set values into internal transmission buffer */
  LINC_PutMessage(LINC_CMD_AUTH, (uint8_t*)&dataBytes, LINC_CMD_AUTH_LEN);
}


/**
 * @brief This function gets the selected signal from CMD_Memory_LIN message
 * @return The value of the signal
 */
LINC_Memory_t LINP_getSelectedMemory(void)
{
  LINC_cmdMemory_t dataBytes;
  
  /* Get values from internal transmission buffer */
  LINC_GetMessage(LINC_CMD_MEMORY, (uint8_t*)&dataBytes, LINC_CMD_MEMORY_LEN);
  
  return (dataBytes.selectedMemory);
}


/**
 * @brief This function gets the generic defect signal from CMD_Memory_LIN message
 * @return The value of the signal
 */
LINC_PanelDefect_t LINP_getGenericDefect(void)
{
  LINC_cmdMemory_t dataBytes;
  
  /* Get values from internal transmission buffer */
  LINC_GetMessage(LINC_CMD_MEMORY, (uint8_t*)&dataBytes, LINC_CMD_MEMORY_LEN);
  
  return (dataBytes.memoryGenDefect);
}


/**
 * @brief This function gets the generic defect signal from CMD_Memory_LIN message
 * @return The value of the signal
 */
LINC_ErrorBit_t LINP_getErrorBit(void)
{
  LINC_cmdMemory_t dataBytes;
  
  /* Get values from internal transmission buffer */
  LINC_GetMessage(LINC_CMD_MEMORY, (uint8_t*)&dataBytes, LINC_CMD_MEMORY_LEN);
  
  return (dataBytes.Error_Bit_Memory);
}


/**
 * @brief This function reports the status of DTC setting
 * @return The value of the signal
 */
PRES_Fault_t LINP_CheckSlaveOnline(void)
{
  return (Linp_PrivateData[NO_RESPONSE]);
}


/**
 * @brief This function reports the status of DTC setting
 * @return The value of the signal
 */
PRES_Fault_t LINP_CheckCommunication(void)
{
  return (Linp_PrivateData[ERROR_BIT_ACTIVE]);
}


/**
 * @brief Callback function for DTC recovering
 * @return The value of the signal
 */
void LINP_RxDataCbk(void)
{
  /* Reset Private data for DTC report */
  Linp_PrivateData[NO_RESPONSE] = PRES_NO_FAULT;
  
  /* Response from LIN Slave keyboard */
  Linp_ResponseFromSlave = TRUE;
}


/**
 * @brief This function checks if LIN Slave keyboard is online and answers to sent header
 * @return The value of the signal
 */
bool_t LINP_IsSlaveOnline(void)
{
  return (Linp_ResponseFromSlave);
}


/**
 * @brief Used to set/reset the BitError DTC
 * @return The value of the signal
 */
void LIN_SetBitErrorDTC(bool_t status)
{
  if (status)
  {
    /* Set private data for DTC report */
    Linp_PrivateData[ERROR_BIT_ACTIVE] = PRES_SIGNAL_ERROR;
  }
  else
  {
    /* Set private data for DTC report */
    Linp_PrivateData[ERROR_BIT_ACTIVE] = PRES_NO_FAULT;
  }
}


#endif /* end __LINP_IS_PRESENT__ */

/*______ E N D _____ (LINP_config.c) _________________________________________*/

