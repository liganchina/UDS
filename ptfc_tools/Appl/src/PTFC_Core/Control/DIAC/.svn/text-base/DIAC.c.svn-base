/**
 * @file DIAC.c
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief Core File of DIAC Driver. This driver is able to convert
 *  an analog input in a digital one, in according with the configured
 *  voltage thresholds.
 *
 * @see www.Bitron.net
 */


#define DIAC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIAC.h"
#include "DIAC_config.h"
#include "stdlib.h"       /* Funzione abs() */

/* Module inhibition filter */
#ifdef __DIAC_IS_PRESENT__
/*______ L O C A L - T Y P E S _______________________________________________*/


typedef struct
{
  DRVD_Level_t channelLevel;
  CTRL_EnSts_t functionState;   /*Function State, enabled/disabled by proxi*/
}DIAC_PrivateData_t;
#if 0
typedef struct
{
 uint16_t thresLevel;
 }DIAC_ThresData_t;
#endif

/*______ L O C A L - M A C R O S _____________________________________________*/

 /* Tick number to scan all thresholds configured */
 #define DIAC_SCAN_TICK_NMB      ((uint8_t)(DIAC_CHN_SCAN_TIME_US/DIAC_TICK_TIME))

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

 DIAC_PrivateData_t       Diac_PrivateData[DIAC_HDL_MAX];
 static uint16_t          Diac_ThresLevel  [DIAC_THRES_MAX];
 static uint16_t          Diac_VrefValue   [DIAC_VREF_MAX];

 /* Current channel buffer */
 static DIAC_Thresholds_t Diac_CurrentThres;
 /* Variables for spreading strategy */
 static uint8_t           Diac_ScanTickNmb;
 static uint8_t           Diac_ChanToScan;
 static uint8_t           Diac_SubChanForTick[DIAC_SCAN_TICK_NMB];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function Initializes the DIOD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void DIAC_Init(void)
{
  /* Init Private data */
  DIAC_Channel_t    chan;
  DIAC_Thresholds_t thres;
  DIAC_Vref_t       refV;

  for (chan = (DIAC_Channel_t)0U; chan < DIAC_HDL_MAX; chan++)
  {
    Diac_PrivateData[chan].channelLevel = DIAC_CfgTable[chan].INIT_VALUE;
    Diac_PrivateData[chan].functionState = CTRL_ENABLE;
  }

  for (thres = (DIAC_Thresholds_t)0U; thres < DIAC_THRES_MAX; thres++)
  {
    Diac_ThresLevel[thres] = DIAC_ThresTable[thres].INIT_VALUE;
  }

  for (refV = (DIAC_Vref_t)0U; refV < DIAC_VREF_MAX; refV++)
  {
    Diac_VrefValue[refV] = 0U;
  }

  /* Set the first channel as current */
  Diac_CurrentThres = ((DIAC_Thresholds_t)0u);

  /* Init of the spreading variables */
  Diac_ChanToScan = DIAC_THRES_MAX;
  thres = (DIAC_Thresholds_t)0;
  for(Diac_ScanTickNmb = DIAC_SCAN_TICK_NMB; Diac_ScanTickNmb > 0U; Diac_ScanTickNmb--)
  {
    Diac_SubChanForTick[thres] = GBLS_SUB_CHAN_NMB(Diac_ChanToScan, Diac_ScanTickNmb);
    Diac_ChanToScan -= Diac_SubChanForTick[thres];
    thres++;
  }
  Diac_ScanTickNmb = 0u;
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief This function computes the discrete thresholds.
 * @param  none
 * @return non
 */
void DIAC_Mgm(void)
{
  uint16_t          adValueRef;
  uint16_t          rawAdValue;
  DIAC_Vref_t       refV;
  uint8_t           SubThres;
  uint8_t           subChanCheck;

  /* Aggiorno le tensioni di riferimento */
  for(refV = (DIAC_Vref_t)0U; refV < DIAC_VREF_MAX; refV++)
  {
    rawAdValue = ADCC_GetLastChnData(DIAC_VrefTable[refV].ADCC_VREF_CHAN); /* Raw Value */

    if (DIAC_VrefTable[refV].VREF_HW_GAIN != DIAC_NO_GAIN)
    {
      /* Riscalo la tensione di riferimento in base al suo partitore */
      Diac_VrefValue[refV] = (uint16_t)(((uint32_t)rawAdValue * (uint32_t)(DIAC_VrefTable[refV].VREF_HW_GAIN)) >> 10U);
    }
    else
    {
      /* Non ho bisogno di riscalare la tensione di riferimento */
      Diac_VrefValue[refV] = rawAdValue;
    }

    /* Sommo l'offset solo se evito underflow e se Vref > OFFSET */
    if (Diac_VrefValue[refV] > (uint16_t)abs(DIAC_VrefTable[refV].VREF_HW_OFFSET))
    {
      Diac_VrefValue[refV] = (uint16_t)(((uint16_t)Diac_VrefValue[refV]) + (uint16_t)DIAC_VrefTable[refV].VREF_HW_OFFSET);
    }
    else
    {
    }
  }
  
  subChanCheck = Diac_SubChanForTick[Diac_ScanTickNmb];

  /* Scan a subchannels number by the spreading strategy */
  for (SubThres = 0U; ((SubThres < subChanCheck) &&
                      (Diac_CurrentThres < DIAC_THRES_MAX)); SubThres++)
  {
    if (DIAC_ThresTable[Diac_CurrentThres].DIAC_VREF_HDL != DIAC_VREF_MAX)
    {
      adValueRef = Diac_VrefValue[DIAC_ThresTable[Diac_CurrentThres].DIAC_VREF_HDL]; /* Reference Value */
      /* Calcolo le soglie in funzione della tensione di riferimento */
      Diac_ThresLevel[Diac_CurrentThres] = (uint16_t)(((uint32_t)adValueRef * (uint32_t)(DIAC_ThresTable[Diac_CurrentThres].RATIO)) >> 10U) + DIAC_ThresTable[Diac_CurrentThres].THRES;
    }
    else
    {
      Diac_ThresLevel[Diac_CurrentThres] = DIAC_ThresTable[Diac_CurrentThres].THRES;
    }

    /* Update current threshold num */
    Diac_CurrentThres++;
  }

  /* Reinit current channel */
  if( Diac_CurrentThres >= DIAC_THRES_MAX )
  {
    Diac_CurrentThres = ((DIAC_Thresholds_t)0u);
  }

  /* Update spreading variables */
  if (Diac_ScanTickNmb < (DIAC_SCAN_TICK_NMB-1U))
  {
    Diac_ScanTickNmb++;
  }
  else
  {
    Diac_ScanTickNmb = 0u;
  }
}

/**
 * @brief This function returns the level of requested input.
 * @param chan the requested channel
 * @return electrical level.
 * @note  It must be called only one time at the system init.
 */
DRVD_Level_t DIAC_GetLevel(DIAC_Channel_t chan)
{
  uint16_t         adValue;
  DIAC_CfgTable_t  PtrCfgTable;

  PtrCfgTable = DIAC_CfgTable[chan];

  if (Diac_PrivateData[chan].functionState == CTRL_ENABLE)
  {
    adValue = ADCC_GetLastChnData(PtrCfgTable.ADCC_CHAN); /* Row Value */

    if (PtrCfgTable.MULTI_LEVEL_MODE == FALSE)
    {
      if(adValue > Diac_ThresLevel[PtrCfgTable.THRES_HIGH_HDL])
      {
        Diac_PrivateData[chan].channelLevel = L_HIGH;
      }
      else if (adValue < Diac_ThresLevel[PtrCfgTable.THRES_LOW_HDL])
      {
        Diac_PrivateData[chan].channelLevel = L_LOW;
      }
      else
      {
      }
    }
    else
    {
      if(adValue > Diac_ThresLevel[PtrCfgTable.THRES_HIGH_HDL])
      {
        Diac_PrivateData[chan].channelLevel = L_LOW;
      }
      else if (adValue < Diac_ThresLevel[PtrCfgTable.THRES_LOW_HDL])
      {
        Diac_PrivateData[chan].channelLevel = L_LOW;
      }
      else
      {
        Diac_PrivateData[chan].channelLevel = L_HIGH;
      }
    }
  }
  else
  {
    Diac_PrivateData[chan].channelLevel = DIAC_CfgTable[chan].INIT_VALUE;
  }
  /* Valore letto */
  return (Diac_PrivateData[chan].channelLevel);
}

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
void DIAC_EnableDisable (DIAC_Channel_t hdl, CTRL_EnSts_t state)
{
  Diac_PrivateData[hdl].functionState = state;
}

#endif /* __DIAC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

