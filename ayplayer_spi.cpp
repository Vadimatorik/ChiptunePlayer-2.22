#include "ayplayer_spi.h"

spi_master_hardware_os< EC_SPI_NAME                :: SPI1,
EC_SPI_CFG_CLK_POLARITY    :: IDLE_0,
EC_SPI_CFG_CLK_PHASE       :: FIRST,
EC_SPI_CFG_NUMBER_LINE     :: LINE_2,
EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,
EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,
EC_SPI_CFG_FRAME_FORMAT    :: TI,
EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_2,
EC_SPI_CFG_CS              :: DISABLED > spi1;

extern "C" {
void spi1_handler ( void ) {
    //spi1.handler();
}
}



int ayplayer_spi_init ( void ) {
    spi1.reinit();

    return 0;
}
