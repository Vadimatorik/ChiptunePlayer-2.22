#include <stdint.h>
#include "stm32_f20x_f21x_port.h"

constexpr pin_config_t a[] = {
	{
		.port				= PORT_A,
		.pin_name			= PORT_PIN_0,
		.mode				= PIN_OUTPUT_MODE,
		.output_config		= PIN_OUTPUT_PUSH_PULL_CONFIG,
		.speed				= PIN_LOW_SPEED,
		.pull				= PIN_NO_PULL,
		.af					= PIN_AF_NOT_USE,
		.locked				= PIN_CONFIG_LOCKED,
		.state_after_init	= PIN_STATE_AFTER_INIT_RESET
	},
	{
		.port				= (enum_port_name)21,
		.pin_name			= PORT_PIN_12,
		.mode				= PIN_OUTPUT_MODE,
		.output_config		= PIN_OUTPUT_PUSH_PULL_CONFIG,
		.speed				= PIN_LOW_SPEED,
		.pull				= PIN_NO_PULL,
		.af					= PIN_AF_NOT_USE,
		.locked				= PIN_CONFIG_LOCKED,
		.state_after_init	= PIN_STATE_AFTER_INIT_RESET
	}
};

const constexpr pin led(a);
const constexpr global_port g_port(a, 1);

uint32_t l;
int main (void){
	g_port.reinit_all_ports();
	led.set();

	while(1) {
		l++;
	};
}
