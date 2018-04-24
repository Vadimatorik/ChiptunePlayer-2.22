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
	this->mcu->spi1->reinit( this->rccIndex );
	this->mcu->spi2->reinit( this->rccIndex );
	this->mcu->spi3->reinit( this->rccIndex );

	/// UART.
	this->mcu->debugUart->reinit( this->rccIndex );
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

extern const fsmStep< AyPlayer > ayPlayerHardwareMcInitFsmStep;

void AyPlayer::mainTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->fsm.relinking( &ayPlayerHardwareMcInitFsmStep, o );
	o->fsm.start();
	while( true ) {
		vTaskDelay( 1000 );
	}
}
