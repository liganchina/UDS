/**
 * @file LINC.c
 * @brief LIN control: source code of LIN module for control layer. 
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time 
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/


#define LINC_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINC.h"
#include "LINC_if.h"
#include "LINC_config.h"
#include "UARTD_if.h"

/* Module inhibition filter */
#ifdef __LINC_IS_PRESENT__

/*______ L O C A L - D E F I N E S ___________________________________________*/
#define LINC_SYNC_BYTE       (uint8_t)0x55
#define LINC_GOTOSLEEP_PID   (uint8_t)Linc_MessageMap[LINC_CommandGTS]->Id
#define LINC_PID_ID_MASK     (uint8_t)0x3F; /* Used for calculating the cks */

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/
/* LINC machine state */
static LINC_Status_t Linc_Status;

/* Reference to currently scheduled message */
static const Linc_lin_frame_st_t *Linc_ReqFramePtr;

/* Flag to GoToSleep signal request */
static bool_t Linc_GoToSleepRequest;

/* Flag to determine if internal WakeUp is request */
static bool_t Linc_WakeUpRequest;
static uint8_t Linc_WakeUpCount;

/* Flag to determine if external bus Signal is received */
static bool_t Linc_ReceivedExternalSignal;

/* Flag to determine if external WakeUp is received */
static bool_t Linc_ReceivedExternalWakeUp;

/* Flag to determine if external bus Signal is received and confirmed */
static bool_t Linc_ReceivedExternalSignalConfirmed;

/* Flags for timer */
static bool_t Linc_TimerStart;


/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* Look for requested PID in message map */
static const Linc_lin_frame_st_t *Linc_FindFrameFromPid(uint8_t pid);

/* Compute PID for requested ID */
static uint8_t Linc_ComputePidFromId(uint8_t id);

/* Set error type and counter */
static void Linc_SetErrorFrame(LINC_FrameError_t ErrorType);

/* Start and stop timer for check error */
static void Linc_RestartTimer(uint32_t time);
static void Linc_StopTimer(void);

/* Select ID frame value to send according to frame type */
static uint8_t Linc_GetIdFrame(LINC_MessageMap_t MsgHndle);

/* Interrupt timer */
static uint16_t Linc_INTTM03_Isr(void);


/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief This function Initializes the LINC driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void LINC_Init(void)
{ 
  /* Init state machine */  
  Linc_Status = LINC_SLEEP;
  
  /* Set interrupt */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTTM03, (ISRD_EvtCbk_t)Linc_INTTM03_Isr); 
  
  /* Init local data */
  Linc_ReqFramePtr = NULL;
  
  /* Init GoToSleep message */
  Linc_GoToSleepRequest = FALSE;
  
  /* Init request WakeUp from bus */
  Linc_ReceivedExternalSignal = FALSE;
  Linc_ReceivedExternalWakeUp = FALSE;
  Linc_ReceivedExternalSignalConfirmed = FALSE;
  
  /* Call task for LIN reception (slave task) */
  LINC_ReceptionTask(UARTD_CHN_HND);  
}
   
/**
 * @brief Send required buffer as a LIN response
 * @param Frame Handle, Tx buffer pointer, length of buffer
 * @return void
 * @note
 */
void LINC_PutMessage(LINC_MessageMap_t MsgHandle, 
                     uint8_t *DataBuf, uint8_t len)
{
  /* Support variables */
  uint8_t byteIdx;
  uint8_t bytesNum;
  const Linc_lin_frame_st_t *framePtr = NULL;
  
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  if (framePtr != NULL)
  {
    /* Make sure the buffer length is not exceeded */
    if (len < framePtr->DataLen)
    {
      bytesNum = len;
    }
    else
    {
      bytesNum = framePtr->DataLen;
    }
    
    for (byteIdx = 0U; byteIdx < bytesNum; byteIdx++)
    {
      framePtr->DataBuff[byteIdx] = DataBuf[byteIdx];
    }
  }
}

/**
 * @brief Returns data received as LIN response
 * @param Frame Handle, Rx buffer pointer, maximum length of buffer
 * @return uint8_t
 * @note
 */
