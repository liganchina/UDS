/********************************************************************************/
/* @F_PROJECT:          TTM636                                                  */
/* F_NAME:              UDSA_RdiConfig.c                                        */
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
| FRAT         Francesco Talarico        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 26/09/2013  0.1  GIL      First Implementation : split from UDSA_Config.c
| 15/10/2013  0.2  GIL      Manage differences between fhisical and functional diagnosis
| 16/07/2015  1.0  FRAT     Porting from Ferrari NAG/NAP F151M and alignment to Alfa Romeo CCD R5
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define UDSA_MAX_PROXI_LEN      255U
#define UDSA_ERASE_EE_KEY_SIZE  7u
#define UDSA_NUM_MOTOR          4U

/*______ G L O B A L - T Y P E S _____________________________________________*/


/*______ E X T E R N A L - D A T A ___________________________________________*/
// TODO TIGRE
//extern u08 UDSA_MirrorApplSwId[UDSA_LN_APP_SW_IDENTIFICATION];
extern DRVD_RStatus_t UDSA_EraseEpromResult;
extern __no_init u16 UDSA_BootSwVers;

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Read */
static u08 Udsa_DidReadVINOdometer(u08 *Data, u16 Length);                            /*0103*/
static u08 Udsa_DidReadEcuInputs(u08 *Data, u16 Length);                              /*0131*/
static u08 Udsa_DidReadEcuOutputs(u08 *Data, u16 Length);                             /*0132*/
static u08 Udsa_DidReadHeaterCurrent(u08 *Data, u16 Length);                          /*0133*/
static u08 Udsa_DidReadPillarCalibration(u08 *Data, u16 Length);                      /*0134*/
static u08 Udsa_DidReadVehicleSpeed(u08 *Data, u16 Length);                           /*1002*/
static u08 Udsa_DidReadBatteryVoltage(u08 *Data, u16 Length);                         /*1004*/
static u08 Udsa_DidReadECUTimeStampsRAM(u08 *Data, u16 Length);                       /*1008*/
static u08 Udsa_DidReadECUTimeStampsFromKeyOnRAM(u08 *Data, u16 Length);              /*1009*/
static u08 Udsa_DidReadCheckEOLConfigurationData(u08 *Data, u16 Length);              /*102A*/
static u08 Udsa_DidReadOperationalModeStatus(u08 *Data, u16 Length);                  /*1921*/

static u08 Udsa_DidReadNumberOfFlashRewrite(u08 *Data, u16 Length);                   /*2003*/
static u08 Udsa_DidReadECUTimeStampsEEPROM(u08 *Data, u16 Length);                    /*2008*/
static u08 Udsa_DidReadECUTimeStampsKeyOnEEPROM(u08 *Data, u16 Length);               /*2009*/
static u08 Udsa_DidReadKeyOnCounterEEPROM(u08 *Data, u16 Length);                     /*200A*/
static u08 Udsa_DidReadECUTimeFirstDTCDetectionEEPROM(u08 *Data, u16 Length);         /*200B*/
static u08 Udsa_DidReadECUTimeStamps1DTCDetectEEPROM(u08 *Data, u16 Length);          /*200C*/
static u08 Udsa_DidReadProgrammingStatus(u08 *Data, u16 Length);                      /*2010*/
static u08 Udsa_DidReadVINLockState(u08 *Data, u16 Length);                           /*2013*/
static u08 Udsa_DidReadECUProxiData(u08 *Data, u16 Length);                           /*2024*/
static u08 Udsa_DidReadProxiWriteCounter(u08 *Data, u16 Length);                      /*292E*/

static u08 Udsa_DidReadBootSoftwareIdentification(u08 *Data, u16 Length);             /*F180*/
static u08 Udsa_DidReadApplicationSoftwareIdentification (u08 *Data, u16 Length);     /*F181*/
static u08 Udsa_DidReadApplicationDataIdentification (u08 *Data, u16 Length);         /*F182*/
static u08 Udsa_DidReadBootSoftwareFingerprint (u08 *Data, u16 Length);               /*F183*/
static u08 Udsa_DidReadApplSoftwareFingerprint (u08 *Data, u16 Length);               /*F184*/
static u08 Udsa_DidReadApplicationDataFingerprint (u08 *Data, u16 Length);            /*F185*/
static u08 Udsa_DidReadActiveDiagnSessionDataIdentifier(u08 *Data, u16 Length);       /*F186*/
static u08 Udsa_DidReadVehicleManufacturerSparePartNumber(u08 *Data, u16 Length);     /*F187*/
static u08 Udsa_DidReadVehicleManufECUSoftwareNumber (u08 *Data, u16 Length);         /*F188*/
static u08 Udsa_DidReadVehManEcuSwCalN (u08 *Data, u16 Length);                       /*F18A*/
static u08 Udsa_DidReadVehManEcuSwAppN (u08 *Data, u16 Length);                       /*F18B*/
static u08 Udsa_DidReadEcuSerialNumber (u08 *Data, u16 Length);                       /*F18C*/
static u08 Udsa_DidReadVINOriginal (u08 *Data, u16 Length);                           /*F190*/
static u08 Udsa_DidReadVehicleManECUHWNumber (u08 *Data, u16 Length);                 /*F191*/
static u08 Udsa_DidReadSystemSupplierEcuHardwareNumber(u08 *Data, u16 Length);        /*F192*/
static u08 Udsa_DidReadSystemSupplierEcuHWVerNumber(u08 *Data, u16 Length);           /*F193*/
static u08 Udsa_DidReadSystemSupplierEcuSoftwareNumber(u08 *Data, u16 Length);        /*F194*/
static u08 Udsa_DidReadSystemSupplierEcuSWVerNumber(u08 *Data, u16 Length);           /*F195*/
static u08 Udsa_DidReadHomologationCode(u08 *Data, u16 Length);                       /*F196*/
static u08 Udsa_DidReadIdentificationCode(u08 *Data, u16 Length);                     /*F1A0*/
static u08 Udsa_DidReadEOLConfigurationCode(u08 *Data, u16 Length);                   /*F1A1*/
static u08 Udsa_DidReadSincomAndFactory (u08 *Data, u16 Length);                      /*F1A4*/
static u08 Udsa_DidReadISOCode(u08 *Data, u16 Length);                                /*F1A5*/
static u08 Udsa_DidReadVINCurrent(u08 *Data, u16 Length);                             /*F1B0*/

static u08 Udsa_DidReadNTCDrvTemperature(u08 *Data, u16 Length);                      /*FD20*/
static u08 Udsa_DidReadNTCPsgTemperature(u08 *Data, u16 Length);                      /*FD21*/
static u08 Udsa_DidReadNTCSteerTemperature(u08 *Data, u16 Length);                    /*FD22*/
static u08 Udsa_DidReadHeatTemp(u08 *Data, u16 Length);                               /*FD23*/
static u08 Udsa_DidReadHeatTime(u08 *Data, u16 Length);                               /*FD24*/
static u08 Udsa_DidReadHeatDuty(u08 *Data, u16 Length);                               /*FD25*/
static u08 Udsa_DidReadSeatPositions(u08 *Data, u16 Length);                          /*FD30*/
static u08 Udsa_DidReadStrokes(u08 *Data, u16 Length);                                /*FD33*/
static u08 Udsa_DidReadNominalStroke(u08 *Data, u16 Length);                          /*FD34*/
static u08 Udsa_DidReadAPSADebug(u08 *Data, u16 Length);                              /*FD35*/
static u08 Udsa_DidReadAntiPinchThresholds(u08 *Data, u16 Length);                    /*FD36*/
static u08 Udsa_DidReadSeatAndMirrorsMemoryStored(u08 *Data, u16 Length);             /*FD39*/
static u08 Udsa_DidReadOpModeStatusInternal(u08 *Data, u16 Length);                   /*FD53*/
static u08 Udsa_DidReadAntiPinchAdaptation(u08 *Data, u16 Length);                    /*FD54*/
static u08 Udsa_DidReadAntiPinchAttention(u08 *Data, u16 Length);                     /*FD55*/

static u08 Udsa_DidReadEquipmentSelection(u08 *Data, u16 Length);                     /*FD50*/
static u08 Udsa_DidReadEquipmentConfiguration(u08 *Data, u16 Length);                 /*FD51*/

/* Write */
static u08 Udsa_DidWritePillarCalibration (u08 *Data, u16 Length);                    /*0134*/
static u08 Udsa_DidWriteProxiData (u08 *Data, u16 Length);                            /*2023*/
static u08 Udsa_DidWriteBootSoftwareIdentification (u08 *Data, u16 Length);           /*F180*/
static u08 Udsa_DidWriteApplicationSoftwareIdentification (u08 *Data, u16 Length);    /*F181*/
static u08 Udsa_DidWriteApplicationDataIdentification (u08 *Data, u16 Length);        /*F182*/
static u08 Udsa_DidWriteBootSoftwareFingerprint (u08 *Data, u16 Length);              /*F183*/
static u08 Udsa_DidWriteApplSoftwareFingerprint (u08 *Data, u16 Length);              /*F184*/
static u08 Udsa_DidWriteApplicationDataFingerprint (u08 *Data, u16 Length);           /*F185*/
static u08 Udsa_DidWriteVehicleManufacturerSparePartNumber(u08 *Data, u16 Length);    /*F187*/
static u08 Udsa_DidWriteVehicleManufECUSoftwareNumber (u08 *Data, u16 Length);        /*F188*/
static u08 Udsa_DidWriteVehManEcuSwCalN (u08 *Data, u16 Length);                      /*F18A*/
static u08 Udsa_DidWriteVehManEcuSwAppN (u08 *Data, u16 Length);                      /*F18B*/
static u08 Udsa_DidWriteEcuSerialNumber (u08 *Data, u16 Length);                      /*F18C*/
static u08 Udsa_DidWriteVINOriginal (u08 *Data, u16 Length);                          /*F190*/
static u08 Udsa_DidWriteVehicleManufacECUHardwareNumber (u08 *Data, u16 Length);      /*F191*/
static u08 Udsa_DidWriteSystemSupplierEcuHardwareNumber (u08 *Data, u16 Length);      /*F192*/
static u08 Udsa_DidWriteSystemSupplEcuHWVerNumber (u08 *Data, u16 Length);            /*F193*/
static u08 Udsa_DidWriteSystemSupplierEcuSoftwareNumber (u08 *Data, u16 Length);      /*F194*/
static u08 Udsa_DidWriteSystemSupplEcuSWVerNumber (u08 *Data, u16 Length);            /*F195*/
static u08 Udsa_DidWriteHomologationCode (u08 *Data, u16 Length);                     /*F196*/
static u08 Udsa_DidWriteSincomAndFactory (u08 *Data, u16 Length);                     /*F1A4*/
static u08 Udsa_DidWriteISOCode(u08 *Data, u16 Length);                               /*F1A5*/

static u08 Udsa_DidWriteHeatTemp(u08 *Data, u16 Length);                              /*FD23*/
static u08 Udsa_DidWriteHeatTime(u08 *Data, u16 Length);                              /*FD24*/
static u08 Udsa_DidWriteHeatDuty(u08 *Data, u16 Length);                              /*FD25*/

static u08 Udsa_DidWriteNominalStroke(u08 *Data, u16 Length);                         /*FD34*/

static u08 Udsa_DidWriteAntiPinchThresholds(u08 *Data, u16 Length);                   /*FD36*/
static u08 Udsa_DidWriteAntiPinchAdaptation(u08 *Data, u16 Length);                   /*FD54*/
static u08 Udsa_DidWriteAntiPinchAttention(u08 *Data, u16 Length);                    /*FD55*/

