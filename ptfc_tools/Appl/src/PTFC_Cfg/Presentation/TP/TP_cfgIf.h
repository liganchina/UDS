/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              TP_CfgIf                                            */
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

#ifndef TP_CFGIF_H_
#define TP_CFGIF_H_

#ifdef TP_CONFIG_IF_OWNER
	#define TP_CONFIG_IF_EXTERN
#else
	#define TP_CONFIG_IF_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define TP_ENABLE_PADDING        FALSE
#define TP_PADDING_BYTE          0x00U   /* Byte usato per il padding (se abilitato) */
#define RXBUF_LENGTH             266U
#define TXBUF_LENGTH             266U

#define TP_HIPRTY_PHYS_MSG_EN    FALSE   /* To manage high priority physical addressing diagnostic messages (if enabled)*/
#define TP_FUNC_MSG_EN           TRUE    /* To manage functional addressing diagnostic messages (if enabled)*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* TP_CFGIF_H_ */
