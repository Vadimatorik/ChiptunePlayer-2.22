#include "ayplayer.h"

extern "C" {

extern MHost				makiseHost;
extern MakiseGUI			makiseGui;
extern MakiseDriver			makiseGuiDriver;

}

void AyPlayer::initWindowIndexingSupportedFiles( char* stateIndexing ) {
	m_create_slist(	&this->g.sl,
					&makiseHost.host,
					mp_rel( 0,	11,
							128, 64 - 11 ),
					stateIndexing,
					nullptr,
					nullptr,
					MSList_List,
					&this->gui->ssl,
					&this->gui->sslItem );

	/// Привязка list-а к его элементам.
	for ( int i = 0; i < 4; i++ ) {
		this->g.slItem[ i ].text	=	nullptr;
		m_slist_add( &this->g.sl, &this->g.slItem[ i ] );
	}
}

void AyPlayer::initWindowSortingFileList ( void ) {
	m_create_message_window(	&this->g.mw,
								&makiseHost.host,
								mp_rel( 0,	11,
										128, 64 - 11 ),
								"Sorting list file...",
								&this->gui->smw );
	this->guiUpdate();
}

void AyPlayer::removeWindowSortingFileList ( void) {
	makise_g_cont_rem( &this->g.mw.el );
}


void AyPlayer::initGuiStatusBar( void ) {
	m_create_player_status_bar(	&this->g.sb,
								&makiseHost.host,
								mp_rel(	0,	0,
										128, 12	),
								&this->gui->statusBarCfg,
								&this->gui->statusBarCallbackCfg	);
}

void AyPlayer::initPlayWindow ( void ) {
	mCreatePlayBar(	&this->g.pb,
					&makiseHost.host,
					mp_rel(	0,	57,
							128, 7	),
					1,
					&this->gui->playBarStyle );

	/// Время трека сразу в статус бар.
	mPlayBarSetNewTrack( &this->g.pb, this->fat.currentFileInfo.lenTick / 50 );

	mCreateScrollString(	&this->g.ss,
							&makiseHost.host,
							this->fat.currentFileInfo.fileName,
							mp_rel(	0,	11,
									128, 12	),
							&this->gui->scrollStringStyle	);
}

void AyPlayer::removePlayWindow ( void ) {
	makise_g_cont_rem( &this->g.pb.el );
}

void AyPlayer::removeWindowIndexingSupportedFiles( void ) {
	makise_g_cont_rem( &this->g.sl.el );
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
									&makiseHost.host,
									mp_rel( 0,	11,
											128, 64 - 11 ),
									massage,
									&this->gui->smw );
		this->guiUpdate();
		makise_g_cont_rem( &this->g.mw.el );
}


extern ST7565		lcd;

// Перерисовывает GUI и обновляет экран.
void AyPlayer::guiUpdate ( void ) {
	USER_OS_TAKE_MUTEX( this->os->mHost, portMAX_DELAY );
	lcd.bufClear();
	makise_g_host_call( &makiseHost, &makiseGui, M_G_CALL_PREDRAW );
	makise_g_host_call( &makiseHost, &makiseGui, M_G_CALL_DRAW );
	lcd.update();
	USER_OS_GIVE_BIN_SEMAPHORE( this->os->sGuiUpdate );
	USER_OS_GIVE_MUTEX( this->os->mHost );
}
