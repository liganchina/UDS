/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DOVFC_cfgIf                                            */
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
| ----------  ---  ------  ----------------------------------------------------
| 21/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DOVFC_CFGIF_H_
#define DOVFC_CFGIF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum DOVFC_Handle_e
{
  DOVFC_CmdTiltSlideCom,  /* cmdRele1A */
  DOVFC_CmdSlideFd     ,  /* cmdRele1B */
  DOVFC_CmdTiltUp      ,  /* cmdRele2  */
  DOVFC_CmdSpareMotCom ,  /* cmdRele3A */
  DOVFC_CmdSpareMotDw  ,  /* cmdRele3B */
  DOVFC_CmdLiftBackrCom,  /* cmdRele4  */
  DOVFC_CmdLiftUp      ,  /* cmdRele5A */
  DOVFC_CmdBackrFd     ,  /* cmdRele5B */
  DOVFC_CmdRelProtEN   ,  /* cmdRele6 */
  DOVFC_7V5Hall        ,  /* AlimHall  */
  DOVFC_HDL_MAX
}DOVFC_Handle_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/



/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DOVFC_CFGIF_H_ */
