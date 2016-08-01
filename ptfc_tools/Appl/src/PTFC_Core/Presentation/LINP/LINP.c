/**
 * @file LINP.c
 * @brief LIN presentation: source code of LIN module for presentation layer. 
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/

#define LINP_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINP.h"
#include "LINP_if.h"
#include "LINP_config.h"

/* Module inhibition filter */
#ifdef __LINP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

static Linp_Status_t Linp_Status;   /* State of LINP */

static uint8_t Linp_IndSt;          /* Index of current schedule table */
static uint8_t Linp_IndFr;          /* Index of current frame */
static uint8_t Linp_TimerSlot;      /* Counter for current time slot */
static uint16_t Linp_StTotalTime;   /* Total time for current schedule table */

static LINC_MessageMap_t Linp_PrevId; /* Used for set error in current frame */
static uint8_t Linp_PrevIndFr;      /* Index of current frame */

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* Reset index of schedule table and frame */
static void Linp_ResetFrameStart(void);

/* Calculate total time for current schedule table */
static uint16_t Linp_CalculateTableTime(void);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function Initializes the LINP driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void LINP_Init(void)
{
  /* Initializing of global variables */
  Linp_Status = LINP_SLEEP;
  Linp_TimerSlot = 0u;
  /* Reset index of schedule table and frame*/
  Linp_ResetFrameStart();  
}

/**
 * @brief Activates network transmitting a "wake up" command
 * @return void
 * @note 
 */
void LINP_WakeUp(uint8_t chn_hnd)
{
  /* Set LINC, LTMS and UARTD in IDLE status and send WakeUp signal */
  LINC_WakeUp(chn_hnd); 
}

/**
 * @brief Send network to sleep transmitting a "go to sleep" command
 * @return void
 * @note 
 */
void LINP_GoToSleep(uint8_t chn_hnd)
{
  /* Change LINP status */
  Linp_Status = LINP_SLEEP; 
  
  /* Send "go to sleep" on bus and manage LINC, UARTD and LTMS layers */
  if (UARTD_GOTOSLEEP_MODE == UARTD_RECEPTION_TASK_ON)
  {
    LINC_GoToSleep(chn_hnd);
  }  
  
}

/**
 * @brief Sends the message header and calculates for each frame the slot time
 * @return void
 * @note This function is called every 10 ms
 */
