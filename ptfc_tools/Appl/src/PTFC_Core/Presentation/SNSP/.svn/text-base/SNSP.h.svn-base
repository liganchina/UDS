/**
 * @file SNSP.h
 * @author
 * @date 26/06/2015
 * @brief
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 *                Livio Bastonero           Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 26/06/2015        0.1     First revision
 */

#ifndef __SNSP_H
#define __SNSP_H

/* Dichiarazione dell'interfaccia del Layer */
#ifdef SNSP_IF_OWNER
	#define SNSP_EXTERN
#else
	#define SNSP_EXTERN		extern
#endif

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "PRES_if.h"
#include "SNSP_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ GLOBAL - T Y P E S _____________________________________________*/

/* Module inhibition filter */
#ifdef __SNSP_IS_PRESENT__

typedef struct SNSP_FunRet_s
{
  int16_t  temperature;
  PRES_Fault_t error;
}SNSP_FunRet_t;

typedef struct SNSP_CfgTable_s
{
  SNSP_FunRet_t       (*GetNTCTempError)(void);
}SNSP_CfgTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

SNSP_EXTERN const SNSP_CfgTable_t SNSP_CfgTable[SNSP_HDL_MAX];

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

SNSP_FunRet_t  Snsp_Temp_Error(int16_t X, int16_t Z, const FUNP_Interp_curve_point_t TAB[], uint8_t num_point);


#endif /*__SNSP_IS_PRESENT__ */

#endif  /* end __SNSP_H */

/*_____ E N D _____ (SNSP.h) _________________________________________________*/
