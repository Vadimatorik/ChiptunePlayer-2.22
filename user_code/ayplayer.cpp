#include "ayplayer.h"

extern const fsm_step< ay_player_class > ay_player_class_wdt_init_fsm_step;

void ay_player_class::init ( void ) {
	this->fsm_init.relinking( &ay_player_class_wdt_init_fsm_step, this );
	this->fsm_init.start();
}

int ay_player_class::fsm_step_func_wdt_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->wdt->init();
	return 0;
}

int ay_player_class::fsm_step_func_gpio_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->gp->reinit_all_ports();
	return 0;
}
