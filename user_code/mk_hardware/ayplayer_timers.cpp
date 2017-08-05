#include "ayplayer_timers.h"

tim1_or_8_comp_one_channel< TIM1_OR_TIM8::TIM1, 1, 2, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N > ay_player_clk_tim;

void ayplayer_timers_init ( void ) {
    ay_player_clk_tim.reinit();
    ay_player_clk_tim.on();
}
