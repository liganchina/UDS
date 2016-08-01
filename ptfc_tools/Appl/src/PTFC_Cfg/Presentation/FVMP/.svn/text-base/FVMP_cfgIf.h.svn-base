/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              FVMP_CfgIf                                            */
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

#ifndef FVMP_CFGIF_H_
#define FVMP_CFGIF_H_

#ifdef FVMP_CONFIG_IF_OWNER
  #define FVMP_CONFIG_IF_EXTERN
#else
  #define FVMP_CONFIG_IF_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum FVMP_Handle_e
{
  FVMP_INTERNAL_FAIL   = 0   ,     /* (0)  */
  FVMP_MEM_KEY               ,     /* (1)  */
  FVMP_TILT_SLIDE_KEY        ,     /* (2)  */
  FVMP_LIFT_BACKR_KEY        ,     /* (3)  */
  FVMP_TILT_SLIDE_RL         ,     /* (4)  */
  FVMP_LIFT_BACK_RL          ,     /* (5)  */
  FVMP_PROT_RL               ,     /* (6)  */
  FVMP_SLIDE_HALL_SENSOR     ,     /* (7)  */
  FVMP_TILT_HALL_SENSOR      ,     /* (8)  */
  FVMP_LIFT_HALL_SENSOR      ,     /* (9)  */
  FVMP_BACKREST_HALL_SENSOR  ,     /* (10)  */
  FVMP_DRIVER_SEAT_HEATER    ,     /* (11) */
  FVMP_PSNGR_SEAT_HEATER     ,     /* (12) */
  FVMP_STEERW_HEATER         ,     /* (13) */
  FVMP_NTC_STEERW            ,     /* (14) */
  FVMP_NTC_DRV               ,     /* (15) */
  FVMP_NTC_PSG               ,     /* (16) */
  FVMP_VEHICLE_SPEED_MSG     ,     /* (17) */
  FVMP_NODE_MUTE             ,     /* (18) */
  FVMP_BUS_OFF               ,     /* (19) */
  FVMP_BCM                   ,     /* (20) */
  FVMP_IPC                   ,     /* (21) */
  FVMP_ACM                   ,     /* (22) */
  FVMP_STATUS_BCM1           ,     /* (23) */
  FVMP_STATUS_CCAN3          ,     /* (24) */
  FVMP_OP_MODE_STS_SNA       ,     /* (25) */
  FVMP_SLIDE_LOW_CURRENT     ,     /* (26) */
  FVMP_VBATT_MOTORS          ,     /* (27) */
  FVMP_VBATT_ELE             ,     /* (28) */
  FVMP_MOTOR_OVERCURRENT     ,     /* (29) */
  FVMP_HDL_MAX
}FVMP_Handle_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

FVMP_CONFIG_IF_EXTERN void FVMP_ConfigPseudoInit(void);
FVMP_CONFIG_IF_EXTERN void FVMP_ConfigInit(void);
FVMP_CONFIG_IF_EXTERN void FVMP_NetOnEvent(void);
FVMP_CONFIG_IF_EXTERN void FVMP_NetOffEvent(void);
FVMP_CONFIG_IF_EXTERN bool FVMP_isProtReleOk(void);
FVMP_CONFIG_IF_EXTERN void FVMP_KeyOffOnTrans(void);
FVMP_CONFIG_IF_EXTERN void FVMP_KeyStsChanged(PRES_KeyStatus_t KeyStatus);
FVMP_CONFIG_IF_EXTERN void FVMP_OpModeStsChanged(OperationalModeSts_t OpModeStatus);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* FVMP_CFGIF_H_ */
