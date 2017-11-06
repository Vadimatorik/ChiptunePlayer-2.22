#include "ayplayer_spi.h"

spi_cfg spi1_cfg = {
};

spi_cfg spi2_slow_cfg = {
};

spi_cfg spi2_fast_cfg = {
};

spi_cfg spi3_cfg = {
};


spi_master_8bit spi1( &spi1_cfg );
spi_master_8bit spi2_slow( &spi2_slow_cfg );
spi_master_8bit spi2_fast( &spi2_fast_cfg );
spi_master_8bit spi3( &spi3_cfg );

int ayplayer_spi_init ( void ) {
    m_spi3_init();
    spi1.reinit();
    spi3.reinit();
    spi1.on();
    spi3.on();
    return 0;
}
