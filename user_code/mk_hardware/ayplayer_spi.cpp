#include "ayplayer_spi.h"

spi_master_8bit_cfg spi1_cfg = {
    .SPIx                   = SPI1,
    .pin_cs                 = &lcd_cs_pin_obj,
    .clk_polarity           = SPI_POLARITY_HIGH,
    .clk_phase              = SPI_PHASE_2EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_2,
    .dma_tx                 = DMA2_Stream5,
    .dma_rx                 = nullptr,
    .dma_tx_ch              = DMA_CHANNEL_3,
    .dma_rx_ch              = 0
};

spi_master_8bit_cfg spi2_slow_cfg = {
    .SPIx                   = SPI2,
    .pin_cs                 = &sd2_cs_pin_obj,
    .clk_polarity           = SPI_POLARITY_LOW,
    .clk_phase              = SPI_PHASE_1EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_2,
    .dma_tx                 = DMA1_Stream4,
    .dma_rx                 = DMA1_Stream3,
    .dma_tx_ch              = DMA_CHANNEL_0,
    .dma_rx_ch              = DMA_CHANNEL_0
};

spi_master_8bit_cfg spi2_fast_cfg = {
    .SPIx                   = SPI2,
    .pin_cs                 = &sd2_cs_pin_obj,
    .clk_polarity           = SPI_POLARITY_LOW,
    .clk_phase              = SPI_PHASE_1EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_2,
    .dma_tx                 = DMA1_Stream4,
    .dma_rx                 = DMA1_Stream3,
    .dma_tx_ch              = DMA_CHANNEL_0,
    .dma_rx_ch              = DMA_CHANNEL_0
};

spi_master_8bit_cfg spi3_cfg = {
    .SPIx                   = SPI3,
    .pin_cs                 = &sd2_cs_pin_obj,
    .clk_polarity           = SPI_POLARITY_LOW,
    .clk_phase              = SPI_PHASE_1EDGE,
    .baud_rate_prescaler    = SPI_BAUDRATEPRESCALER_2,
    .dma_tx                 = DMA1_Stream7,
    .dma_rx                 = nullptr,
    .dma_tx_ch              = DMA_CHANNEL_0,
    .dma_rx_ch              = 0
};

spi_master_8bit spi1_obj( &spi1_cfg );
spi_master_8bit spi2_slow_obj( &spi2_slow_cfg );
spi_master_8bit spi2_fast_obj( &spi2_fast_cfg );
spi_master_8bit spi3_obj( &spi3_cfg );

int ayplayer_spi_init ( void ) {
    m_spi3_init();
    spi1_obj.reinit();
    spi3_obj.reinit();
    spi1_obj.on();
    spi3_obj.on();
    return 0;
}

extern "C" void DMA2_Stream5_IRQHandler (void) {
    spi1_obj.handler();
}

extern "C" void DMA1_Stream3_IRQHandler (void) {
    spi2_slow_obj.handler();
    spi2_fast_obj.handler();
}

extern "C" void DMA1_Stream4_IRQHandler (void) {
    spi2_slow_obj.handler();
    spi2_fast_obj.handler();
}

extern "C" void DMA1_Stream7_IRQHandler (void) {
    spi3_obj.handler();
}
