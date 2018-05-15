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

	TimerHandle_t		t;
	t = xTimerCreateStatic(	"ScrollStringName",
						500/portTICK_RATE_MS,
						pdTRUE,
						( void* )this,
						AyPlayer::scrollNameInMainWindow,
						&this->timStNameScroll	);

	xTimerStart( t, 1000 );

	vTaskStartScheduler();
}

void AyPlayer::scrollNameInMainWindow ( TimerHandle_t timer ) {
	AyPlayer* o = ( AyPlayer* )pvTimerGetTimerID( timer );
	if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
		mSlimHorizontalListScrollString( &o->g.shl );
		o->guiUpdate();
	}
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
	int					r;
	( void )r;
	while( true ) {
		USER_OS_QUEUE_RESET( o->os->qAyButton );  // Старые команды нас не интересуют.
		USER_OS_QUEUE_RECEIVE( o->os->qAyButton, &qData, portMAX_DELAY );

		b	=	static_cast< EC_BUTTON_NAME >( qData );

		if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
			if ( b == EC_BUTTON_NAME::ENTER_CLICK ) {
				switch( static_cast< uint32_t >( o->playState ) ) {
				case static_cast< uint32_t >( AYPLAYER_STATUS::STOP ):
					USER_OS_GIVE_BIN_SEMAPHORE( o->os->sStartPlay );
					break;

				case static_cast< uint32_t >( AYPLAYER_STATUS::PAUSE ):
					o->playPauseSet( true );
					o->guiUpdate();
					continue;

				case static_cast< uint32_t >( AYPLAYER_STATUS::PLAY ):
					o->playPauseSet( false );
					o->guiUpdate();
					continue;
				};
			}

			if ( b == EC_BUTTON_NAME::ENTER_LONG_PRESS ) {
				if ( ( o->playState == AYPLAYER_STATUS::PLAY ) || ( o->playState == AYPLAYER_STATUS::PAUSE ) ) {
					o->stopPlayFile();
					o->guiUpdate();
				}
				continue;
			}

			if ( b == EC_BUTTON_NAME::LEFT_CLICK ) {
				if ( o->currentFile > 0 ) {
					o->currentFile--;
					o->stopPlayFile();
					o->startPlayTrack();
					mSlimHorizontalListLeft( &o->g.shl, o->fat.currentFileInfo.fileName );
					o->guiUpdate();
				}
				continue;
			}

			if ( b == EC_BUTTON_NAME::RIGHT_CLICK ) {
				if ( o->currentFile < o->countFileInCurrentDir - 1 ) {
					o->currentFile++;
					o->stopPlayFile();
					o->startPlayTrack();
					mSlimHorizontalListRight( &o->g.shl, o->fat.currentFileInfo.fileName );
					o->guiUpdate();
				}
				continue;
			}
		}
	}
}


void AyPlayer::startPlayTrack ( void ) {
	int r;
	r = this->getFileInfoFromListCurDir( this->lType, this->currentFile );
	if ( r != 0 )
		return;

	mSlimHorizontalListSetStringCurrentItem( &this->g.shl, this->fat.currentFileInfo.fileName );
	mPlayBarSetNewTrack( &this->g.pb, this->fat.currentFileInfo.lenTick / 50 );

	USER_OS_GIVE_BIN_SEMAPHORE( this->os->sStartPlay );
}

void AyPlayer::updateLcdTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->mcu->lcdPwmTim->setDuty( o->illuminationDuty );
	while( true ) {


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
	}
}

void AyPlayer::playTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;

	int  r;
	while ( true ) {
		USER_OS_TAKE_BIN_SEMAPHORE( o->os->sStartPlay, portMAX_DELAY );
		o->playState		=	AYPLAYER_STATUS::PLAY;
		o->guiUpdate();
		r	=	o->startPlayFile();

		/// Если трек был остановлен или проблемы на аппаратном уровне.
		if ( r != 0 ) {
			o->playState		=	AYPLAYER_STATUS::STOP;
			continue;
		}

		/// Переходим на следующий трек если это был не последний.
		if ( o->currentFile < o->countFileInCurrentDir - 1 ) {
			o->currentFile++;
		} else {
			o->currentFile	=	0;
		}
		o->startPlayTrack();
	}
}
