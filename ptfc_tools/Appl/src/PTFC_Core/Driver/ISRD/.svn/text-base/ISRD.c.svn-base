/**
 * @file ISRD.c
 * @brief Interrupt Service Routine Driver: source code of ISR module 
 * for driver layer.
 * @n The main module features/services are:
 * @li Mapping of all uC physical interrupts
 * @li ISR callback vector (RAM area dedicated)
 * @li API to set any function as ISR callback for a specific interrupt
 * @li RAM protection for re-addressing from physical ISR to ISR callback
 * @li WARNING: This module MUST BE COMPILED with HIGH OPTIMIZATION
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

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ISRD.h"

/*_____ L O C A L - D E F I N E ______________________________________________*/

#ifdef __DEBUG__
  /* Multiple interrupts for a single interrupt vector */
  #define ISRD_INTCSI11_INTIIC11_vect       (INTCSI11_vect)
  #define ISRD_INTKR_INTP6_vect             (INTKR_vect)
  #define ISRD_INTIIC20_INTST2_vect         (INTIIC20_vect)
#endif /* end __DEBUG__ */

/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/** Lookup table cointaining the ISR callbacks */
#pragma dataseg = ISR_CBK
  static __no_init ISRD_EvtCbk_t Isrd_CbkTable[ISRD_VECTOR_NMB];
#pragma dataseg = default


/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/

#ifdef __DEBUG__
  static void Isrd_ActuateRecovery(void);
#endif /* end __DEBUG__ */

/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/**
 * @brief Initialization routine for Interrupt Service Routine module
 * of the driver layer.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ISRD_Init(void)
{
  /* Clear the ISR cbk lookup table */
  memset(Isrd_CbkTable, 0U, (sizeof(ISRD_EvtCbk_t)*ISRD_VECTOR_NMB));
}

/**
 * @brief This routine store, for a specific index linked to a specific interrupt,
 * the ISR callback in a lookup table. If in the position selected yet exist a 
 * callback the routine will notify the error.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] VectorIdx: Index for all interrupt vectors present in the micro.
 *             The indexes are described by enumerative type ISRD_VectorIdx_t.
 * @param [in] Cbk: Callback address to set for a specific interrupt. This
 *             parameter is a function-pointer of type ISRD_EvtCbk_t.
 * @param [out] None
 * @return bool_t
 * @retval FALSE The ISR callback storage is failed.
 * @retval TRUE The ISR callback storage is OK.
 */
bool_t ISRD_SetEvtCbk(ISRD_VectorIdx_t VectorIdx, ISRD_EvtCbk_t Cbk)
{
  /* Setup status */
  bool_t SetSts = FALSE;

  /* Only if there is no cbk configured... */
  if( Isrd_CbkTable[VectorIdx] == NULL )
  {
    /* ...store the driver module callback in the cbk lookup table */
    Isrd_CbkTable[VectorIdx] = Cbk;

    /* Notify the correct setup */
    SetSts = TRUE;
  }
  else
  {
    /* Notify the error */
    SetSts = FALSE;
  }
  
  return (SetSts);
}

#ifdef __DEBUG__
/**
 * @brief Recovery routine used in case of inconsistence from key computed by
 * the physical callback and the driver callback.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Isrd_ActuateRecovery(void)
{
  /* If the RAM is in crash and if the uC don't kill, 
     this recovery actuate an HW reset */
  LPMS_HwReset();
}
#endif /* end __DEBUG__ */

#ifdef __DEBUG__
/**
 * @brief Physical ISR for INTWDTI_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy. 
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTWDTI_vect
__interrupt void ISRD_INTWDTI(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTWDTI] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTWDTI]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTWDTI) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLVI_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLVI_vect
__interrupt void ISRD_INTLVI(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLVI] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLVI]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLVI) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP0_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP0_vect
__interrupt void ISRD_INTP0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP1_vect
__interrupt void ISRD_INTP1(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP2_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP2_vect
__interrupt void ISRD_INTP2(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP2] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP2]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP2) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP3_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP3_vect
__interrupt void ISRD_INTP3(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP3] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP3]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP3) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP4_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP4_vect
__interrupt void ISRD_INTP4(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP4] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP4]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP4) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP5_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP5_vect
__interrupt void ISRD_INTP5(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP5] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP5]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP5) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTCLM_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTCLM_vect
__interrupt void ISRD_INTCLM(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTCLM] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTCLM]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCLM) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTCSI00_vect. This routine is 
 * stored in ROM to bank1. It check in the array Isrd_CbkTable the callback 
 * presence for this interrupt. If there is a callback routine, call it and check 
 * its consistence by an simple alghoritm computed by ISRD_ComputeCbkCheck routine. 
 * In case of SRAM corruption will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 3  /* CC - not change - dedicated bank for nested management */
