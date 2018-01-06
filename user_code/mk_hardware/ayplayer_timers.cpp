#include "ayplayer_timers.h"

const tim_comp_one_channel_cfg		ay_f_cfg = {
	.tim			= TIM1,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.period			= 1,
	.prescaler		= 0,
	.out_channel	= TIM_CHANNEL_2,
	.polarity		= TIM_OCPOLARITY_LOW,
	.pulse			= 1,
};

// Генератор частоты AY.
tim_comp_one_channel clk_tim_obj( &ay_f_cfg );

// Генератор прерываний.
//tim6_and_7_interrupt< TIM6_OR_TIM7::TIM6, 400, 400 > ay_player_interrupt_ay;
tim_interrupt interrupt_ay_obj( nullptr );

// Подцветка дисплея.
//tim3_and_4_pwm_one_channel< TIM3_OR_TIM4::TIM3, 290, 100, EC_TIM_3_AND_4_CH::CH_1 > ay_player_lcd_pwm;

void ayplayer_timers_init ( void ) {
	clk_tim_obj.reinit();
	clk_tim_obj.on();

	/*
	ay_player_interrupt_ay.reinit();
	ayplayer_nvic.irq_set_priority( IRQ_NAME::TIM6, IRQ_PRIO::PRIO_5 );
	ayplayer_nvic.irq_enable( IRQ_NAME::TIM6 );
	ay_player_clk_tim.reinit();
	ay_player_lcd_pwm.reinit();
	ay_player_lcd_pwm.duty_set(0.4);        // ВЫПЕЛИТЬ КОСТЫЛЬ!!!
	ay_player_lcd_pwm.on();*/
}