uint8_t LINC_GetMessage(LINC_MessageMap_t MsgHandle, 
                        uint8_t *DataBuf, uint8_t len)
{
  /* Support variables */
  uint8_t byteIdx;
  uint8_t bytesNum;
  const Linc_lin_frame_st_t *framePtr = NULL;
  
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  if (framePtr != NULL)
  {
    /* Make sure the buffer length is not exceeded */
    if (len < framePtr->DataLen)
    {
      bytesNum = len;
    }
    else
    {
      bytesNum = framePtr->DataLen;
    }
    
    for (byteIdx = 0U; byteIdx < bytesNum; byteIdx++)
    {
      DataBuf[byteIdx] = framePtr->DataBuff[byteIdx];
    }
  }
  
  return bytesNum;
}

/**
 * @brief Read frame status form bus
 * @param Frame Handle
 * @return LINC_FrameError_t
 * @note
 */
LINC_FrameError_t LINC_GetMessageStatus(LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
  LINC_FrameError_t error_type ; 
  const Linc_lin_frame_st_t *framePtr = NULL;
  
  /* Set Generic error */
  error_type = LINC_ERROR_GENERIC_HW;
  
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  if (framePtr != NULL)
  {
    /* Return frame selected error type */
    error_type = *framePtr->FrameError;
  }  
  return error_type;
}

/**
 * @brief Read frame error count on bus
 * @param Frame Handle
 * @return uint8_t
 * @note
 */
uint8_t LINC_GetMessageErrorCount(LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
  uint8_t error_count = 0u;
 
  const Linc_lin_frame_st_t *framePtr = NULL;
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  if (framePtr != NULL)
  {
    /* Return frame selected error count */
    error_count = *framePtr->FrameErrorCount;
  }  
  return error_count;
}

/**
 * @brief Reset frame error type and frame
 * @param Frame Handle
 * @return void
 * @note
 */
void LINC_ResetMessageError(LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
  const Linc_lin_frame_st_t *framePtr = NULL;
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  if (framePtr != NULL)
  {
    /* Reset error type */
    *framePtr->FrameError = LINC_NO_FAULT;
    
    /* Reset error count */
    *framePtr->FrameErrorCount = 0U;
  }  
}

/**
 * @brief Wake up transceiver and UART
 * @param channel index
 * @return void
 * @note
 */
void LINC_WakeUp(uint8_t chn_hnd)
{  

  /* Wake up transceiver */
  if (LTMS_GetStatus(chn_hnd) == LTMS_SLEEP)
  {
    LTMS_WakeUp(chn_hnd);
  }
     
  /* Wake up UART */
  if (UARTD_GetStatus(chn_hnd) == UARTD_SLEEP)
  {
    UARTD_WakeUp(chn_hnd);
  }
  
  /* Change status and send on bus a WakeUp signal*/
  if(Linc_Status == LINC_SLEEP)
  {         
    Linc_WakeUpRequest = TRUE;
    Linc_WakeUpCount = 0U;
    Linc_Status = LINC_WAKE_UP;

    /* Call task for LIN reception (slave task) */
    LINC_ReceptionTask(UARTD_CHN_HND);    
  }
  
}

/**
 * @brief Send Go to sleep command to transceiver and UART
 * @param channel index
 * @return void
 * @note
 */
void LINC_GoToSleep(uint8_t chn_hnd)
{
  /* Support variables */
  const Linc_lin_frame_st_t *Linc_GoToSleepPtr;
  Linc_GoToSleepPtr = Linc_MessageMap[LINC_CommandGTS];
  
  if(Linc_Status != LINC_SLEEP)
  {
    /* If LINC isn't in Sleep mode, send a GoToSleep on network */    
    if(Linc_GoToSleepRequest == FALSE)
    {
      /* Send GoToSleep frame on network */
      Linc_GoToSleepRequest = TRUE;
      LINC_PutHeader(chn_hnd, LINC_CommandGTS);
          
      if (UARTD_GOTOSLEEP_MODE == UARTD_POWEROFF)
      {
        /* Check if it a target frame */
        
        /* Start transmission */
        UARTD_SendBuffer(chn_hnd, Linc_GoToSleepPtr->DataBuff, Linc_GoToSleepPtr->DataLen);
        /* Send static checksum */
        UARTD_SendByte(chn_hnd, 0x00U);
        
        /* Reset flag for send new GTS signal */
        Linc_GoToSleepRequest = FALSE;
        
        Linc_Status = LINC_SLEEP;
      }    
    }  
  }
  else
  {
    /* If LINC is in Sleep mode, control lower levels. */
    /* LIN transceiver sleep mode activate */ 
    if (LTMS_GetStatus(chn_hnd) != LTMS_SLEEP)
    {
      LTMS_GoToSleep(chn_hnd);
    }      
    /* UARTD sleep mode activate */
    if (UARTD_GetStatus(chn_hnd) == UARTD_SLEEP)
    {
      UARTD_GoToSleep(chn_hnd);
    }
  }
}

