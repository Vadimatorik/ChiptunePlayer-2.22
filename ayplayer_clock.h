#ifndef AYPLAYER_CLOCK_H_
#define AYPLAYER_CLOCK_H_

#include "stm32_f20x_f21x_rcc.h"

const constexpr pll_cfg array_pll_cfg = {
    .s  = EC_RCC_PLL_SOURCE::HSE,
    .m  = 16,
    .n  = 240,
    .p  = EC_RCC_PLL_P::DIV_2,
    .q  = 15
};

const constexpr rcc_cfg ayplayer_rcc_cfg = {
    .pll            = &array_pll_cfg,
    .pll_count      = 1
};

constexpr const rcc ayplayer_rcc( &ayplayer_rcc_cfg );
#endif
