#pragma once

#include "stm32_f20x_f21x_include_module_lib.h"
#include "ayplayer_port.h"

//const constexpr pll_cfg< EC_RCC_PLL_SOURCE::HSE, 25, 240, EC_RCC_PLL_P::DIV_2, 5, EC_RCC_AHB_DIV::DIV_1, EC_RCC_APB1_DIV::DIV_4, EC_RCC_APB2_DIV::DIV_2, 3300 >pll_max;

// HSE  = 16 000 000
// AHB  =  4 000 000
// APB1 =  4 000 000
// APB2 =  4 000 000
const constexpr src_dev_cfg< EC_RCC_AHB_DIV::DIV_4, EC_RCC_APB1_DIV::DIV_1, EC_RCC_APB2_DIV::DIV_1 >pll_hse_max;

const constexpr rcc_cfg ayplayer_rcc_cfg = {
    .main_pll_cfg   = nullptr,//&pll_max,
    .pll_cfg_count  = 0,//1,
    .dev_cfg        = &pll_hse_max,
    .src_cfg_count  = 1,
    .gb             = &ayplayer_global_port
};

int ayplayer_clock_init ( void );
