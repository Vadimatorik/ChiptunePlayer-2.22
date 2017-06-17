#ifndef AYPLAYER_PORT_H_
#define AYPLAYER_PORT_H_

#include "stm32_f20x_f21x_port.h"

/*
 * Структура инициализации всех выводов порта.
 */
const constexpr pin_config_t ayplayer_global_port_pin_cfg[] = {
    /*
     * ADC.
     */
    M_PIN_CFG_ADC(EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_0),                    // ADC_BAT.
    M_PIN_CFG_ADC(EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_4),                    // ADC_RIGHT.
    M_PIN_CFG_ADC(EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_1),                    // ADC_LEFT.

    /*
     * EXTI кнопки.
     */
    {   // B_V_UP.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_1,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // B_V_DOWN.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_2,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * MIDI (USART2).
     */
    {   // MIDI_UART_RX.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_3,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::USART2,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * LCD (SPI1 + TIMx)
     */
    {   // LCD_CLK.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_5,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI1,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // LCD_MISO.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_6,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI1,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // LCD_MOSI.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_7,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI1,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // LCD_RES.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_4,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::SET
    },
    {   // LCD_DC.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_5,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // LCD_CS.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_2,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },

    /*
     * MICRO-SD SDIO (SDIO + GPIO).
     */
    {   // SD1_PUSH.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_8,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_SMD.
        .port               = EC_PORT_NAME::D,
        .pin_name           = EC_PORT_PIN_NAME::PIN_2,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_D0.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_8,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_D1.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_9,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_D2.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_10,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_D3.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_11,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD_CLK.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_12,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SDIO,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * USB (USB_FS + GPIO).
     */
    {   // OTG_FS_VBUS
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_9,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // USB_DM
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_11,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::HIGH,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::OTG_FS,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // USB_DP.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_12,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::HIGH,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::OTG_FS,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * AY (GPIO + TIM1 + SPI3)
     */
    {   // BDIR.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_10,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // AY_1_RES.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_15,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // AY_2_RES.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_15,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // BC1.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_6,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // AY_CLK.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_0,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::FAST,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::TIM1,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SPI_AUDIO_CLK.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_3,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI3,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SPI_AUDIO_TX.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_5,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI3,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SHDN.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_6,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SPI_AUDIO_ST_REG.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_8,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // CS_RES
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_14,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },


    /*
     * SPI клавиатура (SPI общий AY, тут только вход).
     */
    {   // BUTTON_IN.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_7,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * SWD.LOW
     */
    {   // SWDIO.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_13,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::SYS,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SWDCLK.
        .port               = EC_PORT_NAME::A,
        .pin_name           = EC_PORT_PIN_NAME::PIN_14,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::DOWN,
        .af                 = EC_PIN_AF::SYS,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * PWR.
     */
    {   // 5V_ON.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_0,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // POWER_ON.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_1,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::SET      // Чтобы после нажатия на кнопку
                                                                // включения зафиксироваться во включенном
                                                                // состоянии.
    },
    {   // TP_ST.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_14,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // TP_CH.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_15,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // AY1_ON.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_4,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // AY2_ON.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_12,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },

    /*
     * MICRO-SD SPI2 (SPI2 + GPIO).
     */
    {   // SD2_RX.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_2,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI2,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD2_TX.
        .port               = EC_PORT_NAME::C,
        .pin_name           = EC_PORT_PIN_NAME::PIN_3,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI2,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD2_CLK.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_13,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::SPI2,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // SD2_CS.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_7,
        .mode               = EC_PIN_MODE::OUTPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::PUSH_PULL,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::RESET
    },
    {   // SD2_PUSH.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_9,
        .mode               = EC_PIN_MODE::INPUT,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::LOW,
        .pull               = EC_PIN_PULL::UP,
        .af                 = EC_PIN_AF::NO_USE,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },

    /*
     * BOOT-USART (USART3)
     */
    {   // BOOT_TX.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_10,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::USART3,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
    {   // BOOT_RX.
        .port               = EC_PORT_NAME::B,
        .pin_name           = EC_PORT_PIN_NAME::PIN_11,
        .mode               = EC_PIN_MODE::AF,
        .output_config      = EC_PIN_OUTPUT_CFG::NO_USE,
        .speed              = EC_PIN_SPEED::MEDIUM,
        .pull               = EC_PIN_PULL::NO_USE,
        .af                 = EC_PIN_AF::USART3,
        .locked             = EC_LOCKED::LOCKED,
        .state_after_init   = EC_PIN_STATE_AFTER_INIT::NO_USE
    },
};

int ayplayer_port_init ( void );

#endif