/**
 * @brief Indicates the reception of wake up signal from slave node
 * @param channel index
 * @return boolean
 * @note
 */
bool LINC_GetBusWakeUpRequest(uint8_t chn_hnd)
{
  /* Support variables */
  bool_t receivedExternalWakeUp = Linc_ReceivedExternalWakeUp;
  
  /* Reset flag */
  Linc_ReceivedExternalWakeUp = FALSE;
  
  return receivedExternalWakeUp;
}

/**
 * @brief Indicates the reception of signal from bus
 * @param channel index
 * @return boolean
 * @note
 */
bool LINC_GetBusSignalRequest(uint8_t chn_hnd)
{ 
  /* Support variables */
  bool_t receivedExternalSignal = Linc_ReceivedExternalSignal;
  
  /* Reset flag */
  Linc_ReceivedExternalSignal = FALSE;  
  
  return receivedExternalSignal;
}

/**
 * @brief Indicates the confirm of signal reception from bus
 * @param channel index
 * @return boolean
 * @note
 */
bool LINC_GetBusSignalRequestConfirmed(uint8_t chn_hnd)
{ 
  /* Support variables */
  bool_t receivedExternalSignalConfirmed = Linc_ReceivedExternalSignalConfirmed;
  
  /* Reset flag */
  Linc_ReceivedExternalSignalConfirmed = FALSE;  
  
  return receivedExternalSignalConfirmed;
}

/**
 * @brief Return LINC status
 * @param channel index
 * @return LINC_Status_t
 * @note
 */
LINC_Status_t LINC_GetStatus(uint8_t chn_hnd)
{
  return Linc_Status;
}

/**
 * @brief Get UARTD Error state
 * @param channel index
 * @return UARTD_HwErrorStatus_t
 * @note
 */
UARTD_HwErrorStatus_t LINC_GetDiag(uint8_t chn_hnd)
{
  return UARTD_GetDiag(chn_hnd);
}

/**
 * @brief Send identifier
 * @param channel index, Frame Handle
 * @return void
 * @note
 */
void LINC_PutHeader(uint8_t chn_hnd, LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
  uint8_t id_frame;
  
  /* Select id frame to send */
  id_frame = Linc_GetIdFrame(MsgHandle);
  /* If Linc_GetIdFrame return a id_frame = 0xFF this header is not to be sent.
    This slot time is empty */
  if(id_frame != 0xFF)
  {
    UARTD_SendBreak(chn_hnd);
    UARTD_SendByte(chn_hnd, LINC_SYNC_BYTE);
  
    /* Compute PID */
    id_frame = Linc_ComputePidFromId(id_frame);
  
    /* Send PID */
    UARTD_SendByte(chn_hnd, id_frame);  
  }

}

/**
 * @brief This function handles the reception and transmission of the frame
 * @return void
 * @note
 */
