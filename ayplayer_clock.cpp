#include "ayplayer_clock.h"

constexpr const rcc ayplayer_rcc( &ayplayer_rcc_cfg );

int ayplayer_clock_init ( void ) {
    ayplayer_rcc.pll_main_on();
    return 0;
}
