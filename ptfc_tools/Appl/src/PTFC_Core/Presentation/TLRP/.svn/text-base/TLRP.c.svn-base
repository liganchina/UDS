/**
 * @file TLRP.c
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief Core File of DIOD Driver. This driver is able manage low resolution timers
 * and call a callback function when the timer is up.
 *
 * @see www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 15/06/2013 1.0  MM      First release
|-----------------------------------------------------------------------------
| 09/10/2014 1.1  CC      New management of the callback: deleted input parameter
|-----------------------------------------------------------------------------
*/

#include "TLRP.h"
#include "TLRP_config.h"

/* Module inhibition filter */
#ifdef __TLRP_IS_PRESENT__

TLRP_PrivateData_t	TLRP_PrivateData;


/**
 * @brief This function initializes the TLRP driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void TLRP_Init(void)
{
  memset(&TLRP_PrivateData.timerFast[0U], 0U, (2U*TLRP_HDLF_MAX));
  memset(&TLRP_PrivateData.timerSlow[0U], 0U, (4U*TLRP_HDLS_MAX));
}

/**
 * @brief This function set a fast timer.
 * @return the result of the operation
 * @note  The timer value is statically configured.
 */
DRVD_RStatus_t TLRP_SetFast(TLRP_HandlerFast_t hdl)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < TLRP_HDLF_MAX)
  {
    TLRP_PrivateData.timerFast[hdl] = TLRP_TimerTableFast[hdl].timeToRun;
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function set a slow timer.
 * @return the result of the operation
 * @note  The timer value is statically configured.
 */
DRVD_RStatus_t TLRP_SetSlow(TLRP_HandlerSlow_t hdl)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < TLRP_HDLS_MAX)
  {
    TLRP_PrivateData.timerSlow[hdl] = TLRP_TimerTableSlow[hdl].timeToRun;
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function reset a fast timer.
 * @return the result of the operation
 */
DRVD_RStatus_t TLRP_ResetFast(TLRP_HandlerFast_t hdl)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < TLRP_HDLF_MAX)
  {
    TLRP_PrivateData.timerFast[hdl] = 0u;
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function reset a slow timer.
 */
DRVD_RStatus_t TLRP_ResetSlow(TLRP_HandlerSlow_t hdl)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < TLRP_HDLS_MAX)
  {
    TLRP_PrivateData.timerSlow[hdl] = 0u;
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function check a fast timer.
 * @return the current value of the timer
 */
u16 TLRP_GetFast(TLRP_HandlerFast_t hdl)
{
  u16 valueReturn;

  if (hdl < TLRP_HDLF_MAX)
  {
    valueReturn = TLRP_PrivateData.timerFast[hdl];
  }
  else
  {
    valueReturn = 0xFFFFU;
  }

  return valueReturn;
}

/**
 * @brief This function check a slow timer.
 * @return the current value of the timer
 */
u32 TLRP_GetSlow(TLRP_HandlerSlow_t hdl)
{
  u32 valueReturn;

  if (hdl < TLRP_HDLS_MAX)
  {
    valueReturn = TLRP_PrivateData.timerSlow[hdl];
  }
  else
  {
    valueReturn = 0xFFFFFFFFU;
  }

  return valueReturn;
}

/**
 * @brief This function manages the internal counters of TLRP driver.
 * @return void
 * @note  It must be called periodically (Fast)
 */
void TLRP_MgmFast(void)
{
  u08 hdl;
  /* Ciclo su tutti i timer disponibili */
  for (hdl = 0u; hdl < TLRP_HDLF_MAX; hdl++)
  {
    if (TLRP_PrivateData.timerFast[hdl] > 0u)
    {
      /* Decremento il timer */
      TLRP_PrivateData.timerFast[hdl] -= TLRP_FAST_TICK;
      /* Se è scaduto chiamo la callback */
      if ((TLRP_PrivateData.timerFast[hdl] == 0u) &&
          (TLRP_TimerTableFast[hdl].callback != NULL))
      {
        TLRP_TimerTableFast[hdl].callback();
      }
    }
  }
}

/**
 * @brief This function manages the internal counters of TLRP driver.
 * @return void
 * @note  It must be called periodically (Slow)
 */
void TLRP_MgmSlow(void)
{
  u08 hdl;
  /* Ciclo su tutti i timer disponibili */
  for (hdl = 0u; hdl < TLRP_HDLS_MAX; hdl++)
  {
    if (TLRP_PrivateData.timerSlow[hdl] > 0u)
    {
      /* Decremento il timer */
      TLRP_PrivateData.timerSlow[hdl] -= TLRP_SLOW_TICK;
      /* Se è scaduto chiamo la callback */
      if ((TLRP_PrivateData.timerSlow[hdl] == 0u) &&
          (TLRP_TimerTableSlow[hdl].callback != NULL))
      {
        TLRP_TimerTableSlow[hdl].callback();
      }
    }
  }
}


#endif /* end __TLRP_IS_PRESENT__ */

/*______ E N D _____ (TLRP.c) ________________________________________________*/
