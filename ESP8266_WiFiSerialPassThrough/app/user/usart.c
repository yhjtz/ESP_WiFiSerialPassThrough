#include "usart.h"
uint8 uart_buf[UART_BUFF_LENTH]={0};         //开辟一个串口数据缓存空间


void ICACHE_FLASH_ATTR
usart_init(uint32 Baudrate){
	uart_init(Baudrate,115200);
	//由于IO2被用作LED，这里重定义uart1的引脚
//	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_U1TXD);
//	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_U1RXD);
}