void LINC_ReceptionTask(uint8_t chn_hnd)
{
  /* Support variables */
  uint8_t byteIdx;
  uint8_t readByte = 0U;
  uint8_t readFrame[8];
  uint8_t availBytes;  
  uint8_t computedChecksum_u8;
  uint16_t computedChecksum_u16;
  UARTD_HwErrorStatus_t HW_status;   
    
  /* Verify UARTD status for check error in HW */  
  HW_status = UARTD_GetDiag(chn_hnd);
  if((HW_status != UARTD_NO_ERROR) && 
     (Linc_Status != LINC_SLEEP) && (Linc_Status != LINC_WAKE_UP))
  { 
    /* Set Error in LINC */
    if(Linc_Status !=  LINC_ERROR)
    { 
      /* Select a error type */
      switch (Linc_Status)
      {
        case LINC_IDLE:
          /* If error occurred in Break Field, reset a poiter of frame */          
          Linc_ReqFramePtr = NULL;
          /* Set Error Generic */
          Linc_SetErrorFrame(LINC_ERROR_GENERIC_HW);          
          break;
        case LINC_RG_DATA:
          /* Set Error Response */
          Linc_SetErrorFrame(LINC_ERROR_RESPONSE);
          break;       
        default:
          /* Set Error Generic */
          Linc_SetErrorFrame(LINC_ERROR_GENERIC_HW);
          break;
      }     
      /* Change status in Error */
      Linc_Status =  LINC_ERROR;        
    }
  }  
  
  /* Change status */
  switch (Linc_Status)
  {
    case LINC_SLEEP:
      /* Waits for reception by UARTD interrupt HW */
      if(UARTD_GetBusSignalRequest(chn_hnd) == TRUE)
      {
        /* Start timer only one time */
        if((Linc_ReceivedExternalSignal == FALSE) && 
            (Linc_ReceivedExternalSignalConfirmed== FALSE))
        {
          /* Start Timer */
          Linc_RestartTimer(LINC_TIMEOUT_WAKEUPEXT_COUNT); 

          /* External Signal received */
          Linc_ReceivedExternalSignal = TRUE;
        }
        
      } 
      if(UARTD_GetBusWakeUpRequest(chn_hnd) == TRUE)
      {
        /* Stop timer */
        Linc_StopTimer();  
        
        /* External WakeUp signal received */
        Linc_ReceivedExternalWakeUp = TRUE;  
    
        /* Change status */
        Linc_Status = LINC_IDLE;        
      }
      break;
    case LINC_WAKE_UP:
      
      if(Linc_WakeUpRequest == TRUE)
      {
        /* Send new WakeUp on network */
         UARTD_SendWakeUp(chn_hnd);         
         Linc_WakeUpRequest = FALSE;
         Linc_WakeUpCount ++;      
      }              
      if(UARTD_IsBreakReceived(chn_hnd) == TRUE)
      {
        /* Occurs if the whole sequence has been sent */
        if(Linc_WakeUpCount == LINC_WAKEUP_SIGNAL_COUNT)
        {        
          /* Reset breack field len for Header field */ 
          UARTD_ResetBreakFieldLen(chn_hnd);
          Linc_Status = LINC_IDLE; 
        }
        else
        {
          /* Start Timer */
          Linc_RestartTimer(LINC_TIMEOUT_WAKEUP_COUNT);
        }       
      }
      break;      
    case LINC_IDLE:                  
      if(UARTD_IsBreakReceived(chn_hnd) == TRUE)
      {
        /* BF Received */
        Linc_Status =  LINC_BF_RD;   
        
        /* Reset frame pointer (is set when ID is received) */
        Linc_ReqFramePtr = NULL;
        
        /* Start Timer for new status*/
        Linc_RestartTimer(LINC_TIMEOUT_INTB_COUNT);        
      }               
      break;
    case LINC_ERROR:
      if(UARTD_IsBreakReceived(chn_hnd) == TRUE)
      {
        /* BF Received */
        Linc_Status =  LINC_BF_RD;

        /* Reset frame pointer (is set when ID is received) */
        Linc_ReqFramePtr = NULL;
        
        /* Start Timer for new status*/
        Linc_RestartTimer(LINC_TIMEOUT_INTB_COUNT);        
      }     
      break;      
    case LINC_BF_RD:      
      
      if(UARTD_IsDataReceived(chn_hnd) == TRUE)
      {
        /* Stop timer */
        Linc_StopTimer();    
        
        /* SYNC (0x55) received */
        readByte = UARTD_ReadByte(chn_hnd);        
        if (readByte == LINC_SYNC_BYTE)
        {
          Linc_Status =  LINC_SF_RD;
          
          /* Start Timer for new status*/
          Linc_RestartTimer(LINC_TIMEOUT_INTB_COUNT);          
        }
        else
        {
          /* Set LINC error */
          Linc_Status = LINC_ERROR;
        }
      }
      break;
    case LINC_SF_RD:           
     
      if(UARTD_IsDataReceived(chn_hnd) == TRUE)
      {
        /* Stop timer */  
        Linc_StopTimer();         
        
        /* PID (check if RX o TX) received */
        readByte = UARTD_ReadByte(chn_hnd);
        
        /* Init checksum with PID */
        computedChecksum_u16 = readByte;
        
        /* Retrieve ID */
        readByte &= LINC_PID_ID_MASK;
        
        /* Check if it a target frame */
        Linc_ReqFramePtr = Linc_FindFrameFromPid(readByte);        
        
        /* Verify ID */        
        if(readByte < LINC_GOTOSLEEP_PID)
        {
          /* Correct PID */
          if (Linc_ReqFramePtr != NULL) /* A frame is found */
          {
            if (Linc_ReqFramePtr->DataSource == SOURCE_PUBLISHER)
            {
              /* It is necessary to send data */
              
              /* Callback from frame sent to upper layer (APPL_cbk) */
              if ( Linc_ReqFramePtr->IndCbk != NULL)
              {
                Linc_ReqFramePtr->IndCbk();
              }              
              
              /* Start transmission */
              UARTD_SendBuffer(chn_hnd, Linc_ReqFramePtr->DataBuff, Linc_ReqFramePtr->DataLen);
              
              for (byteIdx = 0U; byteIdx < Linc_ReqFramePtr->DataLen; byteIdx++)
              {
                computedChecksum_u16 += Linc_ReqFramePtr->DataBuff[byteIdx];
              }
              
              /* Add Carry */
              computedChecksum_u16 = ((computedChecksum_u16 >> 8) + (computedChecksum_u16 & 0x00FFU));
              while ((computedChecksum_u16 & 0xFF00) != 0U)
              {
                computedChecksum_u16 = ((computedChecksum_u16 >> 8) + (computedChecksum_u16 & 0x00FFU));
              }
              
              computedChecksum_u8 = (uint8_t)computedChecksum_u16;           
                            
              /* Send inverted checksum */
              UARTD_SendByte(chn_hnd, (0xFF - computedChecksum_u8));
   
              /* Now that transmission is started, wait until end of operation*/
              /* (Go to Receiving state) */
            }
            else
            {
              /* receive data from slave */
            }         
            /* Receive data (own or from slave) */
            Linc_Status =  LINC_RG_DATA;          
          }
          else
          {
            /* Frame not found: Not own PID */                  
            /* Go back to idle state */
            Linc_Status = LINC_IDLE;
          }    
        } 
        else
        {
          /* Not Correct PID received */          
          if((readByte == 0x3C) || (readByte == 0x3D))
          {
            /* Transport protocol */  
            if(Linc_GoToSleepRequest == TRUE)
            {
              if (UARTD_GOTOSLEEP_MODE == UARTD_RECEPTION_TASK_ON)
              {
                /* Send GTS signal if request */
                UARTD_SendBuffer(chn_hnd, Linc_ReqFramePtr->DataBuff, Linc_ReqFramePtr->DataLen);
              
                /* Send static checksum */
                UARTD_SendByte(chn_hnd, 0x00U);
              }
              Linc_Status =  LINC_RG_DATA;              
            }
            else
            {
              /* Set LINC error */
              Linc_Status = LINC_ERROR;
            }              
          }
          else 
          {
            /* Error: ID not valid */
            /* Set LINC error */
            Linc_Status = LINC_ERROR;
          }                        
        }        
      }
      /* Start Timer for new status*/
      if(Linc_Status == LINC_RG_DATA)
      {
        Linc_RestartTimer(LINC_TIMEOUT_RESP_COUNT);
      }
      break;
    case LINC_RG_DATA:      

      /* Check whether required number of bytes has been received */                 
      availBytes = UARTD_GetNumberOfRxBytes(chn_hnd);

      if (availBytes == Linc_ReqFramePtr->DataLen + 1)
      {
        /* Stop timer */  
        Linc_StopTimer();                 
        
        /* Clear checsum */
        computedChecksum_u16 = Linc_ComputePidFromId(Linc_ReqFramePtr->Id);
        
        /* Read bytes */
        for (byteIdx = 0U; byteIdx < Linc_ReqFramePtr->DataLen; byteIdx++)
        {
          readByte = UARTD_ReadByte(chn_hnd);
          
          /* Store data in message buffer */
          readFrame[byteIdx] = readByte;          
          
          /* Update checksum */
          computedChecksum_u16 += readByte;
        }
        
        /* Add Carry */
        computedChecksum_u16 = ((computedChecksum_u16 >> 8) + (computedChecksum_u16 & 0x00FFU));
        while ((computedChecksum_u16 & 0xFF00) != 0U)
        {
          computedChecksum_u16 = ((computedChecksum_u16 >> 8) + (computedChecksum_u16 & 0x00FFU));
        }        
        computedChecksum_u8 = (uint8_t)computedChecksum_u16;
        
        /* Read Received Checksum byte */
        readByte = UARTD_ReadByte(chn_hnd);
              
        /* If checksum matches, no error */
        if ((readByte + computedChecksum_u8) == 0xFF)
        {
          /* Frame Correctly received */ 
  
          /* Store data in message buffer */
          for (byteIdx = 0U; byteIdx < Linc_ReqFramePtr->DataLen; byteIdx++)
          {          
            /* Store data in message buffer */            
            Linc_ReqFramePtr->DataBuff[byteIdx] = readFrame[byteIdx];
          }          
          
          /* Reset error count */
          *Linc_ReqFramePtr->FrameError = LINC_NO_FAULT;
          /* *Linc_ReqFramePtr->frame_error_count = 0x00; */
          
          /* Reset flag of sporadic frame request */
          if(Linc_ReqFramePtr->FrameType == FR_TYPE_SPORADIC)
          {
            *Linc_ReqFramePtr->SprRequest = FALSE;
          }
                    
        }
        else
        {
          /* If there's a GTS request don't set checksum error (classic) */
          if(Linc_GoToSleepRequest == TRUE)
          {
            if (UARTD_GOTOSLEEP_MODE == UARTD_RECEPTION_TASK_ON)
            {
              /* LIN transceiver sleep mode activate */ 
              LTMS_GoToSleep(chn_hnd);            
              /* UARTD sleep mode activate */
              UARTD_GoToSleep(chn_hnd);   
     
              /* Reset flag for detection of WakeUp source */
              Linc_ReceivedExternalSignal = FALSE;
              Linc_ReceivedExternalWakeUp = FALSE;
              Linc_ReceivedExternalSignalConfirmed = FALSE;
            }
            /* Change status */
            Linc_Status = LINC_SLEEP;            
                                   
            /* Request complete: now LTMS and UARTD GoToSleep */
            Linc_GoToSleepRequest = FALSE;
                       
          }
          else
          {
            /* Error: checksum not correct */
            Linc_SetErrorFrame(LINC_ERROR_RESPONSE);          
          }         
        }  
        /* Go back to idle state */
        if(Linc_Status != LINC_SLEEP)
        {          
          Linc_Status = LINC_IDLE;
          /* Callback from frame received to upper layer (APPL_cbk) */
          if (Linc_ReqFramePtr->DataSource == SOURCE_RECEIVER)
          {
            if ( Linc_ReqFramePtr->IndCbk != NULL)
            {
              Linc_ReqFramePtr->IndCbk();
            }             
          }           
        }                     
      }
      else
      {
        /* Continue receiving */        
      }
      break;
    default:
      /* Should not be here */
      break;
  }
}

