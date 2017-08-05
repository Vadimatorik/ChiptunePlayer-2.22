#pragma once

#include "stm32_f20x_f21x_include_module_lib.h"

extern tim1_or_8_comp_one_channel< TIM1_OR_TIM8::TIM1, 1, 2, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N > ay_player_clk_tim;

void ayplayer_timers_init ( void );
