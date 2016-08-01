/*
*******************************************************************************
* Copyright(C) 2008, 2014 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for 78K0R/Fx3
* 16-Bit Single-Chip Microcontrollers
* Filename:	FE78K0R_CG_systeminit.c
* Abstract:	This file implements system initializing function.
* APIlib:	Applilet3 for 78K0R/Fx3 V3.01.00.01 [17 Jul 2014]
* Device:	uPD78F1833_64
* Compiler:	IAR Systems icc78k0r
* Creation date:	06/03/2015
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "FE78K0R_CG_macrodriver.h"
#include "FE78K0R_CG_system.h"
#include "FE78K0R_CG_port.h"
#include "FE78K0R_CG_int.h"
#include "FE78K0R_CG_serial.h"
#include "FE78K0R_CG_timer.h"
#include "FE78K0R_CG_wdt.h"
#include "DRVD_typedefs.h"


/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#define DELAY_24MHZ_OPTIM_HIGH_1MS 3400u

extern void            MEMD_RamTest(void);
extern DRVD_RStatus_t  MEMD_GetRamTestResult(void);

u16 __low_level_init(void);
void systeminit(void);

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function initializes every macro.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void systeminit(void)
{
  uint16_t WdCnt;
    
  CG_ReadResetSource();
  PORT_Init();
#ifdef __DEBUG__
  CLOCK_Init();
#endif
  WDT_Init();
  MEMD_RamTest();
  if (MEMD_GetRamTestResult() == MS_NOT_OK)
  {
    /* RAM test failed, wait for external watchdog reset */
    while(1)
    {
      /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
      for(WdCnt = 0U; WdCnt < DELAY_24MHZ_OPTIM_HIGH_1MS; WdCnt++)
      {
        NOP();
      }
      /* Refresh internal watchdog */
      WDT_Restart();
    }
  }
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function initializes hardware setting.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
u16 __low_level_init(void)
{
  DI();
  systeminit();
  
  return MD_TRUE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
