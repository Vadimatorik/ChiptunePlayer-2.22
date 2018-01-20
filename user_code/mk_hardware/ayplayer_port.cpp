#include "ayplayer_port.h"

global_port ayplayer_gp_obj( ayplayer_gp_cfg, M_SIZE_ARRAY( ayplayer_gp_cfg ) );

// LCD.
pin ayplayer_lcd_res_pin_obj			( &ayplayer_lcd_res_pin_cfg );
pin ayplayer_lcd_dc_pin_obj				( &ayplayer_lcd_dc_pin_cfg );
pin ayplayer_lcd_cs_pin_obj				( &ayplayer_lcd_cs_pin_cfg );

// MICROSD 2.
pin ayplayer_sd2_cs_pin_obj				( &ayplayer_sd2_cs_pin_cfg );
// Не используется в текущей версии платы.
// pin ayplayer_sd2_push_pin_obj			( &ayplayer_sd2_push_pin_cfg );

// Защелка сдвигового регистра.
pin ayplayer_spi_audio_st_reg_pin_obj	( &ayplayer_spi_audio_st_reg_pin_cfg );

// AY_YM.
pin ayplayer_bdir_pin_obj				( &ayplayer_bdir_pin_cfg );
pin ayplayer_bc1_pin_obj				( &ayplayer_bc1_pin_cfg );
pin ayplayer_chip_1_pwr_on_pin_obj		( &ayplayer_chip_1_pwr_on_pin_cfg );
pin ayplayer_chip_2_pwr_on_pin_obj		( &ayplayer_chip_2_pwr_on_pin_cfg );

// PWR.
pin ayplayer_pwr_5_v_on_pin_obj			( &ayplayer_pwr_5_v_on_pin_cfg );
pin ayplayer_pwr_on_pin_obj				( &ayplayer_pwr_on_pin_cfg );

// Потенциометры.
pin ayplayer_dp_cs_res_pin_obj			( &ayplayer_dp_cs_res_pin_cfg );
pin ayplayer_shdn_pin_obj				( &ayplayer_shdn_pin_cfg );

// Общий вход кнопок.
pin ayplayer_button_in_pin_obj			( &ayplayer_button_in_pin_cfg );

// + - громкость.
pin ayplayer_button_inc_pin_obj			( &ayplayer_button_inc_pin_cfg );
pin ayplayer_button_dec_pin_obj			( &ayplayer_button_dec_pin_cfg );

void ayplayer_port_init ( void ) {
    ayplayer_gp_obj.reinit_all_ports();			// Инициализируем все порты.
    // Выставляем состояние на тех, на которых это критично в момент запуска
    // (критичено значение сразу после включения).
    ayplayer_lcd_res_pin_obj.set(1);
    ayplayer_lcd_dc_pin_obj.set(1);
    ayplayer_pwr_5_v_on_pin_obj.set(1);
    ayplayer_pwr_on_pin_obj.set(1);
}
