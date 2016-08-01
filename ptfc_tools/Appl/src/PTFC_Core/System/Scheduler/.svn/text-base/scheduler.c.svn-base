#define SCHEDULER_GLOBALS

#include "MCAL_if.h"

#include "scheduler.h"
#include "SCHDS_config.h"
#include "TASK_if.h"

/* ======================    Local variables   ============================ */
#if defined __CPU_LOAD_MONITOR__
static u32 idleTimer;  // Misura tempo di idle della CPU.
static volatile bool schedulerTimerTickExecuted;
#endif

/* ======================    global variables   ============================ */
schedulerTaskReqStruct      schedulerTaskReq;
schedulerTaskOverrStruct    schedulerTaskOverr;
strSchedBackgroundTaskReq   strSCHED_BackgroundTaskReq;


static void SchedulerUpdateBackgroundTaskReq(void);


/**
 * Description: Initializes the data structures of the scheduler.
 *
 * Argument(s): None
 *
 * Return(s):   None
 *
 * Note(s):     Must be called before any other function that uses the scheduler
 *
 */
void SchedulerInit(void) 
{
  schedulerTaskReq.slowTask = 0u;
  schedulerTaskReq.mediumTask = 0u;
  schedulerTaskReq.fastTask = 0u;
  schedulerTaskReq.backgroundTask = 0u;

  schedulerTaskOverr.slowTask = 0u;
  schedulerTaskOverr.mediumTask = 0u;
  schedulerTaskOverr.fastTask = 0u;
  schedulerTaskOverr.backgroundTask = 0u;

  strSCHED_BackgroundTaskReq.fastTask = 0u;
  strSCHED_BackgroundTaskReq.mediumTask = 0u;
  strSCHED_BackgroundTaskReq.slowTask = 0u;
#if defined __CPU_LOAD_MONITOR__
  TASK_CpuLoadAvg = 0u;
  TASK_CpuLoadPeak = 0u;
#endif
}

/**
 * Description: Starts the scheduler
 *
 * Argument(s): None
 *
 * Return(s):   None
 *
 * Note(s):     Must be called to start the scheduler
 *
 */
void SchedulerStart(void) 
{
  /* Start SchedulerTick timer */
  TAU0_Channel0_Start();
#ifdef FOREGROUND_TASK_ENABLED
  /* Start SchedulerForeground timer */
  TAU0_Channel1_Start();
#endif
}

/**
 * Description: SchedulerTick routine
 *              this is TimerXX interrupt service routine:
 *              here task request flags are set (see structure: "schedulerTaskReq") when task timers ("baseTimer") reach zero.
 *              according to task request flags:
 *              - foreground tasks will be executed in TimerXX Interval Interrupt routine
 *              - background tasks will be executed in main
 *
 * Argument(s): None
 *
 * Return(s):   None
 *
 * Note(s):     every time a task request flag is set the foreground task interrupt is enabled (function: "SLRS_FrgrndResumeTask()")
 *              otherwise the foreground task interrupt remain disabled (function: "SLRS_FrgrndSuspendTask()" called in foreground tasks
 *              interrupt routine)
 */
void SchedulerTick(void) 
{
  static uint16_t baseTimerBackground = TIMER_BACKGROUND;
#ifdef FOREGROUND_TASK_ENABLED
  static uint16_t baseTimerForegroundFast = TIMER_FOREGROUND_FAST;
  static uint16_t baseTimerForegroundMedium = TIMER_FOREGROUND_MEDIUM;
  static uint16_t baseTimerForegroundSlow = TIMER_FOREGROUND_SLOW;

  baseTimerForegroundFast--;
  if (0u == baseTimerForegroundFast) 
  {                    // Task Fast
    baseTimerForegroundFast = TIMER_FOREGROUND_FAST;        // Timer base time initialization
    if (schedulerTaskReq.fastTask != 0u) 
    {                  // Check for overrun error detection
        schedulerTaskOverr.fastTask = 1u;
    }
    schedulerTaskReq.fastTask = 1u;                         // Start time fast task
  }
  baseTimerForegroundMedium--;
  if (0u == baseTimerForegroundMedium)
  {                  // Task medium
    baseTimerForegroundMedium = TIMER_FOREGROUND_MEDIUM;    // Restart timer
    if (schedulerTaskReq.mediumTask != 0u) 
    {                // Check for overrun error detection
        schedulerTaskOverr.mediumTask = 1u;
    }
    schedulerTaskReq.mediumTask = 1u;                       // Start time medium task
  }
  baseTimerForegroundSlow--;
  if (0u == baseTimerForegroundSlow)
  {                    // Task Slow
    baseTimerForegroundSlow = TIMER_FOREGROUND_SLOW;        // Restart timer
    if (schedulerTaskReq.slowTask != 0u) 
    {                  // Check for overrun error detection
        schedulerTaskOverr.slowTask = 1u;
    }
    schedulerTaskReq.slowTask = 1u;                         // Start time slow task
  }
#endif // FOREGROUND_TASK_ENABLED

  baseTimerBackground--;

#if defined __CPU_LOAD_MONITOR__
  schedulerTimerTickExecuted = TRUE; //Tell to idle CPU function that tick timer interrupt was executed
#endif
  if (0u == baseTimerBackground)
  {                        // Background task
    baseTimerBackground = TIMER_BACKGROUND;     // Restart timer
    if (schedulerTaskReq.backgroundTask != 0u) 
    {            // Check for overrun error detection
        schedulerTaskOverr.backgroundTask = 1u;
    }
    SchedulerUpdateBackgroundTaskReq();
    schedulerTaskReq.backgroundTask = 1u;       // Start background task
  }
}

