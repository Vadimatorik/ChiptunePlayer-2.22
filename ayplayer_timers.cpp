#include "ayplayer_timers.h"

#define TIMER_AY_CLK_CFG                        TIM1_OR_TIM8::TIM1, 1, 8, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N

void ayplayer_timers_init ( void ) {
    const tim1_comp_one_channel_base< TIMER_AY_CLK_CFG >*tim1 = tim1_comp_one_channel_base< TIMER_AY_CLK_CFG >::instance();
    tim1->reinit();
    tim1->on();
    volatile tim_1_or_8_registers_struct* tim = ( tim_1_or_8_registers_struct* )TIM1_OR_TIM8::TIM1;

    (void) tim;
    uint32_t a = 0;
    (void)a;
    while( true ) {
        a++;
    }
}
