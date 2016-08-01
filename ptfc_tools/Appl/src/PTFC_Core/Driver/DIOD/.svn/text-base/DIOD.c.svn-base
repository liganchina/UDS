/**
 * @file DIOD.c
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief Core File of DIOD Driver. This driver is able set or read an electrical 
 * level on the selected channel
 * @link www.Bitron.net
 */

#define DIOD_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIOD.h"

/* Module inhibition filter */
#ifdef __DIOD_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

#if (DRVD_UC_PACKAGE == DRVD_48_PIN) /* uC 78F1826 - 48pin */

const DIOD_ResourceTab_t DIOD_ResTab[PORT_HDL_MAX] =
{
  {&P0,  BIT_0_MASK},

  {&P1,  BIT_0_MASK},
  {&P1,  BIT_1_MASK},
  {&P1,  BIT_2_MASK},
  {&P1,  BIT_3_MASK},
  {&P1,  BIT_4_MASK},
  {&P1,  BIT_5_MASK},
  {&P1,  BIT_6_MASK},
  {&P1,  BIT_7_MASK},

  {&P3,  BIT_0_MASK},
  {&P3,  BIT_1_MASK},
  {&P3,  BIT_2_MASK},

  {&P4,  BIT_0_MASK},
  {&P4,  BIT_1_MASK},

  {&P6,  BIT_0_MASK},
  {&P6,  BIT_1_MASK},
  {&P6,  BIT_2_MASK},
  {&P6,  BIT_3_MASK},

  {&P7,  BIT_0_MASK},
  {&P7,  BIT_1_MASK},
  {&P7,  BIT_2_MASK},
  {&P7,  BIT_3_MASK},

  {&P8,  BIT_0_MASK},
  {&P8,  BIT_1_MASK},
  {&P8,  BIT_2_MASK},
  {&P8,  BIT_3_MASK},
  {&P8,  BIT_4_MASK},
  {&P8,  BIT_5_MASK},
  {&P8,  BIT_6_MASK},
  {&P8,  BIT_7_MASK},

  {&P9,  BIT_0_MASK},
  {&P9,  BIT_1_MASK},
  {&P9,  BIT_2_MASK},

  {&P12, BIT_0_MASK},
  {&P12, BIT_1_MASK},
  {&P12, BIT_2_MASK},
  {&P12, BIT_3_MASK},
  {&P12, BIT_4_MASK},
  {&P12, BIT_5_MASK},

  {&P13, BIT_0_MASK},

  {&P14, BIT_0_MASK},
};
#endif


#if (DRVD_UC_PACKAGE == DRVD_64_PIN) /* uC 78K0R family - 64pin */

const DIOD_ResourceTab_t DIOD_ResTab[PORT_HDL_MAX] =
{
  {&P0,  BIT_0_MASK},

  {&P1,  BIT_0_MASK},
  {&P1,  BIT_1_MASK},
  {&P1,  BIT_2_MASK},
  {&P1,  BIT_3_MASK},
  {&P1,  BIT_4_MASK},
  {&P1,  BIT_5_MASK},
  {&P1,  BIT_6_MASK},
  {&P1,  BIT_7_MASK},

  {&P3,  BIT_0_MASK},
  {&P3,  BIT_1_MASK},
  {&P3,  BIT_2_MASK},

  {&P4,  BIT_0_MASK},
  {&P4,  BIT_1_MASK},
  {&P4,  BIT_2_MASK},
  {&P4,  BIT_3_MASK},

  {&P5,  BIT_0_MASK},
  {&P5,  BIT_1_MASK},
  {&P5,  BIT_2_MASK},
  {&P5,  BIT_3_MASK},

  {&P6,  BIT_0_MASK},
  {&P6,  BIT_1_MASK},
  {&P6,  BIT_2_MASK},
  {&P6,  BIT_3_MASK},

  {&P7,  BIT_0_MASK},
  {&P7,  BIT_1_MASK},
  {&P7,  BIT_2_MASK},
  {&P7,  BIT_3_MASK},
  {&P7,  BIT_4_MASK},
  {&P7,  BIT_5_MASK},
  {&P7,  BIT_6_MASK},
  {&P7,  BIT_7_MASK},

  {&P8,  BIT_0_MASK},
  {&P8,  BIT_1_MASK},
  {&P8,  BIT_2_MASK},
  {&P8,  BIT_3_MASK},
  {&P8,  BIT_4_MASK},
  {&P8,  BIT_5_MASK},
  {&P8,  BIT_6_MASK},
  {&P8,  BIT_7_MASK},

  {&P9,  BIT_0_MASK},
  {&P9,  BIT_1_MASK},
  {&P9,  BIT_2_MASK},
  {&P9,  BIT_3_MASK},
  {&P9,  BIT_4_MASK},
  {&P9,  BIT_5_MASK},
  {&P9,  BIT_6_MASK},

  {&P12, BIT_0_MASK},
  {&P12, BIT_1_MASK},
  {&P12, BIT_2_MASK},
  {&P12, BIT_3_MASK},
  {&P12, BIT_4_MASK},
  {&P12, BIT_5_MASK},

  {&P13, BIT_0_MASK},

  {&P14, BIT_0_MASK},
};
#endif


