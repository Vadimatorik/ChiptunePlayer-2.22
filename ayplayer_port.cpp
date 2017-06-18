#include "ayplayer_port.h"

const constexpr global_port ayplayer_global_port( ayplayer_global_port_pin_cfg, M_SIZE_ARRAY(ayplayer_global_port_pin_cfg) );

int ayplayer_port_init ( void ) {
    return ( ayplayer_global_port.reinit_all_ports() == E_ANSWER_GP::SUCCESS )?0:-1;
}
