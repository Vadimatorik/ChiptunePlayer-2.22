#pragma once

#include "pin_cfg_check_param.h"
#include "pin.h"
#include "port.h"

//
// Структуры конфигурации выводов.
//
//
// ADC.
//
const pin_config_adc_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_0 >      adc_bat;
const pin_config_adc_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_4 >      adc_right;
const pin_config_adc_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_1 >      adc_left;

//
// EXTI кнопки.
//
#define BUTTON_INC      EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_1
#define BUTTON_DEC      EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_2
const pin_config_check_param< BUTTON_INC,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        b_v_up;
const pin_config_check_param< BUTTON_DEC,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        b_v_down;

//
// MIDI ( USART2 ).
//
const pin_config_check_param<EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::USART2,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        midi_uart_rx;

//
// LCD ( SPI1 + TIMx ).
//

#define LCD_RES_PIN_HEADING             EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_4
#define LCD_DC_PIN_HEADING              EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_5
#define LCD_CS_PIN_HEADING              EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_2

const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_5,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_clk;
// Вывод MISO используется как PWM для подцветки.
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_6,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::TIM3,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_pwm;
//const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_6,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_miso;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_7,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_mosi;
const pin_config_check_param< LCD_RES_PIN_HEADING,                       EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           lcd_res;
const pin_config_check_param< LCD_DC_PIN_HEADING,                        EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         lcd_dc;
const pin_config_check_param< LCD_CS_PIN_HEADING,                        EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           lcd_cs;

//
// micro-sd ( SDIO + GPIO ).
//
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_0,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_push;
const pin_config_check_param< EC_PORT_NAME::D, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_smd;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_8,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d0;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_9,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d1;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_10, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d2;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d3;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_12, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_clk;

//
// USB ( USB_FS + GPIO ).
//
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_9,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        otg_fs_vbus;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::OTG_FS,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        usb_dm;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_12, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::OTG_FS,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        usb_dp;

//
// AY ( GPIO + TIM1 + SPI3 )
//

#define SHDN_PIN_HEADING                EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_6
#define DP_CS_PIN_HEADING               EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_14
#define BC1_PIN_HEADING                 EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_6
#define BDIR_PIN_HEADING                EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_12
#define SPI_AUDIO_ST_REG_PIN_HEADING    EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_8

const pin_config_check_param< BDIR_PIN_HEADING,                          EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         bdir;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay_1_res;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay_2_res;
const pin_config_check_param< BC1_PIN_HEADING,                           EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         bc1;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_0,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::TIM1,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        ay_clk;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI3,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        spi_audio_clk;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_5,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI3,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        spi_audio_tx;
const pin_config_check_param< SHDN_PIN_HEADING,                          EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         shdn;
const pin_config_check_param< SPI_AUDIO_ST_REG_PIN_HEADING,              EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         spi_audio_st_reg;
const pin_config_check_param< DP_CS_PIN_HEADING,                         EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           dp_cs_res;

//
// SPI клавиатура ( SPI общий AY, тут только вход ).
//

#define B_IN_PIN_HEADING            EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_7

const pin_config_check_param< B_IN_PIN_HEADING,                          EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::DOWN,     EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >           button_in;

//
// SWD.
//
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_13, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::SYS,         EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >          swd_io;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_14, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::DOWN,      EC_PIN_AF::SYS,         EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >          swd_clk;

//
// PWR.
//

#define PWR_5_V_IN_PIN_HEADING              EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_8
#define CHIP_1_PWR_ON_PIN_HEADING           EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_4
#define CHIP_2_PWR_ON_PIN_HEADING           EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_10
#define PWR_ON_PIN_HEADING                  EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_1

const pin_config_check_param< PWR_5_V_IN_PIN_HEADING,                    EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >           on_5v;
const pin_config_check_param< PWR_ON_PIN_HEADING,                        EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >           power_on;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_14, EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >          tp_st;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >          tp_ch;
const pin_config_check_param< CHIP_1_PWR_ON_PIN_HEADING,                 EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >           ay1_on;
const pin_config_check_param< CHIP_2_PWR_ON_PIN_HEADING,                 EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >           ay2_on;

