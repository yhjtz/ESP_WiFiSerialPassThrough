#include "usart.h"
uint8 uart_buf[UART_BUFF_LENTH]={0};         //����һ���������ݻ���ռ�


void ICACHE_FLASH_ATTR
usart_init(uint32 Baudrate){
	uart_init(Baudrate,115200);
	//����IO2������LED�������ض���uart1������
//	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_U1TXD);
//	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_U1RXD);
}


