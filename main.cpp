#include <stdint.h>
#include "stm32_f20x_f21x_port.h"
#include "stm32_f20x_f21x_rcc.h"


/*
const constexpr rcc_cfg		ay_rcc_cfg = {
	.pll					= array_pll_cfg,
	.pll_count				= sizeof(array_pll_cfg)/sizeof(array_pll_cfg[0])
};*/

const constexpr pin_config_t ayplayer_pin_cfg11[] = {
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_0),					// ADC_BAT.
	MACRO_PIN_CFG_ADC(PORT_A, PORT_PIN_4),					// ADC_RIGHT.
	MACRO_PIN_CFG_ADC(PORT_B, PORT_PIN_1),					// ADC_LEFT.
	{
		.port				= PORT_C,
		.pin_name			= PORT_PIN_0,
		.mode				= PIN_OUTPUT_MODE,
		.output_config		= PIN_OUTPUT_PUSH_PULL_CONFIG,
		.speed				= PIN_LOW_SPEED,
		.pull				= PIN_NO_PULL,
		.af					= PIN_AF_NOT_USE,
		.locked				= PIN_CONFIG_LOCKED,
		.state_after_init	= PIN_STATE_AFTER_INIT_SET
	}
};




//const constexpr pin					led(a);
const constexpr global_port			g_port(ayplayer_pin_cfg11, 4);
//const constexpr rcc					ay_rcc(&ay_rcc_cfg);

uint32_t l = 0;
int main (void){
	*((uint32_t*)0x40023850) |= 0xFF;
	g_port.reinit_all_ports();
	//led.set();

	while(1) {
		l++;
	};
}
