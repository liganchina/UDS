/**
 * @file   PWMC_cbk.h
 * @author Mastrodonato Matteo
 * @date   10/12/2014
 * @brief  File containing the user configuration of PWMC Driver.
 *
 * @see    www.Bitron.net
 */

#ifndef PWMC_CBK_H_
#define PWMC_CBK_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This is a function callcack called at the end of the PWM pediod.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl The handle of PWM object associated to the PMW command
 *                 that just reached the period end.
 * @param [out] None
 * @return None
 */
void PWMC_EndPeriod(uint8_t hdl);

/**
 * @brief This is a function callcack called when a fbk transition occurs.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl The handle of PWM object associated to the feedback
 *                 that just had a transition.
 * @param [out] None
 * @return None
 */
void PWMC_FbkTransition(uint8_t hdl);


/*______ E X T E R N A L - D A T A ___________________________________________*/




#endif /* PWMC_CBK_H_ */
