/******************************************************************************/
/** @file       FANA.c                                                        */
/** @title      FAN presentation                                              */
/** @brief      module for FAN management                                     */
/** @date       12/02/2015                                                    */
/** @author     Davide Fogliano                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano		     Polimatica S.r.l.
|-----------------------------------------------------------------------------
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 12/02/2015 0.1  DF      First draft
|-----------------------------------------------------------------------------
| 02/05/2015 0.2  DC      Improvements in failure managements
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define FANA_IF_OWNER

#include "FANA.h"

/* Module inhibition filter */
#ifdef __FANA_IS_PRESENT__ 
/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/
typedef struct FANA_privateData_s
{
  u08          current_level   :8;
  u08    	     request_level   :8;
  bool         fault_present   :1;
  bool         running         :1;
  bool         ioControlActive :1;
}Fana_privateData_t;

/*_____ P R I V A T E - D A T A ______________________________________________*/
static Fana_privateData_t Fana_privateTable[FANA_MAX_HDL];

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

void FANA_Init(void)
{
  FANA_handle_t hdl;
  
  /* intialize private data */
  for( hdl = (FANA_handle_t)0u; hdl < FANA_MAX_HDL; hdl++)
  {
    Fana_privateTable[hdl].current_level   = 0U;
    Fana_privateTable[hdl].request_level   = 0U;
    Fana_privateTable[hdl].fault_present   = FALSE;
    Fana_privateTable[hdl].running         = TRUE;
    Fana_privateTable[hdl].ioControlActive = FALSE;
  }
}

void FANA_Mgm(void)
{
  FANA_handle_t hdl;
  PRES_Fault_t fault;
  bool is_destructive;
  
  /* this function (implemented in FANA_Config.c) upate the command of ventilation by calling FANA_SetLevel() */
  FANA_CommandUpdate();
  
  for( hdl = (FANA_handle_t)0u; hdl < FANA_MAX_HDL; hdl++)
  {
    if(Fana_privateTable[hdl].running)
    {
      if(Fana_privateTable[hdl].current_level != Fana_privateTable[hdl].request_level)
      {
        /* the command has changed,  reset the fault information */
        FVMP_ResetLine(FANA_CfgTable[hdl].PWM_FAULT_LINE);
        FVMP_ResetLine(FANA_CfgTable[hdl].SUPPLY_FAULT_LINE);
        Fana_privateTable[hdl].fault_present = FALSE;
      }

      fault = PRES_NOT_TESTED;
      is_destructive = FALSE;

      if(FANA_CfgTable[hdl].TYPE == FANA_THREE_WIRE)
      {
        /* check if some fault on FAN power is present and validated */
        FVMP_GetDiag(FANA_CfgTable[hdl].SUPPLY_FAULT_LINE, &fault, &is_destructive);
      }

      if((fault == PRES_NO_FAULT) || (FANA_CfgTable[hdl].TYPE != FANA_THREE_WIRE))
      {
        /* No fault on FAN power supply or two wire FAN*/
        /* Check if some fault on FAN PWM is present and validated */
        FVMP_GetDiag(FANA_CfgTable[hdl].PWM_FAULT_LINE, &fault, &is_destructive);
      }

      if((fault != PRES_NOT_TESTED) && (fault != PRES_NO_FAULT))
      {
//        if(is_destructive)
//        {
          /* Disable power supply */
          DOIFC_SetState(FANA_CfgTable[hdl].SUPPLY_HANDLE, S_OFF);
          /* set the duty cycle to 0*/
          PWMC_SetDuty(FANA_CfgTable[hdl].PWM_HANDLE, 0u);
//        }
        Fana_privateTable[hdl].fault_present = TRUE;
      }
      else
      {
//        if(fault == PRES_NO_FAULT)
//        {
          Fana_privateTable[hdl].fault_present = FALSE;
//        }
      }

      if(Fana_privateTable[hdl].fault_present == FALSE)
      {
        /* update the power supply output */
        if(FANA_CfgTable[hdl].TYPE == FANA_THREE_WIRE)
        {
          /* management of the shared power supply */
          if(Fana_privateTable[hdl].request_level > 0U)
          {
            /* set the shared variable bit n° [hdl] */
            *FANA_CfgTable[hdl].SHARED_SUPPLY_VAR |= (u16)(1U<<(u08)hdl);
          }
          else
          {
            /* clear the shared variable bit n° [hdl] */
            *FANA_CfgTable[hdl].SHARED_SUPPLY_VAR &= ~((u16)(1U<<(u08)hdl));
          }

          if((*FANA_CfgTable[hdl].SHARED_SUPPLY_VAR) != 0U)
          {
            /* enable power supply */
            DOIFC_SetState(FANA_CfgTable[hdl].SUPPLY_HANDLE, S_ON);
          }
          else
          {
            /* Disable power supply */
            DOIFC_SetState(FANA_CfgTable[hdl].SUPPLY_HANDLE, S_OFF);
          }
        }
        /* update the Duty Cycle only if IOControl for this handle is not active */
        if(Fana_privateTable[hdl].ioControlActive == FALSE)
        {
          /* set the right level duty cycle */
          PWMC_SetDuty(FANA_CfgTable[hdl].PWM_HANDLE, Fana_privateTable[hdl].request_level);
        }
      }

      /* Update current_level */
      Fana_privateTable[hdl].current_level = Fana_privateTable[hdl].request_level;        

    }//if Runnning - END
  }//for 
}

