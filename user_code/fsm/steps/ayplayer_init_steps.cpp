#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"

int AyPlayer::fsmStepFuncHardwareMcInit ( HANDLER_FSM_INPUT_DATA ) {
	BASE_RESULT r;

	/*!
	 * WDT init.
	 */
	//r = obj->mcu->wdt->reinit( 0 );
	//assertParam( r == BASE_RESULT::OK );

	obj->mcu->pwr->reinit( 0 );

	/*!
	 * GPIO init.
	 */
	///
	r = obj->mcu->gp->reinitAllPorts();
	assertParam( r == BASE_RESULT::OK );

	/// Фиксируем питание.
	obj->mcu->gpio->pwr.all_pwr->reset();

	/*!
	 * RCC и все объекты, зависящие от него.
	 */
	obj->rccMaxFrequancyInit();

	/*!
	 * NVIC.
	 */
	NVIC_SetPriority( DMA1_Stream3_IRQn, 10 );
	NVIC_SetPriority( DMA1_Stream4_IRQn, 10 );
	NVIC_SetPriority( DMA1_Stream7_IRQn, 5 );				/// Выдача в AY (сдвиговый регистр).
	NVIC_SetPriority( DMA2_Stream5_IRQn, 10 );
	NVIC_SetPriority( DMA2_Stream6_IRQn, 10 );

	NVIC_SetPriority( USART3_IRQn, 10 );

	NVIC_SetPriority( PVD_IRQn, 10 );

	/// Выдача семафора задаче обновления AY регистров.
	NVIC_SetPriority( TIM6_DAC_IRQn, 5 );

	NVIC_EnableIRQ( DMA1_Stream3_IRQn );
	NVIC_EnableIRQ( DMA1_Stream4_IRQn );
	NVIC_EnableIRQ( DMA1_Stream7_IRQn );
	NVIC_EnableIRQ( DMA2_Stream5_IRQn );
	NVIC_EnableIRQ( DMA2_Stream6_IRQn );

	NVIC_EnableIRQ( USART3_IRQn );

	NVIC_EnableIRQ( PVD_IRQn );

	NVIC_EnableIRQ( TIM6_DAC_IRQn );

	/*!
	 * После инициализации запускаем все модули,
	 * которые должны всегда находиться в работе.
	 */
	obj->startBaseInterfaces();
	return 0;
}

int AyPlayer::fsmStepFuncFreeRtosObjInit ( HANDLER_FSM_INPUT_DATA ) {
	obj->os->qAyLow[0]		=	USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ayLowOutDataStruct ), &obj->os->qbAyLow[0][0], &obj->os->qsAyLow[0] );
	obj->os->qAyLow[1]		=	USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ayLowOutDataStruct ), &obj->os->qbAyLow[1][0], &obj->os->qsAyLow[1] );
	obj->os->qAyButton		=	USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( uint8_t ), obj->os->qbAyButton, &obj->os->qsAyButton );

	obj->os->sPlayTic		=	USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &obj->os->sbPlayTic );
	obj->os->sStartPlay		=	USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &obj->os->sbStartPlay );

	obj->os->mSpi3			=	USER_OS_STATIC_MUTEX_CREATE( &obj->os->mbSpi3 );
	obj->os->mHost			=	USER_OS_STATIC_MUTEX_CREATE( &obj->os->mbHost );

	return 0;
}

int AyPlayer::fsmStepFuncHardwarePcbInit ( HANDLER_FSM_INPUT_DATA ) {
	/// У ay, srButton и button одинаковая инициализация.
	/// Поэтому только 1 вызываем.
	obj->pcb->srAy->init();
	obj->pcb->ay->init();

	/// Опрос клавиатуры.
	obj->pcb->button->init();

	return 0;
}

extern "C" {

extern MHost				makiseHost;
extern MakiseGUI			makiseGui;
extern MakiseDriver			makiseGuiDriver;

uint32_t*	makiseGuiGetBuffer			( uint32_t size );
void		makiseGuiPredraw			( MakiseGUI* gui );
void		makiseGuiDraw				( MakiseGUI* gui );
MInputData	makiseGuiInpHandler			( MInputData d, MInputResultEnum res );
void		makiseGuiUpdate				( MakiseGUI* gui );

}

extern ST7565		lcd;

int AyPlayer::fsmStepFuncGuiInit ( HANDLER_FSM_INPUT_DATA ) {
	makise_gui_autoinit(	&makiseHost,
							&makiseGui,
							&makiseGuiDriver,
							makiseGuiGetBuffer,
							makiseGuiInpHandler,
							makiseGuiDraw,
							makiseGuiPredraw,
							makiseGuiUpdate		);

	/// Статус бар всегда показывается.
	obj->initGuiStatusBar();

	if ( lcd.reset()			!= BASE_RESULT::OK ) return M_ERROR;
	if ( lcd.setContrast( 8 )	!= BASE_RESULT::OK ) return M_ERROR;
	if ( lcd.clear()			!= BASE_RESULT::OK ) return M_ERROR;
	if ( lcd.on()				!= BASE_RESULT::OK ) return M_ERROR;



	obj->l->sendMessage( RTL_TYPE_M::INIT_OK, "MakiseGui started." );

	return 0;
}

