/* ============================================================================ **
**                           B I T R O N    S p A                               **
** ============================================================================ **
**                      +++++++++++++++++++++++++++++                           **
**           Modulo:    +    main.c                 +                           **
**                      +++++++++++++++++++++++++++++                           **
**                                                                              **
**   Progetto :          IVECO_ALM                                              **
**                                                                              **
    Microprocessore:

78K0R/Fx3:
    FE3 - uPD78F1837 (80 pin, 16KB RAM, 256KB code Flash,  KB data Flash)
    Tempo ciclo macchina = durata istruzione __no_operation()/NOP: 1 clock.
    One instruction clock cycle is one cycle of the CPU clock (fCLK)
    selected by the system clock control register (CKC).
        fCLK= 8 MHz:125 ns
        fCLK=16 MHz:62,5 ns
        fCLK=20 MHz:50 ns
        fCLK=24 MHz (external clock 8 or 16 MHz with PLL_ON): 41,67 ns
**                                                                              **
**   Descrizione :                                                              **
**     Programma principale                                                     **
**                                                                              **
**                                                                              **
**   Requisiti :                                                                **
**                                                                              **
**                                                                              **
**   Procedure Globali :                                                        **
**     main();                                                                  **
**                                                                              **
** ============================================================================ */

#include "global.h"
#include "TASK_if.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/

/*
  Se si utilizza on-chip debugger (MINICUBE2) verificare eventuali restrizioni 
  sulla mappa di memoria Flash/RAM.
*/
//---------------------------------------------------------------------------------
// Security ID CODE: for OCD on-chip debugging only / 78K CPU module + QB-MINI2
//---------------------------------------------------------------------------------

#ifdef __DEBUG__
  /* Set option bytes */
  #pragma location = "OPTBYTE"
  __root const UCHAR opbyte0 = 0x77U;
  #pragma location = "OPTBYTE"
  __root const UCHAR opbyte1 = 0xFDU;
  #pragma location = "OPTBYTE"
  __root const UCHAR opbyte2 = 0xFFU;
  #pragma location = "OPTBYTE"
  #if defined __ON_CHIP_DEBUG__
    __root const UCHAR opbyte3 = 0x85U;
  #else
    __root const UCHAR opbyte3 = 0x04U;
  #endif
  
  #if defined __ON_CHIP_DEBUG__
    #pragma location = "SECUID"
    static __root __far const u08 SecurityIDCode[10] = 
      {0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU};
  #endif /* end __ON_CHIP_DEBUG__ */
#endif /* end __DEBUG__ */

#if defined IDLE_CPU
  typedef struct cpuLoadStruct_s
  {
    u16 ProceedToCalculate   :1;
    u16 LoadLimitFlag        :1;
    u16 Timer2StartFlag      :1;
    u16 IdleFirstTimeFlag    :1;
    u16 StartCalculateFlag   :1;
    u16 spare5               :1;
    u16 spare6               :1;
    u16 spare7               :1;
  
  }cpuLoadStruct_t;

  static void idleCPU(void);
  static void calculateCPU(void);

  static cpuLoadStruct_t CpuMngFlag;
  u32 beginCpu, endCpu, resultCpu;
#endif

/* ======================    Prototypies   ============================ */
static void mainLoop(void);
#if defined IDLE_CPU
  static void idleCPU(void);
  void calculateCPU(void);

  cpuLoadStruct_t CpuMngFlag;
  u32 beginCpu, endCpu, resultCpu;
