/**
 * @file DISPA_config.c
 * @brief DISPA Module: configuration header
 *
 * @version 0.1
 * @author Davide Fogliano (Polimatica S.r.l.)
 * @date 24 june 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano           Polimatica S.r.l
|-----------------------------------------------------------------------------
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
| 24/07/15   0.2  DC      Porting to 952 project
|-----------------------------------------------------------------------------
*/

#ifndef __DISPA_CONFIG_H
#define __DISPA_CONFIG_H


/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "MOTA.h"
#include "MOTA_Define.h"
#include "APSA.h"
#include "APSA_Config.h"
#include "DISPA_cbk.h"
#include "EXMMA_config.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

typedef enum MSM_storageStatus_e
{
  STORAGE_NOT_ACTIVE          = 0x00u,
  STORAGE_ACTIVE              = 0x01u,
  STORAGE_SUCCESS             = 0x02u,
  STORAGE_SNA                 = 0x03u
}MSM_storageStatus_t;

#define DISPA_TOL_PERCENT      50U
#define DISPA_SLIDE_TOL        70U

#define DISPA_MEM_RECALL_SPEED_TH 10U     /* (risoluzione: 1 Km/h / lsb) */

/*______ G L O B A L - M A C R O S ___________________________________________*/

#define DISPA_USER_INIT()                 DISPA_cfgInit();\
                                          DISPA_UpdateFunctionByProxi();\
                                          EEPP_UpdateFunctionByProxi()

#define DISPA_MODEL_IN_INIT()

#define DISPA_FAST_MODEL_IN_UPDATE()      DISPA_FastModelInUpdate()

#define DISPA_MODEL_STEP_CALL()\
{\
  MOTA();\
  APSA();\
}

#define DISPA_COMPUTE_COMMAND()           DISPA_ComputeCommands()

#define DISPA_STATUS_UPDATE()             DISPA_UpdateStatus()

#define DISPA_SLOW_MODEL_IN_UPDATE()      DISPA_SlowModelInUpdate()

#define DISPA_PRIORITY_CALCULATION()      DISPA_PriorityManager()

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

void DISPA_UpdateFunctionByProxi(void);

#endif /* end __DISPA_IS_PRESENT__ */

#endif /* end __DISPA_CONFIG_H */

/*_____ E N D _____ (DISPA_config.h) __________________________________________*/

