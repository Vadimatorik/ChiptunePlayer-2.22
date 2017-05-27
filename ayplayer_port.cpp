#include "stm32_f20x_f21x_port.h"

/*
 * Структуры инициализации всех выводов микроконтроллера.
 */
const constexpr pin_config_t ayplayer_pin_cfg[] = {
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_0),					// ADC_BAT.
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_4),					// ADC_RIGHT.
	MACRO_PIN_CFG_ADC(PORT_B, PORT_PIN_1),					// ADC_LEFT.
	/*{
		.port				= PORT_C,
		.pin_name			= PORT_PIN_0,
		.mode				= PIN_OUTPUT_MODE,
		.output_config		= PIN_OUTPUT_PUSH_PULL_CONFIG,
		.speed				= PIN_LOW_SPEED,
		.pull				= PIN_NO_PULL,
		.af					= PIN_AF_NOT_USE,
		.locked				= PIN_CONFIG_LOCKED,
		.state_after_init	= PIN_STATE_AFTER_INIT_SET
	}*/
};


