#pragma once

#include "timer.h"
extern tim_comp_one_channel ay_clk_obj;
//< TIM6_OR_TIM7::TIM6, 400, 400 >
extern tim_interrupt interrupt_ay_obj;

void ayplayer_timers_init ( void );
