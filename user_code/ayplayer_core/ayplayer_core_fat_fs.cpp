#include "ayplayer.h"
#include "ayplayer_fat.h"

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
		this->errorMicroSdDraw( sd, r );
	} else {
		char massage[] = "FatFs connected witch SDX!";
		/// Пишем вместо X номер карты.
		massage[ sizeof( massage ) - 3 ] = '1' + ( uint32_t )sd;

		this->l->sendMessage( RTL_TYPE_M::INIT_OK, massage );
	}

	return r;
}

int AyPlayer::checkingFile( AY_MICROSD sdName, const char* path, const char* nameFile, FILINFO* fi ) {
	FRESULT fRes;
	int r = AyPlayerFat::checkingFile( path, nameFile, fi, fRes );
	if ( r < 0 ) {
		this->errorMicroSdDraw( sdName, fRes );
		assertParam( false );
	}
	return r;
}

int AyPlayer::removeFile( AY_MICROSD sdName, const char* path, const char* nameFile ) {
	FRESULT fRes;
	int r = AyPlayerFat::removeFile( path, nameFile, fRes );
	if ( r < 0 ) {
		this->errorMicroSdDraw( sdName, fRes );
		assertParam( false );
	}
	return r;
}

int AyPlayer::removeDirRecurisve( AY_MICROSD sdName, const char* path, const char* nameDir ) {
	FRESULT fRes;

	char* fullPath	=	( char* )pvPortMalloc( 4096 );
	assertParam( fullPath );

	/// Собираем единую строку.
	sprintf( fullPath, "%s/%s", path, nameDir );

	int r = AyPlayerFat::removeDirRecurisve( fullPath, fRes );

	if ( r < 0 ) {
		this->errorMicroSdDraw( sdName, fRes );
		assertParam( false );
	}

	vPortFree( fullPath );

	return r;
}

int AyPlayer::checkingSystemFileInRootDir( AY_MICROSD sdName, const char* fatValome ) {
	FILINFO*	fi						=	( FILINFO* )pvPortMalloc( sizeof( FILINFO ) );
	assertParam( fi );

	int r;

	do {
		r = this->checkingFile( sdName, fatValome, "System Volume Information", fi );
		if ( r == 1 )		break;
		r = this->checkingFile( sdName, fatValome, "thumbs.db", fi );
		if ( r == 1 )		break;
		r = this->checkingFile( sdName, fatValome, "Desktop.ini", fi );
		if ( r == 1 )		break;
		r = this->checkingFile( sdName, fatValome, "autorun.inf", fi );
		if ( r == 1 )		break;
	} while( false );

	vPortFree( fi );

	return r;
}

void AyPlayer::removeSystemFileInRootDir( AY_MICROSD sdName, const char* fatValome ) {
	do {
		this->removeDirRecurisve( sdName, fatValome, "System Volume Information" );
		this->removeFile( sdName, fatValome, "thumbs.db" );
		this->removeFile( sdName, fatValome, "Desktop.ini" );
		this->removeFile( sdName, fatValome, "autorun.inf" );
	} while( false );
}
