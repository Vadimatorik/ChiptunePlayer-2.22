#include "ayplayer.h"

RCC_RESULT AyPlayer::setRccCfg ( uint32_t numberCfg ) {
	__disable_irq();

	this->mcu->wdt->resetService();
	this->offObjDependingRcc();

	RCC_RESULT r;
	r = this->mcu->rcc->setCfg( numberCfg );

	if ( r == RCC_RESULT::OK ) {
		this->rccIndex = numberCfg;
		reinitObjDependingRcc();
		SysTick_Config( SystemCoreClock / 1000 );
	}

	__enable_irq();
	return r;
}

void AyPlayer::offObjDependingRcc ( void ) {
	/// Таймеры.
	this->mcu->ayClkTim->off();
	this->mcu->lcdPwmTim->off();
	this->mcu->interruptAyTim->off();

	/// Время в задачах.
#ifdef configGENERATE_RUN_TIME_STATS
	this->mcu->timRunTimeStats->off();
#endif

	/// Аналого-цифровые преобразователи.
	this->mcu->adc1->stopContinuousConversion();

	/// SPI.
	this->mcu->spi1->off();
	this->mcu->spi2->off();
	this->mcu->spi3->off();

	/// UART.
	this->mcu->debugUart->off();
}

void AyPlayer::reinitObjDependingRcc ( void ) {
	/// Таймеры.
	this->mcu->ayClkTim->reinit( this->rccIndex );
	this->mcu->lcdPwmTim->reinit( this->rccIndex );
	this->mcu->interruptAyTim->reinit( this->rccIndex );

#ifdef configGENERATE_RUN_TIME_STATS
	this->mcu->timRunTimeStats->reinit( this->rccIndex );
	this->mcu->timRunTimeStats->on();
#endif

	/// Аналого-цифровые преобразователи.
	this->mcu->adc1->reinit( this->rccIndex );

	/// SPI.
	this->mcu->spi1->reinit( 0 );
	this->mcu->spi1->setPrescaler( this->rccIndex );

	this->mcu->spi2->reinit( 0 );
	this->mcu->spi2->setPrescaler( this->rccIndex );

	this->mcu->spi3->reinit( 0 );
	this->mcu->spi3->setPrescaler( this->rccIndex );

	/// UART всегда с одной скоростью.
	this->mcu->debugUart->reinit( 0 );
}

void AyPlayer::startBaseInterfaces ( void ) {
	BASE_RESULT	r;
	r = this->mcu->adc1->startContinuousConversion();
	assertParam( r == BASE_RESULT::OK );
	r = this->mcu->debugUart->on();
	assertParam( r == BASE_RESULT::OK );
	r = this->mcu->spi1->on();
	assertParam( r == BASE_RESULT::OK );
	r = this->mcu->spi2->on();
	assertParam( r == BASE_RESULT::OK );
	r = this->mcu->spi3->on();
	assertParam( r == BASE_RESULT::OK );
}

void AyPlayer::start ( void ) {
	USER_OS_STATIC_TASK_CREATE( AyPlayer::mainTask, "main", TB_MAIN_TASK_SIZE, ( void* )this, MAIN_TASK_PRIO, this->tbMainask, &this->tsMainTask );
	vTaskStartScheduler();
}

void AyPlayer::rccMaxFrequancyInit ( void ) {
	RCC_RESULT	rccRes;

	/// Пытаемся завестись в 120 МГц от внешнего кварца.
	rccRes = this->setRccCfg( 0 );

	if ( rccRes == RCC_RESULT::OK ) {
		this->rccIndex = 0;
		return;
	}

	/// Если упал именно внешний кварц.
	if ( rccRes == RCC_RESULT::ERROR_OSC_INIT ) {
		/// Пробуем от внутреннего в 120 МГц.
		rccRes = this->setRccCfg( 1 );
		if ( rccRes == RCC_RESULT::OK ) {
			this->rccIndex = 1;
			return;
		}


		/// С PLL мертв, пытаемся стартануть от
		/// внутреннего на стандартной
		/// конфигурации без PLL.
		rccRes = this->setRccCfg( 2 );
		if ( rccRes == RCC_RESULT::OK ) {
			this->rccIndex = 2;
			return;
		}

		return;		/// Что-то очень не так.
	} else {
		/// Упал PLL. Пробуем просто на внешний.
		rccRes = this->setRccCfg( 3 );
		if ( rccRes == RCC_RESULT::OK ) {
			this->rccIndex = 3;
			return;
		}

		/// Внешний кварц тоже мертв...
		rccRes = this->setRccCfg( 2 );
		if ( rccRes == RCC_RESULT::OK ) {
			this->rccIndex = 2;
			return;
		}

		assertParam( false );
	}
}

uint32_t AyPlayer::checkSd ( AY_MICROSD sd ) {
	( void )sd;
	/// Карта есть...
	return 0;
}

void AyPlayer::waitSdCardInsert ( void ) {
	bool flagMicroSd1Present = true;
	bool flagMicroSd2Present = true;

	do {
		if ( this->checkSd( AY_MICROSD::SD1 ) ) {
			this->l->sendMessage( RTL_TYPE_M::RUN_MESSAGE_OK, "SD1 is detected!" );
			flagMicroSd1Present = true;
		} else {
			this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD1 missing!" );

			const char SD1_NOT_PRESENT[]	=	"SD1 not present!";

			/// Если ранее предполагалось, что карта на месте.
			if ( flagMicroSd1Present == true ) {
				m_create_message_window(	&this->g.mw,
											&this->g.c,
											mp_rel( 9, 10, 108, 44 ),
											( char* )SD1_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();
			}

			flagMicroSd1Present = false;
			vTaskDelay( 100 );
			continue;
		}

		if ( this->checkSd( AY_MICROSD::SD2 ) ) {
			this->l->sendMessage( RTL_TYPE_M::RUN_MESSAGE_OK, "SD2 is detected!" );

			const char SD2_NOT_PRESENT[]	=	"SD2 not present!";

			/// Если ранее предполагалось, что карта на месте.
			if ( flagMicroSd2Present == true ) {
				m_create_message_window(	&this->g.mw,
											&this->g.c,
											mp_rel( 9, 10, 108, 44 ),
											( char* )SD2_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();
			}

			flagMicroSd2Present = true;
		} else {
			this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" );

			flagMicroSd2Present = false;
			vTaskDelay( 100 );
			continue;
		}
	} while( flagMicroSd1Present && flagMicroSd2Present );
}

// Перерисовывает GUI и обновляет экран.
void AyPlayer::guiUpdate ( void ) {
    USER_OS_TAKE_MUTEX( this->os->mHost, portMAX_DELAY );
    this->pcb->lcd->bufClear();
    makise_g_host_call( &this->g.h, M_G_CALL_PREDRAW );
    makise_g_host_call( &this->g.h, M_G_CALL_DRAW );
    this->pcb->lcd->update();
    USER_OS_GIVE_BIN_SEMAPHORE( this->os->sGuiUpdate );
    USER_OS_GIVE_MUTEX( this->os->mHost );
}

extern const fsmStep< AyPlayer > ayPlayerFreeRtosObjInitFsmStep;

void AyPlayer::mainTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->fsm.start( &ayPlayerFreeRtosObjInitFsmStep, o );
	while( true ) {
		vTaskDelay( 1000 );
	}
}
