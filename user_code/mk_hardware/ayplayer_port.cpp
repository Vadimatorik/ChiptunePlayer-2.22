#include "ayplayer_port.h"

global_port ayplayer_global_port_obj( ayplayer_global_port_pin_cfg, M_SIZE_ARRAY(ayplayer_global_port_pin_cfg) );

//
// Объекты pin (ручное управление выводами).
//
// LCD.
pin lcd_res_pin_obj( &lcd_res_pin_cfg );
pin lcd_dc_pin_obj( &lcd_dc_pin_cfg );
pin lcd_cs_pin_obj( &lcd_cs_pin_cfg );

// MICROSD 2.
pin sd2_cs_pin_obj( &sd2_cs_pin_cfg );
pin sd2_push_pin_obj( &sd2_push_pin_cfg );

// Защелка сдвигового регистра.
pin spi_audio_st_reg_pin_obj( &spi_audio_st_reg_pin_cfg );

// AY_YM.
pin bdir_pin_obj( &bdir_pin_cfg );
pin bc1_pin_obj( &bc1_pin_cfg );
pin chip_1_pwr_on_pin_obj( &chip_1_pwr_on_pin_cfg );
pin chip_2_pwr_on_pin_obj( &chip_2_pwr_on_pin_cfg );

// PWR.
pin pwr_5_v_on_pin_obj( &pwr_5_v_on_pin_cfg );
pin pwr_on_pin_obj( &pwr_on_pin_cfg );

// Потенциометры.
pin dp_cs_res_pin_obj( &dp_cs_res_pin_cfg );
pin shdn_pin_obj( &shdn_pin_cfg );

// Общий вход кнопок.
pin button_in_pin_obj( &button_in_pin_cfg );

// + - громкость.
pin button_inc_pin_obj( &button_inc_pin_cfg );
pin button_dec_pin_obj( &button_dec_pin_cfg );

int ayplayer_port_init ( void ) {
    ayplayer_global_port_obj.reinit_all_ports();
    lcd_res_pin_obj.set(1);
    lcd_dc_pin_obj.set(1);
    pwr_5_v_on_pin_obj.set(1);
    pwr_on_pin_obj.set(1);

    return 0;
}
