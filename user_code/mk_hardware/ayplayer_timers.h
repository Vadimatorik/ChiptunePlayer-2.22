#pragma once

#include "timer.h"
//< TIM1_OR_TIM8::TIM1, 1, 2, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N >
extern tim_comp_one_channel ay_player_clk_tim;
//< TIM6_OR_TIM7::TIM6, 400, 400 >
extern tim_interrupt ay_player_interrupt_ay;

void ayplayer_timers_init ( void );