/**
 * @brief Set error type and increase error counter into selected frame
 * @param Frame Handle
 * @return void
 * @note
 */
void LINC_SetMessageError(LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
  uint8_t errorCount;  
  const Linc_lin_frame_st_t *framePtr;
  
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  /* Set error only if Linc_ReqFramePtr == NULL, otherwise error type is
    already set in LINC_ReceptionTask */
  if (Linc_ReqFramePtr->Id != framePtr->Id) 
  {           
    /* Set error type */
    *framePtr->FrameError = LINC_ERROR_GENERIC_HW;
    /* Increase error couter */
    errorCount = *framePtr->FrameErrorCount;
    if(LINC_FRAME_MAX_ERROR_COUNT > errorCount)
    {
      errorCount ++;      
      *framePtr->FrameErrorCount = errorCount;
    }    
  }
  
  /* If error occurred detection, reset a status of LINC. This functionality 
    is required to detect a error in new break field frame */          
  Linc_Status = LINC_IDLE;
}

/**
 * @brief Set request to send of sporadic frame
 * @param Frame Handle
 * @return void
 * @note
 */
void LINC_SetMessageSprRequest(LINC_MessageMap_t MsgHandle)
{
  /* Support variables */
   const Linc_lin_frame_st_t *framePtr;
  /* Look for frame */
  framePtr = Linc_MessageMap[MsgHandle];
  
  /* Set request only if selected frame is a sporadic frame */  
  if (framePtr != NULL)
  {
    if(framePtr->FrameType == FR_TYPE_SPORADIC)
    {
      *framePtr->SprRequest = TRUE;        
    }  
  }  
}




