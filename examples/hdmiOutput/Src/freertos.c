
/* USER CODE BEGIN 1 */

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "spi.h"
#include "nrf24l01.h"
#include "fatfs.h"
#include "ethernetif.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "app_ethernet.h"

#define NRF24L01_PAYLOAD_LENGTH	32u



/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048 * 4
};

osThreadId_t GUI_TaskHandle;
const osThreadAttr_t GUI_Task_attributes = {
  .name = "GUI_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 2048 * 4
};

osThreadId_t NRF24L01_TxCommandHandle;
const osThreadAttr_t NRF24L01_TxCommand_attributes = {
		.name = "TXCmd_Task",
		.priority = (osPriority_t)osPriorityNormal,
		.stack_size = 512 * 2
};


osThreadId_t EtherLink_TaskHandle;
const osThreadAttr_t EtherLink_Task_attributes = {
  .name = "EtherLink",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 2
};

osThreadId_t DHCP_TaskHandle;
const osThreadAttr_t DHCP_attributes = {
		.name = "DHCP",
		.priority = (osPriority_t)osPriorityBelowNormal,
		.stack_size = 1024 * 2
};

osThreadId_t BlinkLedStatus_TaskHandle;
const osThreadAttr_t Blink_attributes = {
		.name = "BlinkLed",
		.priority = (osPriority_t)osPriorityNormal,
		.stack_size = 1024 * 2
};


nrf24l01 nrf;
uint8_t rxBuffer[NRF24L01_PAYLOAD_LENGTH];
nrf24l01_config config;

static const uint8_t rx_address[5] = {1, 2, 3, 4, 6};
static const uint8_t tx_address[5] = {1, 2, 3, 4, 5};
struct netif gnetif;

//QualityAirModule qualityAirModule = {
//		.moduleID = 0xF875,
//		.airQualityIndex = 0.0f,
//		.carbonDioxide = 0.0f,
//		.humidity = 0.0f,
//		.temperature = 0.0f
//};

  /* File object for USBH */


void StartDefaultTask(void *argument);
void NRF24L01TxCommand_Task(void* argument);
void BlinkLedStatus_Task(void* argument);

extern void MX_LWIP_Init(void);
extern void MX_USB_HOST_Init(void);
extern void TouchGFX_Task(void *argument);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */


/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
	called if a stack overflow is detected. */
}


__weak void vApplicationMallocFailedHook(void)
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created. It is also called by various parts of the
	demo application. If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
}



void nrf_packet_received_callback(nrf24l01* dev, uint8_t* data)
{
    dev->rx_busy = 0;


    HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);

}

/**
  * @brief  Initializes the lwIP stack
  * @param  None
  * @retval None
  */
static void Netif_Config(void)
{
	ip_addr_t ipaddr;
	ip_addr_t netmask;
	ip_addr_t gw;

#if LWIP_DHCP
	ip_addr_set_zero_ip4(&ipaddr);
	ip_addr_set_zero_ip4(&netmask);
	ip_addr_set_zero_ip4(&gw);
#else
	IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
	IP_ADDR4(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
	IP_ADDR4(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
#endif /* LWIP_DHCP */

	/* add the network interface */
	netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
	/*  Registers the default network interface. */
	netif_set_default(&gnetif);

	ethernet_link_status_updated(&gnetif);

#if LWIP_NETIF_LINK_CALLBACK
	netif_set_link_callback(&gnetif, ethernet_link_status_updated);

	EtherLink_TaskHandle = osThreadNew(ethernet_link_thread, (void*)&gnetif, &EtherLink_Task_attributes);
#endif

#if LWIP_DHCP
	/* Start DHCPClient */
	DHCP_TaskHandle = osThreadNew(DHCP_Thread, (void*)&gnetif, &DHCP_attributes);
#endif
}
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void){
	config.data_rate        = NRF_DATA_RATE_1MBPS;
	config.tx_power         = NRF_TX_PWR_0dBm;
	config.crc_width        = NRF_CRC_WIDTH_1B;
	config.addr_width       = NRF_ADDR_WIDTH_5;
	config.payload_length   = (uint8_t)NRF24L01_PAYLOAD_LENGTH;    // maximum is 32 bytes
	config.retransmit_count = 15;   // maximum is 15 times
	config.retransmit_delay = 0x0F; // 4000us, LSB:250us
	config.rf_channel       = 0;
	config.rx_address       = rx_address;
	config.tx_address       = tx_address;
	config.rx_buffer        = rxBuffer;

	config.spi         = &hspi2;
	config.spi_timeout = 10; // milliseconds
	config.ce_port     = NRF24_CE_GPIO_Port;
	config.ce_pin      = NRF24_CE_Pin;
	config.irq_port    = NRF24_IRQ_GPIO_Port;
	config.irq_pin     = NRF24_IRQ_Pin;
	config.csn_port    = NRF24_CSN_GPIO_Port;
	config.csn_pin     = NRF24_CSN_Pin;

	nrf_init(&nrf, &config);

//	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
 	GUI_TaskHandle = osThreadNew(TouchGFX_Task, NULL, &GUI_Task_attributes);
//   	NRF24L01_TxCommandHandle = osThreadNew(NRF24L01TxCommand_Task, NULL, &NRF24L01_TxCommand_attributes);
  	BlinkLedStatus_TaskHandle = osThreadNew(BlinkLedStatus_Task, NULL, &Blink_attributes);
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void *argument)
{

	/* Create tcp_ip stack thread */
	tcpip_init(NULL, NULL);

	/* Initialize the LwIP stack */
	Netif_Config();

	for( ;; )
	{
		/* Delete the Init Thread */
		osThreadTerminate(NULL);
	}
}

void BlinkLedStatus_Task(void* argument)
{
	for(;;)
	{
		HAL_GPIO_TogglePin(LED_STATUS_GPIO_Port, LED_STATUS_Pin);
		osDelay(100);
	}
}

/**
  * @brief  Function implementing the NRF24L01TxCommand_Task thread.
  * @param  argument: Not used
  * @retval None
  */
void NRF24L01TxCommand_Task(void* argument)
{
	for(;;)
	{
//		nrf_send_packet(&nrf, (const uint8_t*)&qualityAirModule.moduleID);
		osDelay(500);
	}
}

/* USER CODE END 1 */

