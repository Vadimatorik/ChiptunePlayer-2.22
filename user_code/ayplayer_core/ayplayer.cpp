#include "ayplayer.h"
#include "ayplayer_button.h"

extern const fsmStep< AyPlayer > ayPlayerFreeRtosObjInitFsmStep;
extern const fsmStep< AyPlayer > ayPlayerMicroSdInitFsmStep;

void AyPlayer::start ( void ) {
	/*!
	 * Основной поток проекта.
	 */
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::mainTask,
								"main",
								TB_MAIN_TASK_SIZE,
								( void* )this,
								MAIN_TASK_PRIO,
								this->tbMainTask,
								&this->tsMainTask );

	/*!
	 * Контроль подсветки экрана.
	 */
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::illuminationControlTask,
								"illuminationControl",
								TB_ILLUMINATION_CONTROL_TASK_SIZE,
								( void* )this,
								ILLUMINATION_CONTROL_TASK_PRIO,
								this->tbIlluminationControlTask,
								&this->tsIlluminationControlTask	);

	/// Обработка нажатой клавиши.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::buttonClickHandlerTask,
								"buttonClickHandler",
								TB_BUTTON_CLICK_HANDLER_TASK_SIZE,
								( void* )this,
								BUTTON_CLICK_HANDLER_TASK_PRIO,
								this->tbButtonClickHandlerTask,
								&this->tsButtonClickHandlerTask	);

	/// Фоновое обновление экрана.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::updateLcdTask,
									"updateLcd",
									TB_UPDATE_LCD_TASK_SIZE,
									( void* )this,
									BUTTON_UPDATE_LCD_TASK_PRIO,
									this->tbUpdateLcdTask,
									&this->tsUpdateLcdTask	);

	/// Воспроизведение трека.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::playTask,
								"play",
								TB_PLAY_TASK_SIZE,
								( void* )this,
								PLAY_TASK_PRIO,
								this->tbPlayTask,
								&this->tsPlayTask	);

	/// Обновление плей-бара при прохождении секунды.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::playTickHandlerTask,
								"playTick",
								TB_PLAY_TICK_TASK_SIZE,
								( void* )this,
								PLAY_TICK_TASK_PRIO,
								this->tbPlayTickTask,
								&this->tsPlayTickTask	);

	vTaskStartScheduler();
}


void AyPlayer::mainTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->fsm.start( &ayPlayerFreeRtosObjInitFsmStep, o );
	o->fsm.start( &ayPlayerMicroSdInitFsmStep, o );
	while( true ) {
		vTaskDelay( 1000 );
	}
}

void AyPlayer::illuminationControlTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->mcu->lcdPwmTim->setDuty( o->illuminationDuty );
	while( true ) {
		o->mcu->lcdPwmTim->on();
		vTaskDelay( 1000 );
	}
}

void AyPlayer::buttonClickHandlerTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;

	EC_BUTTON_NAME		b;
	uint8_t				qData;
	while( true ) {
		USER_OS_QUEUE_RESET( o->os->qAyButton );  // Старые команды нас не интересуют.
		USER_OS_QUEUE_RECEIVE( o->os->qAyButton, &qData, portMAX_DELAY );

		b	=	static_cast< EC_BUTTON_NAME >( qData );

		if ( b == EC_BUTTON_NAME::ENTER ) {
			if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
				USER_OS_GIVE_BIN_SEMAPHORE( o->os->sStartPlay );
			}
		}
	}
}

void AyPlayer::updateLcdTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->mcu->lcdPwmTim->setDuty( o->illuminationDuty );
	while( true ) {
		if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
			mScrollStringScroll( &o->g.ss );
		}

		if ( USER_OS_TAKE_BIN_SEMAPHORE( o->os->sGuiUpdate, 1000 ) == pdFALSE ) {
			o->guiUpdate();
		}
	}
}

void AyPlayer::playTickHandlerTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	while ( true ) {
		USER_OS_TAKE_BIN_SEMAPHORE( o->os->sPlayTic, portMAX_DELAY );
		mPlayBarIncSec( &o->g.pb );

		if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
			mScrollStringScroll( &o->g.ss );
		}
	}
}

void AyPlayer::playTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;

	int  r;
	while ( true ) {
		USER_OS_TAKE_BIN_SEMAPHORE( o->os->sStartPlay, portMAX_DELAY );
		o->playState		=	AYPLAYER_STATUS::PLAY;
		r	=	o->startPlayFile();
		o->playState		=	AYPLAYER_STATUS::STOP;

		// Переходим на следующий трек если это был не последний..
		if ( r == 0 ) {
			//m_click_play_list( &gui_pl, M_KEY_DOWN );
			//..m_click_play_list( &gui_pl, M_KEY_OK );
			//gui_update();
		}
	}
}
