#pragma once

#include "stm32_f20x_f21x_rcc.h"

const pll_cfg< EC_RCC_PLL_SOURCE::HSE, 16, 240, EC_RCC_PLL_P::DIV_2, 15 >pll_120;

const constexpr rcc_cfg ayplayer_rcc_cfg = {
    .main_pll_cfg   = &pll_120,
    .pll_count      = 1
};

int ayplayer_clock_init ( void );
