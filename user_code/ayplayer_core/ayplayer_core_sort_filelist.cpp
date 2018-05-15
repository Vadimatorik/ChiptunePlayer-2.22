#include "ayplayer.h"
#include "ayplayer_fat.h"
#include <algorithm>
#include <vector>

itemFileInFat* AyPlayer::structureItemFileListFilling ( const char* const nameTrack, const uint32_t lenTickTrack, const AY_FORMAT format ) {
	/// Выделяем память под элемент
	/// (его удалит после записи writeItemFileListAndRemoveItem).
	itemFileInFat* i	=	( itemFileInFat* )pvPortMalloc( sizeof( itemFileInFat ) );
	assertParam( i );

	/// Заполняем.
	strcpy( i->fileName, nameTrack );
	i->format		=	format;
	i->lenTick		=	lenTickTrack;

	return i;
}

int	AyPlayer::sortFileListCreateFile ( const char* const path, FIL** fNoSort, FIL** fNameSort, FIL** fLenSort ) {
	int r = 0;

	do {
		/// Открываем файл со списком.
		*fNoSort	=	AyPlayerFat::openFile( path, LIST_NO_SORT_FAT_NAME );
		if ( fNoSort == nullptr ) {
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "File <<" LIST_NO_SORT_FAT_NAME ">> not been open in dir:", path );
			r = -1;
			break;
		}

		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<" LIST_NO_SORT_FAT_NAME ">> opened successfully in dir:", path );

		/// Отсортированные по именам.
		*fNameSort	=	AyPlayerFat::openFileListWithRewrite( path, LIST_SORT_NAME_FAT_NAME );
		if ( fNameSort == nullptr ) {
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "File <<" LIST_SORT_NAME_FAT_NAME ">> not been open in dir:", path );
			r = -1;
			break;
		}

		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<" LIST_SORT_NAME_FAT_NAME ">> opened successfully in dir:", path );

		/// Отсортированные по длительности.
		*fLenSort	=	AyPlayerFat::openFileListWithRewrite( path, LIST_SORT_LEN_FAT_NAME );
		if ( fLenSort == nullptr ) {
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "File <<" LIST_SORT_LEN_FAT_NAME ">> not been open in dir:", path );
			r = -1;
			break;
		}

		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<" LIST_SORT_LEN_FAT_NAME ">> opened successfully in dir:", path );

	}  while( false );

	if ( r != 0 )	{
		AyPlayerFat::closeFile( *fNoSort );
		AyPlayerFat::closeFile( *fNameSort );
		AyPlayerFat::closeFile( *fLenSort );
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "File <<" LIST_NO_SORT_FAT_NAME ">>, <<" LIST_SORT_NAME_FAT_NAME ">> and <<" LIST_SORT_LEN_FAT_NAME ">> are closed in an emergency! Dir:", path );
		return r;
	}

	return r;
}

int	AyPlayer::sortFileListCloseFile ( const char* const path, DIR* d, FILINFO* fi, FIL* fNoSort, FIL* fNameSort, FIL* fLenSort ) {
	int r = 0;
	if ( fi )										vPortFree( fi );
	r	=	( AyPlayerFat::closeDir( d )			!= 0 ) ? -1 : r;
	r	=	( AyPlayerFat::closeFile( fNoSort )		!= 0 ) ? -1 : r;
	r	=	( AyPlayerFat::closeFile( fNameSort )	!= 0 ) ? -1 : r;
	r	=	( AyPlayerFat::closeFile( fLenSort )	!= 0 ) ? -1 : r;

	if ( r == 0 ) {
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<" LIST_NO_SORT_FAT_NAME ">>, <<" LIST_SORT_NAME_FAT_NAME ">> and <<" LIST_SORT_LEN_FAT_NAME ">> closed successfully! Dir:", path );
	} else {
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "File <<" LIST_NO_SORT_FAT_NAME ">>, <<" LIST_SORT_NAME_FAT_NAME ">> and <<" LIST_SORT_LEN_FAT_NAME ">> are closed in an emergency! Dir:", path );
	}

	return r;
}

