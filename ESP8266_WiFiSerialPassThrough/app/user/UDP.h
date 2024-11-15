#ifndef __UDP__H
#define __UDP__H
#include "osapi.h"
#include "user_interface.h"
#include "espconn.h"
#include "ip_addr.h"
#include "mem.h"
#include "ets_sys.h"
#include "user_interface.h"
void ICACHE_FLASH_ATTR softap_init(void);//AP初始化
void ICACHE_FLASH_ATTR udpserver_init(void);//UDP初始化
uint8 ICACHE_FLASH_ATTR check_wifi_connection();//检测WIFI
void ICACHE_FLASH_ATTR UdpRcData_To_uart_rx();//UDP接受数据转发到串口



#endif