#pragma vector = INTCSI00_vect
__interrupt void ISRD_INTCSI00(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTCSI00] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTCSI00]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCSI00) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTCSI01_vect. This routine is 
 * stored in ROM to bank1. It check in the array Isrd_CbkTable the callback 
 * presence for this interrupt. If there is a callback routine, call it and check 
 * its consistence by an simple alghoritm computed by ISRD_ComputeCbkCheck routine. 
 * In case of SRAM corruption will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTCSI01_vect
__interrupt void ISRD_INTCSI01(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTCSI01] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTCSI01]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCSI01) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTDMA0_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTDMA0_vect
__interrupt void ISRD_INTDMA0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTDMA0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTDMA0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTDMA0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTDMA1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTDMA1_vect
__interrupt void ISRD_INTDMA1(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTDMA1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTDMA1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTDMA1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTWUTM_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTWUTM_vect
__interrupt void ISRD_INTWUTM(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTWUTM] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTWUTM]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTWUTM) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTFL_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTFL_vect
__interrupt void ISRD_INTFL(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTFL] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTFL]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTFL) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLT0_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLT0_vect
__interrupt void ISRD_INTLT0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLT0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLT0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLT0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLR0_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLR0_vect
__interrupt void ISRD_INTLR0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLR0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLR0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLR0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLS0_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLS0_vect
__interrupt void ISRD_INTLS0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLS0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLS0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLS0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTPLR0_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTPLR0_vect
__interrupt void ISRD_INTPLR0(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTPLR0] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTPLR0]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPLR0) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTP8_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#if (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
    (DRVD_UC_PACKAGE == DRVD_100_PIN)
#pragma bank = 1
#pragma vector = INTP8_vect
__interrupt void ISRD_INTP8(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP8] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP8]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP8) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}
#endif /* (DRVD_UC_PACKAGE == DRVD_80_PIN)||(DRVD_UC_PACKAGE == DRVD_100_PIN) */

/**
 * @brief Physical ISR for INTTM00_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM00_vect
__interrupt void ISRD_INTTM00(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM00] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM00]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM00) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM01_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 2  /* CC - not change - dedicated bank for nested management */
#pragma vector = INTTM01_vect
__interrupt void ISRD_INTTM01(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM01] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM01]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM01) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM02_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM02_vect
__interrupt void ISRD_INTTM02(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM02] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM02]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM02) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM03_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM03_vect
__interrupt void ISRD_INTTM03(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM03] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM03]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM03) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTAD_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTAD_vect
__interrupt void ISRD_INTAD(void)
{
	/* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTAD] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTAD]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTAD) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLT1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLT1_vect
__interrupt void ISRD_INTLT1(void)
{
	/* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLT1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLT1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLT1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLR1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLR1_vect
__interrupt void ISRD_INTLR1(void)
{
	/* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLR1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLR1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLR1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTLS1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTLS1_vect
__interrupt void ISRD_INTLS1(void)
{
	/* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTLS1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTLS1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLS1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTPLR1_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTPLR1_vect
__interrupt void ISRD_INTPLR1(void)
{
	/* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTPLR1] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTPLR1]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPLR1) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTCSI10_vect. This routine is 
 * stored in ROM to bank1. It check in the array Isrd_CbkTable the callback 
 * presence for this interrupt. If there is a callback routine, call it and check 
 * its consistence by an simple alghoritm computed by ISRD_ComputeCbkCheck routine. 
 * In case of SRAM corruption will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTCSI10_vect
__interrupt void ISRD_INTCSI10(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTCSI10] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTCSI10]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCSI10) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for ISRD_INTCSI11_INTIIC11_vect. This routine is stored
 * in ROM to bank1. It check in the array Isrd_CbkTable the callback presence
 * for this interrupt. If there is a callback routine, call it and check its
 * consistence by an simple alghoritm computed by ISRD_ComputeCbkCheck routine.
 * In case of SRAM corruption will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#if (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
    (DRVD_UC_PACKAGE == DRVD_100_PIN)
#pragma bank = 1
#pragma vector = ISRD_INTCSI11_INTIIC11_vect
__interrupt void ISRD_INTCSI11_INTIIC11(void)
{
	/* Check the callback presence */
	if( (Isrd_CbkTable[ISRD_VECTOR_INTCSI11] != NULL) &&
	    (Isrd_CbkTable[ISRD_VECTOR_INTIIC11] == NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTCSI11]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCSI11) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	/* Check the callback presence */
	else if( (Isrd_CbkTable[ISRD_VECTOR_INTCSI11] == NULL) &&
	         (Isrd_CbkTable[ISRD_VECTOR_INTIIC11] != NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTIIC11]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTIIC11) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	else
	{
	  /* do nothing */
	}
}
#endif /* (DRVD_UC_PACKAGE == DRVD_80_PIN)||(DRVD_UC_PACKAGE == DRVD_100_PIN) */

