#pragma once

#include "mc_hardware_interfaces_wdt.h"

#include "fsm.h"

#include "ayplayer_port.h"

struct ay_player_class_config_strcut {
	wdt_base*				wdt;
	ayplayer_gpio_struct*	gpio;
	global_port_base*		gp;
};

class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) :
		wdt			( cfg->wdt ),
		gpio		( cfg->gpio ),
		gp			( cfg->gp )
	{}

	void init ( void );

	static int fsm_step_func_wdt_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
	static int fsm_step_func_gpio_init			( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );

private:
	fsm_class< ay_player_class >	fsm_init;

	wdt_base*						wdt;
	ayplayer_gpio_struct*			gpio;
	global_port_base*				gp;
};