/**
 *
 */
void SchedulerForeground(void) 
{
#ifdef FOREGROUND_TASK_ENABLED
  if (1u == schedulerTaskReq.fastTask) 
  {              // Execution of fast time task
    TaskForegroundFast();
    schedulerTaskReq.fastTask = 0u;
  }

  if (1u == schedulerTaskReq.mediumTask) 
  {            // Execution of medium time task
    /* Insert here the medium time functions */
    TaskForegroundMedium();
    schedulerTaskReq.mediumTask = 0u;
  }
  
  if (1u == schedulerTaskReq.slowTask) 
  {              // Execution of slow time task
    /* Insert here the slow time functions */
    TaskForegroundSlow();
    schedulerTaskReq.slowTask = 0u;
  }
#endif /* end FOREGROUND_TASK_ENABLED */
}


/**
 *
 */
static void SchedulerUpdateBackgroundTaskReq(void)
{
  static uint16_t TimerBackgroundFast   = TIMER_BACKGROUND_FAST;
  static uint16_t TimerBackgroundMedium = TIMER_BACKGROUND_MEDIUM;
  static uint16_t TimerBackgroundSlow   = TIMER_BACKGROUND_SLOW;
#if defined __CPU_LOAD_MONITOR__
  static uint16_t TimerBackgroundCpuCalc = TIMER_BACKGROUND_CPU_CALC;
#endif

  TimerBackgroundFast--;
  if (0u == TimerBackgroundFast)
  {
    /* Executed every 1 ms */
    TimerBackgroundFast = TIMER_BACKGROUND_FAST;
    strSCHED_BackgroundTaskReq.fastTask = 1u;
  }

  TimerBackgroundMedium--;
  if (0u == TimerBackgroundMedium)
  {
    /* Executed every 5 ms */
    TimerBackgroundMedium = TIMER_BACKGROUND_MEDIUM;
    strSCHED_BackgroundTaskReq.mediumTask = 1u;
  }

  TimerBackgroundSlow--;
  if (0u == TimerBackgroundSlow)
  {
    /* Executed every 100 ms */
    TimerBackgroundSlow = TIMER_BACKGROUND_SLOW;
    strSCHED_BackgroundTaskReq.slowTask = 1u;
  }

#if defined __CPU_LOAD_MONITOR__
  TimerBackgroundCpuCalc--;
  if (0u == TimerBackgroundCpuCalc) 
  {
    /* Executed every 10 ms */
    TimerBackgroundCpuCalc = TIMER_BACKGROUND_CPU_CALC;
    strSCHED_BackgroundTaskReq.cpuCalcTask = 1u;
  }
#endif
}

/**
*
*/
#ifdef FOREGROUND_TASK_ENABLED
void SLRS_FrgrndResumeTask(void)
{
  /* Foreground task enable, interrupt enable */
  TAU0_Channel1_Start();
}

/**
 *
 */
void SLRS_FrgrndSuspendTask(void)
{
  /* Foreground task disable interrupt disable */
  TAU0_Channel1_Stop();
}
#endif // FOREGROUND_TASK_ENABLED

/**
*
*/
void SLRS_BckgrndResumeTask(void)
{
  /* Background tasks enable, interrupt enable */
  TAU0_Channel0_Start();
}

/**
 *
 */
void SLRS_BckgrndSuspendTask(void)
{
  /* Background task disable interrupt disable */
  TAU0_Channel0_Stop();
}

