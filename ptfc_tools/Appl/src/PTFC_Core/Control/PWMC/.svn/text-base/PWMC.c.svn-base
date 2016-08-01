/******************************************************************************/
/** @file       PWMC.c                                                        */
/** @title      Pulse Width Modulation Control                                */
/** @brief      PWM module for control layer.                                 */
/** @date       02/12/2014                                                    */
/** @author     Mastrodonato Matteo                                           */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 02/12/2014 0.1  MM      First draft
|-----------------------------------------------------------------------------
|            1.0  MM      First release
|-----------------------------------------------------------------------------
|            1.1  DAF     Modification, SW PWM diagnosis performed by DOIFC
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define PWMC_IF_OWNER

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "PWMC.h"
#include "PWMC_config.h"

/* Module inhibition filter */
#ifdef __PWMC_IS_PRESENT__

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#define DUTY_100      100U
#define DUTY_0          0U

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/**
 * Transition count for diagnosis by interrupt fbk.
 *
 * */
typedef enum PWMC_Trans_e
{
  TRANS_1  = 0,
  TRANS_2,
  TRANS_OK,
}PWMC_Trans_t;

/*_____ G L O B A L - D A T A ________________________________________________*/


typedef struct PWMC_SwPrivateData_s
{
  uint16_t          actualTime;
  uint16_t          offTime;
  uint8_t           actualDuty;
  CTRL_State_t      actualState;
  uint16_t          timeFromLastTrans;
  CTRL_EnSts_t      functionState;   /*Function State, enabled/disabled by proxi*/
}PWMC_SwPrivateData_t;

typedef struct PWMC_HwPrivateData_s
{
  uint8_t           actualDuty;
  CTRL_State_t      actualState;
  PWMC_Trans_t      cmdTrans;
  PWMC_Trans_t      fbkTrans;
  CTRL_State_t      diagDataState;
  CTRL_Fault_t      diagData;
  CTRL_Fault_t      lastFault;
  CTRL_FaultState_t faultState;
  CTRL_EnSts_t      functionState;   /*Function State, enabled/disabled by proxi*/
}PWMC_HwPrivateData_t;


static PWMC_SwPrivateData_t Pwmc_SwPrivateData[PWMC_SW_HDL_MAX];
static PWMC_HwPrivateData_t Pwmc_HwPrivateData[PWMC_HW_HDL_MAX - PWMC_SW_HDL_MAX];

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief Initialization routine for PWMC control module. This routine must be
 *        called only during transition POWER_OFF --> RUN.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void PWMC_Init(void)
{
  PWMC_Handle_t hdl;

  for (hdl = (PWMC_Handle_t)0; hdl < PWMC_SW_HDL_MAX; hdl++)
  {
    Pwmc_SwPrivateData[hdl].actualTime    = 0U;
    Pwmc_SwPrivateData[hdl].offTime       = PWMC_SwCfgTable[hdl].PERIOD;
    Pwmc_SwPrivateData[hdl].actualDuty    = 0U;
    Pwmc_SwPrivateData[hdl].actualState   = S_OFF;
    Pwmc_SwPrivateData[hdl].functionState = CTRL_ENABLE;
  }

  for (hdl = (PWMC_Handle_t)0U; hdl < (PWMC_Handle_t)(PWMC_HW_HDL_MAX - PWMC_SW_HDL_MAX); hdl++)
  {
    TMRD_ChangeDuty ((TMRD_Channel_t)PWMC_HwCfgTable[hdl].CMD_CHAN, 0U);
    TMRD_EnableTimer((TMRD_Channel_t)PWMC_HwCfgTable[hdl].CMD_CHAN);

    Pwmc_HwPrivateData[hdl].cmdTrans      = TRANS_1;
    Pwmc_HwPrivateData[hdl].fbkTrans      = TRANS_1;
    Pwmc_HwPrivateData[hdl].actualDuty    = 0U;
    Pwmc_HwPrivateData[hdl].actualState   = S_OFF;
    Pwmc_HwPrivateData[hdl].diagDataState = S_OFF;
    Pwmc_HwPrivateData[hdl].diagData      = CTRL_NO_FAULT;
    Pwmc_HwPrivateData[hdl].lastFault     = CTRL_NOT_TESTED;
    Pwmc_HwPrivateData[hdl].faultState    = CTRL_NOT_TESTED_NO_FAULT_STATE;
    Pwmc_HwPrivateData[hdl].functionState = CTRL_DISABLE;
  }
}

