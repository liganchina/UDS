/********************************************************************************/
/* @F_PROJECT:          PTFC                                                    */
/* F_NAME:              DOIFC - Digital Output current(I) Feedback              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1843-FG3                                  */
/* F_CREATION_DATE:     21/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/********************(C) Copyright 2012 Bitron S.p.A. ***************************/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 21/giu/2013     0.1  Matteo MASTRODONATO
 */

#define DOIFC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "DOIFC.h"

/* Module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

DOIFC_PrivateData_t	DOIFC_PrivateData[DOIFC_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

void DOIFC_ResetDiag(DOIFC_Handle_t hdl);
uint16_t Doifc_GetFbk(DOIFC_Handle_t hdl);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief Module initialization. Called once at system startup
 * @param None
 * @return None
 */
void DOIFC_Init(void)
{
  DOIFC_Handle_t hdl;

  for (hdl = (DOIFC_Handle_t)0; hdl < DOIFC_HDL_MAX; hdl++)
  {
    DOIFC_PrivateData[hdl].diagData      = CTRL_NOT_TESTED;
    DOIFC_PrivateData[hdl].diagDataState = S_OFF;
    DOIFC_PrivateData[hdl].diagState     = SHORT_CIRCUIT_DIAG;
    DOIFC_PrivateData[hdl].lastFault     = CTRL_NOT_TESTED;
    DOIFC_PrivateData[hdl].outState      = S_OFF;
    DOIFC_PrivateData[hdl].oldOutState   = S_OFF;
    DOIFC_PrivateData[hdl].faultState    = CTRL_NOT_TESTED_NO_FAULT_STATE;
    DOIFC_PrivateData[hdl].freeze        = S_OFF;
    DOIFC_PrivateData[hdl].diagRetry     = 0u;
    DOIFC_PrivateData[hdl].diagWaitCycle = 0u;
    DOIFC_PrivateData[hdl].functionState = CTRL_ENABLE;
    
    /* Inizializzo la diagnosi */
    DOIFC_ResetDiag(hdl);
  }

  DOIFC_CONFIG_INIT()
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
DRVD_RStatus_t DOIFC_SetState(DOIFC_Handle_t hdl, CTRL_State_t state)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < DOIFC_HDL_MAX)
  {
    if (DOIFC_PrivateData[hdl].functionState == CTRL_ENABLE)
    {
      if(state == S_PREVIOUS)
      {
        /* Setto l'uscita allo stato memorizzato in precedenza */
        state = DOIFC_PrivateData[hdl].outState;
      }
      else
      {
        /* Memorizzo lo stato dell'uscita richiesto */
        DOIFC_PrivateData[hdl].outState = state;
      }

      if (DOIFC_PrivateData[hdl].freeze == S_OFF)
      {
        if (state == S_ON)
        {
          if (DOIFC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
          {
            DIOD_SetLevel(DOIFC_CfgTable[hdl].OUT_CHAN, L_LOW);
          }
          else
          {
            DIOD_SetLevel(DOIFC_CfgTable[hdl].OUT_CHAN, L_HIGH);
          }
        }
        else if(state == S_OFF)
        {
          if (DOIFC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
          {
            DIOD_SetLevel(DOIFC_CfgTable[hdl].OUT_CHAN, L_HIGH);
          }
          else
          {
            DIOD_SetLevel(DOIFC_CfgTable[hdl].OUT_CHAN, L_LOW);
          }
        }
        else
        {
          valueReturn = MS_PAR_NOT_OK;
        }
      }
      else /* DOIFC_PrivateData[hdl].freeze = S_ON */
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
CTRL_State_t DOIFC_GetState(DOIFC_Handle_t hdl)
{
  CTRL_State_t returnValue;
  if (DOIFC_CfgTable[hdl].ACTIVE_LEVEL == (DIOD_GetLevel(DOIFC_CfgTable[hdl].OUT_CHAN)))
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
/*See document DOIFC_Diag_and_Recovery_v1.0.docx for more inforamtion         */
/*----------------------------------------------------------------------------*/
bool DOIFC_PerformDiag(u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState)
{
  u16  fbkLevel;
  bool valueReturn;

  /* comunico lo stato del comando */
  *cmdState = DOIFC_PrivateData[hdl].outState;
  /* inizializzatione */
  *fault    = DOIFC_PrivateData[hdl].lastFault;
  /* comunico lo stato della macchina a stati */
  *faultState = DOIFC_PrivateData[hdl].faultState;

  if(DOIFC_PrivateData[hdl].functionState == CTRL_ENABLE)
  {
    switch(DOIFC_PrivateData[hdl].diagState)
    {
      case SHORT_CIRCUIT_DIAG:
        /* Salvo lo stato del comando a inizio diagnosi, se durante la diagnosi cambia la invalido */
        DOIFC_PrivateData[hdl].oldOutState = DOIFC_PrivateData[hdl].outState;

        /* Leggo il feedback */
        fbkLevel = Doifc_GetFbk((DOIFC_Handle_t)hdl);

        /* Verifico se il fbk è sopra la soglia di corto circuito */
        if (fbkLevel > DOIFC_CfgTable[hdl].SHORT_CIRCUIT_THRES)
        {
          if(DOIFC_PrivateData[hdl].outState == S_ON)
          {
            /* destructive short, actuate recovery */
            *fault = CTRL_NOT_TESTED;
            DOIFC_PrivateData[hdl].lastFault = CTRL_NOT_TESTED;
            valueReturn = TRUE;
          
            /* Strategia di recovery: spengo e frezzo l'uscita e passo nello stato wait, dopo riproverò a vedere se c'è ancora corto */
            DOIFC_SetState((DOIFC_Handle_t)hdl, S_OFF);        /* Spengo l'uscita */
            DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_ON);      /* Congelo lo stato dell'uscita       */

            /* aggiorno le variabili per la recovery e passo all stato di wait */
            DOIFC_PrivateData[hdl].diagRetry = 0u;
            DOIFC_PrivateData[hdl].diagWaitCycle = 0u;
            DOIFC_PrivateData[hdl].diagState = RECOVERY_WAIT;
          }
          else /* outState = S_OFF */
          {
            /* Gestione per smart driver che impostano un livello alto del fbk in caso di corto cicuito in off */
            if(DOIFC_CfgTable[hdl].DRIVER_TYPE == HSD)
            {
              if (DOIFC_CfgTable[hdl].OC_OR_STB_DETECTION == TRUE)
              {
                /* OPEN LOAD o SHORT TO BATT fails: if configured to TRUE
                 * it is possible to distinguish between the two fails */
                *fault = CTRL_SHORT_TO_BAT;
                DOIFC_PrivateData[hdl].lastFault = CTRL_SHORT_TO_BAT;
              }
              else
              {
                /* no difference between OPEN LOAD and SHORT TO BATT */
                *fault = CTRL_OC_OR_STB;
                DOIFC_PrivateData[hdl].lastFault = CTRL_OC_OR_STB;
              }
            }
            else /* LSD */
            {
              *fault = CTRL_SHORT_TO_GND;
              DOIFC_PrivateData[hdl].lastFault = CTRL_SHORT_TO_GND;
            }

            /* diagnosis end */
            valueReturn = TRUE;
          }
        }
        /* Verifico se c'è un open load */
        else if(fbkLevel < DOIFC_CfgTable[hdl].OPEN_CIRCUIT_THRES)
        {
          if(DOIFC_PrivateData[hdl].outState == S_ON)
          {
            if (DOIFC_CfgTable[hdl].OC_OR_STB_DETECTION == TRUE)
            {
              /* Possibile OPEN LOAD o SHORT TO BATT: se configurato in DOIFC_config.c
               * spengo l'uscita per poter discriminare i due casi */
              DOIFC_SetState((DOIFC_Handle_t)hdl, S_OFF);
              DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_ON);      /* Congelo lo stato dell'uscita       */
              DOIFC_SetState((DOIFC_Handle_t)hdl, S_ON);         /* Memorizzo lo stato da ripristinare */
              DOIFC_OL_TEST_OUT_OFF_START((DOIFC_Handle_t)hdl)   /* Chiamo una eventuale macro utente  */

              DOIFC_PrivateData[hdl].diagState = SHORT_TO_BATT_DIAG;
            
              /* diagnosis not finished */
              valueReturn = FALSE;
            }
            else /* no difference between OPEN LOAD and SHORT TO BATT fails */
            {
              *fault = CTRL_OC_OR_STB;
              DOIFC_PrivateData[hdl].lastFault = CTRL_OC_OR_STB;

              /* diagnosis end */
              valueReturn = TRUE;
            }
          }
          else /* outState = S_OFF */
          {
            /* Non è presente il corto a batteria e in OFF state non posso eseguire la diagnosi di open load, comunico NO_FAULT */
            *fault = CTRL_NO_FAULT;
            DOIFC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;

            /* diagnosis end */
            valueReturn = TRUE;
          }
        }
        else
        {
          /* La corrente è nei limiti, nessun fault presente */
          *fault = CTRL_NO_FAULT;
          DOIFC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;
          
          /* diagnosis end */
          valueReturn = TRUE;
        }

        break;

      case SHORT_CIRCUIT_RECOVERY:
        /* Leggo il feedback */
        fbkLevel = Doifc_GetFbk((DOIFC_Handle_t)hdl);

        /* Verifico se il fbk è sopra la soglia di corto circuito */
        if (fbkLevel > DOIFC_CfgTable[hdl].SHORT_CIRCUIT_THRES)
        {
          /* turn off the output */
          DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_OFF); /* remove freeze state */
          DOIFC_SetState((DOIFC_Handle_t)hdl, S_OFF); /* disable the output */
          DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_ON); /*freeze state again */

          DOIFC_PrivateData[hdl].diagRetry++;

          if(DOIFC_PrivateData[hdl].diagRetry == DOIFC_CfgTable[hdl].REC_RETRY)
          {
            /* set the fault */
            if(DOIFC_CfgTable[hdl].DRIVER_TYPE == HSD)
            {
              *fault = CTRL_SHORT_TO_GND;
              DOIFC_PrivateData[hdl].lastFault = CTRL_SHORT_TO_GND;
            }
            else /* LSD */
            {
              if (DOIFC_CfgTable[hdl].OC_OR_STB_DETECTION == TRUE)
              {
                /* OPEN LOAD o SHORT TO BATT fails: if configured to TRUE
                 * it is possible to distinguish between the two fails */
                *fault = CTRL_SHORT_TO_BAT;
                DOIFC_PrivateData[hdl].lastFault = CTRL_SHORT_TO_BAT;
              }
              else
              {
                /* no difference between OPEN LOAD and SHORT TO BATT */
                *fault = CTRL_OC_OR_STB;
                DOIFC_PrivateData[hdl].lastFault = CTRL_OC_OR_STB;
              }
            }

            DOIFC_PrivateData[hdl].diagState = FAIL_CONFIRMED;
            DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_OFF); /* remove freeze state */
            DOIFC_SetState((DOIFC_Handle_t)hdl, S_PREVIOUS); /* restore previous state */
            /* diagnosis end */
            if(DOIFC_CfgTable[hdl].MANAGE_DIAG == TRUE)
            {
              valueReturn = FALSE;
            }
            else
            {
              valueReturn = TRUE;
            }
          }
          else
          {
            DOIFC_PrivateData[hdl].diagWaitCycle = 0u;
            DOIFC_PrivateData[hdl].diagState = RECOVERY_WAIT;
          }
        }
        else
        {
          /*remove freeze and return to normal state */
          DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_OFF); /* remove freeze state */
          DOIFC_SetState((DOIFC_Handle_t)hdl, S_PREVIOUS);  /* restore previous state */
          DOIFC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
        }
        break;
        
      case RECOVERY_WAIT:
        *fault    = DOIFC_PrivateData[hdl].lastFault;
        DOIFC_PrivateData[hdl].diagWaitCycle++;
        
        if(DOIFC_PrivateData[hdl].diagWaitCycle == DOIFC_CfgTable[hdl].REC_WAIT_CYCLES)
        {
          /* try to enable again the output */
          DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_OFF); /* remove freeze state */
          DOIFC_SetState((DOIFC_Handle_t)hdl, S_ON); /* enable the output */
          DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_ON); /*freeze state again */
          DOIFC_PrivateData[hdl].diagState = SHORT_CIRCUIT_RECOVERY;
        }
        
        valueReturn = FALSE;
        break;
        
      case SHORT_TO_BATT_DIAG:
      /* This state of the diagnosis state machine is reached only if
       * OC_OR_STB_DETECTION is TRUE in DOIFC_config.c
       * The output was switched off in the previous state to distinguish
       * between OPEN LOAD and SHORT TO BATT */

        /* Comando OFF */
        fbkLevel = Doifc_GetFbk((DOIFC_Handle_t)hdl);

        if(fbkLevel < DOIFC_CfgTable[hdl].OPEN_CIRCUIT_THRES)
        {
          *fault = CTRL_OPEN_LOAD;
          DOIFC_PrivateData[hdl].lastFault = CTRL_OPEN_LOAD;
        }
        else
        {
          *fault = CTRL_NO_FAULT; /* Il corto circuito a batteria lo segnalo solo con comando richiesto = OFF */
          DOIFC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;
        }

        DOIFC_FreezeState((DOIFC_Handle_t)hdl, S_OFF);   /* Scongelo l'uscita */
        DOIFC_SetState((DOIFC_Handle_t)hdl, S_PREVIOUS); /* Ripristino lo stato dell'uscita */

        DOIFC_OL_TEST_OUT_OFF_END((DOIFC_Handle_t)hdl)   /* Chiamo una eventuale macro utente */

        /* Ho finito la diagnosi, ritorno allo stato iniziale di controllo corto circuito */
        DOIFC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
        valueReturn = TRUE;
        break;

      case FAIL_CONFIRMED:
        if(DOIFC_CfgTable[hdl].MANAGE_DIAG == TRUE)
        {
          if(DOIFC_PrivateData[hdl].oldOutState != DOIFC_PrivateData[hdl].outState)
          {
            /* diagnosis end */
            valueReturn = FALSE;
            DOIFC_ResetDiag((DOIFC_Handle_t)hdl);
          }
          else
          {
             /* diagnosis end */
             valueReturn = TRUE;
          }
        }
        else
        {
          /* The diagnosis reset is performed by external module */
        }

        break;

      default:
        /* Error */
        DOIFC_ResetDiag((DOIFC_Handle_t)hdl);
        valueReturn = TRUE; /* Comunico al gestore della diagnosi che ho finito */
        break;
    }
  }
  else
  {}
  
  return valueReturn;
}

