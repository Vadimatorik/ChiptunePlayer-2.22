#include "spi.h"
#include "dma.h"
#include "ayplayer.h"

uint32_t baudratePrescalerSpi1[ AYPLAYER_RCC_CFG_COUNT ] = {
	SPI_BAUDRATEPRESCALER_4,
	SPI_BAUDRATEPRESCALER_4,
	SPI_BAUDRATEPRESCALER_2,
	SPI_BAUDRATEPRESCALER_2
};

/// Конфигурация SPI для работы с LCD
SpiMaster8BitCfg spi1Cfg = {
	.SPIx						=	SPI1,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_HIGH,
	.clkPhase					=	SPI_PHASE_2EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi1,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT,

	.dmaTx						=	DMA2_Stream5,
	.dmaRx						=	nullptr,
	.dmaTxCh					=	DMA_CHANNEL_3,
	.dmaRxCh					=	0
};

uint32_t baudratePrescalerSpi2[ AYPLAYER_RCC_CFG_COUNT * 2 ] = {
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256
};

/// Конфигурация SPI2 для работы с micro-sd
SpiMaster8BitCfg spi2Cfg = {
	.SPIx						=	SPI2,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_LOW,
	.clkPhase					=	SPI_PHASE_1EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi2,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT * 2,

	.dmaTx						=	DMA1_Stream4,
	.dmaRx						=	DMA1_Stream3,
	.dmaTxCh					=	DMA_CHANNEL_0,
	.dmaRxCh					=	DMA_CHANNEL_0
};

uint32_t baudratePrescalerSpi3[ AYPLAYER_RCC_CFG_COUNT ] = {
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256,
	SPI_BAUDRATEPRESCALER_256
};

/// Для сдвигового регистра и потенциометров.
SpiMaster8BitCfg spi3Cfg = {
	.SPIx						=	SPI3,

	.pinCs						=	nullptr,

	.clkPolarity				=	SPI_POLARITY_LOW,
	.clkPhase					=	SPI_PHASE_1EDGE,

	.baudratePrescalerArray		=	baudratePrescalerSpi3,
	.numberBaudratePrescalerCfg	=	AYPLAYER_RCC_CFG_COUNT,

	.dmaTx						=	DMA1_Stream7,
	.dmaRx						=	nullptr,
	.dmaTxCh					=	DMA_CHANNEL_0,
	.dmaRxCh					=	0
};

SpiMaster8Bit spi1( &spi1Cfg, 1 );
SpiMaster8Bit spi2( &spi2Cfg, 1 );
SpiMaster8Bit spi3( &spi3Cfg, 1 );
