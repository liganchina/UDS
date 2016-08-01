#ifndef __FE78K0R_CG_TIMER_USER_H
#define __FE78K0R_CG_TIMER_USER_H


#include "TASK_if.h"
#include "PWMC_cbk.h"

typedef enum TMRD_Channel_e
{
  PWMD_CHAN_0 = 0,
  PWMD_CHAN_1,
  PWMD_CHAN_2
} TMRD_Channel_t;

/*#define TMRD_PWMC_BackrestFan     2U*/
/*#define TMRD_PWMC_CushionFan      3U*/
#define TMRD_PWMC_BackLight       3U

/**
 * @brief This callback macro provide to TM00 timer ISR callback service.
 * This timer in this configuration is used for the base tick (1ms) of the
 * background task.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define TMRD_IsrCbkINTTM00()\
{\
  /* Insert here the callback routines */\
  SchedulerTick();\
}

/**
 * @brief This callback macro provide to TM01 timer ISR callback service.
 * This timer in this configuration is used for the base tick (1ms) of the
 * foreground task.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define TMRD_IsrCbkINTTM01()\
{\
  /* Insert here the callback routines */\
  SchedulerForeground();\
}

/**
 * @brief This callback macro provide to TM12 timer ISR callback service.
 * In this configuration is used to notify the period (frequency) of
 * the PWM at output pin P55.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define TMRD_IsrCbkINTTM12()\
{\
  /* Insert here the callback routines */\
}

/**
 * @brief This callback macro provide to TM14 timer ISR callback service.
 * In this configuration is used to notify the period (frequency) of
 * the PWM at output pin P56.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define TMRD_IsrCbkINTTM14()\
{\
  /* Insert here the callback routines */\
}

/**
 * @brief This callback macro provide to TM16 timer ISR callback service.
 * In this configuration is used to notify the period (frequency) of
 * the PWM at output pin P56.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define TMRD_IsrCbkINTTM16()\
{\
  /* Insert here the callback routines */\
}

void TMRD_EnableTimer(TMRD_Channel_t chan);
void TMRD_DisbleTimer(TMRD_Channel_t chan);

void TMRD_ChangeDuty(TMRD_Channel_t chan, uint8_t duty);

#endif /* end __FE78K0R_CG_TIMER_USER_H */
