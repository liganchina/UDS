/**
 * @file IPOC.c
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief Core File of IPOC Driver. This driver is able to convert
 *  an analog input in a digital one, in according with the configured
 *  voltage thresholds.
 *
 * @see www.Bitron.net
 */


#define IPOC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "IPOC.h"
#include "IPOC_config.h"
#include "stdlib.h"       /* Funzione abs() */

#ifdef __IPOC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct
{
  int16_t*               currPosPtr;
  IPOC_Stall_t           stallSts;
  IPOC_DirectionCount_t  moveDirection;
  IPOC_DirectionCount_t  oldDirection;
  uint16_t               sampleMax;
  uint16_t               sampleMin;
  DRVD_Level_t           level;
  bool_t                 risingEdge   :1;
  bool_t                 fallingEdge  :1;
  bool_t                 updateMinMax :1;
  uint16_t               decelerationTime;
  uint16_t               sampleMinPrev;
  uint16_t               sampleMaxPrev;
}Ipoc_PrivateData_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

static Ipoc_PrivateData_t   Ipoc_PrivateData[IPOC_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/**
 * @brief Performs the move,e
 * @return void
 * @note  It must be called only one time at the system init.
 */
static void Ipoc_EdgeCount(IPOC_Channel_t chan);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function Initializes the DIOD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void IPOC_Init(void)
{
  /* Init Private data */
  u08 chan;

  for (chan = 0U; chan < IPOC_HDL_MAX; chan++)
  {
    Ipoc_PrivateData[chan].currPosPtr       = NULL;           /*  s16                    */
    Ipoc_PrivateData[chan].stallSts         = IPOC_NO_STALL;  /*  bool                   */
    Ipoc_PrivateData[chan].moveDirection    = IPOC_CMD_IDLE;  /*  IPOC_DirectionCount_t  */
    Ipoc_PrivateData[chan].oldDirection     = IPOC_CMD_IDLE;  /*  IPOC_DirectionCount_t  */
    Ipoc_PrivateData[chan].sampleMax        = 0U;             /*  uint16_t               */
    Ipoc_PrivateData[chan].sampleMin        = 0xFFFFU;        /*  uint16_t               */
    Ipoc_PrivateData[chan].level            = L_LOW;          /*  DRVD_Level_t           */
    Ipoc_PrivateData[chan].risingEdge       = FALSE;          /*  bool                   */
    Ipoc_PrivateData[chan].fallingEdge      = FALSE;          /*  bool                   */
    Ipoc_PrivateData[chan].decelerationTime = 0U;             /*  uint16_t               */
    Ipoc_PrivateData[chan].updateMinMax     = FALSE;          /*  bool                   */
    Ipoc_PrivateData[chan].sampleMaxPrev    = 0U;             /*  uint16_t               */
    Ipoc_PrivateData[chan].sampleMinPrev    = 0xFFFFU;        /*  uint16_t               */
  }
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief Set the current position of the selected channel. It should be used at
 * @brief power on on in case of pulse compensation.
 * @param chan the requested channel
 * @return
 */
void IPOC_SetCounter(IPOC_Channel_t chan, int16_t *counterPtr)
{
  Ipoc_PrivateData[chan].currPosPtr = counterPtr;
}

/**
 * @brief Get the position of the selected channel
 * @param chan the requested channel
 * @return int16_t
 */
int16_t IPOC_GetPosition(IPOC_Channel_t chan)
{
  return (*(Ipoc_PrivateData[chan].currPosPtr));
}

/**
 * @brief Set the position of the selected channel
 * @param chan the requested channel
 * @return CTRL_ResSts_t
 * @retval MS_OK Position set correctly
 * @retval MS_NOT_OK Counter not configured
 */
CTRL_ResSts_t IPOC_SetPosition(IPOC_Channel_t chan, int16_t position)
{
  CTRL_ResSts_t valueReturn;

  if(Ipoc_PrivateData[chan].currPosPtr != NULL)
  {
    *Ipoc_PrivateData[chan].currPosPtr = position;
    valueReturn = CTRL_OK;
  }
  else
  {
    valueReturn = CTRL_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief Get if the selected channel is in stall condition
 * @param chan the requested channel
 * @return boolean
 * @retval TRUE
 * @retval FALSE
 */
IPOC_Stall_t IPOC_GetStallStatus(IPOC_Channel_t chan)
{
  return Ipoc_PrivateData[chan].stallSts;
}

/**
 * @brief Set the selected channel is in stall condition.
 * @param chan the requested channel
 * @return none
 */
void IPOC_SetStallStatus(IPOC_Channel_t chan, IPOC_Stall_t stallSts)
{
  Ipoc_PrivateData[chan].stallSts = stallSts;
}

/**
 * @brief Get the counter direction of selected channel
 * @param chan the requested channel
 * @return IPOC_DirectionCount_t
 * @retval IPOC_CMD_IDLE
 * @retval IPOC_CMD_UP_FW
 * @retval IPOC_CMD_DOWN_BW
 */
IPOC_DirectionCount_t IPOC_GetDirection(IPOC_Channel_t chan)
{
  return Ipoc_PrivateData[chan].moveDirection;
}

/**
 * @brief Set the counter direction of selected channel
 * @param chan the requested channel
 * @return none
 */
void IPOC_SetDirection(IPOC_Channel_t chan, IPOC_DirectionCount_t moveDirection)
{
  Ipoc_PrivateData[chan].moveDirection = moveDirection;
}

/**
 * @brief This function manages pulse counters. It have to be called periodically considering the
 * @brief maximum frequency of input pulse signal.
 * @param chan the requested channel, moveDirection movement direction
 * @return none
 */
void IPOC_CounterMgm(void)
{
  uint16_t       ad_Value;
  uint16_t       adHallThresold;
  uint16_t       adHallRange;
  bool           enableCount;
  IPOC_Channel_t chan;

  for (chan = (IPOC_Channel_t)0; chan < IPOC_HDL_MAX; chan++)
  {
    if (Ipoc_PrivateData[chan].moveDirection != IPOC_CMD_IDLE)
    {
      enableCount = TRUE;
      Ipoc_PrivateData[chan].oldDirection     = Ipoc_PrivateData[chan].moveDirection;
      Ipoc_PrivateData[chan].decelerationTime = IPOC_DECELERATION_TIME; // normal deceleration time
    }
    else
    {
      if (Ipoc_PrivateData[chan].decelerationTime > 0U)
      {
        Ipoc_PrivateData[chan].decelerationTime -= IPOC_TICK_TIME;
        if (Ipoc_PrivateData[chan].decelerationTime == 0U)
        {
          enableCount = FALSE;
          Ipoc_PrivateData[chan].oldDirection = Ipoc_PrivateData[chan].moveDirection;
          Ipoc_PrivateData[chan].sampleMax = 0U;
          Ipoc_PrivateData[chan].sampleMaxPrev = 0U;
          Ipoc_PrivateData[chan].sampleMin = 0xFFFFU;
          Ipoc_PrivateData[chan].sampleMinPrev = 0xFFFFU;
          Ipoc_PrivateData[chan].updateMinMax = FALSE;
        }
        else
        {
          enableCount = TRUE;
        }
      }
      else
      {
        enableCount = FALSE;
      }
    }

    if (enableCount == TRUE)
    {
      ad_Value = ADCC_GetLastChnData(IPOC_CfgTable[chan].AD_SENS_CHAN);
      
      if (ad_Value > Ipoc_PrivateData[chan].sampleMax)
      { // Update maximum
        adHallRange = (uint16_t)abs((int)Ipoc_PrivateData[chan].sampleMaxPrev - (int)ad_Value);
        if ((adHallRange < IPOC_MAX_DIFF_PULSE) && (ad_Value < IPOC_DIAG_THRES_UP))
        {
          if ((Ipoc_PrivateData[chan].updateMinMax != FALSE)
              && ((ad_Value - Ipoc_PrivateData[chan].sampleMax) > IPOC_MIN_APPLITUDE))
          { // Some pulses are already recognized and there is a DC offset change
            Ipoc_PrivateData[chan].sampleMax = 0U;
            Ipoc_PrivateData[chan].sampleMin = 0xFFFFU;
            Ipoc_PrivateData[chan].sampleMaxPrev = 0U;
            Ipoc_PrivateData[chan].sampleMinPrev = 0xFFFFU;
            Ipoc_PrivateData[chan].updateMinMax = FALSE;
            Ipoc_EdgeCount(chan);
          }
          else
          { // Update maximum
            Ipoc_PrivateData[chan].sampleMax = ad_Value;
          }
        }
        Ipoc_PrivateData[chan].sampleMaxPrev = ad_Value;
      }

      if (ad_Value < Ipoc_PrivateData[chan].sampleMin)
      { // Update minimum
        adHallRange = (uint16_t)abs((int)Ipoc_PrivateData[chan].sampleMinPrev - (int)ad_Value);
        if ((adHallRange < IPOC_MAX_DIFF_PULSE) && (ad_Value > IPOC_DIAG_THRES_DOWN))
        {
          if ((Ipoc_PrivateData[chan].updateMinMax != FALSE)
              && ((Ipoc_PrivateData[chan].sampleMin - ad_Value) > IPOC_MIN_APPLITUDE))
          { // Some pulses are already recognized and there is a DC offset change
            Ipoc_PrivateData[chan].sampleMax = 0U;
            Ipoc_PrivateData[chan].sampleMin = 0xFFFFU;
            Ipoc_PrivateData[chan].sampleMaxPrev = 0U;
            Ipoc_PrivateData[chan].sampleMinPrev = 0xFFFFU;
            Ipoc_PrivateData[chan].updateMinMax = FALSE;
            Ipoc_EdgeCount(chan);
          }
          else
          { // Update minimum
            Ipoc_PrivateData[chan].sampleMin = ad_Value;
          }
        }
        Ipoc_PrivateData[chan].sampleMinPrev = ad_Value;
      }

      // Evaluates the threshold
      adHallRange = Ipoc_PrivateData[chan].sampleMax - Ipoc_PrivateData[chan].sampleMin;
      adHallThresold = Ipoc_PrivateData[chan].sampleMin + (adHallRange >> 1U);

      if ((adHallRange > IPOC_MIN_APPLITUDE)
          && (Ipoc_PrivateData[chan].sampleMax > Ipoc_PrivateData[chan].sampleMin))
      {
        Ipoc_PrivateData[chan].updateMinMax = TRUE; // Set the flag to recognize the DC offset change

        if (ad_Value > adHallThresold)
        { // Sensor to 1
          if (Ipoc_PrivateData[chan].level != L_LOW)
          { // Rising edge second sample
            if (Ipoc_PrivateData[chan].risingEdge == FALSE)
            { // Pulse not yet counted
              Ipoc_PrivateData[chan].risingEdge = TRUE;
              Ipoc_PrivateData[chan].fallingEdge = FALSE;
              Ipoc_EdgeCount(chan);
            }
          }
          else
          { // Rising edge first sample
            Ipoc_PrivateData[chan].level = L_HIGH;
          }
        }
        else
        { // sensor to 0
          if (Ipoc_PrivateData[chan].level == L_LOW)
          { // Falling edge second sample
            if (Ipoc_PrivateData[chan].fallingEdge == FALSE)
            { // Pulse not yet counted
              Ipoc_PrivateData[chan].fallingEdge = TRUE;
              Ipoc_PrivateData[chan].risingEdge = FALSE;
              Ipoc_EdgeCount(chan);
            }
            else
            {
            }
          }
          else
          { // Falling edge first sample
            Ipoc_PrivateData[chan].level = L_LOW;
          }
        }
      }
    }
    else
    {
    }
  }
}


/**
 * @brief Performs the update of current position counters.
 * @param chan current channel.
 * @return void
  */
static void Ipoc_EdgeCount(IPOC_Channel_t chan)
{
  if (Ipoc_PrivateData[chan].currPosPtr != NULL)
  {
    if (Ipoc_PrivateData[chan].oldDirection == IPOC_CMD_UP_FW)
    {
      if (Ipoc_PrivateData[chan].stallSts == IPOC_STALL_UP_FW)
      {
        if ((*Ipoc_PrivateData[chan].currPosPtr) > IPOC_MIN_PULSE_CNT)
        {
          (*Ipoc_PrivateData[chan].currPosPtr)--;
        }
        else
        {
        }
      }
      else
      {
        if ((*Ipoc_PrivateData[chan].currPosPtr) < IPOC_MAX_PULSE_CNT)
        {
          (*Ipoc_PrivateData[chan].currPosPtr)++;
        }
        else
        {
        }
      }
    }
    else if(Ipoc_PrivateData[chan].oldDirection == IPOC_CMD_DOWN_BW)
    {
      if (Ipoc_PrivateData[chan].stallSts == IPOC_STALL_DOWN_BW)
      {
        if((*Ipoc_PrivateData[chan].currPosPtr) < IPOC_MAX_PULSE_CNT)
        {
          (*Ipoc_PrivateData[chan].currPosPtr)++;
        }
        else
        {
        }
      }
      else
      {
        if((*Ipoc_PrivateData[chan].currPosPtr) > IPOC_MIN_PULSE_CNT)
        {
          (*Ipoc_PrivateData[chan].currPosPtr)--;
        }
        else
        {
        }
      }
    }
    else
    {
      /* Direction unknown */
    }
  }
  else
  {
    /* Counter not valid */
  }
}


#endif /* __IPOC_IS_PRESENT__ */

/*______ E N D _____ (IPOC.c) _________________________________________*/

