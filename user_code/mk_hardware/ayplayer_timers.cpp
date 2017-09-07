#include "ayplayer_timers.h"

// Генератор частоты AY.
tim1_and_8_comp_one_channel< TIM1_OR_TIM8::TIM1, 1, 2, EC_TIM_CH_TOGGLE::CH_2, EC_TIM_CH_MODE::N > ay_player_clk_tim;

// Генератор прерываний.
tim6_and_7_interrupt< TIM6_OR_TIM7::TIM6, 400, 400 > ay_player_interrupt_ay;

// Подцветка дисплея.
tim3_and_4_pwm_one_channel< TIM3_OR_TIM4::TIM3, 290, 100, EC_TIM_3_AND_4_CH::CH_1 > ay_player_lcd_pwm;

void ayplayer_timers_init ( void ) {
    ay_player_interrupt_ay.reinit();
    ayplayer_nvic.irq_set_priority( IRQ_NAME::TIM6, IRQ_PRIO::PRIO_5 );
    ayplayer_nvic.irq_enable( IRQ_NAME::TIM6 );
    ay_player_clk_tim.reinit();
    ay_player_lcd_pwm.reinit();
    ay_player_lcd_pwm.duty_set(0.4);
    ay_player_lcd_pwm.on();
}
