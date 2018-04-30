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

	/*!
	 * RCC и все объекты, зависящие от него.
	 */
	obj->rccMaxFrequancyInit();

	/*!
	 * NVIC.
	 */
	NVIC_SetPriority( DMA1_Stream3_IRQn, 10 );
	NVIC_SetPriority( DMA1_Stream4_IRQn, 10 );
	NVIC_SetPriority( DMA1_Stream7_IRQn, 10 );
	NVIC_SetPriority( DMA2_Stream5_IRQn, 10 );
	NVIC_SetPriority( DMA2_Stream6_IRQn, 10 );

	NVIC_SetPriority( USART3_IRQn, 10 );

	NVIC_SetPriority( PVD_IRQn, 10 );

	NVIC_EnableIRQ( DMA1_Stream3_IRQn );
	NVIC_EnableIRQ( DMA1_Stream4_IRQn );
	NVIC_EnableIRQ( DMA1_Stream7_IRQn );
	NVIC_EnableIRQ( DMA2_Stream5_IRQn );
	NVIC_EnableIRQ( DMA2_Stream6_IRQn );

	NVIC_EnableIRQ( USART3_IRQn );

	NVIC_EnableIRQ( PVD_IRQn );

	/*!
	 * После инициализации запускаем все модули,
	 * которые должны всегда находиться в работе.
	 */
	obj->startBaseInterfaces();
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

int AyPlayer::fsmStepFuncHardwarePcbInit ( HANDLER_FSM_INPUT_DATA ) {
	/// У ay, srButton и button одинаковая инициализация.
	/// Поэтому только 1 вызываем.
	obj->pcb->srAy->init();
	obj->pcb->ay->init();

	return 0;
}

extern "C" {
extern const MakiseGUI mGui;
}

int AyPlayer::fsmStepFuncGuiInit ( HANDLER_FSM_INPUT_DATA ) {
	obj->g.c.gui						= ( MakiseGUI* )&mGui;
	obj->g.h.host						= &obj->g.c;
	obj->g.h.host->gui					= ( MakiseGUI* )&mGui;

	int r;
	r = makise_start( obj->g.h.host->gui );

	/// Статус бар всегда показывается.
	obj->initGuiStatusBar();

	assertParam( r == M_OK );

	obj->l->sendMessage( RTL_TYPE_M::INIT_OK, "MakiseGui started." );

	return 0;
}

int AyPlayer::fsmStepFuncMicroSdInit ( HANDLER_FSM_INPUT_DATA ) {
	/*!
	 * Ждем валидную карту.
	 */
	do {
		obj->waitSdCardInsert();

		if ( obj->fatFsReinit( AY_MICROSD::SD1 ) != FRESULT::FR_OK ) {
			obj->waitSdCardDisconnect( AY_MICROSD::SD1 );
			continue;
		}

		if ( obj->fatFsReinit( AY_MICROSD::SD2 ) != FRESULT::FR_OK ) {
			obj->waitSdCardDisconnect( AY_MICROSD::SD2 );
			continue;
		}

		break;
	} while( true );

	return 0;
}
/*
int AyPlayer::fsmStepFuncIndexingSupportedFiles ( HANDLER_FSM_INPUT_DATA ) {
	FRESULT r;

	char path[] = "0:/playlist.sys";
	FILINFO		fi;

	r = f_stat( path, &fi );
	switch( ( uint32_t )r ) {
	case FR_OK:
		obj->l->sendMessage( RTL_TYPE_M::INIT_OK, "The <<0:/playlist.sys>> file exists!" );
		return 0;

	case FR_NO_FILE:
		obj->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "The <<0:/playlist.sys>> file not exists!" );
		return 1;

	default:

		while(1);
		return 2;
	}
}*/


int AyPlayer::fsmStepFuncIndexingSupportedFiles ( HANDLER_FSM_INPUT_DATA ) {
	char*			path		=	( char* )pvPortMalloc( 4096 );
	assertParam( path );
	strcpy( path, "0:");

	obj->l->sendMessage( RTL_TYPE_M::INIT_OK, "Indexing files start." );
	obj->initWindowIndexingSupportedFiles();
	obj->indexingSupportedFiles( path );
	vPortFree( path );

	/*
	obj->l->sendMessage( RTL_TYPE_M::RUN_MESSAGE_OK, "Creating file <<0:/playlist.sys>> in sd1." );


	r = f_open( &fList, "0:/playlist.sys", FA_WRITE | FA_CREATE_ALWAYS);
	if ( r != FR_OK ) {
		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<0:/playlist.sys>> in sd1 was not create." ) ) {

		}
	}

		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<0:/playlist.sys>> in sd1 created." ) != BASE_RESULT::OK ) return 2;

		/// Поиск по маске PSG.
		FILINFO		f_scan;

		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "Started scanning <<.psg>> file in sd1." ) != BASE_RESULT::OK ) return 2;

		r = f_findfirst( &obj->sd1_fdir, &f_scan, "0:/", "*.psg");
		while ( r == FR_OK && f_scan.fname[0] ) {
			char massageBuf[1024];
			sprintf( massageBuf, "The file <<%s>> is found.", f_scan.fname );
			if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, massageBuf ) != BASE_RESULT::OK ) return 2;

			uint32_t	len_file;
			EC_AY_FILE_MODE_ANSWER r_ay;
			r_ay = obj->ay_f->psg_file_get_long( f_scan.fname, len_file );


			if ( r_ay == EC_AY_FILE_MODE_ANSWER::OK ) {
				sprintf( massageBuf, "Length file <<%lu>> ticks.", len_file );
				if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, massageBuf ) != BASE_RESULT::OK ) return 2;

				if ( writeDataOfTreck( fList, f_scan.fname, len_file ) != 0 ) {
					if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_ERROR, "Write list file error!" ) != BASE_RESULT::OK ) return 2;
					return 1;
				} else {
					if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File added to list." ) != BASE_RESULT::OK ) return 2;
				}
			} else {
				if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_ERROR, "Length was not received." ) != BASE_RESULT::OK ) return 2;
			}

			r = f_findnext( &obj->sd1_fdir, &f_scan );
		}

		r = f_close( &fList );
		if ( r != FR_OK ) {
			if ( r == FR_DISK_ERR ) return 1;
			return 3;
		}*/

		return 0;
}






