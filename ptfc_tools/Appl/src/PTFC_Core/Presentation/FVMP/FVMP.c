/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              FVMP                                                    */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     02/lug/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
 |-----------------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------------
 | MM           Matteo MASTRODONATO       Bitron S.p.A.
 |-----------------------------------------------------------------------------
 |               R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------------
 | Date        Ver  Author  Description
 | ----------  ---  ------  ----------------------------------------------------
 | 02/lug/2013 0.1  MM
 */

#define FVMP_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "FVMP.h"

/* Module inhibition filter */
#ifdef __FVMP_IS_PRESENT__

/*______ L O C A L - M A C R O S _____________________________________________*/

/* Tick number to scan all channels configured */
#define FVMP_SCAN_TICK_NMB      ((uint8_t)(FVMP_CHN_SCAN_TIME_US/FVMP_TICK_TIME))
#define FVMP_TICK_MS            (FVMP_CHN_SCAN_TIME_US/1000U)

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct
{
  u16           validCounter;
  u16           invalidCounter;
  bool          validated      :1;
  bool          invalidated    :1;
  PRES_Fault_t  validatedFault;
  PRES_Fault_t  oldFault;
  PRES_State_t  validatedinState;
} FVMP_PrivateData_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

static FVMP_PrivateData_t FVMP_PrivateData[FVMP_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/* Variables for spreading strategy */
static FVMP_Handle_t Fvmp_CurrentHdl;
static uint8_t       Fvmp_ScanTickNmb;
static uint8_t       Fvmp_SubChanForTick[FVMP_SCAN_TICK_NMB];

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static bool Fvmp_isDestructive(FVMP_Handle_t hdl, PRES_Fault_t newFault);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

void FVMP_PseudoInit(void)
{
  FVMP_PSEUDO_RUN();
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
/*    Inizializzazione al PWR-ON                                              */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void FVMP_Init(void)
{
  FVMP_Handle_t hdl;
  uint8_t       chanToScan;

  for (hdl = (FVMP_Handle_t) 0; hdl < FVMP_HDL_MAX; hdl++)
  {
    FVMP_PrivateData[hdl].validCounter     = 0U;
    FVMP_PrivateData[hdl].invalidCounter   = FVMP_CfgTable[hdl].INVALID_TIME_MS;
    FVMP_PrivateData[hdl].validated        = FALSE;
    FVMP_PrivateData[hdl].invalidated      = FALSE;
    FVMP_PrivateData[hdl].validatedFault   = PRES_NOT_TESTED;
    FVMP_PrivateData[hdl].oldFault         = PRES_NOT_TESTED;
    FVMP_PrivateData[hdl].validatedinState = S_OFF;
  }

  /* Init of the spreading variables */
  chanToScan      = FVMP_HDL_MAX;
  Fvmp_CurrentHdl = (FVMP_Handle_t) 0;

  hdl = (FVMP_Handle_t) 0;
  for(Fvmp_ScanTickNmb = FVMP_SCAN_TICK_NMB; Fvmp_ScanTickNmb > 0U; Fvmp_ScanTickNmb--)
  {
    Fvmp_SubChanForTick[hdl] = GBLS_SUB_CHAN_NMB(chanToScan, Fvmp_ScanTickNmb);
    chanToScan -= Fvmp_SubChanForTick[hdl];
    hdl++;
  }
  Fvmp_ScanTickNmb = 0u;

  /* Post init hook macro */
  FVMP_POST_INIT();

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
/*   Dopo un reset del FVMP, verrà chiamata nuovamente la callback di fault   */
/*    sia in caso di conferma sia in caso di svalidazione del fault           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void FVMP_Reset(void)
{
  FVMP_Handle_t hdl;

  for (hdl = (FVMP_Handle_t) 0; hdl < FVMP_HDL_MAX; hdl++)
  {
    FVMP_PrivateData[hdl].validCounter     = 0U;
    FVMP_PrivateData[hdl].invalidCounter   = FVMP_CfgTable[hdl].INVALID_TIME_MS;
    FVMP_PrivateData[hdl].validated        = FALSE;
    FVMP_PrivateData[hdl].invalidated      = FALSE;
    FVMP_PrivateData[hdl].validatedFault   = PRES_NOT_TESTED;
    FVMP_PrivateData[hdl].oldFault         = PRES_NOT_TESTED;
    FVMP_PrivateData[hdl].validatedinState = S_OFF;
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
/*   Dopo un reset del FVMP, verrà chiamata nuovamente la callback di fault   */
/*    sia in caso di conferma sia in caso di svalidazione del fault           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DRVD_RStatus_t FVMP_ResetLine(FVMP_Handle_t hdl)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < FVMP_HDL_MAX)
  {
    FVMP_PrivateData[hdl].validCounter     = 0U;
    FVMP_PrivateData[hdl].invalidCounter   = FVMP_CfgTable[hdl].INVALID_TIME_MS;
    FVMP_PrivateData[hdl].validated        = FALSE;
    FVMP_PrivateData[hdl].invalidated      = FALSE;
    FVMP_PrivateData[hdl].validatedFault   = PRES_NOT_TESTED;
    FVMP_PrivateData[hdl].oldFault         = PRES_NOT_TESTED;

    valueReturn = MS_OK;
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
void FVMP_Mgm(void)
{
  uint8_t         SubChan;
  PRES_Fault_t    newFault;
  PRES_State_t    newState;
  FVMP_CfgTable_t PtrCfgTable;
  uint8_t         subChanCheck;
  
  subChanCheck = Fvmp_SubChanForTick[Fvmp_ScanTickNmb];

    /* Scan a subchannels number by the spreading strategy */
  for (SubChan = 0U; ((SubChan < subChanCheck) &&
                      (Fvmp_CurrentHdl < FVMP_HDL_MAX)); SubChan++)
  {
    PtrCfgTable = FVMP_CfgTable[Fvmp_CurrentHdl];

    if (PtrCfgTable.STATE_FUN_PTR != NULL)
    {
      newState = PtrCfgTable.STATE_FUN_PTR(PtrCfgTable.DIAG_CHAN);
    }
    else
    {
      newState = S_OFF; /* Not used, set to the same value of init FVMP_PrivateData[Fvmp_CurrentHdl].validatedinState */
    }

    newFault = PtrCfgTable.DIAG_FUN_PTR(PtrCfgTable.DIAG_CHAN);

    /* Caso:
     *       -si valida un fault in uno stato (es: stato ON, ritorno FVMP = Short to Ground).
     *       -l'uscita commuta nell'altro stato (es: stato OFF, ritorno FVMP = Short to Ground).
     *       -Si valida un fault anche in questo stato (es: stato OFF, ritorno FVMP = Short to bat).
     *       -Viene rimosso il fault. La diagnosi di basso livello ritorna un NOT TESTED
     *        in quanto ricorda che aveva visto fault in entrambi gli stati. NOT TESTED normalmente
     *        congela l'evoluzione della FVMP.
     *
     * Scelta progettuale:
     *
     *        -Se riceviamo un NOT TESTED e l'uscita è nello stesso stato in cui ha validato il fault
     *         dichiariamo NO FAULT.
     *        -NB:Se si torna nell'altro stato e il fault è ancora presente si validerà
     *         nuovamente il fault.
     *
     * */
    if ((newFault == PRES_NOT_TESTED)  &&
        (FVMP_PrivateData[Fvmp_CurrentHdl].validated == TRUE)  &&
        (newState == FVMP_PrivateData[Fvmp_CurrentHdl].validatedinState))
    {
      /* Implementazione commento sovrastante */
      newFault = PRES_NO_FAULT;
    }
    else
    {
      /* NOP */
    }

    if (newFault == PRES_NO_FAULT)
    {
      /* Frequently case */
      if (FVMP_PrivateData[Fvmp_CurrentHdl].invalidated == TRUE)
      {
        FVMP_PrivateData[Fvmp_CurrentHdl].validCounter = 0U;
        FVMP_PrivateData[Fvmp_CurrentHdl].validatedFault = PRES_NO_FAULT;
      }
      else
      {
        /* Svalidazione */
        if (FVMP_PrivateData[Fvmp_CurrentHdl].invalidCounter < 0xFFFFu) /* 0xFFFF = Fault non svalidabile */
        {
          if (FVMP_PrivateData[Fvmp_CurrentHdl].invalidCounter > 0U)
          {
            FVMP_PrivateData[Fvmp_CurrentHdl].invalidCounter -= FVMP_TICK_MS;
          }
          else
          {
            FVMP_PrivateData[Fvmp_CurrentHdl].validated   = FALSE;
            FVMP_PrivateData[Fvmp_CurrentHdl].invalidated = TRUE;
            FVMP_PrivateData[Fvmp_CurrentHdl].validatedFault = PRES_NO_FAULT;
            FVMP_PrivateData[Fvmp_CurrentHdl].validCounter = 0U;

            /* Call Callback */
            if (PtrCfgTable.FAULT_CALLBACK != NULL)
            {
              PtrCfgTable.FAULT_CALLBACK(Fvmp_CurrentHdl, PRES_NO_FAULT, FALSE);
            }
          }
        }
        else
        {
          /* DTC non svalidabile */
        }
      }
    }
    else if (newFault == PRES_NOT_TESTED)
    {
      /* NOP */
    }
    else
    {
      /* Fault Present */
      if (newFault != FVMP_PrivateData[Fvmp_CurrentHdl].oldFault)
      {
        FVMP_PrivateData[Fvmp_CurrentHdl].oldFault = newFault;
        FVMP_PrivateData[Fvmp_CurrentHdl].validated = FALSE;
        FVMP_PrivateData[Fvmp_CurrentHdl].validCounter = 0U;
      }
      else
      {
        /* NOP */
      }

      if (FVMP_PrivateData[Fvmp_CurrentHdl].validCounter < PtrCfgTable.VALID_TIME_MS)
      {
        /* Nop */
        FVMP_PrivateData[Fvmp_CurrentHdl].validCounter += FVMP_TICK_MS;
      }
      else
      {
        if (FVMP_PrivateData[Fvmp_CurrentHdl].validated == FALSE)
        {
          /* Fault Validated */
          FVMP_PrivateData[Fvmp_CurrentHdl].validated   = TRUE;
          FVMP_PrivateData[Fvmp_CurrentHdl].invalidated = FALSE;
          FVMP_PrivateData[Fvmp_CurrentHdl].validatedFault = newFault;
          FVMP_PrivateData[Fvmp_CurrentHdl].invalidCounter = PtrCfgTable.INVALID_TIME_MS;
          FVMP_PrivateData[Fvmp_CurrentHdl].validatedinState = newState;

          /* Call Callback */
          if (PtrCfgTable.FAULT_CALLBACK != NULL)
          {
            PtrCfgTable.FAULT_CALLBACK(Fvmp_CurrentHdl, newFault, Fvmp_isDestructive(Fvmp_CurrentHdl, newFault));
          }
        }
        else
        {
          /* NOP */
        }
      }

    }
    /* Update current channel */
    Fvmp_CurrentHdl++;
  }

  /* Reinit current channel */
  if (Fvmp_CurrentHdl >= FVMP_HDL_MAX)
  {
    Fvmp_CurrentHdl = ((FVMP_Handle_t)0u);
  }

  /* Update spreading variables */
  if (Fvmp_ScanTickNmb < (FVMP_SCAN_TICK_NMB - 1U))
  {
    Fvmp_ScanTickNmb++;
  }
  else
  {
    Fvmp_ScanTickNmb = 0u;
  }
}

DRVD_RStatus_t FVMP_GetDiag(FVMP_Handle_t hdl, PRES_Fault_t* fault, bool* destructive)
{
  DRVD_RStatus_t valueReturn;

  if (hdl < FVMP_HDL_MAX)
  {
    *fault        = FVMP_PrivateData[hdl].validatedFault;
    *destructive  = Fvmp_isDestructive(hdl, *fault);
    valueReturn   = MS_OK;
  }
  else
  {
    *fault        = PRES_NOT_TESTED;
    *destructive  = FALSE;
    valueReturn   = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

static bool Fvmp_isDestructive(FVMP_Handle_t hdl, PRES_Fault_t newFault)
{
  bool destructive;

  if ((newFault == PRES_SHORT_TO_GND) ||
      (newFault == PRES_OC_OR_STG))
  {
    if (STG_DESTR & FVMP_CfgTable[hdl].FAULT_IMPACT)
    {
      destructive = TRUE;
    }
    else
    {
      destructive = FALSE;
    }
  }
  else if ((newFault == PRES_SHORT_TO_BAT) ||
           (newFault == PRES_OC_OR_STB))
  {
    if (STB_DESTR & FVMP_CfgTable[hdl].FAULT_IMPACT)
    {
      destructive = TRUE;
    }
    else
    {
      destructive = FALSE;
    }
  }
  else if (newFault == PRES_OPEN_LOAD)
  {
    if (OL_DESTR & FVMP_CfgTable[hdl].FAULT_IMPACT)
    {
      destructive = TRUE;
    }
    else
    {
      destructive = FALSE;
    }
  }
  else if (newFault == PRES_OVER_VOLTAGE)
  {
    if (OV_DESTR & FVMP_CfgTable[hdl].FAULT_IMPACT)
    {
      destructive = TRUE;
    }
    else
    {
      destructive = FALSE;
    }
  }
  else if (newFault == PRES_UNDER_VOLTAGE)
  {
    if (UV_DESTR & FVMP_CfgTable[hdl].FAULT_IMPACT)
    {
      destructive = TRUE;
    }
    else
    {
      destructive = FALSE;
    }
  }
  else
  {
    destructive = FALSE; /* = NOT_TESTED || NO_FAULT || ... */
  }

  return destructive;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __FVMP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

