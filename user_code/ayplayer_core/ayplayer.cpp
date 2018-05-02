#include "ayplayer.h"
#include "ayplayer_fat.h"

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
											mp_rel( 0,	11,
													128, 64 - 11 ),
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
											mp_rel( 0,	11,
													128, 64 - 11 ),
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

		m_create_message_window(	&this->g.mw,
									&this->g.c,
									mp_rel( 0,	11,
											128, 64 - 11 ),
									massage,
									&this->gui->smw );
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

void AyPlayer::printMessageAndArg ( RTL_TYPE_M type, const char* const message, char* arg ) {
	const uint32_t lenPath				=	strlen( arg ) + 1;
	const uint32_t infoStringLen		=	strlen( message ) + 1;
	const uint32_t mallocByteGetValue	=	lenPath + infoStringLen;

	/// Открываем корень.
	char*		outputMessage;
	outputMessage = ( char* )pvPortMalloc( mallocByteGetValue );
	assertParam( outputMessage );

	sprintf( outputMessage, "%s\t%s", message, arg );

	this->l->sendMessage( type, outputMessage );

	vPortFree( outputMessage );
}

void AyPlayer::initWindowIndexingSupportedFiles( char* stateIndexing ) {
	m_create_slist(	&this->g.sl,
					&this->g.c,
					mp_rel( 0,	11,
							128, 64 - 11 ),
					stateIndexing,
					nullptr,
					nullptr,
					MSList_List,
					&this->gui->ssl,
					&this->gui->sslItem );

	for ( int i = 0; i < 4; i++ ) {
		this->g.slItem[ i ].text	=	nullptr;
		m_slist_add( &this->g.sl, &this->g.slItem[ i ] );
	}
}

uint32_t AyPlayer::getStatePlay ( void ) {
	return 0;
}

uint32_t AyPlayer::getPercentBattery ( void ) {
	return 0;
}

void AyPlayer::initGuiStatusBar( void ) {
	m_create_player_status_bar(	&this->g.sb,
								&this->g.c,
								mp_rel(	0,	0,
										128, 12	),
								&this->gui->statusBarCfg,
								&this->gui->statusBarCallbackCfg	);
}

// Метод сдвигает вниз все строки (1 удаляется) и добавляет вверх новую.
void AyPlayer::slItemShiftDown ( uint32_t cout, char* newSt ) {
	/// Если раньше там была не пустая строка.
	if ( this->g.slItem[ cout - 1 ].text != nullptr ) {
		vPortFree( this->g.slItem[ cout - 1 ].text );
	}

    for ( uint32_t l = cout - 1; l > 0 ; l-- ) {
        this->g.slItem[ l ].text = this->g.slItem[ l - 1 ].text;
    }

    uint32_t lenString = strlen( newSt ) + 1;
    this->g.slItem[ 0 ].text = ( char* )pvPortMalloc( lenString );
    strcpy( this->g.slItem[ 0 ].text, newSt );
}

void AyPlayer::slItemClean ( uint32_t cout ) {
    for ( uint32_t l = 0; l < cout ; l++ ) {
    	if ( this->g.slItem[ l ].text ) {
    		vPortFree( this->g.slItem[ l ].text );
    	}
    }
}

