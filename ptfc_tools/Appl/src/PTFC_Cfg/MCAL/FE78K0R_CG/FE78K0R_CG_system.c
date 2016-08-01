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
* Filename:	FE78K0R_CG_system.c
* Abstract:	This file implements device driver for System module.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

MD_STATUS gPllStatus1;	/* PLL lock state 1 */
MD_STATUS gPllStatus2;	/* PLL lock state 2 */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the clock generator.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CLOCK_Init(void)
{
	USHORT i;
	UCHAR temp_stabset, temp_stabwait;

	gPllStatus1 = MD_OK;
	gPllStatus2 = MD_OK;
	/* Set fMX */
	CMC = _40_CG_HISYS_OSC | _00_CG_SYSOSC_UNDER10M | _00_CG_SUB_PORT;
	OSTS = _05_CG_OSCSTAB_SEL15;
	GUARD |= _01_CG_CSC_ENWR;
	MSTOP = 0U;
	temp_stabset = _FC_CG_OSCSTAB_STA15;
	do
	{
		temp_stabwait = OSTC;
		temp_stabwait &= temp_stabset;
	}
	while (temp_stabwait != temp_stabset);
	/* Set fMAIN */
	DI();
	OSMC = _04_CG_FCLK_OVER20M | _01_CG_FCLK_OVER10M;
	NOP();
	NOP();
	/* CC - Not Uncommented - never. In this routine and in the next 
	        on the interrupts must be disabled. */
#if 0
	EI();
#endif
	MCM0 = 1U;
	/* Set fPLL */
	GUARD |= _02_CG_PLLCTL_ENWR;
	PLLCTL = _40_CG_PLLLOCKUP_SEL1 | _00_CG_FPLLO_DIV1 | _10_CG_FPLLI_DIV2;
	PLLON = 1U;
	/* Change the waiting time according to the system */
	for( i=0U; i<=CG_LOCK_WAITTIME; i++ )
	{
		NOP();
	}
	if (LOCK == 0U)
	{
		gPllStatus1 = MD_ERROR;
	}
	else
	{
		SELPLL = 1U;
	}
	if (SELPLLS == 0U)
	{
		gPllStatus2 = MD_ERROR;
	}
	GUARD &= (UCHAR)~_02_CG_PLLCTL_ENWR;
	/* Set fSUB */
	XTSTOP = 1U;
	/* Set fCLK */
	CSS = 0U;
	CKC &= (UCHAR)~_07_CG_CPUCLK;
	CKC |= _00_CG_CPUCLK_MAIN0;
	/* Set fIH */
	HIOSTOP = 1U;
	GUARD &= (UCHAR)~_01_CG_CSC_ENWR;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
