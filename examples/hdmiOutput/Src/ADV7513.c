/*
 * ADV7513.c
 *
 *  Created on: 14 de ago de 2020
 *      Author: Deived
 */


#include "ADV7513.h"
#include "main.h"
#include "stdio.h"
#include "i2c.h"
#include "i2s.h"
#include "sai.h"


#define ADV7513_I2C_DELAY 5000


AUDIO_OUT_Ctx_t Audio_Out_Ctx[AUDIO_OUT_INSTANCES_NBR];


static void HDMI_IO_Write(uint8_t deviceAddress, uint8_t reg, uint8_t value){
	while(HAL_I2C_Mem_Write(&hi2c1,
			deviceAddress,
			reg,
			sizeof(uint8_t),
			&value,
			sizeof(uint8_t),
			ADV7513_I2C_DELAY) != HAL_OK);
}

static uint8_t HDMI_IO_Read(uint8_t deviceAddress, uint8_t reg){
	uint8_t tmp = 0;

	while(HAL_I2C_Mem_Read(&hi2c1,
			deviceAddress,
			reg,
			I2C_MEMADD_SIZE_8BIT,
			&tmp,
			1,
			ADV7513_I2C_DELAY) != HAL_OK);

	return tmp;
}


void BSP_VIDEO_Init(void){
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x98, 0x03);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x01, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x02, 0x18);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x03, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x14, 0x70);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x15, 0x20);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x16, 0x30);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x18, 0x46);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x40, 0x80);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x41, 0x10);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x49, 0xA8);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x55, 0x10);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x56, 0x98);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x96, 0xF6);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x73, 0x07);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x76, 0x1F);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x98, 0x03);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x99, 0x02);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x9A, 0xE0);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x9C, 0x30);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x9D, 0x61);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xA2, 0xA4);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xA3, 0xA4);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xA5, 0x04);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xAB, 0x40);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xAF, 0x16);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xBA, 0x60);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xD1, 0xFF);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xDE, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xE4, 0x60);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0xFA, 0x7D);

	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x17, 0x60);



	//Full rbg out

	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x18, 0xA8);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x19, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1A, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1B, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1C, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1D, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1E, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x1F, 0x00);

	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x20, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x21, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x22, 0x08);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x23, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x24, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x25, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x26, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x27, 0x00);

	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x28, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x29, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2A, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2B, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2C, 0x08);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2D, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2E, 0x00);
	HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x2F, 0x00);
}
/**
  * @brief  Power on the ADV7513 bridge.
  * @param  None
  * @retval None
  */

void BSP_PowerOn(void){


}

/**
  * @brief  Power off the ADV7513 bridge.
  * @param  None
  * @retval None
  */

void BSP_PowerDown(void){

}

/**
  * @brief  Get Device version from ADV7513 bridge.
  * @param  None
  * @retval uint8_t
  */

uint8_t BSP_VIDEO_ReadDeviceVersion(void){
	uint8_t tmp = 0;

	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS1, 0x00);

	return tmp;
}

/**
  * @brief  Get Device ID from ADV7513 bridge.
  * @param  None
  * @retval uint16_t
  */

uint16_t BSP_VIDEO_GetDeviceID(void){
	uint16_t tmp = 0;

	tmp = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS1, 0xF5) << 8;
	tmp |= HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS1, 0xF6);

	return tmp;
}


void BSP_AUDIO_OUT_SelectInterface(uint32_t interface){

	uint8_t res = 0;

	if(interface == SELECT_AUDIO_I2S){
		HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x0A, 0x00);
		/*Enable I2S0 channel and configure formart*/
		HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x0C, 0x04);
	}else{
		/*Enable SPDIF and internal MCLK generator*/
		HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x0B, 0xA0);
		res = HDMI_IO_Read(ADV7513_I2C_MAINMAP_ADDRESS1, 0x0A);
		res ^= 16;
		HDMI_IO_Write(ADV7513_I2C_MAINMAP_ADDRESS1, 0x0A, res);
	}
}


