#ifndef __GPIO__H
#define __GPIO__H
#include "osapi.h"
#include "user_interface.h"

void ICACHE_FLASH_ATTR LED_init(void);
void ICACHE_FLASH_ATTR LED_set(uint8_t value);
void ICACHE_FLASH_ATTR KEY_init(void);
uint8_t ICACHE_FLASH_ATTR KEY_Scan(void);


#endif
