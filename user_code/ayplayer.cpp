#include "ayplayer.h"
#include "core_cm3.h"

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

int ay_player_class::fsm_step_func_rcc_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( obj );
	UNUSED( previous_step );
	return 0;
}

int ay_player_class::fsm_step_func_debug_uart_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->debug_uart->reinit();
	return 0;
}

int ay_player_class::fsm_step_func_nvic_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_EnableIRQ( USART3_IRQn );
	return 0;
}
