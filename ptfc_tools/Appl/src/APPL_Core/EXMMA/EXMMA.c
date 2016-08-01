/**
* @file EXMMA.c
* @author De Stephanis Alessio
* @date 31 mar 2015
* @brief EXternal Mirrors Management module
* @see www.Bitron.net
*/


#define EXMMA_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "EXMMA.h"
#include "EXMMA_config.h"

#ifdef __EXMMA_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static void Exmma_setCurrentPositions(MIRR_Data_t bufStruct);
static void Exmma_getMirrorSignals(MIRR_Data_t *bufStruct);
static void Exmma_setMirrorSignals(MIRR_Data_t bufStruct);
static void Exmma_activateMirrors(void);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief This function initializes the EXMMA module
 * @author De Stephanis Alessio
 * @param [in] None
 * @param [out] None
 * @return None
 */
void EXMMA_Init(void)
{
}


/**
 * @brief External mirrors cyclic management
 * @author De Stephanis Alessio
 * @param [in] None
 * @param [out] None
 * @return None
 */
void EXMMA_Mgm(void)
{
  MIRR_Data_t readMirrorsValues;

  /* Check if Key status is ON */
  if (KEYA_GetKeyStatus() == KEYA_ON_STATUS)
  {
    /* Read from CAN the mirror's positions and directions */
    Exmma_getMirrorSignals(&readMirrorsValues);
    
    /* Check for stable signals to save */
    Exmma_setCurrentPositions(readMirrorsValues);
  }
}


/**
 * @brief Memory recall routine
 * @author De Stephanis Alessio
 * @param [in] Number of slot memory to recall
 * @param [out] None
 * @return None
 */
void EXMMA_MemRecall(uint8_t recMemory)
{
  /* Check if the requested memory slot exists */
  if (recMemory < NUM_MEMORIE)
  {
    /* Check if the called memory slot has been already written before */
    if (EERAM_MirrorMemInit[recMemory])
    {
      switch (recMemory)
      {
        case MEM_1:
        {
          /* Copy EEPROM data into current memory */
          memcpy(&EERAM_MirrorMCorr, &EERAM_MirrorM1, sizeof(MIRR_Data_t));
        }
        break;

        case MEM_2:
        {
          /* Copy EEPROM data into current memory */
          memcpy(&EERAM_MirrorMCorr, &EERAM_MirrorM2, sizeof(MIRR_Data_t));
        }
        break;

        case MEM_3:
        {
          /* Copy EEPROM data into current memory */
          memcpy(&EERAM_MirrorMCorr, &EERAM_MirrorM3, sizeof(MIRR_Data_t));
        }
        break;

        default:
          break;
      }

      /* Activate mirrors movement and save MCorr */
      Exmma_activateMirrors();
    }
  }
}


/**
 * @brief Memory saving routine
 * @author De Stephanis Alessio
 * @param [in] Number of slot memory to save
 * @param [out] None
 * @return None
 */
void EXMMA_MemSave(uint8_t savMemory)
{
  /* Check if the requested memory slot exists */
  if (savMemory < NUM_MEMORIE)
  {
    /* Check for requested memory slot validity */
    switch (savMemory)
    {
      case MEM_1:
      {
        /* Save data in selected user memory */
        Exmma_getMirrorSignals(&EERAM_MirrorM1);

        /* Write new data in Eeprom */
        EEPP_WriteData(EEPP_HDL_MirrorM1, NULL);
      }
      break;

      case MEM_2:
      {
        /* Save data in selected user memory */
        Exmma_getMirrorSignals(&EERAM_MirrorM2);

        /* Write new data in Eeprom */
        EEPP_WriteData(EEPP_HDL_MirrorM2, NULL);
      }
      break;

      case MEM_3:
      {
        /* Save data in selected user memory */
        Exmma_getMirrorSignals(&EERAM_MirrorM3);

        /* Write new data in Eeprom */
        EEPP_WriteData(EEPP_HDL_MirrorM3, NULL);
      }
      break;

      default:
        break;
    }
    
    /* Set flag after memory store */
    EERAM_MirrorMemInit[savMemory] = TRUE;
    EEPP_WriteData(EEPP_HDL_MirrorMemInit, NULL);
  }
}


/**
 * @brief Changes the "key" status following KEYA module notification
 * @author De Stephanis Alessio
 * @param [in] new KeyStatus
 * @param [out] None
 * @return None
 */
void EXMMA_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
static PRES_KeyStatus_t Exmma_KeyStatus = ANY_KEY;   

  /* Check if a Key-ON event occurred */
  if ((Exmma_KeyStatus != KEYA_CRANK_STATUS) &&
      (KeyStatus == KEYA_ON_STATUS))
  {   
    /* Activate mirrors movement with MCorr data */
    Exmma_activateMirrors();
  }
  
  /* Update the Key Status */
  Exmma_KeyStatus = KeyStatus;
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief This function checks is the read signals are stable and saves them into RAM and EEPROM
 * @author De Stephanis Alessio
 * @param [in] Mirror data structure to check
 * @param [out] None
 * @return None
 */
