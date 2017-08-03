#include "ayplayer_spi.h"

spi_master_8bit_hardware_os < SPI1_CFG_OBJ_PARAM > spi1;
spi_master_8bit_hardware_os < SPI2_CFG_OBJ_PARAM > spi2;
spi_master_8bit_hardware_os < SPI3_CFG_OBJ_PARAM > spi3;

int ayplayer_spi_init ( void ) {
    spi1.reinit();
    spi2.reinit();
    spi3.reinit();

    spi1.on();
    spi2.on();
    spi3.on();

    return 0;
}