void LINP_SchedulerTick(uint8_t chn_hnd)
{
  /* Support variables */
  LINC_MessageMap_t Linp_CurrPid;   /* Used for manage current frame */

  if(Linp_TimerSlot == 0u)
  {               
    if(Linp_Status == LINP_IDLE)
    {                 
      /* Normale mode active */
      /* Retrieve Pid */
      Linp_CurrPid = Linp_SchTab[Linp_IndSt].Table[Linp_IndFr].LinId;
      
      /* Check LINC Status for set generic error in a previous frame if it
        don't detect from LINC_ReceptionTask*/
      if(LINC_GetStatus(chn_hnd) == LINC_ERROR)
      {
        /* Set error on frame if not a short circuit error */ 
        if((LINC_GetDiag(chn_hnd) != UARTD_SHORT_CIRCUIT_LOW) &&
            (LINC_GetDiag(chn_hnd) != UARTD_SHORT_CIRCUIT_HIGH))
        {
          /* Set error from frame Id */
          LINC_SetMessageError(Linp_PrevId);
        }    
      }

      /* Check FrameError to manage the Timeout of LINP (All Error type) */
      if(LINC_GetMessageStatus(Linp_PrevId) != LINC_NO_FAULT)
      { 
        /* Check ErrorFrameCkbEnable to call a recovery only one time */
        if(*Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].ErrorFrameCkbEnable == TRUE)
        {
          /* Increase timer if ErrorFrame is occurred */
          *Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].TimeOutCounterMs += Linp_StTotalTime;
          
          /* Checks whether the timer has expired */
          if(*Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].TimeOutCounterMs >= 
              Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].TimeOutMs)
          {
            /* Call APPL callback for current frame */
            if (Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].ErrorFrameCbk != NULL)
            {
              Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].ErrorFrameCbk();
            }            
            /* Disable recovery callback enable */
            *Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].ErrorFrameCkbEnable = FALSE;
            /* Reset timer */
            *Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].TimeOutCounterMs = 0;
          }        
        }      
      }
      else
      {
        /* Reset counter for error NoResponseError in current frame */ 
        *Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].TimeOutCounterMs = 0;
        
        /* Reset recovery callback enable */
        *Linp_SchTab[Linp_IndSt].Table[Linp_PrevIndFr].ErrorFrameCkbEnable = TRUE;
      }           
        
      /* Sending header on LIN bus */
      LINC_PutHeader(chn_hnd, Linp_CurrPid);
      
      /* Save previous Pid */
      Linp_PrevId = Linp_CurrPid;
      Linp_PrevIndFr = Linp_IndFr;
      
      /* Set slot time for frame */
      Linp_TimerSlot = Linp_SchTab[Linp_IndSt].Table[Linp_IndFr].SlotTimeMs / LINP_TIME_TICK;
      if(Linp_TimerSlot > 0)
      {
        Linp_TimerSlot--;
      }
      /* Increase message index */
      Linp_IndFr++;
      
      /* Check end of table */
      if (Linp_IndFr == Linp_SchTab[Linp_IndSt].Len)
      {
        /* Reset message index */
        Linp_IndFr = 0;      
      }      
      
    }
    else
    {
      /* Sleep mode: return in IDLE if WakeUp signal is send or received*/
      if(LINC_GetStatus(chn_hnd) == LINC_IDLE)
      {        
        /* Set a Idle status for start the transmittion of header on bus */
        Linp_Status = LINP_IDLE;
        /* Reset index of schedule table and frame */
        Linp_ResetFrameStart();
      }       
    }               
  }
  else
  {
    /* Decrements the schedule time slot */
    Linp_TimerSlot--;
  }
}

/**
 * @brief Change the schedule table index
 * @return void
 * @note
 */
void LINP_SetSchedulerTable(uint8_t scheduleTableNum)
{
  /* Change current schedule table used */
  Linp_Status = LINP_IDLE;
  Linp_IndSt = scheduleTableNum;
  Linp_IndFr = 0u;  
  Linp_TimerSlot = 0u;
  Linp_StTotalTime = Linp_CalculateTableTime();
}

/**
 * @brief Return index of schedule table
 * @return uint8_t
 * @note 
 */
uint8_t LINP_GetSchedulerTable(void)
{
  /* Return index of schedule table on run*/
  return Linp_IndSt;
}


/* Private functions */

/**
 * @brief Reset counter for index of schedule table and frame 
 * @param 
 * @return 
 */
static void Linp_ResetFrameStart(void)
{
  /* Reset variables */
  Linp_IndSt = 0u;
  Linp_IndFr = 0u;
  Linp_PrevId = LINC_CommandGTS; /* Insert a not valid PID value */ 
  Linp_PrevIndFr = 0xFF;        /* Insert a nor valid index of frame */
  Linp_StTotalTime = Linp_CalculateTableTime(); /* Totale time for current ST */
}

/**
 * @brief Calculate total time for current schedule table
 * @param 
 * @return 
 */

static uint16_t Linp_CalculateTableTime(void)
{
  /* Local variables */
  uint8_t index = 0u;
  uint16_t totalScheduleTime = 0u;
  
  /* Calculate total time for current schedule table */
  while (index < Linp_SchTab[Linp_IndSt].Len)
  {
    /* Increase total time calculate */
    totalScheduleTime += Linp_SchTab[Linp_IndSt].Table[index].SlotTimeMs;
    /* Increase index */
    index ++;
  }

  return totalScheduleTime;
}

#endif /* end __LINP_IS_PRESENT__ */

/*______ E N D _____ (LINP.c) ________________________________________________*/
