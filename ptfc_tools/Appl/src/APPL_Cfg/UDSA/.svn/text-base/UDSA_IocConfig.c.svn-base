/********************************************************************************/
/* @F_PROJECT:          TTM 520 FIAT                                            */
/* F_NAME:              UDSA_IocConfig.c                                        */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     26/09/2013                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| MAD          Mario Dallera             Consultant
| DF           Davide Fogliano           Polimatica S.r.l.
| FRAT         Francesco TALARICO        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 26/09/2013  0.1  GIL      First Implementation : split from UDSA_Config.c
| 15/10/2013  0.2  GIL      Manage differences between fhisical and functional diagnosis
| 25/06/2015  0.4  FRAT     New management of IO Conrol via DFCA module (porting from Ferrari F151M)
| 16/07/2015  0.5  FRAT     Alignment to Alfa Romeo CCD R5
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define UDSA_IOC_NO_MOVEMENT        0x00u
#define UDS_IOC_MOV_UP_FW           0x01u
#define UDS_IOC_MOV_DW_BK           0x02u

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


/*IO control - RDI range [FD00 - FD1F] */
static u08 Udsa_IoCtrlHeatingPsg(u08 *Data, u16 Length);      /* FD05 */
static u08 Udsa_IoCtrlHeatingDrv(u08 *Data, u16 Length);       /* FD06 */
static u08 Udsa_IoCtrlTilt(u08 *Data, u16 Length);             /* FD0A */
static u08 Udsa_IoCtrlLift(u08 *Data, u16 Length);             /* FD0B */
static u08 Udsa_IoCtrlBackrest(u08 *Data, u16 Length);         /* FD0C */
static u08 Udsa_IoCtrlSlide(u08 *Data, u16 Length);            /* FD0E */
static u08 Udsa_IoCtrlHeatingSteer(u08 *Data, u16 Length);     /* FD12 */


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O ___________________________________________*/

/*______ P R I V A T E - D A T A ___________________________________________*/

/********************************************************************************************************************************************/
/*                                               DID TABL                                                                                   */
/********************************************************************************************************************************************/

const UDSA_CmdByIdentifier_Service_t UDSA_IOControlByIdentifier[MAX_NUM_IOCTRL] =              /* 2F */
{
/* +--------+-------+------+------------------------------------------------------------------------------------------+--------------+----------------------------------+
   |  DID   |  En   | RxDL |                           Session                                                        |  Diag Type   |     Callback Function            |
   |        |       |      |                                                                                          |              |                                  |
   +--------+-------+------+------------------------------------------------------------------------------------------+--------------+----------------------------------+*/
    { 0xFD05u,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlHeatingPsg         },
    { 0xFD06u,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlHeatingDrv         },
    { 0xFD0Au,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlTilt               },
    { 0xFD0Bu,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlLift               },
    { 0xFD0Cu,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlBackrest           },
    { 0xFD0Eu,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlSlide              },
    { 0xFD12u,  ENABLE,   0u , DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION | DIAG_EOL_SESSION                          , UDSA_ADS_PHYS, Udsa_IoCtrlHeatingSteer       },
};

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/******************************************************************************/
/*                  Heating Rear Control    (DID = 0xFD05)                    */
/******************************************************************************/
static u08 Udsa_IoCtrlHeatingPsg(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_SEAT_PSG, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                    Heating Front Control    (DID = 0xFD06)                 */
/******************************************************************************/
static u08 Udsa_IoCtrlHeatingDrv(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_SEAT_DRV, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                     Tilt Motor Control    (DID = 0xFD0A)                   */
/******************************************************************************/
static u08 Udsa_IoCtrlTilt(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_TILT, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                      Lift Motor Control    (DID = 0xFD0B)                  */
/******************************************************************************/
static u08 Udsa_IoCtrlLift(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_LIFT, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                   Backrest Motor Control    (DID = 0xFD0C)                 */
/******************************************************************************/
static u08 Udsa_IoCtrlBackrest(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_BACKREST, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                    Slide Motor Control    (DID = 0xFD0E)                   */
/******************************************************************************/
static u08 Udsa_IoCtrlSlide(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_SLIDE, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

/******************************************************************************/
/*                    Heating Steer Control    (DID = 0xFD12)                 */
/******************************************************************************/
static u08 Udsa_IoCtrlHeatingSteer(u08 *Data, u16 Length)
{
  return DISPA_SetIoControl(DISPA_STW, (UDSA_IOControlSubf_t)Data[3], Data[4]);
}

#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDSA_IocConfig.c) ______________________________________*/
