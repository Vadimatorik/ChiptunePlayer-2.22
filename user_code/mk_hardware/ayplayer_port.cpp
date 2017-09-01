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

// Защелка сдвигового регистра.
pin< SPI_AUDIO_ST_REG_PIN_HEADING >     spi_audio_st_reg_obj;

// AY_YM.
pin< BDIR_PIN_HEADING >                 bdir_obj;
pin< BC1_PIN_HEADING >                  bc1_obj;

// Потенциометры.
pin< DP_CS_PIN_HEADING >                dp_cs_res_obj;
pin< SHDN_PIN_HEADING >                 shdn_obj;

// Общий вход кнопок.
pin< B_IN_PIN_HEADING >                 b_in;

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == EC_ANSWER_GP::SUCCESS ) ? 0 : -1;
}
