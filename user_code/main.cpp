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
extern adc_one_channel					adc_bat_obj;
extern tim_comp_one_channel				ay_clk_obj;
extern tim_pwm_one_channel				lcd_pwm_obj;
extern tim_interrupt					interrupt_ay_obj;
extern run_time_logger					ay_log_obj;

extern module_shift_register			sr_ay;
extern module_shift_register			sr_button;

ay_player_mc_strcut ay_mcu = {
	.wdt						= &ayplayer_wdt_obj,
	.gpio						= &ayplayer_gpio_struct_obj,
	.gp							= &ayplayer_gp_obj,
	.debug_uart					= &usart3_obj,
	.rcc						= &ayplayer_rcc,
	.spi1						= &spi1_obj,
	.spi2						= &spi2_obj,
	.spi3						= &spi3_obj,
	.adc1						= &adc_bat_obj,
	.ay_clk						= &ay_clk_obj,
	.lcd_pwm					= &lcd_pwm_obj,
	.interrupt_ay				= &interrupt_ay_obj
};

ay_player_pcb_strcut ay_pcb = {
	.sr_ay						= &sr_ay,
	.sr_button					= &sr_button
};

ay_player_class_config_strcut ay_cfg = {
	.mcu						= &ay_mcu,
	.l							= &ay_log_obj,
	.pcb						= &ay_pcb
};

ay_player_class		ay( &ay_cfg );

extern "C" {

int main ( void ) {
	ay.init();

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
