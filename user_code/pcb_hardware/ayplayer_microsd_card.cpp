#include "microsd_card_sdio.h"
#include "microsd_card_spi.h"
#include "pin.h"
#include "spi.h"

extern pin							ayplayer_sd2_cs_pin_obj;
extern spi_master_8bit				ayplayer_spi2_obj;

microsd_spi_cfg_t ayplayer_microsd_card_sd2_cfg = {
    .cs         = &ayplayer_sd2_cs_pin_obj,
	.p_spi      = &ayplayer_spi2_obj,
    .slow       = SPI_BAUDRATEPRESCALER_256,
    .fast       = SPI_BAUDRATEPRESCALER_256
};

microsd_spi ayplayer_sd2_obj( &ayplayer_microsd_card_sd2_cfg );

const microsd_sdio_cfg_t ayplayer_microsd_card_sd1_cfg = {
	.wide						= SDIO_BUS_WIDE_1B,
	.div						= IS_SDIO_CLKDIV( 0xFF ),
	.dma_tx						= DMA2_Stream3,
	.dma_rx						= DMA2_Stream6,
	.dma_tx_ch					= DMA_CHANNEL_4,
	.dma_rx_ch					= DMA_CHANNEL_4
};

microsd_sdio ayplayer_sd1_obj( &ayplayer_microsd_card_sd1_cfg );

extern "C" {
	void DMA2_Stream6_IRQHandler		( void ) { ayplayer_sd1_obj.dma_rx_handler(); };
	void DMA2_Stream3_IRQHandler		( void ) { ayplayer_sd1_obj.dma_tx_handler(); };
	void SDIO_IRQHandler				( void ) { ayplayer_sd1_obj.sdio_handler(); };
};
