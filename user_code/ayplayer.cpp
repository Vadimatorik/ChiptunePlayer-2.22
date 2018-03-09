#include "ayplayer.h"

extern const fsm_step< ay_player_class > ay_player_class_wdt_init_fsm_step;

void ay_player_class::init ( void ) {
	this->fsm.relinking( &ay_player_class_wdt_init_fsm_step, this );
	this->fsm.start();
}

int ay_player_class::fsm_step_func_wdt_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	( void )previous_step;
	( void )obj;
	return 0;
}
