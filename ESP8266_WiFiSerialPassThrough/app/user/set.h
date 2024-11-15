#ifndef __SET_H
#define __SET_H
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
typedef struct{
	char header[4];	//数据头
	uint8_t CMD;//当该位值为0XBF时，读取FLASH
	uint32_t BaudRate;
	uint8_t WIFI_Number[5];
	uint8_t WIFI_Key[9];
	uint8_t client_IP_Num;
	uint32_t Udp_local_port;
	uint32_t Udp_remote_port;
	char tail[3];
}Flash_SetInfo_t;

typedef struct{
	uint32_t BaudRate;
	uint8_t WIFI_Name[12];
	uint8_t WIFI_Key[9];
	uint8_t client_IP[4];
	uint32_t Udp_local_port;
	uint32_t Udp_remote_port;
}InitInfo_t;

void flash_data_rcProcess(uint8_t* buff,uint32_t len);
uint8_t StrCompare(char* str, uint8_t* Buff, uint8_t StartNum);
void load_LocalSetInfo(void);
extern Flash_SetInfo_t FlashSetInfo;
extern uint8_t flash_data_rcBUFF[40];
extern InitInfo_t init_Info;
#endif
