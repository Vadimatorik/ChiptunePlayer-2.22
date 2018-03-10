#include "microsd_card.h"
#include "pin.h"
#include "spi.h"

extern pin							ayplayer_sd2_cs_pin_obj;
extern spi_master_8bit				ayplayer_spi2_obj;

microsd_spi_cfg_t microsd_card_cfg = {
    .cs         = &ayplayer_sd2_cs_pin_obj,
	.p_spi      = &ayplayer_spi2_obj,
    .slow       = SPI_BAUDRATEPRESCALER_256,
    .fast       = SPI_BAUDRATEPRESCALER_256
};

microsd_spi ayplayer_sd2_obj( &microsd_card_cfg );
