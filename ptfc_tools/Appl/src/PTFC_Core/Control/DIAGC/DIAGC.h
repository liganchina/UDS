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

#ifndef DIAGC_H_
#define DIAGC_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__


/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef bool (*PerformDiag_t)(u08 hdl, CTRL_State_t *CmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState);
typedef void (*DecodeDiag_t) (u08 hdl, CTRL_FaultState_t faultState);

typedef struct
{
  u08              DIAG_OBJ_HDL;
  PerformDiag_t    PERFORM_DIAG_FUNC;
  DecodeDiag_t     DECODE_DIAG_FUNC;
  DIAGC_Group_t    DIAG_GROUP;
} DIAGC_CfgTable_t;


typedef struct
{
  DIAGC_Callback_t START_GROUP_DIAG;
  DIAGC_Callback_t END_GROUP_DIAG;
} DIAGC_CfgCbkTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const DIAGC_CfgTable_t    DIAGC_CfgTable[DIAGC_HDL_MAX];

#if (DIAGC_ENABLE_GROUP_CBK == TRUE)
  extern const DIAGC_CfgCbkTable_t DIAGC_CfgCbkTable[DIAGC_GROUP_MAX];
#endif /* DIAGC_ENABLE_GROUP_CBK == TRUE */

#endif /* end __DIAGC_IS_PRESENT__ */

#endif /* DIAGC_H_ */
