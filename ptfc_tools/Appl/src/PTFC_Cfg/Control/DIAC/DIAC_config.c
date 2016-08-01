/**
 * @file DIAC_config.c
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of DIAC Driver.
 *
 * @see www.Bitron.net
 */

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIAC.h"
#include "DIAC_config.h"

#ifdef __DIAC_IS_PRESENT__

#define DIAC_CFG_IF_OWNER

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

const DIAC_VrefTable_t DIAC_VrefTable[DIAC_VREF_MAX] = {
/*                     ADCC_VREF_IDN    VREF_HW_GAIN     VREF_HW_OFFSET */
/*                                      [1/1024 lsb]      [4883uV/LSB]  */
/* DIAC_KeyRef   */ {  ADCC_KeyDiag,    DIAC_NO_GAIN,         -172,       },
};

const DIAC_ThresTable_t DIAC_ThresTable[DIAC_THRES_MAX] = {
/*                       RATIO         THRES       VREF_AD_IDN     INIT_VALUE  */
/*                    [1/1024 LSB]  [4883uV/BIT]                  [4883uV/BIT] */
/* DIAC_0Key0     */ {      0U,           0U,       DIAC_KeyRef,         0U,    },
/* DIAC_0Key16    */ {    164U,           0U,       DIAC_KeyRef,       174U,    },
/* DIAC_0Key30    */ {    303U,           0U,       DIAC_KeyRef,       239U,    },
/* DIAC_0Key47    */ {    466U,           0U,       DIAC_KeyRef,       363U,    },
/* DIAC_0Key61    */ {    613U,           0U,       DIAC_KeyRef,       573U,    },
/* DIAC_0Key77    */ {    771U,           0U,       DIAC_KeyRef,       665U,    },
/* DIAC_0Key84    */ {    841U,           0U,       DIAC_KeyRef,       765U,    },
/* DIAC_0Key90    */ {    921U,           0U,       DIAC_KeyRef,       759U,    },
/* DIAC_0Key98    */ {    982U,           0U,       DIAC_KeyRef,       859U,    },
/* DIAC_KB_5V00   */ {      0U,        1024U,       DIAC_VREF_MAX,    1024U,    },
/* DIAC_FHall_9V5 */ {      0U,         300U,       DIAC_VREF_MAX,     300U,    }, /* TODO COBRA: da configurare */
/* DIAC_FHall_5V5 */ {      0U,         500U,       DIAC_VREF_MAX,     500U,    }, /* TODO COBRA: da configurare */
/* DIAC_RProt_9V5 */ {      0U,         480U,       DIAC_VREF_MAX,     480U,    },
/* DIAC_RProt_5V5 */ {      0U,         250U,       DIAC_VREF_MAX,     250U,    },
};

/*______ G L O B A L - D A T A _______________________________________________*/

/* I valori delle soglie si riferiscono alla tensione sul PIN Connettore */

