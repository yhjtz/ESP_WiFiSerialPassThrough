#ifndef __TIMER__H
#define __TIMER__H
#define USE_US_TIMER //要使用函数os_timer_arm_us，需要先定义USE_US_TIMER

#include "osapi.h"
#include "user_interface.h"


void ICACHE_FLASH_ATTR os_timer1_init(void);
void ICACHE_FLASH_ATTR os_timer2_init(void);
void ICACHE_FLASH_ATTR os_timer3_init(void);
#endif