/**
 * @brief Manage the PWM SW period and duty transitions.
					Call this function periodically, the tick time must be less equal
					than the minimun Ton of the configured PWM signals.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void PWMC_Mgm(void)
{
  PWMC_Handle_t hdl;
  bool_t execDiag;

  for (hdl = (PWMC_Handle_t)0; hdl < PWMC_SW_HDL_MAX; hdl++)
  {
    if(Pwmc_SwPrivateData[hdl].functionState == CTRL_ENABLE)
    {
      execDiag = (Pwmc_SwPrivateData[hdl].actualTime) & (PWMC_SwCfgTable[hdl].MIN_CMD);
    
      /* Il ton è a fine periodo */
      Pwmc_SwPrivateData[hdl].actualTime += PWMC_TICK_TIME;

      if (execDiag != ((Pwmc_SwPrivateData[hdl].actualTime) & (PWMC_SwCfgTable[hdl].MIN_CMD)))
      {
        if (((Pwmc_SwPrivateData[hdl].actualTime - Pwmc_SwPrivateData[hdl].timeFromLastTrans) > PWMC_SwCfgTable[hdl].MIN_CMD) ||
            ((Pwmc_SwPrivateData[hdl].actualTime - Pwmc_SwPrivateData[hdl].timeFromLastTrans) == 0U))
        {
          DOIFC_PerformAndDecodeDiag(PWMC_SwCfgTable[hdl].CMD_CHAN);
        }
      }

      /* Controllo se il Toff è scaduto */
      if (Pwmc_SwPrivateData[hdl].actualTime > Pwmc_SwPrivateData[hdl].offTime)
      {
        /* Inizio il Ton */
        if (Pwmc_SwPrivateData[hdl].actualState == S_OFF)
        {
          DOIFC_SetState(PWMC_SwCfgTable[hdl].CMD_CHAN, S_ON);
          Pwmc_SwPrivateData[hdl].actualState = S_ON;
          Pwmc_SwPrivateData[hdl].timeFromLastTrans = Pwmc_SwPrivateData[hdl].actualTime;
        }
        else
        {
        }
      }
      else
      {
        /* Toff */
      }

      if (Pwmc_SwPrivateData[hdl].actualTime >= PWMC_SwCfgTable[hdl].PERIOD)
      {
        /* Reset Period counter */
        Pwmc_SwPrivateData[hdl].actualTime = 0U;

        Pwmc_SwPrivateData[hdl].timeFromLastTrans   = 0U;

        if(Pwmc_SwPrivateData[hdl].offTime > 0U) /* Duty < 100% */
        {
          /* Start Toff */
          DOIFC_SetState(PWMC_SwCfgTable[hdl].CMD_CHAN, S_OFF);
          Pwmc_SwPrivateData[hdl].actualState = S_OFF;
        }
        else
        {
        }
      }
      else
      {
      }
    }
    else
    {
    }
  }
}

/**
 * @brief Set the duty cycle of the signal passed as parameter.
					Duty has a resolution of 1%/Bit.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal to change the duty cycle.
 * @param [out] duty the new duty cycle.
 * @return CTRL_Fault_t
 * @retval CTRL_OK Request correclty applied
 * @retval CTRL_PAR_NOT_OK Request refused due to duty cycle ouf of bound.
 */

CTRL_ResSts_t PWMC_SetDuty(PWMC_Handle_t hdl, uint8_t duty)
{
  CTRL_ResSts_t ret_val = CTRL_OK;
  uint32_t temp1, temp2;

  if(duty > DUTY_100)
  {
    ret_val = CTRL_PAR_NOT_OK;
  }
  else
  {
    if (hdl < PWMC_SW_HDL_MAX)
    {
      if (Pwmc_SwPrivateData[hdl].functionState == CTRL_ENABLE)
      {
        if (Pwmc_SwPrivateData[hdl].actualDuty != duty)
        {
          DOIFC_DiagExtReset(PWMC_SwCfgTable[hdl].CMD_CHAN);
          Pwmc_SwPrivateData[hdl].actualDuty = duty;
          temp1 = (uint32_t)PWMC_SwCfgTable[hdl].PERIOD * (uint32_t)duty;
          temp2 = temp1 /  DUTY_100;
          Pwmc_SwPrivateData[hdl].offTime = (PWMC_SwCfgTable[hdl].PERIOD - (uint16_t)temp2);
        }
        else
        {
        }
      }
      else
      {
        ret_val = CTRL_PAR_NOT_ENABLED;
      }
    }
    else
    {
      hdl = (PWMC_Handle_t)(hdl - PWMC_SW_HDL_MAX);

      if (Pwmc_HwPrivateData[hdl].functionState == CTRL_ENABLE)
      {
        if (duty < PWMC_HwCfgTable[hdl].MIN_DUTY)
        {
          duty = DUTY_0;
        }
        else if (duty > (DUTY_100 - PWMC_HwCfgTable[hdl].MIN_DUTY))
        {
          duty = DUTY_100;
        }
        else
        {
        }

        if (Pwmc_HwPrivateData[hdl].actualDuty != duty)
        {
          Pwmc_HwPrivateData[hdl].actualDuty = duty;
          Pwmc_HwPrivateData[hdl].cmdTrans = TRANS_1;
          Pwmc_HwPrivateData[hdl].fbkTrans = TRANS_1;

          TMRD_ChangeDuty((TMRD_Channel_t)PWMC_HwCfgTable[hdl].CMD_CHAN, duty);
          INTD_EnableIsr((INTD_Channel_t)PWMC_HwCfgTable[hdl].FBK_CHAN);
        }
        else
        {
        }
      }
      else
      {
        ret_val = CTRL_PAR_NOT_ENABLED;
      }
    }
  }

  return ret_val;
}


