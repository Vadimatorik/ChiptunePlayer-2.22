#pragma once

#include "fsm.h"
#include "mc_hardware_interfaces_wdt.h"

struct ay_player_class_config_strcut {
	wdt_base*				wdt;
};

class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) : wdt( cfg->wdt ) {}

	void init ( void );

	static int fsm_step_func_wdt_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj );
private:
	fsm_class< ay_player_class >	fsm;

	wdt_base*						wdt;
};
