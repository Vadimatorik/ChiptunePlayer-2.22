#pragma once

#include "fsm.h"
#include "wdt.h"
#include "uart.h"
#include "ayplayer_port.h"

struct ay_player_class_config_strcut {
	wdt_base*				wdt;
	ayplayer_gpio_struct*	gpio;
	global_port_base*		gp;
	uart_base*				debug_uart;
};

class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) :
		wdt			( cfg->wdt ),
		gpio		( cfg->gpio ),
		gp			( cfg->gp ),
		debug_uart	( cfg->debug_uart )
	{}

	void init ( void );

	static int fsm_step_func_wdt_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
	static int fsm_step_func_gpio_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
	static int fsm_step_func_rcc_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
	static int fsm_step_func_debug_uart_init	( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
	static int fsm_step_func_nvic_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );

private:
	fsm_class< ay_player_class >	fsm_init;

	wdt_base*						wdt;
	ayplayer_gpio_struct*			gpio;
	global_port_base*				gp;
	uart_base*						debug_uart;
};
