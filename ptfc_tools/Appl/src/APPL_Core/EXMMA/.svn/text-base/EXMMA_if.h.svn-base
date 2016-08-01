/********************************************************************************/
/* @F_PROJECT:          LEAR F151 M                                             */
/* F_NAME:              EXMMA_if.h                                              */
/* @F_PURPOSE:          EXternal Mirrors Management module                      */
/* @F_CREATED_BY:       De Stephanis Alessio                                    */
/* F_CREATION_DATE:     31/mar/2015                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| ADS          De Stephanis Alessio      Intecs S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 31/mar/2015 0.1  ADS      First release
*/

#ifndef EXMMA_IF_H_
#define EXMMA_IF_H_

#ifdef EXMMA_IF_OWNER
  #define EXMMA_EXTERN
#else
  #define EXMMA_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define MEM_1     0u
#define MEM_2     1u
#define MEM_3     2u
#define NO_MEM    255u

#define LEFT      0u
#define RIGHT     1u

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

void EXMMA_Init(void);
void EXMMA_Mgm(void);
void EXMMA_MemRecall(uint8_t recMemory);
void EXMMA_MemSave(uint8_t savMemory);
void EXMMA_KeyStsChanged(PRES_KeyStatus_t KeyStatus);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* EXMMA_IF_H_ */
