#include "ayplayer_timers.h"

#define TIMER_AY_CLK_CFG                        TIM1_OR_TIM8::TIM1, 1, 8, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N

const tim1_comp_one_channel_base< TIMER_AY_CLK_CFG >* ay_player_clk_tim = nullptr;

void ayplayer_timers_init ( void ) {
    ay_player_clk_tim = tim1_comp_one_channel_base< TIMER_AY_CLK_CFG >::instance();
    ay_player_clk_tim->reinit();
    ay_player_clk_tim->on();
}
