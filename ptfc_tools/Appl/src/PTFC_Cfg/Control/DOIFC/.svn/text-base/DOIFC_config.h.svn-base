/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DOIFC_config                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     21/giu/2013                                                 */
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
| ----------  ---  ------  ---------------------------------------------------
| 21/giu/2013      0.1     Matteo MASTRODONATO
*/

#ifndef DOIFC_CONFIG_H_
#define DOIFC_CONFIG_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/**
 * Enable/Disable the high/low gain pin control for current feedback (pin is
 * configured in DOIFC_CfgTable as parameter FBK_GAIN_CHAN).
 * If DOIFC_HIGH_GAIN_FBK_EN is disabled the diagnosis state machine disables
 * the following internal states:
 *  - OPEN LOAD DIAG (used for Oper Load diagnosis with High Gain)
 *  - ENDING DIAG 1 (dummy state for timing alignment)
 * When DOIFC_HIGH_GAIN_FBK_EN is disabled the DOIFC_PerformDiag() calls
 * requested for complete a diagnosis cycle are reduced of one tick.
 *
 */
#define DOIFC_HIGH_GAIN_FBK_EN        FALSE

/**
 * Enable/Disable the high/low fkb enable pin control before starting
 * diagnosis.
 * When DOIFC_EN_FBK_PORT_EN is disabled the DOIFC_PerformDiag() calls
 * requested for complete a diagnosis cycle are reduced of one tick.
 *
 */
//#define DOIFC_EN_FBK_PIN_EN           TRUE


#define DOIFC_OL_TEST_OUT_OFF_START(hdl)
#define DOIFC_OL_TEST_OUT_OFF_END(hdl)

#define DOIFC_OL_TEST_HIGH_GAIN_START(hdl)
#define DOIFC_OL_TEST_HIGH_GAIN_END(hdl)


#define DOIFC_CONFIG_INIT()           DOIFC_UserCfg();

/* this define is used to get feedback not from ADCC (multipleexed feedback managed by DOIFC_Config.c */
#define DOIFC_GET_FBK(hdl)            DOIFC_GetFbk(hdl)

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern void DOIFC_UserCfg(void);
extern uint16_t DOIFC_GetFbk(DOIFC_Handle_t hdl);

#endif /* DOIFC_CONFIG_H_ */
