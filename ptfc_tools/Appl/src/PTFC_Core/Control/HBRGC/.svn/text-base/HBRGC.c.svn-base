/**
 * @file HBRGC.c
 * @brief Source code of driver for Infineon BTM7752 h-bridge chipset
 * @author Daniele Cloralio
 * @date 08 apr 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| DC           Daniele CLORALIO          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 08/apr/2015 0.1  DC      First version
| ----------  ---  ------  ----------------------------------------------------
| 01/ott/2015 0.2  DC      Improvements in diagnosis state machines, according to 
                           DOIFC_Diag_and_Recovery_v1.0.docx
 */

#define HBRGC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "HBRGC.h"

/* Module inhibition filter */
#ifdef __HBRGC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

HBRGC_PrivateData_t	HBRGC_PrivateData[HBRGC_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

void HBRGC_ResetDiag(HBRGC_Handle_t hdl);
DRVD_RStatus_t HBRGC_FreezeState(HBRGC_Handle_t hdl, CTRL_State_t enableFreeze);
void HBRGC_ResetState(u08 hdl);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function is used to initialize the local variable
 * @param none
 * @return void
 */
void HBRGC_Init(void)
{
  HBRGC_Handle_t hdl;

  for (hdl = (HBRGC_Handle_t)0; hdl < HBRGC_HDL_MAX; hdl++)
  {
    HBRGC_PrivateData[hdl].diagData        = CTRL_NOT_TESTED;
    HBRGC_PrivateData[hdl].diagDataState   = S_OFF;
    HBRGC_PrivateData[hdl].diagState       = SHORT_CIRCUIT_DIAG;
    HBRGC_PrivateData[hdl].lastFault       = CTRL_NOT_TESTED;
    HBRGC_PrivateData[hdl].outStateHS1     = S_OFF;
    HBRGC_PrivateData[hdl].outStateHS2     = S_OFF;
    HBRGC_PrivateData[hdl].oldOutStateHS1  = S_OFF;
    HBRGC_PrivateData[hdl].oldOutStateHS2  = S_OFF;
    HBRGC_PrivateData[hdl].faultState      = CTRL_NOT_TESTED_NO_FAULT_STATE;
    HBRGC_PrivateData[hdl].freeze          = S_OFF;
    HBRGC_PrivateData[hdl].diagRetry       = 0U;
    HBRGC_PrivateData[hdl].diagWaitCycle   = 0U;
    HBRGC_PrivateData[hdl].diagDebounce    = 0U;
    /* Inizializzo le uscite a 0 */
    HBRGC_ResetState(hdl);
  }

  HBRGC_CONFIG_INIT()
}

/* the HBRGC_Mgm call the HBRGC_PerformAndDecodeDiag() for each handle */
void HBRGC_Mgm(void)
{
  HBRGC_Handle_t hdl;

  for (hdl = (HBRGC_Handle_t)0; hdl < HBRGC_HDL_MAX; hdl++)
  {
      HBRGC_PerformAndDecodeDiag(hdl);
  }

}

/* This function can be used to perform synchronized diagnostic, must be called from module that use the handle */
void HBRGC_PerformAndDecodeDiag(HBRGC_Handle_t hdl)
{
  CTRL_Fault_t      newFault;
  CTRL_State_t      cmdState;
  CTRL_FaultState_t newState;

  HBRGC_PerformDiag(hdl, &cmdState, &newFault, &newState);

  newState = DIAGC_DiagFsmEvolve(newFault,cmdState,newState);

  HBRGC_DecodeDiag(hdl,newState);
}

/**
 * @brief This function is used to set the current output state related to the specified input pin
 *
 *****INPUT*****|*****OUTPUT*****
 *--------------|---------------*
 * INH  IN1  IN2| HS1 LS1 HS2 LS2
 *  0    0    0 |  0   0   0   0  standby
 *  1    0    0 |  0   1   0   1
 *  1    1    0 |  1   0   0   1  forward
 *  1    0    1 |  0   1   1   0  backward
 *  1    1    1 |  1   0   1   0  stop
 *--------------|---------------
 * @param hdl is the current h-bridge handle to be used
 * @param input is the input pin (IN1 or IN2)
 * @param state is the state to be set
 * @return returns the execution state.
 */
DRVD_RStatus_t HBRGC_SetState(HBRGC_Handle_t hdl, HBRGC_InputSelection_t input, CTRL_State_t state)
{
  DRVD_RStatus_t valueReturn;

  if ((hdl < HBRGC_HDL_MAX) && (input < HBRGC_INPUT_MAX))
  {
    valueReturn = MS_OK;
    // if diagnosis in off state is in progress, reset inhibit pin and inputs
    //    if (HBRGC_PrivateData[hdl].diagState == OPEN_LOAD_DETECTION)
    //    {
    //      HBRGC_ResetState(hdl);
    //    }
    if(state == S_PREVIOUS)
    {
      /* set the output as the one saved before */
      state = (input == HBRGC_INPUT_IN1) ? HBRGC_PrivateData[hdl].outStateHS1 : HBRGC_PrivateData[hdl].outStateHS2;
    }
    else
    {
      /* save HS state as current output state*/
      if (input == HBRGC_INPUT_IN1)
      {
        HBRGC_PrivateData[hdl].outStateHS1 = state;
      }
      else
      {
        HBRGC_PrivateData[hdl].outStateHS2 = state;
      }
    }

    if (HBRGC_PrivateData[hdl].freeze == S_OFF)
    {
      if (state == S_ON)
      {
        /* set inhibit pin */
        /* check if INH pin is already in ACTIVE LEVEL or not */
        if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL != (DIOD_GetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN)))
        {
          /* set input INH to ACTIVE LEVEL according to config table */
          if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_LOW);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_HIGH);
          }
        }
        /* set input PIN */
        /* set input pin INx to ACTIVE LEVEL according to config table */
        if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
        {
          if (input == HBRGC_INPUT_IN1)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_LOW);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_LOW);
          }
        }
        else
        {
          if (input == HBRGC_INPUT_IN1)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_HIGH);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_HIGH);
          }
        }
      } /* end S_ON */
      else if(state == S_OFF)
      {
        /* check if INH is not active, in case set it to active */
        if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL != (DIOD_GetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN)))
        {
          /* set input INH to ACTIVE LEVEL according to config table */
          if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_LOW);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_HIGH);
          }
        }
        /* set input PIN */
        /* set input PIN to NOT ACTIVE according to config table*/
        if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
        {
          if (input == HBRGC_INPUT_IN1)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_HIGH);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_HIGH);
          }
        }
        else
        {
          if (input == HBRGC_INPUT_IN1)
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_LOW);
          }
          else
          {
            DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_LOW);
          }
        }
      } /* end S_OFF */
      else
      {
        valueReturn = MS_PAR_NOT_OK;
      }
      /* check if we have to put the chip in standby */
      if ((HBRGC_CfgTable[hdl].ACTIVE_LEVEL == DIOD_GetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN)) &&
          (HBRGC_PrivateData[hdl].outStateHS1 == S_OFF) &&
          (HBRGC_PrivateData[hdl].outStateHS2 == S_OFF))
      {
        /* motor is in stop state, if diagnosis is not active put the chip in stand by */
        if ((HBRGC_PrivateData[hdl].diagState == SHORT_CIRCUIT_DIAG) ||
            (HBRGC_PrivateData[hdl].diagState == FAIL_CONFIRMED ))
        {
        /* set inhibit pin and two input pins to low */
          HBRGC_ResetState(hdl);
        }
      }
    }
    else /* HBRGC_PrivateData[hdl].freeze = S_ON */
    {
      /* Diagnosi critica in corso */
      /* Non aggiorno l'uscita, ci penserà poi la diagnosi quando terminerà */
    }
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }
  return valueReturn;
}

