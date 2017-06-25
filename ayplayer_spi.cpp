#include "ayplayer_spi.h"

int ayplayer_spi_init ( void ) {
    spi1.spi_reinit();
    spi1.spi_on();
    return 0;
}
