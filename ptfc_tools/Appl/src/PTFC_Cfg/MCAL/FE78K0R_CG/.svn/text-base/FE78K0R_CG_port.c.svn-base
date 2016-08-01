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
* Filename:	FE78K0R_CG_port.c
* Abstract:	This file implements device driver for PORT module.
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
#include "FE78K0R_CG_port.h"


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
**	This function initializes the Port I/O.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_Init(void)
{
	P0 = _00_Pn0_OUTPUT_0;
#ifndef __DEBUG__
	P1 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0;
#else   
	P1 = _00_Pn0_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0;
#endif
	P3 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0;
	P4 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
	P5 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
	P6 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _08_Pn3_OUTPUT_1;
	P7 = _00_Pn0_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
	P12 = _00_Pn5_OUTPUT_0;
	P13 = _00_Pn0_OUTPUT_0;
	P14 = _00_Pn0_OUTPUT_0;
	PU1 = _01_PUn0_PULLUP_ON | _02_PUn1_PULLUP_ON;
	PM0 = _00_PMn0_MODE_OUTPUT | _FE_PM0_DEFAULT;
#ifndef __DEBUG__
	PM1 = _01_PMn0_MODE_INPUT  | _02_PMn1_MODE_INPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
#else
  PM1 = _00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
#endif
	PM3 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _F8_PM3_DEFAULT;
	PM4 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM4_DEFAULT;
	PM5 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM5_DEFAULT;
	PM6 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM6_DEFAULT;
	PM7 = _00_PMn0_MODE_OUTPUT | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
	PM9 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _20_PMn5_NOT_USE | _40_PMn6_MODE_INPUT | _80_PM9_DEFAULT;
	PM12 = _01_PMn0_NOT_USE | _00_PMn5_MODE_OUTPUT | _DE_PM12_DEFAULT;
	PM14 = _00_PMn0_MODE_OUTPUT | _FE_PM14_DEFAULT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
