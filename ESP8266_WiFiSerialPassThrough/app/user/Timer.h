#ifndef __TIMER__H
#define __TIMER__H
#define USE_US_TIMER //Ҫʹ�ú���os_timer_arm_us����Ҫ�ȶ���USE_US_TIMER

#include "osapi.h"
#include "user_interface.h"


void ICACHE_FLASH_ATTR os_timer1_init(void);
void ICACHE_FLASH_ATTR os_timer2_init(void);
void ICACHE_FLASH_ATTR os_timer3_init(void);
#endif
