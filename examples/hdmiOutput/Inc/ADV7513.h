#ifndef ADV7513_H_
#define ADV7513_H_

#include "main.h"




/**
  * @brief  ADV7533 I2C Addresses 0x7A / 0x78
  */
#define ADV7513_I2C_CEC_ADDRESS        		((uint8_t)0x78)
#define ADV7513_I2C_MAINMAP_ADDRESS0		((uint8_t)0x72)
#define	ADV7513_I2C_MAINMAP_ADDRESS1		((uint8_t)0x7A)

#define ADV7513_I2C_EDID_ADDRESS			((uint8_t)0x7E)

/**
  * @brief  ADV7513 Aspect ratio
  */
#define ADV7513_ASPECT_RATIO_16_9        ((uint8_t)0x00)
#define ADV7513_ASPECT_RATIO_4_3         ((uint8_t)0x01)



/**
  * @brief  ADV7533 Aspect ratio
  */
#define ADV7513_MODE_HDMI                0x1
#define ADV7513_MODE_DVI                 0x0


/*Hot Plug Detect Register Map*/

#define HPD_Reg_BitState(reg_value)					(((unsigned char)(reg_value >> 6)) & 0x01)
#define HPD_Reg_MonitorSenseState(reg_value)		(((unsigned char)(reg_value >> 5)) & 0x01)
#define HPD_Reg_InterruptEnableW(value)				(((unsigned char)(value << 7)))
#define HPD_Reg_InterrutEnableR(reg_value)			(((unsigned char)(reg_value >> 7)) & 0x01)
#define HPD_Reg_InterruptEnableSenseW(value)  		(((unsigned char)(value << 6)))
#define HPD_Reg_InterruptEnableSenseR(reg_value)  	(((unsigned char)(reg_value >> 6)) & 0x01)


/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K     192000U
#define AUDIO_FREQUENCY_176K     176400U
#define AUDIO_FREQUENCY_96K       96000U
#define AUDIO_FREQUENCY_88K       88200U
#define AUDIO_FREQUENCY_48K       48000U
#define AUDIO_FREQUENCY_44K       44100U
#define AUDIO_FREQUENCY_32K       32000U
#define AUDIO_FREQUENCY_22K       22050U
#define AUDIO_FREQUENCY_16K       16000U
#define AUDIO_FREQUENCY_11K       11025U
#define AUDIO_FREQUENCY_8K         8000U

/* Audio bits per sample */
#define AUDIO_RESOLUTION_8B                 8U
#define AUDIO_RESOLUTION_16B                16U
#define AUDIO_RESOLUTION_24B                24U
#define AUDIO_RESOLUTION_32B                32U

#define AUDIO_OUT_DEVICE_HDMI               5U

/* Audio Mute state */
#define BSP_AUDIO_MUTE_DISABLED             0U
#define BSP_AUDIO_MUTE_ENABLED              1U


/* Common Error codes */
#define BSP_ERROR_NONE                    0
#define BSP_ERROR_NO_INIT                -1
#define BSP_ERROR_WRONG_PARAM            -2
#define BSP_ERROR_BUSY                   -3
#define BSP_ERROR_PERIPH_FAILURE         -4
#define BSP_ERROR_COMPONENT_FAILURE      -5
#define BSP_ERROR_UNKNOWN_FAILURE        -6
#define BSP_ERROR_UNKNOWN_COMPONENT      -7
#define BSP_ERROR_BUS_FAILURE            -8
#define BSP_ERROR_CLOCK_FAILURE          -9
#define BSP_ERROR_MSP_FAILURE            -10
#define BSP_ERROR_FEATURE_NOT_SUPPORTED  -11


/* Audio Out states */
#define AUDIO_OUT_STATE_RESET               0U
#define AUDIO_OUT_STATE_PLAYING             1U
#define AUDIO_OUT_STATE_STOP                2U
#define AUDIO_OUT_STATE_PAUSE               3U

/* Audio Out instances number */
#define AUDIO_OUT_INSTANCES_NBR             2U

#define POS_VAL(VAL)                  (POSITION_VAL(VAL) - 4U)
#define VOLUME_OUT_CONVERT(Volume)    (((Volume) > 100)? 63:((uint8_t)(((Volume) * 63) / 100)))

#define SELECT_AUDIO_I2S         1
#define SELECT_AUDIO_SPDIF_SAI   0


/* Audio bits per sample */
#define AUDIO_RESOLUTION_8B                 8U
#define AUDIO_RESOLUTION_16B                16U
#define AUDIO_RESOLUTION_24B                24U
#define AUDIO_RESOLUTION_32B                32U



typedef struct{
	uint32_t Device;
	uint32_t SampleRate;
	uint32_t BitsPerSample;
	uint32_t ChannelsNbr;
	uint32_t Volume;
}BSP_AUDIO_Init_t;

