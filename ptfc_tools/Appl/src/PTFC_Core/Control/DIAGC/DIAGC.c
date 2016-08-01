/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DIAGC                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/giu/2013                                                 */
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
| 24/giu/2013     0.1  Matteo MASTRODONATO
*/

#define DIAGC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "DIAGC_config.h"
#include "DIAGC.h"

/* Module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef enum Diagc_DiagEvent_e
{
  EV_WAIT,
  EV_FAULT_CMD_OFF,
  EV_FAULT_CMD_ON,
  EV_NO_FAULT_CMD_OFF,
  EV_NO_FAULT_CMD_ON,
  EV_FAULT_CMD_ALL,
  EV_NO_FAULT_CMD_ALL,
  DIAGC_NUM_EV
} Diagc_DiagEvent_t;


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

static DIAGC_Group_t  DIAGC_CurrentGroup;
static bool           DIAGC_GroupEnded;
static bool           DIAGC_ChanDiagEnded[DIAGC_HDL_MAX];

static const CTRL_FaultState_t DIAGC_StateMachine[DIAGC_NUM_EV][CTRL_NUM_FAULT_STATE] = {
/* STATE/INP_EVENT */

/* EV_WAIT             */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_NOT_TESTED_NO_FAULT_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_FAULT_CMD_ON_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_FAULT_CMD_OFF_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_NOT_TESTED_FAULT_CMD_ON_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_NOT_TESTED_FAULT_STATE         },

/* EV_FAULT_CMD_OFF    */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_FAULT_CMD_OFF_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_FAULT_CMD_OFF_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_FAULT_CMD_OFF_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_FAULT_CMD_OFF_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_FAULT_CMD_OFF_STATE            },

/* EV_FAULT_CMD_ON     */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_FAULT_CMD_ON_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_FAULT_CMD_ON_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_FAULT_CMD_ON_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_FAULT_CMD_ON_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_FAULT_CMD_ON_STATE             },

/* EV_NO_FAULT_CMD_OFF */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_NO_FAULT_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_NOT_TESTED_FAULT_CMD_ON_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_NOT_TESTED_FAULT_CMD_ON_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_NOT_TESTED_FAULT_CMD_ON_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  },

/* EV_NO_FAULT_CMD_ON  */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_NO_FAULT_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE },

/* EV_FAULT_CMD_ALL    */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_FAULT_CMD_ALL_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_FAULT_CMD_ALL_STATE            },

/* EV_NO_FAULT_CMD_ALL */ /* CTRL_NOT_TESTED_NO_FAULT_STATE      --> */ { CTRL_NO_FAULT_STATE,
                          /* CTRL_NO_FAULT_STATE                 --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ON_STATE             --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_OFF_STATE            --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_FAULT_CMD_ALL_STATE            --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_NOT_TESTED_FAULT_CMD_ON_STATE  --> */   CTRL_NO_FAULT_STATE,
                          /* CTRL_NOT_TESTED_FAULT_STATE         --> */   CTRL_NO_FAULT_STATE                 }
};


/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static Diagc_DiagEvent_t Diagc_NewEvent(CTRL_State_t cmdState, CTRL_Fault_t newFault);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
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
void DIAGC_Init(void)
{
  DIAGC_Handle_t    hdl;

  DIAGC_CurrentGroup = DIAGC_GROUP_00;
  DIAGC_GroupEnded   = TRUE;

  for (hdl = (DIAGC_Handle_t)0U; hdl < DIAGC_HDL_MAX; hdl++)
  {
    DIAGC_ChanDiagEnded[hdl] = FALSE;
  }
}

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
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

