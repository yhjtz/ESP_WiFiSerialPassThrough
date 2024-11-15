#include "Timer.h"
#include "UDP.h"
#include "GPIO.h"
#include "usart.h"
#include "set.h"
uint32_t Led_TIM_Counter= 500*1000;
os_timer_t os_timer1;             //声明一个软件定时器变量
os_timer_t os_timer2;             //声明一个软件定时器变量
os_timer_t os_timer3;             //声明一个软件定时器变量

void ICACHE_FLASH_ATTR os_timer2_cb(void){
	LED_set(2);
}
/******************************************************************************
 * 函数名      : 软件定时器初始化函数
 * 描述          : 初始化软件定时器
 * 参数          : 无
 * 返回值      : 无
*******************************************************************************/
void ICACHE_FLASH_ATTR
os_timer1_init(void)
{

	//------------------------------------------------------------------------------------
	//步骤1：关闭定时器
	os_timer_disarm(&os_timer1);

	//------------------------------------------------------------------------------------
	//设置定时器,定时时间到会触发回调函数工作
	os_timer_setfn(&os_timer1, (os_timer_func_t	*)UdpRcData_To_uart_rx, NULL);

	//------------------------------------------------------------------------------------
	//启动定时器，设置定时间隔为100us
	os_timer_arm_us(&os_timer1, 100,1);
}


void ICACHE_FLASH_ATTR
os_timer2_init(void)
{

	//------------------------------------------------------------------------------------
	//步骤1：关闭定时器
	os_timer_disarm(&os_timer2);

	//------------------------------------------------------------------------------------
	//设置定时器,定时时间到会触发回调函数uart_rx工作
	os_timer_setfn(&os_timer2, (os_timer_func_t	*)os_timer2_cb, NULL);

	//------------------------------------------------------------------------------------
	//启动定时器，设置定时间隔
	os_timer_arm_us(&os_timer2, Led_TIM_Counter,1);
}

void ICACHE_FLASH_ATTR os_timer3_cb(void){
		uint32 len = 0;
		//计算接收到的数据长度
		len = rx_buff_deq(uart_buf, UART_BUFF_LENTH);
		if(len!=0){
			flash_data_rcProcess(uart_buf,len);
			os_memset(uart_buf,0,UART_BUFF_LENTH);
		}


}
void ICACHE_FLASH_ATTR
os_timer3_init(void)
{

	//------------------------------------------------------------------------------------
	//步骤1：关闭定时器
	os_timer_disarm(&os_timer3);

	//------------------------------------------------------------------------------------
	//设置定时器,定时时间到会触发回调函数uart_rx工作
	os_timer_setfn(&os_timer3, (os_timer_func_t	*)os_timer3_cb, NULL);

	//------------------------------------------------------------------------------------
	//启动定时器，设置定时间隔为100us
	os_timer_arm_us(&os_timer3, 15*1000,1);
}

