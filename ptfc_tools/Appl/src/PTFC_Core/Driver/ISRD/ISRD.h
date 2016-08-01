/**
 * @file ISRD.h
 * @brief Interrupt Service Routine Driver: private interface of ISR module 
 * for driver layer.
 * @n The main module features/services are:
 * @li Mapping of all uC physical interrupts
 * @li ISR callback vector (RAM area dedicated)
 * @li API to set any function as ISR callback for a specific interrupt
 * @li RAM protection for re-addressing from physical ISR to ISR callback
 * </ul>
 *
 * @version 1.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 14 july 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 14/07/14   0.1  CC      First draft not tested for RL78 - R5F10AGFLFB/F13
|-----------------------------------------------------------------------------
| 12/09/14   0.2  CC      Porting to 78K0R family - uC 78F1837_80
|-----------------------------------------------------------------------------
| 20/09/14   1.0  CC      First official release
|-----------------------------------------------------------------------------
| 17/11/14   1.1  CC      Porting to 78K0R family
|-----------------------------------------------------------------------------
*/

#ifndef __ISRD_H
#define __ISRD_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "DRVD_if.h"

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ F U N C T I O N S - P R O T O T Y P E S ______________________________*/
  
__interrupt void ISRD_INTWDTI(void);
__interrupt void ISRD_INTLVI(void);
__interrupt void ISRD_INTP0(void);
__interrupt void ISRD_INTP1(void);
__interrupt void ISRD_INTP2(void);
__interrupt void ISRD_INTP3(void);
__interrupt void ISRD_INTP4(void);
__interrupt void ISRD_INTP5(void);
__interrupt void ISRD_INTCLM(void);
__interrupt void ISRD_INTCSI00(void);
__interrupt void ISRD_INTCSI01(void);
__interrupt void ISRD_INTDMA0(void);
__interrupt void ISRD_INTDMA1(void);
__interrupt void ISRD_INTWUTM(void);
__interrupt void ISRD_INTFL(void);
__interrupt void ISRD_INTLT0(void);
__interrupt void ISRD_INTLR0(void);
__interrupt void ISRD_INTLS0(void);
__interrupt void ISRD_INTPLR0(void);
__interrupt void ISRD_INTP8(void);
__interrupt void ISRD_INTTM00(void);
__interrupt void ISRD_INTTM01(void);
__interrupt void ISRD_INTTM02(void);
__interrupt void ISRD_INTTM03(void);
__interrupt void ISRD_INTAD(void);
__interrupt void ISRD_INTLT1(void);
__interrupt void ISRD_INTLR1(void);
__interrupt void ISRD_INTLS1(void);
__interrupt void ISRD_INTPLR1(void);
__interrupt void ISRD_INTCSI10(void);
__interrupt void ISRD_INTCSI11_INTIIC11(void);
__interrupt void ISRD_INTTM04(void);
__interrupt void ISRD_INTTM05(void);
__interrupt void ISRD_INTTM06(void);
__interrupt void ISRD_INTTM07(void);
__interrupt void ISRD_INTKR_INTP6(void);
__interrupt void ISRD_INTP7(void);
__interrupt void ISRD_INTC0ERR(void);
__interrupt void ISRD_INTC0WUP(void);
__interrupt void ISRD_INTC0REC(void);
__interrupt void ISRD_INTC0TRX(void);
__interrupt void ISRD_INTTM10(void);
__interrupt void ISRD_INTTM11(void);
__interrupt void ISRD_INTTM12(void);
__interrupt void ISRD_INTTM13(void);
__interrupt void ISRD_INTMD(void);
__interrupt void ISRD_INTIIC20_INTST2(void);
__interrupt void ISRD_INTSR2(void);
__interrupt void ISRD_INTPR2(void);
__interrupt void ISRD_INTTM14(void);
__interrupt void ISRD_INTTM15(void);
__interrupt void ISRD_INTTM16(void);
__interrupt void ISRD_INTTM17(void);
__interrupt void ISRD_INTTM20(void);
__interrupt void ISRD_INTTM21(void);
__interrupt void ISRD_INTTM22(void);
__interrupt void ISRD_INTTM23(void);
__interrupt void ISRD_INTTM25(void);
__interrupt void ISRD_INTTM27(void);
__interrupt void ISRD_INTDMA2(void);
__interrupt void ISRD_INTDMA3(void);
__interrupt void ISRD_BRK_I(void);


#endif /* end __ISRD_H */

/*_____ E N D _____ (ISRD.h) _________________________________________________*/
