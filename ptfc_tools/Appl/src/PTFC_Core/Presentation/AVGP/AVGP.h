/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                                */
/* F_NAME:              AVGP                                                    */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     07/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MAM          Matteo MASTRODONATO       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 07/giu/2013 0.1  MAM	   Matteo MASTRODONATO
*/

#ifndef AVGP_H_
#define AVGP_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __AVGP_IS_PRESENT__

/* !!! NOT MOVE !!! */
#define	AVGP_1_SAMPLE		  0U
#define	AVGP_2_SAMPLE		  1U
#define	AVGP_4_SAMPLE		  2U
#define	AVGP_8_SAMPLE		  3U
#define	AVGP_16_SAMPLE		4U
#define	AVGP_32_SAMPLE		5U
#define	AVGP_64_SAMPLE		6U
#define	AVGP_128_SAMPLE		7U
#define	AVGP_256_SAMPLE		8U

#include "AVGP_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef struct 
{
	ADCD_Channel_t  ADCD_CHAN;
	u16				SCALING_GAIN;
	u16				OVER_V_THRES_H;
	u16				OVER_V_THRES_L;
	u16				UNDER_V_THRES_H;
	u16				UNDER_V_THRES_L;
	u16				HW_CAL_OFFSET;
}AVGP_CfgTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/


#define AVGP_FAST_BUFF_SIZE		0x1U << AVGP_FAST_SAMPLE
#define AVGP_SLOW_BUFF_SIZE		0x1U << AVGP_SLOW_SAMPLE


#define	AVGP_GAIN_DIV		    10U /* 1/(2^AVGP_GAIN_DIV) = risoluzione del parametro SCALING GAIN */

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const AVGP_CfgTable_t AVGP_CfgTable[];

#endif /* end __AVGP_IS_PRESENT__ */

#endif /* AVGP_H_ */