/* Private functions */

/**
 * @brief Look for requested PID in message map, returns null if not found
 * @param PID
 * @return Pointer to frame
 * @note
 */
static const Linc_lin_frame_st_t *Linc_FindFrameFromPid(uint8_t pid)
{  
  /* Support variables */
  uint8_t mexIdx_u8 = 0U;
  bool_t found_b = FALSE;
  const Linc_lin_frame_st_t * foundFramePtr;
  
  foundFramePtr = NULL;
  
  while ((mexIdx_u8 < LINC_MESSAGE_MAP_LEN) && (found_b == FALSE))
  {
    if (Linc_MessageMap[mexIdx_u8]->Id == pid)
    {
      /* Frame found */
      found_b = TRUE;
      
      /* Store frame reference */
      foundFramePtr = Linc_MessageMap[mexIdx_u8];
    }
    else
    {
      mexIdx_u8++;
    }
  }

  return foundFramePtr;
}

/**
 * @brief Compute PID for requested ID
 * @param ID
 * @return PID
 */
static uint8_t Linc_ComputePidFromId(uint8_t id)
{
  /* Support variables */
  uint8_t P0_byte;
  uint8_t P1_byte;
  uint8_t PID;
  
  /* Calculate parity bits */
  P0_byte = (id & 0x01) ^
           ((id & 0x02) >> 1 ) ^
           ((id & 0x04) >> 2 ) ^
           ((id & 0x10) >> 4 );
  
  P1_byte = ~(((id & 0x02) >> 1 ) ^
             ((id & 0x08) >> 3 ) ^
             ((id & 0x10) >> 4 ) ^
             ((id & 0x20) >> 5 ));
  
  /* Update id field */
  PID = (uint8_t)(P1_byte << 7) | (uint8_t)(P0_byte << 6) | id;
  
  return PID;
}