const DIAC_CfgTable_t DIAC_CfgTable[DIAC_HDL_MAX] =
{
/* HANDLE                  ADCC_CHAN           THRES_HIGH_IDN     THRES_LOW_IDN    INIT_VALUE  MULTI_LEVEL_MODE  */
/* DIAC_Mem1          */ { ADCC_MemKey,         DIAC_0Key98,       DIAC_0Key84,       L_LOW,        TRUE  },
/* DIAC_Mem2          */ { ADCC_MemKey,         DIAC_0Key47,       DIAC_0Key0,        L_LOW,        TRUE  },
/* DIAC_Mem3          */ { ADCC_MemKey,         DIAC_0Key84,       DIAC_0Key47,       L_LOW,        TRUE  },
/* DIAC_Back_BW       */ { ADCC_BackrLiftKey,   DIAC_0Key77,       DIAC_0Key61,       L_LOW,        TRUE  },
/* DIAC_Back_FW       */ { ADCC_BackrLiftKey,   DIAC_0Key61,       DIAC_0Key47,       L_LOW,        TRUE  },
/* DIAC_Tilt_UP       */ { ADCC_SlideTiltKey,   DIAC_0Key30,       DIAC_0Key16,       L_LOW,        TRUE  },
/* DIAC_Tilt_DW       */ { ADCC_SlideTiltKey,   DIAC_0Key47,       DIAC_0Key30,       L_LOW,        TRUE  },
/* DIAC_Slide_FW      */ { ADCC_SlideTiltKey,   DIAC_0Key61,       DIAC_0Key47,       L_LOW,        TRUE  },
/* DIAC_Slide_BW      */ { ADCC_SlideTiltKey,   DIAC_0Key77,       DIAC_0Key61,       L_LOW,        TRUE  },
/* DIAC_Lift_DW       */ { ADCC_BackrLiftKey,   DIAC_0Key47,       DIAC_0Key30,       L_LOW,        TRUE  },
/* DIAC_Lift_UP       */ { ADCC_BackrLiftKey,   DIAC_0Key30,       DIAC_0Key16,       L_LOW,        TRUE  },
/* DIAC_Fbk7V5        */ { ADCC_7V5_Fbk,        DIAC_FHall_9V5,    DIAC_FHall_5V5,    L_LOW,        FALSE },
/* DIAC_SlideTilt_OPEN*/ { ADCC_SlideTiltKey,   DIAC_KB_5V00,      DIAC_0Key77,       L_LOW,        TRUE  },
/* DIAC_BackrLift_OPEN*/ { ADCC_BackrLiftKey,   DIAC_KB_5V00,      DIAC_0Key77,       L_LOW,        TRUE  },
/* DIAC_Mem_OPEN      */ { ADCC_MemKey,         DIAC_KB_5V00,      DIAC_0Key98,       L_LOW,        TRUE  },
/* DIAC_FbkProtRel    */ { ADCC_RelProtFbk,     DIAC_RProt_5V5,    DIAC_RProt_2V5,    L_LOW,        FALSE },
};

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


CTRL_Fault_t DIAC_GetButtonDiag(DIAC_Channel_t chan)
{
  CTRL_Fault_t fault;

  if (DIAC_GetLevel(chan) != DIAC_CfgTable[chan].INIT_VALUE)
  {
    fault = CTRL_BUTTON_STUCKED;
  }
  else
  {
    fault = CTRL_NO_FAULT;
  }

  return fault;
}

CTRL_Fault_t DIAC_GetBtnTiltSlideDiag(DIAC_Channel_t chan)
{
  CTRL_Fault_t fault;
  DIAC_Channel_t i;

  fault = CTRL_NO_FAULT;

  for (i = DIAC_Tilt_UP; i <= DIAC_Slide_BW; i++)
  {
    if (DIAC_GetLevel(i) != L_LOW)
    {
      fault = CTRL_BUTTON_STUCKED;
      break;
    }
  }

  return fault;
}

CTRL_Fault_t DIAC_GetBtnLiftBackDiag(DIAC_Channel_t chan)
{
  CTRL_Fault_t fault;
  DIAC_Channel_t i;

  fault = CTRL_NO_FAULT;

  for (i = DIAC_Lift_DW; i <= DIAC_Lift_UP; i++)
  {
    if (DIAC_GetLevel(i) != L_LOW)
    {
      fault = CTRL_BUTTON_STUCKED;
      break;
    }
  }

  for (i = DIAC_Back_BW; i <= DIAC_Back_FW; i++)
  {
    if (DIAC_GetLevel(i) != L_LOW)
    {
      fault = CTRL_BUTTON_STUCKED;
      break;
    }
  }

  return fault;
}

CTRL_Fault_t DIAC_GetBtnMemDiag(DIAC_Channel_t chan)
{
  CTRL_Fault_t fault;
  DIAC_Channel_t i;

  fault = CTRL_NO_FAULT;

  for (i = DIAC_Mem1; i <= DIAC_Mem3; i++)
  {
    if (DIAC_GetLevel(i) != L_LOW)
    {
      fault = CTRL_BUTTON_STUCKED;
      break;
    }
  }
  
  return fault;
}

#endif /* __DIAC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

