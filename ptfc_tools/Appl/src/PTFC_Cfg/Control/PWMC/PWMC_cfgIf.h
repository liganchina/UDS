/**
 * @file PWMC_cfgIf.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of PWMC Driver.
 *  In particular contains the object idx (es: enumerator) of PWMC,
 *  extern of user defined function or variables.
 *
 * @see www.Bitron.net
 */

#ifndef PWMC_CFGIF_H_
#define PWMC_CFGIF_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum PWMC_Handle_e
{
  PWMC_HeatDrv = 0               ,
  PWMC_HeatPass                  ,
  PWMC_HeatSteer                 ,
  PWMC_SW_HDL_MAX                ,
  PWMC_HeatLed = PWMC_SW_HDL_MAX , /* Don't modify the right part of "="!!*/
  PWMC_HW_HDL_MAX
}PWMC_Handle_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* PWMC_CFGIF_H_ */
