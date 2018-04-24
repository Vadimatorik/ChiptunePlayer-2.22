#include "microsd_card_sdio.h"
#include "microsd_card_spi.h"
#include "pin.h"
#include "spi.h"

extern Pin							sd2Cs;
extern SpiMaster8Bit				spi2;

microsdSpiCfg sd2Cfg = {
	.cs			= &sd2Cs,
	.s			= &spi2,
	.slow		= SPI_BAUDRATEPRESCALER_256,
	.fast		= SPI_BAUDRATEPRESCALER_256
};

MicrosdSpi sd2( &sd2Cfg );

const microsd_sdio_cfg_t sd1Cfg = {
	.wide						= SDIO_BUS_WIDE_4B,
	.div						= 0xFF,
	.dma_rx						= DMA2_Stream6,
	.dma_rx_ch					= DMA_CHANNEL_4,
	.dma_rx_irq_prio			= 6,
	.sdio_irq_prio				= 0								// Не используется.
};

MicrosdSdio sd1( &sd1Cfg );

extern "C" {
};

// number = 1/0.
// return 1 - карта есть.
uint32_t check_sd ( uint32_t number ) {
	( void )number;
	return 1;
}
