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
* Filename:	FE78K0R_CG_timer_user.c
* Abstract:	This file implements device driver for TAU module.
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
#include "FE78K0R_CG_timer_user.h"
#include "FE78K0R_CG_timer.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTTM00 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
static uint16_t Tmrd_INTTM00_Isr(void);
#ifdef FOREGROUND_TASK_ENABLED
  static bool_t Tmrd_OffsetFgrnd;
  static uint16_t Tmrd_INTTM01_Isr(void);
#endif
static uint16_t Tmrd_INTTM16_Isr(void);


void TMRD_Init(void)
{
  /* Timer0 - Interval timer callbacks */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTTM00, (ISRD_EvtCbk_t)Tmrd_INTTM00_Isr);
#ifdef FOREGROUND_TASK_ENABLED
  Tmrd_OffsetFgrnd = FALSE;
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTTM01, (ISRD_EvtCbk_t)Tmrd_INTTM01_Isr);
#endif

  /* Timer 1 - PWM timer callbacks */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTTM16, (ISRD_EvtCbk_t)Tmrd_INTTM16_Isr);
}



void TMRD_EnableTimer(TMRD_Channel_t chan)
{
  if (chan == PWMD_CHAN_0)
  {
    TAU1_Channel6_Start();
  }
  else
  {
  }

}


void TMRD_DisbleTimer(TMRD_Channel_t chan)
{
  if (chan == PWMD_CHAN_0)
  {
    TAU1_Channel6_Stop();
  }
  else
  {
  }
}


void TMRD_ChangeDuty(TMRD_Channel_t chan, uint8_t duty)
{
  if (chan == PWMD_CHAN_0)
  {
    TAU1_Channel7_ChangeDuty((UCHAR)duty);
  }
  else
  {
  }
}

/***********************************************************************
* Function Name: Tmrd_INTTM00_Isr
* Description  : This function is INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
************************************************************************/
static uint16_t Tmrd_INTTM00_Isr(void)
{
  /* Call timer TM00 callback */
  TMRD_IsrCbkINTTM00()

  /* Compute and return the key by interrupt vector index */
  return( ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM00) );
}

/***********************************************************************
* Function Name: Tmrd_INTTM01_Isr
* Description  : This function is INTTM01 interrupt service routine.
* Arguments    : None
* Return Value : None
************************************************************************/
#ifdef FOREGROUND_TASK_ENABLED
static uint16_t Tmrd_INTTM01_Isr(void)
{
  /* Enable nested interrupt */
  EI();

  /* Call the callback after the initialization offset */
  if( Tmrd_OffsetFgrnd == TRUE )
  {
    /* Call timer TM01 callback */
    TMRD_IsrCbkINTTM01()
  }
  /* Notify offset of 50 us and reload the timer to 1 ms */
  else
  {
    Tmrd_OffsetFgrnd = TRUE;
    /* Set the foreground timer to 1 ms as backgournd task */
    TAU0_Channel1_ChangeTimerCondition(_5DBF_TAU_TDR00_VALUE);
  }  
  
  /* Compute and return the key by interrupt vector index */
  return( ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM01) );
}
#endif /* end FOREGROUND_TASK_ENABLED */


/***********************************************************************
* Function Name: Tmrd_INTTM16_Isr
* Description  : This function is INTTM16 interrupt service routine.
* Arguments    : None
* Return Value : None
************************************************************************/
static uint16_t Tmrd_INTTM16_Isr(void)
{
  /* Call timer TM16 callback */
  TMRD_IsrCbkINTTM16()

  /* Compute and return the key by interrupt vector index */
  return( ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM16) );
}


