#include "spi.h"
#include "dma.h"
#include "ayplayer.h"

uint32_t baudratePrescalerSpi1[ AYPLAYER_RCC_CFG_COUNT ] = {
	SPI_BAUDRATEPRESCALER_128,
	SPI_BAUDRATEPRESCALER_128,
	SPI_BAUDRATEPRESCALER_128,
	SPI_BAUDRATEPRESCALER_128
};

/// Конфигурация SPI для работы с LCD
SpiMaster8BitCfg spi1_cfg = {
	.SPIx						=	SPI1,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_HIGH,
	.clkPhase					=	SPI_PHASE_2EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi1,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT,

	.dmaTx						=	DMA2_Stream5,
	.dmaRx						=	nullptr,
	.dmaTxCh					=	DMA_CHANNEL_3,
	.dmaRxCh					=	0,

	.handlerReseivePrio			=	6
};

uint32_t baudratePrescalerSpi2[ AYPLAYER_RCC_CFG_COUNT ] = {
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256
};

/// Конфигурация SPI2 для работы с micro-sd
SpiMaster8BitCfg spi2_cfg = {
	.SPIx						=	SPI2,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_LOW,
	.clkPhase					=	SPI_PHASE_1EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi2,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT,

	.dmaTx						=	DMA1_Stream4,
	.dmaRx						=	DMA1_Stream3,
	.dmaTxCh					=	DMA_CHANNEL_0,
	.dmaRxCh					=	DMA_CHANNEL_0,

	.handlerReseivePrio			=	6
};

uint32_t baudratePrescalerSpi3[ AYPLAYER_RCC_CFG_COUNT ] = {
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256
};

/// Для сдвигового регистра и потенциометров.
SpiMaster8BitCfg spi3_cfg = {
	.SPIx						=	SPI3,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_LOW,
	.clkPhase					=	SPI_PHASE_1EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi3,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT,

	.dmaTx						=	DMA1_Stream7,
	.dmaRx						=	nullptr,
	.dmaTxCh					=	DMA_CHANNEL_0,
	.dmaRxCh					=	0,

	.handlerReseivePrio			=	6
};

SpiMaster8Bit ayplayer_spi1_obj( &spi1_cfg, 1 );
SpiMaster8Bit ayplayer_spi2_obj( &spi2_cfg, 1 );
SpiMaster8Bit ayplayer_spi3_obj( &spi3_cfg, 1 );

/*!
 * Обработчики прерываний.
 */
extern "C" {

void dma2_stream5_handler ( void ) { ayplayer_spi1_obj.reseiveByteHandler(); }
void dma1_stream3_handler ( void ) { ayplayer_spi2_obj.reseiveByteHandler(); }
void dma1_stream4_handler ( void ) { ayplayer_spi2_obj.reseiveByteHandler(); }
void dma1_stream7_handler ( void ) { ayplayer_spi3_obj.reseiveByteHandler(); }

}
