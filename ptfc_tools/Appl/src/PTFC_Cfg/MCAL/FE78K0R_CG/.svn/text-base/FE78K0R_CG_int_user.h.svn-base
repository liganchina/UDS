#ifndef __FE78K0R_CG_INT_USER_H
#define __FE78K0R_CG_INT_USER_H


#include "TASK_if.h"

/* TODO COBRA: inserire numero corretto */
#define INTD_PWMC_BackLight       3U

typedef enum INTD_Channel_e
{
  INTD_CHAN_0 = 0,
} INTD_Channel_t;


/**
 * @brief This callback macro provide to ISR callback service
 * of the external interrupt INTP0.
 * This configuration is used for PWM17 diagnosis.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
#define INTD_IsrCbkINTP0()\
{\
  /* Insert here the callback routines */\
  PWMC_FbkTransition(INTD_PWMC_BackLight);\
}


/**
 * @brief This fuction enables the interrut request and the
 * related callback of the channel passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return None
 */
void INTD_EnableIsr(INTD_Channel_t chan);


/**
 * @brief This fuction disables the interrut request and the
 * related callback of the channel passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return None
 */
void INTD_DisableIsr(INTD_Channel_t chan);

/**
 * @brief This fuction return the electrical level of requested channel
 * passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return electrical level
 * @retval 0
 * @retval 1
 */
u08 INTD_GetLevel(INTD_Channel_t chan);

#endif /* end __FE78K0R_CG_INT_USER_H */
