/**
 * @file DISPA.c
 * @brief The DISPA module: private header
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
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __DISPA_H__
#define __DISPA_H__

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "global.h"
#include "APPL_if.h"
#include "DISPA_cbk.h"

/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/* typedef of function pointer that modules need to implment to be used by DISPA: */
typedef u08               (*DISPA_SetCmd_t)         (u08 handle, u08 cmd);

  /* typedef of Methods for IOCOntrol management */
typedef u08               (*DISPA_CheckIoCallback_t)(u08 handle, u08 cmd);
typedef void              (*DISPA_StartIoCallback_t)(u08 handle, u08 cmd);
typedef void              (*DISPA_StopIoCallback_t) (u08 handle);

typedef struct DISPA_FunctionCfg_s
{
  u08             FUNCTION_HANDLE;
  DISPA_Module_t  MODULE;
  bool            SELF_IOCONTROL; //if TRUE the IOContontrol is managed internally by DISPA  
  DISPA_IoGroup_t GROUP;          // = DISPA_GROUP_MAX if the function is not IOcontrol enabled
  u16             IOC_TIMER;
} DISPA_FunctionCfg_t;

typedef struct DISPA_ModuleCfg_s
{
  /* Methods for functional management */
  DISPA_SetCmd_t        SetCmd;
  
  /* Methods for IOCOntrol management */
  DISPA_CheckIoCallback_t CheckIoCallback; /* if NULL, it means that the iocontrol for that module can be startd in any moment,
                                              return 0 if ok else return the UDS NACK to send to UDS client*/
  DISPA_StartIoCallback_t StartIoCallback; /* NULL only if the module is not IOControl enabled */
  DISPA_StopIoCallback_t  StopIoCallback;          /* NULL only if the module is not IOControl enabled */
  u08                     IdleCommand;
  u08                     SuspCommand;
} DISPA_ModuleCfg_t;

/*_____ G L O B A L - D A T A ________________________________________________*/;
extern const DISPA_ModuleCfg_t DISPA_ModuleCfgTable[DISPA_MOD_MAX];
extern const DISPA_FunctionCfg_t DISPA_FunctionCfgTable[DISPA_HANDLE_MAX];

/*_____ G L O B A L - M A C R O S ____________________________________________*/
#define DISPA_TIME_SECONDS(x)      (((x)*1000U)/DISPA_SLOW_MGM_TICK_MS)
#define DISPA_TIME_MS(x)           ((x)/DISPA_SLOW_MGM_TICK_MS)

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (DISPA.h) ________________________________________________*/