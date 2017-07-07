#include "ayplayer_spi.h"

const spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >* spi1 = nullptr;
const spi_master_hardware_os< SPI2_CFG_OBJ_PARAM >* spi2 = nullptr;
const spi_master_hardware_os< SPI3_CFG_OBJ_PARAM >* spi3 = nullptr;

extern "C" {

void spi1_handler ( void ) {
    spi1->handler();
}

void spi2_handler ( void ) {
    spi2->handler();
}

void spi3_handler ( void ) {
    spi3->handler();
}

}

int ayplayer_spi_init ( void ) {
    spi1 = spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance();
    spi2 = spi_master_hardware_os< SPI2_CFG_OBJ_PARAM >::instance();
    spi3 = spi_master_hardware_os< SPI3_CFG_OBJ_PARAM >::instance();

    spi1->reinit();
    spi2->reinit();
    spi3->reinit();

    ayplayer_nvic.irq_set_priority( IRQ_NAME::SPI1, IRQ_PRIO::PRIO_6 );
    ayplayer_nvic.irq_enable( IRQ_NAME::SPI1 );
    ayplayer_nvic.irq_set_priority( IRQ_NAME::SPI2, IRQ_PRIO::PRIO_6 );
    ayplayer_nvic.irq_enable( IRQ_NAME::SPI2 );
    ayplayer_nvic.irq_set_priority( IRQ_NAME::SPI3, IRQ_PRIO::PRIO_6 );
    ayplayer_nvic.irq_enable( IRQ_NAME::SPI3 );
    return 0;
}
