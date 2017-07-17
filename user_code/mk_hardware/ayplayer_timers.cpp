#include "ayplayer_timers.h"


const tim1_comp_one_channel_cfg_t ay_player_clk_tim_cfg = {
    .p_tim          = TIM1_OR_TIM8::TIM1,
    .prescaler      = 1,
    .period_toggle  = 2,
    .ch_toggle      = EC_TIM_CH_TOGGLE::CH_2,
    .mode           = EC_TIM_CH_MODE::N
};

tim1_comp_one_channel ay_player_clk_tim ( &ay_player_clk_tim_cfg );

void ayplayer_timers_init ( void ) {
    ay_player_clk_tim.reinit();
    ay_player_clk_tim.on();
}
