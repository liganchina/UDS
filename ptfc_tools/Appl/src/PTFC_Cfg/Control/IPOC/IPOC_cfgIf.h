/**
 * @file IPOC_cfgIf.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of IPOC Driver.
 *  In particular contains the object idx (es: enumerator) of IPOC,
 *  extern of user defined function or variables.
 *
 * @see www.Bitron.net
 */

#ifndef IPOC_CFGIF_H_
#define IPOC_CFGIF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum IPOC_Channel_e
{
  IPOC_Slide  = 0,
  IPOC_Tilt      ,
  IPOC_Lift      ,
  IPOC_Backres   ,
  IPOC_Spare     ,
	IPOC_HDL_MAX
}IPOC_Channel_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* IPOC_CFGIF_H_ */
