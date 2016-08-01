/**
 * @file Driver.c
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the init function call of each module of Driver layer
 *
 * @see www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo MASTRODONATO       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 12/giu/13   0.1  MM       First draft
|-----------------------------------------------------------------------------
| 26/09/14    1.0  CC       Insert the routines DRVD_PseudoInit and 
|                           DRVD_PrPseudoWakeup for new power management done by
|                           LPMS module
|-----------------------------------------------------------------------------
| 
*/

#define DRVD_IF_OWNER

#include "DRVD_if.h"


/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void DRVD_Init(void)
{
/*____ DRVD layer Initialization ________________*/

  /* Interrupt Service Routine Driver initialization */
  ISRD_Init();

  /* MCAL Driver initialization */
  /* Timer 0 - Scheduler */
  TAU0_Init();
  TMRD_Init();
  /* Timer 1 - PWM */
  TAU1_Init();
  /* PWM feedback */
  INTP_Init();
  INTD_Init();
	/* Serial for EE */
  SAU0_Init();
  SPID_Init();
  
/* ADCD module inhibition filter */
#ifdef __ADCD_IS_PRESENT__
  /* Analog Digital Converter Driver initialization */
  ADCD_Init();
#endif
/* DIOD module inhibition filter */
#ifdef __DIOD_IS_PRESENT__
  DIOD_Init();            /* Digital Input/Output             */
#endif
/* CAND module inhibition filter */
#ifdef __CAND_IS_PRESENT__
  CAND_Init();
#endif
  /* MEMD module inhibition filter */
#ifdef __MEMD_IS_PRESENT__
  /* Memory test Driver initialization */
  MEMD_Init();
#endif
/* UARTD module inhibition filter */
#ifdef __UARTD_IS_PRESENT__
  UARTD_Init();
#endif
}

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void DRVD_PseudoInit(void)
{
/*____ DRVD layer Initialization ________________*/

  /* Interrupt Service Routine Driver initialization */
  ISRD_Init();

  /* MCAL Driver initialization */
  /* Timer 0 - Scheduler */
	TAU0_Init();
  TMRD_Init();
  /* Serial for EE */
  SAU0_Init();
  SPID_Init();

/* DIOD module inhibition filter */
#ifdef __DIOD_IS_PRESENT__
  DIOD_Init();            /* Digital Input/Output */
#endif

/* CAND module inhibition filter */
#ifdef __CAND_IS_PRESENT__
  CAND_Init();
#endif
#ifdef __MEMD_IS_PRESENT__
  /* Memory test Driver initialization */
  MEMD_Init();
#endif
/* ADCD module inhibition filter */
#ifdef __ADCD_IS_PRESENT__
  /* Analog Digital Converter Driver initialization */
  ADCD_Init();
#endif
}

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void DRVD_PrPseudoWakeup(void)
{
/*____ DRVD layer Initialization ________________*/

  /* MCAL Driver initialization */
  /* Timer 1 - PWM */
	TAU1_Init();
	/* PWM feedback */
	INTP_Init();
	INTD_Init();

/* UARTD module inhibition filter */
#ifdef __UARTD_IS_PRESENT__
  UARTD_Init();
#endif 

}

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void DRVD_RunPwrOff(void)
{
  /* CAND module inhibition filter */
#ifdef __CAND_IS_PRESENT__
  CAND_PwrOff();
#endif

/* UARTD module inhibition filter */
#ifdef __UARTD_IS_PRESENT__
  UARTD_GoToSleep(UARTD_CHN_HND);
#endif
}

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void DRVD_PseudoRUNPwrOff(void)
{
  /* CAND module inhibition filter */
#ifdef __CAND_IS_PRESENT__
  CAND_PwrOff();
#endif

/* UARTD module inhibition filter */
#ifdef __UARTD_IS_PRESENT__
  UARTD_GoToSleep(UARTD_CHN_HND);
#endif
}

