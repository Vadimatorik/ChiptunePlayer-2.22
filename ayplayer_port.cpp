#include "ayplayer_port.h"



const constexpr pin_config_t ayplayer_global_port_pin_cfg_1[] = {
    adc_bat, adc_right, adc_left,                                                                           // ADC.
    midi_uart_rx,                                                                                           // MIDI (USART2).
    lcd_clk, lcd_miso, lcd_mosi, lcd_res, lcd_dc, lcd__cs,                                                  // LCD (SPI1 + TIMx).
    sd1_push, sd1_smd, sd1_d0, sd1_d1, sd1_d2, sd1_d3, sd1_clk,                                             // micro-sd (SDIO + GPIO).
    otg_fs_vbus, usb_dm, usb_dp,                                                                            // USB (USB_FS + GPIO).
    bdir, ay_1_res, ay_2_res, bc1, ay_clk, spi_audio_clk, spi_audio_tx, shdn, spi_audio_st_reg, cs_res,     // AY (GPIO + TIM1 + SPI3)
    button_in,                                                                                              // SPI клавиатура (SPI общий AY, тут только вход).
    swd_io, swd_clk,                                                                                        // SWD.
    on_5v, power_on, tp_st, tp_ch, ay1_on, ay2_on,                                                          // PWR.
    sd2_rx, sd2_tx, sd2__clk, sd2_cs, sd2_push,                                                             // MICRO-SD SPI2 (SPI2 + GPIO).
    boot_tx, boot_rx                                                                                        // BOOT-USART (USART3).
};

const constexpr global_port ayplayer_global_port( ayplayer_global_port_pin_cfg_1, M_SIZE_ARRAY(ayplayer_global_port_pin_cfg_1) );

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == E_ANSWER_GP::SUCCESS )?0:-1;
}
