#ifndef __FALSH_H
#define __FALSH_H
#include "spi_flash.h"
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"
void Flash_write(uint8_t* buff,uint32_t len);
void Flash_read(uint8_t* buff,uint32_t len);

#endif


