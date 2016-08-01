/**
 * @file LINC.h
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

#ifndef __LINC_H
#define __LINC_H

#include "DRVD_if.h"
#include "CTRL_if.h"
#include "LINC_cbk.h"

/* Module inhibition filter */
#ifdef __LINC_IS_PRESENT__


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
/* Data source for a given frame */
typedef enum
{
  SOURCE_PUBLISHER,
  SOURCE_RECEIVER
} Linc_data_src_et;

/* Frame type */
typedef enum
{ 
  /* Carry signals and their frame identifiers are in the range 0 (zero) to 59 (0x3B) */
  FR_TYPE_UNCONDITIONAL = 0,
  /* Special message type which are supervised by the LIN master */    
  FR_TYPE_EVENT_TRIGGERED,                            
  /* Transmitted by the master as required, so a collision cannot occur */
  FR_TYPE_SPORADIC,                                   
  /* Carry diagnostic or configuration data and they always contain eight data bytes (60 (0x3C) or 61 (0x3D)) */
  FR_TYPE_DIAGNOSTIC,                                 
  FR_TYPE_MAX_NUM
} Linc_fr_type_et;


/* Lin frame structure */
typedef struct
{
  uint8_t           Id;                   /* ID number of the frame */
  Linc_data_src_et  DataSource;           /* Direction of communication */
  uint8_t           *DataBuff;            /* Data buffer */
  uint8_t           DataLen;              /* Length of data buffer */  
  Linc_fr_type_et   FrameType;            /* Frame type */   
  bool              *SprRequest;          /* Request of sporadic frame */
  uint8_t           SprPriority;          /* Priority level of sporadic frame */  
  LINC_FrameError_t *FrameError;          /* Frame error type */
  uint8_t           *FrameErrorCount;     /* Frame error count */
  void              (*IndCbk)(void);      /* Indication callback */
} Linc_lin_frame_st_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Timer timeout counts, used as parameter to restart timer */
#define LINC_TIMEOUT_INTB_COUNT   (F_CLK_MHZ*LINC_INTERBYTE_PER_US/TIM03_PRESC)
#define LINC_TIMEOUT_RESP_COUNT   (F_CLK_MHZ*LINC_RESPONSE_PER_US/TIM03_PRESC)
#define LINC_TIMEOUT_WAKEUP_COUNT (F_CLK_MHZ*LINC_WAKEUP_LEN_PER_US/TIM03_PRESC)
#define LINC_TIMEOUT_WAKEUPEXT_COUNT (F_CLK_MHZ*LINC_WAKEUP_EXT_PER_US/TIM03_PRESC)

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#endif /* end __LINC_IS_PRESENT__ */

#endif  // __LINC_H