static u08 Udsa_DidWriteEquipmentSelection (u08 *Data, u16 Length);                   /*FD50*/
static u08 Udsa_DidWriteEquipmentConfiguration (u08 *Data, u16 Length);               /*FD51*/

static u08 Udsa_DidWriteEraseEeprom(u08 *Data, u16 Length);                           /*FDF1*/

/*______ G L O B A L - D A T A _______________________________________________*/
const u08 Udsa_ERASE_EE_KEY[UDSA_ERASE_EE_KEY_SIZE]  = { 0x41U, 0x53U, 0x53U, 0x41U, 0x4CU, 0x56U, 0x4FU };

const UDSA_CmdByIdentifier_Service_t UDSA_ReadDataByIdentifier[MAX_NUM_DID_READ] =              /* Servizio 22 - 52 DID */
{
/* +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+
   |   DID     |  En   |RxDL |                           Session                                                                    | Diag type   |                      Callback Function                |
   |           |       |     |                                                                                                      |             |                                                       |
   +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+*/
    { 0x0103u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVINOdometer                            },
    { 0x0131u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadEcuInputs                              },
    { 0x0132u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadEcuOutputs                             },
    { 0x0133u,    ENABLE, 3u, DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidReadHeaterCurrent                          },
    { 0x0134u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_PHYS, Udsa_DidReadPillarCalibration                      },
    { 0x1002u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehicleSpeed                           },
    { 0x1004u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadBatteryVoltage                         },
    { 0x1008u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeStampsRAM                       },
    { 0x1009u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeStampsFromKeyOnRAM              },
    { 0x102Au,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadCheckEOLConfigurationData              },
    { 0x1921u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadOperationalModeStatus                  },
    { 0x2003u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadNumberOfFlashRewrite                   },
    { 0x2008u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeStampsEEPROM                    },
    { 0x2009u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeStampsKeyOnEEPROM               },
    { 0x200Au,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadKeyOnCounterEEPROM                     },
    { 0x200Bu,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeFirstDTCDetectionEEPROM         },
    { 0x200Cu,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUTimeStamps1DTCDetectEEPROM          },
    { 0x2010u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadProgrammingStatus                      },
    { 0x2013u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVINLockState                           },
    { 0x2024u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadECUProxiData                           },
    { 0x292Eu,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadProxiWriteCounter                      },
    { 0xF180u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadBootSoftwareIdentification             },
    { 0xF181u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadApplicationSoftwareIdentification      },
    { 0xF182u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadApplicationDataIdentification          },
    { 0xF183u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadBootSoftwareFingerprint                },
    { 0xF184u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadApplSoftwareFingerprint                },
    { 0xF185u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadApplicationDataFingerprint             },
    { 0xF186u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadActiveDiagnSessionDataIdentifier       },
    { 0xF187u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehicleManufacturerSparePartNumber     },
    { 0xF188u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehicleManufECUSoftwareNumber          },
    { 0xF18Au,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehManEcuSwCalN                        },
    { 0xF18Bu,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehManEcuSwAppN                        },
    { 0xF18Cu,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadEcuSerialNumber                        },
    { 0xF190u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVINOriginal                            },
    { 0xF191u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVehicleManECUHWNumber                  },
    { 0xF192u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadSystemSupplierEcuHardwareNumber        },
    { 0xF193u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadSystemSupplierEcuHWVerNumber           },
    { 0xF194u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadSystemSupplierEcuSoftwareNumber        },
    { 0xF195u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadSystemSupplierEcuSWVerNumber           },
    { 0xF196u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadHomologationCode                       },
    { 0xF1A0u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadIdentificationCode                     },
    { 0xF1A1u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadEOLConfigurationCode                   },
    { 0xF1A4u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadSincomAndFactory                       },
    { 0xF1A5u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadISOCode                                },
    { 0xF1B0u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadVINCurrent                             },
    { 0xFD20u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadNTCDrvTemperature                      },
    { 0xFD21u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadNTCPsgTemperature                      },
    { 0xFD22u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadNTCSteerTemperature                    },
    { 0xFD23u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadHeatTemp                               },
    { 0xFD24u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadHeatTime                               },
    { 0xFD25u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_BOTH, Udsa_DidReadHeatDuty                               },
    { 0xFD30u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_BOTH, Udsa_DidReadSeatPositions                          },
    { 0xFD33u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_BOTH, Udsa_DidReadStrokes                                },
    { 0xFD34u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadNominalStroke                          },
    { 0xFD35u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadAPSADebug                              },
    { 0xFD36u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadAntiPinchThresholds                    },
    { 0xFD39u,    ENABLE, 3u, DIAG_ALL_SESSION                                                                                      , UDSA_ADS_PHYS, Udsa_DidReadSeatAndMirrorsMemoryStored             },
    { 0xFD50u,    ENABLE, 3u, DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidReadEquipmentSelection                     },
    { 0xFD51u,    ENABLE, 3u, DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidReadEquipmentConfiguration                 },
    { 0xFD53u,    ENABLE, 3u, DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidReadOpModeStatusInternal                   },
    { 0xFD54u,    ENABLE, 3u, DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidReadAntiPinchAdaptation                    },
    { 0xFD55u,    ENABLE, 3u, DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidReadAntiPinchAttention                     }
};

const UDSA_CmdByIdentifier_Service_t UDSA_WriteDataByIdentifier[MAX_NUM_DID_WRITE] =        /*Servizio 2E - 25 DID */
{
/* +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+
   |   DID     |  En   |RxDL |                           Session                                                                    | Diag type   |                      Callback Function                |
   |           |       |     |                                                                                                      |             |                                                       |
   +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+*/
  /* Configuration */
    { 0x0134u,   ENABLE,   7u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                         , UDSA_ADS_PHYS, Udsa_DidWritePillarCalibration                     },
    { 0x2023u,   ENABLE,   0u,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                       , UDSA_ADS_PHYS, Udsa_DidWriteProxiData                             },
    { 0xF180u,   ENABLE,  17u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteBootSoftwareIdentification            },
    { 0xF181u,   ENABLE,  17u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteApplicationSoftwareIdentification     },
    { 0xF182u,   ENABLE,  17u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteApplicationDataIdentification         },
    { 0xF183u,   ENABLE,  16u,  DIAG_SUPPL_SESSION | DIAG_PROGRAMMING_SESSION                                                         , UDSA_ADS_PHYS, Udsa_DidWriteBootSoftwareFingerprint               },
    { 0xF184u,   ENABLE,  16u,  DIAG_SUPPL_SESSION | DIAG_PROGRAMMING_SESSION                                                         , UDSA_ADS_PHYS, Udsa_DidWriteApplSoftwareFingerprint               },
    { 0xF185u,   ENABLE,  16u,  DIAG_SUPPL_SESSION | DIAG_PROGRAMMING_SESSION                                                         , UDSA_ADS_PHYS, Udsa_DidWriteApplicationDataFingerprint            },
    { 0xF187u,   ENABLE,  14u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVehicleManufacturerSparePartNumber    },
    { 0xF188u,   ENABLE,  14u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVehicleManufECUSoftwareNumber         },
    { 0xF18Au,   ENABLE,  13u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVehManEcuSwCalN                       },
    { 0xF18Bu,   ENABLE,  13u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVehManEcuSwAppN                       },
    { 0xF18Cu,   ENABLE,  18u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteEcuSerialNumber                       },
    { 0xF190u,   ENABLE,  20u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVINOriginal                           },
    { 0xF191u,   ENABLE,  14u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteVehicleManufacECUHardwareNumber       },
    { 0xF192u,   ENABLE,  14u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteSystemSupplierEcuHardwareNumber       },
    { 0xF193u,   ENABLE,   4u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteSystemSupplEcuHWVerNumber             },
    { 0xF194u,   ENABLE,  14u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteSystemSupplierEcuSoftwareNumber       },
    { 0xF195u,   ENABLE,   5u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteSystemSupplEcuSWVerNumber             },
    { 0xF196u,   ENABLE,   9u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteHomologationCode                      },
    { 0xF1A4u,   ENABLE,   9u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                         , UDSA_ADS_PHYS, Udsa_DidWriteSincomAndFactory                      },
    { 0xF1A5u,   ENABLE,   8u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteISOCode                               },
    { 0xFD23u,   ENABLE,  13u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                         , UDSA_ADS_PHYS, Udsa_DidWriteHeatTemp                              },
    { 0xFD24u,   ENABLE,  19u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                         , UDSA_ADS_PHYS, Udsa_DidWriteHeatTime                              },
    { 0xFD25u,   ENABLE,   8u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                         , UDSA_ADS_PHYS, Udsa_DidWriteHeatDuty                              },
    { 0xFD34u,   ENABLE,   5u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidWriteNominalStroke                         },
    { 0xFD36u,   ENABLE,   4u,  DIAG_SUPPL_SESSION | DIAG_EXTENDED_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidWriteAntiPinchThresholds                   },
    { 0xFD50u,   ENABLE,   5u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteEquipmentSelection                    },
    { 0xFD51u,   ENABLE,  13u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteEquipmentConfiguration                },
    { 0xFD54u,   ENABLE,   4u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteAntiPinchAdaptation                   },
    { 0xFD55u,   ENABLE,   4u,  DIAG_EXTENDED_SESSION | DIAG_SUPPL_SESSION                                                            , UDSA_ADS_PHYS, Udsa_DidWriteAntiPinchAttention                    },
    { 0xFDF1u,   ENABLE,  10u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_DidWriteEraseEeprom                           }
};

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/******************************************************************************/
/*     Read Callback                                                          */
/******************************************************************************/
/******************************************************************************/
/*                            Vin Odometer            (DID = 0x0103)          */
/******************************************************************************/
static u08 Udsa_DidReadVINOdometer(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  Diag_Response[3] = EERAM_VINOdometer.VINOdometerCount;
  Diag_Response[4] = EERAM_VINOdometer.VINOdometerLockStatus;

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                         Read ECU inputs            (DID = 0x0131)          */
/******************************************************************************/
static u08 Udsa_DidReadEcuInputs(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  //keys status
  Diag_Response[3u + Diag_Resp_MRDI]  = (u08)(((S_ON == DINP_GetState(DINP_Slide_FW)) << 7u) |
                                      ((S_ON == DINP_GetState(DINP_Slide_BW))   << 6u) |
                                      ((S_ON == DINP_GetState(DINP_Tilt_UP))    << 5u) |
                                      ((S_ON == DINP_GetState(DINP_Tilt_DW))    << 4u) |
                                      ((S_ON == DINP_GetState(DINP_Lift_UP))    << 3u) |
                                      ((S_ON == DINP_GetState(DINP_Lift_DW))    << 2u) |
                                      ((S_ON == DINP_GetState(DINP_Back_FW))    << 1u) |
                                      ((S_ON == DINP_GetState(DINP_Back_BW))        ));


#if 0   /* Predisposizione per lo Smart Switch */
  if(DINP_GetState(DINP_SS_5) == S_ON)
  {
    Diag_Response[4u + Diag_Resp_MRDI]  =  0x05u;
  }
  else if(DINP_GetState(DINP_SS_4) == S_ON)
  {
    Diag_Response[4u + Diag_Resp_MRDI]  =  0x04u;
  }
  else if(DINP_GetState(DINP_SS_3) == S_ON)
  {
    Diag_Response[4u + Diag_Resp_MRDI]  =  0x03u;
  }
  else if(DINP_GetState(DINP_SS_2) == S_ON)
  {
    Diag_Response[4u + Diag_Resp_MRDI]  =  0x02u;
  }
  else if(DINP_GetState(DINP_SS_1) == S_ON)
  {
    Diag_Response[4u + Diag_Resp_MRDI]  =  0x01u;
  }
  else
#endif

  //Smart switch status
  Diag_Response[4u + Diag_Resp_MRDI]  =  0x00u;// Bit7-6 (Not Used) Easy Entry
                                               // Bit5-4 (Not Used) Equipment configuration
                                               // Bit3   (Not Used) Driver/Passenger
                                               // Bit2-0 (Not Used) Smart switch status
#if 0
  // driver/passenger
  if(LPMS_GetMsmEcuType() == LPMS_MSM_ECU_PASSENGER )
  {
    //Passenger
    Diag_Response[4u + Diag_Resp_MRDI] |= 0x08u;
  }

  //Equipment configuration
  Diag_Response[4u + Diag_Resp_MRDI] |= (((u08)LPMS_GetMsmEquipment()) << 4u);

  // Easy entry code
  Diag_Response[4u + Diag_Resp_MRDI] |= ((DISPA_GetEasyEntryCode())<<6u);
#endif
  //Heating level
  Diag_Response[5u + Diag_Resp_MRDI] = 0x00U;

  //Fan level
  Diag_Response[6u + Diag_Resp_MRDI] = 0x00U;

  Diag_Response[7u + Diag_Resp_MRDI] = 0x00U;// Bit7 (Not Used) SBR
                                             // Bit6 (Not Used) Belt Switch
                                             // Bit5 (Not Used) Cushion Forward Key
                                             // Bit4 (Not Used) Cushion Backward Key
                                             // Bit3 (Not Used) Steering Wheel Up
                                             // Bit2 (Not Used) Steering Wheel Down
                                             // Bit1 (Not Used) Steering Wheel Forward
                                             // Bit0 (Not Used) Steering Wheel Backward

  Diag_Response[8u + Diag_Resp_MRDI]  = (u08)(0x00U                                 | // Bit7-4 (Not Used) Spare
                                      ((S_ON == DINP_GetState(DINP_Mem3))    << 3u) | // Bit3 Memory3
                                      ((S_ON == DINP_GetState(DINP_Mem2))    << 2u) | // Bit2 Memory2
                                      ((S_ON == DINP_GetState(DINP_Mem1))    << 1u)); // Bit1 Memory1
                                                                                      // Bit0 (Not Used) hall sensor end stroke

  Diag_Response_Ln = 9U;

  return ret_val;
}

/******************************************************************************/
/*                         Read ECU outputs           (DID = 0x0132)          */
/******************************************************************************/
static u08 Udsa_DidReadEcuOutputs(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK; 

  Diag_Response[3u + Diag_Resp_MRDI] = (u08)(((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdSlideFd))      << 7u) | //Slide Forward
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdTiltSlideCom)) << 6u) | //Slide Backward
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdTiltUp))       << 5u) | //Tilt Up
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdTiltSlideCom)) << 4u) | //Tilt Down
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdLiftUp))       << 3u) | //Lift Up
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdLiftBackrCom)) << 2u) | //Lift Down
                                       ((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdBackrFd))      << 1u) | //Bakrest Forward
                                       ( L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdLiftBackrCom)));         //Bakrest Backward

  Diag_Response[4u + Diag_Resp_MRDI] = 0x00U;// Bit7 (Not Used) Cushion Forward
                                             // Bit6 (Not Used) Cushion Backwarda
                                             // Bit5 (Not Used) Headrest Up
                                             // Bit4 (Not Used) Headrest Down
                                             // Bit3 (Not Used) Lumbar V Up
                                             // Bit2 (Not Used) Lumbar V Down
                                             // Bit1 (Not Used) Lumbar H Forward
                                             // Bit0 (Not Used) Lumbar H Backward

  Diag_Response[5u + Diag_Resp_MRDI] = 0x00U |                                              // Bit7, Bit6 (Not Used), Bit5  (Not Used) Fan Power
                                       (u08)(((L_HIGH == (u08)DIOD_GetLevel(DIOD_CmdRelProtEN)) << 4u));// Bit4 Protection relay
                                                                                            // Bit3 (Not Used) Bolster Cushion Deflate
                                                                                            // Bit2 (Not Used) Bolster Cushion Inlate
                                                                                            // Bit1 (Not Used) Bolster Backrest Deflate
                                                                                            // Bit0 (Not Used) Bolster Backrest Inflate

  Diag_Response[6u + Diag_Resp_MRDI] = 0x00U;// Bit7 (Not Used)
                                             // Bit6 (Not Used)
                                             // Bit5 (Not Used) Belt Carrier Forward
                                             // Bit4 (Not Used) Belt Carrier Backward
                                             // Bit3 (Not Used) Steering wheel V Up
                                             // Bit2 (Not Used) Steering wheel V Down
                                             // Bit1 (Not Used) Steering wheel H Forward
                                             // Bit0 (Not Used) Steering wheel H Backward


  Diag_Response[7u + Diag_Resp_MRDI] = PWMC_GetDuty(PWMC_HeatDrv);   //Heater Driver % duty cyle
  Diag_Response[8u + Diag_Resp_MRDI] = PWMC_GetDuty(PWMC_HeatPass);  //Heater Passenger % duty cyle
  Diag_Response[9u + Diag_Resp_MRDI] = PWMC_GetDuty(PWMC_HeatSteer); //Heater Steering % duty cyle
  Diag_Response[10u + Diag_Resp_MRDI] = 0x00U;                       //(Not Used) Fan backrest % duty cyle
  Diag_Response[11u + Diag_Resp_MRDI] = 0x00U;                       //(Not Used) Fan cuchion % duty cyle

  Diag_Response_Ln = 12U;

  return ret_val;
}

