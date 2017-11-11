#include "ayplayer_microsd_card.h"

microsd_spi_cfg_t microsd_card_cfg = {
    .cs         = &sd2_cs_pin_obj,
    .p_spi      = &spi2_obj,
    .slow       = SPI_BAUDRATEPRESCALER_16,
    .fast       = SPI_BAUDRATEPRESCALER_16
};

microsd_spi sd2( &microsd_card_cfg );