#if defined __CPU_LOAD_MONITOR__
/*
    - chiamata ogni TIMER_BACKGROUND_CPU_CALC ms (*1000U: trasforma in µs).
    - accumula i valori di idleTimer misurati da SchedulerIdleCPU(), dopo azzera la variabile.
    - calcola CPU load e salva valori di picco e media.

    Calcolo carico CPU istantaneo: un campione ogni TIMER_BACKGROUND_CPU_CALC ms.
    Calcolo CPU idle time  idleTime [µs]: idleTimer/(TICK_COMPARE_VALUE/TICK_PERIOD).

    Valore massimo teorico (0% CPU load) della variabile idleTime [µs]: (TIMER_BACKGROUND_CPU_CALC*1000U)

    CPU load average calculation period = TIMER_BACKGROUND_CPU_CALC*CPU_LOAD_AVG_SAMPLES (640ms)
    
    TASK_CpuLoadPeak     [0.1%] = (uint8_t)(cpuLoadPeak/(TIMER_BACKGROUND_CPU_CALC))
    TASK_CpuLoadAvg      [0.1%] = (uint8_t)(cpuLoadAverage/(TIMER_BACKGROUND_CPU_CALC))
*/
void SchedulerCalculateCPU(void)
{
    static u32 idleTimerMin = 0xFFFFFFFFUL;
    static u32 idleTimerSum;
    static u08 idleTimeSamples;
    
    u32 cpuLoadPeak;
    u32 cpuLoadAverage;
    u32 idle_time;

   idle_time = idleTimer;
   idleTimer = 0UL;

    if ((idle_time < idleTimerMin) || (TASK_CpuLoadPeak == 0U))// Aggiorna il valore di picco.
    {
        idleTimerMin = idle_time;   // Salva il valore minimo del tempo di CPU idle, per trovare il picco del carico CPU.

        cpuLoadPeak = (TIMER_BACKGROUND_CPU_CALC*1000U)-(idle_time/(TICK_COMPARE_VALUE/TIMER_TICK_US));
        TASK_CpuLoadPeak = (u16)(cpuLoadPeak/(TIMER_BACKGROUND_CPU_CALC));
    }

    idleTimerSum += idle_time;
    if (++idleTimeSamples == CPU_LOAD_AVG_SAMPLES)
    {
        idleTimeSamples = 0U;

        idle_time = idleTimerSum / CPU_LOAD_AVG_SAMPLES;
	idleTimerSum = 0UL;

        cpuLoadAverage = (TIMER_BACKGROUND_CPU_CALC*1000U)-(idle_time/(TICK_COMPARE_VALUE/TIMER_TICK_US));
        TASK_CpuLoadAvg = (u16)(cpuLoadAverage/(TIMER_BACKGROUND_CPU_CALC));
    }
}

void SchedulerIdleCPU(void)
{
/*
TIMER_TICK_COUNT: timer read buffer register, operates as counter.
In the interval timer mode, the 16-bit counter register (TCR) count operation is "Counting down".
*/
    u16 beginIdle;
    u16 endIdle;
    u08 *ptrTask;
    u08 *ptrBackTask;
    
    ptrTask = (u08*)&schedulerTaskReq;
    ptrBackTask = (u08*)&strSCHED_BackgroundTaskReq;
        
    if ((*ptrTask == 0U) && (*ptrBackTask == 0U))	// Non ci sono richieste di esecuzione task attive e non ci sono task di sistema in esecuzione
	 													// (altrimenti la CPU starebbe eseguendo la funzione systemTasks() in interrupt).
    {
        schedulerTimerTickExecuted = FALSE;
        
        beginIdle = TIMER_TICK_COUNT;		// Legge tick subito prima di passare in HALT mode (begin idle).
        __halt();	
        endIdle = TIMER_TICK_COUNT;		// Legge tick appena uscito da HALT mode (end idle)..
        // Calcola il tempo passato in HALT mode e accumula il valore, usato per calcolo CPU load: vedi calculateCPU().
        if (schedulerTimerTickExecuted)
        {
            // Tick timer interrupt occurred.
            // Uscito da HALT mode per interrupt di tick timer: considerare solo beginIdle.

//			idleTimer += TICK_COMPARE_VALUE - beginIdle;// up counter
			idleTimer += beginIdle;// down counter
        }
        else
        {
          // other interrupt occurred.
//			idleTimer += endIdle - beginIdle;// up counter
			idleTimer += beginIdle - endIdle;// down counter
        }
    }
}
#endif

/*_____ E N D _____ (Scheduler.c) ____________________________________________*/