/**
 * @brief This function is called by DIAGC scheduler. Trigger che diagnosis and get
 *  from the hdl the information to evolve the fault state machine.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal
 * @param [out] cmdState the command state when the last fault has been seen.
 * @param [out] fault the last fault seen
 * @param [out] faultState is the old state of the fault state machine.
 * @return bool_t
 * @retval TRUE the diagnosis is performed
 * @retval FALSE the diagnosis need further call to end the procedure
 */
bool_t PWMC_PerformDiag(u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState)
{
  if (hdl < PWMC_SW_HDL_MAX)
  {
  }
  else
  {
    hdl = hdl - PWMC_SW_HDL_MAX;

    if(Pwmc_HwPrivateData[hdl].functionState == CTRL_ENABLE)
    {
      if ((Pwmc_HwPrivateData[hdl].actualDuty > DUTY_0) &&
          (Pwmc_HwPrivateData[hdl].actualDuty < DUTY_100))
      {
        /* comunico lo stato del comando */
        *cmdState = Pwmc_HwPrivateData[hdl].diagDataState;
      }
      else
      {
        /* duty fuori range, diagnosi disponibile solo diagnosi "statica" */

        if (Pwmc_HwPrivateData[hdl].actualDuty == DUTY_0)
        {
          /* comunico lo stato del comando */
          *cmdState = S_OFF;
        }
        else
        {
          *cmdState = S_ON;
        }

        /* Get fbk level */
        if ( ((DRVD_Level_t)INTD_GetLevel((INTD_Channel_t)PWMC_HwCfgTable[hdl].FBK_CHAN)) == L_HIGH)
        {
          if (PWMC_HwCfgTable[hdl].DRIVER_TYPE == HSD)
          {
            if (*cmdState == S_ON)
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_NO_FAULT;
            }
            else
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_OC_OR_STB;
            }
          }
          else
          {
            if (*cmdState == S_ON)
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_SHORT_TO_BAT;
            }
            else
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_NO_FAULT;
            }
          }
        }
        else /* FBK_CHAN = LOW */
        {
          if (PWMC_HwCfgTable[hdl].DRIVER_TYPE == HSD)
          {
            if (*cmdState == S_ON)
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_SHORT_TO_GND;
            }
            else
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_NO_FAULT;
            }
          }
          else
          {
            if (*cmdState == S_ON)
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_NO_FAULT;
            }
            else
            {
              Pwmc_HwPrivateData[hdl].lastFault = CTRL_OC_OR_STG;
            }
          }
        }
      }
    }
    else
    {
      *cmdState = S_OFF;
    }
    /* comunico l'ultimo fault visto */
    *fault      = Pwmc_HwPrivateData[hdl].lastFault;
    /* comunico lo stato della macchina a stati */
    *faultState = Pwmc_HwPrivateData[hdl].faultState;
  }

  /* Comunico che la diagnosi è terminata */
  return TRUE;
}


/**
 * @brief This function is called by DIAGC scheduler. Decode the information coming
 * from the fault state machine and update the internal handle diagnosis.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal
 * @param [in] faultState is the new state of the fault state machine.
 * @return none
 */
