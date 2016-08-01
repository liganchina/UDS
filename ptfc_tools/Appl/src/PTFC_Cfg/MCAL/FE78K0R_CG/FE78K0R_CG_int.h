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
* Filename:	FE78K0R_CG_int.h
* Abstract:	This file implements device driver for INT module.
* APIlib:	Applilet3 for 78K0R/Fx3 V3.01.00.01 [17 Jul 2014]
* Device:	uPD78F1833_64
* Compiler:	IAR Systems icc78k0r
* Creation date:	06/03/2015
*******************************************************************************
*/

#ifndef _MDINT_
#define _MDINT_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/

/*
	External Interrupt Rising Edge Enable Register (EGP)
*/
/* INTPn pin valid edge selection(EGPn) */
#define _00_INTP_EGP_RESET_VALUE		0x00U	/* external interrupt rising edge enable register value after reset */
#define _01_INTP0_EDGE_RISING_SEL		0x01U	/* rising edge selected for INTP0 pin */
#define _00_INTP0_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP0 pin */
#define _02_INTP1_EDGE_RISING_SEL		0x02U	/* rising edge selected for INTP1 pin */
#define _00_INTP1_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP1 pin*/
#define _04_INTP2_EDGE_RISING_SEL		0x04U	/* rising edge selected for INTP2 pin */
#define _00_INTP2_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP2 pin */
#define _08_INTP3_EDGE_RISING_SEL		0x08U	/* rising edge selected for INTP3 pin */
#define _00_INTP3_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_RISING_SEL		0x10U	/* rising edge selected for INTP4 pin */
#define _00_INTP4_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP4 pin */
#define _20_INTP5_EDGE_RISING_SEL		0x20U	/* rising edge selected for INTP5 pin */
#define _00_INTP5_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP5 pin */
#define _40_INTP6_EDGE_RISING_SEL		0x40U	/* rising edge selected for INTP6 pin */
#define _00_INTP6_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP6 pin */
#define _80_INTP7_EDGE_RISING_SEL		0x80U	/* rising edge selected for INTP7 pin */
#define _00_INTP7_EDGE_RISING_UNSEL		0x00U	/* rising edge not selected for INTP7 pin */

/*
	External Interrupt Falling Edge Enable Register (EGN)
*/
/* INTPn pin valid edge selection(EGNn) */
#define _00_INTP_EGN_RESET_VALUE		0x00U	/* external interrupt falling edge enable register value after reset */
#define _01_INTP0_EDGE_FALLING_SEL		0x01U	/* falling edge selected for INTP0 pin */
#define _00_INTP0_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP0 pin */
#define _02_INTP1_EDGE_FALLING_SEL		0x02U	/* falling edge selected for INTP1 pin */
#define _00_INTP1_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP1 pin */
#define _04_INTP2_EDGE_FALLING_SEL		0x04U	/* falling edge selected for INTP2 pin */
#define _00_INTP2_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP2 pin */
#define _08_INTP3_EDGE_FALLING_SEL		0x08U	/* falling edge selected for INTP3 pin */
#define _00_INTP3_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP3 pin */
#define _10_INTP4_EDGE_FALLING_SEL		0x10U	/* falling edge selected for INTP4 pin */
#define _00_INTP4_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP4 pin */
#define _20_INTP5_EDGE_FALLING_SEL		0x20U	/* falling edge selected for INTP5 pin */
#define _00_INTP5_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP5 pin */
#define _40_INTP6_EDGE_FALLING_SEL		0x40U	/* falling edge selected for INTP6 pin */
#define _00_INTP6_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP6 pin */
#define _80_INTP7_EDGE_FALLING_SEL		0x80U	/* falling edge selected for INTP7 pin */
#define _00_INTP7_EDGE_FALLING_UNSEL		0x00U	/* falling edge not selected for INTP7 pin */

/*
	Key Return Mode Register (KRM)
*/
/* Key interrupt mode control(KRMn) */
#define _00_KR_KRM_RESET_VALUE			0x00U	/* KRM value after reset */
#define _01_KR0_SIGNAL_DETECT_ON		0x01U	/* detect KR0 signal */
#define _00_KR0_SIGNAL_DETECT_OFF		0x00U	/* not detect KR0 signal */
#define _02_KR1_SIGNAL_DETECT_ON		0x02U	/* detect KR1 signal */        
#define _00_KR1_SIGNAL_DETECT_OFF		0x00U	/* not detect KR1 signal */
#define _04_KR2_SIGNAL_DETECT_ON		0x04U	/* detect KR2 signal */        
#define _00_KR2_SIGNAL_DETECT_OFF		0x00U	/* not detect KR2 signal */
#define _08_KR3_SIGNAL_DETECT_ON		0x08U	/* detect KR3 signal */        
#define _00_KR3_SIGNAL_DETECT_OFF		0x00U	/* not detect KR3 signal */
#define _10_KR4_SIGNAL_DETECT_ON		0x10U	/* detect KR4 signal */        
#define _00_KR4_SIGNAL_DETECT_OFF		0x00U	/* not detect KR4 signal */
#define _20_KR5_SIGNAL_DETECT_ON		0x20U	/* detect KR5 signal */        
#define _00_KR5_SIGNAL_DETECT_OFF		0x00U	/* not detect KR5 signal */
#define _40_KR6_SIGNAL_DETECT_ON		0x40U	/* detect KR6 signal */        
#define _00_KR6_SIGNAL_DETECT_OFF		0x00U	/* not detect KR6 signal */
#define _80_KR7_SIGNAL_DETECT_ON		0x80U	/* detect KR7 signal */        
#define _00_KR7_SIGNAL_DETECT_OFF		0x00U	/* not detect KR7 signal */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/


/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void INTP_Init(void);
void INTP0_Enable(void);
void INTP0_Disable(void);
/**
 * @brief Initialization routine for the external interrupt driver module
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void INTD_Init(void);
#endif
