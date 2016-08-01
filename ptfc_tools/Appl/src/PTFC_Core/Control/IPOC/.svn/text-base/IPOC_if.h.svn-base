/**
 * @file IPOC_if.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing interface of IPOC Driver.
 *  IPOC: "Digital Input on Analog pin"
 *
 * @see www.Bitron.net
 */

#ifndef IPOC_IF_H_
#define IPOC_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef IPOC_IF_OWNER
	#define IPOC_EXTERN
#else
	#define IPOC_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "IPOC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum
{
  IPOC_CMD_IDLE = 0U,
  IPOC_CMD_UP_FW,
  IPOC_CMD_DOWN_BW
}IPOC_DirectionCount_t;

typedef enum
{
  IPOC_NO_STALL = 0U,
  IPOC_STALL_UP_FW,
  IPOC_STALL_DOWN_BW,
  IPOC_STALL_BOTH
}IPOC_Stall_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the DIOD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
IPOC_EXTERN	void IPOC_Init(void);


/**
 * @brief Set the counter buffer used by selected channel. It should be used at
 * @brief power on on, typically the buffer is shared with EEPROM manager.
 * @param chan the requested channel
 * @return
 */
IPOC_EXTERN void IPOC_SetCounter(IPOC_Channel_t chan, int16_t *counterPtr);


/**
 * @brief Get the position of the selected channel
 * @param chan the requested channel
 * @return int16_t
 */

int16_t IPOC_GetPosition(IPOC_Channel_t chan);


/**
 * @brief Set the position of the selected channel
 * @param chan the requested channel
 * @return CTRL_ResSts_t
 * @retval MS_OK Position set correctly
 * @retval MS_NOT_OK Counter not configured
 */
CTRL_ResSts_t IPOC_SetPosition(IPOC_Channel_t chan, int16_t position);


/**
 * @brief Get if the selected channel is in stall condition
 * @param chan the requested channel
 * @return boolean
 * @retval TRUE
 * @retval FALSE
 */
IPOC_EXTERN IPOC_Stall_t IPOC_GetStallStatus(IPOC_Channel_t chan);


/**
 * @brief Set the selected channel is in stall condition.
 * @param chan the requested channel
 * @return none
 */
IPOC_EXTERN void IPOC_SetStallStatus(IPOC_Channel_t chan, IPOC_Stall_t stallSts);


/**
 * @brief Get the counter direction of selected channel
 * @param chan the requested channel
 * @return IPOC_DirectionCount_t
 * @retval IPOC_CMD_IDLE
 * @retval IPOC_CMD_UP_FW
 * @retval IPOC_CMD_DOWN_BW
 */
IPOC_EXTERN IPOC_DirectionCount_t IPOC_GetDirection(IPOC_Channel_t chan);


/**
 * @brief Set the counter direction of selected channel
 * @param chan the requested channel
 * @return none
 */
IPOC_EXTERN void IPOC_SetDirection(IPOC_Channel_t chan, IPOC_DirectionCount_t moveDirection);


/**
 * @brief This function manages pulse counters. It have to be called periodically considering the
 * @brief maximum frequency of input pulse signal.
 * @param chan the requested channel, moveDirection movement direction
 * @return none
 */
IPOC_EXTERN void IPOC_CounterMgm(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* IPOC_IF_H_ */