APPL_ResSts_t FANA_SetLevel(FANA_handle_t hdl,u08 level)
{
  APPL_ResSts_t ret_val = APPL_OK;

  if(hdl >= FANA_MAX_HDL) 
  {
    ret_val = APPL_PAR_NOT_OK;
  }
  else
  { 
    /* update the required level only if IOControl for this hande is not active */
    if(Fana_privateTable[hdl].ioControlActive == FALSE) 
    {
      if((FANA_CfgTable[hdl].NUM_LEVEL == 0U) || (FANA_CfgTable[hdl].LEVELS == NULL))
      {
        /* Check if parameter is in range */
        if (level > 100U)
        {
          ret_val = APPL_PAR_NOT_OK;
        }
        else
        {
          /* parameters OK, change the requested level */
          Fana_privateTable[hdl].request_level = level;
        }
      }
      else
      {
        /* Check if parameter is in range */
        if (level >= FANA_CfgTable[hdl].NUM_LEVEL)
        {
          ret_val = APPL_PAR_NOT_OK;
        }
        else
        {
          /* parameters OK, change the requested level */
          Fana_privateTable[hdl].request_level = FANA_CfgTable[hdl].LEVELS[level];
        }
      }
    }
  }
  return ret_val;
}


CTRL_Fault_t FANA_GetDiag(FANA_handle_t hdl)
{
  CTRL_Fault_t faultTmp;
  /* Update fault information */
  /* check FAN type */
  if(FANA_CfgTable[hdl].TYPE == FANA_THREE_WIRE)
  {
    if(DOIFC_GetState(FANA_CfgTable[hdl].SUPPLY_HANDLE) == S_ON)
    {
      faultTmp = PWMC_GetDiag(FANA_CfgTable[hdl].PWM_HANDLE);
    }
    else
    {
      faultTmp = CTRL_NOT_TESTED;
    }
  }
  else
  {
    faultTmp = PWMC_GetDiag(FANA_CfgTable[hdl].PWM_HANDLE);
  }

  return (faultTmp);
}



FANA_EXTERN u08 FANA_CheckIoControl(u08 hdl, u08 command)
{
  u08 ret_val;

  if(Fana_privateTable[hdl].fault_present)
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    ret_val = SERVICE_OK;

    /* check the required command according to levels type (level or direct duty cycle vale) */
    if((FANA_CfgTable[hdl].NUM_LEVEL == 0U) || (FANA_CfgTable[hdl].LEVELS == NULL))
    {
      /* Check if parameter are in range */
      if (command > 100U)
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }
    }
    else
    {
      /* Check if parameter are in range */
      //if (command >= FANA_CfgTable[hdl].NUM_LEVEL)
      // Daniele: IoControl set only one level now
      if (command > 1U)
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }
    }
  }

  return ret_val;
}

void FANA_StartIoControl(u08 hdl, u08 level)
{
  //FANA_SetLevel((FANA_handle_t)hdl, level);
  if (level == 0)
  {
    PWMC_SetDuty(FANA_CfgTable[hdl].PWM_HANDLE, FANA_DUTY_0);
  }
  else
  {
    PWMC_SetDuty(FANA_CfgTable[hdl].PWM_HANDLE, FANA_DUTY_50);
  }
  Fana_privateTable[hdl].ioControlActive = TRUE;
}

void FANA_StopIoControl(u08 hdl)
{
  PWMC_SetDuty(FANA_CfgTable[hdl].PWM_HANDLE, FANA_DUTY_0);
  Fana_privateTable[hdl].ioControlActive = FALSE;
}

#endif
/*______ E N D _____ (FANA.c) _________________________________________*/