void PWMC_DecodeDiag(u08 hdl, CTRL_FaultState_t faultState)
{
  if (hdl < PWMC_SW_HDL_MAX)
  {
#if 0
    Pwmc_SwPrivateData[hdl].faultState = faultState;

    if(faultState == CTRL_NO_FAULT_STATE)
    {
      Pwmc_SwPrivateData[hdl].diagData = CTRL_NO_FAULT;
    }
    else if((faultState == CTRL_FAULT_CMD_ON_STATE)  ||
            (faultState == CTRL_FAULT_CMD_OFF_STATE) ||
            (faultState == CTRL_FAULT_CMD_ALL_STATE))
    {
      Pwmc_SwPrivateData[hdl].diagData = Pwmc_SwPrivateData[hdl].lastFault;
    }
    else
    {
      Pwmc_SwPrivateData[hdl].diagData = CTRL_NOT_TESTED;
    }

    /* Reset diag */
    Pwmc_SwPrivateData[hdl].lastFault = CTRL_NOT_TESTED;
#endif
  }
  else
  {
    hdl = hdl - PWMC_SW_HDL_MAX;

    Pwmc_HwPrivateData[hdl].faultState = faultState;

    if(faultState == CTRL_NO_FAULT_STATE)
    {
      Pwmc_HwPrivateData[hdl].diagData = CTRL_NO_FAULT;
    }
    else if((faultState == CTRL_FAULT_CMD_ON_STATE)  ||
            (faultState == CTRL_FAULT_CMD_OFF_STATE) ||
            (faultState == CTRL_FAULT_CMD_ALL_STATE))
    {
      Pwmc_HwPrivateData[hdl].diagData = Pwmc_HwPrivateData[hdl].lastFault;
    }
    else
    {
      Pwmc_HwPrivateData[hdl].diagData = CTRL_NOT_TESTED;
    }
  }
}

/**
 * @brief This function returns the electrical diagnosis of the selected handle.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT
 * @retval CTRL_OC_OR_STB
 * @retval CTRL_OC_OR_STG
 * @retval CTRL_SHORT_TO_BAT
 * @retval CTRL_SHORT_TO_GND
 * @retval CTRL_NOT_TESTED
 */
CTRL_Fault_t PWMC_GetDiag(PWMC_Handle_t hdl)
{
  CTRL_Fault_t ret_val;

  if (hdl < PWMC_SW_HDL_MAX)
  {
    /* SW PWM don't manage diagnosis */
    ret_val = DOIFC_GetDiag(PWMC_SwCfgTable[hdl].CMD_CHAN);
  }
  else
  {
    hdl = (PWMC_Handle_t)(hdl - PWMC_SW_HDL_MAX);

    Pwmc_HwPrivateData[hdl].cmdTrans = TRANS_1;
    Pwmc_HwPrivateData[hdl].fbkTrans = TRANS_1;
    INTD_EnableIsr((INTD_Channel_t)PWMC_HwCfgTable[hdl].FBK_CHAN);

    ret_val = (Pwmc_HwPrivateData[hdl].diagData);
  }

  return ret_val;
}


/**
 * @brief This function returns the command state related to diag information
 * returned by PWMC_GetDiag().
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @return CTRL_State_t
 * @retval S_OFF
 * @retval S_ON
 * @retval S_TOGGLE
 */
CTRL_State_t PWMC_GetDiagState(PWMC_Handle_t hdl)
{
  CTRL_State_t ret_val;

  if (hdl < PWMC_SW_HDL_MAX)
  {
    ret_val = S_OFF;
  }
  else
  {
    hdl = (PWMC_Handle_t)(hdl - PWMC_SW_HDL_MAX);

    ret_val = (Pwmc_HwPrivateData[hdl].diagDataState);
  }

  return ret_val;
}


/**
 * @brief This is a function callback called at the end of the PWM period.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl The handle of PWM object associated to the PMW command
 *                 that just reached the period end.
 * @param [out] None
 * @return None
 */