static void Exmma_setCurrentPositions(MIRR_Data_t bufStruct)
{
  static bool_t Exmma_saveDrvInRam = TRUE;
  static bool_t Exmma_savePsngrInRam = TRUE;
  static bool_t Exmma_saveInEeprom = FALSE;
  
  /* Only if the mirrors are not activated by MSM module */
  if (EXMMA_READ_DATA_READY == CMMD_NOT_READY)
  {
    /* Check for changed driver signals */
    if ((bufStruct.DrvStandStillSts == CMMD_STANDSTILL) && (Exmma_saveDrvInRam))
    {
      /* Update driver data in Ram */
      EERAM_MirrorMCorr.DrvVertPos = bufStruct.DrvVertPos;
      EERAM_MirrorMCorr.DrvHorizPos = bufStruct.DrvHorizPos;
      EERAM_MirrorMCorr.DrvStandStillSts = bufStruct.DrvStandStillSts;
      
      /* Reset flag for saving in Ram */
      Exmma_saveDrvInRam = FALSE;
      
      /* Set flag for Eeprom updating */
      Exmma_saveInEeprom = TRUE;
    }
    else if (bufStruct.DrvStandStillSts == CMMD_MOVING)
    {
      /* Save the read signals when they will be still */
      Exmma_saveDrvInRam = TRUE;
    }
    else
    {
      /* Else condition added for Misra rule 14.10 */
    }
    
    /* Check for changed passenger signals */
    if ((bufStruct.PsngrStandStillSts == CMMD_STANDSTILL) && (Exmma_savePsngrInRam))
    {
      /* Update passenger data in Ram */
      EERAM_MirrorMCorr.PsngrVertPos = bufStruct.PsngrVertPos;
      EERAM_MirrorMCorr.PsngrHorizPos = bufStruct.PsngrHorizPos;
      EERAM_MirrorMCorr.PsngrStandStillSts = bufStruct.PsngrStandStillSts;
      
      /* Reset flag for saving in Ram */
      Exmma_savePsngrInRam = FALSE;
      
      /* Set flag for Eeprom updating */
      Exmma_saveInEeprom = TRUE;
    }
    else if (bufStruct.PsngrStandStillSts == CMMD_MOVING)
    {
      /* Save the read signals when they will be still */
      Exmma_savePsngrInRam = TRUE;
    }
    else
    {
      /* Else condition added for Misra rule 14.10 */
    }
    
    /* Check if Eeprom has to be updated */
    if (Exmma_saveInEeprom)
    {
      /* Read mirror data from RAM and update CAN message */
      Exmma_setMirrorSignals(EERAM_MirrorMCorr);
      
      /* Write RAM data in EEPROM */
      EEPP_WriteData(EEPP_HDL_MirrorMCorr, NULL);
      
      /* Reset flag */
      Exmma_saveInEeprom = FALSE;
    }
  }
}


/**
 * @brief This function retrieves values from CAN bus and puts them into the pointed structure
 * @author De Stephanis Alessio
 * @param [in] Pointer to mirror data structure to fill with read signals
 * @param [out] None
 * @return None
 */
static void Exmma_getMirrorSignals(MIRR_Data_t *bufStruct)
{
  /* Get driver data */
  bufStruct->DrvVertPos           = EXMMA_READ_DRIVER_VERT_POS;
  bufStruct->DrvHorizPos          = EXMMA_READ_DRIVER_HORIZ_POS;
  bufStruct->PsngrVertPos         = EXMMA_READ_PSNGR_VERT_POS;
  bufStruct->PsngrHorizPos        = EXMMA_READ_PSNGR_HORIZ_POS;
  bufStruct->DrvStandStillSts     = EXMMA_READ_DRIVER_STILL;
  bufStruct->PsngrStandStillSts   = EXMMA_READ_PSNGR_STILL;
}


/**
 * @brief This function writes values on CAN bus from the passed structure
 * @author De Stephanis Alessio
 * @param [in] Mirror data structure to write on output signals
 * @param [out] None
 * @return None
 */
static void Exmma_setMirrorSignals(MIRR_Data_t bufStruct)
{
  /* Set signals to write on CAN bus */
  EXMMA_UPDATE_PSNGR_VERT_POS(bufStruct.PsngrVertPos);
  EXMMA_UPDATE_PSNGR_HORIZ_POS(bufStruct.PsngrHorizPos);
  EXMMA_UPDATE_DRIVER_VERT_POS(bufStruct.DrvVertPos);
  EXMMA_UPDATE_DRIVER_HORIZ_POS(bufStruct.DrvHorizPos);
}


/**
 * @brief Activates the mirror movement with MCorr signals
 * @author De Stephanis Alessio
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Exmma_activateMirrors(void)
{
  /* Set on CAN bus the mirror's positions and directions */
  Exmma_setMirrorSignals(EERAM_MirrorMCorr);

  /* Send mirror movement command on CAN bus */
  EXMMA_SET_MIRROR_MOVEMENT_CMD(CMMD_READY);
}


#endif /* __EXMMA_IS_PRESENT__ */

/*______ E N D _____ (EXMMA.c) _________________________________________*/