int32_t BSP_AUDIO_OUT_Init(uint32_t Instance, BSP_AUDIO_Init_t* AudioInit){
	int32_t ret = BSP_ERROR_NONE;
	uint8_t res = 0;

	if(Instance >= AUDIO_OUT_INSTANCES_NBR){
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else{
		/* Fill Audio_Out_Ctx structure */
		Audio_Out_Ctx[Instance].Device         = AudioInit->Device;
		Audio_Out_Ctx[Instance].Instance       = Instance;
		Audio_Out_Ctx[Instance].SampleRate     = AudioInit->SampleRate;
		Audio_Out_Ctx[Instance].BitsPerSample  = AudioInit->BitsPerSample;
		Audio_Out_Ctx[Instance].ChannelsNbr    = AudioInit->ChannelsNbr;
		Audio_Out_Ctx[Instance].Volume         = AudioInit->Volume;
		Audio_Out_Ctx[Instance].State          = AUDIO_OUT_STATE_RESET;

		BSP_AUDIO_OUT_SelectInterface(Instance);


//		if(Instance == 0U){
//			if(MX_SAI1_Init(AudioInit->SampleRate) != HAL_OK){
//				ret = BSP_ERROR_PERIPH_FAILURE;
//			}
//		}
//		else if(Instance == 1U){
//			if(MX_I2S1_Init(AudioInit->SampleRate) != HAL_OK){
//				ret = BSP_ERROR_PERIPH_FAILURE;
//			}
//		}
	}

	return ret;
}

int32_t BSP_AUDIO_OUT_DeInit(uint32_t Instance){

}

#if (USE_HAL_SAI_REGISTER_CALLBACKS == 1)||(USE_HAL_I2S_REGISTER_CALLBACKS == 1)

int32_t BSP_AUDIO_OUT_RegisterMspCallbacks (uint32_t Instance, BSP_AUDIO_OUT_Cb_t *CallBacks){

}
#endif

int32_t BSP_AUDIO_OUT_RegisterDefaultMspCallbacks (uint32_t Instance){

}




/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hsai SAI handle
  * @retval None
  */

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(hsai);

	/* Manage the remaining file size and new address offset: This function
	 should be coded by user (its prototype is already declared in stm32h7b3i_eval_audio.h) */
	BSP_AUDIO_OUT_TransferComplete_CallBack(0);
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hsai  SAI handle
  * @retval None
  */
void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(hsai);

	/* Manage the remaining file size and new address offset: This function
	 should be coded by user (its prototype is already declared in stm32h7b3i_eval_audio.h) */
	BSP_AUDIO_OUT_HalfTransfer_CallBack(0);
}

/**
  * @brief  SAI error callbacks.
  * @param  hsai SAI handle
  * @retval None
  */
void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai){
	UNUSED(hsai);
	BSP_AUDIO_OUT_Error_CallBack(0);
}



/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hi2s I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(hi2s);

	/* Manage the remaining file size and new address offset: This function
	 should be coded by user (its prototype is already declared in stm32h7b3i_eval_audio.h) */
	BSP_AUDIO_OUT_TransferComplete_CallBack(1);
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hi2s  I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(hi2s);

	/* Manage the remaining file size and new address offset: This function
	should be coded by user (its prototype is already declared in stm32h7b3i_eval_audio.h) */
	BSP_AUDIO_OUT_HalfTransfer_CallBack(1);

	HAL_I2S_ErrorCallback(hi2s);
}