/******************************************************************************/
/*                     Heater Current                 (DID = 0x0133)          */
/******************************************************************************/
static u08 Udsa_DidReadHeaterCurrent(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u16 calc_Ia;

    /* Current Conversion is (0,1 A/ bit)

      I_A = (ADCval * 0,332)

      Using 33 instead of 33,2 */

  calc_Ia = (ADCC_GetChnAvrgData(ADCC_HeatDrvFbk) * 33u) / 100U;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)calc_Ia;

  calc_Ia = (ADCC_GetChnAvrgData(ADCC_HeatPassFbk) * 33u) / 100U;

  Diag_Response[4U + Diag_Resp_MRDI] = (u08)calc_Ia;

  calc_Ia = (ADCC_GetChnAvrgData(ADCC_HeatSteerFbk) * 33u) / 100U;

  Diag_Response[5U + Diag_Resp_MRDI] = (u08)calc_Ia;

  Diag_Response_Ln = 6U;

  return ret_val;
}

/******************************************************************************/
/*                  Pillar Calibration                (DID = 0x0134)          */
/******************************************************************************/
static u08 Udsa_DidReadPillarCalibration(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = EERAM_ConfigModel.PillarPosition;
  Diag_Response[3U + Diag_Resp_MRDI] = tmp16.bytes[1];
  Diag_Response[4U + Diag_Resp_MRDI] = tmp16.bytes[0];

  tmp16.word = EERAM_ConfigModel.Welcome_Distance;
  Diag_Response[5U + Diag_Resp_MRDI] = tmp16.bytes[1];
  Diag_Response[6U + Diag_Resp_MRDI] = tmp16.bytes[0];

  Diag_Response_Ln = 7U;

  return ret_val;
}

/******************************************************************************/
/*                          Read Vehicle Speed        (DID = 0x1002)          */
/******************************************************************************/
static u08 Udsa_DidReadVehicleSpeed(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte speed;

  speed.word = FUNP_GetVehicleSpeed();

  Diag_Response[3U + Diag_Resp_MRDI] = speed.bytes[1u]; // High byte
  Diag_Response[4U + Diag_Resp_MRDI] = speed.bytes[0u]; // Low  byte

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                         Read Battery Voltage       (DID = 0x1004)          */
/******************************************************************************/
static u08 Udsa_DidReadBatteryVoltage(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte calc_vbat;

  calc_vbat.word = FUNP_GetBatteryVoltage();

  Diag_Response[3U + Diag_Resp_MRDI] = calc_vbat.bytes[1u];
  Diag_Response[4U + Diag_Resp_MRDI] = calc_vbat.bytes[0u];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                         ECU Time STamps RAM       (DID = 0x1008)          */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeStampsRAM(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u32 Udsa_EcuTimeStamps;

  Udsa_EcuTimeStamps = DDMP_GetEcuTimeStamps();


   Diag_Response[3U + Diag_Resp_MRDI] = (u08)((Udsa_EcuTimeStamps & 0xFF000000u) >> 24u);
   Diag_Response[4U + Diag_Resp_MRDI] = (u08)((Udsa_EcuTimeStamps & 0x00FF0000u) >> 16u);
   Diag_Response[5U + Diag_Resp_MRDI] = (u08)((Udsa_EcuTimeStamps & 0x0000FF00u) >>  8u);
   Diag_Response[6U + Diag_Resp_MRDI] = (u08)( Udsa_EcuTimeStamps & 0x000000FFu        );

  Diag_Response_Ln = 7U;

  return ret_val;
}

/******************************************************************************/
/*              ECU Time STamps RAM From KeyOn       (DID = 0x1009)           */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeStampsFromKeyOnRAM(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u16 Udsa_EcuTimeStampsFromKeyOn;

  Udsa_EcuTimeStampsFromKeyOn = DDMP_GetEcuTimeStampsFromKeyOn();

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((Udsa_EcuTimeStampsFromKeyOn & 0xFF00u) >> 8u);
  Diag_Response[4U + Diag_Resp_MRDI] = (u08)( Udsa_EcuTimeStampsFromKeyOn & 0x00FFu       );

  Diag_Response_Ln = 5U;

  return ret_val;

}

/******************************************************************************/
/*           Read Check EOL Configuration Data        (DID = 0x102A)          */
/******************************************************************************/
static u08 Udsa_DidReadCheckEOLConfigurationData(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_EOL_CHECK; i++)
  {
    Diag_Response[3U + Diag_Resp_MRDI + i] = EERAM_CheckEOLConfData[i];
  }

  Diag_Response_Ln = UDSA_LN_EOL_CHECK + 3U;

  return (ret_val);
}

/******************************************************************************/
/*                Read Operational Mode Status   (DID = 0x1921)               */
/******************************************************************************/
static u08 Udsa_DidReadOperationalModeStatus(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  DDMP_GetOperationalModeStatus(&Diag_Response[3U+Diag_Resp_MRDI], DDMP_OP_MODE);

  Diag_Response_Ln = DDMP_OP_MODE+3U;

  return ret_val;
}

/******************************************************************************/
/*              Read Number of flash rewriting       (DID = 0x2003)           */
/******************************************************************************/
static u08 Udsa_DidReadNumberOfFlashRewrite(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_EcuStatusInfo.NumFlashRewrite;

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*              Read ECU Time Stamps EEPROM        (DID = 0x2008)             */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeStampsEEPROM(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeStamps & 0xFF000000u) >> 24u);
  Diag_Response[4U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeStamps & 0x00FF0000u) >> 16u);
  Diag_Response[5U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeStamps & 0x0000FF00u) >>  8u);
  Diag_Response[6U + Diag_Resp_MRDI] = (u08)( EERAM_EcuStatusInfo.EcuTimeStamps & 0x000000FFu        );

  Diag_Response_Ln = 7U;

  return ret_val;
}

