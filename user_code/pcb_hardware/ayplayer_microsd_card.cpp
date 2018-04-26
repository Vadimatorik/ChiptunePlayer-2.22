#include "microsd_card_sdio.h"
#include "microsd_card_spi.h"
#include "pin.h"
#include "spi.h"
#include "ayplayer.h"

extern Pin							sd2Cs;
extern SpiMaster8Bit				spi2;
extern AyPlayer						ay;

void setSpiSpeed ( SpiMaster8BitBase* spi, bool speed ) {
	/*!
	 * Первые AYPLAYER_RCC_CFG_COUNT cfg - медленные.
	 * Следующие AYPLAYER_RCC_CFG_COUNT cfg - быстрые.
	 */
	spi->setPrescaler( ay.getRccMode() * ( ( uint32_t )speed + 1 ) );
}

microsdSpiCfg sd2Cfg = {
	.cs				=	&sd2Cs,
	.s				=	&spi2,
	.setSpiSpeed	=	setSpiSpeed
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
