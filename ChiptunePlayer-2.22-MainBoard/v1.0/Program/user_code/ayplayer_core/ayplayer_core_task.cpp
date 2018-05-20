#include "ayplayer.h"
#include "ayplayer_button.h"

extern "C" {

extern MHost				makiseHost;

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

		/*!
		 * Основное окно.
		 */
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
					mSlimHorizontalListLeft( o->g.shl, o->fat.currentFileInfo.fileName );
					o->guiUpdate();
				}
				continue;
			}

			if ( b == EC_BUTTON_NAME::RIGHT_CLICK ) {
				if ( o->currentFile < o->countFileInCurrentDir - 1 ) {
					o->currentFile++;
					o->stopPlayFile();
					o->startPlayTrack();
					mSlimHorizontalListRight( o->g.shl, o->fat.currentFileInfo.fileName );
					o->guiUpdate();
				}
				continue;
			}

			/// Переход в эквалайзер.
			if ( b == EC_BUTTON_NAME::DOWN_CLICK ) {
				o->removePlayWindow();									/// Закрываем текущее окно.
				o->wNow = AYPLAYER_WINDOW_NOW::EQUALIZER;				/// Говорим что следующее будет эквалайзер.
				o->initEqualizerWindow();
				o->guiUpdate();
				continue;
			}
		}

		/*!
		 * Окно эквалайзера.
		 */
		if ( o->wNow == AYPLAYER_WINDOW_NOW::EQUALIZER ) {
			if ( ( b == EC_BUTTON_NAME::BACK_LONG_CLICK ) ||
				 ( b == EC_BUTTON_NAME::BACK_CLICK ) ) {
				o->removeEqualizerWindow();
				o->wNow = AYPLAYER_WINDOW_NOW::MAIN;
				o->initPlayWindow();
				o->guiUpdate();
				continue;
			}

			if ( ( b == EC_BUTTON_NAME::LEFT_LONG_CLICK ) ||
				 ( b == EC_BUTTON_NAME::LEFT_CLICK ) ) {

				o->g.currentSlider--;
				if ( o->g.currentSlider < 0 )
					o->g.currentSlider	=	5;

				mi_focus_prev( &makiseHost );
				o->guiUpdate();
				continue;
			}

			if ( ( b == EC_BUTTON_NAME::RIGHT_LONG_CLICK ) ||
				 ( b == EC_BUTTON_NAME::RIGHT_CLICK ) ) {

				o->g.currentSlider++;
				if ( o->g.currentSlider == 6)
					o->g.currentSlider	=	0;

				mi_focus_next( &makiseHost );
				o->guiUpdate();
				continue;
			}

			if ( ( b == EC_BUTTON_NAME::DOWN_CLICK ) ||
				 ( b == EC_BUTTON_NAME::DOWN_LONG_CLICK ) ) {
				uint8_t* value;
				value = &o->eq.A1;

				if ( value[ o->g.currentSlider ] > 0 ) {
					int b = value[ o->g.currentSlider ] - 10;
					if ( b < 0 ) {
						value[ o->g.currentSlider ] = 0;
					} else {
						value[ o->g.currentSlider ] = static_cast< uint8_t >( b );
					}
				}

				m_slider_set_value(	o->g.sliders[ o->g.currentSlider ],
									value[ o->g.currentSlider ] );

				o->setValueEqualizer();

				o->guiUpdate();
				continue;
			}

			if ( ( b == EC_BUTTON_NAME::UP_CLICK ) ||
				 ( b == EC_BUTTON_NAME::UP_LONG_CLICK ) ) {
				uint8_t* value;
				value = &o->eq.A1;

				if ( value[ o->g.currentSlider ] < 0xFF ) {
					int b = value[ o->g.currentSlider ] + 10;
					if ( b > 0xFF ) {
						value[ o->g.currentSlider ] = 0xFF;
					} else {
						value[ o->g.currentSlider ] = static_cast< uint8_t >( b );
					}
				}

				m_slider_set_value(	o->g.sliders[ o->g.currentSlider ],
									value[ o->g.currentSlider ] );

				o->setValueEqualizer();

				o->guiUpdate();
				continue;
			}
		}
	}
}

