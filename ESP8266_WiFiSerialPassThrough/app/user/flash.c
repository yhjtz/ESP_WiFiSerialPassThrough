#include "flash.h"
/* 0x3FF000
 * 0x3FF000/0x1000=0x3FF=1023
 * */
#define FLASH_SECTOR     1023    // Ҫʹ�õ���������
#define FLASH_ADDRESS    (FLASH_SECTOR * SPI_FLASH_SEC_SIZE) // ������ʼ��ַ


void Flash_write(uint8_t* buff,uint32_t len) {
    // ��������
    spi_flash_erase_sector(FLASH_SECTOR);

    // д�����ݵ� Flash
    spi_flash_write(FLASH_ADDRESS, buff, len);
}

void Flash_read(uint8_t* buff,uint32_t len) {

    // �� Flash �ж�ȡ����
    spi_flash_read(FLASH_ADDRESS, buff, len);

}