void PWMC_EndPeriod(uint8_t hdl)
{
  hdl = (PWMC_Handle_t)(hdl - PWMC_SW_HDL_MAX);
  
  if (Pwmc_HwPrivateData[hdl].cmdTrans == TRANS_1)
  {
    Pwmc_HwPrivateData[hdl].cmdTrans = TRANS_2;
  }
  else if (Pwmc_HwPrivateData[hdl].cmdTrans == TRANS_2)
  {
    Pwmc_HwPrivateData[hdl].cmdTrans = TRANS_OK;

    /* Diag ended */
    if (Pwmc_HwPrivateData[hdl].fbkTrans == TRANS_OK)
    {
      Pwmc_HwPrivateData[hdl].lastFault = CTRL_NO_FAULT;
      Pwmc_HwPrivateData[hdl].diagDataState = S_TOGGLE;
    }
    else
    {
      /* Get fbk level */
      if ( ((DRVD_Level_t)INTD_GetLevel((INTD_Channel_t)PWMC_HwCfgTable[hdl].FBK_CHAN)) == L_HIGH)
      {
        if (PWMC_HwCfgTable[hdl].DRIVER_TYPE == HSD)
        {
          Pwmc_HwPrivateData[hdl].lastFault = CTRL_OC_OR_STB;
          Pwmc_HwPrivateData[hdl].diagDataState = S_OFF;
        }
        else
        {
          Pwmc_HwPrivateData[hdl].lastFault = CTRL_SHORT_TO_BAT;
          Pwmc_HwPrivateData[hdl].diagDataState = S_ON;
        }
      }
      else
      {
        if (PWMC_HwCfgTable[hdl].DRIVER_TYPE == HSD)
        {
          Pwmc_HwPrivateData[hdl].lastFault = CTRL_SHORT_TO_GND;
          Pwmc_HwPrivateData[hdl].diagDataState = S_ON;
        }
        else
        {
          Pwmc_HwPrivateData[hdl].lastFault = CTRL_OC_OR_STG;
          Pwmc_HwPrivateData[hdl].diagDataState = S_OFF;
        }
      }
    }
  }
  else
  {
    /* TRANS_OK */
  }
}


/**
 * @brief This is a function callcack called when a fbk transition occurs.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl The handle of PWM object associated to the feedback
 *                 that just had a transition.
 * @param [out] None
 * @return None
 */
void PWMC_FbkTransition(uint8_t hdl)
{
  hdl = (PWMC_Handle_t)(hdl - PWMC_SW_HDL_MAX);
  
  if (Pwmc_HwPrivateData[hdl].fbkTrans == TRANS_1)
  {
    Pwmc_HwPrivateData[hdl].fbkTrans = TRANS_2;
  }
  else if (Pwmc_HwPrivateData[hdl].fbkTrans == TRANS_2)
  {
    Pwmc_HwPrivateData[hdl].fbkTrans = TRANS_OK;
    INTD_DisableIsr((INTD_Channel_t)PWMC_HwCfgTable[hdl].FBK_CHAN);
  }
  else
  {
    /* Diag ended */
  }
}

/**
 * @brief This function is used to initialize the Diagnosis State Machine.
 * @param hdl is the diagnosis line
 * @param fault is the last fault detected (ie: stored in EEPROM)
 * @return Returns the status of user request.
 */

/** TODO COBRA: per la gestione del bit 6 fiat... */

#if 0
DRVD_RStatus_t PWMC_SetFault(PWMC_Handle_t hdl, CTRL_Fault_t fault)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < PWMC_HDL_MAX)
  {
    if ((fault == CTRL_SHORT_TO_GND) || (fault == CTRL_OC_OR_STG))
    {
      if(PWMC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        Pwmc_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
      }
      else
      {
        Pwmc_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
    }
    else if ((fault == CTRL_SHORT_TO_BAT) || (fault == CTRL_OC_OR_STB))
    {
      if(PWMC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        Pwmc_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
      else
      {
        Pwmc_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
      }
    }
    else
    {
      valueReturn = MS_PAR_NOT_OK;
    }
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}
#endif /* if 0 */

/**
 * @brief Get the duty cycle of the signal passed as parameter.
					Duty has a resolution of 1%/Bit.
 * @author Davide Fogliano - Polimatica S.r.l.
 * @param [in] hdl handle of the signal to get the duty cycle.
 * @return Duty cycle
 * @retval 0xFF handler not valid
 */
u08 PWMC_GetDuty(PWMC_Handle_t hdl)
{
  u08 ret_val;
  
  if (hdl < PWMC_SW_HDL_MAX)
  {/*SW PWM */
    ret_val = Pwmc_SwPrivateData[hdl].actualDuty;
  }
  else if (hdl < PWMC_HW_HDL_MAX)
  {/*HW PWM */
    ret_val = Pwmc_HwPrivateData[hdl - PWMC_SW_HDL_MAX].actualDuty;
  }
  else
  {/* Handler not in range, return 0xFF */
    ret_val = 0xFFU;
  }

  return (ret_val);
}

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
void PWMC_EnableDisable (PWMC_Handle_t hdl, CTRL_EnSts_t state)
{
  if (hdl < PWMC_SW_HDL_MAX)
  {
    Pwmc_SwPrivateData[hdl].functionState = state;
  }
  else if (hdl < PWMC_HW_HDL_MAX)
  {
    Pwmc_HwPrivateData[hdl - PWMC_SW_HDL_MAX].functionState = state;
  }
  else
  {}
}

#endif /* PWMC_IS_PRESENT */

/*_____ E N D _____ (PWMC_if.h) ______________________________________________*/
