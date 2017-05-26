#include "stm32_f20x_f21x_rcc.h"

const constexpr pll_cfg		array_pll_cfg = {
	.s					= pll_source_hse,
	.m					= 25,
	.n					= 240,
	.p					= 2,
};

const main_pll pll_array(&array_pll_cfg);