/**
 * @brief This function is used to retrieve the current state related to the specified input
 * @param hdl is the current handle
 * @param input is the input pin
 * @return returns the output state.
 */
CTRL_State_t HBRGC_GetState(HBRGC_Handle_t hdl, HBRGC_InputSelection_t input)
{
  CTRL_State_t returnValue;
  returnValue = S_OFF;

  if ((hdl < HBRGC_HDL_MAX) && (input < HBRGC_INPUT_MAX))
  {
    if (input == HBRGC_INPUT_IN1)
    {
      if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == (DIOD_GetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1)))
      {
        returnValue = S_ON;
      }
      else
      {
        returnValue = S_OFF;
      }
    }
    else
    {
      if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == (DIOD_GetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2)))
      {
        returnValue = S_ON;
      }
      else
      {
        returnValue = S_OFF;
      }
    }
  }

  return returnValue;
}

bool HBRGC_PerformDiag(u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState)
{
  bool valueReturn;
  u16  fbkLevel;

  /* set the current command state, out state is S_ON if only one high side is on */
  /* if both high side are on, motor is in stop state (S_OFF) */
  *cmdState = (CTRL_State_t)(HBRGC_PrivateData[hdl].outStateHS1 ^ HBRGC_PrivateData[hdl].outStateHS2);
  /* fault init */
  *fault = CTRL_NOT_TESTED;
  /* set the current diagnosis fsm state */
  *faultState = HBRGC_PrivateData[hdl].faultState;

  switch(HBRGC_PrivateData[hdl].diagState)
  {
  case SHORT_CIRCUIT_DIAG:
    /* Save the current commands state to check if it changes and revert it if needed */
    HBRGC_PrivateData[hdl].oldOutStateHS1 = HBRGC_PrivateData[hdl].outStateHS1;
    HBRGC_PrivateData[hdl].oldOutStateHS2 = HBRGC_PrivateData[hdl].outStateHS2;
    
    /* check current feedback level */
    fbkLevel = ADCC_GetLastChnData(HBRGC_CfgTable[hdl].FBK_CHAN);
    /* Verifico se il fbk è sopra la soglia di corto circuito */
    if (fbkLevel > HBRGC_CfgTable[hdl].SHORT_CIRCUIT_THRES)
    {
      if((HBRGC_PrivateData[hdl].outStateHS1 == S_ON) ||
          (HBRGC_PrivateData[hdl].outStateHS2 == S_ON))
      {
        HBRGC_PrivateData[hdl].diagDebounce++;
        valueReturn = FALSE;
        /* check if fail was already debounced */
        if ((HBRGC_PrivateData[hdl].diagDebounce == HBRGC_CfgTable[hdl].DIAG_DEBOUNCE) ||
            (HBRGC_PrivateData[hdl].lastFault == CTRL_SHORT_TO_GND))
        {
          /* destructive short, should actuate recovery */
          *fault = CTRL_SHORT_TO_GND;
          HBRGC_PrivateData[hdl].lastFault = CTRL_SHORT_TO_GND;
          HBRGC_PrivateData[hdl].diagDebounce = 0U;

          /* Strategia di recovery: spengo e frezzo l'uscita e passo nello stato wait, dopo riproverò a vedere se c'è ancora corto */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_OFF);        /* Spengo l'uscita */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_OFF);        /* Spengo l'uscita */
          HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_ON);      /* Congelo lo stato dell'uscita       */

          /* aggiorno le variabili per la recovery e passo all stato di wait */
          HBRGC_PrivateData[hdl].diagRetry = 0u;
          HBRGC_PrivateData[hdl].diagWaitCycle = 0u;
          HBRGC_PrivateData[hdl].diagState = RECOVERY_WAIT;
        }
        else
        {
          /* keep same state */
          HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
        }
      }
      else /* outState = S_OFF */
      {
        HBRGC_PrivateData[hdl].diagDebounce++;
        HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;

        /* check if fail was already debounced */
        if ((HBRGC_PrivateData[hdl].diagDebounce == HBRGC_CfgTable[hdl].DIAG_DEBOUNCE) ||
            (HBRGC_PrivateData[hdl].lastFault == CTRL_OC_OR_STB))
        {
          /* Gestione per smart driver che impostano un livello alto del fbk in caso di corto cicuito in off */
          *fault = CTRL_OC_OR_STB;
          HBRGC_PrivateData[hdl].lastFault = CTRL_OC_OR_STB;
          HBRGC_PrivateData[hdl].diagDebounce = 0U;

          /* diagnosis end */
          valueReturn = TRUE;
        }
        else
        {
          /* diagnosis not end yet */
          valueReturn = FALSE;
        }
      }
    }
    /* Verifico se c'è un open load */
    else if(fbkLevel < HBRGC_CfgTable[hdl].OPEN_CIRCUIT_THRES)
    {
      if (HBRGC_PrivateData[hdl].outStateHS1 ^ HBRGC_PrivateData[hdl].outStateHS2)
      {
        HBRGC_PrivateData[hdl].diagDebounce++;
        /* diagnosis not finished */
        valueReturn = FALSE;

        /* check if fail was already debounced */
        if ((HBRGC_PrivateData[hdl].diagDebounce == HBRGC_CfgTable[hdl].DIAG_DEBOUNCE) ||
            (HBRGC_PrivateData[hdl].lastFault == CTRL_OC_OR_STB))
        {
          HBRGC_PrivateData[hdl].diagDebounce = 0U;
          /* Possibile OPEN LOAD o SHORT TO BATT:
           * spengo l'uscita per poter discriminare i due casi */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_OFF);        /* Spengo l'uscita */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_OFF);        /* Spengo l'uscita */
          HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_ON);      /* Congelo lo stato dell'uscita       */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, HBRGC_PrivateData[hdl].oldOutStateHS1);        /* Memorizzo lo stato da ripristinare */
          HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, HBRGC_PrivateData[hdl].oldOutStateHS2);        /* Memorizzo lo stato da ripristinare */
          HBRGC_OL_TEST_OUT_OFF_START((HBRGC_Handle_t)hdl)   /* Chiamo una eventuale macro utente  */

          HBRGC_PrivateData[hdl].diagState = SHORT_TO_BATT_DIAG;
        }
        else
        {
          HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
        }
      }
      else if ((HBRGC_PrivateData[hdl].outStateHS1 == S_ON) &&
               (HBRGC_PrivateData[hdl].outStateHS2 == S_ON))
      {
        /* Non rilevo OC e corto a ground durante frenata */
        *fault = CTRL_NOT_TESTED;
        HBRGC_PrivateData[hdl].lastFault = CTRL_NOT_TESTED;

        /* diagnosis end */
        valueReturn = TRUE;
        HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
      }
      else /* entrambe le uscite a OFF */
      {
        /* Non è presente il corto a batteria e in OFF state non posso eseguire la diagnosi di open load, comunico NO_FAULT */
        *fault = CTRL_NO_FAULT;
        HBRGC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;
		HBRGC_PrivateData[hdl].diagDebounce = 0U;

        /* diagnosis end */
        valueReturn = TRUE;
        HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
      }
    }
    else
    {
      /* La corrente è nei limiti, nessun fault presente */
      *fault = CTRL_NO_FAULT;
      HBRGC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;
      HBRGC_PrivateData[hdl].diagDebounce = 0U;

      /* diagnosis end */
      valueReturn = TRUE;
      HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
    }
    break;

  case SHORT_CIRCUIT_RECOVERY:
    /* Leggo il feedback */
    fbkLevel = ADCC_GetLastChnData(HBRGC_CfgTable[hdl].FBK_CHAN);

    /* Verifico se il fbk è sopra la soglia di corto circuito */
    if (fbkLevel > HBRGC_CfgTable[hdl].SHORT_CIRCUIT_THRES)
    {
      /* turn off the output */
      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF); /* remove freeze state */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_OFF);  /* disable the output */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_OFF);  /* disable the output */
      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_ON); /*freeze state again */

      HBRGC_PrivateData[hdl].diagRetry++;

      if(HBRGC_PrivateData[hdl].diagRetry == HBRGC_CfgTable[hdl].REC_RETRY)
      {
        /* restore previous state */
        HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, HBRGC_PrivateData[hdl].oldOutStateHS1);        /* Memorizzo lo stato da ripristinare */
        HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, HBRGC_PrivateData[hdl].oldOutStateHS2);        /* Memorizzo lo stato da ripristinare */
        /*remove freeze and return to normal state */
        HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF); /* remove freeze state */
        HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
        HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
      
        HBRGC_PrivateData[hdl].diagState = FAIL_CONFIRMED;
        /* diagnosis end */
        valueReturn = TRUE;
      }
      else
      {
        HBRGC_PrivateData[hdl].diagWaitCycle = 0u;
        HBRGC_PrivateData[hdl].diagState = RECOVERY_WAIT;
      }
    }
    else
    {
      /* restore previous state */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, HBRGC_PrivateData[hdl].oldOutStateHS1);        /* Memorizzo lo stato da ripristinare */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, HBRGC_PrivateData[hdl].oldOutStateHS2);        /* Memorizzo lo stato da ripristinare */
      /*remove freeze and return to normal state */
      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF); /* remove freeze state */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
      HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
    }
    break;

  case RECOVERY_WAIT:
    *fault    = HBRGC_PrivateData[hdl].lastFault;
    HBRGC_PrivateData[hdl].diagWaitCycle++;

    if(HBRGC_PrivateData[hdl].diagWaitCycle == HBRGC_CfgTable[hdl].REC_WAIT_CYCLES)
    {
      /* try to enable again the output */
      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF); /* remove freeze state */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_ON);  /* enable the output */
      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_ON);  /* enable the output */
      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_ON); /*freeze state again */
      HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_RECOVERY;
    }

    valueReturn = FALSE;
    break;


  case SHORT_TO_BATT_DIAG:
    /* Comando OFF */

    /* Leggo il feedback */
    fbkLevel = ADCC_GetLastChnData(HBRGC_CfgTable[hdl].FBK_CHAN);

    if(fbkLevel < HBRGC_CfgTable[hdl].OPEN_CIRCUIT_THRES)
    {
      *fault = CTRL_OC_OR_STB;
      HBRGC_PrivateData[hdl].lastFault = CTRL_OC_OR_STB;

//      /* Strategia di recovery: spengo e frezzo l'uscita e passo nello stato wait, dopo riproverò a vedere se c'è ancora corto */
//      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF);   /* Scongelo l'uscita */
//      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_OFF);        /* Spengo l'uscita */
//      HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_OFF);        /* Spengo l'uscita */
//      HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_ON);      /* Congelo lo stato dell'uscita       */
//
//      /* aggiorno le variabili per la recovery e passo all stato di wait */
//      HBRGC_PrivateData[hdl].diagRetry = 0u;
//      HBRGC_PrivateData[hdl].diagWaitCycle = 0u;
//      HBRGC_PrivateData[hdl].diagState = RECOVERY_WAIT;
//      valueReturn = FALSE;
    }
    else
    {
      *fault = CTRL_NO_FAULT; /* Il corto circuito a batteria lo segnalo solo con comando richiesto = OFF */
      HBRGC_PrivateData[hdl].lastFault = CTRL_NO_FAULT;
    }
    HBRGC_FreezeState((HBRGC_Handle_t)hdl, S_OFF);   /* Scongelo l'uscita */
    HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN1, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
    HBRGC_SetState((HBRGC_Handle_t)hdl, HBRGC_INPUT_IN2, S_PREVIOUS); /* Ripristino lo stato dell'uscita */
    HBRGC_OL_TEST_OUT_OFF_END((HBRGC_Handle_t)hdl)   /* Chiamo una eventuale macro utente */

    /* Ho finito la diagnosi, ritorno allo stato iniziale di controllo corto circuito */
    HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
    valueReturn = TRUE;
    break;


  case FAIL_CONFIRMED:
    if ((HBRGC_PrivateData[hdl].oldOutStateHS1 != HBRGC_PrivateData[hdl].outStateHS1) ||
        (HBRGC_PrivateData[hdl].oldOutStateHS2 != HBRGC_PrivateData[hdl].outStateHS2))
    {
      HBRGC_ResetDiag((HBRGC_Handle_t)hdl);
    }
    break;


  default:
    /* Error */
    //HBRGC_ResetDiag((HBRGC_Handle_t)hdl);
    valueReturn = TRUE; /* Comunico al gestore della diagnosi che ho finito */
    break;

  }
  return valueReturn;
}

