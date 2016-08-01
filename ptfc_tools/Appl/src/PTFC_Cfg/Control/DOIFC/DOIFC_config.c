/********************************************************************************/
/* @F_PROJECT:          TESLA X                                                 */
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
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 21/giu/2013     0.1  Matteo MASTRODONATO
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DOIFC.h"

/* Module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L -D E F I N E ______________________________________________*/
#define DOIFC_SHARED_FBK_AVG_COUNT     8u
#define DOIFC_SHARED_FBK_AVG_SHIFT     3u

/*______ G L O B A L - D A T A _______________________________________________*/

const DOIFC_CfgTable_t DOIFC_CfgTable[DOIFC_HDL_MAX] = {

/* Handle                         OUT_CHAN               ACTIVE_LEVEL  FBK_CHAN             MANAGE_DIAG       FBK_GAIN_CHAN  FBK_GAIN_ACT_LEV   SHORT_CIRCUIT_THRES   OPEN_CIRCUIT_THRES   OC_OR_STB_DETECTION  DRIVER_TYPE   REC_RETRY   REC_WAIT_CYCLES  */
/* DOIFC_CmdHeatDrv           */ {DIOD_CmdHeatDrv,       L_HIGH,       ADCC_HeatDrvFbk,         FALSE,          DIOD_HDL_MAX,      L_LOW,             500U, /* 20A */     20U, /*    1A */         FALSE,         HSD,         3u,          100u       },
/* DOIFC_CmdHeatPass          */ {DIOD_CmdHeatPass,      L_HIGH,       ADCC_HeatPassFbk,        FALSE,          DIOD_HDL_MAX,      L_LOW,             500U, /* 20A */     20U, /*    1A */         FALSE,         HSD,         3u,          100u       },
/* DOIFC_CmdHeatSteer         */ {DIOD_CmdHeatSteer,     L_HIGH,       ADCC_HeatSteerFbk,       FALSE,          DIOD_HDL_MAX,      L_LOW,             500U, /* 20A  */    20U, /*    1A */         FALSE,         HSD,         3u,          100u       },
};

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

void DOIFC_UserCfg(void)
{
}

uint16_t DOIFC_GetFbk(DOIFC_Handle_t hdl)
{
  return 0u;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __DOIFC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