#if (DRVD_UC_PACKAGE == DRVD_80_PIN) /* uC 78F1837 - 80pin */

const DIOD_ResourceTab_t DIOD_ResTab[PORT_HDL_MAX] =
{
  {&P0,  BIT_0_MASK},
  {&P0,  BIT_1_MASK},
  {&P0,  BIT_2_MASK},

  {&P1,  BIT_0_MASK},
  {&P1,  BIT_1_MASK},
  {&P1,  BIT_2_MASK},
  {&P1,  BIT_3_MASK},
  {&P1,  BIT_4_MASK},
  {&P1,  BIT_5_MASK},
  {&P1,  BIT_6_MASK},
  {&P1,  BIT_7_MASK},

  {&P3,  BIT_0_MASK},
  {&P3,  BIT_1_MASK},
  {&P3,  BIT_2_MASK},

  {&P4,  BIT_0_MASK},
  {&P4,  BIT_1_MASK},
  {&P4,  BIT_2_MASK},
  {&P4,  BIT_3_MASK},
  {&P4,  BIT_4_MASK},
  {&P4,  BIT_5_MASK},
  {&P4,  BIT_6_MASK},
  {&P4,  BIT_7_MASK},

  {&P5,  BIT_0_MASK},
  {&P5,  BIT_1_MASK},
  {&P5,  BIT_2_MASK},
  {&P5,  BIT_3_MASK},
  {&P5,  BIT_4_MASK},
  {&P5,  BIT_5_MASK},
  {&P5,  BIT_6_MASK},
  {&P5,  BIT_7_MASK},

  {&P6,  BIT_0_MASK},
  {&P6,  BIT_1_MASK},
  {&P6,  BIT_2_MASK},
  {&P6,  BIT_3_MASK},
  {&P6,  BIT_4_MASK},
  {&P6,  BIT_5_MASK},
  {&P6,  BIT_6_MASK},
  {&P6,  BIT_7_MASK},

  {&P7,  BIT_0_MASK},
  {&P7,  BIT_1_MASK},
  {&P7,  BIT_2_MASK},
  {&P7,  BIT_3_MASK},
  {&P7,  BIT_4_MASK},
  {&P7,  BIT_5_MASK},
  {&P7,  BIT_6_MASK},
  {&P7,  BIT_7_MASK},

  {&P8,  BIT_0_MASK},
  {&P8,  BIT_1_MASK},
  {&P8,  BIT_2_MASK},
  {&P8,  BIT_3_MASK},
  {&P8,  BIT_4_MASK},
  {&P8,  BIT_5_MASK},
  {&P8,  BIT_6_MASK},
  {&P8,  BIT_7_MASK},

  {&P9,  BIT_0_MASK},
  {&P9,  BIT_1_MASK},
  {&P9,  BIT_2_MASK},
  {&P9,  BIT_3_MASK},
  {&P9,  BIT_4_MASK},
  {&P9,  BIT_5_MASK},
  {&P9,  BIT_6_MASK},
  {&P9,  BIT_7_MASK},

  {&P12, BIT_0_MASK},
  {&P12, BIT_1_MASK},
  {&P12, BIT_2_MASK},
  {&P12, BIT_3_MASK},
  {&P12, BIT_4_MASK},
  {&P12, BIT_5_MASK},
  {&P12, BIT_6_MASK},

  {&P13, BIT_0_MASK},

  {&P14, BIT_0_MASK},
};
#endif

#if (DRVD_UC_PACKAGE == DRVD_100_PIN) /* uC 78F1843 - 100pin */

