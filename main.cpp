#include <stdint.h>
#include "stm32_f20x_f21x_port.h"
#include "stm32_f20x_f21x_rcc.h"


/*
const constexpr rcc_cfg		ay_rcc_cfg = {
	.pll					= array_pll_cfg,
	.pll_count				= sizeof(array_pll_cfg)/sizeof(array_pll_cfg[0])
};*/

const constexpr pin_config_t ayplayer_pin_cfg11[] = {
	M_PIN_CFG_ADC(EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_0),					// ADC_BAT.
	M_PIN_CFG_ADC(EC_PORT_NAME::A, EC_PORT_PIN_NAME::PIN_4),					// ADC_RIGHT.
	M_PIN_CFG_ADC(EC_PORT_NAME::B, EC_PORT_PIN_NAME::PIN_1),					// ADC_LEFT.
	/*{
		.port				= ENUM_PORT_NAME::C,
		.pin_name			= ENUM_PORT_PIN_NAME::PIN_0,
		.mode				= ENUM_PIN_MODE::OUTPUT,
		.output_config		= ENUM_PIN_OUTPUT_CFG::PUSH_PULL,
		.speed				= ENUM_PIN_SPEED::LOW,
		.pull				= ENUM_PIN_PULL::NO,
		.af					= PIN_AF_NOT_USE,
		.locked				= LOCKED,
		.state_after_init	= SET
	},
	{
		.port				= ENUM_PORT_NAME::B,
		.pin_name			= ENUM_PORT_PIN_NAME::PIN_4,
		.mode				= ENUM_PIN_MODE::OUTPUT,
		.output_config		= ENUM_PIN_OUTPUT_CFG::PUSH_PULL,
		.speed				= ENUM_PIN_SPEED::LOW,
		.pull				= ENUM_PIN_PULL::NO,
		.af					= PIN_AF_NOT_USE,
		.locked				= LOCKED,
		.state_after_init	= SET
	},
	{
		.port				= ENUM_PORT_NAME::B,
		.pin_name			= ENUM_PORT_PIN_NAME::PIN_12,
		.mode				= ENUM_PIN_MODE::OUTPUT,
		.output_config		= ENUM_PIN_OUTPUT_CFG::PUSH_PULL,
		.speed				= ENUM_PIN_SPEED::LOW,
		.pull				= ENUM_PIN_PULL::NO,
		.af					= PIN_AF_NOT_USE,
		.locked				= LOCKED,
		.state_after_init	= SET
	}*/
};




const constexpr pin					led(ayplayer_pin_cfg11);
const constexpr global_port			g_port(ayplayer_pin_cfg11, 3);
//const constexpr rcc					ay_rcc(&ay_rcc_cfg);

uint32_t l = 0;
int main (void){
	*((uint32_t*)(0x40023800 + 0x30)) |= 0xFF;
	g_port.reinit_all_ports();
	led.reinit(0);
	led.reinit(1);
	led.reinit(2);
	while(1) {
		l++;
	};
}
