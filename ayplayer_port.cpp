#include "stm32_f20x_f21x_port.h"

/*
 * Структуры инициализации всех выводов микроконтроллера.
 */
const constexpr pin_config_t ayplayer_pin_cfg[] = {
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_0),					// ADC_BAT.
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_4),					// ADC_RIGHT.
	MACRO_PIN_CFG_ADC(PORT_B, PORT_PIN_1),					// ADC_LEFT.
};


