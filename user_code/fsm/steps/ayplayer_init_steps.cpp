#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"

extern ayplayerFreertosObjStrcut	osData;

extern const fsmStep< AyPlayer > AyPlayerBaseObjectInitFsmStep;
//extern const fsm_step< ay_player_class > ay_player_class_freertos_obj_init_fsm_step;

void AyPlayer::init ( void ) {
	/*this->fsm.relinking( &ay_player_class_wdt_init_fsm_step, this );
	this->fsm.start();
	this->fsm.relinking( &ay_player_class_freertos_obj_init_fsm_step, this );
	this->fsm.start();*/
}

void AyPlayer::start ( void ) {
	vTaskStartScheduler();
}

/*
int ay_player_class::fsm_step_func_wdt_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
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
	RCC_RESULT r;

	/// Пытаемся завестись в 120 МГц от внешнего кварца.
	r = obj->mcu->rcc->set_cfg( 0 );

	if ( r == RCC_RESULT::OK ) {
		obj->rcc_index = 0;
		return 0;
	}

	/// Если упал именно внешний кварц.
	if ( r == RCC_RESULT::ERROR_OSC_INIT ) {
		/// Пробуем от внутреннего в 120 МГц.
		r = obj->mcu->rcc->set_cfg( 1 );
		if ( r == RCC_RESULT::OK ) {
			obj->rcc_index = 1;
			return 0;
		}


		/// С PLL мертв, пытаемся стартануть от
		/// внутреннего на стандартной
		/// конфигурации без PLL.
		r = obj->mcu->rcc->set_cfg( 2 );
		if ( r == RCC_RESULT::OK ) {
			obj->rcc_index = 2;
			return 0;
		}

		return 1;		/// Что-то очень не так.
	} else {
		/// Упал PLL. Пробуем просто на внешний.
		r = obj->mcu->rcc->set_cfg( 3 );
		if ( r == RCC_RESULT::OK ) {
			obj->rcc_index = 3;
			return 0;
		}

		/// Внешний кварц тоже мертв...
		r = obj->mcu->rcc->set_cfg( 2 );
		if ( r == RCC_RESULT::OK ) {
			obj->rcc_index = 2;
			return 0;
		}

		return 1;		/// Что-то очень не так.
	}

	return 0;
}

int ay_player_class::fsm_step_func_debug_uart_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	bool r;
	r = obj->mcu->debug_uart->reinit();
	return ( r == true ) ? 0 : 1;
}

int ay_player_class::fsm_step_func_nvic_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_EnableIRQ( USART3_IRQn );
	NVIC_EnableIRQ( TIM6_DAC_IRQn );
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

int ay_player_class::fsm_step_func_adc_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	if ( obj->mcu->adc1->reinit() != true ) return 1;
	if ( obj->mcu->adc1->start_continuous_conversion() != true ) return 1;
	return 0;
}

int ay_player_class::fsm_step_func_timer_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	if ( obj->mcu->interrupt_ay->reinit( obj->rcc_index )		!= true ) return 1;
	if ( obj->mcu->ay_clk->reinit( obj->rcc_index )				!= true ) return 1;
	if ( obj->mcu->lcd_pwm->reinit( obj->rcc_index )			!= true ) return 1;
	return 0;
}

int ay_player_class::fsm_step_func_timer_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_spi_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_debug_uart_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_rcc_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_adc_falling ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_freertos_obj_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );	UNUSED( obj );

	os_data.q_ay_low[0]		= USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &os_data.qb_ay_low[0][0], &os_data.qs_ay_low[0] );
	os_data.q_ay_low[1]		= USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &os_data.qb_ay_low[1][0], &os_data.qs_ay_low[1] );
	os_data.q_ay_button		= USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( uint8_t ), os_data.qb_ay_button, &os_data.qs_ay_button );

	os_data.s_play_tic		= USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &os_data.sb_play_tic );
	os_data.s_gui_update	= USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &os_data.sb_gui_update );

	os_data.m_spi3			= USER_OS_STATIC_MUTEX_CREATE( &os_data.mb_spi3 );
	os_data.m_host			= USER_OS_STATIC_MUTEX_CREATE( &os_data.mb_host );

	USER_OS_STATIC_TASK_CREATE( ay_player_class::main_task, "main_task", TB_MAIN_TASK_SIZE, ( void* )obj, MAIN_TASK_PRIO, obj->tb_main_task, &obj->ts_main_task );

	return 0;
}

int ay_player_class::fsm_step_func_shift_register_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->pcb->sr_ay->init();
	obj->pcb->sr_button->init();
	return 0;
}

int ay_player_class::fsm_step_func_button_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	obj->pcb->button->init();
	return 0;
}
*/

