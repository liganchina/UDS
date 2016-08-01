/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              Ddmp.h                                                  */
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

#ifndef DDMP_H
#define DDMP_H


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __DDMP_IS_PRESENT__

#include "DDMP_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/



/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum Ddmp_write_e
{
  DDMP_WRITE_ST_START               = 0x00,  /*Scrittura non iniziata */
  DDMP_WRITE_ST_FAILED              = 0x01,  /*Scrittura fallita a causa di parametri errati */
  DDMP_WRITE_ST_DENIED              = 0x02,  /*Scrittura fallita in quanto non c'è nessuna cella sostituibile */
  DDMP_WRITE_ST_CELL_UPDATE         = 0x04,  /*E' stata aggiornata una cella con l'errore già presente */
  DDMP_WRITE_ST_CELL_READY          = 0x08,  /*L'errore era già presente con lo stesso fault symptom */
  DDMP_WRITE_ST_IN_CLEAN_CELL       = 0x10,  /*E' stata trovata una cella libera */
  DDMP_WRITE_ST_SECURITY_CODE       = 0x20,  /*Scrittura dei componenti di sicurezza e/o con priorità maggiore (indice priorità minore) */
  DDMP_WRITE_ST_SUBSTITUTE_OLD_CODE = 0x40,  /*Sostituzione Vecchio Dtc secondo il criterio ECUTimeStamps */
  DDMP_WRITE_ST_OK                  = 0x7C,  /*Scrittura completata correttamente */
  DDMP_WRITE_ST_COMPLETED           = 0x7F   /*Scrittura completata */
} Ddmp_write_t;

/* Memorizzazione dei comandi ricevuti per tutti i DTC.
   Utilizzo questa struttura per capire quando devo decrementare
   i contatori di errore.
   L'errore sarà decrementato quando tutti i bit del codice
   relativo a quel DTC saranno a zero.                                 */

typedef struct Ddmp_Operation_s
{
  /* ------------------------------------------------------------- */
  /* Operazioni eseguite sui DTC nel ciclo precedente.
     Queste informazioni sono utilizzate per gestire il decremento
     degli event counter.                                          */
  /* ------------------------------------------------------------- */
  bool UpdateDTC : 1;  /*Aggiornamento di un DTC gia' presente*/
  bool StoreDTC  : 1;  /*Memorizzazione di un nuovo DTC*/
  bool ClearDTC  : 1;  /*Cancellazione di un DTC*/
}Ddmp_Operation_t;




typedef enum Ddmp_StatusInformation_e
{
  DDMP_SS_FAIL_LAMP_OFF              = 0x0FU,  /*DTC Storage Stage in presenza guasto*/
  DDMP_SS_FAIL_INTERMITTENT          = 0x0EU,  /*DTC verificatosi almeno una volta nel Monitoring Cycle corrente ma attualmente NON presente*/
  DDMP_SS_FAIL_PENDING               = 0x0CU,  /*DTC non verificatosi nel Monitoring Cycle corrente*/
  DDMP_SS_FAIL_CONFIRMED             = 0x08U,  /*DTC in memoria ma assente da almeno 2 Monitoring Cycle*/
  DDMP_SS_TEST_NOT_COMPLETED         = 0x40U,   /*DTC il cui test diagnostico non è stato completato nel corrente Monitoring Cycle*/
} Ddmp_StatusInformation_t;



/*Codici di ritorno delle funzioni di accesso ai DTC*/

/*SCRITTURA NUOVI DTC*/

typedef enum DDMP_Fault_Manager_e
{
  FAULT_NOT_MANAGED,
  FAULT_MANAGED
} DDMP_Fault_Manager_t;

#if (DDMP_DTC_TIME_PRI_EN == TRUE)
typedef enum DDMP_SetOlderDtc_e
{
  NEWEST,
  OLDEST
} DDMP_SetOlderDtc_t;
#endif

typedef enum DDMP_SetLessPriorityID_e
{
  HIGHER_PRIORITY,
  LOWER_PRIORITY
} DDMP_SetLessPriorityID_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/


void DDMP_UserUpdateSnapshot(Ddmp_Block_t * DtcBlockPntr, u08 EventNum);

DDMP_Read_Result_t DDMP_UserReadDtcSnapshotRecord(Ddmp_Block_t *DtcPntr,
                                                         u08   FaultSym,
                                                         DDMP_Snapshot_Event_Num_t SnapNum,
                                                         u08   *BufferPntr,
                                                         u08   *AddLen);

DDMP_Read_Result_t DDMP_UserReadAllDtcByMask     (u08             *DiagBufPtr,
                                                  DDMP_Sub_Func_t SubFunc,
                                                  u08             *Mask,
                                                  u08             *NumOfDtc );

#if(DDMP_DTC_TIME_PRI_EN == TRUE)
DDMP_SetOlderDtc_t DDMP_UserSetOlderDtc(u08 index, u32 *TimeMin, u16 *TimeFromKeyOnMin);
#endif

void DDMP_UserGetEnvCond(DDMP_Env_Cond_Num_t EnvCondNum, u08 *buffer, u08 Sympt);

#endif /* end __DDMP_IS_PRESENT__ */

#endif /* DDMP_H */

/*______ E N D _____ (ddmp.h) ________________________________________________*/


