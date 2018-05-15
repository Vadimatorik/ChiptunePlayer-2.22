#include "timer.h"
#include "user_os.h"
#include "ayplayer.h"

const clkTimBaseCfg ay_clk_cfg_clk_tim_param[ AYPLAYER_RCC_CFG_COUNT ] = {
	/// Индекс RCC: 0.
	{
		.period				= 32 - 1 + 2,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 1.
	{
		.period				= 32 - 1 + 2,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 2.
	{
		.period				= 4 - 1,
		.prescaler			= 0,
		.pulse				= 0
	},
	/// Индекс RCC: 3.
	{
		.period				= 4 - 1,
		.prescaler			= 0,
		.pulse				= 0
	}
};

const timCompOneChannelCfg ay_clk_cfg = {
	.tim			= TIM1,
	.cfg			= ay_clk_cfg_clk_tim_param,
	.countCfg		= AYPLAYER_RCC_CFG_COUNT,
	.outChannel		= TIM_CHANNEL_2,
	.polarity		= TIM_OCPOLARITY_LOW,
};

TimCompOneChannel ayClk( &ay_clk_cfg );				/// Генератор частоты AY.

const clkTimBaseCfg interrupt_ay_cfg_clk_tim_param[ AYPLAYER_RCC_CFG_COUNT ] = {
	/// Индекс RCC: 0.
	{
		.period				= 400 - 1,
		.prescaler			= 3000 - 1,
		.pulse				= 0
	},
	/// Индекс RCC: 1.
	{
		.period				= 400 - 1,
		.prescaler			= 3000 - 1,
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

const timInterruptCfg interrupt_ay_cfg = {
	.tim			= TIM6,
	.cfg			= interrupt_ay_cfg_clk_tim_param,
	.countCfg		= AYPLAYER_RCC_CFG_COUNT,
};

TimInterrupt interruptAy( &interrupt_ay_cfg );		/// Генератор прерываний.

const clkTimBaseCfg lcd_pwm_cfg_clk_tim_param[ AYPLAYER_RCC_CFG_COUNT ] = {
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

const timPwmOneChannelCfg lcd_pwm_cfg = {
	.tim			= TIM3,
	.cfg			= interrupt_ay_cfg_clk_tim_param,
	.countCfg		= AYPLAYER_RCC_CFG_COUNT,
	.outChannel		= TIM_CHANNEL_1,
	.polarity		= TIM_OCPOLARITY_LOW
};

TimPwmOneChannel lcdPwm( &lcd_pwm_cfg );			/// Подцветка дисплея.


#ifdef configGENERATE_RUN_TIME_STATS

/// Прерывания с частотый 20 кГц.
const clkTimBaseCfg tim5BaseCfg[ AYPLAYER_RCC_CFG_COUNT ] = {
	/// Индекс RCC: 0.
	{
		.period				=	0xFFFFFFFF,
		.prescaler			=	1500 - 1,
		.pulse				=	0
	},
	/// Индекс RCC: 1.
	{
		.period				=	0xFFFFFFFF,
		.prescaler			=	1500 - 1,
		.pulse				=	0
	},
	/// Индекс RCC: 2.
	{
		.period				=	0xFFFFFFFF,
		.prescaler			=	800 - 1,
		.pulse				=	0
	},
	/// Индекс RCC: 2.
	{
		.period				=	0xFFFFFFFF,
		.prescaler			=	800 - 1,
		.pulse				=	0
	},
};

timCounterCfg		timRunTimeStatsCfg = {
	.tim					= TIM5,
	.cfg					= tim5BaseCfg,
	.countCfg				= AYPLAYER_RCC_CFG_COUNT
};

TimCounter		timRunTimeStats( &timRunTimeStatsCfg );

#endif
