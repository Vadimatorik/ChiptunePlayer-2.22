#include "ayplayer.h"

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
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::illuminationControl,
								"led",
								TB_ILLUMINATION_CONTROL_TASK_SIZE,
								( void* )this,
								ILLUMINATION_CONTROL_TASK_PRIO,
								this->tbIlluminationControlTask,
								&this->tsIlluminationControlTask );

	/*!
	 * Проигрывание трека.
	 */

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

void AyPlayer::illuminationControl ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->mcu->lcdPwmTim->setDuty( o->illuminationDuty );
	while( true ) {
		o->mcu->lcdPwmTim->on();
		vTaskDelay( 1000 );
	}
}

void AyPlayer::playTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
/*
    char* name;
    EC_AY_FILE_MODE_ANSWER  r;
    while ( true ) {
        USER_OS_QUEUE_RECEIVE( ayplayer_play_queue, &name, portMAX_DELAY );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::PLAY );
        r = ay_file_mode.psg_file_play( name, 1 );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::STOP );

        // Переходим на следующий трек.
        if ( r == EC_AY_FILE_MODE_ANSWER::TRACK_END ) {
            m_click_play_list( &gui_pl, M_KEY_DOWN );
            m_click_play_list( &gui_pl, M_KEY_OK );
            gui_update();
        }
    }*/
	(void)o;
	while(1) {
		vTaskDelay(1000);
	}
}
