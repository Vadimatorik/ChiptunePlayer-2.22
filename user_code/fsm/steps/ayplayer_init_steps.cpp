#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"

void AyPlayer::start ( void ) {
	USER_OS_STATIC_TASK_CREATE( AyPlayer::mainTask, "main", TB_MAIN_TASK_SIZE, ( void* )this, MAIN_TASK_PRIO, this->tbMainask, &this->tsMainTask );
	vTaskStartScheduler();
}

int AyPlayer::fsmStepFuncHardwareMcInit ( HANDLER_FSM_INPUT_DATA ) {
	BASE_RESULT r;

	/*!
	 * WDT init.
	 */
	r = obj->mcu->wdt->reinit( 0 );
	assertParam( r == BASE_RESULT::OK );

	/*!
	 * GPIO init.
	 */
	///
	r = obj->mcu->gp->reinitAllPorts();
	assertParam( r == BASE_RESULT::OK );

	/*!
	 * RCC и все объекты, зависящие от него.
	 */
	RCC_RESULT	rccRes;

	/// Пытаемся завестись в 120 МГц от внешнего кварца.
	rccRes = obj->setRccCfg( 0 );

	if ( rccRes == RCC_RESULT::OK ) {
		obj->rccIndex = 0;
		return 0;
	}

	/// Если упал именно внешний кварц.
	if ( rccRes == RCC_RESULT::ERROR_OSC_INIT ) {
		/// Пробуем от внутреннего в 120 МГц.
		rccRes = obj->setRccCfg( 1 );
		if ( rccRes == RCC_RESULT::OK ) {
			obj->rccIndex = 1;
			return 0;
		}


		/// С PLL мертв, пытаемся стартануть от
		/// внутреннего на стандартной
		/// конфигурации без PLL.
		rccRes = obj->setRccCfg( 2 );
		if ( rccRes == RCC_RESULT::OK ) {
			obj->rccIndex = 2;
			return 0;
		}

		return 1;		/// Что-то очень не так.
	} else {
		/// Упал PLL. Пробуем просто на внешний.
		rccRes = obj->setRccCfg( 3 );
		if ( rccRes == RCC_RESULT::OK ) {
			obj->rccIndex = 3;
			return 0;
		}

		/// Внешний кварц тоже мертв...
		rccRes = obj->setRccCfg( 2 );
		if ( rccRes == RCC_RESULT::OK ) {
			obj->rccIndex = 2;
			return 0;
		}

		assertParam( false );
	}

	return 0;
}

int AyPlayer::fsmStepFuncFreeRtosObjInit ( HANDLER_FSM_INPUT_DATA ) {
	obj->os->qAyLow[0]		= USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ayLowOutDataStruct ), &obj->os->qbAyLow[0][0], &obj->os->qsAyLow[0] );
	obj->os->qAyLow[1]		= USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ayLowOutDataStruct ), &obj->os->qbAyLow[1][0], &obj->os->qsAyLow[1] );
	obj->os->qAyButton		= USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( uint8_t ), obj->os->qbAyButton, &obj->os->qsAyButton );

	obj->os->sPlayTic		= USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &obj->os->sbPlayTic );
	obj->os->sGuiUpdate		= USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &obj->os->sbGuiUpdate );

	obj->os->mSpi3			= USER_OS_STATIC_MUTEX_CREATE( &obj->os->mbSpi3 );
	obj->os->mHost			= USER_OS_STATIC_MUTEX_CREATE( &obj->os->mbHost );

	return 0;
}


/*
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
	if ( obj->mcu->interrupt_ay->reinit( obj->rccIndex )		!= true ) return 1;
	if ( obj->mcu->ay_clk->reinit( obj->rccIndex )				!= true ) return 1;
	if ( obj->mcu->lcd_pwm->reinit( obj->rccIndex )			!= true ) return 1;
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

