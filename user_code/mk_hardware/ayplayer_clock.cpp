#include "ayplayer_clock.h"

rcc ayplayer_rcc( nullptr );


int ayplayer_clock_init ( void ) {
    //ayplayer_rcc.pll_sysclk_src_clock_set();
    //ayplayer_rcc.hse_sysclk_src_clock_set();
    ayplayer_rcc.set_cfg( 0 );
    return 0;
}