void HBRGC_ResetState(u08 hdl)
{
  if (HBRGC_CfgTable[hdl].ACTIVE_LEVEL == L_LOW)
  {
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_HIGH);
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_HIGH);
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_HIGH);
  }
  else
  {
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INHIBIT_CHAN, L_LOW);
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN1, L_LOW);
    DIOD_SetLevel(HBRGC_CfgTable[hdl].INPUT_CHAN2, L_LOW);
  }
  HBRGC_PrivateData[hdl].outStateHS1 = S_OFF;
  HBRGC_PrivateData[hdl].outStateHS2 = S_OFF;
}

void HBRGC_DecodeDiag(u08 hdl, CTRL_FaultState_t faultState)
{
  HBRGC_PrivateData[hdl].faultState = faultState;

  if(faultState == CTRL_NO_FAULT_STATE)
  {
    HBRGC_PrivateData[hdl].diagData = CTRL_NO_FAULT;
  }
  else if((faultState == CTRL_FAULT_CMD_ON_STATE)  ||
      (faultState == CTRL_FAULT_CMD_OFF_STATE) ||
      (faultState == CTRL_FAULT_CMD_ALL_STATE))
  {
    HBRGC_PrivateData[hdl].diagData = HBRGC_PrivateData[hdl].lastFault;
  }
  else
  {
    HBRGC_PrivateData[hdl].diagData = CTRL_NOT_TESTED;
  }

  HBRGC_PrivateData[hdl].diagDataState =  (CTRL_State_t) (HBRGC_PrivateData[hdl].oldOutStateHS1 ^ HBRGC_PrivateData[hdl].oldOutStateHS2);
}

