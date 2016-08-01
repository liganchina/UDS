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
* Filename:	FE78K0R_CG_int.c
* Abstract:	This file implements device driver for INT module.
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
#include "FE78K0R_CG_int.h"

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
**	This function initializes INTP module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP_Init(void)
{
	EGP0 = _00_INTP_EGP_RESET_VALUE;
	EGN0 = _00_INTP_EGN_RESET_VALUE;
	PMK0 = 1U;	/* disable INTP0 operation */
	PIF0 = 0U;	/* clear INTP0 interrupt flag */
	/* Set INTP0 low priority */
	PPR10 = 1U;
	PPR00 = 1U;
	EGN0 = _01_INTP0_EDGE_FALLING_SEL;
	EGP0 = _01_INTP0_EDGE_RISING_SEL;
    	/* Set INTP0 pin */
	PM12 |= 0x01U;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function clears INTP0 interrupt flag and enables interrupt.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP0_Enable(void)
{
	PIF0 = 0U;	/* clear INTP0 interrupt flag */
	PMK0 = 0U;	/* enable INTP0 interrupt */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function disables INTP0 interrupt and clears interrupt flag.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void INTP0_Disable(void)
{
	PMK0 = 1U;	/* disable INTP0 interrupt */
	PIF0 = 0U;	/* clear INTP0 interrupt flag */
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
