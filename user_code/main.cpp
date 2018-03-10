#include "main.h"
#include "ayplayer.h"

extern wdt								ayplayer_wdt_obj;
extern ayplayer_gpio_struct				ayplayer_gpio_struct_obj;
extern global_port						ayplayer_gp_obj;
extern uart								usart3_obj;
extern rcc								ayplayer_rcc;
extern spi_master_8bit					spi1_obj;
extern spi_master_8bit					spi2_obj;
extern spi_master_8bit					spi3_obj;

ay_player_mc_strcut ay_mcu = {
	.wdt						= &ayplayer_wdt_obj,
	.gpio						= &ayplayer_gpio_struct_obj,
	.gp							= &ayplayer_gp_obj,
	.debug_uart					= &usart3_obj,
	.rcc						= &ayplayer_rcc,
	.spi1						= &spi1_obj,
	.spi2						= &spi2_obj,
	.spi3						= &spi3_obj,
};

ay_player_class_config_strcut ay_cfg = {
	.mcu						= &ay_mcu
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
