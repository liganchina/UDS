/********************************************************************************/
/* @F_PROJECT:          TTM 636 FIAT                                            */
/* F_NAME:              UDSA_cbk                                                */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/lug/2013                                             */
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
| 24/lug/2013     0.1  Matteo MASTRODONATO
*/

#ifndef UDSA_CBK_H_
#define UDSA_CBK_H_

#ifdef UDSA_IF_OWNER
	#define UDSA_EXTERN
#else
	#define UDSA_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

UDSA_EXTERN void UDSA_CheckDiagSessionAct(void);
UDSA_EXTERN void UDSA_IO_CtrlTimerElapsed(void);
UDSA_EXTERN void UDSA_SecAccess_ClearCounterOfAttempt(void);
UDSA_EXTERN void UDSA_Nak78PendingDelay(void);
UDSA_EXTERN void UDSA_EraseEepromCompleted(DRVD_RStatus_t ws);
UDSA_EXTERN void UDSA_WriteProgrammingStatus(void);

UDSA_EXTERN void UDSA_CallBoot(void);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* UDSA_CBK_H_ */
