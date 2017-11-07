#pragma once

#include "user_os.h"
#include "pin.h"
#include "port.h"

//**********************************************************************
// Структуры конфигурации выводов.
//**********************************************************************
// ADC.
const pin_cfg adc_bat_pin_cfg               = { GPIOA, { GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg adc_right_pin_cfg             = { GPIOA, { GPIO_PIN_4, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg adc_left_pin_cfg              = { GPIOB, { GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };

// EXTI кнопки.
const pin_cfg button_inc_pin_cfg            = { GPIOA, { GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg button_dec_pin_cfg            = { GPIOA, { GPIO_PIN_2, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };

// MIDI ( USART2 ).
const pin_cfg midi_uart_rx_pin_cfg          = { GPIOA, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2 } };

// LCD ( SPI1 + TIMx ).
const pin_cfg lcd_clk_pin_cfg               = { GPIOA, { GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pin_cfg lcd_pwm_pin_cfg               = { GPIOA, { GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF2_TIM3 } };
const pin_cfg lcd_mosi_pin_cfg              = { GPIOA, { GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1} };
const pin_cfg lcd_res_pin_cfg               = { GPIOC, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg lcd_dc_pin_cfg                = { GPIOC, { GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg lcd_cs_pin_cfg                = { GPIOB, { GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

// micro-sd ( SDIO + GPIO ).
const pin_cfg sd1_push_pin_cfg              = { GPIOC, { GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg sd1_smd_pin_cfg               = { GPIOD, { GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg sd1_d0_pin_cfg                = { GPIOC, { GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg sd1_d1_pin_cfg                = { GPIOC, { GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg sd1_d2_pin_cfg                = { GPIOC, { GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg sd1_d3_pin_cfg                = { GPIOC, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg sd1_clk_pin_cfg               = { GPIOC, { GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };

// USB ( USB_FS + GPIO ).
const pin_cfg otg_fs_vbus_pin_cfg           = { GPIOA, { GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg usb_dm_pin_cfg                = { GPIOA, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL,GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS } };
const pin_cfg usb_dp_pin_cfg                = { GPIOA, { GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL,GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS } };

// AY ( GPIO + TIM1 + SPI3 )
const pin_cfg bdir_pin_cfg                  = { GPIOB, { GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg ay_1_res_pin_cfg              = { GPIOA, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ay_2_res_pin_cfg              = { GPIOB, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg bc1_pin_cfg                   = { GPIOC, { GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg ay_clk_pin_cfg                = { GPIOB, { GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF1_TIM1 } };
const pin_cfg spi_audio_clk_pin_cfg         = { GPIOB, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF6_SPI3 } };
const pin_cfg spi_audio_tx_pin_cfg          = { GPIOB, { GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg shdn_pin_cfg                  = { GPIOB, { GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg spi_audio_st_reg_pin_cfg      = { GPIOB, { GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg dp_cs_res_pin_cfg             = { GPIOB, { GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

// SPI клавиатура ( SPI общий AY, тут только вход ).
const pin_cfg button_in_pin_cfg             = { GPIOC, { GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_PULLDOWN, GPIO_SPEED_FREQ_LOW, 0 } };

// SWD.
const pin_cfg swd_io_pin_cfg                = { GPIOA, { GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF0_SWJ } };
const pin_cfg swd_clk_pin_cfg               = { GPIOA, { GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF0_SWJ } };

// PWR.
const pin_cfg pwr_5_v_on_pin_cfg            = { GPIOA, { GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg pwr_on_pin_cfg                = { GPIOC, { GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg tp_st_pin_cfg                 = { GPIOC, { GPIO_PIN_14, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg tp_ch_pin_cfg                 = { GPIOC, { GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg chip_1_pwr_on_pin_cfg         = { GPIOB, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg chip_2_pwr_on_pin_cfg         = { GPIOA, { GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };

// MICRO-SD SPI2 ( SPI2 + GPIO ).          
const pin_cfg sd2_rx_pin_cfg                = { GPIOC, { GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg sd2_tx_pin_cfg                = { GPIOC, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg sd2_clk_pin_cfg               = { GPIOB, { GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg sd2_cs_pin_cfg                = { GPIOB, { GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

const pin_cfg sd2_push_pin_cfg              = { GPIOB, { GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };

//
// BOOT-USART ( USART3 )
//
const pin_cfg boot_tx_pin_cfg               = { GPIOB, { GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART3 } };
const pin_cfg boot_rx_pin_cfg               = { GPIOB, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART3 } };

//
// Глобальный порт.
//
const pin_cfg ayplayer_global_port_pin_cfg[] = {
    button_inc_pin_cfg, button_dec_pin_cfg,                                                                                                                                                 // BUTTON, EXTI.
    adc_bat_pin_cfg, adc_right_pin_cfg, adc_left_pin_cfg,                                                                                                                                   // ADC.
    midi_uart_rx_pin_cfg,                                                                                                                                                                   // MIDI (USART2).
    lcd_clk_pin_cfg, lcd_pwm_pin_cfg, lcd_mosi_pin_cfg, lcd_res_pin_cfg, lcd_dc_pin_cfg, lcd_cs_pin_cfg,                                                                                    // LCD (SPI1 + TIMx).
    sd1_push_pin_cfg, sd1_smd_pin_cfg, sd1_d0_pin_cfg, sd1_d1_pin_cfg, sd1_d2_pin_cfg, sd1_d3_pin_cfg, sd1_clk_pin_cfg,                                                                     // micro-sd (SDIO + GPIO).
    otg_fs_vbus_pin_cfg, usb_dm_pin_cfg, usb_dp_pin_cfg,                                                                                                                                    // USB (USB_FS + GPIO).
    bdir_pin_cfg, ay_1_res_pin_cfg, ay_2_res_pin_cfg, bc1_pin_cfg, ay_clk_pin_cfg, spi_audio_clk_pin_cfg, spi_audio_tx_pin_cfg, shdn_pin_cfg, spi_audio_st_reg_pin_cfg, dp_cs_res_pin_cfg,  // AY (GPIO + TIM1 + SPI3)
    button_in_pin_cfg,                                                                                                                                                                      // SPI клавиатура (SPI общий AY, тут только вход).
    pwr_5_v_on_pin_cfg, pwr_on_pin_cfg, tp_st_pin_cfg, tp_ch_pin_cfg, chip_1_pwr_on_pin_cfg, chip_2_pwr_on_pin_cfg,                                                                         // PWR.
    sd2_rx_pin_cfg, sd2_tx_pin_cfg, sd2_clk_pin_cfg, sd2_cs_pin_cfg, sd2_push_pin_cfg,                                                                                                      // MICRO-SD SPI2 (SPI2 + GPIO).
    boot_tx_pin_cfg, boot_rx_pin_cfg,                                                                                                                                                       // BOOT-USART (USART3).
    swd_io_pin_cfg, swd_clk_pin_cfg,                                                                                                                                                        // SWD.
};

extern global_port ayplayer_global_port_obj;

// LCD.
extern pin lcd_res_pin_obj;
extern pin lcd_dc_pin_obj;
extern pin lcd_cs_pin_obj;

// MICROSD 2.
extern pin sd2_cs_pin_obj;
extern pin sd2_push_pin_obj;

// Защелка сдвигового регистра.
extern pin spi_audio_st_reg_pin_obj;

// AY_YM.
extern pin bdir_pin_obj;
extern pin bc1_pin_obj;
extern pin chip_1_pwr_on_pin_obj;
extern pin chip_2_pwr_on_pin_obj;

// PWR.
extern pin pwr_5_v_on_pin_obj;
extern pin pwr_on_pin_obj;

// Потенциометры.
extern pin dp_cs_res_pin_obj;
extern pin shdn_pin_obj;

// Общий вход кнопок.
extern pin button_in_pin_obj;

// + - громкость.
extern pin button_inc_pin_obj;
extern pin button_dec_pin_obj;


int ayplayer_port_init ( void );
