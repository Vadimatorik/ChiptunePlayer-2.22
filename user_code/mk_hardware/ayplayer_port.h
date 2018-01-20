#pragma once
#include "pin.h"
#include "port.h"
#include "user_os.h"

//**********************************************************************
// Структуры конфигурации выводов.
//**********************************************************************
// ADC.
const pin_cfg ayplayer_adc_bat_pin_cfg               = { GPIOA, { GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_adc_right_pin_cfg             = { GPIOA, { GPIO_PIN_4, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_adc_left_pin_cfg              = { GPIOB, { GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };

// EXTI кнопки.
const pin_cfg ayplayer_button_inc_pin_cfg            = { GPIOA, { GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_button_dec_pin_cfg            = { GPIOA, { GPIO_PIN_2, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };

// MIDI ( USART2 ).
const pin_cfg ayplayer_midi_uart_rx_pin_cfg          = { GPIOA, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2 } };

// LCD ( SPI1 + TIMx ).
const pin_cfg ayplayer_lcd_clk_pin_cfg               = { GPIOA, { GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1 } };
const pin_cfg ayplayer_lcd_pwm_pin_cfg               = { GPIOA, { GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF2_TIM3 } };
const pin_cfg ayplayer_lcd_mosi_pin_cfg              = { GPIOA, { GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI1} };
const pin_cfg ayplayer_lcd_res_pin_cfg               = { GPIOC, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg ayplayer_lcd_dc_pin_cfg                = { GPIOC, { GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg ayplayer_lcd_cs_pin_cfg                = { GPIOB, { GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

// micro-sd ( SDIO + GPIO ).
const pin_cfg ayplayer_sd1_push_pin_cfg              = { GPIOC, { GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_sd1_smd_pin_cfg               = { GPIOD, { GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg ayplayer_sd1_d0_pin_cfg                = { GPIOC, { GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg ayplayer_sd1_d1_pin_cfg                = { GPIOC, { GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg ayplayer_sd1_d2_pin_cfg                = { GPIOC, { GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg ayplayer_sd1_d3_pin_cfg                = { GPIOC, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };
const pin_cfg ayplayer_sd1_clk_pin_cfg               = { GPIOC, { GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF12_SDIO } };

// USB ( USB_FS + GPIO ).
const pin_cfg ayplayer_otg_fs_vbus_pin_cfg           = { GPIOA, { GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_usb_dm_pin_cfg                = { GPIOA, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL,GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS } };
const pin_cfg ayplayer_usb_dp_pin_cfg                = { GPIOA, { GPIO_PIN_12, GPIO_MODE_AF_PP, GPIO_NOPULL,GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF10_OTG_FS } };

// AY ( GPIO + TIM1 + SPI3 )
const pin_cfg ayplayer_bdir_pin_cfg                  = { GPIOB, { GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };
const pin_cfg ayplayer_ay_1_res_pin_cfg              = { GPIOA, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_ay_2_res_pin_cfg              = { GPIOB, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_bc1_pin_cfg                   = { GPIOC, { GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg ayplayer_ay_clk_pin_cfg                = { GPIOB, { GPIO_PIN_0, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF1_TIM1 } };
const pin_cfg ayplayer_spi_audio_clk_pin_cfg         = { GPIOB, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF6_SPI3 } };
const pin_cfg ayplayer_spi_audio_tx_pin_cfg          = { GPIOB, { GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg ayplayer_shdn_pin_cfg                  = { GPIOB, { GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_spi_audio_st_reg_pin_cfg      = { GPIOB, { GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg ayplayer_dp_cs_res_pin_cfg             = { GPIOB, { GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

// SPI клавиатура ( SPI общий AY, тут только вход ).
const pin_cfg ayplayer_button_in_pin_cfg             = { GPIOC, { GPIO_PIN_7, GPIO_MODE_INPUT, GPIO_PULLDOWN, GPIO_SPEED_FREQ_LOW, 0 } };

// SWD.
const pin_cfg ayplayer_swd_io_pin_cfg                = { GPIOA, { GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF0_SWJ } };
const pin_cfg ayplayer_swd_clk_pin_cfg               = { GPIOA, { GPIO_PIN_14, GPIO_MODE_AF_PP, GPIO_PULLDOWN, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF0_SWJ } };

// PWR.
const pin_cfg ayplayer_pwr_5_v_on_pin_cfg            = { GPIOA, { GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_pwr_on_pin_cfg                = { GPIOC, { GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_tp_st_pin_cfg                 = { GPIOC, { GPIO_PIN_14, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_tp_ch_pin_cfg                 = { GPIOC, { GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0 } };
const pin_cfg ayplayer_chip_1_pwr_on_pin_cfg         = { GPIOB, { GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };
const pin_cfg ayplayer_chip_2_pwr_on_pin_cfg         = { GPIOA, { GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, 0 } };

// MICRO-SD SPI2 ( SPI2 + GPIO ).          
const pin_cfg ayplayer_sd2_rx_pin_cfg                = { GPIOC, { GPIO_PIN_2, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg ayplayer_sd2_tx_pin_cfg                = { GPIOC, { GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg ayplayer_sd2_clk_pin_cfg               = { GPIOB, { GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF5_SPI2 } };
const pin_cfg ayplayer_sd2_cs_pin_cfg                = { GPIOB, { GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, 0 } };

const pin_cfg ayplayer_sd2_push_pin_cfg              = { GPIOB, { GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, 0 } };

// BOOT-USART ( USART3 ). Отладочный.
const pin_cfg ayplayer_boot_tx_pin_cfg               = { GPIOB, { GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART3 } };
const pin_cfg ayplayer_boot_rx_pin_cfg               = { GPIOB, { GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_MEDIUM, GPIO_AF7_USART3 } };

//**********************************************************************
// Глобальный порт.
//**********************************************************************
const pin_cfg ayplayer_gp_cfg[] = {
	// BUTTON.
    ayplayer_button_inc_pin_cfg, ayplayer_button_dec_pin_cfg,

	// ADC.
    ayplayer_adc_bat_pin_cfg, ayplayer_adc_right_pin_cfg, ayplayer_adc_left_pin_cfg,

	// MIDI (USART2).
    ayplayer_midi_uart_rx_pin_cfg,

	// LCD (SPI1 + TIMx).
    ayplayer_lcd_clk_pin_cfg, ayplayer_lcd_pwm_pin_cfg, ayplayer_lcd_mosi_pin_cfg,
	ayplayer_lcd_res_pin_cfg, ayplayer_lcd_dc_pin_cfg, ayplayer_lcd_cs_pin_cfg,

	// micro-sd (SDIO + GPIO).
    ayplayer_sd1_push_pin_cfg, ayplayer_sd1_smd_pin_cfg, ayplayer_sd1_d0_pin_cfg,
	ayplayer_sd1_d1_pin_cfg, ayplayer_sd1_d2_pin_cfg, ayplayer_sd1_d3_pin_cfg,
	ayplayer_sd1_clk_pin_cfg,

	// USB (USB_FS + GPIO).
	ayplayer_otg_fs_vbus_pin_cfg, ayplayer_usb_dm_pin_cfg, ayplayer_usb_dp_pin_cfg,

	// AY (GPIO + TIM1 + SPI3).
	ayplayer_bdir_pin_cfg, ayplayer_ay_1_res_pin_cfg, ayplayer_ay_2_res_pin_cfg,
	ayplayer_bc1_pin_cfg, ayplayer_ay_clk_pin_cfg, ayplayer_spi_audio_clk_pin_cfg,
	ayplayer_spi_audio_tx_pin_cfg, ayplayer_shdn_pin_cfg,
	ayplayer_spi_audio_st_reg_pin_cfg, ayplayer_dp_cs_res_pin_cfg,

	// SPI клавиатура (SPI общий AY, тут только вход).
	ayplayer_button_in_pin_cfg,

	// PWR.
	ayplayer_pwr_5_v_on_pin_cfg, ayplayer_pwr_on_pin_cfg, ayplayer_tp_st_pin_cfg,
	ayplayer_tp_ch_pin_cfg, ayplayer_chip_1_pwr_on_pin_cfg,
	ayplayer_chip_2_pwr_on_pin_cfg,

	// MICRO-SD SPI2 (SPI2 + GPIO).
	ayplayer_sd2_rx_pin_cfg, ayplayer_sd2_tx_pin_cfg, ayplayer_sd2_clk_pin_cfg,
	ayplayer_sd2_cs_pin_cfg, ayplayer_sd2_push_pin_cfg,

	// BOOT-USART (USART3).
	ayplayer_boot_tx_pin_cfg, ayplayer_boot_rx_pin_cfg,

	// SWD.
	ayplayer_swd_io_pin_cfg, ayplayer_swd_clk_pin_cfg,
};

extern global_port ayplayer_gp_obj;

// LCD.
extern pin ayplayer_lcd_res_pin_obj;
extern pin ayplayer_lcd_dc_pin_obj;
extern pin ayplayer_lcd_cs_pin_obj;

// MICROSD 2.
extern pin ayplayer_sd2_cs_pin_obj;
extern pin ayplayer_sd2_push_pin_obj;

// Защелка сдвигового регистра.
extern pin ayplayer_spi_audio_st_reg_pin_obj;

// AY_YM.
extern pin ayplayer_bdir_pin_obj;
extern pin ayplayer_bc1_pin_obj;
extern pin ayplayer_chip_1_pwr_on_pin_obj;
extern pin ayplayer_chip_2_pwr_on_pin_obj;

// PWR.
extern pin ayplayer_pwr_5_v_on_pin_obj;
extern pin ayplayer_pwr_on_pin_obj;

// Потенциометры.
extern pin ayplayer_dp_cs_res_pin_obj;
extern pin ayplayer_shdn_pin_obj;

// Общий вход кнопок.
extern pin ayplayer_button_in_pin_obj;

// + - громкость.
extern pin ayplayer_button_inc_pin_obj;
extern pin ayplayer_button_dec_pin_obj;

void ayplayer_port_init ( void );