int AyPlayer::writeSortFile ( FIL* output, FIL* input, uint16_t* sortArray, uint32_t count ) {
	int funResult;

	/// Пишем все структуры.
	for ( uint32_t i = 0; i < count; i++ ) {
		/// Выделяем память под считываемый из исходного файла элемент.
		itemFileInFat*	item	=	( itemFileInFat* )pvPortMalloc( sizeof( itemFileInFat ) );
		assertParam( item );

		funResult = AyPlayerFat::readItemFileListAndRemoveItem( input, item, sortArray[ i ] );
		if ( funResult != 0 )	break;	/// Что-то с картой.
		funResult = AyPlayerFat::writeItemFileListAndRemoveItem( output, item );
		if ( funResult != 0 )	break;	/// Что-то с картой.
	}

	return funResult;
}

void AyPlayer::initPointArrayToSort ( uint16_t* array, uint32_t count ) {
	/// Изначально все строкутры в своем порядке 0..countFileInDir-1.
	for ( uint32_t i = 0; i < count; i++ )
		array[ i ] = i;
}


int AyPlayer::sortForNameFileList ( const char* const path, uint16_t* fl, uint32_t countFileInDir, FILINFO* fi, DIR* d, FIL* fNoSort, FIL* fNameSort ) {
	int	sortResult	=	0;
	/// Начинаем быструю сортировку по имени.
	std::sort( fl, &fl[ countFileInDir ], [ this, path, &sortResult, fi, d, fNoSort, fNameSort ]( int a, int b ) {
		/*!
	 	 * Если в процессе сортировки упадет флешка - то выдаем одно значение для быстроты сортировки и выходим.
	 	 * Так массив быстро отсортируется и выйдя мы поймем, что упали.
	 	 */
		if ( sortResult < 0 ) {
			return true;
		}

		/// Получаем имена треков.
		char*	aStruct	=	AyPlayerFat::getNameTrackFromFile( fNoSort, a );

		if ( aStruct == nullptr ) {
			sortResult	=	-1;
			return true;
		}

		char*	bStruct	=	AyPlayerFat::getNameTrackFromFile( fNoSort, b );
		if ( bStruct == nullptr ) {
			sortResult	=	-1;
			return true;
		}

		/// Сравниваем строки.
		int resStrcmp;
		resStrcmp	=	strcmp( aStruct, bStruct );

		/// После сравнения удаляем сравниваемые элементы.
		vPortFree( aStruct );
		vPortFree( bStruct );

		/// Возвращаем результат сравнения.
		return resStrcmp < 0;
	} );

	if ( sortResult == 0 ) {
		sortResult = this->writeSortFile( fNameSort, fNoSort, fl, countFileInDir );
	}

	return sortResult;
}

int AyPlayer::sortForLenFileList ( const char* const path, uint16_t* fl, uint32_t countFileInDir, FILINFO* fi, DIR* d, FIL* fNoSort, FIL* fLenSort ) {
	int	sortResult	=	0;

	/// Начинаем быструю сортировку по имени.
	std::sort( fl, &fl[ countFileInDir ], [ this, path, &sortResult, fi, d, fNoSort, fLenSort ]( int a, int b ) {
		/*!
	 	 * Если в процессе сортировки упадет флешка - то выдаем одно значение для быстроты сортировки и выходим.
	 	 * Так массив быстро отсортируется и выйдя мы поймем, что упали.
	 	 */
		if ( sortResult < 0 ) {
			return true;
		}

		/// Получаем имена треков.
		uint32_t	aLen	=	AyPlayerFat::getSizeTrackFromFile( fNoSort, a );

		if ( aLen == 0xFFFFFFFF ) {
			sortResult	=	-1;
			return true;
		}

		uint32_t	bLen	=	AyPlayerFat::getSizeTrackFromFile( fNoSort, b );
		if ( bLen == 0xFFFFFFFF ) {
			sortResult	=	-1;
			return true;
		}

		return aLen < bLen;
	} );

	if ( sortResult == 0 ) {
		sortResult = this->writeSortFile( fLenSort, fNoSort, fl, countFileInDir );
	}

	return sortResult;
}

