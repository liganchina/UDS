/******************************************************************************/
/** @file       CTRL.c                                                        */
/** @title      Analog Digital Converter Control                              */
/** @brief      File containing the init function call of each module of      */
/**             Control layer                                                 */
/** @date       27/08/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 27/08/14   0.1  CC      First draft
|-----------------------------------------------------------------------------
| 26/09/14   1.0  CC       Insert the routines CTRL_PseudoInit and
|                          CTRL_PrPseudoWakeup for new power management done by
|                          LPMS module
|-----------------------------------------------------------------------------
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#define CTRL_IF_OWNER

#include "CTRL_if.h"

/*______ L O C A L - D E F I N E _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void CTRL_Init(void)
{
/* ADCC module inhibition filter */
#ifdef __ADCC_IS_PRESENT__
  ADCC_Init();            /* Analog input */
#endif

/* MUXC module inhibition filter */
#ifdef __MUXC_IS_PRESENT__
  MUXC_Init();            /* Multiplexer mgm */
#endif

/* DIAC module inhibition filter */
#ifdef __DIAC_IS_PRESENT__
  DIAC_Init();            /* Digital input on analog pin mgm */
#endif

/* DIAGC module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__
    /* Gestione Diagnosi Elettrica */
  DIAGC_Init();
#endif

/* EEPC module inhibition filter */
#ifdef __EEPC_IS_PRESENT__
  EEPC_Init();            /* Eeprom mgm */
#endif

/* DOIFC module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__
  DOIFC_Init(); /* Digital Output with current fbk     */
#endif

/* HBGRC module inhibition filter */
#ifdef __HBRGC_IS_PRESENT__
  HBRGC_Init(); /* hbridge btm7752 module     */
#endif

/* DOVFC module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__
  DOVFC_Init(); /* Digital Output with voltage fbk     */
#endif

/* IPOC module inhibition filter */
#ifdef __IPOC_IS_PRESENT__
  IPOC_Init(); /* Input position control module       */
#endif
  
/* PWMC module inhibition filter */
#ifdef __PWMC_IS_PRESENT__
  PWMC_Init(); /* PWMC - PWM control module       */
#endif

/* LINC module inhibition filter */
#ifdef __LINC_IS_PRESENT__
  LINC_Init();
#endif
}

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void CTRL_PseudoInit(void)
{
/* EEPC module inhibition filter */
#ifdef __EEPC_IS_PRESENT__
  EEPC_Init();            /* Eeprom mgm */
#endif

/* ADCC module inhibition filter */
#ifdef __ADCC_IS_PRESENT__
  ADCC_Init();            /* Analog input */
#endif

/* MUXC module inhibition filter */
#ifdef __MUXC_IS_PRESENT__
  MUXC_Init();            /* Multiplexer mgm */
#endif

/* DIAC module inhibition filter */
#ifdef __DIAC_IS_PRESENT__
  DIAC_Init();            /* Digital input on analog pin mgm */
#endif
}

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void CTRL_PrPseudoWakeup(void)
{
/* EEPC module inhibition filter */
#ifdef __EEPC_IS_PRESENT__
  EEPC_Init();            /* Eeprom mgm */
#endif

  /* DIAGC module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__
  DIAGC_Init(); /* Gestione Diagnosi Elettrica */
#endif

/* DOIFC module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__
  DOIFC_Init(); /* Digital Output with current fbk     */
#endif

/* DOVFC module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__
  DOVFC_Init(); /* Digital Output with voltage fbk     */
#endif

/* IPOC module inhibition filter */
#ifdef __IPOC_IS_PRESENT__
  IPOC_Init(); /* Input position control module       */
#endif

/* PWMC module inhibition filter */
#ifdef __PWMC_IS_PRESENT__
  PWMC_Init(); /* PWMC - PWM control module       */
#endif

/* LINC module inhibition filter */
#ifdef __LINC_IS_PRESENT__
  LINC_Init();
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
void CTRL_RunPwrOff(void)
{
#ifdef __LINC_IS_PRESENT__
   LINC_GoToSleep(UARTD_CHN_HND);
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
void CTRL_PseudoRUNPwrOff(void)
{
#ifdef __LINC_IS_PRESENT__
   LINC_GoToSleep(UARTD_CHN_HND);
#endif
}

/*_____ E N D _____ (CTRL.c) _________________________________________________*/
