#include "ayplayer_port.h"

//
// Объекты pin (ручное управление выводами).
//
// LCD.
pin< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_4 >  lcd_res_obj;
pin< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_5 >  lcd_dc_obj;
pin< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_2 >  lcd_cs_obj;

// MICROSD 2.
pin< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_7 >  sd2_cs_obj;

// Защелка сдвигового регистра.
pin< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_8 >  spi_audio_st_reg_obj;

// AY_YM.
pin< EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_10 > bdir_obj;
pin< EC_PORT_NAME::C, EC_PORT_PIN_NAME::PIN_6 >  bc1_obj;

// Потенциометры.
pin< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_14 > dp_cs_res_obj;
pin< EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_6 >  shdn_obj;

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == E_ANSWER_GP::SUCCESS ) ? 0 : -1;
}
