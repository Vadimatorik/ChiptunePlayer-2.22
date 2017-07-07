#pragma once

#include "stm32_f20x_f21x_include_module_lib.h"
#include "ayplayer_nvic.h"

/*
 * Для LCD.
 */
#define SPI1_CFG_OBJ_PARAM        EC_SPI_NAME                :: SPI1,           \
                                  EC_SPI_CFG_CLK_POLARITY    :: IDLE_1,         \
                                  EC_SPI_CFG_CLK_PHASE       :: SECOND,         \
                                  EC_SPI_CFG_NUMBER_LINE     :: LINE_2,         \
                                  EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,     \
                                  EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,    \
                                  EC_SPI_CFG_FRAME_FORMAT    :: MOTOROLA,       \
                                  EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_2,          \
                                  EC_SPI_CFG_CS              :: ENABLED

/*
 * Для micro-sd
 */
#define SPI2_CFG_OBJ_PARAM        EC_SPI_NAME                :: SPI2,           \
                                  EC_SPI_CFG_CLK_POLARITY    :: IDLE_0,         \
                                  EC_SPI_CFG_CLK_PHASE       :: FIRST,          \
                                  EC_SPI_CFG_NUMBER_LINE     :: LINE_2,         \
                                  EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,     \
                                  EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,    \
                                  EC_SPI_CFG_FRAME_FORMAT    :: MOTOROLA,       \
                                  EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_8,          \
                                  EC_SPI_CFG_CS              :: ENABLED

/*
 * Для сдвигового регистра и потенциометров.
 */
#define SPI3_CFG_OBJ_PARAM        EC_SPI_NAME                :: SPI3,           \
                                  EC_SPI_CFG_CLK_POLARITY    :: IDLE_0,         \
                                  EC_SPI_CFG_CLK_PHASE       :: FIRST,          \
                                  EC_SPI_CFG_NUMBER_LINE     :: LINE_2,         \
                                  EC_SPI_CFG_ONE_LINE_MODE   :: USE_2_LINE,     \
                                  EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,    \
                                  EC_SPI_CFG_FRAME_FORMAT    :: MOTOROLA,       \
                                  EC_SPI_CFG_BAUD_RATE_DEV   :: DEV_8,          \
                                  EC_SPI_CFG_CS              :: ENABLED

extern const spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >* spi1;
extern const spi_master_hardware_os< SPI2_CFG_OBJ_PARAM >* spi2;
extern const spi_master_hardware_os< SPI3_CFG_OBJ_PARAM >* spi3;

int ayplayer_spi_init ( void );



