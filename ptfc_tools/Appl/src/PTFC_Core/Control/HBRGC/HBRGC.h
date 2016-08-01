/**
 * @file HBRGC.h
 * @brief Driver for Infineon BTM7752 h-bridge chip
 * @author Daniele Cloralio
 * @date 08 apr 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
|              Daniele CLORALIO          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 08/apr/2015     0.1  Daniele CLORALIO
 */

#ifndef HBRGC_H_
#define HBRGC_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __HBRGC_IS_PRESENT__

#include "HBRGC_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum HBRGC_DiagState_e
{
  SHORT_CIRCUIT_DIAG = 0,
  SHORT_CIRCUIT_RECOVERY,
  RECOVERY_WAIT,
  SHORT_TO_BATT_DIAG,
  FAIL_CONFIRMED,
} HBRGC_DiagState_t;

/* Struttura di configurazione statica (tabella in HBRGC in HBRGC_config.c */
typedef struct HBRGC_CfgTable_s
{
  DIOD_Channel_t    INPUT_CHAN1;
  DIOD_Channel_t    INPUT_CHAN2;
  DIOD_Channel_t    INHIBIT_CHAN;
  DRVD_Level_t      ACTIVE_LEVEL;
  ADCC_InputChn_t   FBK_CHAN;
  u16               SHORT_CIRCUIT_THRES;
  u16               OPEN_CIRCUIT_THRES;
//  u16               ERROR_MODE_THRES; // not used
  u08               REC_RETRY;       /* number of retry in case of destructive short circuit */
  u08               REC_WAIT_CYCLES; /* number off cycle to stay in wait state for recovery */
  u08               DIAG_DEBOUNCE;   /* number of consecutive diagnosis result before change the diag status */
}HBRGC_CfgTable_t;

/* Dati privati di HBRGC */
typedef struct HBRGC_PrivateData_s
{
  CTRL_Fault_t         lastFault;       /* Ultimo fault visto (interno) */
  CTRL_State_t         diagDataState;   /* Stato del comando durante la diagnosi */
  CTRL_Fault_t         diagData;        /* Risultato della diagnosi */
  CTRL_State_t         outStateHS1;      /* Stato attuale del comando */
  CTRL_State_t         outStateHS2;      /* Stato attuale del comando */
  CTRL_State_t         oldOutStateHS1;     /* Stato precedente del comando */
  CTRL_State_t         oldOutStateHS2;     /* Stato precedente del comando */
  HBRGC_DiagState_t    diagState;       /* Macchina a stati interna di diagnosi */
  CTRL_State_t         freeze;          /* Blocca eventuali modifiche allo stato uscita */
  CTRL_FaultState_t    faultState;      /* Stato della macchina a stati di diagnosi (DIAGP) */
  uint8_t              diagRetry;
  uint8_t              diagWaitCycle;
  uint8_t              diagDebounce;    /* Debounce per spunto motore e frenata */
}HBRGC_PrivateData_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const HBRGC_CfgTable_t HBRGC_CfgTable[HBRGC_HDL_MAX];

#endif /* end __HBRGC_IS_PRESENT__ */

#endif /* HBRGC_H_ */