void DIAGC_Mgm(void)
{
  CTRL_Fault_t      newFault;
  CTRL_State_t      cmdState;
  DIAGC_Handle_t    hdl;
  Diagc_DiagEvent_t DiagEvent;
  CTRL_FaultState_t newState;

#if (DIAGC_ENABLE_GROUP_CBK == TRUE)
  DIAGC_Group_t     tmpGroup;

  if ((DIAGC_CfgCbkTable[DIAGC_CurrentGroup].START_GROUP_DIAG != NULL) && (DIAGC_GroupEnded == TRUE))
  {
    DIAGC_CfgCbkTable[DIAGC_CurrentGroup].START_GROUP_DIAG(DIAGC_CurrentGroup);
  }
  else
  {
  }
#endif /* DIAGC_ENABLE_GROUP_CBK = TRUE */
  
  DIAGC_GroupEnded = TRUE;

  for (hdl = (DIAGC_Handle_t)0U; hdl < DIAGC_HDL_MAX; hdl++)
  {
    if ((DIAGC_CfgTable[hdl].DIAG_GROUP == DIAGC_CurrentGroup) &&
        (DIAGC_ChanDiagEnded[hdl]       == FALSE))
    {
      /* Eseguo la diagnosi dell'oggetto corrente, facendomi ritornare:
       * - Stato Comando,
       * - ultimo Fault,
       * - lo stato della macchina a stati di diagnosi */

      DIAGC_ChanDiagEnded[hdl] = DIAGC_CfgTable[hdl].PERFORM_DIAG_FUNC(DIAGC_CfgTable[hdl].DIAG_OBJ_HDL, &cmdState, &newFault, &newState);

      if(DIAGC_ChanDiagEnded[hdl] == FALSE)
      {
        DIAGC_GroupEnded = FALSE;
      }
      else
      {
        /* NOP */
      }

      /* Calcolo il nuovo evento di diagnosi */
      DiagEvent = Diagc_NewEvent(cmdState, newFault);

      /* Gestione macchina a stati */
      newState = DIAGC_StateMachine[DiagEvent][newState];

      /* Comunico l'evoluzione della macchina a stati all'oggetto che sto diagnosticando */
      DIAGC_CfgTable[hdl].DECODE_DIAG_FUNC(DIAGC_CfgTable[hdl].DIAG_OBJ_HDL, newState);
    }
  }

  if (DIAGC_GroupEnded == TRUE)
  {
#if (DIAGC_ENABLE_GROUP_CBK == TRUE)
    tmpGroup = DIAGC_CurrentGroup;
#endif /* DIAGC_ENABLE_GROUP_CBK = TRUE */

    /* Evolvo il gruppo prima della callback poichè all'interno l'utende potrebbe
     * chiamare la SetNextGroup, quindi aggiornando il gruppo dopo andrei a
     * sovrascrivere (incrementare) quello appena settato. */
    DIAGC_CurrentGroup++;
    DIAGC_CurrentGroup %= DIAGC_GROUP_MAX;

    for (hdl = (DIAGC_Handle_t)0U; hdl < DIAGC_HDL_MAX; hdl++)
    {
      if (DIAGC_CfgTable[hdl].DIAG_GROUP == DIAGC_CurrentGroup)
      {
        DIAGC_ChanDiagEnded[hdl] = FALSE;
      }
      else{}
    }

#if (DIAGC_ENABLE_GROUP_CBK == TRUE)
    if (DIAGC_CfgCbkTable[tmpGroup].END_GROUP_DIAG != NULL)
    {
      DIAGC_CfgCbkTable[tmpGroup].END_GROUP_DIAG(tmpGroup);
    }
    else{}
#endif /* DIAGC_ENABLE_GROUP_CBK = TRUE */
  
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
DRVD_RStatus_t DIAGC_SetNextGroup(DIAGC_Group_t group)
{
  DRVD_RStatus_t valueReturn;

  if(DIAGC_GroupEnded == TRUE)
  {
    DIAGC_CurrentGroup = group;
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_BUSY;
  }
  return valueReturn;
}

CTRL_FaultState_t DIAGC_DiagFsmEvolve(CTRL_Fault_t newFault, CTRL_State_t cmdState,CTRL_FaultState_t currentState)
{
  Diagc_DiagEvent_t DiagEvent;
  
  /* Calcolo il nuovo evento di diagnosi */
  DiagEvent = Diagc_NewEvent(cmdState, newFault);
  
  /* Gestione macchina a stati */
  return DIAGC_StateMachine[DiagEvent][currentState];
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

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
static Diagc_DiagEvent_t Diagc_NewEvent(CTRL_State_t cmdState, CTRL_Fault_t newFault)
{
  Diagc_DiagEvent_t event;

  if (newFault == CTRL_NOT_TESTED)
  {
    event = EV_WAIT;
  }
  else
  {
    if(cmdState == S_ON)
    {
      if (newFault == CTRL_NO_FAULT)
      {
        event = EV_NO_FAULT_CMD_ON;
      }
      else
      {
        event = EV_FAULT_CMD_ON;
      }
    }
    else if (cmdState == S_OFF)
    {
      if(newFault == CTRL_NO_FAULT)
      {
        event = EV_NO_FAULT_CMD_OFF;
      }
      else
      {
        event = EV_FAULT_CMD_OFF;
      }
    }
    else if (cmdState == S_TOGGLE)
    {
      if(newFault == CTRL_NO_FAULT)
      {
        event = EV_NO_FAULT_CMD_ALL;
      }
      else
      {
        event = EV_FAULT_CMD_ALL;
      }
    }
    else
    {
      /* Event unknown */
      event = EV_WAIT;
    }
  }
  return event;
}


#endif /* end __DIAGC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

