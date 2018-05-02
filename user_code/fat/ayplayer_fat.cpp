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

FIL* AyPlayerFat::openFileList ( char* path ) {
	FRESULT				r;
	FIL*				f;

	/// Выделяем память под объект файла FatFS.
	f	=	( FIL* )pvPortMalloc( sizeof( FIL ) );
	assertParam( f );


	char* fullPath	=	AyPlayerFat::getFullPath( path, ".fileList" );
	/// Пытаемся открыть файл с перезаписью, если таковой ранее существовал.
    r = f_open( f, fullPath, FA_CREATE_ALWAYS | FA_READ | FA_WRITE );
    vPortFree( fullPath );

    if ( r != FR_OK ) {
    	vPortFree( f );
    	f = nullptr;
    }

    return f;
}

int AyPlayerFat::closeFileList ( FIL* f ) {
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
    return ( ( r != FR_OK ) || ( l != sizeof( itemFileInFat ) ) ) ? 0 : -1;
}

int AyPlayerFat::startFindingFileInDir ( DIR** dir, FILINFO** fInfo, const char* const pathDir, const char* const maskFind ) {
	FRESULT				r;

	/// Выделяем память под объект директории, в которой будем искать файл,
	DIR*		d					=	( DIR* )pvPortMalloc( sizeof( DIR ) );
	assertParam( d );

	/// Выделяем память под объект директории, в которой будем искать файл,
	FILINFO*	fi					=	( FILINFO* )pvPortMalloc( sizeof( FILINFO ) );
	assertParam( d );

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
