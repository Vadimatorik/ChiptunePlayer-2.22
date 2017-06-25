#pragma once

#include "stm32_f20x_f21x_rcc.h"
#include "ayplayer_port.h"

const pll_cfg< EC_RCC_PLL_SOURCE::HSE, 25, 240, EC_RCC_PLL_P::DIV_2, 15, EC_RCC_AHB_DIV::DIV_1, EC_RCC_APB1_DIV::DIV_4, EC_RCC_APB2_DIV::DIV_2, 3300 >pll_max;

const constexpr rcc_cfg ayplayer_rcc_cfg = {
    .main_pll_cfg   = &pll_max,
    .pll_count      = 1,
    .gb             = &ayplayer_global_port
};

int ayplayer_clock_init ( void );
