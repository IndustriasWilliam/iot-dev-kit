#include "ltdc.h"



LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void){

	LTDC_LayerCfgTypeDef pLayerCfg = {0};

	hltdc.Instance = LTDC;
	hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	hltdc.Init.HorizontalSync = 31;
	hltdc.Init.VerticalSync = 7;
	hltdc.Init.AccumulatedHBP = 71;
	hltdc.Init.AccumulatedVBP = 13;
	hltdc.Init.AccumulatedActiveW = 871;
	hltdc.Init.AccumulatedActiveH = 613;
	hltdc.Init.TotalWidth = 879;
	hltdc.Init.TotalHeigh = 617;
	hltdc.Init.Backcolor.Blue = 0;
	hltdc.Init.Backcolor.Green = 80;
	hltdc.Init.Backcolor.Red = 150;
	if (HAL_LTDC_Init(&hltdc) != HAL_OK){
		Error_Handler();
	}
	pLayerCfg.WindowX0 = 0;
	pLayerCfg.WindowX1 = 800;
	pLayerCfg.WindowY0 = 0;
	pLayerCfg.WindowY1 = 600;
	pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
	pLayerCfg.FBStartAdress = 0xC0000000;
	pLayerCfg.ImageWidth = 800;
	pLayerCfg.ImageHeight = 600;
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK){
		Error_Handler();
	}
}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle){

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	if(ltdcHandle->Instance == LTDC){
		/** Initializes the peripherals clock
		*/
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
		PeriphClkInitStruct.PLL3.PLL3M = 5;
		PeriphClkInitStruct.PLL3.PLL3N = 45;
		PeriphClkInitStruct.PLL3.PLL3P = 10;
		PeriphClkInitStruct.PLL3.PLL3Q = 25;
		PeriphClkInitStruct.PLL3.PLL3R = 8;
		PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
		PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
		PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
		  Error_Handler();
		}

		/* LTDC clock enable */
		__HAL_RCC_LTDC_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOI_CLK_ENABLE();
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOG_CLK_ENABLE();
		/**LTDC GPIO Configuration
		PE5     ------> LTDC_G0
		PE6     ------> LTDC_G1
		PI9     ------> LTDC_VSYNC
		PI10     ------> LTDC_HSYNC
		PF10     ------> LTDC_DE
		PH2     ------> LTDC_R0
		PH3     ------> LTDC_R1
		PH8     ------> LTDC_R2
		PH9     ------> LTDC_R3
		PH10     ------> LTDC_R4
		PH11     ------> LTDC_R5
		PH12     ------> LTDC_R6
		PG6     ------> LTDC_R7
		PG7     ------> LTDC_CLK
		PH13     ------> LTDC_G2
		PH14     ------> LTDC_G3
		PH15     ------> LTDC_G4
		PI0     ------> LTDC_G5
		PI1     ------> LTDC_G6
		PI2     ------> LTDC_G7
		PG10     ------> LTDC_B2
		PG11     ------> LTDC_B3
		PG12     ------> LTDC_B1
		PG14     ------> LTDC_B0
		PI4     ------> LTDC_B4
		PI5     ------> LTDC_B5
		PI6     ------> LTDC_B6
		PI7     ------> LTDC_B7
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
							  |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
							  |GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_9
							  |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
							  |GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
							  |GPIO_PIN_12|GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

		/* LTDC interrupt Init */
		HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(LTDC_IRQn);
		HAL_NVIC_SetPriority(LTDC_ER_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
	}
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle){

	if(ltdcHandle->Instance == LTDC){
		/* USER CODE BEGIN LTDC_MspDeInit 0 */

		/* USER CODE END LTDC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_LTDC_CLK_DISABLE();

		/**LTDC GPIO Configuration
		PE5     ------> LTDC_G0
		PE6     ------> LTDC_G1
		PI9     ------> LTDC_VSYNC
		PI10     ------> LTDC_HSYNC
		PF10     ------> LTDC_DE
		PH2     ------> LTDC_R0
		PH3     ------> LTDC_R1
		PH8     ------> LTDC_R2
		PH9     ------> LTDC_R3
		PH10     ------> LTDC_R4
		PH11     ------> LTDC_R5
		PH12     ------> LTDC_R6
		PG6     ------> LTDC_R7
		PG7     ------> LTDC_CLK
		PH13     ------> LTDC_G2
		PH14     ------> LTDC_G3
		PH15     ------> LTDC_G4
		PI0     ------> LTDC_G5
		PI1     ------> LTDC_G6
		PI2     ------> LTDC_G7
		PG10     ------> LTDC_B2
		PG11     ------> LTDC_B3
		PG12     ------> LTDC_B1
		PG14     ------> LTDC_B0
		PI4     ------> LTDC_B4
		PI5     ------> LTDC_B5
		PI6     ------> LTDC_B6
		PI7     ------> LTDC_B7
		*/
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5|GPIO_PIN_6);

		HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
							  |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
							  |GPIO_PIN_7);

		HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

		HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_9
							  |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
							  |GPIO_PIN_14|GPIO_PIN_15);

		HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
							  |GPIO_PIN_12|GPIO_PIN_14);

		/* LTDC interrupt Deinit */
		HAL_NVIC_DisableIRQ(LTDC_IRQn);
		HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);

	}
}