/******************************************************************************/
/*     Read ECU Time Stamps From KeyOn EEPROM        (DID = 0x2009)           */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeStampsKeyOnEEPROM(u08 *Data, u16 Length)  //FT: ad ogni Key ON, il contenuto dell’RDI $2009 rappresenta il valore del ciclo precedente.
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeStampsFromKeyOn & 0xFF00u) >> 8u);
  Diag_Response[4U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeStampsFromKeyOn & 0x00FFu)    );

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                         Read Key On Counter        (DID = 0x200A)          */
/******************************************************************************/
static u08 Udsa_DidReadKeyOnCounterEEPROM(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.KeyOnCnt & 0xFF00u) >> 8u); // High byte
  Diag_Response[4U + Diag_Resp_MRDI] = (u08) (EERAM_EcuStatusInfo.KeyOnCnt & 0x00FFu)       ; // Low byte

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*     Read ECU Time Stamps From KeyOn EEPROM        (DID = 0x200B)           */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeFirstDTCDetectionEEPROM(u08 *Data, u16 Length) //FT: copia dell'RDI 1008 alla validazione del primo DTC detectato. Da resettare in caso di clear DTC
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection & 0xFF000000u) >> 24u);
  Diag_Response[4U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection & 0x00FF0000u) >> 16u);
  Diag_Response[5U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection & 0x0000FF00u) >>  8u);
  Diag_Response[6U + Diag_Resp_MRDI] = (u08)( EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection & 0x000000FFu    );

  Diag_Response_Ln = 7U;

  return ret_val;
}

/******************************************************************************/
/*     Read ECU Time Stamps From KeyOn EEPROM        (DID = 0x200C)           */
/******************************************************************************/
static u08 Udsa_DidReadECUTimeStamps1DTCDetectEEPROM(u08 *Data, u16 Length)  //FT: copia dell'RDI 1009 alla validazione del primo DTC detectato. Da resettare in caso di clear DTC
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeFromKeyOn1DTCDetect & 0xFF00u) >> 8u);
  Diag_Response[4U + Diag_Resp_MRDI] = (u08)((EERAM_EcuStatusInfo.EcuTimeFromKeyOn1DTCDetect & 0x00FFu)     );

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                Read Programming Status EEPROM\FLASH   (DID = 0x2010)          */
/******************************************************************************/
static u08 Udsa_DidReadProgrammingStatus(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_PROG_STATUS; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ProgStatus[i];
  }

  Diag_Response_Ln = UDSA_LN_PROG_STATUS+3U;
  return ret_val;
}

/******************************************************************************/
/*                            VIN LOCK State          (DID = 0x2013)          */
/******************************************************************************/
static u08 Udsa_DidReadVINLockState(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = VF607_GetVINLock();

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*           Read ECU Proxi Data                      (DID = 0x2024)          */
/******************************************************************************/
static u08 Udsa_DidReadECUProxiData(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  /* CR06303 */
  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_SysConfigProxy.IgnitionPreStartLogic;
  Diag_Response[3U + Diag_Resp_MRDI + 1U] = FUNP_GetCountryCode();

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*           Read Proxi write Counter                      (DID = 0x292E)     */
/******************************************************************************/
static u08 Udsa_DidReadProxiWriteCounter(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_SysConfigProxy.WriteCounter;

  Diag_Response_Ln = 4U;

  return (ret_val);
}

/******************************************************************************/
/*                Read Boot Software Identification   (DID = 0xF180)          */
/******************************************************************************/
static u08 Udsa_DidReadBootSoftwareIdentification(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_BOOT_SW_ID; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_BootSwId[i];
  }

  Diag_Response_Ln = UDSA_LN_BOOT_SW_ID+3U;
  return ret_val;
}

/******************************************************************************/
/*          Read Application Software Identification  (DID = 0xF181)          */
/******************************************************************************/
static u08 Udsa_DidReadApplicationSoftwareIdentification(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_APPL_SW_ID; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ApplSwId[i];
  }

  Diag_Response_Ln = UDSA_LN_APPL_SW_ID+3U;
  return ret_val;
}

/******************************************************************************/
/*          Read Application Data Identification  (DID = 0xF182)              */
/******************************************************************************/
static u08 Udsa_DidReadApplicationDataIdentification(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_APPL_DATA_ID; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ApplDataId[i];
  }

  Diag_Response_Ln = UDSA_LN_APPL_DATA_ID+3U;
  return ret_val;
}

/******************************************************************************/
/*          Read Boot Software Fingerprint  (DID = 0xF183)                    */
/******************************************************************************/
static u08 Udsa_DidReadBootSoftwareFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_BOOT_FINGER; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_BootSwFinger[i];
  }

  Diag_Response_Ln = UDSA_LN_BOOT_FINGER+3U;
  return ret_val;
}

/******************************************************************************/
/*          Read Application Software Fingerprint  (DID = 0xF184)             */
/******************************************************************************/
static u08 Udsa_DidReadApplSoftwareFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_APPL_FINGER; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ApplSwFinger[i];
  }

  Diag_Response_Ln = UDSA_LN_APPL_FINGER+3U;
  return ret_val;
}

/******************************************************************************/
/*          Read Application Data Fingerprint  (DID = 0xF185)                 */
/******************************************************************************/
static u08 Udsa_DidReadApplicationDataFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_DATA_FINGER; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ApplDataFinger[i];
  }

  Diag_Response_Ln = UDSA_LN_DATA_FINGER+3U;
  return ret_val;
}

/******************************************************************************/
/*        Read Active Diagn Session Data Identifier   (DID = 0xF186)          */
/******************************************************************************/
static u08 Udsa_DidReadActiveDiagnSessionDataIdentifier(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  switch (UDSA_DiagSession)
  {
  case DIAG_DEFAULT_SESSION:
    Diag_Response[3U + Diag_Resp_MRDI] = UDSA_DEFAULT_SESSION;
    break;

  case DIAG_EXTENDED_SESSION:
    Diag_Response[3U + Diag_Resp_MRDI] = UDSA_EXTENDED_SESSION;
    break;

  case DIAG_EOL_SESSION:
    Diag_Response[3U + Diag_Resp_MRDI] = UDSA_EOL_SESSION;
    break;

  case DIAG_SUPPL_SESSION:
    Diag_Response[3U + Diag_Resp_MRDI] = UDSA_SUPPL_SESSION;
    break;

  default:
    Diag_Response[3U + Diag_Resp_MRDI] = UDSA_NO_SESSION;
    break;
  }

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*       Read Vehicle Manufacturer Spare Part Number  (DID = 0xF187)          */
/******************************************************************************/
static u08 Udsa_DidReadVehicleManufacturerSparePartNumber(u08 *Data, u16 Length)
{
  uint8_t ret_val = SERVICE_OK;
  uint8_t i = 0U;

  for (i=0U; i <  UDSA_LN_SPARE_PART_NUMBER ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VehManSparePartN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_SPARE_PART_NUMBER+3U;

  return ret_val;
}

/******************************************************************************/
/*     Read Vehicle Manufacturing ECU Software Number (DID = 0xF188)          */
/******************************************************************************/
static u08 Udsa_DidReadVehicleManufECUSoftwareNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_VEH_MAN_ECU_SW_NUM ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VehManEcuSwN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_VEH_MAN_ECU_SW_NUM+3U;

  return ret_val;
}

/******************************************************************************/
/*                Read ECU Manufacturing Date         (DID = 0xF18A)          */
/******************************************************************************/
static u08 Udsa_DidReadVehManEcuSwCalN(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VehManEcuSwCalN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM+3U;

  return ret_val;
}

/******************************************************************************/
/*                Read ECU Manufacturing Date         (DID = 0xF18B)          */
/******************************************************************************/
static u08 Udsa_DidReadVehManEcuSwAppN(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_VEH_MAN_ECU_SW_APP_NUM; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VehManEcuSwAppN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_VEH_MAN_ECU_SW_APP_NUM+3U;

  return ret_val;
}

/******************************************************************************/
/*                    Read Ecu Serial Number          (DID = 0xF18C)          */
/******************************************************************************/
static u08 Udsa_DidReadEcuSerialNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_SERIAL_NUMBER; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_EcuSerialNum[i];
  }

  Diag_Response_Ln = UDSA_LN_SERIAL_NUMBER+3U;

  return ret_val;
}

/******************************************************************************/
/*                             Read VIN Original      (DID = 0xF190)          */
/******************************************************************************/
static u08 Udsa_DidReadVINOriginal(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_VIN ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VINOriginal.VINX[i] ;
  }

  Diag_Response_Ln = UDSA_LN_VIN+3U;

  return ret_val;
}

/******************************************************************************/
/*     Read Vehicle Manufacturer ECU Hardware Number  (DID = 0xF191)          */
/******************************************************************************/
static u08 Udsa_DidReadVehicleManECUHWNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_ECU_HW_NUMBER ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VehManEcuHwN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_ECU_HW_NUMBER+3U;

  return ret_val;
}

/******************************************************************************/
/*        Read System Supplier Ecu Hardware Number    (DID = 0xF192)          */
/******************************************************************************/
static u08 Udsa_DidReadSystemSupplierEcuHardwareNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_SYS_SUP_ECU_HW_NUM ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_SysSuppEcuHwN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_SYS_SUP_ECU_HW_NUM+3U;

  return ret_val;
}

/******************************************************************************/
/*   Read System Supplier Ecu Hardware Version Number (DID = 0xF193)          */
/******************************************************************************/
static u08 Udsa_DidReadSystemSupplierEcuHWVerNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_SysSuppEcuHwVerN;

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*           Read System Supplier Ecu Software Number (DID = 0xF194)          */
/******************************************************************************/
static u08 Udsa_DidReadSystemSupplierEcuSoftwareNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_SYS_SUP_ECU_SW_NUM ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_SysSuppEcuSwN[i] ;
  }

  Diag_Response_Ln = UDSA_LN_SYS_SUP_ECU_SW_NUM+3U;

  return ret_val;
}

/******************************************************************************/
/*   Read System Supplier Ecu Software Version Number (DID = 0xF195)          */
/******************************************************************************/
static u08 Udsa_DidReadSystemSupplierEcuSWVerNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  Diag_Response[3U + Diag_Resp_MRDI]= EERAM_SysSuppEcuSwVerN[0];
  Diag_Response[4U + Diag_Resp_MRDI]= EERAM_SysSuppEcuSwVerN[1];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*            Read ExhaustRegulationOrTypeApprovalNumber      (DID = 0xF196)  */
/******************************************************************************/
static u08 Udsa_DidReadHomologationCode(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i <  UDSA_LN_HOMOLOG ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_HomologationCode[i] ;
  }

  Diag_Response_Ln = UDSA_LN_HOMOLOG+3U;

  return ret_val;
}

/******************************************************************************/
/*                     Read SincomAndFactory          (DID = 0xF1A4)          */
/******************************************************************************/
static u08 Udsa_DidReadSincomAndFactory(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_SIN_FACTORY ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_SincomAndFactory[i] ;
  }

  Diag_Response_Ln = UDSA_LN_SIN_FACTORY + 3U;

  return ret_val;
}

/******************************************************************************/
/*                     Read ISOCode                   (DID = 0xF1A5)          */
/******************************************************************************/
static u08 Udsa_DidReadISOCode(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_ISO ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_ISOCode[i] ;
  }

  Diag_Response_Ln = UDSA_LN_ISO + 3U;

  return ret_val;
}

