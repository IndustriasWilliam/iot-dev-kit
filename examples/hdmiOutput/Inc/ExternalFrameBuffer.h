/*
 * ExternalFrameBuffer.h
 *
 *  Created on: Aug 20, 2022
 *      Author: Deived William
 */

#include "main.h"

#ifndef INC_EXTERNALFRAMEBUFFER_H_
#define INC_EXTERNALFRAMEBUFFER_H_


extern SDRAM_HandleTypeDef hsdram1;

void MX_FMC_Init(void);
void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram);
void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram);

#endif
