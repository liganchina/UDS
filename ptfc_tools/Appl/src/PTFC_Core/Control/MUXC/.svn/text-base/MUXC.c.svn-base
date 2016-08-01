/**
 * @file MUXC.c
 * @author mmastrodonato
 * @date 10/set/2014
 * @brief Multiplexer management module.
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 * MM             Matteo Mastrodonato       Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 10/set/2014    0.1  MM      First revision
 */

#define MUXC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MUXC.h"
#include "MUXC_config.h"

#ifdef __MUXC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/* Max multiplexer size (real size) */
#define MUXC_MUX_SIZE       (1U << MUXC_MAX_MUX_SIZE)

#if (MUXC_ANALOG_EN == TRUE)
/* Virtual Analog channel buffer size */
#define MUXC_AN_BUFF_SIZE   (MUXC_AN_MUX_NUM_HDL  * MUXC_MUX_SIZE)
#endif

#if (MUXC_DIGITAL_EN == TRUE)
/* Virtual Digital channel buffer size */
#define MUXC_DGT_BUFF_SIZE  (MUXC_DGT_MUX_NUM_HDL * MUXC_MUX_SIZE)
#endif

/*______ P R I V A T E - D A T A _____________________________________________*/

#if (MUXC_ANALOG_EN == TRUE)
/* Virtual Analog channel input buffer */
u16 Muxc_AnValue [MUXC_AN_BUFF_SIZE];
#endif

#if (MUXC_DIGITAL_EN == TRUE)
/* Virtual Digital channel input buffer */
DRVD_Level_t Muxc_DgtValue[MUXC_DGT_BUFF_SIZE];
#endif

/* Current multiplexer channel selected */
u08 Muxc_CurrentChan;

/* Declaration of configuration objects */
#if (MUXC_ANALOG_EN == TRUE)
  extern const ADCD_InputChn_t    MUXC_AnMuxArray     [MUXC_AN_MUX_NUM_HDL ];
  extern const MUXC_AnCfgTable_t  MUXC_AnChanCfgTable [MUXC_AN_CH_NUM_HDL  ];
#endif

#if (MUXC_DIGITAL_EN == TRUE)
  extern const DIOD_Channel_t     MUXC_DgtMuxArray    [MUXC_DGT_MUX_NUM_HDL];
  extern const MUXC_DgtCfgTable_t MUXC_DgtChanCfgTable[MUXC_DGT_CH_NUM_HDL ];
#endif

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief Initialization routine for MUXC module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void MUXC_Init(void)
{
  u08 tmpIdx;

#if (MUXC_ANALOG_EN == TRUE)
  /* Init analog virtual channel buffer */
  for (tmpIdx = 0U; tmpIdx < MUXC_AN_BUFF_SIZE; tmpIdx++)
  {
    Muxc_AnValue[tmpIdx] = 0U;
  }
#endif

#if (MUXC_DIGITAL_EN == TRUE)
  /* Init digital virtual channel buffer */
  for (tmpIdx = 0U; tmpIdx < MUXC_DGT_BUFF_SIZE; tmpIdx++)
  {
    Muxc_DgtValue[tmpIdx] = L_LOW;
  }
#endif

  Muxc_CurrentChan = 0U;

  /* Set channel 0 channel */
  DIOD_SetLevel(MUXC_SEL_1, L_LOW);
  DIOD_SetLevel(MUXC_SEL_2, L_LOW);
  DIOD_SetLevel(MUXC_SEL_3, L_LOW);

#if (MUXC_ANALOG_EN == TRUE)
  /* Set the End of ADC conversion callback */
  ISRD_SetEvtCbk(ISRD_VECTOR_BRK_I, (ISRD_EvtCbk_t)MUXC_AdcEndOfConv);
#endif
}


/**
 * @brief Periodic call to manage the channel selection and acquisition.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
#if (MUXC_ANALOG_EN == TRUE)
uint16_t MUXC_AdcEndOfConv(void)
{
  MUXC_AnMux_t  muxAnHdl;

  /* Acquire the value of each analog multiplexer */
  for (muxAnHdl = (MUXC_AnMux_t)0U; muxAnHdl < MUXC_AN_MUX_NUM_HDL; muxAnHdl++)
  {
    Muxc_AnValue[(muxAnHdl << MUXC_MAX_MUX_SIZE) + Muxc_CurrentChan] = ADCD_GetChannelData(MUXC_AnMuxArray[muxAnHdl]);
  }
  
  return ISRD_ComputeCbkCheck(ISRD_VECTOR_BRK_I);
}
#endif

void MUXC_Mgm(void)
{
#if (MUXC_DIGITAL_EN == TRUE)
  MUXC_DgtMux_t muxDgtHdl;
  
  /* Acquire the value of each digital multiplexer */
  for (muxDgtHdl = (MUXC_DgtMux_t)0U; muxDgtHdl < MUXC_DGT_MUX_NUM_HDL; muxDgtHdl++)
  {
    Muxc_DgtValue[(muxDgtHdl << MUXC_MAX_MUX_SIZE) + Muxc_CurrentChan] = DIOD_GetLevel(MUXC_DgtMuxArray[muxDgtHdl]);
  }
#endif
  /* Increment the mux channel */
  Muxc_CurrentChan++;

  /* Limit the channel to max size */
  if (Muxc_CurrentChan == MUXC_MUX_SIZE)
  {
    Muxc_CurrentChan = 0U;
  }
  else
  {
  }
  /*Muxc_CurrentChan &= ~((u08)MUXC_MUX_SIZE) */

  /* Set next channel */
  DIOD_SetLevel(MUXC_SEL_1, (DRVD_Level_t)( Muxc_CurrentChan & (u08)0x01U));
  DIOD_SetLevel(MUXC_SEL_2, (DRVD_Level_t)((Muxc_CurrentChan & (u08)0x02U)>>1U));
  DIOD_SetLevel(MUXC_SEL_3, (DRVD_Level_t)((Muxc_CurrentChan & (u08)0x04U)>>2U));

}


/**
 * @brief This routine returns the last ADC value read for a channel.
 *
 * @param [in] channel  Virtual channel handle.
 * @param [out] None
 *
 * @return u16 The conversion result of virtual requested channel.
 */
#if (MUXC_ANALOG_EN == TRUE)
u16 MUXC_GetChannelData(MUXC_AnChannel_t channel)
{
  return Muxc_AnValue[(MUXC_AnChanCfgTable[channel].MUX_HDL << MUXC_MAX_MUX_SIZE) + MUXC_AnChanCfgTable[channel].MUX_CHANNEL];
}
#endif

/**
 * @brief This routine returns the last read physical value for a channel.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return DRVD_Level_t the physical value of requested channel.
 * @retval L_LOW
 * @retval L_HIGH
 */
#if (MUXC_DIGITAL_EN == TRUE)
DRVD_Level_t MUXC_GetLevel(MUXC_DgtChannel_t channel)
{
  return Muxc_DgtValue[(MUXC_DgtChanCfgTable[channel].MUX_HDL << MUXC_MAX_MUX_SIZE) + MUXC_DgtChanCfgTable[channel].MUX_CHANNEL];
}
#endif

#endif /*  __MUXC_IS_PRESENT__  */

/*______ E N D _____ (MUXC.c) _________________________________________*/
