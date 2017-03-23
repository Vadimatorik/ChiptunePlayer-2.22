#include <stdint.h>

#include "stm32f2_api/stm32_f20x_f21x_port.h"

volatile uint8_t a_loop[] = {1, 2, 2, 2, 2, 3, 4};


const pin_config a[2] = {
		{.port = port_a, .pin_name = port_pin_0,	.mode = pin_output_mode,
				.output_config = pin_output_push_pull_config,	.speed = pin_low_speed,
				.pull = pin_no_pull,	.af = pin_af_not_use,
				.locked = pin_config_locked, .state_after_init = pin_state_after_init_reset},
		{.port = port_b, .pin_name = port_pin_12,	.mode = pin_output_mode,
				.output_config = pin_output_push_pull_config,	.speed = pin_low_speed,
				.pull = pin_no_pull,	.af = pin_af_not_use,
				.locked = pin_config_locked, .state_after_init = pin_state_after_init_reset},
		};

pin led(a, 2);
global_port g_port(a, 2);

int main (void){
	g_port.reinit_all_ports();
	led.set();
	led.reinit(1);
	while(1) {
		a_loop[0]++;
	};
}
//5368	   1463	      4	   6835	   1ab3
//5408	   1463	    256	   7127	   1bd7
//5408	   1463	     32	   6903	   1af7
//5408	   1463	    184	   7055	   1b8f
//5808	   1463	    204	   7475	   1d33
//6488	   1463	    264	   8215	   2017
//6500	   1463	    264	   8227	   2023
