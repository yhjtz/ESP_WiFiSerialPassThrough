#include "set.h"
#include "mem.h"
#include "driver/uart.h"
#include "flash.h"


Flash_SetInfo_t FlashSetInfo;//flash中存储的信息
InitInfo_t init_Info;

void protocol_decode(uint8_t* buff,Flash_SetInfo_t* FlashSetInfo){
	FlashSetInfo->WIFI_Number[4]='\0';
	FlashSetInfo->WIFI_Key[8]='\0';
	//该函数根据协议解码
	FlashSetInfo->CMD=buff[4];
	FlashSetInfo->BaudRate=buff[5]<<24|buff[6]<<16|buff[7]<<8|buff[8];
	memcpy(FlashSetInfo->WIFI_Number,&buff[9],4);
	memcpy(FlashSetInfo->WIFI_Key,&buff[13],8);
	FlashSetInfo->client_IP_Num=buff[21];
	FlashSetInfo->Udp_local_port=buff[22]<<24|buff[23]<<16|buff[24]<<8|buff[25];
	FlashSetInfo->Udp_remote_port=buff[26]<<24|buff[27]<<16|buff[28]<<8|buff[29];
}

void flash_data_rcProcess(uint8_t* buff,uint32_t len){
	if (len==33)
	{
		if(StrCompare("SET=",buff,0) && StrCompare("END",buff,30)){
		  //uart0_tx_buffer(buff,len);
		  Flash_write(buff,33);
		  uart0_tx_buffer(buff,len);
		  uart0_tx_buffer((uint8_t*)"set successfully!\n",18);
		  //protocol_decode(buff,&FlashSetInfo);
//		  os_printf("CMD=%X\n",FlashSetInfo.CMD);
//		  os_printf("BaudRate=%d\n",FlashSetInfo.BaudRate);
//		  os_printf("WIFI_Number=%s\n",FlashSetInfo.WIFI_Number);
//		  os_printf("WIFI_Key=%s\n",FlashSetInfo.WIFI_Key);
//		  os_printf("client_IP_Num=%d\n",FlashSetInfo.client_IP_Num);
//		  os_printf("Udp_local_port=%d\n",FlashSetInfo.Udp_local_port);
//		  os_printf("Udp_remote_port=%d\n",FlashSetInfo.Udp_local_port);

		}
		return;
	}
	else if(StrCompare("GET_SET",buff,0)){
		load_LocalSetInfo();
		os_printf("BaudRate=%d\n",init_Info.BaudRate);
		os_printf("CMD=%02X\n",FlashSetInfo.CMD);
		os_printf("WIFI_Name=%s\n",init_Info.WIFI_Name);
		os_printf("WIFI_Key=%s\n",init_Info.WIFI_Key);
		os_printf("IP={%d,%d,%d,%d}\n",init_Info.client_IP[0],init_Info.client_IP[1],init_Info.client_IP[2],init_Info.client_IP[3]);
		os_printf("Udp_local_port=%d\n",init_Info.Udp_local_port);
		os_printf("Udp_remote_port=%d\n",init_Info.Udp_remote_port);
		return;

	}
	else if(StrCompare("DO_RST",buff,0)){
		system_restart();
		return;

	}
	else if(StrCompare("GET_ACK",buff,0)){
		 uart0_tx_buffer((uint8_t*)"ACK\n",4);
		return;
	}
}

void load_LocalSetInfo(void){
	uint8_t buff[33];
	//加载本地设置信息
	Flash_read(buff,33);
	//解码
	protocol_decode(buff,&FlashSetInfo);
	if(FlashSetInfo.CMD==0xBF){
		init_Info.BaudRate=FlashSetInfo.BaudRate;

		os_strcpy(init_Info.WIFI_Name,"FlySET_\0");
		os_strcat(init_Info.WIFI_Name,FlashSetInfo.WIFI_Number);

		os_strcpy(init_Info.WIFI_Key,FlashSetInfo.WIFI_Key);

		init_Info.client_IP[0]=192;
		init_Info.client_IP[1]=168;
		init_Info.client_IP[2]=4;
		init_Info.client_IP[3]=FlashSetInfo.client_IP_Num;
		init_Info.Udp_local_port=FlashSetInfo.Udp_local_port;
		init_Info.Udp_remote_port=FlashSetInfo.Udp_remote_port;

	}
	else{
		init_Info.BaudRate=57600;

		os_strcpy(init_Info.WIFI_Name,"FlySET_0000\0");
		os_strcpy(init_Info.WIFI_Key,"12345678\0");

		init_Info.client_IP[0]=192;
		init_Info.client_IP[1]=168;
		init_Info.client_IP[2]=4;
		init_Info.client_IP[3]=2;
		init_Info.Udp_local_port=14550;
		init_Info.Udp_remote_port=14550;
	}

}

/*
	  字符串比较,比较字符串最大长度不超过50
	  str:指向对比的字符串常量
	  Buff:指向被对比字符串所在缓冲区
	  StartNum:表示从Buff缓冲区第几个字符开始
*/
uint8_t StrCompare(char* str, uint8_t* Buff, uint8_t StartNum) {
	char sstr[50];//字符串比较缓冲区
	for (uint8_t i = 0; i < strlen(str); i++) {
		sstr[i] = (char)Buff[StartNum + i];
	}
	sstr[strlen(str)] = '\0';
	if (strncmp(str, sstr, strlen(str)) != 0) return 0;//字符串相等返回0
	else return 1;
}

