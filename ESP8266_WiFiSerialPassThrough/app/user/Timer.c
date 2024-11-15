#include "Timer.h"
#include "UDP.h"
#include "GPIO.h"
#include "usart.h"
#include "set.h"
uint32_t Led_TIM_Counter= 500*1000;
os_timer_t os_timer1;             //����һ�������ʱ������
os_timer_t os_timer2;             //����һ�������ʱ������
os_timer_t os_timer3;             //����һ�������ʱ������

void ICACHE_FLASH_ATTR os_timer2_cb(void){
	LED_set(2);
}
/******************************************************************************
 * ������      : �����ʱ����ʼ������
 * ����          : ��ʼ�������ʱ��
 * ����          : ��
 * ����ֵ      : ��
*******************************************************************************/
void ICACHE_FLASH_ATTR
os_timer1_init(void)
{

	//------------------------------------------------------------------------------------
	//����1���رն�ʱ��
	os_timer_disarm(&os_timer1);

	//------------------------------------------------------------------------------------
	//���ö�ʱ��,��ʱʱ�䵽�ᴥ���ص���������
	os_timer_setfn(&os_timer1, (os_timer_func_t	*)UdpRcData_To_uart_rx, NULL);

	//------------------------------------------------------------------------------------
	//������ʱ�������ö�ʱ���Ϊ100us
	os_timer_arm_us(&os_timer1, 100,1);
}


void ICACHE_FLASH_ATTR
os_timer2_init(void)
{

	//------------------------------------------------------------------------------------
	//����1���رն�ʱ��
	os_timer_disarm(&os_timer2);

	//------------------------------------------------------------------------------------
	//���ö�ʱ��,��ʱʱ�䵽�ᴥ���ص�����uart_rx����
	os_timer_setfn(&os_timer2, (os_timer_func_t	*)os_timer2_cb, NULL);

	//------------------------------------------------------------------------------------
	//������ʱ�������ö�ʱ���
	os_timer_arm_us(&os_timer2, Led_TIM_Counter,1);
}

void ICACHE_FLASH_ATTR os_timer3_cb(void){
		uint32 len = 0;
		//������յ������ݳ���
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
	//����1���رն�ʱ��
	os_timer_disarm(&os_timer3);

	//------------------------------------------------------------------------------------
	//���ö�ʱ��,��ʱʱ�䵽�ᴥ���ص�����uart_rx����
	os_timer_setfn(&os_timer3, (os_timer_func_t	*)os_timer3_cb, NULL);

	//------------------------------------------------------------------------------------
	//������ʱ�������ö�ʱ���Ϊ100us
	os_timer_arm_us(&os_timer3, 15*1000,1);
}