//
// MICRO-SD SPI2 ( SPI2 + GPIO ).
//

#define SD2_CS_PIN_HEADING                  EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_7          
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::UP,            EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_rx;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,        EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_tx;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_13, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,        EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_clk;
const pin_config_check_param< SD2_CS_PIN_HEADING,                        EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           sd2_cs;

#define SD2_PUSH_PIN_HEADING                EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_9
const pin_config_check_param< SD2_PUSH_PIN_HEADING,                      EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,    EC_PIN_PULL::UP,            EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_push;

//
// BOOT-USART ( USART3 )
//
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_10, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,EC_PIN_PULL::NO_USE,     EC_PIN_AF::USART3,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >            boot_tx;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,EC_PIN_PULL::NO_USE,     EC_PIN_AF::USART3,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >            boot_rx;

//
// Глобальный порт.
//
const constexpr pin_config_t ayplayer_global_port_pin_cfg[] = {
    b_v_up, b_v_down,
    adc_bat, adc_right, adc_left,                                                                           // ADC.
    midi_uart_rx,                                                                                           // MIDI (USART2).
    lcd_clk, lcd_pwm, lcd_mosi, lcd_res, lcd_dc, lcd_cs,                                                    // LCD (SPI1 + TIMx).
    sd1_push, sd1_smd, sd1_d0, sd1_d1, sd1_d2, sd1_d3, sd1_clk,                                             // micro-sd (SDIO + GPIO).
    otg_fs_vbus, usb_dm, usb_dp,                                                                            // USB (USB_FS + GPIO).
    bdir, ay_1_res, ay_2_res, bc1, ay_clk, spi_audio_clk, spi_audio_tx, shdn, spi_audio_st_reg, dp_cs_res,  // AY (GPIO + TIM1 + SPI3)
    button_in,                                                                                              // SPI клавиатура (SPI общий AY, тут только вход).
    on_5v, power_on, tp_st, tp_ch, ay1_on, ay2_on,                                                          // PWR.
    sd2_rx, sd2_tx, sd2_clk, sd2_cs, sd2_push,                                                              // MICRO-SD SPI2 (SPI2 + GPIO).
    boot_tx, boot_rx,                                                                                       // BOOT-USART (USART3).
    swd_io, swd_clk,                                                                                        // SWD.
};

const constexpr global_port ayplayer_global_port( ayplayer_global_port_pin_cfg, M_SIZE_ARRAY(ayplayer_global_port_pin_cfg) );

extern pin< LCD_RES_PIN_HEADING >                           lcd_res_obj;
extern pin< LCD_DC_PIN_HEADING >                            lcd_dc_obj;
extern pin< LCD_CS_PIN_HEADING >                            lcd_cs_obj;

// MICROSD 2.
extern pin< SD2_CS_PIN_HEADING >                            sd2_cs_obj;

// Защелка сдвигового регистра.
extern pin< SPI_AUDIO_ST_REG_PIN_HEADING >                  spi_audio_st_reg_obj;

// AY_YM.
extern pin< BDIR_PIN_HEADING >                              bdir_obj;
extern pin< BC1_PIN_HEADING >                               bc1_obj;
extern pin< CHIP_1_PWR_ON_PIN_HEADING >                     chip_1_pwr_on_obj;
extern pin< CHIP_2_PWR_ON_PIN_HEADING >                     chip_2_pwr_on_obj;

// PWR.
extern pin< PWR_5_V_IN_PIN_HEADING >                        pwr_5_v_on_obj;

// Потенциометры.
extern pin< DP_CS_PIN_HEADING >                             dp_cs_res_obj;
extern pin< SHDN_PIN_HEADING >                              shdn_obj;

// Общий вход кнопок.
extern pin< B_IN_PIN_HEADING >                              b_in;

// + - громкость.
extern pin< BUTTON_INC >                                    b_inc;
extern pin< BUTTON_DEC >                                    b_dec;

extern pin< PWR_ON_PIN_HEADING >                            pwr_on_obj;

int ayplayer_port_init ( void );