/******************************************************************************/
/*                     Read Identification Code          (DID = 0xF1A0)       */
/******************************************************************************/
static u08 Udsa_DidReadIdentificationCode(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i,j;
  /*F187*/
  j = 0U;
  for (i=0U; i <  UDSA_LN_SPARE_PART_NUMBER ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_VehManSparePartN[i] ;
    j++;
  }
  /*F190*/
  for (i=0U; i <  UDSA_LN_VIN  ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_VINOriginal.VINX[i] ;
    j++;
  }
  /*F192*/
  for (i=0U; i <  UDSA_LN_SYS_SUP_ECU_HW_NUM ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_SysSuppEcuHwN[i] ;
    j++;
  }
  /*F193*/
  Diag_Response[3U+j+(u08)Diag_Resp_MRDI]= EERAM_SysSuppEcuHwVerN;
  j++;
  /*F194*/
  for (i=0U; i <  UDSA_LN_SYS_SUP_ECU_SW_NUM ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_SysSuppEcuSwN[i] ;
    j++;
  }
  /*F195*/
  Diag_Response[3U + Diag_Resp_MRDI+j] = EERAM_SysSuppEcuSwVerN[0];
  j++;
  Diag_Response[3U + Diag_Resp_MRDI+j] = EERAM_SysSuppEcuSwVerN[1];
  j++;
  /*F196*/
  for (i=0U; i <  UDSA_LN_HOMOLOG ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_HomologationCode[i] ;
    j++;
  }
  /*F1A5*/
  for (i=0U; i < UDSA_LN_ISO ; i++)
  {
    Diag_Response[3U+j+(u08)Diag_Resp_MRDI] = EERAM_ISOCode[i] ;
    j++;
  }

  Diag_Response_Ln = (u16)(j+3U);

  return ret_val;
}

/******************************************************************************/
/*                    Read EOL Configuration Code (DID = 0xF1A1)              */
/******************************************************************************/
static u08 Udsa_DidReadEOLConfigurationCode(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;
  u08 j;

  j=0U;
  /* 19.01.2015 - FZ - Bug Fix - Le ECU che sono proxabili devono avere il valore di questo bit a EOL_PROGRAMMING */
  for (i=0U; i <  UDSA_LN_CONF_DATA ; i++)
  {
    Diag_Response[3+i + Diag_Resp_MRDI] = (u08)((EERAM_SysConfigProxy.ConfCode[j+1]&0x0F) + (u08)((EERAM_SysConfigProxy.ConfCode[j]<<4)&0xF0)) ;
//    Diag_Response[3+i + Diag_Resp_MRDI] = EERAM_SysConfigProxy.ConfCode[i] ;
    j+=2U;
  }

  i--;
  j-=2U;
  Diag_Response[3+i + Diag_Resp_MRDI] = (0x00 + (u08)((EERAM_SysConfigProxy.ConfCode[j]<<4)&0xF0));   /* Il 12imo Nible deve essere messo a ZERO */

  Diag_Response_Ln = UDSA_LN_CONF_DATA + 3U;

  return (ret_val);
}

/******************************************************************************/
/*                     Read VIN Current               (DID = 0xF1B0)          */
/******************************************************************************/
static u08 Udsa_DidReadVINCurrent(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i=0u;

  for (i=0U; i < UDSA_LN_VIN ; i++)
  {
    Diag_Response[3U+i+(u08)Diag_Resp_MRDI] = EERAM_VINCurrent.VINX[i];
  }

  Diag_Response_Ln = UDSA_LN_VIN + 3U;

  return ret_val;
}

