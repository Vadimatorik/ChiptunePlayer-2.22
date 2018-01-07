#include "ayplayer_hardware.h"

void ayplayer_mc_hardware ( void ) {
	//ayplayer_wdt_init();
	ayplayer_port_init();
	ayplayer_clock_init();
	ayplayer_adc_init();
	ayplayer_spi_init();
	ayplayer_timers_init();
	ayplayer_usart_init();
}