typedef struct{
	uint32_t Instance;            /* Audio OUT instance              */
	uint32_t Device;              /* Audio OUT device to be used     */
	uint32_t SampleRate;          /* Audio OUT Sample rate           */
	uint32_t BitsPerSample;       /* Audio OUT Sample Bit Per Sample */
	uint32_t Volume;              /* Audio OUT volume                */
	uint32_t ChannelsNbr;         /* Audio OUT number of channel     */
	uint32_t IsMute;              /* Mute state                      */
	uint32_t State;               /* Audio OUT State                 */
	uint32_t IsMspCallbacksValid; /* Is Msp Callbacks registered      */
}AUDIO_OUT_Ctx_t;

typedef struct{
	uint32_t AudioFrequency;
	uint32_t AudioMode;
	uint32_t DataSize;
	uint32_t MonoStereoMode;
	uint32_t ClockStrobing;
	uint32_t Synchro;
	uint32_t OutputDrive;
	uint32_t SynchroExt;
	uint32_t FrameLength;
	uint32_t ActiveFrameLength;
	uint32_t SlotActive;
}MX_SAI_Config;

typedef struct{
	uint32_t SampleRate;
	uint32_t AudioMode;
	uint32_t FullDuplexMode;
}MX_I2S_Config;

/* (USE_HAL_SAI_REGISTER_CALLBACKS == 1)||(USE_HAL_I2S_REGISTER_CALLBACKS == 1) */
#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)||(USE_HAL_I2S_REGISTER_CALLBACKS == 1)
typedef struct{
#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)
	pSAI_CallbackTypeDef  pMspSaiInitCb;
	pSAI_CallbackTypeDef  pMspSaiDeInitCb;
#endif
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1)
	pI2S_CallbackTypeDef  pMspI2sInitCb;
	pI2S_CallbackTypeDef  pMspI2sDeInitCb;
#endif
}BSP_AUDIO_OUT_Cb_t;
#endif


void BSP_VIDEO_Init(void);
uint8_t BSP_VIDEO_ReadDeviceVersion(void);
uint16_t BSP_VIDEO_GetDeviceID(void);

int32_t BSP_AUDIO_OUT_Init(uint32_t Instance, BSP_AUDIO_Init_t* AudioInit);
int32_t BSP_AUDIO_OUT_DeInit(uint32_t Instance);

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1) || (USE_HAL_I2S_REGISTER_CALLBACKS == 1)
int32_t BSP_AUDIO_OUT_RegisterMspCallbacks (uint32_t Instance, BSP_AUDIO_OUT_Cb_t *CallBacks);
int32_t BSP_AUDIO_OUT_RegisterDefaultMspCallbacks (uint32_t Instance);
#endif /* (USE_HAL_SAI_REGISTER_CALLBACKS == 1)|| (USE_HAL_I2S_REGISTER_CALLBACKS == 1) */

int32_t BSP_AUDIO_OUT_Play(uint32_t Instance, uint8_t* pData, uint32_t NbrOfBytes);
int32_t BSP_AUDIO_OUT_Pause(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Resume(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Stop(uint32_t Instance);
int32_t BSP_AUDIO_OUT_Mute(uint32_t Instance);
int32_t BSP_AUDIO_OUT_UnMute(uint32_t Instance);
int32_t BSP_AUDIO_OUT_IsMute(uint32_t Instance, uint32_t *IsMute);


int32_t BSP_AUDIO_OUT_SetDevice(uint32_t Instance, uint32_t Device);
int32_t BSP_AUDIO_OUT_GetDevice(uint32_t Instance, uint32_t *Device);

int32_t BSP_AUDIO_OUT_SetSampleRate(uint32_t Instance, uint32_t SampleRate);
int32_t BSP_AUDIO_OUT_GetSampleRate(uint32_t Instance, uint32_t *SampleRate);

int32_t BSP_AUDIO_OUT_SetBitsPerSample(uint32_t Instance, uint32_t BitsPerSample);
int32_t BSP_AUDIO_OUT_GetBitsPerSample(uint32_t Instance, uint32_t *BitsPerSample);

int32_t BSP_AUDIO_OUT_SetChannelsNbr(uint32_t Instance, uint32_t ChannelNbr);
int32_t BSP_AUDIO_OUT_GetChannelsNbr(uint32_t Instance, uint32_t *ChannelNbr);

int32_t BSP_AUDIO_OUT_SetVolume(uint32_t Instance, uint32_t Volume);
int32_t BSP_AUDIO_OUT_GetVolume(uint32_t Instance, uint32_t *Volume);
int32_t BSP_AUDIO_OUT_GetState(uint32_t Instance, uint32_t *State);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred.*/
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance);

/* This function is called when half of the requested buffer has been transferred. */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance);

/* This function is called when an Interrupt due to transfer error on or peripheral error occurs. */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance);

void BSP_AUDIO_OUT_SelectInterface(uint32_t interface);

#endif
