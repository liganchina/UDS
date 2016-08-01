/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              DOIFC_cfgIf  Digital Output with current(I) Feedback    */
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
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 21/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DOIFC_H_
#define DOIFC_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__

#include "DOIFC_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/


typedef enum DOIFC_DiagState_e
{
  SHORT_CIRCUIT_DIAG = 0,
  SHORT_CIRCUIT_RECOVERY,
  RECOVERY_WAIT,
  SHORT_TO_BATT_DIAG,
  FAIL_CONFIRMED,
} DOIFC_DiagState_t;


typedef enum Doifc_diagRecStates_e
{
  DOIFC_DIAGREC_INIT,
  DOIFC_DIAGREC_TEST_STG,
  DOIFC_DIAGREC_TEST_STB,
  DOIFC_DIAGREC_TEST_OPEN,
  DOIFC_DIAGREC_WAIT,
  DOIFC_DIAGREC_FAIL //confirmed fail
}Doifc_diagRecStates_t;

/* Struttura di configurazione statica (tabella in DOIFC in DOIFC_config.c */
typedef struct DOIFC_CfgTable_s
{
  DIOD_Channel_t    OUT_CHAN;
  DRVD_Level_t      ACTIVE_LEVEL;
  ADCC_InputChn_t   FBK_CHAN; /* FBK_CHAN = ADCC_CHN_NMB means that the feedback value is directly available using DOIFC_GetFbk() */
//  DIOD_Channel_t    EN_FBK_CHAN;
//  DRVD_Level_t      EN_FBK_ACT_LEV;
  bool_t            MANAGE_DIAG; /* TRUE = the diagnosis is performed in DOIFC_Mgm() and is autoresetted, FALSE = the DOIFC_PerformAndDecodeDiag() function for this handle is called by other module */
  DIOD_Channel_t    FBK_GAIN_CHAN;
  DRVD_Level_t      FBK_GAIN_ACT_LEV;
  u16               SHORT_CIRCUIT_THRES;
  u16               OPEN_CIRCUIT_THRES;
  u08               OC_OR_STB_DETECTION; /* set TRUE if OPEN CIRCUIT and SHORT CIRCUIT to BATTERY should be distinguished or not */
  CTRL_DriverType_t DRIVER_TYPE;
  u08               REC_RETRY;       /* number of retry in case of destructive short circuit */
  u08               REC_WAIT_CYCLES; /* number off cycle to staty in wait state for recovery */
}DOIFC_CfgTable_t;

/* Dati privati di DOIFC */
typedef struct DOIFC_PrivateData_s
{
  CTRL_Fault_t         lastFault;       /* Ultimo fault visto (interno) */
  CTRL_State_t         diagDataState;   /* Stato del comando durante la diagnosi */
  CTRL_Fault_t         diagData;        /* Risultato della diagnosi */
  CTRL_State_t         outState;        /* Stato attuale del comando */
  CTRL_State_t         oldOutState;     /* Stato precedente del comando */
  DOIFC_DiagState_t    diagState;       /* Macchina a stati interna di diagnosi */
  CTRL_State_t         freeze;          /* Blocca eventuali modifiche allo stato uscita.
                                         * Attivato solo durante la diagnosi in out ON per discriminare
                                         * lo short to battery dall'open load */
  CTRL_FaultState_t    faultState;      /* Stato della macchina a stati di diagnosi (DIAGP) */
  uint8_t              diagRetry;
  uint8_t              diagWaitCycle;
  CTRL_EnSts_t         functionState;   /* Function State, enabled/disabled by proxi */
}DOIFC_PrivateData_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const DOIFC_CfgTable_t DOIFC_CfgTable[DOIFC_HDL_MAX];

#endif /* end __DOIFC_IS_PRESENT__ */

#endif /* DOIFC_H_ */
