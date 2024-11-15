#ifndef __USART__H
#define __USART__H
#include "osapi.h"
#include "user_interface.h"
#include "mem.h"
#include "driver/uart.h"
#define UART_BUFF_LENTH 1024	//串口缓冲区大小
void ICACHE_FLASH_ATTR usart_init(uint32 Baudrate);

extern uint8 uart_buf[UART_BUFF_LENTH];
extern uint32_t Led_TIM_Counter;
#endif
