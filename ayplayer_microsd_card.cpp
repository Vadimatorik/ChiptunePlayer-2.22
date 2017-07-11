#include "ayplayer_microsd_card.h"

microsd_spi_cfg_t microsd_card_cfg = {
    .cs                 = &sd2_cs_obj,
    .init_spi_baudrate  = 0,     //100000,
    .spi_baudrate_job   = 0,     //10000000,
    .p_spi              = &spi2
};

microsd_spi sd2( &microsd_card_cfg );

void ayplayer_microsd_card_init (void) {
    sd2.reinit();
}