void DOIFC_DecodeDiag(u08 hdl, CTRL_FaultState_t faultState)
{
  DOIFC_PrivateData[hdl].faultState = faultState;

  if(faultState == CTRL_NO_FAULT_STATE)
  {
    DOIFC_PrivateData[hdl].diagData = CTRL_NO_FAULT;
  }
  else if((faultState == CTRL_FAULT_CMD_ON_STATE)  ||
          (faultState == CTRL_FAULT_CMD_OFF_STATE) ||
          (faultState == CTRL_FAULT_CMD_ALL_STATE))
  {
    DOIFC_PrivateData[hdl].diagData = DOIFC_PrivateData[hdl].lastFault;
  }
  else
  {
    DOIFC_PrivateData[hdl].diagData = CTRL_NOT_TESTED;
  }

  DOIFC_PrivateData[hdl].diagDataState = DOIFC_PrivateData[hdl].oldOutState;
}

CTRL_Fault_t DOIFC_GetDiag(DOIFC_Handle_t hdl)
{
  return DOIFC_PrivateData[hdl].diagData;
}

CTRL_State_t DOIFC_GetDiagState(DOIFC_Handle_t hdl)
{
  return DOIFC_PrivateData[hdl].diagDataState;
}

void DOIFC_ResetDiag(DOIFC_Handle_t hdl)
{
//
//#if (DOIFC_HIGH_GAIN_FBK_EN == TRUE)
//  /* Spengo il guadagno di corrente */
//  //if(DOIFC_CfgTable[hdl].FBK_GAIN_CHAN != CHAN_NOT_USED)
//  {
//    if (DOIFC_CfgTable[hdl].FBK_GAIN_ACT_LEV == L_HIGH)
//    {
//      DIOD_SetLevel(DOIFC_CfgTable[hdl].FBK_GAIN_CHAN, L_LOW);
//    }
//    else
//    {
//      DIOD_SetLevel(DOIFC_CfgTable[hdl].FBK_GAIN_CHAN, L_HIGH);
//    }
//  }
//#endif /* DOIFC_HIGH_GAIN_FBK_EN = TRUE */
  
  /* Set fault to not tested: */
  DOIFC_PrivateData[hdl].lastFault = CTRL_NOT_TESTED;
  
  /*remove eventually present freezed state */
  DOIFC_FreezeState(hdl,S_OFF);

  DOIFC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
}

