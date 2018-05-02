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

uint32_t AyPlayer::getRccMode ( void ) {
	return this->rccIndex;
}
