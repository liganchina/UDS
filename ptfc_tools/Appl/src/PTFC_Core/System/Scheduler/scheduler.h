#ifndef __SCHEDULER_H
#define __SCHEDULER_H

/* ============================================================================ **
**                           B I T R O N    S p A                               **
** ============================================================================ **
**                      +++++++++++++++++++++++++++++                           **
**           Modulo:    +    scheduler.h            +                           **
**                      +++++++++++++++++++++++++++++                           **
**                                                                              **
**   Progetto :         MSM model X                                             **
**                                                                              **
**                                                                              **
** ============================================================================ */

#include "typedefs.h"
#include "scheduler_if.h"

#ifdef  SCHEDULER_GLOBALS
#define SCHEDULER_EXT
#else
#define SCHEDULER_EXT extern
#endif

#define TIMER_FOREGROUND_FAST       ((uint16_t)((TIMER_TICK_FOREGROUND_FAST)/TIMER_TICK_US))            /* <500 us */
#define TIMER_FOREGROUND_MEDIUM     ((uint16_t)((TIMER_TICK_FOREGROUND_MEDIUM)/TIMER_TICK_US))          /* <  5 ms */
#define TIMER_FOREGROUND_SLOW       ((uint16_t)((TIMER_TICK_FOREGROUND_SLOW)/TIMER_TICK_US))            /* < 10 ms */

#define TIMER_BACKGROUND            ((uint16_t)((TIMER_TICK_BACKGROUND)/TIMER_TICK_US))               		 											/*   1 ms */
#define TIMER_BACKGROUND_FAST       ((uint16_t)((TIMER_TICK_BACKGROUND_FAST)/((uint32_t)(TIMER_BACKGROUND * TIMER_TICK_US))))   /*   1 ms */
#define TIMER_BACKGROUND_MEDIUM     ((uint16_t)((TIMER_TICK_BACKGROUND_MEDIUM)/((uint32_t)(TIMER_BACKGROUND * TIMER_TICK_US)))) /*   5 ms */
#define TIMER_BACKGROUND_SLOW       ((uint32_t)((TIMER_TICK_BACKGROUND_SLOW)/((uint32_t)(TIMER_BACKGROUND * TIMER_TICK_US)))) 	/* 100 ms */
#define TIMER_BACKGROUND_MEDIUM_SL  (TIMER_BACKGROUND_MEDIUM * 2u)

#if defined __CPU_LOAD_MONITOR__
#define TIMER_BACKGROUND_CPU_CALC   ((uint16_t)((10000u)/((uint32_t)(TIMER_BACKGROUND * TIMER_TICK_US))))    /*     10 ms */
#define CPU_LOAD_AVG_SAMPLES        64u //number of samples to calculate CPU average, 64*10 = 640 ms average, use power of 2 to simplify the calculation
#define TIMER_TICK_COUNT            (TCR00)         // Timer tick count register
#define TICK_COMPARE_VALUE	        (TDR00+1U)	
#endif

/* Convert time in ms to tick (5ms  time base) */
#define CVT_MS_2_TICK5(x)    ((u16)((u16)(x) / TIMER_BACKGROUND_MEDIUM))
/* Convert time in ms to tick (10ms time base) */
#define CVT_MS_2_TICK10(x)   ((u16)((u16)(x) / TIMER_BACKGROUND_MEDIUM_SL))

/* ========================       struct      ============================== */
typedef struct schedulerTaskReq_s
{
  uint8_t fastTask          :1;   /* foreground @   1 ms */
  uint8_t mediumTask        :1;   /* foreground @   5 ms */
  uint8_t slowTask          :1;   /* foreground @  10 ms */
  uint8_t backgroundTask    :1;   /* background @  10 ms */
  uint8_t spare             :4;   /* Spare field */
}schedulerTaskReqStruct;

typedef struct schedulerTaskOverr_s
{
  uint8_t slowTask          :1;
  uint8_t mediumTask        :1;
  uint8_t fastTask          :1;
  uint8_t backgroundTask    :1;
  uint8_t spare             :4;   /* Spare field */
}schedulerTaskOverrStruct;

typedef struct SchedBackgroundTaskReq_s
{
  uint8_t fastTask          :1;   /* background @     1 ms */
  uint8_t mediumTask        :1;   /* background @     5 ms */
  uint8_t slowTask 	        :1;   /* background @   100 ms */
#if defined __CPU_LOAD_MONITOR__
  uint8_t cpuCalcTask 	    :1;   /* background @    10 ms */
  uint8_t spare             :4;   /* Spare field */
#else
  uint8_t spare             :5;   /* Spare field */
#endif
}strSchedBackgroundTaskReq;


//typedef struct {
//    uint8_t TestRAM             :1; // primo byte
//    uint8_t TestFlash           :1;
//    uint8_t calculateCPU        :1;
//    uint8_t Timer500            :1;
//    uint8_t ADC                 :1;
//    uint8_t INVirTask           :1;
//    uint8_t ScrmTask            :1;
//    uint8_t OutpTask            :1; // primo byte
//    uint8_t OutpTaskSlope       :1; // secondo byte
//    uint8_t ScrmDiagTask        :1;
//    uint8_t ScrmDiagCurrTask    :1;
//    uint8_t spare3              :1;
//    uint8_t spare4              :1;
//    uint8_t spare5              :1;
//    uint8_t spare6              :1;
//    uint8_t spare7              :1; // secondo byte
//}
//Task;


//SCHEDULER_EXT __saddr Task Run;


#if defined IDLE_CPU
  SCHEDULER_EXT u32 CpuActiveTime; // misura tempo di CPU attiva
  SCHEDULER_EXT u16 cpuLoadSample;
  SCHEDULER_EXT u16 cpuLoadPeak;
  SCHEDULER_EXT u32 cpuLoadAverage;
#endif


/* ======================    global variables   ============================ */
SCHEDULER_EXT schedulerTaskReqStruct       schedulerTaskReq;
SCHEDULER_EXT schedulerTaskOverrStruct     schedulerTaskOverr;
SCHEDULER_EXT strSchedBackgroundTaskReq    strSCHED_BackgroundTaskReq;


/* =====================     function declare      ========================= */
SCHEDULER_EXT void SchedulerTick(void);
SCHEDULER_EXT void SchedulerForeground(void);
SCHEDULER_EXT void SchedulerInit(void);
SCHEDULER_EXT void SchedulerStart(void);

#if defined __CPU_LOAD_MONITOR__
SCHEDULER_EXT void SchedulerCalculateCPU(void);
SCHEDULER_EXT void SchedulerIdleCPU(void);
#endif

// -----------------------------------------------------------------------------


#endif  // __SCHEDULER_H
