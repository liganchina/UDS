/**
 * @file LINC_config.c
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
| MAM          Matteo Mastrodonato       Bitron S.p.A.
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
| 27/06/2015 1.0  MAM     Configuration of message map for NAG/NAP F151M.
|                         LDF v1.1.
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINC.h"
#include "LINC_config.h"

/* Module inhibition filter */
#ifdef __LINC_IS_PRESENT__

/*______ G L O B A L - D A T A _______________________________________________*/

/* Definition of single frames for all the message map */


/* FRAME CMD_Authorizations */
static uint8_t Linc_cmdAuthDataBuffer[LINC_CMD_AUTH_LEN] =
                                                  {0x00} ;  /* Data buffer */


static bool              Linc_cmdAuthRequest = FALSE;    /* Request frame (only sporadic frame ) */
static LINC_FrameError_t Linc_cmdAuthErrorType;          /* Frame error (type) */
static uint8_t           Linc_cmdAuthErrorCount = 0u;    /* Frame error (count) */

/* Frame structure */
const Linc_lin_frame_st_t Linc_cmdAuth =
{
  0x10U,                       /* ID number of the frame */
  SOURCE_PUBLISHER,            /* Direction of communication */
  Linc_cmdAuthDataBuffer,      /* Data buffer */
  LINC_CMD_AUTH_LEN,           /* Length of data buffer */
  FR_TYPE_UNCONDITIONAL,       /* Frame type */
  &Linc_cmdAuthRequest,        /* Request of sporadic frame */
  0x00U,                       /* Priority level of sporadic frame */
  &Linc_cmdAuthErrorType,      /* Frame error type */
  &Linc_cmdAuthErrorCount,     /* Frame error count */
  NULL                         /* Indication callback */
};


/* FRAME CMD MEMORY */
static uint8_t Linc_cmdMemoryDataBuffer[LINC_CMD_MEMORY_LEN] =
                                             {0x00}; /* Data buffer */

static bool              Linc_cmdMemoryRequest = FALSE;   /* Request frame (only sporadic frame ) */
static LINC_FrameError_t Linc_cmdMemoryErrorType;         /* Frame error (type) */
static uint8_t           Linc_cmdMemoryErrorCount = 0u;   /* Frame error (count) */

const Linc_lin_frame_st_t Linc_cmdMemory =
{
  0x1AU,                       /* ID number of the frame */
  SOURCE_RECEIVER,             /* Direction of communication */
  Linc_cmdMemoryDataBuffer,    /* Data buffer */
  LINC_CMD_MEMORY_LEN,         /* Length of data buffer */
  FR_TYPE_UNCONDITIONAL,       /* Frame type */
  &Linc_cmdMemoryRequest,      /* Request of sporadic frame */
  0x00U,                       /* Priority level of sporadic frame */
  &Linc_cmdMemoryErrorType,    /* Frame error type */
  &Linc_cmdMemoryErrorCount,   /* Frame error count */
  LINP_RxDataCbk               /* Indication callback */
};


/* FRAME 3C (GoToSleep request) */
static uint8_t Linc_Frame3CDataBuffer[LINC_FRAME_3C_LEN] = 
                    {0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; /* Data buffer */

static bool Linc_Frame3CSprRequest = FALSE;      /* Request frame (only sporadic frame ) */
static LINC_FrameError_t Linc_Frame3CErrorType;  /* Frame error (type) */
static uint8_t Linc_Frame3CErrorCount = 0u;      /* Frame error (count) */

/* Frame structure */
const Linc_lin_frame_st_t Linc_Frame3C =
{
  0x3CU,                      /* ID number of the frame */
  SOURCE_PUBLISHER,           /* Direction of communication */
  Linc_Frame3CDataBuffer,     /* Data buffer */
  LINC_FRAME_3C_LEN,          /* Length of data buffer */
  FR_TYPE_UNCONDITIONAL,      /* Frame type */
  &Linc_Frame3CSprRequest,    /* Request of sporadic frame */
  0x00U,                      /* Priority level of sporadic frame */
  &Linc_Frame3CErrorType,     /* Frame error type */
  &Linc_Frame3CErrorCount,    /* Frame error count */
  NULL                        /* Indication callback */
};


/* MESSAGE MAP */
const Linc_lin_frame_st_t * Linc_MessageMap[LINC_MESSAGE_MAP_LEN] =
{
  &Linc_cmdAuth,
  &Linc_cmdMemory,
  &Linc_Frame3C, /* GoTo Sleep Cmd - !!! DO NOT REMOVE !!! */
};



/**
 * @brief Wrapper routine for electrical diagnosis on LIN bus.
 * It can be used to set/reset the related DTC ad presentation
 * layer.
 * @param [in]  dummy: parameter not used.
 *              Only to be copliant to FVMP prototype.
 * @param [out] None
 *
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT: no electrical fault detected
 * @retval CTRL_SHORT_TO_GND: short circuit to ground
 * @retval CTRL_SHORT_TO_BAT: short circuit to vbatt
 *
 */
CTRL_Fault_t LINC_GetEltDiag(uint8_t dummy)
{
  CTRL_Fault_t valueReturn;

  /* ********************** Short circuit detection *********************/
  if(LINC_GetDiag(UARTD_CHN_HND) == UARTD_SHORT_CIRCUIT_LOW)
  {
    /* Set ground short circuit */
    valueReturn = CTRL_SHORT_TO_GND;
  }
  else if(LINC_GetDiag(UARTD_CHN_HND) == UARTD_SHORT_CIRCUIT_HIGH)
  {
    /* Set Vbat short circuit */
    valueReturn = CTRL_SHORT_TO_BAT;
  }
  else
  {
    valueReturn = CTRL_NO_FAULT;
  }

  return valueReturn;
}


#endif /* end __LINC_IS_PRESENT__ */

/*______ E N D _____ (LINC_config.c) _________________________________________*/

