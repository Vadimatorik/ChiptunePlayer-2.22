#include "ayplayer.h"
#include "core_cm3.h"

extern const fsm_step< ay_player_class > ay_player_class_wdt_init_fsm_step;

void ay_player_class::init ( void ) {
	this->fsm_init.relinking( &ay_player_class_wdt_init_fsm_step, this );
	this->fsm_init.start();
}

int ay_player_class::fsm_step_func_wdt_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->mcu->wdt->init();
	return 0;
}

int ay_player_class::fsm_step_func_gpio_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->mcu->gp->reinit_all_ports();
	return 0;
}

int ay_player_class::fsm_step_func_rcc_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->mcu->rcc->set_cfg( 0 );
	return 0;
}

int ay_player_class::fsm_step_func_debug_uart_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	RCC_RESULT r;
	/// Пытаемся завестись в 120 МГц от внешнего кварца.
	r = obj->mcu->rcc->set_cfg( 0 );
	if ( r == RCC_RESULT::OK ) return 0;

	/// Если упал именно внешний кварц.
	if ( r == RCC_RESULT::ERROR_OSC_INIT ) {
		/// Пробуем от внутреннего в 120 МГц.
		r = obj->mcu->rcc->set_cfg( 1 );
		if ( r == RCC_RESULT::OK ) return 0;

		/// С PLL мертв, пытаемся стартануть от
		/// внутреннего на стандартной
		/// конфигурации без PLL.
		r = obj->mcu->rcc->set_cfg( 2 );
		if ( r == RCC_RESULT::OK ) return 0;
		return 1;		/// Что-то очень не так.
	} else {
		/// Упал PLL. Пробуем просто на внешний.
		r = obj->mcu->rcc->set_cfg( 3 );
		if ( r == RCC_RESULT::OK ) return 0;

		/// Внешний кварц тоже мертв...
		r = obj->mcu->rcc->set_cfg( 2 );
		if ( r == RCC_RESULT::OK ) return 0;
		return 1;		/// Что-то очень не так.
	}
}

int ay_player_class::fsm_step_func_rcc_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}


int ay_player_class::fsm_step_func_nvic_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_EnableIRQ( USART3_IRQn );
	return 0;
}

int ay_player_class::fsm_step_func_spi_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );

	if ( obj->mcu->spi1->reinit() != BASE_RESULT::OK ) return 1;
	if ( obj->mcu->spi2->reinit() != BASE_RESULT::OK ) return 1;
	if ( obj->mcu->spi3->reinit() != BASE_RESULT::OK ) return 1;
	obj->mcu->spi1->on();
	obj->mcu->spi2->on();
	obj->mcu->spi3->on();

	return 0;
}
