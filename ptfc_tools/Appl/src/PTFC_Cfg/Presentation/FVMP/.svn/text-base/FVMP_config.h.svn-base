/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              FVMP_config                                            */
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

#ifndef FVMP_CONFIG_H_
#define FVMP_CONFIG_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "VF608_cbk.h"

//#include "APPL_if.h" //DF: for bad configuration, gateway heart beat and FAN diagnostic

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define FVMP_PSEUDO_RUN()        FVMP_ConfigPseudoInit()

#define FVMP_POST_INIT()         FVMP_ConfigInit()

/**
 * Tick time to use for compute the maximum ticks number. This time must be used
 * as reference for call the module management routine with the correct task time.
 */
#define FVMP_TICK_TIME           ((uint16_t)10000u)

/**
 * Time to scan all channel configured. This time must be set in microseconds.
 */
#define FVMP_CHN_SCAN_TIME_US    ((uint16_t)50000u)

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

FVMP_CONFIG_IF_EXTERN void FVMP_FaultEvent    (FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive);
FVMP_CONFIG_IF_EXTERN void FVMP_ReleFaultEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive);
FVMP_CONFIG_IF_EXTERN void FVMP_VbattEvent    (FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive);
FVMP_CONFIG_IF_EXTERN void FVMP_ProtReleFaultEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* FVMP_CONFIG_H_ */
