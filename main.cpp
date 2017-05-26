#include <stdint.h>
#include "stm32_f20x_f21x_port.h"
#include "stm32_f20x_f21x_rcc.h"


/*
const constexpr rcc_cfg		ay_rcc_cfg = {
	.pll					= array_pll_cfg,
	.pll_count				= sizeof(array_pll_cfg)/sizeof(array_pll_cfg[0])
};*/


//const constexpr pin					led(a);
//const constexpr global_port			g_port(a, 1);
//const constexpr rcc					ay_rcc(&ay_rcc_cfg);

uint32_t l = 0;
int main (void){
	//g_port.reinit_all_ports();
	//led.set();

	while(1) {
		l++;
	};
}
