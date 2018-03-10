#include "spi.h"
#include "dma.h"

/// Конфигурация SPI для работы с LCD
spi_master_8bit_cfg spi1_cfg = {
    .SPIx                   = SPI1,
    .pin_cs                 = nullptr,
    .clk_polarity           = SPI_POLARITY_HIGH,
    .clk_phase              = SPI_PHASE_2EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_128,
    .dma_tx                 = DMA2_Stream5,
    .dma_rx                 = nullptr,
    .dma_tx_ch              = DMA_CHANNEL_3,
	.dma_rx_ch              = 0,
	.handler_prio			= 6
};

/// Конфигурация SPI2 для работы с micro-sd
spi_master_8bit_cfg spi2_cfg = {
    .SPIx                   = SPI2,
    .pin_cs                 = nullptr,
    .clk_polarity           = SPI_POLARITY_LOW,
    .clk_phase              = SPI_PHASE_1EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_256,
    .dma_tx                 = DMA1_Stream4,
    .dma_rx                 = DMA1_Stream3,
    .dma_tx_ch              = DMA_CHANNEL_0,
	.dma_rx_ch              = DMA_CHANNEL_0,
	.handler_prio			= 6
};

/// Для сдвигового регистра и потенциометров.
spi_master_8bit_cfg spi3_cfg = {
    .SPIx                   = SPI3,
    .pin_cs                 = nullptr,
    .clk_polarity           = SPI_POLARITY_LOW,
    .clk_phase              = SPI_PHASE_1EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_256,
    .dma_tx                 = DMA1_Stream7,
    .dma_rx                 = nullptr,
    .dma_tx_ch              = DMA_CHANNEL_0,
	.dma_rx_ch              = 0,
	.handler_prio			= 6
};

spi_master_8bit ayplayer_spi1_obj( &spi1_cfg );
spi_master_8bit ayplayer_spi2_obj( &spi2_cfg );
spi_master_8bit ayplayer_spi3_obj( &spi3_cfg );

/*!
 * Обработчики прерываний.
 */
extern "C" {

void DMA2_Stream5_IRQHandler ( void ) { ayplayer_spi1_obj.handler(); }
void DMA1_Stream3_IRQHandler ( void ) { ayplayer_spi2_obj.handler(); }
void DMA1_Stream4_IRQHandler ( void ) { ayplayer_spi2_obj.handler(); }
void DMA1_Stream7_IRQHandler ( void ) { ayplayer_spi3_obj.handler(); }

}
