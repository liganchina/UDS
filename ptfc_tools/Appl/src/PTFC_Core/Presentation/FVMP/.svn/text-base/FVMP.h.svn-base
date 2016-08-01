/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              FVMP                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     02/lug/2013                                                 */
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
| 02/lug/2013     0.1  Matteo MASTRODONATO
*/

#ifndef FVMP_H_
#define FVMP_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __FVMP_IS_PRESENT__

#include "FVMP_cbk.h"
#include "FVMP_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef PRES_Fault_t (*GetDiag_t)  (u08 channel);  /* Get Diagnosis Fault     */
typedef PRES_State_t (*GetState_t) (u08 channel);  /* Get Command State       */

typedef struct {
  u08                  DIAG_CHAN;
  GetDiag_t            DIAG_FUN_PTR;
  GetState_t           STATE_FUN_PTR;
  u16                  VALID_TIME_MS;
  u16                  INVALID_TIME_MS;
  u08                  FAULT_IMPACT;
  FVMP_FaultValidCbk_t FAULT_CALLBACK;
} FVMP_CfgTable_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

#define  DESTR_OFF   0x00u
#define  STB_DESTR   0x01u
#define  STG_DESTR   0x02u
#define  OL_DESTR    0x04u
#define  OV_DESTR    0x08u
#define  UV_DESTR    0x10u

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const FVMP_CfgTable_t FVMP_CfgTable[FVMP_HDL_MAX];

#endif /* end __FVMP_IS_PRESENT__ */

#endif /* FVMP_H_ */
