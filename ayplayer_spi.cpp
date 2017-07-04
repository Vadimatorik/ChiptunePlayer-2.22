#include "ayplayer_spi.h"

extern "C" {
void spi1_handler ( void ) {
    const spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >* spi1 = spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance();
    spi1->handler();
}
}

int ayplayer_spi_init ( void ) {
    const spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >* spi1 = spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance();
    spi1->reinit();
    ayplayer_nvic.irq_set_priority( IRQ_NAME::SPI1, IRQ_PRIO::PRIO_6 );
    ayplayer_nvic.irq_enable( IRQ_NAME::SPI1 );
    return 0;
}