/**
  * @brief  I2S error callbacks
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(hi2s);


}

/**
  * @brief  Starts playing audio stream from a data buffer for a determined size.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  pData         pointer on data address
  * @param  NbrOfBytes   Size of total samples in bytes
  *                      BitsPerSample: 16 or 32
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_Play(uint32_t Instance, uint8_t* pData, uint32_t NbrOfBytes){
	int32_t ret = BSP_ERROR_NONE;

	if((Instance >= AUDIO_OUT_INSTANCES_NBR) || (((NbrOfBytes / (Audio_Out_Ctx[Instance].BitsPerSample/8U)) > 0xFFFFU))){
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else if (Audio_Out_Ctx[Instance].State != AUDIO_OUT_STATE_STOP){
		ret = BSP_ERROR_BUSY;
	}
	else{
		if(Instance == 0U){
			if(HAL_SAI_Transmit_DMA(&hsai_BlockA1, pData, (uint16_t)(NbrOfBytes /(Audio_Out_Ctx[Instance].BitsPerSample/8U))) != HAL_OK){
				ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
		else{
			if(HAL_I2S_Transmit_DMA(&hi2s1, (uint16_t*)pData, (uint16_t)(NbrOfBytes /(Audio_Out_Ctx[Instance].BitsPerSample/8U))) != HAL_OK){
			ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
		if(ret == BSP_ERROR_NONE){
			/* Update BSP AUDIO OUT state */
			Audio_Out_Ctx[Instance].State = AUDIO_OUT_STATE_PLAYING;
		}
	}

	/* Return BSP status */
	return ret;
}
/**
  * @brief  This function Pauses the audio file stream. In case
  *         of using DMA, the DMA Pause feature is used.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @note   When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play()
  *          function for resume could lead to unexpected behavior).
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_Pause(uint32_t Instance){

	int32_t ret = BSP_ERROR_NONE;

	if (Instance >= AUDIO_OUT_INSTANCES_NBR){
		ret = BSP_ERROR_WRONG_PARAM;
	}
	/* Check audio out state */
	else if(Audio_Out_Ctx[Instance].State != AUDIO_OUT_STATE_PLAYING){
		ret = BSP_ERROR_BUSY;
	}
	else{
		/* Pause DMA transfer of audio samples towards the serial audio interface */
	    if(Instance == 0U){
	    	if(HAL_SAI_DMAPause(&hsai_BlockA1) != HAL_OK){
	    		ret = BSP_ERROR_PERIPH_FAILURE;
	    	}
	    }
	    else{
	    	if(HAL_I2S_DMAPause(&hi2s1) != HAL_OK){
	    		ret = BSP_ERROR_PERIPH_FAILURE;
	    	}
	    	else{
	    		/* Workaround */
	    		hi2s1.Instance->IFCR = 0x800;
	    	}
		}
	}
	if(ret == BSP_ERROR_NONE){
		/* Update BSP AUDIO OUT state */
		Audio_Out_Ctx[Instance].State = AUDIO_OUT_STATE_PAUSE;
	}

	/* Return BSP status */
	return ret;
}

/**
  * @brief   Resumes the audio file stream.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @note    When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play()
  *          function for resume could lead to unexpected behavior).
  * @retval BSP status
  */

