/*
 * app_ethernet.h
 *
 *  Created on: 27 de dez de 2020
 *      Author: Deived William
 */

#ifndef INC_APP_ETHERNET_H_
#define INC_APP_ETHERNET_H_


#ifdef __cplusplus
 extern "C" {
#endif

#include "lwip/netif.h"


#define DHCP_OFF                   (uint8_t) 0
#define DHCP_START                 (uint8_t) 1
#define DHCP_WAIT_ADDRESS          (uint8_t) 2
#define DHCP_ADDRESS_ASSIGNED      (uint8_t) 3
#define DHCP_TIMEOUT               (uint8_t) 4
#define DHCP_LINK_DOWN             (uint8_t) 5


void ethernet_link_status_updated(struct netif *netif);
#if LWIP_DHCP
void DHCP_Thread(void* argument);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __APP_ETHERNET_H */