int	AyPlayer::sortFileList ( char* path ) {
	int					r	=	0;

	FILINFO*			fi			=	nullptr;
	DIR*				d			=	nullptr;
	FIL*				fNoSort		=	nullptr;
	FIL*				fNameSort	=	nullptr;
	FIL*				fLenSort	=	nullptr;

	/// Ищем файл в директории.
	r	=	AyPlayerFat::startFindingFileInDir( &d, &fi, path, LIST_NO_SORT_FAT_NAME );
	if ( r != 0 )
		return r;			/// Папка без поддерживаемых файлов.

	if ( sortFileListCreateFile( path, &fNoSort, &fNameSort, &fLenSort ) != 0 ) {
		AyPlayerFat::closeDir( d );
		return -1;
	}

	/// Мы нашли наш файл.
	char*	fullPathToFile	=	AyPlayerFat::getFullPath( path, fi->fname );

	/// Лог: найден файл под маску.
	this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Start sorting file:", fullPathToFile );					/// Лог.
	vPortFree( fullPathToFile );

	/// Получаем колличество файлов в директории.
	const uint32_t	countFileInDir	=	fi->fsize	/	sizeof( itemFileInFat );

	/*!
	 * Для каждой структуры выделим свой номер, так как они расположены в исходном файле.
	 */
	uint16_t* fl	=	( uint16_t* )pvPortMalloc( sizeof( uint16_t ) * countFileInDir );

	/// Сортировка по имени.
	this->initPointArrayToSort( fl, countFileInDir );
	r = sortForNameFileList( path, fl, countFileInDir, fi, d, fNoSort, fNameSort );
	if ( r != 0 ) {
		vPortFree( fl );
		this->sortFileListCloseFile( path, d, fi, fNoSort, fNameSort, fLenSort );
		return r;
	}

	/// Сортировка по длине.
	this->initPointArrayToSort( fl, countFileInDir );
	r = sortForLenFileList( path, fl, countFileInDir, fi, d, fNoSort, fLenSort );
	if ( r != 0 ) {
		vPortFree( fl );
		this->sortFileListCloseFile( path, d, fi, fNoSort, fNameSort, fLenSort );
		return r;
	}

	vPortFree( fl );

	/// Во время сортировки случилась ошибка.
	if ( r != 0 ) {
		this->sortFileListCloseFile( path, d, fi, fNoSort, fNameSort, fLenSort );
		return -1;
	}

	r = this->sortFileListCloseFile( path, d, fi, fNoSort, fNameSort, fLenSort );
	return r;
}

FRESULT AyPlayer::findingFileListAndSort ( char* path ) {
	FRESULT					r;
	static FILINFO			f;

	/// Открываем директорию. Все игры с памятью внутри.
	DIR*	d	=	AyPlayerFat::openDir( path );

	if ( d == nullptr )
		return FRESULT::FR_DISK_ERR;

	this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Open  dir:", path );

	/// Флаг единоразового файла в директории.
	bool				scanDir	=	false;

	/// Рекурсивно обходим все папки.
	while( 1 ) {
		r = f_readdir( d, &f );

		/// Если проблемы на нижнем уравне.
		if ( r != FR_OK )
			break;

		/// В данной директории нет файла с описанием.
		if ( f.fname[ 0 ] == 0 ) {
			/// Лог: директория закончилась.
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Close dir:", path );

			break;
		}

		/// Найдена новая директория.
		if ( f.fattrib & AM_DIR ) {
			uint32_t i = strlen(path);
			sprintf( &path[ i ], "/%s", f.fname );

			r	=	this->findingFileListAndSort( path );

			if ( r != FRESULT::FR_OK )								/// Аварийная ситуация.
				break;

			path[ i ] = 0;
		} else {
			if ( scanDir == true ) continue;						/// Сканируем директорию лишь единожды.
			scanDir = true;
			if ( this->sortFileList( path ) != 0 ) {				/// Сортируем файл, если он там есть.
				break;
			}
		}
	}

	/// Фиксируем FRESULT::FR_DISK_ERR как приоритет над всем.
	r = ( AyPlayerFat::closeDir( d ) == -1 ) ? FRESULT::FR_DISK_ERR : r;

	return r;
}

