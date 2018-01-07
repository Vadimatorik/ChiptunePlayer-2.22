#include "main.h"

extern "C" {

int main ( void ) {
	ayplayer_mc_hardware();
	ayplayer_housekeeping_init();
	ayplayer_button_init();
	ayplayer_shift_register();
	ayplayer_ay_init();
//	ayplayer_core_init();

    vTaskStartScheduler();
    while ( true );
}

}
