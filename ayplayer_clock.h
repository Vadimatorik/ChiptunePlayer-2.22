#pragma once

#include "stm32_f20x_f21x_rcc.h"

const pll_cfg_check_param< EC_RCC_PLL_SOURCE::HSE, 16, 240, EC_RCC_PLL_P::DIV_2, 15 >pll_120;

const constexpr rcc_cfg ayplayer_rcc_cfg = {
    .pll            = &pll_120,
    .pll_count      = 1
};

constexpr const rcc ayplayer_rcc( &ayplayer_rcc_cfg );
