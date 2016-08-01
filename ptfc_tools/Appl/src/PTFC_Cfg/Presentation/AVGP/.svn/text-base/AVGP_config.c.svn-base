/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                                */
/* F_NAME:              AVGP_config                                             */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     07/giu/2013                                             */
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
| 07/giu/2013     0.1  Matteo MASTRODONATO
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "AVGP.h"

/* Module inhibition filter */
#ifdef __AVGP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/


const AVGP_CfgTable_t AVGP_CfgTable[] = {
/* HANDLE              ADCD_Channel     Scaling Gain       OVER_V_THRES_H       OVER_V_THRES_L      UNDER_V_THRES_H     UNDER_V_THRES_L      HW_CAL_OFFSET
 *                                      (res: 1/1024 LSB)  (res: 4883mV/LSB)    (res: 4883mV/LSB)   (res: 4883mV/LSB)   (res: 4883mV/LSB)    (res: 4883mV/LSB)
 * Valori a 25°C su connettore                                      16.5V                16.2V                9.8V                9.5V               0.6V    */
/* AVGP_Vbat  */       {ADCD_Vbat,      4860U,             3420U,/* 16.7V */    3359U,/* 16.4V */   2028U, /* 9.9V */    1966U, /* 9.6V */     154U /* 0.75V */ }
};

/* I valori delle soglie e dell'offset di calibrazione si riferiscono alla tensione sul CONNETTORE */

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


#endif /* end __AVGP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

