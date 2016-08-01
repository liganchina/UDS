/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              DOVFC                                                   */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     21/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 21/giu/2013     0.1  Matteo MASTRODONATO
*/

#define DOVFC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "DOVFC.h"

/* Module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

DOVFC_PrivateData_t	DOVFC_PrivateData[DOVFC_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/*----------------------------------------------------------------------------*/
/*Name : Module initialization                                                */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DOVFC_Init(void)
{
  DOVFC_Handle_t hdl;

  for (hdl = (DOVFC_Handle_t)0; hdl < DOVFC_HDL_MAX; hdl++)
  {
    DOVFC_PrivateData[hdl].diagData      = CTRL_NOT_TESTED;
    DOVFC_PrivateData[hdl].diagDataState = S_OFF;
    DOVFC_PrivateData[hdl].lastFault     = CTRL_NOT_TESTED;
    DOVFC_PrivateData[hdl].outState      = S_OFF;
    DOVFC_PrivateData[hdl].faultState    = CTRL_NOT_TESTED_NO_FAULT_STATE;
    DOVFC_PrivateData[hdl].freeze        = S_OFF;
    DOVFC_PrivateData[hdl].diagDebounce  = 0u;
    DOVFC_PrivateData[hdl].functionState = CTRL_ENABLE;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : Xxxx_yyyyzzzz                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DRVD_RStatus_t DOVFC_SetState(DOVFC_Handle_t hdl, CTRL_State_t state)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < DOVFC_HDL_MAX)
  {
    if (DOVFC_PrivateData[hdl].functionState == CTRL_ENABLE)
    {
      if(state == S_PREVIOUS)
      {
        /* Setto l'uscita allo stato memorizzato in precedenza */
        state = DOVFC_PrivateData[hdl].outState;
      }
      else if ((state == S_ON) || (state == S_OFF))
      {
        /* Se il comando cambia devo resettare il debounce */
        if(DOVFC_PrivateData[hdl].outState != state)
        {
          DOVFC_PrivateData[hdl].diagDebounce = 0u;
        }

        /* Memorizzo lo stato dell'uscita richiesto */
        DOVFC_PrivateData[hdl].outState = state;
      }
      else
      {
        valueReturn = MS_PAR_NOT_OK;
      }

      if (DOVFC_PrivateData[hdl].freeze == S_OFF)
      {
        if (state == S_ON)
        {
          if (DOVFC_CfgTable[hdl].CMD_ACT_LEV == L_LOW)
          {
            DIOD_SetLevel(DOVFC_CfgTable[hdl].OUT_CHAN, L_LOW);
          }
          else
          {
            DIOD_SetLevel(DOVFC_CfgTable[hdl].OUT_CHAN, L_HIGH);
          }
        }
        else if(state == S_OFF)
        {
          if (DOVFC_CfgTable[hdl].CMD_ACT_LEV == L_LOW)
          {
            DIOD_SetLevel(DOVFC_CfgTable[hdl].OUT_CHAN, L_HIGH);
          }
          else
          {
            DIOD_SetLevel(DOVFC_CfgTable[hdl].OUT_CHAN, L_LOW);
          }
        }
        else
        {
          valueReturn = MS_PAR_NOT_OK;
        }
      }
      else /* DOVFC_PrivateData[hdl].freeze = S_ON */
      {
        /* Diagnosi critica in corso */
        /* Non aggiorno l'uscita, ci penserà poi la diagnosi quando terminerà */
      }
    }
    else /*function not enabled by proxi*/
    {
      valueReturn = MS_NOT_ENABLED;
    }
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }
  return valueReturn;
}

