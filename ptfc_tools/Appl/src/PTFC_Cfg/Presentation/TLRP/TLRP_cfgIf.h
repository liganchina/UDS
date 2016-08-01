/**
 * @file TLRP_cfgIf.h
 * @author Mastrodonato Matteo
 * @date 14 giu 2013
 * @brief File containing the user configuration of TLRP Driver.
 *  In particular contains the object idx (es: enumerator) of TLRP,
 *  extern of user defined function or variables.
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
| 11/02/2015 1.2  CC      Configuration for F151M project: new timer for N07320
|-----------------------------------------------------------------------------
*/

#ifndef __TLRP_CFGIF_H
#define __TLRP_CFGIF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum TLRP_HandlerFast_e
{
  /* Timer to jump in boot */
  BOOT_Jump_Timer = 0,
  /* Hardware reset timer */
  TLRP_HardReset_Timer,
  /* Timer to stabilize power supply +5s */
  TLRP_LpmsPwSupply5sTimer,
  /* N07320_ed5, par. 3.4.2 - Sleep timer to 100 ms for A5 */
  TLRP_NwmaSleepShortTimer,
  /* Timer for wrapa clear memory request */
  TLRP_ClrRecallReq,
  /* Timer for key sts equal to SNA */
  VF608_T_SNA_Timer,
  VF608_T_Preignition,
  VF608_T_PreignitionStart,
  /* Busoff timer to retransmition strategy */
  TLRP_NwmaBusOffTimer,
  TLRP_HDLF_MAX
}TLRP_HandlerFast_t;


typedef enum TLRP_HandlerSlow_e
{
  /* N07320_ed5, par. 3.4.2 - Stay active timer to 2 sec for A3, A4, A6, A7, A9, A13, A14 */
  TLRP_NwmaSaTimer = 0,
  /* N07320_ed5, par. 3.4.2 - Sleep timer to 2 sec for A10 */
  TLRP_NwmaSleepLongTimer,
  UDSA_SEC_ACC_TOUT,
  /* Timer per salvataggio DTC al Key-Off */
  DDMP_KEY_OFF_Timer,
  UDSA_S3ServerDiagAct_timer,
  UDSA_IO_Cltr_Timer,
  UDSA_Timer_Service28,
  DDMP_EcuTimeStampsTimer,
  DDMP_EcuTimeStampsFromKeyOnTimer,
  NETP_FirstTestTimer,
  UDSA_Nak78EepromEraseTimer,
  TLRP_ProtRelTimeout,
  TLRP_SavePosition,
  TLRP_UserSavePos,
  TLRP_KeyOffStatus,
  TLRP_DiagReEnable,
  TLRP_LoadDumpTimeout,
  VF608_T_BCM1_Missing_Msg,
  VF608_T_CCAN3_Missing_Msg,
  TLRP_Comfort_Timer,
  TLRP_HDLS_MAX
}TLRP_HandlerSlow_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

/* Callback prototype used to stabilize the power supply +5s */
extern void LPMS_PwSupply5sCbk(void);


#endif /* __TLRP_CFGIF_H */
