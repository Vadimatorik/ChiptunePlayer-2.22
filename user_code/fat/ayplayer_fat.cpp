#include "ayplayer_fat.h"
#include <string.h>
#include <stdio.h>

char* AyPlayerFat::getFullPath( const char* const path, const char* const fileName ) {
	/// Получаем длину каждой строки без учета нуля терминатора.
	const uint32_t pathLen		=	strlen( path );
	const uint32_t nameFileLen	=	strlen( fileName );

	/// Получаем длину полной строки с учетом символа "/" и нуля терминатора.
	const uint32_t allLen = pathLen + nameFileLen + 2;

	/// Выделяем память под строку.
	char* allPathToFile	=	( char* )pvPortMalloc( allLen );
	assertParam( allPathToFile );

	/// Собираем единую строку.
	sprintf( allPathToFile, "%s/%s", path, fileName );

	/// Возвращаем указатель на полную строку.
	return allPathToFile;
}

DIR* AyPlayerFat::openDir( char* path ) {
	FRESULT			r;
	DIR*			d;

	/// Выделяем память под объект директории FatFS.
	d	=	( DIR* )pvPortMalloc( sizeof( DIR ) );
	assertParam( d );

	/// Открываем директорию.
	r = f_opendir( d, path );

	/// Если открыть директорию не удалось - высвобождаем память.
	if ( r != FRESULT::FR_OK ) {
		vPortFree( d );
		d	=	nullptr;
	}

	return d;
}

int AyPlayerFat::closeDir( DIR* d ) {
	if ( d == nullptr )		return 0;

	FRESULT			r;

	/// Закрываем директорию.
	r = f_closedir( d );
	vPortFree( d );

	/// Возвращаем успешность операции.
	return ( r == FRESULT::FR_OK ) ? 0 : -1;
}

FIL* AyPlayerFat::openFileListWithRewrite ( const char* const path, const char* const name ) {
	FRESULT				r;
	FIL*				f;

	/// Выделяем память под объект файла FatFS.
	f	=	( FIL* )pvPortMalloc( sizeof( FIL ) );
	assertParam( f );


	char* fullPath	=	AyPlayerFat::getFullPath( path, name );
	/// Пытаемся открыть файл с перезаписью, если таковой ранее существовал.
    r = f_open( f, fullPath, FA_CREATE_ALWAYS | FA_READ | FA_WRITE );
    vPortFree( fullPath );

    if ( r != FR_OK ) {
    	vPortFree( f );
    	f = nullptr;
    }

    return f;
}

FIL* AyPlayerFat::openFileList ( const char* const path, const char* const name ) {
	FRESULT				r;
	FIL*				f;

	/// Выделяем память под объект файла FatFS.
	f	=	( FIL* )pvPortMalloc( sizeof( FIL ) );
	assertParam( f );


	char* fullPath	=	AyPlayerFat::getFullPath( path, name );
	/// Пытаемся открыть файл с перезаписью, если таковой ранее существовал.
    r = f_open( f, fullPath, FA_READ );
    vPortFree( fullPath );

    if ( r != FR_OK ) {
    	vPortFree( f );
    	f = nullptr;
    }

    return f;
}

int AyPlayerFat::closeFile ( FIL* f ) {
	if ( f == nullptr )		return 0;

	FRESULT				r;

	/// Пытаемся открыть файл с перезаписью, если таковой ранее существовал.
    r = f_close( f );
    vPortFree( f );

    return ( r == FRESULT::FR_OK ) ? 0 : -1;
}

int	AyPlayerFat::writeItemFileListAndRemoveItem	( FIL* f, itemFileInFat* item ) {
	FRESULT				r;

	/// Пробуем записать.
	UINT				l;
	r = f_write( f, item, sizeof( itemFileInFat ), &l );

	/// После записи нам уже не нужна структура.
	vPortFree( item );

    /// Если записалось целиком все успешно, то возвратим 0.
    return ( ( r == FR_OK ) && ( l == sizeof( itemFileInFat ) ) ) ? 0 : -1;
}

int AyPlayerFat::startFindingFileInDir ( DIR** dir, FILINFO** fInfo, const char* const pathDir, const char* const maskFind ) {
	FRESULT				r;

	/// Выделяем память под объект директории, в которой будем искать файл,
	DIR*		d						=	( DIR* )pvPortMalloc( sizeof( DIR ) );
	assertParam( d );

	/// Выделяем память под объект директории, в которой будем искать файл,
	FILINFO*	fi						=	( FILINFO* )pvPortMalloc( sizeof( FILINFO ) );
	assertParam( fi );

	/// Открываем директорию и ищем в ней файл по маске.
	r = f_findfirst( d, fi, pathDir, maskFind );

	/// Файл найден.
	if ( r == FR_OK && fi->fname[0] ) {
		*dir	=	d;
		*fInfo	=	fi;		/// Отдаем указатель на структуру информации о файле FatFS.

		return 0;
	}

	/// Пошли проблемы, объекты директории и информации о файле теперь не нужны.
	vPortFree( d );
	vPortFree( fi );

	/// Проблемы на уровне флешки.
	if ( r != FR_OK ) {
		return -1;
	}

	/// Просто нет такого файла.
	return 1;
}

