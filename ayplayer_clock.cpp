#include "ayplayer_clock.h"

constexpr const rcc ayplayer_rcc( &ayplayer_rcc_cfg );

int ayplayer_clock_init ( void ) {
    ayplayer_rcc.pll_sysclk_src_clock_set( 0 );
    ayplayer_rcc.global_port_clk_en();

    return 0;
}
