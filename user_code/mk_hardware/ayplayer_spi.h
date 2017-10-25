#pragma once

#include "include_module_lib.h"
#include "ayplayer_nvic.h"
#include "ayplayer_os_object.h"

//**********************************************************************
// Для LCD.
//**********************************************************************
#define SPI1_CFG_OBJ_PARAM        SPI::CFG::NAME            :: SPI1,           \
                                  SPI::CFG::CLK_POLARITY    :: IDLE_1,         \
                                  SPI::CFG::CLK_PHASE       :: SECOND,         \
                                  SPI::CFG::NUMBER_LINE     :: LINE_2,         \
                                  SPI::CFG::ONE_LINE_MODE   :: USE_2_LINE,     \
                                  SPI::CFG::FRAME_FORMAT    :: MOTOROLA,       \
                                  SPI::CFG::BAUDRATE_DEV    :: DEV_2

//**********************************************************************
// Для micro-sd
//**********************************************************************
#define SPI2_SLOW_CFG_OBJ_PARAM   SPI::CFG::NAME            :: SPI2,           \
                                  SPI::CFG::CLK_POLARITY    :: IDLE_0,         \
                                  SPI::CFG::CLK_PHASE       :: FIRST,          \
                                  SPI::CFG::NUMBER_LINE     :: LINE_2,         \
                                  SPI::CFG::ONE_LINE_MODE   :: USE_2_LINE,     \
                                  SPI::CFG::FRAME_FORMAT    :: MOTOROLA,       \
                                  SPI::CFG::BAUDRATE_DEV    :: DEV_2

#define SPI2_FAST_CFG_OBJ_PARAM   SPI::CFG::NAME            :: SPI2,           \
                                  SPI::CFG::CLK_POLARITY    :: IDLE_0,         \
                                  SPI::CFG::CLK_PHASE       :: FIRST,          \
                                  SPI::CFG::NUMBER_LINE     :: LINE_2,         \
                                  SPI::CFG::ONE_LINE_MODE   :: USE_2_LINE,     \
                                  SPI::CFG::FRAME_FORMAT    :: MOTOROLA,       \
                                  SPI::CFG::BAUDRATE_DEV    :: DEV_2

//**********************************************************************
// Для сдвигового регистра и потенциометров.
//**********************************************************************
#define SPI3_CFG_OBJ_PARAM        SPI::CFG::NAME            :: SPI3,           \
                                  SPI::CFG::CLK_POLARITY    :: IDLE_0,         \
                                  SPI::CFG::CLK_PHASE       :: FIRST,          \
                                  SPI::CFG::NUMBER_LINE     :: LINE_2,         \
                                  SPI::CFG::ONE_LINE_MODE   :: USE_2_LINE,     \
                                  SPI::CFG::FRAME_FORMAT    :: MOTOROLA,       \
                                  SPI::CFG::BAUDRATE_DEV    :: DEV_2

extern spi_master_8bit_hardware_os < SPI1_CFG_OBJ_PARAM > spi1;
extern spi_master_8bit_hardware_os < SPI2_SLOW_CFG_OBJ_PARAM > spi2_slow;
extern spi_master_8bit_hardware_os < SPI2_FAST_CFG_OBJ_PARAM > spi2_fast;
extern spi_master_8bit_hardware_os < SPI3_CFG_OBJ_PARAM > spi3;

int ayplayer_spi_init ( void );



