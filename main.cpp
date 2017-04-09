#include <stdint.h>
#include "stm32_f20x_f21x_port.h"

constexpr pin_config a[] = {
	{
		.port = port_a,
		.pin_name = port_pin_0,
		.mode = pin_output_mode,
		.output_config = pin_output_push_pull_config,
		.speed = pin_low_speed,
		.pull = pin_no_pull,
		.af = pin_af_not_use,
		.locked = pin_config_locked,
		.state_after_init = pin_state_after_init_reset
	},
	{
		.port = port_b,
		.pin_name = port_pin_12,
		.mode = pin_output_mode,
		.output_config = pin_output_push_pull_config,
		.speed = pin_low_speed,
		.pull = pin_no_pull,
		.af = pin_af_not_use,
		.locked = pin_config_locked,
		.state_after_init = pin_state_after_init_reset
	}
};

const constexpr pin led(a, 1);
const constexpr global_port g_port(a, 2);


int main (void){
	g_port.reinit_all_ports();
	led.set();

	while(1) {
		//l++;
	};
}
