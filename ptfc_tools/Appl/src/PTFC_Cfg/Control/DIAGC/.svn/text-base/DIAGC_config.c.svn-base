/********************************************************************************/
/* @F_PROJECT:          TELSA X                                                 */
/* F_NAME:              DIAGC_config                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/giu/2013                                             */
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
| ----------  ---  ------  ----------------------------------------------------A
| 24/giu/2013      0.1     Matteo MASTRODONATO
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIAGC_config.h"
#include "DIAGC.h"

/* Module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/



const DIAGC_CfgTable_t DIAGC_CfgTable[DIAGC_HDL_MAX] = {

/* DIAGC Handle               DIAG_OBJ_HDL           PERFORM_DIAG_FUNC     DECODE_DIAG_FUNC    DIAG_GROUP    */
/* DIAGC_CmdTiltSlideCom */ { DOVFC_CmdTiltSlideCom, DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_00}, /* 3 TICK */
/* DIAGC_CmdSlideFd      */ { DOVFC_CmdSlideFd,      DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_00},
/* DIAGC_CmdTiltUp       */ { DOVFC_CmdTiltUp,       DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_00},

/* DIAGC_CmdSpareMotCom  */ { DOVFC_CmdSpareMotCom,  DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_01}, /* 3 TICK */
/* DIAGC_CmdSpareMotDw   */ { DOVFC_CmdSpareMotDw,   DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_01},
/* DIAGC_CmdLiftBackrCom */ { DOVFC_CmdLiftBackrCom, DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_01},

/* DIAGC_CmdLiftUp       */ { DOVFC_CmdLiftUp,       DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_02}, /* 3 TICK */
/* DIAGC_CmdBackrFd      */ { DOVFC_CmdBackrFd,      DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_02},
/* DIAGC_CmdRelProtEN    */ { DOVFC_CmdRelProtEN,    DOVFC_PerformDiag,    DOVFC_DecodeDiag,   DIAGC_GROUP_02},

/* DIAGC_HeatLed   ,     */ { PWMC_HeatLed,          PWMC_PerformDiag,     PWMC_DecodeDiag,    DIAGC_GROUP_03}, /* 1 TICK */
};


#if (DIAGC_ENABLE_GROUP_CBK == TRUE)
const DIAGC_CfgCbkTable_t DIAGC_CfgCbkTable[DIAGC_GROUP_MAX] = {

/*                      START_GROUP_DIAG   END_GROUP_DIAG     */
/*  DIAGC_GROUP_00 */ { NULL,              NULL },
/*  DIAGC_GROUP_01 */ { NULL,              NULL },
/*  DIAGC_GROUP_02 */ { NULL,              NULL },
/*  DIAGC_GROUP_03 */ { NULL,              NULL },
};
#endif /* DIAGC_ENABLE_GROUP_CBK == TRUE */

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* __DIAGC_IS_PRESENT__ */ 

/*______ E N D _____ (Template.c) _________________________________________*/