int AyPlayerFat::findingFileInDir ( DIR* d, FILINFO* fInfo ) {
	FRESULT				r;

	/// Ищем следующий файл по маске.
	r = f_findnext( d, fInfo );

	/// Файл найден.
	if ( r == FR_OK && fInfo->fname[0] ) {
		return 0;
	}

	/// Пошли проблемы, объекты директории и информации о файле теперь не нужны.
	vPortFree( d );
	vPortFree( fInfo );

	/// Проблемы на уровне флешки.
	if ( r != FR_OK ) {
		return -1;
	}

	/// Просто нет такого файла.
	return 1;
}

char* AyPlayerFat::getNameTrackFromFile			( FIL* f, uint32_t nubmerTrack ) {
	FRESULT				r;

	const uint32_t	lseek	=	sizeof( itemFileInFat ) * nubmerTrack;
	r	=	f_lseek( f, lseek );

	if ( r != FR_OK ) {
		return nullptr;
	}

	char*	name			=	( char* )pvPortMalloc( ITEM_FILE_IN_FAT_FILE_NAME_LEN );
	UINT		l;
	r	=	f_read( f, name, ITEM_FILE_IN_FAT_FILE_NAME_LEN, &l );
	if ( ( r == FR_OK ) && ( l == ITEM_FILE_IN_FAT_FILE_NAME_LEN ) ) {
		return name;
	} else {
		vPortFree( name );
		return nullptr;
	}
}

uint32_t AyPlayerFat::getLenTrackFromFile		( FIL* f, uint32_t nubmerTrack ) {
	FRESULT				r;

	const uint32_t	lseek	=	( sizeof( itemFileInFat ) * nubmerTrack ) + ITEM_FILE_IN_FAT_FILE_NAME_LEN + sizeof( AY_FORMAT );
	r	=	f_lseek( f, lseek );

	if ( r != FR_OK )
		return 0xFFFFFFFF;

	uint32_t	len;
	UINT		l;
	r	=	f_read( f, &len, sizeof( uint32_t ), &l );

	return ( ( r == FR_OK ) && ( l == sizeof( uint32_t ) ) ) ? len : 0xFFFFFFFF;
}

int AyPlayerFat::readItemFileListAndRemoveItem ( FIL* f, itemFileInFat* item, uint32_t numberTrack ) {
	FRESULT				r;

	const uint32_t	lseek	=	sizeof( itemFileInFat ) * numberTrack;
	r	=	f_lseek( f, lseek );

	if ( r != FR_OK ) {
		return -1;
	}

	UINT		l;
	r	=	f_read( f, item, sizeof( itemFileInFat ), &l );
	return ( ( r == FR_OK ) && ( l == sizeof( itemFileInFat ) ) ) ? 0 : -1;
}

int AyPlayerFat::checkingFile ( const char* path, const char* nameFile, FILINFO* fi, FRESULT& fatReturn ) {
	FRESULT		r;

	char* fullPath;
	fullPath = AyPlayerFat::getFullPath( path, nameFile );
	r = f_stat( fullPath, fi );
	vPortFree( fullPath );

	switch( ( uint32_t )r ) {
	case ( uint32_t )FR_OK:			return 1;
	case ( uint32_t )FR_NO_FILE:	return 0;
	default:
		fatReturn = r;
		return -1;
	}
}

/// 0 - ок, 1 - нет файла, -1 флешка проблемная.
int AyPlayerFat::removeFile ( const char* path, const char* nameFile, FRESULT& fatReturn ) {
	FRESULT		r;

	char* fullPath;
	fullPath = AyPlayerFat::getFullPath( path, nameFile );

	do {
		r = f_chmod( fullPath, 0, AM_RDO|AM_ARC|AM_SYS|AM_HID );		/// Снимаем блокировки.
		if ( r != FR_OK ) break;
		r = f_unlink( fullPath );
	} while( true );

	vPortFree( fullPath );

	switch( ( uint32_t )r ) {
	case ( uint32_t )FR_OK:			return 0;
	case ( uint32_t )FR_NO_FILE:	return 1;
	default:
		fatReturn = r;
		return -1;
	}
}

