#include "GPIO.h"

/*初始化 LED */
void ICACHE_FLASH_ATTR
LED_init(void){
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);//led
	GPIO_OUTPUT_SET(GPIO_ID_PIN(2),1);//点灯
}

/*设置LED状态:0灭,1亮,其他翻转
 * */
void ICACHE_FLASH_ATTR
LED_set(uint8_t value){
	static bool Led_status=0;
	if(value == 0){
		GPIO_OUTPUT_SET(GPIO_ID_PIN(2),1);
		Led_status=0;
	}
	else if(value == 1){
		GPIO_OUTPUT_SET(GPIO_ID_PIN(2),0);
		Led_status=1;
	}
	else{
		Led_status=!Led_status;
		GPIO_OUTPUT_SET(GPIO_ID_PIN(2),Led_status);
	}
}

/*按键设置*/
void ICACHE_FLASH_ATTR
KEY_init(void){
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);
}
uint8_t ICACHE_FLASH_ATTR
KEY_Scan(void){
	return GPIO_INPUT_GET(GPIO_ID_PIN(4));
}
