/********************************************************************************/
/* @F_PROJECT:          MSM TESLA                                               */
/* F_NAME:              MOTP_cfgIf                                              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FF3                                  */
/* F_CREATION_DATE:     21/oct/2014                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|------------------------------------------------------------------------------
|                A U T H O R   I D E N T I T Y
|------------------------------------------------------------------------------
| Initials      Name                      Company
| --------      ---------------------     -------------------------------------
| MM            Matteo MASTRODONATO       Bitron S.p.A.
|------------------------------------------------------------------------------
|                R E V I S I O N   H I S T O R Y
|------------------------------------------------------------------------------
| Date         Ver  Author  Description
| -----------  ---  ------  ----------------------------------------------------
| 21/oct/2014  0.1  MM      First draft
*/

#ifndef MOTP_CFGIF_H_
#define MOTP_CFGIF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef MOTP_CFGIF_OWNER
  #define MOTP_CFGIF_EXTERN
#else
  #define MOTP_CFGIF_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum MOTP_Handle_e
{
  MOTP_SLIDE = 0,
  MOTP_TILT     ,
  MOTP_LIFT     ,
  MOTP_BACK_R   ,
  MOTP_SPARE    ,
  MOTP_MAX_HDL
} MOTP_Handle_t;


typedef enum MOTP_CmdArrayHandle_e
{
  MOTP_ArraySlideTilt = 0,
  MOTP_ArrayLiftBack     ,
  MOTP_ArraySpare        ,
  MOTP_MAX_CMDA_HDL
} MOTP_CmdArrayHdl_t;


typedef enum {
  CMD_FERMO = 0,          /* USED */     /* Default value */
  CMD_AVANTI,             /* USED */
  CMD_INDIETRO,           /* USED */
  CMD_AVANTI_noHALL,      /* USED */
  CMD_INDIETRO_noHALL,    /* USED */
  CMD_VAI_POS,            /* USED */
  CMD_CHANGE_CONFORT      /* USED */
} CmdMotore;


typedef enum {
  MOTORE_FERMO = 0,       /* USED */    /* Default value */
  MOTORE_MOV_AVANTI,      /* USED */
  MOTORE_MOV_INDIETRO,    /* USED */
  MOTORE_FAIL,            /* USED */
  MOTORE_POS_CONFORT,     /* USED */
} StatiMotore;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/
/* the following macro must return TRUE when the MOTP position diagnostic need to be enabled.
   If no conditions need to be satisfied for position diagnosis set this define to TRUE */
/* For TESLA model X the condition is that he protection relays is not in "short to GND" fault,
   This information is taken from FVMP*/
#define MOTP_POS_DIAG_CONDITION    (FVMP_isProtReleOk())

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

MOTP_CFGIF_EXTERN void         MOTP_MotorFailEvent(MOTP_Handle_t motor, PRES_Fault_t fault);
MOTP_CFGIF_EXTERN void         MOTP_PosFailEvent(MOTP_Handle_t motor);
MOTP_CFGIF_EXTERN void         MOTP_CloseProtRel(MOTP_Handle_t motor);
MOTP_CFGIF_EXTERN void         MOTP_OverCurrentEvent(FVMP_Handle_t currFbkHdl, PRES_Fault_t fault, bool FaultDestructive);
MOTP_CFGIF_EXTERN void         MOTP_StrokeEvtMgm(MOTP_Handle_t motor);
MOTP_CFGIF_EXTERN void         MOTP_CfgPwrOff(void);
MOTP_CFGIF_EXTERN void         MOTP_ResetAllStrokes(void);
MOTP_CFGIF_EXTERN uint16_t     MOTP_GetMotorsCurrent(void);
MOTP_CFGIF_EXTERN PRES_Fault_t MOTP_GetMotorsCurrentDiag(u08 dummy);
MOTP_CFGIF_EXTERN void         MOTP_SavePosition(void);
MOTP_CFGIF_EXTERN void         MOTP_SetPosition(MOTP_Handle_t motor, int16_t pos);
/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MOTP_CFGIF_H_ */
