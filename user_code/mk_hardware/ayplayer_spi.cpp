#include "ayplayer_spi.h"

spi_master_8bit_hardware_os_cfg_t spi1_cfg = {
    .mutex = nullptr
};

spi_master_8bit_hardware_os_cfg_t spi2_cfg = {
    .mutex = nullptr
};

spi_master_8bit_hardware_os_cfg_t spi3_cfg = {
    .mutex = nullptr
};

spi_master_8bit_hardware_os < SPI1_CFG_OBJ_PARAM >      spi1        ( &spi1_cfg );
spi_master_8bit_hardware_os < SPI2_SLOW_CFG_OBJ_PARAM > spi2_slow   ( &spi2_cfg );
spi_master_8bit_hardware_os < SPI2_FAST_CFG_OBJ_PARAM > spi2_fast   ( &spi2_cfg );
spi_master_8bit_hardware_os < SPI3_CFG_OBJ_PARAM >      spi3        ( &spi3_cfg );

int ayplayer_spi_init ( void ) {
    m_spi3_init();
    spi1.reinit();
    spi3.reinit();
    spi1.on();
    spi3.on();
    return 0;
}