/*----------------------------------------------------------------------------*/
/*Name : Xxxx_yyyyzzzz                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
CTRL_State_t DOVFC_GetState(DOVFC_Handle_t hdl)
{
  CTRL_State_t returnValue;
  if (DOVFC_CfgTable[hdl].CMD_ACT_LEV == (DIOD_GetLevel(DOVFC_CfgTable[hdl].OUT_CHAN)))
  {
    returnValue = S_ON;
  }
  else
  {
    returnValue = S_OFF;
  }

  return returnValue;
}

/*----------------------------------------------------------------------------*/
/*Name : Xxxx_yyyyzzzz                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool DOVFC_PerformDiag(u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState)
{
  CTRL_State_t  outFbkStatus;
  bool valueReturn;
  CTRL_Fault_t newFault;
  DOVFC_CfgTable_t PtrCfgTable;
  
  if (hdl < DOVFC_HDL_MAX)
  {
    PtrCfgTable = DOVFC_CfgTable[hdl];
    
    /* comunico lo stato del comando */
    *cmdState = DOVFC_PrivateData[hdl].outState;
    
    /* inizializzazione */
    *fault    = CTRL_NOT_TESTED;
    /* comunico lo stato della macchina a stati */
    *faultState = DOVFC_PrivateData[hdl].faultState;
    
    if(DOVFC_PrivateData[hdl].functionState == CTRL_ENABLE)
    {
      /* Leggo il feedback */
      if (PtrCfgTable.FBK_ACT_LEV == PtrCfgTable.FBK_GET_OP((DIOD_Channel_t)PtrCfgTable.FBK_CHAN))
      {
        outFbkStatus = S_ON;
      }
      else
      {
        outFbkStatus = S_OFF;
      }

      /* Verifico se il feedback è coerente con il comando */
      if(outFbkStatus == (*cmdState))
      {
        newFault = CTRL_NO_FAULT;
      }
      else
      {
        if((*cmdState) == S_OFF)
        {
          if(PtrCfgTable.DRIVER_TYPE == LSD)
          {
            newFault = CTRL_OC_OR_STG;
          }
          else
          {
            newFault = CTRL_OC_OR_STB;
          }
        }
        else if ((*cmdState) == S_ON)
        {
          if(PtrCfgTable.DRIVER_TYPE == LSD)
          {
            newFault = CTRL_SHORT_TO_BAT;
          }
          else
          {
            newFault = CTRL_SHORT_TO_GND;
          }
        }
        else
        {
          /* MISRA 14.10 */
        }
      }

      if (DOVFC_PrivateData[hdl].lastFault != newFault)
      {
        DOVFC_PrivateData[hdl].diagDebounce++;

        if(DOVFC_PrivateData[hdl].diagDebounce == PtrCfgTable.DIAG_DEBOUNCE)
        {
          *fault = newFault;
          DOVFC_PrivateData[hdl].lastFault    = newFault;
          DOVFC_PrivateData[hdl].diagDebounce = 0U;
        }
        else
        {
          *fault = DOVFC_PrivateData[hdl].lastFault;
        }
      }
      else
      {
        *fault = DOVFC_PrivateData[hdl].lastFault;
        DOVFC_PrivateData[hdl].diagDebounce = 0u;
      }
    }
    else
    {
    }
  } 
  
   /* Comunico che la diagnosi è terminata */
  valueReturn = TRUE;
  
  return valueReturn;
}

void DOVFC_DecodeDiag(u08 hdl, CTRL_FaultState_t faultState)
{
  DOVFC_PrivateData[hdl].faultState = faultState;
  
  if(faultState == CTRL_NO_FAULT_STATE)
  {
    DOVFC_PrivateData[hdl].diagData = CTRL_NO_FAULT;
  }
  else if((faultState == CTRL_FAULT_CMD_ON_STATE)  ||
          (faultState == CTRL_FAULT_CMD_OFF_STATE) ||
          (faultState == CTRL_FAULT_CMD_ALL_STATE))
  {
    DOVFC_PrivateData[hdl].diagData = DOVFC_PrivateData[hdl].lastFault;
  }
  else
  {
    DOVFC_PrivateData[hdl].diagData = CTRL_NOT_TESTED;
  }
  
  /* Salvo lo stato del comando durante diagnosi*/
  DOVFC_PrivateData[hdl].diagDataState = DOVFC_PrivateData[hdl].outState;
}

CTRL_Fault_t DOVFC_GetDiag(DOVFC_Handle_t hdl)
{
  return DOVFC_PrivateData[hdl].diagData;
}

CTRL_State_t DOVFC_GetDiagState(DOVFC_Handle_t hdl)
{
  return DOVFC_PrivateData[hdl].diagDataState;
}


/**
* @brief This function is used to initialize the Diagnosis State Machine.
* @param hdl is the diagnosis line
* @param fault is the last fault detected (ie: stored in EEPROM)
* @return Returns the status of user request.
*/
DRVD_RStatus_t DOVFC_SetFault(DOVFC_Handle_t hdl, CTRL_Fault_t fault)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < DOVFC_HDL_MAX)
  {
    if (fault == CTRL_OPEN_LOAD)
    {
      DOVFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
    }
    else if (fault == CTRL_SHORT_TO_GND)
    {
      if(DOVFC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        DOVFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
      }
      else
      {
        DOVFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
    }
    else if (fault == CTRL_SHORT_TO_BAT)
    {
      if(DOVFC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        DOVFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
      else
      {
        DOVFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
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

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
void DOVFC_EnableDisable (DOVFC_Handle_t hdl, CTRL_EnSts_t state)
{
  DOVFC_PrivateData[hdl].functionState = state;
}
#endif /* end __DOVFC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/
