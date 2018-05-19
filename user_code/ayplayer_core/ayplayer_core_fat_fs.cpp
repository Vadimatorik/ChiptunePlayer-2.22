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

int AyPlayer::checkingFileOrDir( AY_MICROSD sdName, const char* path, const char* nameFile, FILINFO* fi ) {
	FRESULT fRes;
	int r = AyPlayerFat::checkingFileOrDir( path, nameFile, fi, fRes );
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
		r = this->checkingFileOrDir( sdName, fatValome, "System Volume Information", fi );
		if ( r == 1 )		break;
		r = this->checkingFileOrDir( sdName, fatValome, ".Trash-1000", fi );
		if ( r == 1 )		break;
		r = this->checkingFileOrDir( sdName, fatValome, "thumbs.db", fi );
		if ( r == 1 )		break;
		r = this->checkingFileOrDir( sdName, fatValome, "Desktop.ini", fi );
		if ( r == 1 )		break;
		r = this->checkingFileOrDir( sdName, fatValome, "autorun.inf", fi );
		if ( r == 1 )		break;
	} while( false );

	vPortFree( fi );

	return r;
}

#define CHECK_RETURN_FUNC_VALUE(r)			if ( r < 0 )	break

int AyPlayer::removeSystemFileInRootDir( AY_MICROSD sdName, const char* fatValome ) {
	FILINFO*		fi	=	nullptr;
	fi	=	( FILINFO* )pvPortMalloc( sizeof( FILINFO ) );
	assertParam( fi );

	int r;

	do {
		r	=	this->checkingFileOrDir( sdName, fatValome, "System Volume Information", fi );
		CHECK_RETURN_FUNC_VALUE(r);
		if ( r == 1 ) {				/// Удаляем папку только если она есть :)
			r	=	this->removeDirRecurisve( sdName, fatValome, "System Volume Information" );
			CHECK_RETURN_FUNC_VALUE(r);
		}

		r	=	this->checkingFileOrDir( sdName, fatValome, ".Trash-1000", fi );
		CHECK_RETURN_FUNC_VALUE(r);
		if ( r == 1 ) {
			r	=	this->removeDirRecurisve( sdName, fatValome, ".Trash-1000" );
			CHECK_RETURN_FUNC_VALUE(r);
		}

		r	=	this->removeFile( sdName, fatValome, "thumbs.db" );
		CHECK_RETURN_FUNC_VALUE(r);
		r	=	this->removeFile( sdName, fatValome, "Desktop.ini" );
		CHECK_RETURN_FUNC_VALUE(r);
		r	=	this->removeFile( sdName, fatValome, "autorun.inf" );
		CHECK_RETURN_FUNC_VALUE(r);
	} while( false );

	vPortFree( fi );

	return r;
}
