/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DOVFC                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     21/giu/2013                                                 */
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

#ifndef DOVFC_H_
#define DOVFC_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__

#include "DOVFC_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef u08 (*GetFbkIn_t)(u08 channel);   /* Get feedback Value (HIGH/LOW) */

/* Struttura di configurazione statica (tabella in DOVFC in DOVFC_config.c */
typedef struct
{
  DIOD_Channel_t    OUT_CHAN;
  DRVD_Level_t      CMD_ACT_LEV;
  GetFbkIn_t        FBK_GET_OP;
  u08               FBK_CHAN;
  DRVD_Level_t      FBK_ACT_LEV;
  CTRL_DriverType_t DRIVER_TYPE;
  u08               DIAG_DEBOUNCE;
}DOVFC_CfgTable_t;

/* Dati privati di DOVFC */
typedef struct
{
  CTRL_Fault_t         lastFault;       /* Ultimo fault visto (interno) */
  CTRL_State_t         diagDataState;   /* Stato del comando durante la diagnosi */
  CTRL_Fault_t         diagData;        /* Risultato della diagnosi */
  CTRL_State_t         outState;        /* Stato attuale del comando */
  CTRL_FaultState_t    faultState;      /* Stato della macchina a stati di diagnosi (DIAGP) */
  CTRL_State_t         freeze;          /* Blocca eventuali modifiche allo stato uscita.
                                          * Attivato solo durante la diagnosi in out ON per discriminare
                                          * lo short to battery dall'open load */
  u08                  diagDebounce;    /* Number of consecutive diagnosis result before change the diag status */
  CTRL_EnSts_t         functionState;   /* Function State, enabled/disabled by proxi */
}DOVFC_PrivateData_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const DOVFC_CfgTable_t DOVFC_CfgTable[DOVFC_HDL_MAX];
extern DOVFC_PrivateData_t  DOVFC_PrivateData[DOVFC_HDL_MAX];

#endif /* end __DOVFC_IS_PRESENT__ */

#endif /* DOVFC_H_ */
