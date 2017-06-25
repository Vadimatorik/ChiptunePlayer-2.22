#include "ayplayer_port.h"


//const constexpr pin pin_lcd_res( &lcd_res );

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == E_ANSWER_GP::SUCCESS ) ? 0 : -1;
}
