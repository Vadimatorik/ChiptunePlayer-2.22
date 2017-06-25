#include "ayplayer_clock.h"

constexpr const rcc ayplayer_rcc( &ayplayer_rcc_cfg );

int ayplayer_clock_init ( void ) {
    //ayplayer_rcc.pll_sysclk_src_clock_set();
    ayplayer_rcc.hse_sysclk_src_clock_set();
    ayplayer_rcc.global_port_clk_en();
    ayplayer_rcc.spi1_clk_on();

    return 0;
}
