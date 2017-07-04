#include "ayplayer_spi.h"



void housekeeping_thread ( void* arg ) {
    (void) arg;
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    const spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >* spi1 = spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance();
    uint8_t out[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    while (1) {
        spi1->tx ( ( void* )out, 10, 10 );
        out[0]++;
        vTaskDelayUntil( &xLastWakeTime, 1000 );
    }
}


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
