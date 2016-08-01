/*
 * SNSP_if.h
 *
 *  Created on: 26/06/2015
 *      Author: Livio Bastonero
 */

#ifndef SNSP_IF_H_
#define SNSP_IF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef SNSP_IF_OWNER
	#define SNSP_EXTERN
#else
	#define SNSP_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "SNSP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief The function performs the initialization of the structure array
 *        SNSP_privateTable[hdl]
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
SNSP_EXTERN	void 		 SNSP_Init(void);

/**
 * @brief Computes the temperature and the diag state of the NTC sensor
          Stores the results into SNS_PrivateData
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
SNSP_EXTERN	void		 SNSP_Mgm(void);

/**
 * @brief The function allows to read the sensor fault
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values listed in SNSP_cfgIf.h
 * @param [out] None
 *
 * @return PRES_Fault_t
 * @retval PRES_NO_FAULT if the sensor has no fault
 * @retval PRES_SHORT_TO_GND if the sensor is short circuited to GND
 * @retval PRES_SHORT_TO_BAT if the sensor is short circuited to BAT
 *
 * @retval CTRL_NOT_TESTED if the device is not tested
 *
 */
SNSP_EXTERN PRES_Fault_t SNSP_GetDiag(SNSP_Handle_t hdl);

/**
 * @brief This function returns the temperature.
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @retval SNSP_PrivateData[hdl].temperatureData
 */
int16_t SNSP_GetTemperature(SNSP_Handle_t hdl);

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
SNSP_EXTERN  void  SNSP_EnableDisable (SNSP_Handle_t hdl, PRES_EnSts_t state);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* SNSP_IF_H_ */
