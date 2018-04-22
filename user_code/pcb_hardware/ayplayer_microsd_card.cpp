#include "microsd_card_sdio.h"
#include "microsd_card_spi.h"
#include "pin.h"
#include "spi.h"

extern Pin							ayplayer_sd2_cs_pin_obj;
extern SpiMaster8Bit				ayplayer_spi2_obj;

microsdSpiCfg ayplayer_microsd_card_sd2_cfg = {
	.cs			= &ayplayer_sd2_cs_pin_obj,
	.s			= &ayplayer_spi2_obj,
	.slow		= SPI_BAUDRATEPRESCALER_256,
	.fast		= SPI_BAUDRATEPRESCALER_256
};

MicrosdSpi ayplayer_sd2_obj( &ayplayer_microsd_card_sd2_cfg );

const microsd_sdio_cfg_t ayplayer_microsd_card_sd1_cfg = {
	.wide						= SDIO_BUS_WIDE_4B,
	.div						= 0xFF,
	.dma_rx						= DMA2_Stream6,
	.dma_rx_ch					= DMA_CHANNEL_4,
	.dma_rx_irq_prio			= 6,
	.sdio_irq_prio				= 0								// Не используется.
};

MicrosdSdio ayplayer_sd1_obj( &ayplayer_microsd_card_sd1_cfg );

extern "C" {
	void dma2_stream6_handler		( void ) { ayplayer_sd1_obj.dmaRxHandler(); };
};

// number = 1/0.
// return 1 - карта есть.
uint32_t check_sd ( uint32_t number ) {
	( void )number;
	return 1;
}