/**
 * @brief Set error type and increase error counter into selected frame
 * @param Error type
 * @return 
 */
static void Linc_SetErrorFrame(LINC_FrameError_t ErrorType)
{
  /* Support variables */
  uint8_t errorCount;
  
  /* Stop Timer */
  Linc_StopTimer();
  
  if (Linc_ReqFramePtr != NULL) 
  {       
    /* Set error type */
    *Linc_ReqFramePtr->FrameError = ErrorType;
    /* Set error couter */
    errorCount = *Linc_ReqFramePtr->FrameErrorCount;
    if(LINC_FRAME_MAX_ERROR_COUNT > errorCount)
    {
      /* Increase error counter */
      errorCount ++;      
      *Linc_ReqFramePtr->FrameErrorCount = errorCount;
    } 
  }
  /* Reset LINC status */
  Linc_Status = LINC_IDLE; 
 
}

/**
 * @brief Restart timer for check error
 * @param Timer value
 * @return 
 */
static void Linc_RestartTimer(uint32_t time)
{
  if(Linc_TimerStart == FALSE)
  {
    /* Stop timer */  
    TAU0_Channel3_Stop(); 
    
    /* Set up timer timeout */
    TAU0_Channel3_ChangeTimerCondition(time);
    /* Start count */
    TAU0_Channel3_Start();
    
    /* Set timer in start */
    Linc_TimerStart = TRUE;
  }
}

/**
 * @brief Stop timer for check error
 * @param Timer value
 * @return 
 */
static void Linc_StopTimer(void)
{
  /* Stop timer */  
  TAU0_Channel3_Stop(); 
  
  /* Set timer in stop */
  Linc_TimerStart = FALSE;
}

/**
 * @brief Select ID frame value to send according to frame type 
 * @param ID
 * @return PID
 */
