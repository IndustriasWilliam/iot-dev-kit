/* USER CODE BEGIN 1 */

#include "main.h"
#include "stm32h7xx_it.h"

extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern DMA2D_HandleTypeDef hdma2d;
extern CEC_HandleTypeDef hcec;
extern LTDC_HandleTypeDef hltdc;
extern TIM_HandleTypeDef htim7;



/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void){
	while (1)
	{
	}
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void){

	while (1){

	}
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void){

	while (1){

	}
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void){

	while (1){

	}
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void){

	while (1){

	}
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void){

}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void){
	HAL_TIM_IRQHandler(&htim7);

}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void){
	HAL_LTDC_IRQHandler(&hltdc);
}

/**
  * @brief This function handles LTDC global error interrupt.
  */
void LTDC_ER_IRQHandler(void){
	HAL_LTDC_IRQHandler(&hltdc);

}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void){
	HAL_DMA2D_IRQHandler(&hdma2d);
}

/**
  * @brief This function handles HDMI-CEC global interrupt.
  */
void CEC_IRQHandler(void){
	HAL_CEC_IRQHandler(&hcec);
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void){
	HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
}



/* USER CODE END 1 */