/******************************************************************************/
/*                  Read NTC Driver temperatures     (DID = 0xFD20)           */
/******************************************************************************/
static u08 Udsa_DidReadNTCDrvTemperature(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = (u16)SNSP_GetTemperature(SNSP_SEAT_DRV);
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*               Read NTC Passenger temperatures     (DID = 0xFD21)           */
/******************************************************************************/
static u08 Udsa_DidReadNTCPsgTemperature(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = (u16)SNSP_GetTemperature(SNSP_SEAT_PASS);
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*               Read NTC Steering temperatures      (DID = 0xFD22)           */
/******************************************************************************/
static u08 Udsa_DidReadNTCSteerTemperature(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = (u16)SNSP_GetTemperature(SNSP_STEER_WHEEL);
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*            Read Heat temperature parameters      (DID = 0xFD23)            */
/******************************************************************************/
static u08 Udsa_DidReadHeatTemp(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;
//  int16_t* temp = NULL;
//  u08 i;

  /*** The parameters are sent in the following order: */
  /* 1. Temp_lim */
  /* 2. Temp_range_min*/
  /* 3. Temp_range_max*/
  /* 4. Max_Av_Surf_Temp*/
  /* 5. Max_Av_Surf_Temp_StW*/
  
//  temp = &EERAM_HeatTempParam.Temp_lim;
//
//  for (i=0U;i<5U;i++)
//  {
//    tmp16.word = *temp;
//    Diag_Response[3u + i + Diag_Resp_MRDI] = tmp16.bytes[1u];
//    Diag_Response[4u + i + Diag_Resp_MRDI] = tmp16.bytes[0u];
//    *temp++;
//  }
  
  /*Temp_lim */
  tmp16.word = EERAM_HeatTempParam.Temp_lim;
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*Temp_range_min*/
  tmp16.word = EERAM_HeatTempParam.Temp_range_min;
  Diag_Response[5u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[6u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*Temp_range_max*/
  tmp16.word = EERAM_HeatTempParam.Temp_range_max;
  Diag_Response[7u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[8u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*Max_Av_Surf_Temp*/
  tmp16.word = EERAM_HeatTempParam.Max_Av_Surf_Temp;
  Diag_Response[9u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[10u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*Max_Av_Surf_Temp_StW*/
  tmp16.word = EERAM_HeatTempParam.Max_Av_Surf_Temp_StW;
  Diag_Response[11u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[12u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 13U;

  return ret_val;
}

/******************************************************************************/
/*               Read Heat time parameters      (DID = 0xFD24)                */
/******************************************************************************/
static u08 Udsa_DidReadHeatTime(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;
//  int16_t* temp = NULL;
//  u08 i;

  /*** The parameters are sent in the following order: */
  /* 1. T1 **********/
  /* 2. T_wait_1 ****/
  /* 3. T2 **********/
  /* 4. T3SW ********/
  /* 5. T3HS ********/
  /* 6. T_wait_2 ****/
  /* 7. T4 **********/
  /* 8. T_low *******/
  
//  temp = &(EERAM_HeatTimeParam.T1);
//
//  for (i=0U;i<8U;i++)
//  {
//    tmp16.word = *temp;
//    Diag_Response[3u + i + Diag_Resp_MRDI] = tmp16.bytes[1u];
//    Diag_Response[4u + i + Diag_Resp_MRDI] = tmp16.bytes[0u];
//    *temp++;
//  }

  /*T1 */
  tmp16.word = EERAM_HeatTimeParam.T1;
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T_wait_1*/
  tmp16.word = EERAM_HeatTimeParam.T_wait_1;
  Diag_Response[5u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[6u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T2*/
  tmp16.word = EERAM_HeatTimeParam.T2;
  Diag_Response[7u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[8u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T3SW*/
  tmp16.word = EERAM_HeatTimeParam.T3SW;
  Diag_Response[9u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[10u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T3HS*/
  tmp16.word = EERAM_HeatTimeParam.T3HS;
  Diag_Response[11u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[12u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T_wait_2 */
  tmp16.word = EERAM_HeatTimeParam.T_wait_2;
  Diag_Response[13u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[14u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T4*/
  tmp16.word = EERAM_HeatTimeParam.T4;
  Diag_Response[15u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[16u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  /*T_low*/
  tmp16.word = EERAM_HeatTimeParam.T_low;
  Diag_Response[17u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[18u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 19U;

  return ret_val;
}

/******************************************************************************/
/*               Read Heat duty parameters      (DID = 0xFD25)                */
/******************************************************************************/
static u08 Udsa_DidReadHeatDuty(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  /*** The parameters are sent in the following order: */
  /* 1. D_3 ****/
  /* 2. D_2 ****/
  /* 3. DWL1 ***/
  /* 4. DHL1 ***/
  /* 5. DLL1 ***/
  
  /*D_3 */
  Diag_Response[3u + Diag_Resp_MRDI] = EERAM_HeatDutyParam.D_3;

  /*D_2 */
  Diag_Response[4u + Diag_Resp_MRDI] = EERAM_HeatDutyParam.D_2;

  /*DWL1 */
  Diag_Response[5u + Diag_Resp_MRDI] = EERAM_HeatDutyParam.DWL1;

  /*DHL1 */
  Diag_Response[6u + Diag_Resp_MRDI] = EERAM_HeatDutyParam.DHL1;

  /*DLL1 */
  Diag_Response[7u + Diag_Resp_MRDI] = EERAM_HeatDutyParam.DLL1;

  Diag_Response_Ln = 8U;

  return ret_val;
}

/******************************************************************************/
/*                    Read Seat positions             (DID = 0xFD30)          */
/******************************************************************************/
static u08 Udsa_DidReadSeatPositions(u08 *Data, u16 Length)
{

  u08 ret_val= SERVICE_OK;
  u16 i;

   //DF: This array defines the motor order for response building, see CDD
  static const IPOC_Channel_t PositionToSend[UDSA_NUM_MOTOR] =
  {
    IPOC_Slide,
    IPOC_Tilt,
    IPOC_Lift,
    IPOC_Backres,
  };

  for( i = 0u; i< UDSA_NUM_MOTOR; i++)
  {
    Diag_Response[3U + (i<<1u) + Diag_Resp_MRDI]      = (u08)(EERAM_ContatoreHall[PositionToSend[i]] >> 8u);
    Diag_Response[3U + (i<<1u) + Diag_Resp_MRDI + 1U] = (u08)(EERAM_ContatoreHall[PositionToSend[i]] & 0x00FFu);
  }

  Diag_Response_Ln = 3U + (i<<1u);

  return ret_val;

}

/******************************************************************************/
/*                    Read strokes information        (DID = 0xFD33)          */
/******************************************************************************/
static u08 Udsa_DidReadStrokes(u08 *Data, u16 Length)
{
  UDSA_WordByte tmp16;
  u08 i,j;

  //DF: This array defines the motor order for response building, see CDD
  static const MOTP_Handle_t StrokesToSend[12] =
  {
    MOTP_SLIDE,
    MOTP_MAX_HDL, //Tilt not present
    MOTP_MAX_HDL, //Lift not present
    MOTP_MAX_HDL, //Backrest not present
    MOTP_MAX_HDL, //Lumbar Vertical not present
    MOTP_MAX_HDL, //Lumbar Horizontal not present
    MOTP_MAX_HDL, //Headrest Vertical not present
    MOTP_MAX_HDL, //Headrest Horizontal not present
    MOTP_MAX_HDL, //Cushion not present
    MOTP_MAX_HDL, //Steering wheel H not present
    MOTP_MAX_HDL, //Steering wheel V not present
    MOTP_MAX_HDL, //Belt carrier not pressent
  };

  //slide stroke
  if (EERAM_ConfigModel.Init_MotorSlide == 1u)
  {
    tmp16.word = (u16)EERAM_Measured_Motors_Stroke;
    // Up/Fw stroke
    Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1];
    Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0];
    // Down/Bw stroke
    Diag_Response[5u + Diag_Resp_MRDI] = 0u;
    Diag_Response[6u + Diag_Resp_MRDI] = 0u;
  }
  else
  {
    Diag_Response[3u + Diag_Resp_MRDI] = (u08)(32000>>8);
    Diag_Response[4u + Diag_Resp_MRDI] = (u08)(32000);
    Diag_Response[5u + Diag_Resp_MRDI] = (u08)(-32000>>8);
    Diag_Response[6u + Diag_Resp_MRDI] = (u08)(-32000);
  }

  for( i = 0u; i< 12u; i++)
  {
    if(MOTP_MAX_HDL == ((MOTP_Handle_t)StrokesToSend[i]))
    {
      /* manage not present motors, send 0x0000 */
      // Up/Fw stroke
      j = i << 2u;
      Diag_Response[3u + j + Diag_Resp_MRDI]      = 0u;
      Diag_Response[3u + j + Diag_Resp_MRDI + 1u] = 0u;

      // Dw/bw stroke
      Diag_Response[3u + j + Diag_Resp_MRDI + 2u] = 0u;
      Diag_Response[3u + j + Diag_Resp_MRDI + 3u] = 0u;
    }
    else
    {
      /* strokes already set */
    }
  }

  j = i << 2u;
  
  Diag_Response_Ln = 3U + j;

  return SERVICE_OK;
}

/******************************************************************************/
/*                     Read Nominal stroke   (DID = 0xFD34)                   */
/******************************************************************************/
static u08 Udsa_DidReadNominalStroke(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = EERAM_Nominal_Motors_Stroke;
  Diag_Response[3U + Diag_Resp_MRDI] = tmp16.bytes[1];
  Diag_Response[4U + Diag_Resp_MRDI] = tmp16.bytes[0];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                   Read Anti Pinch Debug values   (DID = 0xFD35)            */
/******************************************************************************/
static u08 Udsa_DidReadAPSADebug(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  //1^ byte -> mappa corrente nel segmento
  tmp16.word = EERAM_Current_Map_Backward[DISPA_GetAntiPinchSegment()];
  Diag_Response[3U + Diag_Resp_MRDI] = tmp16.bytes[1]; //parte alta
  Diag_Response[4U + Diag_Resp_MRDI] = tmp16.bytes[0]; //parte bassa

  //2^ byte -> soglia attenzione
  tmp16.word = DISPA_GetAttentionThreshold();
  Diag_Response[5U + Diag_Resp_MRDI] = tmp16.bytes[1]; //parte alta
  Diag_Response[6U + Diag_Resp_MRDI] = tmp16.bytes[0]; //parte bassa

  //3^ byte -> soglia antipinzamento
  tmp16.word = DISPA_GetAntiPinchThreshold();
  Diag_Response[7U + Diag_Resp_MRDI] = tmp16.bytes[1]; //parte alta
  Diag_Response[8U + Diag_Resp_MRDI] = tmp16.bytes[0]; //parte bassa

  //4^ byte -> valore corrente attualmente assorbito
  tmp16.word = MOTP_GetMotorsCurrent();
  Diag_Response[9U + Diag_Resp_MRDI] = tmp16.bytes[1]; //parte alta
  Diag_Response[10U + Diag_Resp_MRDI] = tmp16.bytes[0]; //parte bassa

  Diag_Response_Ln = 11U;

  return ret_val;
}

/******************************************************************************/
/*                 Read Anti Pinch Thresholds   (DID = 0xFD36)                */
/******************************************************************************/
static u08 Udsa_DidReadAntiPinchThresholds(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  /* Backwards Anti Pinch Threshold */
  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_Threshold_Antipinch_Backward;

  Diag_Response_Ln = 4U;

  return ret_val;
}


/******************************************************************************/
/*              Seat and mirrors memory store           (DID = 0xFD39)        */
/******************************************************************************/
static u08 Udsa_DidReadSeatAndMirrorsMemoryStored(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 memory, motor;
  u08 Udsa_DiagResponseIndex   = 3u + Diag_Resp_MRDI;

  /* the seat memories are sent in the following order */

  /* M1 Slide   */
  /* M1 Tilt    */
  /* M1 Lift    */
  /* M1 Backres */

  /* M2 Slide   */
  /* M2 Tilt    */
  /* M2 Lift    */
  /* M2 Backres */

  /* M3 Slide   */
  /* M3 Tilt    */
  /* M3 Lift    */
  /* M3 Backres */

  for (memory = 1u; memory <= NUM_MEMORIE; memory++)
  {
    for(motor = (IPOC_Channel_t)0u; motor < (IPOC_Channel_t)UDSA_NUM_MOTOR; motor++)
    {
      Diag_Response[Udsa_DiagResponseIndex] = (u08)((EERAM_MemoM[(((memory-1U)*UDSA_NUM_MOTOR) + (uint8_t)motor)] & 0xFF00) >> 8); /* MSB */
      Udsa_DiagResponseIndex++;
      Diag_Response[Udsa_DiagResponseIndex] = (u08)((EERAM_MemoM[(((memory-1U)*UDSA_NUM_MOTOR) + (uint8_t)motor)] & 0x00FF) >> 0); /* LSB */
      Udsa_DiagResponseIndex++;
    }
  }

  /* Mirror memory */
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorMCorr.DrvVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorMCorr.DrvHorizPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorMCorr.PsngrVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorMCorr.PsngrHorizPos);
  Udsa_DiagResponseIndex++;

  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM1.DrvVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM1.DrvHorizPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM1.PsngrVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM1.PsngrHorizPos);
  Udsa_DiagResponseIndex++;

  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM2.DrvVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM2.DrvHorizPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM2.PsngrVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM2.PsngrHorizPos);
  Udsa_DiagResponseIndex++;

  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM3.DrvVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM3.DrvHorizPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM3.PsngrVertPos);
  Udsa_DiagResponseIndex++;
  Diag_Response[Udsa_DiagResponseIndex] = (u08)(EERAM_MirrorM3.PsngrHorizPos);
  Udsa_DiagResponseIndex++;

  Diag_Response_Ln = Udsa_DiagResponseIndex;

  return ret_val;
}

/******************************************************************************/
/*                    Read equipment selection        (DID = 0xFD50)          */
/******************************************************************************/
static u08 Udsa_DidReadEquipmentSelection(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = (u16)EERAM_BproxiValue;
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response_Ln = 5U;

  return ret_val;
}

/******************************************************************************/
/*                  Read equipment configuration      (DID = 0xFD51)          */
/******************************************************************************/
static u08 Udsa_DidReadEquipmentConfiguration(u08 *Data, u16 Length)
{
  uint8_t ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.word = EERAM_BproxiValue;
  Diag_Response[3u + Diag_Resp_MRDI] = tmp16.bytes[1u];
  Diag_Response[4u + Diag_Resp_MRDI] = tmp16.bytes[0u];

  Diag_Response[5u + Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn;
  Diag_Response[6u + Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn;
  Diag_Response[7u + Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn;
  Diag_Response[8u + Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].BackEn;
  Diag_Response[9u + Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn;
  Diag_Response[10u+ Diag_Resp_MRDI]  = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn;
  Diag_Response[11u + Diag_Resp_MRDI] = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn;
  Diag_Response[12u + Diag_Resp_MRDI] = (uint8_t)EERAM_BproxiConfig[EERAM_BproxiValue].AntiPinchEn;

  Diag_Response_Ln = 13U;

  return ret_val;

}

/******************************************************************************/
/*                  Read Operational Mode Status      (DID = 0xFD53)          */
/******************************************************************************/
static u08 Udsa_DidReadOpModeStatusInternal(u08 *Data, u16 Length)
{
  uint8_t ret_val = SERVICE_OK;
  OperationalModeSts_t OpModeSts;

  OpModeSts = VF608_GetOperationalModeSts();

  Diag_Response[3u + Diag_Resp_MRDI] = OpModeSts;

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*                 Read Anti Pinch Adaptation   (DID = 0xFD54)                */
/******************************************************************************/
static u08 Udsa_DidReadAntiPinchAdaptation(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  /* Anti Pinch adaption enabled or not */
  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_AntiPinchAdaptation;

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*                  Read Anti Pinch Attention      (DID = 0xFD55)             */
/******************************************************************************/
static u08 Udsa_DidReadAntiPinchAttention(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  /* Backwards Anti Pinch Threshold */
  Diag_Response[3U + Diag_Resp_MRDI] = EERAM_Threshold_Att_Backward;

  Diag_Response_Ln = 4U;

  return ret_val;
}

/******************************************************************************/
/*     Write Callback                                                         */
/******************************************************************************/

/******************************************************************************/
/*                  Pillar Calibration                (DID = 0x0134)          */
/******************************************************************************/
static u08 Udsa_DidWritePillarCalibration(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp_pillar, tmp_welcome;

  tmp_pillar.bytes[1] = Diag_Requeste[3u];
  tmp_pillar.bytes[0] = Diag_Requeste[4u];

  tmp_welcome.bytes[1] = Diag_Requeste[5u];
  tmp_welcome.bytes[0] = Diag_Requeste[6u];

  if ((tmp_pillar.word > 0u)  && (tmp_pillar.word <= EERAM_Nominal_Motors_Stroke) &&
      (tmp_welcome.word > 0u) && (tmp_welcome.word <= EERAM_Nominal_Motors_Stroke))
  {
    EERAM_ConfigModel.PillarPosition   = tmp_pillar.word;
    EERAM_ConfigModel.Welcome_Distance = tmp_welcome.word;
    EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return ret_val;
}

/******************************************************************************/
/*                         Write PROXI Data           (DID = 0x2023)          */
/******************************************************************************/
static u08 Udsa_DidWriteProxiData(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i,j;
  u08 mask_proxi1 = 0x80U;
  u08 step_proxi1 =  93U; /* Powertrain_Configuration_3 - BYTE 94  - Bit 7-7 -  Ignition_Pre_Start_Logic */
  u08 ProxiPosCountryCode = 106U; /* Car_Configuration_16       - BYTE 107 - Bit 0-7 -  Country_Code */
  u16 ProxiCRC = 0U;
  u08 ResultCRC[UDSA_LN_CRC_PROXI];
  u16 len_calc;
  u08 z = 0U;

  Length -= 3U;  /* N. 3 = di protocollo */

  if (memcmp(&EERAM_CheckEOLConfData[0u], &EEDEF_CheckEOLConfData[0u], UDSA_LN_EOL_CHECK) != 0u)
  {
    memset(&EERAM_CheckEOLConfData[0u], 0u, sizeof(EERAM_CheckEOLConfData));
    EEPP_WriteData(EEPP_HDL_CheckEOLConfData, NULL);
  }
  /*FRAT - NOTA: Length deve essere almeno UDSA_EOL_N_START_CRC (26) altrimenti la sottrazione nell'else qui sotto */
  /* diventa negativa e len_calc assume un valore in overflow */
  if((Length < UDSA_EOL_N_START_CRC/*UDSA_LN_CONF_CODE*/ ) || (Length > UDSA_MAX_PROXI_LEN )) /* cdd EOL data type */
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    len_calc = Length - UDSA_EOL_N_START_CRC + 1u; /* (Length - 26) + 1 */ /*calcola il CRC a partire dal byte 26 per tutti i bytes della proxi*/
    /*NOTA: Length deve essere almeno UDSA_EOL_N_START_CRC (26)*/
    for (i=0U; i < UDSA_LN_CONF_CODE; i++)
    {
      if( (Diag_Requeste[3+i] < 0x30u) || (Diag_Requeste[3+i] > 0x39u))  /* check 1 norma 07337 pag.8 */
      {                                                                  /* ASCII character strings (from 30 to 39 hex) are accepted in the CONFIGURATION CODE field */
        ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
        if(z < 7U)  /* CheckEOLConfigData queue */
        {
          EERAM_CheckEOLConfData[0U+z] = ret_val;
          EERAM_CheckEOLConfData[1U+z] = i+1;
          EERAM_CheckEOLConfData[2U+z] = 0xFFu;
          z+=3U;
        }
      }
    }

    ProxiCRC = FUNP_crc16_little(&Diag_Requeste[28u], len_calc);
    FUNP_ConvertU16ToString(ProxiCRC, ResultCRC); /*converte il CRC calcolato in 5 caratteri ASCII - norma 07337 pag.7*/

    j=UDSA_LN_CRC_PROXI -1U;
    for (i=UDSA_LN_CONF_CODE - UDSA_LN_CRC_PROXI; i < UDSA_LN_CONF_CODE; i++) /* check 4 norma 07337 pag.8*/
    {
      if(ResultCRC[j] != Diag_Requeste[3+i])
      {
        ret_val = REQUEST_OUT_OF_RANGE;
        if(z < 7U)
        {
          EERAM_CheckEOLConfData[0U+z] = ret_val;
          EERAM_CheckEOLConfData[1U+z] = i+1;
          EERAM_CheckEOLConfData[2U+z] = 0xFFu;
          z+=3U;
        }
      }
      j--;
    }

    if(ret_val == SERVICE_OK)
    {
      for (i=0U; i < UDSA_LN_CONF_CODE; i++)
      {
        EERAM_SysConfigProxy.ConfCode[i] = Diag_Requeste[3+i];
      }

      EERAM_SysConfigProxy.IgnitionPreStartLogic = ((Diag_Requeste[3+step_proxi1]) & mask_proxi1);

      FUNP_SetCountryCode((FUNP_ProxiCountriCode_t) Diag_Requeste[3+ProxiPosCountryCode]);

      if(EERAM_SysConfigProxy.WriteCounter != 0xFFu)
      {
        (EERAM_SysConfigProxy.WriteCounter)++;/*RDI 292E*/
      }

      EEPP_WriteData(EEPP_HDL_SysConfigProxy, NULL);
      EEPP_WriteData(EEPP_HDL_Proxi_Country_Code, NULL);
    }
    else /*check (1,4) proxi failed */
    {
      EEPP_WriteData(EEPP_HDL_CheckEOLConfData, NULL);
    }
  }

  return (ret_val);
}

/******************************************************************************/
/*          Write Boot Software Identification        (DID = 0xF180)          */
/******************************************************************************/
static u08 Udsa_DidWriteBootSoftwareIdentification(u08 *Data, u16 Length) /*FRAT: abilitato solo in SUPPL_SESSION*/
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_BOOT_SW_ID; i++)
  {
    EERAM_BootSwId[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_BootSwId, NULL);

  return ret_val;
}

/******************************************************************************/
/*       Write Application Software Identification    (DID = 0xF181)          */
/******************************************************************************/
static u08 Udsa_DidWriteApplicationSoftwareIdentification(u08 *Data, u16 Length) /*FRAT: abilitato solo in SUPPL_SESSION*/
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_APPL_SW_ID; i++)
  {
    EERAM_ApplSwId[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_ApplSwId, NULL);

  return ret_val;
}

/******************************************************************************/
/*          Write Application Data Identification     (DID = 0xF182)          */
/******************************************************************************/
static u08 Udsa_DidWriteApplicationDataIdentification(u08 *Data, u16 Length) /*FRAT: abilitato solo in SUPPL_SESSION*/
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  for (i = 0U; i < UDSA_LN_APPL_DATA_ID; i++)
  {
    EERAM_ApplDataId[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_ApplDataId, NULL);

  return ret_val;
}

/******************************************************************************/
/*               Write Boot Software Fingerprint       (DID = 0xF183)         */
/* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
/******************************************************************************/
static u08 Udsa_DidWriteBootSoftwareFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  if(ECU_SecAccessSts == SEC_ACC_ECU_PROGRAMMING_UNLOCKED)
  {
    for(i=0U; i < UDSA_LN_BOOT_FINGER; i++)
    {
      EERAM_BootSwFinger[i] = Diag_Requeste[3U+i];
    }

    EEPP_WriteData(EEPP_HDL_BootSwFinger, NULL);
  }
  /* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
  else if((UDSA_DiagSession == DIAG_SUPPL_SESSION) /*&&
      (memcmp(&UDSA_MirrorApplSwId[0u],&EERAM_ApplSwId[0u],UDSA_LN_APPL_SW_ID) == 0)*/)
  {
    for(i=0U; i < UDSA_LN_APPL_FINGER; i++)
    {
      EERAM_BootSwFinger[i] = Diag_Requeste[3U+i];
    }

    EEPP_WriteData(EEPP_HDL_BootSwFinger, NULL);
  }
  else
  {
    ret_val = SECURITY_ACCESS_DENIED;
  }

  return ret_val;
}

/******************************************************************************/
/*               Write Application Software Fingerprint       (DID = 0xF184)  */
/* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
/******************************************************************************/
static u08 Udsa_DidWriteApplSoftwareFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  if(ECU_SecAccessSts == SEC_ACC_ECU_PROGRAMMING_UNLOCKED)
  {
    if (UDSA_FingerCount == 0u)
    {
      UDSA_FingerCount = 1U;

      for(i=0U; i < UDSA_LN_APPL_FINGER; i++)
      {
        EERAM_ApplSwFinger[i] = Diag_Requeste[3U+i];
      }

      EEPP_WriteData(EEPP_HDL_ApplSwFinger, NULL);
    }
    else
    {
      ret_val = REQUEST_SEQUENCE_ERROR;
    }
  }
  /* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
  else if((UDSA_DiagSession == DIAG_SUPPL_SESSION) /*&&
      (memcmp(&UDSA_MirrorApplSwId[0u],&EERAM_ApplSwId[0u],UDSA_LN_APPL_SW_ID) == 0)*/)
  {
    for(i=0U; i < UDSA_LN_APPL_FINGER; i++)
    {
      EERAM_ApplSwFinger[i] = Diag_Requeste[3U+i];
    }

    EEPP_WriteData(EEPP_HDL_ApplSwFinger, NULL);
  }
  else
  {
    ret_val = SECURITY_ACCESS_DENIED;
  }

  return ret_val;
}

/******************************************************************************/
/*               Write Application Data Fingerprint       (DID = 0xF185)      */
/* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
/******************************************************************************/
static u08 Udsa_DidWriteApplicationDataFingerprint(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  if(ECU_SecAccessSts == SEC_ACC_ECU_PROGRAMMING_UNLOCKED)
  {
    if(UDSA_FingerCount == 1u)
    {
      UDSA_FingerCount = 2u; /* ApplicationDataFingerprint is the last to be writen into download sequence */

      for(i=0U; i < UDSA_LN_DATA_FINGER; i++)
      {
        EERAM_ApplDataFinger[i] = Diag_Requeste[3U+i];
      }

      EEPP_WriteData(EEPP_HDL_ApplDataFinger, NULL);
    }
    else
    {
      ret_val = REQUEST_SEQUENCE_ERROR;
    }
  }
  /* TODO FZ - REINTRODURRE LA PROTEZIONE IN SCRITTURA                          */
  else if((UDSA_DiagSession == DIAG_SUPPL_SESSION) /*&&
      (memcmp(&UDSA_MirrorApplSwId[0u],&EERAM_ApplSwId[0u],UDSA_LN_APPL_SW_ID) == 0)*/)
  {
    for(i=0U; i < UDSA_LN_APPL_FINGER; i++)
    {
      EERAM_ApplDataFinger[i] = Diag_Requeste[3U+i];
    }

    EEPP_WriteData(EEPP_HDL_ApplDataFinger, NULL);
  }
  else
  {
    ret_val = SECURITY_ACCESS_DENIED;
  }

  return ret_val;

}

/******************************************************************************/
/*       Write Vehicle Manufacturer Spare Part Number  (DID = 0xF187)         */
/******************************************************************************/
static u08 Udsa_DidWriteVehicleManufacturerSparePartNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_SPARE_PART_NUMBER; i++)
  {
    EERAM_VehManSparePartN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VehManSparePartN, NULL);

  return ret_val;
}

/******************************************************************************/
/*     Write Vehicle Manufacturing ECU Software Number (DID = 0xF188)         */
/******************************************************************************/
static u08 Udsa_DidWriteVehicleManufECUSoftwareNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_VEH_MAN_ECU_SW_NUM; i++)
  {
    EERAM_VehManEcuSwN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VehManEcuSwN, NULL);

  return ret_val;
}

/******************************************************************************/
/*                Write ECU Manufacturing Date         (DID = 0xF18A)         */
/******************************************************************************/
static u08 Udsa_DidWriteVehManEcuSwCalN(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM; i++)
  {
    EERAM_VehManEcuSwCalN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VehManEcuSwCalN, NULL);

  return ret_val;
}

/******************************************************************************/
/*                Write ECU Manufacturing Date         (DID = 0xF18B)         */
/******************************************************************************/
static u08 Udsa_DidWriteVehManEcuSwAppN(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_VEH_MAN_ECU_SW_APP_NUM; i++)
  {
    EERAM_VehManEcuSwAppN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VehManEcuSwAppN, NULL);

  return ret_val;
}

/******************************************************************************/
/*                    Write Ecu Serial Number       (DID = 0xF18C)            */
/******************************************************************************/
static u08 Udsa_DidWriteEcuSerialNumber(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_SERIAL_NUMBER; i++)
  {
    EERAM_EcuSerialNum[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_EcuSerialNum, NULL);

  return ret_val;
}

/******************************************************************************/
/*                          Write VIN Original        (DID = 0xF190)          */
/******************************************************************************/
static u08 Udsa_DidWriteVINOriginal(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_VIN; i++)
  {
    EERAM_VINOriginal.VINX[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VINOriginal, NULL);

  return ret_val;
}

/******************************************************************************/
/*        Write System Supplier Ecu Hardware Number    (DID = 0xF191)         */
/******************************************************************************/
static u08 Udsa_DidWriteVehicleManufacECUHardwareNumber (u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_ECU_HW_NUMBER; i++)
  {
    EERAM_VehManEcuHwN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_VehManEcuHwN, NULL);

  return ret_val;

}
/******************************************************************************/
/*        Write System Supplier Ecu Hardware Number    (DID = 0xF192)         */
/******************************************************************************/
static u08 Udsa_DidWriteSystemSupplierEcuHardwareNumber (u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_SYS_SUP_ECU_HW_NUM; i++)
  {
    EERAM_SysSuppEcuHwN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_SysSuppEcuHwN, NULL);

  return ret_val;
}

/******************************************************************************/
/*        Write System Supplier Ecu Hardware Ver Number    (DID = 0xF193)     */
/******************************************************************************/
static u08 Udsa_DidWriteSystemSupplEcuHWVerNumber (u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  EERAM_SysSuppEcuHwVerN = Diag_Requeste[3];
  EEPP_WriteData(EEPP_HDL_SysSuppEcuHwVerN, NULL);

  return ret_val;
}

/******************************************************************************/
/*        Write System Supplier Ecu Software Number       (DID = 0xF194)      */
/******************************************************************************/
static u08 Udsa_DidWriteSystemSupplierEcuSoftwareNumber (u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_SYS_SUP_ECU_SW_NUM; i++)
  {
    EERAM_SysSuppEcuSwN[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_SysSuppEcuSwN, NULL);


  return ret_val;
}

/******************************************************************************/
/*        Write System Supplier Ecu Software Ver Number    (DID = 0xF195)     */
/******************************************************************************/
static u08 Udsa_DidWriteSystemSupplEcuSWVerNumber (u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;

  EERAM_SysSuppEcuSwVerN[0] = Diag_Requeste[3];
  EERAM_SysSuppEcuSwVerN[1] = Diag_Requeste[4];

  EEPP_WriteData(EEPP_HDL_SysSuppEcuSwVerN, NULL);

  return ret_val;
}



/******************************************************************************/
/*            Write ExhaustRegulationOrTypeApprovalNumber     (DID = 0xF196)  */
/******************************************************************************/
static u08 Udsa_DidWriteHomologationCode(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_HOMOLOG; i++)
  {
    EERAM_HomologationCode[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_HomologationCode, NULL);


  return ret_val;
}

/******************************************************************************/
/*                         Write Sincom And Factory   (DID = 0xF1A4)          */
/******************************************************************************/
static u08 Udsa_DidWriteSincomAndFactory(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 i;

  if(VIN_SecAccessSts == SEC_ACC_VIN_UNLOCKED)
  {
    for(i=0U; i < UDSA_LN_SIN_FACTORY; i++)
    {
      EERAM_SincomAndFactory[i] = Diag_Requeste[3U+i];
    }

    EEPP_WriteData(EEPP_HDL_SincomAndFactory, NULL);
  }
  else
  {
    ret_val = SECURITY_ACCESS_DENIED;
  }

  return ret_val;
}

/******************************************************************************/
/*                     Write ISOCode                   (DID = 0xF1A5)         */
/******************************************************************************/
static u08 Udsa_DidWriteISOCode(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 i;

  for (i=0U; i < UDSA_LN_ISO; i++)
  {
    EERAM_ISOCode[i] = Diag_Requeste[3U+i];
  }

  EEPP_WriteData(EEPP_HDL_ISOCode, NULL);


  return ret_val;
}

/******************************************************************************/
/*           Write Heat temperature parameters      (DID = 0xFD23)            */
/******************************************************************************/
static u08 Udsa_DidWriteHeatTemp(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  s16 param1, param2, param3, param4, param5;

  /*Temp_lim */
  param1  = ((s16)Data[3] << 8U);
  param1 |= ((s16)Data[4]);

  /*Temp_range_min*/
  param2  = ((s16)Data[5] << 8U);
  param2 |= ((s16)Data[6]);

  /*Temp_range_max*/
  param3  = ((s16)Data[7] << 8U);
  param3 |= ((s16)Data[8]);

  /*Max_Av_Surf_Temp*/
  param4  = ((s16)Data[9] << 8U);
  param4 |= ((s16)Data[10]);

  /*Max_Av_Surf_Temp_StW*/
  param5  = ((s16)Data[11] << 8U);
  param5 |= ((s16)Data[12]);

  if (((param1 > HEATA_TEMP_LIM_0) && (param1 < HEATA_TEMP_LIM_1)) &&              /*Temp_lim */
      ((param2 > HEATA_TEMP_RANGE_MIN_0) && (param2 < HEATA_TEMP_RANGE_MIN_1)) &&  /*Temp_range_min*/
      ((param3 > HEATA_TEMP_RANGE_MAX_0) && (param3 < HEATA_TEMP_RANGE_MAX_1)))    /*Temp_range_max*/
  {
    EERAM_HeatTempParam.Temp_lim = param1;
    EERAM_HeatTempParam.Temp_range_min = param2;
    EERAM_HeatTempParam.Temp_range_max = param3;
    EERAM_HeatTempParam.Max_Av_Surf_Temp = param4;
    EERAM_HeatTempParam.Max_Av_Surf_Temp_StW = param5;
    EEPP_WriteData(EEPP_HDL_HeatTempParam, NULL);
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }


  return ret_val;
}

/******************************************************************************/
/*              Write Heat time parameters      (DID = 0xFD24)                */
/******************************************************************************/
static u08 Udsa_DidWriteHeatTime(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u16 param1, param2, param3, param4, param5, param6, param7, param8;

  /*T1 */
  param1  = ((s16)Data[3] << 8U);
  param1 |= ((s16)Data[4]);

  /*T_wait_1*/
  param2  = ((s16)Data[5] << 8U);
  param2 |= ((s16)Data[6]);

  /*T2*/
  param3  = ((s16)Data[7] << 8U);
  param3 |= ((s16)Data[8]);
  
  /*T3SW*/
  param4  = ((s16)Data[9] << 8U);
  param4 |= ((s16)Data[10]);

  /*T3HS*/
  param5  = ((s16)Data[11] << 8U);
  param5 |= ((s16)Data[12]);

  /*T_wait_2 */
  param6  = ((s16)Data[13] << 8U);
  param6 |= ((s16)Data[14]);

  /*T4*/
  param7  = ((s16)Data[15] << 8U);
  param7 |= ((s16)Data[16]);
  
  /*T_low*/
  param8  = ((s16)Data[17] << 8U);
  param8 |= ((s16)Data[18]);

  if((param1 < param3) && (param3 < param7)) /*T1 < T2 < T4*/
  {
    if ((param1 <= HEATA_TIME_T1)       &&        /*T1 */
        (param2 <= HEATA_TIME_T_WAIT_1) &&        /*T_wait_1*/
        (param3 <= HEATA_TIME_T2)       &&        /*T2*/
        (param4 <= HEATA_TIME_T3SW)     &&        /*T3SW*/
        (param5 <= HEATA_TIME_T3HS)     &&        /*T3HS*/
        (param6 <= HEATA_TIME_T_WAIT_2) &&        /*T_wait_2 */
        (param7 <= HEATA_TIME_T4)       &&        /*T4*/
        (param8 <= HEATA_TIME_T_LOW))             /*T_low*/
    {
      EERAM_HeatTimeParam.T1 = param1;
      EERAM_HeatTimeParam.T_wait_1 = param2;
      EERAM_HeatTimeParam.T2 = param3;
      EERAM_HeatTimeParam.T3SW = param4;
      EERAM_HeatTimeParam.T3HS = param5;
      EERAM_HeatTimeParam.T_wait_2 = param6;
      EERAM_HeatTimeParam.T4 = param7;
      EERAM_HeatTimeParam.T_low = param8;
      EEPP_WriteData(EEPP_HDL_HeatTimeParam, NULL);
    }
    else
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/******************************************************************************/
/*              Write Heat duty parameters      (DID = 0xFD25)                */
/******************************************************************************/
static u08 Udsa_DidWriteHeatDuty(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  u08 param1, param2, param3, param4, param5;

  /*D_3 */
  param1 = Data[3u];

  /*D_2 */
  param2 = Data[4u];

  /*DWL1 */
  param3 = Data[5u];

  /*DHL1 */
  param4 = Data[6u];

  /*DLL1 */
  param5 = Data[7u];

  /* duty cycle should be in range [0;100] */
  if ((param1 <= 100U) &&         /*D_3*/
      (param2 <= 100U) &&         /*D_2*/
      (param3 <= 100U) &&         /*DWL1*/
      (param4 <= 100U) &&         /*DHL1*/
      (param5 <= 100U))           /*DLL1*/
  {
    EERAM_HeatDutyParam.D_3 = param1;
    EERAM_HeatDutyParam.D_2 = param2;
    EERAM_HeatDutyParam.DWL1 = param3;
    EERAM_HeatDutyParam.DHL1 = param4;
    EERAM_HeatDutyParam.DLL1 = param5;
    EEPP_WriteData(EEPP_HDL_HeatDutyParam, NULL);
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }


  return ret_val;
}

/******************************************************************************/
/*                     Write Nominal stroke   (DID = 0xFD34)                  */
/******************************************************************************/
static u08 Udsa_DidWriteNominalStroke(u08 *Data, u16 Length)
{
  u08 ret_val= SERVICE_OK;
  UDSA_WordByte tmp16;

  tmp16.bytes[1] = Diag_Requeste[3u];
  tmp16.bytes[0] = Diag_Requeste[4u];
  EERAM_Nominal_Motors_Stroke = tmp16.word;

  EEPP_WriteData(EEPP_HDL_NominalMotorStroke, NULL);

  //Dispa_SetTolerances();

  return ret_val;
}

/******************************************************************************/
/*                Write Anti Pinch Thresholds    (DID = 0xFD36)               */
/******************************************************************************/
static u08 Udsa_DidWriteAntiPinchThresholds(u08 *Data, u16 Length)
{
  u08 tmp1;
  u08 ret_val = SERVICE_OK;

  /* Backwards Anti Pinch Threshold */
  tmp1 = Diag_Requeste[3u];

  if (tmp1 <= 100)
  {
    EERAM_Threshold_Antipinch_Backward = tmp1;
    EEPP_WriteData(EEPP_HDL_AntiPinch_Threshold_Bw, NULL);
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return ret_val;
}

/******************************************************************************/
/*                        Equipment Selection    (DID = 0xFD50)               */
/*                             (Supplier parameters)                          */
/******************************************************************************/
static u08 Udsa_DidWriteEquipmentSelection(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  EERAM_BproxiValue  = (ProductCode_t)Data[3U];
  EERAM_BproxiValue |= (ProductCode_t)Data[4U];

  EEPP_WriteData(EEPP_HDL_BproxiValue, NULL);

  return ret_val;

}

/******************************************************************************/
/*                       Equipment Configuration    (DID = 0xFD51)            */
/*                             (Supplier parameters)                          */
/******************************************************************************/
static u08 Udsa_DidWriteEquipmentConfiguration(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  EERAM_BproxiValue  = (ProductCode_t)Data[3U];
  EERAM_BproxiValue |= (ProductCode_t)Data[4U];

  EEPP_WriteData(EEPP_HDL_BproxiValue, NULL);

  EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn      = Data[5U];
  EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn     = Data[6U];
  EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn      = Data[7U];
  EERAM_BproxiConfig[EERAM_BproxiValue].BackEn      = Data[8U];
  EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn   = Data[9U];
  EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn   = Data[10U];
  EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn   = Data[11U];
  EERAM_BproxiConfig[EERAM_BproxiValue].AntiPinchEn = Data[12U];

  EEPP_WriteData(EEPP_HDL_BproxiBitfield, NULL);

  return ret_val;

}

/******************************************************************************/
/*                 Write Anti Pinch Adaptation    (DID = 0xFD54)              */
/******************************************************************************/
static u08 Udsa_DidWriteAntiPinchAdaptation(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  /* Anti Pinch adaption enabled or not */
  EERAM_AntiPinchAdaptation = Diag_Requeste[3u];
  EEPP_WriteData(EEPP_HDL_AntiPinchAdaptation, NULL);


  return ret_val;
}

/******************************************************************************/
/*                Write Anti Pinch Attention    (DID = 0xFD55)                */
/******************************************************************************/
static u08 Udsa_DidWriteAntiPinchAttention(u08 *Data, u16 Length)
{
  u08 tmp1;
  u08 ret_val;

  /* Backwards Anti Pinch Threshold */
  tmp1= Diag_Requeste[3u];

  if (tmp1 <= 100)
  {
    EERAM_Threshold_Att_Backward = tmp1;
    EEPP_WriteData(EEPP_HDL_AntiPinch_Att_Backward, NULL);
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return ret_val;
}

/******************************************************************************/
/*                          Erase Eeprom    (DID = 0xFDF1)                    */
/*                             (Supplier parameters)                          */
/******************************************************************************/
static u08 Udsa_DidWriteEraseEeprom(u08 *Data, u16 Length)
{
  u08 ret_val;

  // if(memcmp(&UDSA_MirrorApplSwId[0u], &EERAM_ApplSwId[0u], UDSA_LN_APP_SW_IDENTIFICATION) == 0)
  // {
  /* Verifico la chiave */
  if (memcmp(&Diag_Requeste[3], Udsa_ERASE_EE_KEY, UDSA_ERASE_EE_KEY_SIZE) == 0)
  {
    EEPP_EraseEeprom(&EEPP_EraseCompleted);

    UDSA_EraseEpromResult = MS_NOT_OK;
    UDSA_Nak78Pending     = NAK78_PENDING;
    TLRP_SetSlow(UDSA_Nak78EepromEraseTimer);

    ret_val = REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  // }
  // else
  // {
  //   ret_val = REQUEST_OUT_OF_RANGE;
  // }

  return ret_val;

}
#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDSA_RdiConfig.c) ______________________________________*/
