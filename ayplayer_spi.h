#pragma once

#include "stm32_f20x_f21x_spi.h"

const constexpr spi_cfg< EC_SPI_CFG_MODE::MASTER,
                         EC_SPI_CFG_CLK_POLARITY    :: IDLE_0,
                         EC_SPI_CFG_CLK_PHASE       :: FIRST,
                         EC_SPI_CFG_NUMBER_LINE     :: LINE_2,
                         EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,
                         EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,
                         EC_SPI_CFG_RECEIVE_MODE    :: FULL_DUPLEX,
                         EC_SPI_CFG_FRAME_FORMAT    :: TI,
                         EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_2,
                         EC_SPI_CFG_INTERRUPT_TX    :: OFF,
                         EC_SPI_CFG_INTERRUPT_RX    :: OFF,
                         EC_SPI_CFG_INTERRUPT_ERROR :: OFF,
                         EC_SPI_CFG_DMA_TX_BUF      :: ENABLED,
                         EC_SPI_CFG_DMA_RX_BUF      :: ENABLED,
                         EC_SPI_CFG_SS              :: DISABLED,
                         EC_SPI_CFG_SSM             :: SSM_OFF,
                         EC_SPI_CFG_SSM_MODE        :: NO_USE > spi1_cfg;

const constexpr spi< EC_SPI_NAME::SPI1 > spi1( &spi1_cfg );

int ayplayer_spi_init ( void );

