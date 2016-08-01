/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                         */
/* F_NAME:              DINP                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     10/giu/2013                                                 */
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
| 10/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DINP_H_
#define DINP_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __DINP_IS_PRESENT__

#include "DINP_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef struct
{
  u08             CntTest;             /* Debounce test counter */
  PRES_State_t    RetState;            /* Returned state        */
} DINP_PrivateData_t;


typedef u08 (*GetDigIn_t)(u08 channel);   /* Get Input Value (HIGH/LOW) */

/* Typedef struttura da allocare in flash contenente i dati di configurazione statica */
typedef struct
{
  u08              INP_CHAN;        /* Lower Layer Input Channel           */
  GetDigIn_t       GET_VALUE_PTR;   /* Get Input Value (HIGH/LOW)          */
  u08              N_TEST;          /* Debounce test number                */
  DRVD_Level_t     ACTIVE_LEVEL;    /* Active level                        */
  PRES_State_t     INITIAL_STATE;   /* Initial state of debounce filter    */
  DINP_Callback_t  STATE_CHANGED;   /* Input state changes event           */
} DINP_CfgTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const DINP_CfgTable_t DINP_CfgTable[DINP_HDL_MAX];

#endif /* end __DINP_IS_PRESENT__ */

#endif /* DINP_H_ */
