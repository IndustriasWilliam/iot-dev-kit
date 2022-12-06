/*
 * ExternalFrameBuffer.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Deived William
 */


#include "ExternalFrameBuffer.h"

typedef enum {PASSED = 0, FAILED = !PASSED} TestStatus_t;
/* Exported constants --------------------------------------------------------*/

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8  */
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_16

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)



/*uncomment this line to regulate the decoding frame rate to the native video frame rate */
#define USE_FRAMERATE_REGULATION



SDRAM_HandleTypeDef hsdram1;
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);

/* FMC initialization function */
void MX_FMC_Init(void){
	FMC_SDRAM_TimingTypeDef SdramTiming = {0};

	/** Perform the SDRAM1 memory initialization sequence
	*/
	hsdram1.Instance = FMC_SDRAM_DEVICE;
	/* hsdram1.Init */
	hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
	hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_10;
	hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
	hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
	hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
	hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
	hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
	hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
	/* SdramTiming */
	SdramTiming.LoadToActiveDelay = 2;
	SdramTiming.ExitSelfRefreshDelay = 6;
	SdramTiming.SelfRefreshTime = 4;
	SdramTiming.RowCycleDelay = 6;
	SdramTiming.WriteRecoveryTime = 2;
	SdramTiming.RPDelay = 2;
	SdramTiming.RCDDelay = 2;

	if(HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK){
		Error_Handler( );
	}

	SDRAM_Initialization_Sequence(&hsdram1);

#ifdef TEST_SDRAM
	/*##-2- SDRAM memory read/write access */
	if(SDRAM_Test() != PASSED){
		Error_Handler();
	}
#endif
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(FMC_Initialized){
		return;
	}
	FMC_Initialized = 1;

	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();

	/** FMC GPIO Configuration
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC2_C   ------> FMC_SDNE0
	PC3_C   ------> FMC_SDCKE0
	PH5   ------> FMC_SDNWE
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	PE0   ------> FMC_NBL0
	PE1   ------> FMC_NBL1
	*/
	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* sdramHandle){
	HAL_FMC_MspInit();
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
	if(FMC_DeInitialized){
		return;
	}
	FMC_DeInitialized = 1;
	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_DISABLE();

	/** FMC GPIO Configuration
	PF0   ------> FMC_A0
	PF1   ------> FMC_A1
	PF2   ------> FMC_A2
	PF3   ------> FMC_A3
	PF4   ------> FMC_A4
	PF5   ------> FMC_A5
	PC2_C   ------> FMC_SDNE0
	PC3_C   ------> FMC_SDCKE0
	PH5   ------> FMC_SDNWE
	PF11   ------> FMC_SDNRAS
	PF12   ------> FMC_A6
	PF13   ------> FMC_A7
	PF14   ------> FMC_A8
	PF15   ------> FMC_A9
	PG0   ------> FMC_A10
	PG1   ------> FMC_A11
	PE7   ------> FMC_D4
	PE8   ------> FMC_D5
	PE9   ------> FMC_D6
	PE10   ------> FMC_D7
	PE11   ------> FMC_D8
	PE12   ------> FMC_D9
	PE13   ------> FMC_D10
	PE14   ------> FMC_D11
	PE15   ------> FMC_D12
	PD8   ------> FMC_D13
	PD9   ------> FMC_D14
	PD10   ------> FMC_D15
	PD14   ------> FMC_D0
	PD15   ------> FMC_D1
	PG2   ------> FMC_A12
	PG4   ------> FMC_BA0
	PG5   ------> FMC_BA1
	PG8   ------> FMC_SDCLK
	PD0   ------> FMC_D2
	PD1   ------> FMC_D3
	PG15   ------> FMC_SDNCAS
	PE0   ------> FMC_NBL0
	PE1   ------> FMC_NBL1
	*/

	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_11|GPIO_PIN_12
						  |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOC, GPIO_PIN_2|GPIO_PIN_3);

	HAL_GPIO_DeInit(GPIOH, GPIO_PIN_5);

	HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4
						  |GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
						  |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);

	HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14
						  |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1);
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* sdramHandle){
	HAL_FMC_MspDeInit();
}


#ifdef TEST_SDRAM

TestStatus_t SDRAM_Test(void){
	/* Fill the buffer to write */
	Fill_Buffer(aTxBuffer, BUFFER_SIZE, 0x24424578);

	/* Write data to the SDRAM memory */
	for(uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++)
	{
		*(__IO uint32_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR + 4*uwIndex) = aTxBuffer[uwIndex];
	}

	/* Read back data from the SDRAM memory */
	for(uwIndex = 0; uwIndex < BUFFER_SIZE; uwIndex++)
	{
		aRxBuffer[uwIndex] = *(__IO uint32_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR + 4*uwIndex);
	}

	/*##-3- Checking data integrity ############################################*/

	for(uwIndex = 0; (uwIndex < BUFFER_SIZE) && (uwWriteReadStatus == 0); uwIndex++)
	{
		if(aRxBuffer[uwIndex] != aTxBuffer[uwIndex])
		{
			uwWriteReadStatus++;
		}
	}

	if(uwWriteReadStatus != PASSED)
	{
		return FAILED;
	}

	return PASSED;
}

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset){
	uint32_t tmpIndex = 0;

	/* Put in global buffer different values */
	for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
	{
		pBuffer[tmpIndex] = tmpIndex + uwOffset;
	}
}
#endif
/**
  * @brief  Perform the SDRAM external memory initialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram){
	FMC_SDRAM_CommandTypeDef Command = {0};
	__IO uint32_t tmpmrd =0;
	/* Step 3:  Configure a clock configuration enable command */
	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 4: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	HAL_Delay(1);

	/* Step 5: Configure a PALL (precharge all) command */
	Command.CommandMode = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 6 : Configure a Auto-Refresh command */
	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 8;
	Command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 7: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_2   |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	//hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));
//	HAL_SDRAM_ProgramRefreshRate(hsdram, 0x0603);
	HAL_SDRAM_ProgramRefreshRate(hsdram,1854);
}
