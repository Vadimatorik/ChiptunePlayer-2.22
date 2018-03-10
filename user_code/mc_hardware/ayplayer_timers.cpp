#include "timer.h"
#include "user_os.h"

const clk_tim_param ay_clk_cfg_clk_tim_param[] = {
	/// Индекс RCC: 0.
	{
		.period				= 15,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 1.
	{
		.period				= 15,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 2.
	{
		.period				= 4,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 3.
	{
		.period				= 4,
		.prescaler			= 0,
		.pulse				= 0
	}
};

const tim_comp_one_channel_cfg ay_clk_cfg = {
	.tim			= TIM1,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.p_cfg			= ay_clk_cfg_clk_tim_param,
	.size_cfg		= M_SIZE_ARRAY( ay_clk_cfg_clk_tim_param ),
	.out_channel	= TIM_CHANNEL_2,
	.polarity		= TIM_OCPOLARITY_LOW,
};

tim_comp_one_channel ay_clk_obj( &ay_clk_cfg );				/// Генератор частоты AY.

const clk_tim_param interrupt_ay_cfg_clk_tim_param[] = {
	/// Индекс RCC: 0.
	{
		.period				= 400,
		.prescaler			= 1500 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 1.
	{
		.period				= 400,
		.prescaler			= 1500 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 2.
	{
		.period				= 400,
		.prescaler			= 800 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 3.
	{
		.period				= 400,
		.prescaler			= 800 - 1,
		.pulse				= 0
	},
};

const tim_interrupt_cfg interrupt_ay_cfg = {
	.tim			= TIM6,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.p_cfg			= interrupt_ay_cfg_clk_tim_param,
	.size_cfg		= M_SIZE_ARRAY( interrupt_ay_cfg_clk_tim_param ),
};

tim_interrupt interrupt_ay_obj( &interrupt_ay_cfg );		/// Генератор прерываний.

const clk_tim_param lcd_pwm_cfg_clk_tim_param[] = {
	/// Индекс RCC: 0.
	{
		.period				= 125,
		.prescaler			= 1000 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 1.
	{
		.period				= 125,
		.prescaler			= 1000 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 2.
	{
		.period				= 200,
		.prescaler			= 333 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 2.
	{
		.period				= 200,
		.prescaler			= 333 - 1,
		.pulse				= 0
	},
};

const tim_pwm_one_channel_cfg lcd_pwm_cfg = {
	.tim			= TIM3,
	.tim_channel	= HAL_TIM_ACTIVE_CHANNEL_1,
	.p_cfg			= interrupt_ay_cfg_clk_tim_param,
	.size_cfg		= M_SIZE_ARRAY( lcd_pwm_cfg_clk_tim_param ),
	.out_channel	= TIM_CHANNEL_1,
	.polarity		= TIM_OCPOLARITY_LOW
};

tim_pwm_one_channel lcd_pwm_obj( &lcd_pwm_cfg );			///< Подцветка дисплея.
