/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              ddmp_config.h                                           */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:                                                               */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     xxxxx                                                   */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
|
*/

#ifndef DDMP_CONFIG_H
#define DDMP_CONFIG_H


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/


#define DDMP_ENABLE_DTC_EVENT     FVMP_Reset();           \
                                  NETP_ClearDtcEvent();

#define DDMP_CLEAR_DTC_EVENT      FVMP_Reset();           \
                                  NETP_ClearDtcEvent();   \
                                  MOTP_ClearFaults();     \
                                  DDMP_UserClearDtcEvent();

#define DDMP_KEY_ON_EVENT         FVMP_Reset();           \
                                  NETP_ClearDtcEvent();   \
                                  DDMP_UserKeyOnEvent();

#define DDMP_KEY_OFF_EVENT        DDMP_UserKeyOffEvent();



/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Struttura di definizione del codice,livello di priorita', gestione in funzione*/
/*dello stato chiave dei DTC e sicurezza dei DTC*/
typedef enum DDMP_SEVERITY_e
{
  DDMP_NO_INFO      = 0x00,  /*DTC Severity: No info available*/
  DDMP_MAINT_ONLY   = 0x20,  /*DTC Severity: Maintenance Only*/
  DDMP_CK_NEXT_H    = 0x40,  /*DTC Severity: Check at next halt*/
  DDMP_CK_IMM       = 0x80,  /*DTC Severity: Check immediately*/
} DDMP_SEVERITY_t;

typedef enum
{
  DDMP_SPN_FAULT     = 0x00,
  DDMP_SPN_WARN      = 0x01
} DDMP_SPN_TYPE_t;

typedef struct Ddmp_DtcInformation_s
{
  u16               Code                : 16;     /*Codice*/
  u08               Symptoms[4]             ;     /*Possibili sintomi per lo specifico DTC*/
  DDMP_SEVERITY_t   Severity            :  8;     /*Livello di severità*/
  u08               PriorityLevel       :  8;     /* Livello di priorità*/
  u08               SymptomsNum         :  3;     /*Numero di sintomi per lo specifico DTC*/
  PRES_KeyStatus_t  KeyStatus           :  2;     /*0 = DTC attivo al chiave OFF,1 = DTC attivo al chiave ON*/
  bool              SecurityDTC         :  1;     /* DTC di sicurezza (spec. 09009 Ed.3 pag.33, TRUE per i DTC con severità 0x80)*/
  DDMP_SPN_TYPE_t   SPNType             :  1;     /*SPNType*/
  u08               spare               :  1;     /*spare*/
} Ddmp_DtcInformation_t;


typedef struct Ddmp_Env_Cond_Cfg_s
{
  u16       RDI;
  u08       Length;               //lenght is 0 to refer to Symptom data ( DDMP_SNAPSHOT_SYMPTOM_POSITION)
}Ddmp_Env_Cond_Cfg_t;



 /*Verifica se è neccessario il salvataggio dei dati in EEPROM*/

// TODO SAVE...
// mask of the possible DTC value:
//// ALM_IVECO
//typedef enum
//{
//  /* Il DTC ha sempre dato esito positivo                                     */
//  DDMP_NO_FAIL = 0x00u,
//  /* Nel monitoring cycle corrente è stato confermato almeno una volta il DTC,*/
//  /* non è terminata la memorizzazione dello stesso ma durante questa fase il */
//  /* DTC è scomparso. */
//  DDMP_GHOST_DTC = 0x06u,
//  /* Nel monitoring cycle corrente è stato confermato almeno una volta il DTC,*/
//  /* non è terminata la memorizzazione dello stesso.                          */
//  DDMP_CONFIRMED_DTC_BUT_NO_STORED = 0x07u,
//  /* DTC confermato almeno 1 volta nei 40 cicli chiave o prima del DTCClear.  */
//  DDMP_CONFIRMED_DTC = 0x08u,
//  /* DTC confermato almeno una volta nel monitoring cycle precedente.         */
//  DDMP_CONFIRMED_DTC_IN_THE_PREW_MON_CYCLE = 0x0C;
//  /* DTC confermato nel monitoring cycle corrente, memorizzato ma non presente*/
//  DDMP_TEST_FAIL_THIS_MONITORIN_CYCLE = 0x0Eu,
//  /* DTC confermato nel monitoring cycle corrente, memorizzato e presente     */
//  } Ddmp_StatusInformation_t;



/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

extern Ddmp_DtcInformation_t const Ddmp_DtcInformation[DDMP_ALL_DTC_ID];
extern Ddmp_Env_Cond_Cfg_t const Ddmp_EnvCondInformation[DDMP_SNAPSHOT_RECORD_NUM_DATA];

#endif /* DDMP_CONFIG_H */

/*______ E N D _____ (ddmp_config.h) _________________________________________*/
