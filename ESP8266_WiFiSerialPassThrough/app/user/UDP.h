#ifndef __UDP__H
#define __UDP__H
#include "osapi.h"
#include "user_interface.h"
#include "espconn.h"
#include "ip_addr.h"
#include "mem.h"
#include "ets_sys.h"
#include "user_interface.h"
void ICACHE_FLASH_ATTR softap_init(void);//AP��ʼ��
void ICACHE_FLASH_ATTR udpserver_init(void);//UDP��ʼ��
uint8 ICACHE_FLASH_ATTR check_wifi_connection();//���WIFI
void ICACHE_FLASH_ATTR UdpRcData_To_uart_rx();//UDP��������ת��������



#endif