#endif


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is main routine.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
void main(void)
{
  /* Disable all interrupts */  
  DI();
  /* Init for all modules according to Low Power Managment */ 
  LPMS_Init();
  /* Init for scheduler */
  SchedulerInit();
  SchedulerStart();
  /* Enable all interrupts */
  EI();

#if defined IDLE_CPU
  // -------------------------------------------------------------------------
  // reset CpuMngFlag
  // -------------------------------------------------------------------------
  memset((&CpuMngFlag), 0x00u , sizeof(CpuMngFlag));
#endif

  /* Main loop execution */
  while(1)
  {
#if defined IDLE_CPU
    if (Run.calculateCPU) // periodo di chiamata: 10ms
    {
        Run.calculateCPU = FALSE;
        calculateCPU();
    }

    idleCPU();  // Ferma la CPU (HALT mode) se non ci sono task attivi.
                // Usato per misurare quanta CPU libera abbiamo.
                // 1us
#endif

#if defined __CPU_LOAD_MONITOR__    
    SchedulerIdleCPU();
#endif

    /* Call main loop */
    mainLoop(); 
  }
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is mainLoop routine.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
static void mainLoop(void)
{
  /* Manage the task event */
  TaskEvent();
  
  /* Check the main background task scheduling */
  if(schedulerTaskReq.backgroundTask == 1u)
  {
    /* Low Power Manager FSM - manage the states */
    LPMS_FsmManager();

    /* Background task every TIMER_BACKGROUND_FAST (1) ms */
    if (strSCHED_BackgroundTaskReq.fastTask == 1u)
    {
      TaskBackgroundFast();
      strSCHED_BackgroundTaskReq.fastTask = 0u;
    }
    
    /* Background task every TIMER_BACKGROUND_MEDIUM (5) ms */
    if (strSCHED_BackgroundTaskReq.mediumTask == 1u)
    {
      TaskBackground5ms();
      strSCHED_BackgroundTaskReq.mediumTask = 0u;
    }
    
    /* Background task every TIMER_BACKGROUND_SLOW (100) ms */
    if (strSCHED_BackgroundTaskReq.slowTask == 1u)
    {    
      TaskBackground100ms();   
      strSCHED_BackgroundTaskReq.slowTask = 0u;
    }
    
    /* Low Power Manager FSM - manage the event requests */
    LPMS_FsmManager();
    
#if defined __CPU_LOAD_MONITOR__
    /* CPU monitor task task every  TIMER_BACKGROUND_CPU_CALC (10) ms */
    if (strSCHED_BackgroundTaskReq.cpuCalcTask == 1u)
    {    
      SchedulerCalculateCPU();  
      strSCHED_BackgroundTaskReq.cpuCalcTask = 0u;
    }
#endif
    
    /* Notify the end of background task */
    schedulerTaskReq.backgroundTask = 0u;
  }
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is idleCPU routine.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
#if defined IDLE_CPU
// Do not execute a STOP or HALT instruction while the data flash memory is being written or erased. p.1121
#pragma optimize = no_inline
// ----------------------------------------------------------------------------
static void idleCPU(void)
{
    u08 * pRun;

    pRun = (u08 *)&Run;

    if (
            (0u == schedulerTaskReq.backgroundTask) // non ci sono task pending in background
        &&  (0u == pRun[0])                         // non ci sono task a evento
        &&  (0u == pRun[1])         // Attenzione! devo controllare che tutti i flag di Run siano a 0
        )                             //        -> controllare la lunghezza di Run. Infatti se la struttura Run aumenta e occupa
                                      //           2 bytes occorre aggiungere il controllo pRun[1]
    {
      if ( CpuMngFlag.IdleFirstTimeFlag == 1u)
      {
        if( CpuMngFlag.ProceedToCalculate == 0u )
        {
         // ---------------------- START  calculateCPUActive(); ------------------------------------ //
         if( CpuMngFlag.Timer2StartFlag == 1u )
         {
           CpuMngFlag.Timer2StartFlag = 0u;

           TAU0_Channel4_Stop();

           // Legge timer tick (end idle) e accumula per calcolo CPU load.
           endCpu   = TCR04;
           if (beginCpu < endCpu)
            {
             /*Non dovrebbe accadere perchè down counter*/
            }
           else/*down counter*/
            {
              if (CpuMngFlag.LoadLimitFlag == 0u)
               {
                 resultCpu = ((beginCpu-endCpu)*4u);

               }
              else
               {
                 resultCpu = 200000u;
               }
            }
           CpuActiveTime += resultCpu;
          }
          // ---------------------- STOP  calculateCPUActive(); ------------------------------------ //
        }
      }

      /*CPU HALT MODE*/
      __halt();

      /*Idle Time corrisponde alla vasca pari a 0, mentre l'occupazione di Cpu corrisponde alla vasca pari a 1*/
      if(CpuMngFlag.ProceedToCalculate == 0u)
      {
        TAU0_Channel4_Start();
        CpuMngFlag.Timer2StartFlag = 1u;

        if (CpuMngFlag.StartCalculateFlag == 0u)
        {
          TAU0_Channel5_Start();
          CpuMngFlag.StartCalculateFlag = 1u;
        }

        beginCpu = TCR04;  // Legge timer tick per misura durata halt mode (begin idle).
      }

     CpuMngFlag.IdleFirstTimeFlag = 1u;

  }/*END IF */
}

// ----------------------------------------------------------------------------

#define CALCULATE_CPU_CLK_TICK      10u // Periodo [ms] di chiamata task calculateCPU().
#define CPU_LOAD_AVG_SAMPLES        100u

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**  This function is calculateCPU routine.
**
**  Parameters:
**  None
**
**  Returns:
**  None
**
**-----------------------------------------------------------------------------
*/
#pragma optimize = none
static void calculateCPU(void)
{
    static u32 CpuActiveTimeMin = 0x00000000U;
    static u16 idleTimeSamples;
    static u32 CpuActiveTimeSum;

    if (CpuActiveTime > CpuActiveTimeMin)
    {
        CpuActiveTimeMin = CpuActiveTime;
        cpuLoadPeak = (u16)((((u32)(CpuActiveTime))*100u) / 200000u); /* 200000 tick = 10ms */
    }

    CpuActiveTimeSum += (u32)CpuActiveTime;

    if (++idleTimeSamples == CPU_LOAD_AVG_SAMPLES)
    {

      CpuActiveTimeSum  = (u16)((((u32)(CpuActiveTimeSum))*100u) / 200000u);  /* 200000 tick = 10ms */
      cpuLoadAverage    = (u32)(((u32)(CpuActiveTimeSum))) / (idleTimeSamples);
      CpuActiveTimeSum  = 0UL;
      idleTimeSamples   = 0u;
      cpuLoadSample     = 0u;
    }
    CpuActiveTime                 = 0u;
    CpuMngFlag.ProceedToCalculate = 0u;
    CpuMngFlag.LoadLimitFlag      = 0u;
    CpuMngFlag.StartCalculateFlag = 0u;
}
#endif  /* end IDLE_CPU */


/* ==========================  EOF  ========================================= */