int32_t BSP_AUDIO_OUT_Resume(uint32_t Instance){
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= AUDIO_OUT_INSTANCES_NBR){
		ret = BSP_ERROR_WRONG_PARAM;
	}
	/* Check audio out state */
	else if(Audio_Out_Ctx[Instance].State != AUDIO_OUT_STATE_PAUSE){
		ret = BSP_ERROR_BUSY;
	}
	else{
		/* Resume DMA transfer of audio samples towards the serial audio interface */
		if(Instance == 0U){
			if(HAL_SAI_DMAResume(&hsai_BlockA1) != HAL_OK){
				ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
		else{
			if(HAL_I2S_DMAResume(&hi2s1) != HAL_OK){
				ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
	}
	if(ret == BSP_ERROR_NONE){
		/* Update BSP AUDIO OUT state */
		Audio_Out_Ctx[Instance].State = AUDIO_OUT_STATE_PLAYING;
	}

	/* Return BSP status */
	return ret;
}


/**
  * @brief  Stops audio playing and Power down the Audio Codec.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_Stop(uint32_t Instance){
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= AUDIO_OUT_INSTANCES_NBR){
		ret = BSP_ERROR_WRONG_PARAM;
	}
	/* Check audio out state */
	else if(Audio_Out_Ctx[Instance].State == AUDIO_OUT_STATE_STOP){
		/* Nothing to do */
	}
	else if((Audio_Out_Ctx[Instance].State != AUDIO_OUT_STATE_PLAYING) && (Audio_Out_Ctx[Instance].State != AUDIO_OUT_STATE_PAUSE)){
		ret = BSP_ERROR_BUSY;
	}
	else{
		if(Instance == 0U){
			if(HAL_SAI_DMAStop(&hsai_BlockA1)!= HAL_OK){
				ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
		else{
			if(HAL_I2S_DMAStop(&hi2s1) != HAL_OK){
				ret = BSP_ERROR_PERIPH_FAILURE;
			}
		}
	}
	if(ret == BSP_ERROR_NONE){
		/* Update BSP AUDIO OUT state */
		Audio_Out_Ctx[Instance].State = AUDIO_OUT_STATE_STOP;
	}

	/* Return BSP status */
	return ret;
}

/**
  * @brief  Enables the MUTE
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_Mute(uint32_t Instance){

}

/**
  * @brief  Disables the MUTE mode
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_UnMute(uint32_t Instance){

}


/**
  * @brief  Check whether the MUTE mode is enabled or not
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  IsMute    pointer to mute state
  * @retval Mute status
  */
int32_t BSP_AUDIO_OUT_IsMute(uint32_t Instance, uint32_t *IsMute){

}


/**
  * @brief  Updates the audio frequency.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  SampleRate Audio frequency used to play the audio stream.
  * @note   This API should be called after the BSP_AUDIO_OUT_Init() to adjust the
  *         audio frequency.
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_SetSampleRate(uint32_t Instance, uint32_t SampleRate){
	int32_t ret = BSP_ERROR_NONE;


	/* Return BSP status */
	return ret;
}

/**
  * @brief  Get the audio frequency.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  SampleRate  Audio frequency used to play the audio stream.
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_GetSampleRate(uint32_t Instance, uint32_t *SampleRate){

}


/**
  * @brief  Get the audio Resolution.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  BitsPerSample  Audio Resolution used to play the audio stream.
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_SetBitsPerSample(uint32_t Instance, uint32_t BitsPerSample){

}

/**
  * @brief  Get the audio Resolution.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  BitsPerSample  Audio Resolution used to play the audio stream.
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_GetBitsPerSample(uint32_t Instance, uint32_t *BitsPerSample){

}

/**
  * @brief  Set the audio Channels number.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  ChannelNbr  Audio Channels number used to play the audio stream (It can only be 2U for I2S Instance)
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_SetChannelsNbr(uint32_t Instance, uint32_t ChannelNbr){

}

/**
  * @brief  Get the audio Channels number.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  ChannelNbr     Audio Channels number used to play the audio stream.
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_GetChannelsNbr(uint32_t Instance, uint32_t *ChannelNbr){

}

/**
  * @brief  Controls the current audio volume level.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  Volume    Volume level to be set in percentage from 0% to 100% (0 for
  *         Mute and 100 for Max volume level).
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_SetVolume(uint32_t Instance, uint32_t Volume){

}

/**
  * @brief  Get the current audio volume level.
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  Volume    pointer to volume to be returned
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_GetVolume(uint32_t Instance, uint32_t *Volume){

}

/**
  * @brief  Get Audio Out state
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @param  State     Audio Out state
  * @retval BSP status
  */
int32_t BSP_AUDIO_OUT_GetState(uint32_t Instance, uint32_t *State){

}





/**
  * @brief  Manages the DMA full Transfer complete event
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval None
  */
__weak void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(Instance);
}

/**
  * @brief  Manages the DMA Half Transfer complete event
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval None
  */
__weak void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(Instance);
}

/**
  * @brief  Manages the DMA FIFO error event
  * @param  Instance AUDIO OUT Instance. It can only be 0 (SAI) or 1 (I2S)
  * @retval None
  */
__weak void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance){
	/* Prevent unused argument(s) compilation warning */
	UNUSED(Instance);
}