int	AyPlayer::scanDir ( char* path ) {
	int					r	=	0;

	FILINFO*			fi	=	nullptr;
	DIR*				d	=	nullptr;
	FIL*				f	=	nullptr;

	/// Ищем первый файл по маске.
	r	=	AyPlayerFat::startFindingFileInDir( &d, &fi, path, "*.psg" );

	/// Путь до файла со списком прошедших проверку файлов.
	bool	flagFileListCreate	=	false;

	while ( !r ) {
		/// Собираем строчку с полным путем.
		char*	fullPathToFile	=	AyPlayerFat::getFullPath( path, fi->fname );

		/// Лог: найден файл под маску.
		this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "File found:", fullPathToFile );						/// Лог.

		/// Экран: начат анализ файла.
		m_slist_set_text_string( &this->g.sl, "File analysis..." );											/// Экран.
		this->guiUpdate();

		/// Проверяем правильность файла.
		uint32_t fileLen;
		EC_AY_FILE_MODE_ANSWER	rPsgGet;
		rPsgGet = this->ayFile->psgFileGetLong( fullPathToFile, fileLen );

		/// Если файл прошел проверку.
		if ( rPsgGet == EC_AY_FILE_MODE_ANSWER::OK ) {
			/// Если в этой директории еще не создавали файл со списком прошедших проверку файлов.
			if ( flagFileListCreate == false ) {
				flagFileListCreate = true;

				/// Пытаемся создать файл.
				f	=	AyPlayerFat::openFileList( path );

				/// Если не удалось - чистим память и выходим.
				if ( f == nullptr ) {
					this->printMessageAndArg( RTL_TYPE_M::INIT_ERROR, "FileList not created in dir:", path );
					vPortFree( fullPathToFile );
					r = -1;
					break;
				} else {
					this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "FileList created in dir:", path );
				}
			}

			/// Лог: данный об проанализированном файле.
			this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "Analysis was carried out successfully:", fullPathToFile );
			char lenString[50];
			sprintf( lenString, "%lu", fileLen );
			this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "File len tick:", lenString );

			/// В списке новый файл, сдвигаем.
			this->slItemShiftDown( 4, fi->fname );

			/// На экран.
			this->guiUpdate();
		} else {
			this->printMessageAndArg( RTL_TYPE_M::INIT_ISSUE, "Analysis was not carried out successfully:", fullPathToFile );
		}

		/// Полный путь теперь не актуален.
		vPortFree( fullPathToFile );

		/// Ищем следующий элемент.
		r = AyPlayerFat::findingFileInDir( d, fi );

		/// Элементов больше нет.
		if ( r == 1 ) {
			break;
		}
	}

	/// 1 == последний файл, а это штатно.
	if ( r == 1 ) {
		r = 0;					/// d и fi почистила findingFileInDir,
	} else {
		/// Очищаем память.
		/// Даже если что-то не так пойдет на нижнем уровне - эти методы должны выполниться чтобы
		/// очистить память.
		/// Храним в себе только -1 или 0.
		/// Если была хоть раз -1, то не перезаписываем.
		if ( fi )			vPortFree( fi );
		r	=	( AyPlayerFat::closeDir( d ) != 0 ) ? -1 : r;
	}

	r	=	( AyPlayerFat::closeFileList( f ) != 0 ) ? -1 : r;

	return r;
}

FRESULT AyPlayer::indexingSupportedFiles( char* path ) {
	FRESULT					r;
	static FILINFO			f;

	/// Флаг выставляется, когда мы обнаружили в
	/// директории хоть один файл и просканировали ее на все по шаблону.
	/// Чтобы не нраваться на многократное повторное сканирование.
	bool				scanDir	=	false;

	/// Открываем директорию. Все игры с памятью внутри.
	DIR*	d	=	AyPlayerFat::openDir( path );

	if ( d == nullptr )
		return FRESULT::FR_DISK_ERR;

	this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "Open  dir:", path );

	/// Рекурсивно обходим все папки.
	while( 1 ) {
		/// Gui: мы снова начали поиск нужного файла.
		m_slist_set_text_string( &this->g.sl, "Find supported files..." );
		this->guiUpdate();

		r = f_readdir( d, &f );

		/// Если проблемы на нижнем уравне.
		if ( r != FR_OK )
			break;

		/// Закончились элементы в текущей директории.
		if ( f.fname[ 0 ] == 0 ) {
			/// Лог: директория закончилась.
			this->printMessageAndArg( RTL_TYPE_M::INIT_OK, "Close dir:", path );

			break;
		}

		/// Найдена новая директория.
		if ( f.fattrib & AM_DIR ) {
			uint32_t i = strlen(path);
			sprintf( &path[ i ], "/%s", f.fname );

			r	=	this->indexingSupportedFiles( path );

			if ( r != FRESULT::FR_OK )								/// Аварийная ситуация.
				break;

			path[ i ] = 0;
		} else {
			if ( scanDir == true ) continue;						/// Сканируем директорию лишь единожды.
			scanDir = true;
			if ( this->scanDir( path ) != 0 ) {
				break;
			}
		}
	}

	/// Фиксируем FRESULT::FR_DISK_ERR как приоритет над всем.
	r = ( AyPlayerFat::closeDir( d ) == -1 ) ? FRESULT::FR_DISK_ERR : r;

	return r;
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