DRVD_RStatus_t DOIFC_FreezeState(DOIFC_Handle_t hdl, CTRL_State_t enableFreeze)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < DOIFC_HDL_MAX)
  {
    DOIFC_PrivateData[hdl].freeze = enableFreeze;

    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function is used to initialize the Diagnosis State Machine.
 * @param hdl is the diagnosis line
 * @param fault is the last fault detected (ie: stored in EEPROM)
 * @return Returns the status of user request.
 */
DRVD_RStatus_t DOIFC_SetFault(DOIFC_Handle_t hdl, CTRL_Fault_t fault)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < DOIFC_HDL_MAX)
  {
    if (fault == CTRL_OPEN_LOAD)
    {
      DOIFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
    }
    else if (fault == CTRL_SHORT_TO_GND)
    {
      if(DOIFC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        DOIFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
      }
      else
      {
        DOIFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
    }
    else if (fault == CTRL_SHORT_TO_BAT)
    {
      if(DOIFC_CfgTable[hdl].DRIVER_TYPE == HSD)
      {
        DOIFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
      }
      else
      {
        DOIFC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
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

/* the DOIFC_Mgm call the DOIFC_PerformAndDecodeDiag() for each handle if MANAGE_DIAG = TRUE */
void DOIFC_Mgm(void)
{
  DOIFC_Handle_t hdl;

  for (hdl = (DOIFC_Handle_t)0; hdl < DOIFC_HDL_MAX; hdl++)
  {
    if(DOIFC_CfgTable[hdl].MANAGE_DIAG == TRUE)
    {
      DOIFC_PerformAndDecodeDiag(hdl);
    }
  }

}

/* This function can be used to perform synchronized diagnostic, must be called from module that use the handle */
void DOIFC_PerformAndDecodeDiag(DOIFC_Handle_t hdl)
{
  CTRL_Fault_t      newFault;
  CTRL_State_t      cmdState;
  CTRL_FaultState_t newState;
  bool              diagEnd;
  
  diagEnd = DOIFC_PerformDiag(hdl, &cmdState, &newFault, &newState);

  if (diagEnd == TRUE)
  {
    newState = DIAGC_DiagFsmEvolve(newFault,cmdState,newState);
    DOIFC_DecodeDiag(hdl,newState);
  }
}

uint16_t Doifc_GetFbk(DOIFC_Handle_t hdl)
{
  uint16_t ret_val;
  
  if(DOIFC_CfgTable[hdl].FBK_CHAN != ADCC_CHN_NMB)
  {
    ret_val = ADCC_GetLastChnData(DOIFC_CfgTable[hdl].FBK_CHAN);
  }
  else
  {
    ret_val = DOIFC_GET_FBK(hdl);
  }
  
  return ret_val;
}

void DOIFC_DiagExtReset(DOIFC_Handle_t hdl)
{
  /* Check if the handle can be resetted from outside */
  if(DOIFC_CfgTable[hdl].MANAGE_DIAG == FALSE)
  {
    DOIFC_ResetDiag(hdl);
  }
}

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
void DOIFC_EnableDisable (DOIFC_Handle_t hdl, CTRL_EnSts_t state)
{
  DOIFC_PrivateData[hdl].functionState = state;
}

#endif /* end __DOIFC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/
