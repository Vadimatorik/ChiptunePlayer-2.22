#include "ayplayer_spi.h"

const spi_master_hardware_os< EC_SPI_NAME                :: SPI1,
                              EC_SPI_CFG_CLK_POLARITY    :: IDLE_0,
                              EC_SPI_CFG_CLK_PHASE       :: FIRST,
                              EC_SPI_CFG_NUMBER_LINE     :: LINE_2,
                              EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,
                              EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,
                              EC_SPI_CFG_FRAME_FORMAT    :: MOTOROLA,
                              EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_2,
                              EC_SPI_CFG_CS              :: ENABLED > spi1;

void housekeeping_thread ( void* arg ) {
    (void) arg;
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    uint8_t out[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    while (1) {
        spi1.tx ( ( void* )out, 10, 10 );
       // spi1.rx( in );
        out[0]++;
        vTaskDelayUntil( &xLastWakeTime, 1000 );
    }
}


extern "C" {
void spi1_handler ( void ) {
    spi1.handler();
}
}

int ayplayer_spi_init ( void ) {
    spi1.reinit();
    ayplayer_nvic.irq_set_priority( IRQ_NAME::SPI1, IRQ_PRIO::PRIO_6 );
    ayplayer_nvic.irq_enable( IRQ_NAME::SPI1 );
    return 0;
}
