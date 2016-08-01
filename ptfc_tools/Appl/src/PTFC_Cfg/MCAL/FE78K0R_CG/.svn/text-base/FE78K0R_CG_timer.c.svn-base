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
* Filename:	FE78K0R_CG_timer.c
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
**	This function initializes the TAU0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Init(void)
{
	TAU0EN = 1U;		/* supply input clock */
	TPS0 = _0000_TAU_CKM0_FCLK_0 | _0040_TAU_CKM1_FCLK_4 | _0800_TAU_CKM2_FCLK_8 | _F000_TAU_CKM3_FCLK_15;
	/* Stop all channels */
	TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
	/* Mask channel 0 interrupt */
	TMMK00 = 1U;		/* disable INTTM00 interrupt */
	TMIF00 = 0U;		/* clear INTTM00 interrupt flag */
	/* Mask channel 1 interrupt */
	TMMK01 = 1U;		/* disable INTTM01 interrupt */
	TMIF01 = 0U;		/* clear INTTM01 interrupt flag */
	/* Set INTTM00 level 2 priority */
	TMPR100 = 1U;
	TMPR000 = 0U;
	/* Set INTTM01 low priority */
	TMPR101 = 1U;
	TMPR001 = 1U;
	/* Channel 0 used as interval timer */
	TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
	TDR00 = _5DBF_TAU_TDR00_VALUE;
	TOM0 &= ~_0001_TAU_CH0_OUTPUT_COMBIN;
	TOL0 &= ~_0001_TAU_CH0_OUTPUT_LEVEL_L;
	TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
	/* Channel 1 used as interval timer */
	TMR01 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
	TDR01 = _04AF_TAU_TDR01_VALUE;
	TOM0 &= ~_0002_TAU_CH1_OUTPUT_COMBIN;
	TOL0 &= ~_0002_TAU_CH1_OUTPUT_LEVEL_L;
	TOE0 &= ~_0002_TAU_CH1_OUTPUT_ENABLE;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel0_Start(void)
{
	TMIF00 = 0U;		/* clear INTTM00 interrupt flag */
	TMMK00 = 0U;		/* enable INTTM00 interrupt */
	TS0 |= _0001_TAU_CH0_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU0 channel 0 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel0_Stop(void)
{
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
	TMMK00 = 1U;		/* disable INTTM00 interrupt */
	TMIF00 = 0U;		/* clear INTTM00 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU0 channel 0 register value.
**
**  Parameters:
**	regvalue: value for data register
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel0_ChangeTimerCondition(USHORT regvalue)
{
	TDR00 = regvalue;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU0 channel 1 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel1_Start(void)
{
	TMIF01 = 0U;		/* clear INTTM01 interrupt flag */
	TMMK01 = 0U;		/* enable INTTM01 interrupt */
	TS0 |= _0002_TAU_CH1_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU0 channel 1 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel1_Stop(void)
{
	TT0 |= _0002_TAU_CH1_STOP_TRG_ON;
	TMMK01 = 1U;		/* disable INTTM01 interrupt */
	TMIF01 = 0U;		/* clear INTTM01 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU0 channel 1 register value.
**
**  Parameters:
**	regvalue: value for data register
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU0_Channel1_ChangeTimerCondition(USHORT regvalue)
{
	TDR01 = regvalue;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the TAU1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Init(void)
{
	TAU1EN = 1U;		/* supply input clock */
	TPS1 = _0000_TAU_CKM0_FCLK_0 | _0020_TAU_CKM1_FCLK_2 | _0400_TAU_CKM2_FCLK_4 | _F000_TAU_CKM3_FCLK_15;
	/* Stop all channels */
	TT1 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
	/* Mask channel 6 interrupt */
	TMMK16 = 1U;		/* disable INTTM16 interrupt */
	TMIF16 = 0U;		/* clear INTTM16 interrupt flag */
	/* Mask channel 7 interrupt */
	TMMK17 = 1U;		/* disable INTTM17 interrupt */
	TMIF17 = 0U;		/* clear INTTM17 interrupt flag */
	/* Set INTTM16 low priority */
	TMPR116 = 1U;
	TMPR016 = 1U;
	/* Set INTTM17 low priority */
	TMPR117 = 1U;
	TMPR017 = 1U;
	/* Channel 6 is used as master channel for PWM output function */
	TMR16 = _4000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_COMBINATION_MASTER | _0000_TAU_TRIGGER_SOFTWARE | _0001_TAU_MODE_PWM_MASTER;
	TDR16 = _EA5F_TAU_TDR16_VALUE;
	TOM1 &= ~_0040_TAU_CH6_OUTPUT_COMBIN;
	TOL1 &= ~_0040_TAU_CH6_OUTPUT_LEVEL_L;
	TOE1 &= ~_0040_TAU_CH6_OUTPUT_ENABLE;
	/* Channel 7 is used as slave channel for PWM output function */
	TMR17 = _4000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
	TDR17 = _7530_TAU_TDR17_VALUE;
	TOM1 |= _0080_TAU_CH7_OUTPUT_COMBIN;
	TOL1 &= ~_0080_TAU_CH7_OUTPUT_LEVEL_L;
	TO1 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
	TOE1 |= _0080_TAU_CH7_OUTPUT_ENABLE;
	/* Set TO17 pin */
	P7 &= 0xFDU;
	PM7 &= 0xFDU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts TAU1 channel 6 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel6_Start(void)
{
	TMIF16 = 0U;		/* clear INTTM16 interrupt flag */
	TMMK16 = 0U;		/* enable INTTM16 interrupt */
	TMIF17 = 0U;		/* clear INTTM17 interrupt flag */
	TMMK17 = 0U;		/* enable INTTM17 interrupt */
	TOE1 |= _0080_TAU_CH7_OUTPUT_ENABLE;
	TS1 |= _0040_TAU_CH6_START_TRG_ON | _0080_TAU_CH7_START_TRG_ON;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops TAU1 channel 6 counter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel6_Stop(void)
{
	TT1 |= _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
	TOE1 &= ~_0080_TAU_CH7_OUTPUT_ENABLE;
	TMMK16 = 1U;		/* disable INTTM16 interrupt */
	TMIF16 = 0U;		/* clear INTTM16 interrupt flag */
	TMMK17 = 1U;		/* disable INTTM17 interrupt */
	TMIF17 = 0U;		/* clear INTTM17 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes TAU1 channel 7 duty value when used as PWM slave channel.
**
**  Parameters:
**	ratio: duty value to change
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void TAU1_Channel7_ChangeDuty(UCHAR ratio)
{
	ULONG reg = 0U;
	
	if (ratio > 100U)
	{
		ratio = 100U;
	}
	reg = TDR16;
	reg = (reg + 1U) * ratio / 100U;
	TDR17 = (USHORT)reg;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
