#pragma once

#include "include_module_lib.h"
#include "ayplayer_nvic.h"

extern tim1_and_8_comp_one_channel< TIM1_OR_TIM8::TIM1, 1, 2, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N > ay_player_clk_tim;
extern tim6_and_7_interrupt< TIM6_OR_TIM7::TIM6, 400, 400 > ay_player_interrupt_ay;

void ayplayer_timers_init ( void );
