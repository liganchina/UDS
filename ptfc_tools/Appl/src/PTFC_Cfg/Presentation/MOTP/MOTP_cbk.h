/*
 * MOTP_cbk.h
 *
 *  Created on: 22/set/2014
 *      Author: mmastrodonato
 */

#ifndef MOTP_CBK_H_
#define MOTP_CBK_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef MOTP_IF_OWNER
  #define MOTP_EXTERN
#else
  #define MOTP_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

MOTP_EXTERN void MOTP_OpenProtRel(void);
//MOTP_EXTERN void MOTP_SavePosition(void);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MOTP_IF_H_ */
