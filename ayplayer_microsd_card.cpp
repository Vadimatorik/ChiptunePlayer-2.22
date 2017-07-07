#include "ayplayer_microsd_card.h"

microsd_spi_cfg_t microsd_card_cfg = {
    .cs                 = &sd2_cs_obj,
    .init_spi_baudrate  = 0,//100000,
    .spi_baudrate_job   = 0//10000000,
    //.uart_fd = &uart2_fd,
};

microsd_spi sd2(&microsd_card_cfg);

void ayplayer_microsd_card_init (void) {
    sd2.reinit( spi_master_hardware_os< SPI2_CFG_OBJ_PARAM >::instance() );
}
