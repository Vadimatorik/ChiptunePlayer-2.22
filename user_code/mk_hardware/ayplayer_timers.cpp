#include "ayplayer_timers.h"

const tim_comp_one_channel_cfg		ay_clk_cfg = {
	.tim			= TIM1,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.period			= 8,
	.prescaler		= 0,
	.out_channel	= TIM_CHANNEL_2,
	.polarity		= TIM_OCPOLARITY_LOW,
	.pulse			= 0,
};

tim_comp_one_channel ay_clk_obj( &ay_clk_cfg );					// Генератор частоты AY.

const tim_interrupt_cfg		interrupt_ay_cfg = {
	.tim			= TIM6,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.period			= 400,
	.prescaler		= 400
};

tim_interrupt interrupt_ay_obj( &interrupt_ay_cfg );			// Генератор прерываний.

const tim_pwm_one_channel_cfg	lcd_pwm_cfg = {
	.tim			= TIM3,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.period			= 290,
	.prescaler		= 400,
	.out_channel	= TIM_CHANNEL_1,
	.polarity		= TIM_OCPOLARITY_LOW
};

tim_pwm_one_channel lcd_pwm_obj( &lcd_pwm_cfg );				// Подцветка дисплея.

void ayplayer_timers_init ( void ) {
	ay_clk_obj.reinit();
	ay_clk_obj.on();
	lcd_pwm_obj.reinit();
	lcd_pwm_obj.on();
	lcd_pwm_obj.duty_set(0.4);
	interrupt_ay_obj.reinit();
	interrupt_ay_obj.on();
	//NVIC_EnableIRQ( TIM6_DAC_IRQn );
}
