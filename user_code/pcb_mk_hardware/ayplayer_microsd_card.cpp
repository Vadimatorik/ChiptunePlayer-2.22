#include "ayplayer_microsd_card.h"

microsd_spi_cfg_t microsd_card_cfg = {
    .cs         = &ayplayer_sd2_cs_pin_obj,
    .p_spi      = &spi2_obj,
    .slow       = SPI_BAUDRATEPRESCALER_256,
    .fast       = SPI_BAUDRATEPRESCALER_256
};

microsd_spi sd2( &microsd_card_cfg );