CTRL_Fault_t HBRGC_GetDiag(HBRGC_Handle_t hdl)
{
  return HBRGC_PrivateData[hdl].diagData;
}

CTRL_State_t HBRGC_GetDiagState(HBRGC_Handle_t hdl)
{
  return HBRGC_PrivateData[hdl].diagDataState;
}

void HBRGC_ResetDiag(HBRGC_Handle_t hdl)
{
  /* Set fault to not tested: */
  HBRGC_PrivateData[hdl].lastFault = CTRL_NOT_TESTED;
  
  /*remove eventually present freezed state */
  HBRGC_FreezeState(hdl,S_OFF);

  HBRGC_PrivateData[hdl].diagState = SHORT_CIRCUIT_DIAG;
}

DRVD_RStatus_t HBRGC_FreezeState(HBRGC_Handle_t hdl, CTRL_State_t enableFreeze)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < HBRGC_HDL_MAX)
  {
    HBRGC_PrivateData[hdl].freeze = enableFreeze;

    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief This function is used to initialize the Diagnosis State Machine to a specific fault
 * @param hdl is the chipset to diagnose
 * @param fault is the last fault detected (ie: stored in EEPROM)
 * @return Returns the status of user request.
 */
DRVD_RStatus_t HBRGC_SetFault(HBRGC_Handle_t hdl, CTRL_Fault_t fault)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (hdl < HBRGC_HDL_MAX)
  {
    if (fault == CTRL_OPEN_LOAD)
    {
      HBRGC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
    }
    else if (fault == CTRL_SHORT_TO_GND)
    {
      HBRGC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_ON_STATE;
    }
    else if (fault == CTRL_SHORT_TO_BAT)
    {
      HBRGC_PrivateData[hdl].faultState = CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE;
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

#endif /* end __HBRGC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/
