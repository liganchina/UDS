/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DDMP_cbk                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     22/lug/2013                                                 */
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
| 22/lug/2013     0.1  Matteo MASTRODONATO
 */

#ifndef DDMP_CBK_H_
#define DDMP_CBK_H_


#ifdef DDMP_IF_OWNER
#define DDMP_EXTERN
#else
#define DDMP_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Funzione di servizio per il salvataggio dei dati in EEPROM */
DDMP_EXTERN void DDMP_KeyOffService( void );
DDMP_EXTERN void DDMP_SavingService( void );

#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
DDMP_EXTERN void DDMP_MngEcuTimeStampsFromKeyOn(void);
DDMP_EXTERN void DDMP_MngEcuTimeStamps(void);
#endif
/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DDMP_CBK_H_ */
