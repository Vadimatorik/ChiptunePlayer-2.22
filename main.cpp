#include <stdint.h>

#include "stm32f2_api/stm32_f20x_f21x_gpio.h"

volatile uint8_t a_loop[] = {1, 2, 2, 2, 2, 3, 4};


pin_config a[2] = {	pin_config(port_a, port_pin_0, pin_output_mode, pin_output_push_pull_config, pin_low_speed, pin_no_pull, pin_af_not_use),
					pin_config(port_a, port_pin_12, pin_output_mode, pin_output_push_pull_config, pin_low_speed, pin_no_pull, pin_af_not_use)};

global_port g_port(a, 2);

int main (void){
	g_port.init();
	while(1) {
		a_loop[0]++;
	};
}
//5368	   1463	      4	   6835	   1ab3
//5408	   1463	    256	   7127	   1bd7
