#include "ayplayer_port.h"

//
// Объекты pin (ручное управление выводами).
//
// LCD.
pin< LCD_RES_PIN_HEADING >              lcd_res_obj;
pin< LCD_DC_PIN_HEADING >               lcd_dc_obj;
pin< LCD_CS_PIN_HEADING >               lcd_cs_obj;

// MICROSD 2.
pin< SD2_CS_PIN_HEADING >               sd2_cs_obj;
pin< SD2_PUSH_PIN_HEADING >             sd2_push_obj;

// Защелка сдвигового регистра.
pin< SPI_AUDIO_ST_REG_PIN_HEADING >     spi_audio_st_reg_obj;

// AY_YM.
pin< BDIR_PIN_HEADING >                 bdir_obj;
pin< BC1_PIN_HEADING >                  bc1_obj;
pin< CHIP_1_PWR_ON_PIN_HEADING >        chip_1_pwr_on_obj;
pin< CHIP_2_PWR_ON_PIN_HEADING >        chip_2_pwr_on_obj;

// PWR.
pin< PWR_5_V_IN_PIN_HEADING >           pwr_5_v_on_obj;
pin< PWR_ON_PIN_HEADING >               pwr_on_obj;

// Потенциометры.
pin< DP_CS_PIN_HEADING >                dp_cs_res_obj;
pin< SHDN_PIN_HEADING >                 shdn_obj;

// Общий вход кнопок.
pin< B_IN_PIN_HEADING >                 b_in;

// + - громкость.
pin< BUTTON_INC >                       b_inc;
pin< BUTTON_DEC >                       b_dec;

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == EC_ANSWER_GP::SUCCESS ) ? 0 : -1;
}
