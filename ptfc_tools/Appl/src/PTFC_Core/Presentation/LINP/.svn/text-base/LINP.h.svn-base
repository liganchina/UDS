/**
 * @file LINP.h
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

#ifndef __LINP_H
#define __LINP_H

#include "CTRL_if.h"
#include "PRES_if.h"
#include "LINP_config.h"
#include "LINP_cbk.h"

/* #include "LINP_cbk.h" */

/* Module inhibition filter */
#ifdef __LINP_IS_PRESENT__


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Frame structure */
typedef struct
{
  LINC_MessageMap_t  LinId;                    /* Frame Id */
  uint16_t           SlotTimeMs;               /* Slot time (ms), i.e. time between frame */
  uint16_t           TimeOutMs;                /* Time to trigger the "no response error" */
  uint16_t           *TimeOutCounterMs;        /* Counter for timeout */
  bool               *ErrorFrameCkbEnable;     /* Recovery callback enable */
  void               (*ErrorFrameCbk)(void);   /* Callback for time out occurred */
} Linp_message_st_t;

/* Schedule table structure */
typedef struct
{
  const Linp_message_st_t     *Table; /* Pointer to schedule table */
  uint8_t                     Len;    /* Number of frame into schedule table */
} Linp_sched_tab_st_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/* Entire Schedule Table */
extern const Linp_sched_tab_st_t Linp_SchTab[LINP_SCHED_TAB_NUM];


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

#endif /* end __LINP_IS_PRESENT__ */

#endif  // __LINP_H
