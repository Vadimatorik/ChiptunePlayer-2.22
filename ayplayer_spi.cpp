#include "ayplayer_spi.h"

int ayplayer_spi_init ( void ) {
    spi1.reinit();
    return 0;
}
