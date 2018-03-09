#include "main.h"
#include "ayplayer.h"
#include "fsm.h"



//#include "freertos_headers.h"

/*
#include "ayplayer_hardware.h"

#include "ayplayer_housekeeping.h"
#include "ayplayer_button.h"
#include "ayplayer_shift_register.h"
#include "ayplayer_core.h"
*/

#include "wdt.h"

extern wdt ayplayer_wdt_obj;

ay_player_class_config_strcut ay_cfg = {
	.wdt						= &ayplayer_wdt_obj
};

ay_player_class		ay( &ay_cfg );

extern "C" {

int main ( void ) {

	/*
	ayplayer_mc_hardware();
	ayplayer_housekeeping_init();
	ayplayer_button_init();
	ayplayer_shift_register();
	ayplayer_ay_init();
	ayplayer_core_init();*/

	//vTaskStartScheduler();
    while ( true );
}

}