static uint8_t Linc_GetIdFrame(LINC_MessageMap_t MsgHndle)
{
  /* Support variables */
  const Linc_lin_frame_st_t *Linc_FramePtr;
  const Linc_lin_frame_st_t *Linc_FrameSprPtr;
  uint8_t Linc_IdToSend = 0xFFU;
  uint8_t Linc_FramePriority = 0x00U;
  uint8_t byteIdx = 0x00U;
  uint8_t idSearch = 0x00U;	
  
  /* Select a pointer of frame */
//  Linc_FramePtr = Linc_FindFrameFromPid(id);  
  Linc_FramePtr = Linc_MessageMap[MsgHndle];
  
  switch (Linc_FramePtr->FrameType)
  {
    case FR_TYPE_UNCONDITIONAL:
      /* Keep ID frame value provided in the schedule table */
      Linc_IdToSend = Linc_FramePtr->Id;
      break;
    case FR_TYPE_SPORADIC:
      /* Select a Frame to send in this slot time according to request and 
      priority of message */
      
      for (byteIdx = 0U; byteIdx < Linc_FramePtr->DataLen; byteIdx++)
      {
        /* Analyzes all sporadic frame provided for this slot time */
        idSearch = Linc_FramePtr->DataBuff[byteIdx];
        /* Select a sporadic frame */        
        Linc_FrameSprPtr = Linc_FindFrameFromPid(idSearch);
        
        /* Verify if send request is activated */
        if(*Linc_FrameSprPtr->SprRequest == TRUE)
        {          
          if((Linc_FramePriority == 0x00) || 
             (Linc_FrameSprPtr->SprPriority < Linc_FramePriority))
          {
            /* Set new id to send and priority */
            Linc_IdToSend = Linc_FrameSprPtr->Id;
            Linc_FramePriority = Linc_FrameSprPtr->SprPriority;          
          }        
        }         
      }      
      break;
    case FR_TYPE_EVENT_TRIGGERED:
      /* To be define (Not applicable in this version) */
      Linc_IdToSend = Linc_FramePtr->Id;
      break;
    case FR_TYPE_DIAGNOSTIC:
      /* To be define (Not applicable in this version) */
      Linc_IdToSend = Linc_FramePtr->Id;
      break;      
      
    default:
      /* Should not be here */
      break;
  }
  
  return Linc_IdToSend;
  
}


/* ISR , interrupt management*/
static uint16_t Linc_INTTM03_Isr(void)
{
  /* Stop timer */ 
  Linc_StopTimer(); 
  TAU0_Channel3_Stop(); 
 
  switch (Linc_Status)
  {
    case LINC_BF_RD:
        /* Frame without field data (SYNC)*/
        Linc_SetErrorFrame(LINC_ERROR_TIMEOUT_RESPONSE); 
        break;   
    case LINC_SF_RD:
        /* Frame without field data (PID)*/
        Linc_SetErrorFrame(LINC_ERROR_TIMEOUT_RESPONSE); 
        break;      
    case LINC_RG_DATA:
        /* Frame without field data */
        Linc_SetErrorFrame(LINC_ERROR_TIMEOUT_RESPONSE); 
        break;
      
    case LINC_WAKE_UP:
        /* Send new WakeUp signal (only one break field) */
        Linc_WakeUpRequest = TRUE;
        /* Call task for LIN reception (slave task) */
        LINC_ReceptionTask(UARTD_CHN_HND);    
        break;
    case LINC_SLEEP: 
        /* If DUT resceives a signal from bus, but this isn't a break, but 
          only a signal. Recovery management is done by application and not 
          automatic into LIN driver.
          
          Here you can start the schedule table:
          Linc_Status = LINC_IDLE; 
      
          Here you can activate sleep mode for UARTD and transceiver:
          - LIN transceiver sleep mode activate - 
          LTMS_GoToSleep(UARTD_CHN_HND);
          - UARTD sleep mode activate -    
          UARTD_GoToSleep(UARTD_CHN_HND); */ 
          
          /* Recovery: Auto send a WakeUp Message on Bus */
          /*
          LINC_WakeUp(UARTD_CHN_HND);
          */
      
          /* Confirm of external Signal received */
          Linc_ReceivedExternalSignalConfirmed = TRUE;  

      break;        
    default:
      NOP();
 
  }
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM03));
}

/* Callback management */

/*----------------------------------------------------------------------------*/
/*Name :  LINC_RxDataCbk                                                      */
/*Role :  Callback of interrupt receiving data in UARTD module                */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void LINC_RxDataCbk(void)
{
  LINC_ReceptionTask(UARTD_CHN_HND); 
}


#endif /* end __LINC_IS_PRESENT__ */

/*______ E N D _____ (LINC.c) ________________________________________________*/