/**
 * @brief Physical ISR for INTTM04_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM04_vect
__interrupt void ISRD_INTTM04(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM04] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM04]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM04) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM05_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM05_vect
__interrupt void ISRD_INTTM05(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM05] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM05]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM05) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM06_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM06_vect
__interrupt void ISRD_INTTM06(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM06] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM06]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM06) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM07_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM07_vect
__interrupt void ISRD_INTTM07(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM07] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM07]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM07) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for ISRD_INTKR_INTP6_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = ISRD_INTKR_INTP6_vect
__interrupt void ISRD_INTKR_INTP6(void)
{
	/* Check the callback presence */
	if( (Isrd_CbkTable[ISRD_VECTOR_INTKR] != NULL) &&
	    (Isrd_CbkTable[ISRD_VECTOR_INTP6] == NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTKR]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTKR) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	/* Check the callback presence */
	else if( (Isrd_CbkTable[ISRD_VECTOR_INTKR] == NULL) &&
	         (Isrd_CbkTable[ISRD_VECTOR_INTP6] != NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP6]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP6) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	else
	{
	  /* do nothing */
	}
}

/**
 * @brief Physical ISR for INTP7_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTP7_vect
__interrupt void ISRD_INTP7(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTP7] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTP7]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP7) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTC0ERR_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTC0ERR_vect
__interrupt void ISRD_INTC0ERR(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTC0ERR] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTC0ERR]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0ERR) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTC0WUP_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTC0WUP_vect
__interrupt void ISRD_INTC0WUP(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTC0WUP] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTC0WUP]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0WUP) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTC0REC_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTC0REC_vect
__interrupt void ISRD_INTC0REC(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTC0REC] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTC0REC]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0REC) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTC0TRX_vect. This routine is stored in ROM to
 * bank1. It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTC0TRX_vect
__interrupt void ISRD_INTC0TRX(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTC0TRX] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTC0TRX]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0TRX) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM10_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM10_vect
__interrupt void ISRD_INTTM10(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM10] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM10]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM10) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM11_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM11_vect
__interrupt void ISRD_INTTM11(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM11] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM11]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM11) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM12_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM12_vect
__interrupt void ISRD_INTTM12(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM12] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM12]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM12) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM13_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM13_vect
__interrupt void ISRD_INTTM13(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM13] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM13]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM13) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTMD_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTMD_vect
__interrupt void ISRD_INTMD(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTMD] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTMD]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTMD) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for ISRD_INTIIC20_INTST2_vect. This routine is stored in ROM
 * to bank1. It check in the array Isrd_CbkTable the callback presence for this 
 * interrupt. If there is a callback routine, call it and check its consistence 
 * by an simple alghoritm computed by ISRD_ComputeCbkCheck routine. In case of
 * SRAM corruption will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = ISRD_INTIIC20_INTST2_vect
__interrupt void ISRD_INTIIC20_INTST2(void)
{
	/* Check the callback presence */
	if( (Isrd_CbkTable[ISRD_VECTOR_INTIIC20] != NULL) &&
	    (Isrd_CbkTable[ISRD_VECTOR_INTST2] == NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTIIC20]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTIIC20) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	/* Check the callback presence */
	else if( (Isrd_CbkTable[ISRD_VECTOR_INTIIC20] == NULL) &&
	         (Isrd_CbkTable[ISRD_VECTOR_INTST2] != NULL) )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTST2]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTST2) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
	else
	{
	  /* do nothing */
	}
}

