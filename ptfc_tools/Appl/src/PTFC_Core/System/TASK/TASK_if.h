#ifndef __TASK_H 		// MISRA C Rule 19.15: protect include file against repeated inclusion
#define __TASK_H

/*===========================================================================*/
/*        		B I T R O N    S p A                                 */
/*===========================================================================*/
/*  __INCLUDE File Name: 	TASK_if.h		     */
/*  __AUTHOR:			Alessandrelli				     */
/*===========================================================================*/
/*   DESCRIPTION:  							     */
/*								       	     */
/*===========================================================================*/
/*  MOD_ID  *  VER.REV  *   DATE     *  AUTHOR	*  NOTES	             */
/*===========================================================================*/
/*          *    0.0    *  24/05/11  *	Alessandrelli * First Implementation */
/*===========================================================================*/

/* =======================      include         =============================*/
#include "APPL_if.h"
#include "TASK_config.h"

/*-------------------------------------------------------------------------
*      Module: Task
*
*      This module contains the scheduler task of main program
*
*-------------------------------------------------------------------------*/
#ifndef GLOBAL_TASK
#define GLOBAL_TASK extern
#endif

/*-------------------------------------------------------------------------
*       Global Types
*-------------------------------------------------------------------------*/
typedef struct
{
  uint16_t TaskIdle    :1;
  uint16_t TaskTick    :1;
  uint16_t Task1ms     :1;
  uint16_t Task5ms     :1;
  uint16_t Task10ms    :1;
  uint16_t Task100ms   :1;
  uint16_t TaskEvent   :1;
  uint16_t TaskFlash   :1;
  uint16_t TaskLin     :1;
  uint16_t TaskPwm1    :1;
  uint16_t TaskPwm2    :1;
}tTaskRun;


/*-------------------------------------------------------------------------
*       Global Variables
*-------------------------------------------------------------------------*/
/* TODO SGR - for now not used - cla variabile di stato per sapere i task che girano */
//GLOBAL_TASK __saddr volatile tTaskRun TaskRun;

/* =====================     function declare      ========================= */
#ifdef FOREGROUND_TASK_ENABLED
  GLOBAL_TASK void TaskForegroundFast(void);
  GLOBAL_TASK void TaskForegroundMedium(void);
  GLOBAL_TASK void TaskForegroundSlow(void);
#endif /* end FOREGROUND_TASK_ENABLED */
GLOBAL_TASK void TaskBackgroundFast(void);
GLOBAL_TASK void TaskBackground100ms(void);
GLOBAL_TASK void TaskBackground5ms(void);
GLOBAL_TASK void TaskEvent(void);
#ifdef FOREGROUND_TASK_ENABLED
  GLOBAL_TASK void SLRS_FrgrndResumeTask(void);
  GLOBAL_TASK void SLRS_FrgrndSuspendTask(void);
#endif /* end FOREGROUND_TASK_ENABLED */
GLOBAL_TASK void SLRS_BckgrndResumeTask(void);
GLOBAL_TASK void SLRS_BckgrndSuspendTask(void);

/* ========================       struct      ============================== */

/* ======================    global variables   ============================ */
#if defined __CPU_LOAD_MONITOR__
  GLOBAL_TASK u16   TASK_CpuLoadAvg;  //10 ms CPU load average, 0,1 % /bit
  GLOBAL_TASK u16   TASK_CpuLoadPeak; //CPU load peak, cannot be more than 1000, 0,1 % /bit
#endif

#endif /*__TASK_H*/
