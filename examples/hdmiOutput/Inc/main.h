#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* USER CODE BEGIN Includes */

/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

typedef enum
{
	False,
	True = !False
}Boolean;


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


#define NRF24_CSN_Pin GPIO_PIN_2
#define NRF24_CSN_GPIO_Port GPIOE
#define NRF24_CE_Pin GPIO_PIN_3
#define NRF24_CE_GPIO_Port GPIOE
#define NRF24_IRQ_Pin GPIO_PIN_4
#define NRF24_IRQ_GPIO_Port GPIOE
#define SD_DETECT_Pin GPIO_PIN_12
#define SD_DETECT_GPIO_Port GPIOD
#define LED_STATUS_Pin GPIO_PIN_13
#define LED_STATUS_GPIO_Port GPIOD
#define ADV7513_PD_Pin GPIO_PIN_6
#define ADV7513_PD_GPIO_Port GPIOC
#define ADV7513_INT_Pin GPIO_PIN_7
#define ADV7513_INT_GPIO_Port GPIOC
#define USB_FAULT_Pin GPIO_PIN_4
#define USB_FAULT_GPIO_Port GPIOD
#define USB_EN_Pin GPIO_PIN_5
#define USB_EN_GPIO_Port GPIOD


#ifdef __cplusplus
}
#endif

#endif
