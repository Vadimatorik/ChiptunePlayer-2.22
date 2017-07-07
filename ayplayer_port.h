#pragma once

#include "stm32_f20x_f21x_port.h"

/*
 * Структуры конфигурации выводов.
 */
/*
 * ADC.
 */
const pin_config_adc_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_1 >      adc_bat;
const pin_config_adc_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_4 >      adc_right;
const pin_config_adc_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_1 >      adc_left;

/*
 * EXTI кнопки.
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_1,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        b_v_up;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        b_v_down;

/*
 * MIDI ( USART2 ).
 */
const pin_config_check_param<EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::USART2,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        midi_uart_rx;

/*
 * LCD ( SPI1 + TIMx ).
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_5,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_clk;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_6,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_miso;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_7,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI1,          EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        lcd_mosi;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_4,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           lcd_res;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_5,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         lcd_dc;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM, EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         lcd_cs;

/*
 * micro-sd ( SDIO + GPIO ).
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_8,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_push;
const pin_config_check_param< EC_PORT_NAME::D, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_smd;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_8,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d0;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_9,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d1;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_10, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d2;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_d3;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_12, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::SDIO,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd1_clk;

/*
 * USB ( USB_FS + GPIO ).
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_9,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        otg_fs_vbus;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::OTG_FS,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        usb_dm;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_12, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::HIGH,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::OTG_FS,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        usb_dp;

/*
 * AY ( GPIO + TIM1 + SPI3 )
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_10, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         bdir;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay_1_res;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay_2_res;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_6,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         bc1;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_0,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::FAST,     EC_PIN_PULL::NO_USE,    EC_PIN_AF::TIM1,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        ay_clk;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI3,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        spi_audio_clk;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_5,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI3,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        spi_audio_tx;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_6,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        shdn;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_8,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         spi_audio_st_reg;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_14, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         cs_res;

/*
 * SPI клавиатура ( SPI общий AY, тут только вход ).
 */
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_7,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        button_in;

/*
 * SWD.
 */
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_13, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::SYS,         EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        swd_io;
const pin_config_check_param< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_14, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::DOWN,      EC_PIN_AF::SYS,         EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        swd_clk;

/*
 * PWR.
 */
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_0,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         on_5v;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_1,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::SET >           power_on;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_14, EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        tp_st;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_15, EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        tp_ch;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_4,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay1_on;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_12, EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         ay2_on;

/*
 * MICRO-SD SPI2 ( SPI2 + GPIO ).
 */
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_2,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_rx;
const pin_config_check_param< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_3,  EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_tx;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_13, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::SPI2,        EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2__clk;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_7,  EC_PIN_MODE::OUTPUT,    EC_PIN_OUTPUT_CFG::PUSH_PULL,   EC_PIN_SPEED::MEDIUM,   EC_PIN_PULL::NO_USE,    EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::RESET >         sd2_cs;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_9,  EC_PIN_MODE::INPUT,     EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::LOW,      EC_PIN_PULL::UP,        EC_PIN_AF::NO_USE,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        sd2_push;

/*
 * BOOT-USART ( USART3 )
 */
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_10, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,EC_PIN_PULL::NO_USE,       EC_PIN_AF::USART3,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        boot_tx;
const pin_config_check_param< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_11, EC_PIN_MODE::AF,        EC_PIN_OUTPUT_CFG::NO_USE,      EC_PIN_SPEED::MEDIUM,EC_PIN_PULL::NO_USE,       EC_PIN_AF::USART3,      EC_LOCKED::LOCKED,      EC_PIN_STATE_AFTER_INIT::NO_USE >        boot_rx;

/*
 * Глобальный порт.
 */
const constexpr pin_config_t ayplayer_global_port_pin_cfg[] = {
    adc_bat, adc_right, adc_left,                                                                           // ADC.
    midi_uart_rx,                                                                                           // MIDI (USART2).
    lcd_clk, lcd_miso, lcd_mosi, lcd_res, lcd_dc, lcd_cs,                                                  // LCD (SPI1 + TIMx).
    sd1_push, sd1_smd, sd1_d0, sd1_d1, sd1_d2, sd1_d3, sd1_clk,                                             // micro-sd (SDIO + GPIO).
    otg_fs_vbus, usb_dm, usb_dp,                                                                            // USB (USB_FS + GPIO).
    bdir, ay_1_res, ay_2_res, bc1, ay_clk, spi_audio_clk, spi_audio_tx, shdn, spi_audio_st_reg, cs_res,     // AY (GPIO + TIM1 + SPI3)
    button_in,                                                                                              // SPI клавиатура (SPI общий AY, тут только вход).
    swd_io, swd_clk,                                                                                        // SWD.
    on_5v, power_on, tp_st, tp_ch, ay1_on, ay2_on,                                                          // PWR.
    sd2_rx, sd2_tx, sd2__clk, sd2_cs, sd2_push,                                                             // MICRO-SD SPI2 (SPI2 + GPIO).
    boot_tx, boot_rx                                                                                        // BOOT-USART (USART3).
};

const constexpr global_port ayplayer_global_port( ayplayer_global_port_pin_cfg, M_SIZE_ARRAY(ayplayer_global_port_pin_cfg) );

/*
 * Объекты pin (ручное управление выводами).
 */
// LCD.
const constexpr pin lcd_res_obj( &lcd_res );
const constexpr pin lcd_dc_obj( &lcd_dc );
const constexpr pin lcd_cs_obj( &lcd_cs );

// MICROSD 2.
const constexpr pin sd2_cs_obj( &sd2_cs );

int ayplayer_port_init ( void );

