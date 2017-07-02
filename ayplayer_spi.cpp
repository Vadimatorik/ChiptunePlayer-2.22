#include "ayplayer_spi.h"

extern "C" {
void spi1_handler ( void ) {
    spi1.handler();
}
}

int ayplayer_spi_init ( void ) {
    spi1.reinit();

    return 0;
}
