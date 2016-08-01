/******************************************************************************/
/** @file       PWMC.c                                                        */
/** @title      Pulse Width Modulation Control                                */
/** @brief      PWM module for control layer.                                 */
/** @date       02/12/2014                                                    */
/** @author     Mastrodonato Matteo                                           */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 02/12/2014 0.1  MM      First draft
|-----------------------------------------------------------------------------
|            1.0  MM      First release
|-----------------------------------------------------------------------------
*/

#ifndef __PWMC_H
#define __PWMC_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "CTRL_if.h"
#include "MCAL.h"

/* Module inhibition filter */
#ifdef __PWMC_IS_PRESENT__

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum PWMC_pwmType_e
{
  PWMC_HW,
  PWMC_SW,
}PWMC_PwmType_t;


typedef struct PWMC_HwCfgTable_s
{
  uint8_t            CMD_CHAN;
  uint8_t            FBK_CHAN;
  CTRL_DriverType_t  DRIVER_TYPE;
  uint8_t            MIN_DUTY;      /* Min duty for diagnosis verification */
}PWMC_HwCfgTable_t;

typedef struct PWMC_SwCfgTable_s
{
  DOIFC_Handle_t     CMD_CHAN;
  uint16_t           PERIOD;
  uint8_t            MIN_CMD;      /* Min command for diagnosis verification */
}PWMC_SwCfgTable_t;


/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

#define PWMC_2MS    0x02U
#define PWMC_4MS    0x04U
#define PWMC_8MS    0x08U
#define PWMC_16MS   0x10U
#define PWMC_32MS   0x20U
#define PWMC_64MS   0x40U

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

extern const PWMC_HwCfgTable_t PWMC_HwCfgTable[PWMC_HW_HDL_MAX - PWMC_SW_HDL_MAX];
extern const PWMC_SwCfgTable_t PWMC_SwCfgTable[PWMC_SW_HDL_MAX];

/* Module inhibition filter */
#endif /*__PWMC_IS_PRESENT__ */

#endif  /* end __PWMC_H */

/*_____ E N D _____ (PWMC.h) _________________________________________________*/
