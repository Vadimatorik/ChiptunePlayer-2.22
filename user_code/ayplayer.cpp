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

bool AyPlayer::checkSd ( AY_MICROSD sd ) {
	/// Если тип карты определен, значит она есть в слоте.
	if ( this->pcb->sd[ (uint32_t)sd ]->getStatus() != EC_SD_STATUS::NOINIT )
		return true;

	if ( this->pcb->sd[ (uint32_t)sd ]->initialize() != EC_MICRO_SD_TYPE::ERROR ) {
		return true;
	} else {
		return false;
	}
}

void AyPlayer::waitSdCardInsert ( void ) {
	/*!
	 * -1	-	первое сканирование.
	 * 0	-	отсуствует.
	 * 1	-	обнаружена.
	 */
	int flagMicroSd1Present = -1;
	int flagMicroSd2Present = -1;

	do {
		if ( this->checkSd( AY_MICROSD::SD1 ) ) {
			if ( flagMicroSd1Present != 1 ) {
				flagMicroSd1Present = 1;
				this->l->sendMessage( RTL_TYPE_M::INIT_OK, "SD1 is detected!" );
			}
		} else {
			if ( flagMicroSd1Present != 0 ) {
				flagMicroSd1Present = 0;

				this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD1 missing!" );

				const char SD1_NOT_PRESENT[]	=	"SD1 not present!";

				m_create_message_window(	&this->g.mw,
											&this->g.c,
											mp_rel( 9, 10, 108, 44 ),
											( char* )SD1_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();
				makise_g_cont_rem( &this->g.mw.el );
			}

			vTaskDelay( 100 );
			continue;
		}

		if ( this->checkSd( AY_MICROSD::SD2 ) ) {
			if ( flagMicroSd2Present != 1 ) {
				flagMicroSd2Present = 1;
				this->l->sendMessage( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
			}
		} else {
			if ( flagMicroSd2Present != 0 ) {
				flagMicroSd2Present = 0;

				this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" );

				const char SD2_NOT_PRESENT[]	=	"SD2 not present!";

				m_create_message_window(	&this->g.mw,
											&this->g.c,
											mp_rel( 9, 10, 108, 44 ),
											( char* )SD2_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();
				makise_g_cont_rem( &this->g.mw.el );
			}

			vTaskDelay( 100 );
			continue;
		}

	} while( !( flagMicroSd1Present && flagMicroSd2Present ) );
}

void AyPlayer::waitSdCardDisconnect ( const AY_MICROSD sd ) {
	while( true ) {
		if ( this->pcb->sd[ (uint32_t)sd ]->getStatus() != EC_SD_STATUS::OK )
			break;
	}

	char	massage[] = "SDX was been disconnect.";

	if ( sd == AY_MICROSD::SD1 ) {
		massage[ 2 ]	=	'1';
	} else {
		massage[ 2 ]	=	'2';
	}

	this->l->sendMessage( RTL_TYPE_M::INIT_OK, massage );

}

void AyPlayer::errorMicroSdDraw ( const AY_MICROSD sd, const FRESULT r ) {
	char	massage[ 100 ];

	massage[ 0 ] = 'S';
	massage[ 1 ] = 'D';

	if ( sd == AY_MICROSD::SD1 ) {
		massage[ 2 ]	=	'1';
	} else {
		massage[ 2 ]	=	'2';
	}

	massage[ 3 ] = ':';

	const char*	s;

	switch ( r ) {
		case FR_DISK_ERR:				s	=	sErrDiskErr;				break;
		case FR_INT_ERR:				s	=	sErrIntErr;					break;
		case FR_NOT_READY:				s	=	sErrNotReady;				break;
		case FR_NO_FILE:				s	=	sErrNoFile;					break;
		case FR_NO_PATH:				s	=	sErrnoPath;					break;
		case FR_INVALID_NAME:			s	=	sErrInvalidName;			break;
		case FR_DENIED:					s	=	sErrDenied;					break;
		case FR_EXIST:					s	=	sErrExist;					break;
		case FR_INVALID_OBJECT:			s	=	sErrInvalidObject;			break;
		case FR_WRITE_PROTECTED:		s	=	sErrWriteProtected;			break;
		case FR_INVALID_DRIVE:			s	=	sErrInvalidDrive;			break;
		case FR_NOT_ENABLED:			s	=	sErrNotEnabled;				break;
		case FR_NO_FILESYSTEM:			s	=	sErrnoFilesystem;			break;
		case FR_MKFS_ABORTED:			s	=	sErrMkfsAborted;			break;
		case FR_TIMEOUT:				s	=	sErrTimeout;				break;
		case FR_LOCKED:					s	=	sErrLocked;					break;
		case FR_NOT_ENOUGH_CORE:		s	=	sErrNotEnoughCore;			break;
		case FR_TOO_MANY_OPEN_FILES:	s	=	sErrTooManyOpenFiles;		break;
		case FR_INVALID_PARAMETER:		s	=	sErrInvalidParameter;		break;

		default:
			while( 1 );	/// Невозможный исход.
		}



		strcpy( &massage[ 5 ], s );
		massage[ 4 ]	=	'\t';							/// В консоле удобнее через tab.
		this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, massage );

		massage[ 4 ]	=	' ';							/// На экране однозначно на разных строках.

		m_create_message_window( &this->g.mw, &this->g.c, mp_rel( 9, 10, 108, 44 ), massage, ( MakiseStyle_SMessageWindow* )&this->gui->smw );
		this->guiUpdate();
		makise_g_cont_clear( &this->g.c );
}

FRESULT AyPlayer::fatFsReinit( AY_MICROSD sd ) {
	FRESULT	r;

	switch( ( uint32_t )sd ) {
	case ( uint32_t )AY_MICROSD::SD1:
		r = f_mount( &this->fat.f[ 0 ], "0:", 1 );
		break;

	case ( uint32_t )AY_MICROSD::SD2:
		r = f_mount( &this->fat.f[ 1 ], "1:", 1 );
		break;

	default:
		return FRESULT::FR_INVALID_PARAMETER;
	};

	if ( r != FRESULT::FR_OK ) {
		errorMicroSdDraw( sd, r );
	} else {
		char massage[] = "FatFs connected witch SDX!";
		/// Пишем вместо X номер карты.
		massage[ sizeof( massage ) - 3 ] = '1' + ( uint32_t )sd;

		this->l->sendMessage( RTL_TYPE_M::INIT_OK, massage );
	}

	return r;
}

void AyPlayer::printOpenDir ( char* path ) {
	/// Открываем корень.
	char* message	=	( char* )pvPortMalloc( 4500 );
	assertParam( message );
	snprintf( message, 4500, "Open dir: %s", path );
	this->l->sendMessage( RTL_TYPE_M::INIT_OK, message );
	vPortFree( message );
}

void AyPlayer::printCloseDir ( char* path ) {
	/// Открываем корень.
	char* message	=	( char* )pvPortMalloc( 4500 );
	assertParam( message );
	snprintf( message, 4500, "Close dir: %s", path );
	this->l->sendMessage( RTL_TYPE_M::INIT_OK, message );
	vPortFree( message );
}

#define AYPLAYER_ERR_OPEN_DIR			"Error open dir: "

void AyPlayer::printOpenDirError ( char* path ) {
	char* message	=	( char* )pvPortMalloc( 4500 );
	assertParam( message );
	strcpy( message, AYPLAYER_ERR_OPEN_DIR );
	strcpy( &message[ sizeof( AYPLAYER_ERR_OPEN_DIR ) - 1], path );
	this->l->sendMessage( RTL_TYPE_M::INIT_ERROR, message );
	vPortFree( message );
}

void AyPlayer::indexingSupportedFiles( char* path ) {
	FRESULT				r;
	DIR*				d	=	( DIR* )pvPortMalloc( sizeof( DIR ) );
	assertParam( d );
	static FILINFO		f;

	this->printOpenDir( path );

	r = f_opendir( d, path );
	if ( r != FRESULT::FR_OK ) {
		this->errorMicroSdDraw( AY_MICROSD::SD1, r );
		this->printOpenDirError( path );
	}

	/// Рекурсивно обходим все папки.
	while( 1 ) {
		r = f_readdir( d, &f );

		/// Закончились элементы в текущей директории.
		if ( r != FR_OK || f.fname[ 0 ] == 0 ) {
			vPortFree( d );
			break;
		}

		/// Найдена новая директория.
		if ( f.fattrib & AM_DIR ) {
			uint32_t i = strlen(path);
			sprintf( &path[ i ], "/%s", f.fname );
			this->indexingSupportedFiles( path );
			path[ i ] = 0;
		} else {
			static FILINFO	fMusic;
			static DIR		dirMusicFile;
			/// В папке есть хотя бы 1 файл.
			/// Так что ищем в этой директории отдельно файлы, которые поддерживаем.
		    r = f_findfirst( &dirMusicFile, &fMusic, path, "*.psg");

		    while ( r == FR_OK && fMusic.fname[0] ) {
		    	this->l->sendMessage( RTL_TYPE_M::INIT_OK, fMusic.fname );
		        r = f_findnext( &dirMusicFile, &fMusic );
		    }
		}
	}

	this->printCloseDir( path );
	f_closedir( d );

	return;
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

void AyPlayer::start ( void ) {
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::mainTask,
								"main",
								TB_MAIN_TASK_SIZE,
								( void* )this,
								MAIN_TASK_PRIO,
								this->tbMainTask,
								&this->tsMainTask );

	USER_OS_STATIC_TASK_CREATE(	AyPlayer::illuminationControl,
								"led",
								TB_ILLUMINATION_CONTROL_TASK_SIZE,
								( void* )this,
								ILLUMINATION_CONTROL_TASK_PRIO,
								this->tbIlluminationControlTask,
								&this->tsIlluminationControlTask );

	vTaskStartScheduler();
}

uint32_t AyPlayer::getRccMode ( void ) {
	return this->rccIndex;
}

void AyPlayer::mainTask ( void* obj ) {
	AyPlayer* o = ( AyPlayer* )obj;
	o->fsm.start( &ayPlayerFreeRtosObjInitFsmStep, o );
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
