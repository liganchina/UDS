/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                                */
/* F_NAME:              DINP_config                                             */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     10/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 10/giu/2013 0.1  Matteo MASTRODONATO
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DINP.h"

/* Module inhibition filter */
#ifdef __DINP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D E F I N E _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/


const DINP_CfgTable_t DINP_CfgTable[DINP_HDL_MAX] = {
/*                       INP_IDN,             GET_VALUE_PTR,              N_TEST, ACTIVE_LEVEL,  INITIAL_STATE,  STATE_CHANGED     */
/* DINP_Mem1  = 0   */  { DIAC_Mem1        ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_Mem1Input_Cbk      },
/* DINP_Mem2        */  { DIAC_Mem2        ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_Mem2Input_Cbk      },
/* DINP_Mem3        */  { DIAC_Mem3        ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_Mem3Input_Cbk      },
/* DINP_Back_BW     */  { DIAC_Back_BW     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_BackrestBwInput_Cbk},
/* DINP_Back_FW     */  { DIAC_Back_FW     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_BackrestFwInput_Cbk},
/* DINP_Tilt_UP     */  { DIAC_Tilt_UP     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_TiltUpInput_Cbk    },
/* DINP_Tilt_DW     */  { DIAC_Tilt_DW     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_TiltDwInput_Cbk    },
/* DINP_Slide_FW    */  { DIAC_Slide_FW    ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_SlideFwInput_Cbk   },
/* DINP_Slide_BW    */  { DIAC_Slide_BW    ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_SlideBwInput_Cbk   },
/* DINP_Lift_DW     */  { DIAC_Lift_DW     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_LiftDwInput_Cbk    },
/* DINP_Lift_UP     */  { DIAC_Lift_UP     ,   (GetDigIn_t)DIAC_GetLevel,    8u,     L_HIGH,         S_OFF,       DISPA_LiftUpInput_Cbk    },
/* DINP_SteerHeatSw */  { DIOD_SteerHeatSw ,   (GetDigIn_t)DIOD_GetLevel,    8u,     L_HIGH,         S_OFF,       NULL                     },
/* DINP_SlideTilt_OPEN*/{ DIAC_SlideTilt_OPEN, (GetDigIn_t)DIAC_GetLevel,    7u,     L_HIGH,         S_OFF,       DISPA_SlideTiltOpen_Cbk  },
/* DINP_BackrLift_OPEN*/{ DIAC_BackrLift_OPEN, (GetDigIn_t)DIAC_GetLevel,    7u,     L_HIGH,         S_OFF,       DISPA_BackrLiftOpen_Cbk  },
/* DINP_Mem_OPEN      */{ DIAC_Mem_OPEN      , (GetDigIn_t)DIAC_GetLevel,    7u,     L_HIGH,         S_OFF,       DISPA_MemOpen_Cbk        },
};


/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


#endif /* end __DINP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

