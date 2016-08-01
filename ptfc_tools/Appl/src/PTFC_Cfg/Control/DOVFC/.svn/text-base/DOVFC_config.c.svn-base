/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DOVFC_config                                            */
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

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DOVFC.h"

/* Module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

#define DOVFC_RELPROT_HIGH 102U  /* 2.0 V  */

DRVD_Level_t DOVFC_GetRelProtLevel(DIAC_Channel_t chan);

/*______ G L O B A L - D A T A _______________________________________________*/

const DOVFC_CfgTable_t DOVFC_CfgTable[DOVFC_HDL_MAX] = {

/*  Handle                    OUT_CHAN               ACTIVE_LEVEL   FBK_GET_OP                         FBK_CHAN                     FBK_ACT_LEV  DRIVER_TYPE   DIAG_DEBOUNCE */
/*  DOVFC_CmdTiltSlideCom*/  {DIOD_CmdTiltSlideCom,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_TiltSlideComFdFbk,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdSlideFd     */  {DIOD_CmdSlideFd     ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_SlideFdFbk       ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdTiltUp      */  {DIOD_CmdTiltUp      ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_TiltUpFbk        ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdSpareMotCom */  {DIOD_SpareMotCom    ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_SpareComFbk      ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdSpareMotDw  */  {DIOD_SpareMotDw     ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_SpareDwFbk       ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdLiftBackrCom*/  {DIOD_CmdLiftBackrCom,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_LiftBackrComFbk  ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdLiftUp      */  {DIOD_CmdLiftUp      ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_LiftUpFbk        ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdBackrFd     */  {DIOD_CmdBackrFd     ,  L_HIGH,        (GetFbkIn_t)MUXC_GetLevel,         (u08)MUXC_BackrFdFbk       ,     L_LOW,      HSD,           2U        },
/*  DOVFC_CmdRelProtEN   */  {DIOD_CmdRelProtEN   ,  L_HIGH,        (GetFbkIn_t)DOVFC_GetRelProtLevel, (u08)DIAC_FbkProtRel       ,    L_HIGH,      HSD,           2U        },
/*  DOVFC_7V5Hall        */  {DIOD_7V5_En         ,  L_HIGH,        (GetFbkIn_t)DIAC_GetLevel,         (u08)DIAC_Fbk7V5           ,    L_HIGH,      HSD,           2U        },
};


/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

DRVD_Level_t DOVFC_GetRelProtLevel(DIAC_Channel_t chan)
{
  DRVD_Level_t ret_val;

  if (DOVFC_GetState(DOVFC_CmdRelProtEN) == S_ON)
  {
    ret_val = DIAC_GetLevel(chan);
  }
  else /* DOVFC_CmdRelProtEN = S_OFF */
  {
    if (ADCC_GetChnAvrgData(ADCC_RelProtFbk) >
       (ADCC_GetChnAvrgData(ADCC_MOT_Fbk) - DOVFC_RELPROT_HIGH))
    {
      ret_val = L_HIGH;
    }
    else
    {
      ret_val = L_LOW;
    }
  }
  
  return ret_val;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __DOVFC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

