#include "flash.h"
/* 0x3FF000
 * 0x3FF000/0x1000=0x3FF=1023
 * */
#define FLASH_SECTOR     1023    // 要使用的闪存扇区
#define FLASH_ADDRESS    (FLASH_SECTOR * SPI_FLASH_SEC_SIZE) // 扇区起始地址


void Flash_write(uint8_t* buff,uint32_t len) {
    // 擦除扇区
    spi_flash_erase_sector(FLASH_SECTOR);

    // 写入数据到 Flash
    spi_flash_write(FLASH_ADDRESS, buff, len);
}

void Flash_read(uint8_t* buff,uint32_t len) {

    // 从 Flash 中读取数据
    spi_flash_read(FLASH_ADDRESS, buff, len);

}