void AyPlayer::playTickHandlerTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	while ( true ) {
		USER_OS_TAKE_BIN_SEMAPHORE( o->os->sPlayTic, portMAX_DELAY );

		/// Обновляем только если в основном окне.
		if ( o->wNow == AYPLAYER_WINDOW_NOW::MAIN ) {
			mPlayBarIncSec( o->g.pb );
		}
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

extern const fsmStep< AyPlayer > ayPlayerFreeRtosObjInitFsmStep;
extern const fsmStep< AyPlayer > ayPlayerMicroSdInitFsmStep;

/// Для отслеживания клавиш качельки громкости.
#define INC_AND_DEC_STABIL_TIME  			    	100
#define OFF_WAIT_TIME             				   	3000
#define PERIOD_DETECT_PRESS_BUTTON_INC_DEC			10

/*!
 * Основная задача в начале производит
 * инициализацию устройства по деревьям, после чего
 * ждет разряда аккумулятора или выключения кнопками.
 */
void AyPlayer::mainTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->fsm.start( &ayPlayerFreeRtosObjInitFsmStep, o );
	o->fsm.start( &ayPlayerMicroSdInitFsmStep, o );

	/// Счетчики отсчета времени.
	int32_t incStabilTime	= INC_AND_DEC_STABIL_TIME;
	int32_t decStabilTime	= INC_AND_DEC_STABIL_TIME;
	int32_t offTime			= OFF_WAIT_TIME;

	/// Флаги факта нажатия.
	bool incF = false;
	bool decF = false;

	while ( true ) {
		USER_OS_DELAY_MS( PERIOD_DETECT_PRESS_BUTTON_INC_DEC );

		/// Состояние клавиш.
		incF = o->mcu->gpio->vr.inc->read();
		decF = o->mcu->gpio->vr.dec->read();

		/// Обе зажатые клавиши - старт отсчета времени нажатия для отключения.
		if ( ( incF == false ) && ( decF == false ) ) {
			if ( offTime > 0 ) {
				offTime -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
			} else {
				o->powerOff( CAUSE_SHUTDOWN::USER_OFF );
			}
		} else {
			offTime = OFF_WAIT_TIME;
		}

		/// +.
		if ( incF == false ) {
			if ( incStabilTime > 0 ) incStabilTime -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
		} else {
			if ( incStabilTime == 0 ) {
				if ( o->currentVolumeIndex < 15 )
					o->currentVolumeIndex++;
				incStabilTime = INC_AND_DEC_STABIL_TIME;

				/*!
				 * Сопротивление потенциометров меняем только если идет воспроизвдеение или
				 * пауза, поскольку при старне трека с начала значение потенциометров нарастает плавно во
				 * избежание стука.
				 */
				if ( (	o->playState == AYPLAYER_STATUS::PLAY ) ||
						o->playState == AYPLAYER_STATUS::PAUSE	) {
					o->volumeSet( o->volumeTable[ o->currentVolumeIndex ], o->volumeTable[ o->currentVolumeIndex ] );
				}

				continue;
				}
			}

		/// -.
		if ( decF == false ) {
			if ( decStabilTime > 0 ) decStabilTime -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
		} else {
			if ( decStabilTime == 0 ) {
				if ( o->currentVolumeIndex > 0 )
					o->currentVolumeIndex--;
				decStabilTime = INC_AND_DEC_STABIL_TIME;

				if ( (	o->playState == AYPLAYER_STATUS::PLAY ) ||
						o->playState == AYPLAYER_STATUS::PAUSE	) {
					o->volumeSet( o->volumeTable[ o->currentVolumeIndex ], o->volumeTable[ o->currentVolumeIndex ] );
				}

				continue;
			}
		}



	}
}