/**
 * @brief Physical ISR for INTSR2_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTSR2_vect
__interrupt void ISRD_INTSR2(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTSR2] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTSR2]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTSR2) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTPR2_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTPR2_vect
__interrupt void ISRD_INTPR2(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTPR2] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTPR2]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPR2) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM14_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM14_vect
__interrupt void ISRD_INTTM14(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM14] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM14]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM14) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM15_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM15_vect
__interrupt void ISRD_INTTM15(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM15] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM15]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM15) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM16_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM16_vect
__interrupt void ISRD_INTTM16(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM16] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM16]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM16) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM17_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM17_vect
__interrupt void ISRD_INTTM17(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM17] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM17]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM17) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM20_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM20_vect
__interrupt void ISRD_INTTM20(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM20] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM20]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM20) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM21_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM21_vect
__interrupt void ISRD_INTTM21(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM21] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM21]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM21) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM22_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM22_vect
__interrupt void ISRD_INTTM22(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM22] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM22]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM22) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM23_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTTM23_vect
__interrupt void ISRD_INTTM23(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM23] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM23]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM23) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTTM25_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#if (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
    (DRVD_UC_PACKAGE == DRVD_100_PIN)
#pragma bank = 1
#pragma vector = INTTM25_vect
__interrupt void ISRD_INTTM25(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM25] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM25]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM25) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}
#endif /* (DRVD_UC_PACKAGE == DRVD_80_PIN)||(DRVD_UC_PACKAGE == DRVD_100_PIN) */

/**
 * @brief Physical ISR for INTTM27_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#if (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
    (DRVD_UC_PACKAGE == DRVD_100_PIN)
#pragma bank = 1
#pragma vector = INTTM27_vect
__interrupt void ISRD_INTTM27(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTTM27] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTTM27]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM27) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}
#endif /* (DRVD_UC_PACKAGE == DRVD_80_PIN)||(DRVD_UC_PACKAGE == DRVD_100_PIN) */

/**
 * @brief Physical ISR for INTDMA2_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTDMA2_vect
__interrupt void ISRD_INTDMA2(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTDMA2] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTDMA2]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTDMA2) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for INTDMA3_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 1
#pragma vector = INTDMA3_vect
__interrupt void ISRD_INTDMA3(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_INTDMA3] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_INTDMA3]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_INTDMA3) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}

/**
 * @brief Physical ISR for BRK_I_vect. This routine is stored in ROM to bank1.
 * It check in the array Isrd_CbkTable the callback presence for this interrupt.
 * If there is a callback routine, call it and check its consistence by an simple 
 * alghoritm computed by ISRD_ComputeCbkCheck routine. In case of SRAM corruption
 * will be applied a recovery strategy.
 * The time from physical ISR to sw one is 12 Tck.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#pragma bank = 2
#pragma vector = BRK_I_vect
__interrupt void ISRD_BRK_I(void)
{
  /* Check the callback presence */
	if( Isrd_CbkTable[ISRD_VECTOR_BRK_I] != NULL )
	{
	  /* Match the previous keys for consistence check */
	  if( Isrd_CbkTable[ISRD_VECTOR_BRK_I]() != 
	      ISRD_ComputeCbkCheck(ISRD_VECTOR_BRK_I) )
	  {
	    /* Call the recovey routine in case of incosistence */
	    Isrd_ActuateRecovery();
	  }
	}
}
#endif /* end __DEBUG__ */

/*_____ L O C A L - F U N C T I O N S ________________________________________*/
  

/*_____ E N D _____ (ISRD.c) _________________________________________________*/