const DIOD_ResourceTab_t DIOD_ResTab[PORT_HDL_MAX] =
{
  {&P0,  BIT_0_MASK},
  {&P0,  BIT_1_MASK},
  {&P0,  BIT_2_MASK},
  {&P0,  BIT_3_MASK},

  {&P1,  BIT_0_MASK},
  {&P1,  BIT_1_MASK},
  {&P1,  BIT_2_MASK},
  {&P1,  BIT_3_MASK},
  {&P1,  BIT_4_MASK},
  {&P1,  BIT_5_MASK},
  {&P1,  BIT_6_MASK},
  {&P1,  BIT_7_MASK},

  {&P3,  BIT_0_MASK},
  {&P3,  BIT_1_MASK},
  {&P3,  BIT_2_MASK},

  {&P4,  BIT_0_MASK},
  {&P4,  BIT_1_MASK},
  {&P4,  BIT_2_MASK},
  {&P4,  BIT_3_MASK},
  {&P4,  BIT_4_MASK},
  {&P4,  BIT_5_MASK},
  {&P4,  BIT_6_MASK},
  {&P4,  BIT_7_MASK},

  {&P5,  BIT_0_MASK},
  {&P5,  BIT_1_MASK},
  {&P5,  BIT_2_MASK},
  {&P5,  BIT_3_MASK},
  {&P5,  BIT_4_MASK},
  {&P5,  BIT_5_MASK},
  {&P5,  BIT_6_MASK},
  {&P5,  BIT_7_MASK},

  {&P6,  BIT_0_MASK},
  {&P6,  BIT_1_MASK},
  {&P6,  BIT_2_MASK},
  {&P6,  BIT_3_MASK},
  {&P6,  BIT_4_MASK},
  {&P6,  BIT_5_MASK},
  {&P6,  BIT_6_MASK},
  {&P6,  BIT_7_MASK},

  {&P7,  BIT_0_MASK},
  {&P7,  BIT_1_MASK},
  {&P7,  BIT_2_MASK},
  {&P7,  BIT_3_MASK},
  {&P7,  BIT_4_MASK},
  {&P7,  BIT_5_MASK},
  {&P7,  BIT_6_MASK},
  {&P7,  BIT_7_MASK},

  {&P8,  BIT_0_MASK},
  {&P8,  BIT_1_MASK},
  {&P8,  BIT_2_MASK},
  {&P8,  BIT_3_MASK},
  {&P8,  BIT_4_MASK},
  {&P8,  BIT_5_MASK},
  {&P8,  BIT_6_MASK},
  {&P8,  BIT_7_MASK},

  {&P9,  BIT_0_MASK},
  {&P9,  BIT_1_MASK},
  {&P9,  BIT_2_MASK},
  {&P9,  BIT_3_MASK},
  {&P9,  BIT_4_MASK},
  {&P9,  BIT_5_MASK},
  {&P9,  BIT_6_MASK},
  {&P9,  BIT_7_MASK},

  {&P10, BIT_0_MASK},
  {&P10, BIT_1_MASK},
  {&P10, BIT_2_MASK},
  {&P10, BIT_3_MASK},
  {&P10, BIT_4_MASK},
  {&P10, BIT_5_MASK},
  {&P10, BIT_6_MASK},
  {&P10, BIT_7_MASK},

  {&P12, BIT_0_MASK},
  {&P12, BIT_1_MASK},
  {&P12, BIT_2_MASK},
  {&P12, BIT_3_MASK},
  {&P12, BIT_4_MASK},
  {&P12, BIT_5_MASK},
  {&P12, BIT_6_MASK},
  {&P12, BIT_7_MASK},

  {&P13, BIT_0_MASK},

  {&P14, BIT_0_MASK},

  {&P15, BIT_0_MASK},
  {&P15, BIT_1_MASK},
  {&P15, BIT_2_MASK},
  {&P15, BIT_3_MASK},
  {&P15, BIT_4_MASK},
  {&P15, BIT_5_MASK},
  {&P15, BIT_6_MASK},
  {&P15, BIT_7_MASK},
};
#endif

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function Initializes the DIOD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void DIOD_Init(void)
{
}

/**
 * @brief This function set the electrical level of requested channel.
 * @param chan the requested channel
 * @param level the requested electrical level
 * @return the result of the operation.
 */
DRVD_RStatus_t DIOD_SetLevel(DIOD_Channel_t chan, DRVD_Level_t level)
{
  DRVD_RStatus_t valueReturn;

  if (chan < DIOD_HDL_MAX)  /* 
      Per sviluppi futuri...
      && level <= L_HIGH
      &&  DIOD_CfgTable[chan].direction == OUTPUT */
  {
    if (level == L_HIGH)
    {
      *DIOD_ResTab[DIOD_CfgTable[chan]].outPort |= DIOD_ResTab[DIOD_CfgTable[chan]].bitMask;
    }
    else
    {
      *DIOD_ResTab[DIOD_CfgTable[chan]].outPort &= (u08)~DIOD_ResTab[DIOD_CfgTable[chan]].bitMask;
    }

    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return (valueReturn);
}

/**
 * @brief This function returns the level of requested input.
 * @param chan the requested channel
 * @return the result of the operation.
 */
DRVD_Level_t DIOD_GetLevel(DIOD_Channel_t chan)
{
  DRVD_Level_t valueReturn;

  if (chan < DIOD_HDL_MAX)
  {
    if (*DIOD_ResTab[DIOD_CfgTable[chan]].outPort & DIOD_ResTab[DIOD_CfgTable[chan]].bitMask)
    {
      valueReturn = L_HIGH;
    }
    else
    {
      valueReturn = L_LOW;
    }
  }
  else
  {
    valueReturn = (DRVD_Level_t) 0xFF;
  }

  return (valueReturn);
}


#endif /* end __DIOD_IS_PRESENT__ */

/*______ E N D _____ (DIOD.c) ________________________________________________*/
