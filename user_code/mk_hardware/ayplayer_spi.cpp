#include "ayplayer_spi.h"

spi_cfg spi1_cfg = {
};

spi_cfg spi2_slow_cfg = {
};

spi_cfg spi2_fast_cfg = {
};

spi_cfg spi3_cfg = {
};


spi_master_8bit spi1_obj( &spi1_cfg );
spi_master_8bit spi2_slow_obj( &spi2_slow_cfg );
spi_master_8bit spi2_fast_obj( &spi2_fast_cfg );
spi_master_8bit spi3_obj( &spi3_cfg );

int ayplayer_spi_init ( void ) {
    m_spi3_init();
    spi1_obj.reinit();
    spi3_obj.reinit();
    spi1_obj.on();
    spi3_obj.on();
    return 0;
}
