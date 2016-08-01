/**
 * @file TLRP.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the header and include chain of TLRP Driver.
 *
 * @see www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 15/06/2013 1.0  MM      First release
|-----------------------------------------------------------------------------
| 09/10/2014 1.1  CC      New management of the callback: deleted input parameter
|-----------------------------------------------------------------------------
*/

#ifndef __TLRP_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __TLRP_H

#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __TLRP_IS_PRESENT__

#include "TLRP_config.h"


typedef struct
{
  u16                 timeToRun;
  TLRP_CallbackFast_t callback;
}TLRP_TableFast_t;

typedef struct
{
  u32                 timeToRun;
  TLRP_CallbackSlow_t callback;
}TLRP_TableSlow_t;


typedef struct
{
  u16 timerFast[TLRP_HDLF_MAX];
  u32 timerSlow[TLRP_HDLS_MAX];
}TLRP_PrivateData_t;

extern const TLRP_TableFast_t TLRP_TimerTableFast[TLRP_HDLF_MAX];
extern const TLRP_TableSlow_t TLRP_TimerTableSlow[TLRP_HDLS_MAX];

#endif /* end __TLRP_IS_PRESENT__ */

#endif  /* end __TLRP_H */
