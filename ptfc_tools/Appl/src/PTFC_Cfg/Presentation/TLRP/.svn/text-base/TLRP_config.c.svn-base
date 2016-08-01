/**
 * @file TLRP_config.c
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the user configuration of TLRP Driver.
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

#include "TLRP.h"

/* Module inhibition filter */
#ifdef __TLRP_IS_PRESENT__

/*______ P R O T O T Y P E S _________________________________________________*/

/**
 * @brief In case the Country_Code is equal to USA OR CANADA OR MEXICO values,
 * @      at the end of Long comfort timer ECU goes in PowerOff
 * @param none
 * @return none
 * @retval none
 */
void TLRP_Comfort_Timer_Expired(void);

/**
 * @brief In case the Country_Code is equal to USA OR CANADA OR MEXICO values,
 * @      at the end of Long comfort timer ECU goes in PowerOff
 * @param none
 * @return none
 * @retval none
 */
void TLRP_KeyOffStatus_Expired(void);

/*____________________________________________________________________________*/


const TLRP_TableFast_t TLRP_TimerTableFast[TLRP_HDLF_MAX] =
{
  /*         Handle                    Time (ms)      Callback                    */
  /* BOOT_Jump_Timer          */    {      1U,      UDSA_CallBoot                  },
  /* TLRP_HardReset_Timer     */    {     30U,      LPMS_HwReset                   },
  /* TLRP_LpmsPwSupply5sTimer */    {     20U,      LPMS_PwSupply5sCbk             },
  /* TLRP_NwmaSleepShortTimer */    {    100U,      NULL                           },
  /* TLRP_ClrRecallReq        */    {     20U,      DISPA_ClrRecallReq             },
  /* VF608_T_SNA_Timer        */    {     50U,      VF608_OpModeStsRecovery        },
  /* VF608_T_Preignition      */    {    150U,      VF608_EcuRecovery1_PartC       },
  /* VF608_T_PreignitionStart */    {     80U,      VF608_EcuRecovery1_PartG       },
  /* TLRP_NwmaBusOffTimer     */    {   1000U,      NWMA_DllErrorMgmt              },
};


/************************* NOTA BENE *************************/
/* il paramentro Time deve essere multiplo di TLRP_SLOW_TICK */
/*************************************************************/
const TLRP_TableSlow_t TLRP_TimerTableSlow[TLRP_HDLS_MAX] = 
{
  /*         Handle                        Time (ms)      Callback                         */
  /* TLRP_NwmaSaTimer                 */  {   2000UL,      NULL                           },
  /* TLRP_NwmaSleepLongTimer          */  {   2000UL,      NULL                           },
  /* UDSA_SEC_ACC_TOUT                */  {  10000UL,      NULL                           },
  /* DDMP_KEY_OFF_Timer               */  {   5000UL,      DDMP_KeyOffService             },
  /* UDSA_S3ServerDiagAct_timer       */  {   5000UL,      UDSA_CheckDiagSessionAct       },
  /* UDSA_IO_Cltr_Timer               */  {  30000UL,      NULL                           },
  /* UDSA_Timer_Service28             */  {   3000UL,      NETP_Service28OffsetCbk        },
  /* DDMP_EcuTimeStampsTimer          */  {  60000UL,      DDMP_MngEcuTimeStamps          },
  /* DDMP_EcuTimeStampsFromKeyOnTimer */  {  15000UL,      DDMP_MngEcuTimeStampsFromKeyOn },
  /* NETP_FirstTestTimer              */  {   2500UL,      NULL                           },
  /* UDSA_Nak78EepromEraseTimer       */  {   4000UL,      UDSA_Nak78PendingDelay         },
  /* TLRP_ProtRelTimeout              */  {   5000UL,      MOTP_OpenProtRel               },
  /* TLRP_SavePosition                */  {   4000UL,      MOTP_SavePosition              },
  /* TLRP_UserSavePos                 */  {   1500UL,      DISPA_UserSavePos              },
  /* TLRP_KeyOffStatus                */  {  60000UL,      TLRP_KeyOffStatus_Expired      },
  /* TLRP_DiagReEnable                */  {   5000UL,      FVMP_DiagEnableAfterCrank      },
  /* TLRP_LoadDumpTimeout             */  {   1000UL,      NULL                           },
  /* VF608_T_BCM1_Missing_Msg         */  {   1000UL,      VF608_StatusBhBcm1Rec          },
  /* VF608_T_CCAN3_Missing_Msg        */  {   1000UL,      VF608_StatusCcan3Rec           },
  /* TLRP_Comfort_Timer               */  {1200000UL,      TLRP_Comfort_Timer_Expired     },

};


/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief In case the Country_Code is equal to USA OR CANADA OR MEXICO values,
 * @      at the end of Long comfort timer ECU goes in PowerOff
 * @param none
 * @return none
 * @retval none
 */
void TLRP_Comfort_Timer_Expired(void)
{
  LPMS_SetEvent(LPMS_PWR_OFF);
}

/**
 * @brief In case the Country_Code is equal to USA OR CANADA OR MEXICO values,
 * @      at the end of Long comfort timer ECU goes in PowerOff
 * @param none
 * @return none
 * @retval none
 */
void TLRP_KeyOffStatus_Expired(void)
{
  LPMS_SetEvent(LPMS_PWR_OFF);
}

/*____________________________________________________________________________*/

#endif /* end __TLRP_IS_PRESENT__ */

/*______ E N D _____ (TLRP_config.c) _________________________________________*/
