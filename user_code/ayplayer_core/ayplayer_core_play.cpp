#include "ayplayer.h"
#include "ayplayer_fat.h"

/// 0 данные получены.
/// 1 нет такого номера в списке.
/// -1 проблема с microsd.
int AyPlayer::getFileInfoFromListCurDir ( FILE_LIST_TYPE listType, uint32_t numberFileInList ) {
	FIL*	f;

	/*!
	 * Выбираем, какой список открыть (список должен быть сформирован заранее).
	 */
	switch( static_cast< uint32_t >( listType ) ) {
	case static_cast< uint32_t >( FILE_LIST_TYPE::NO_SORT ):
		f	=	AyPlayerFat::openFileInCurrentDir( AY_MICROSD::SD1, LIST_NO_SORT_FAT_NAME );
		break;
	case static_cast< uint32_t >( FILE_LIST_TYPE::NAME_SORT ):
		f	=	AyPlayerFat::openFileInCurrentDir( AY_MICROSD::SD1, LIST_SORT_NAME_FAT_NAME );
		break;
	case static_cast< uint32_t >( FILE_LIST_TYPE::LEN_SORT ):
		f	=	AyPlayerFat::openFileInCurrentDir( AY_MICROSD::SD1, LIST_SORT_LEN_FAT_NAME );
		break;
	}

	if ( f == nullptr )	return -1;

	/*!
	 * Смотрим, есть ли запрашиваемый номер файла в списке.
	 */
	uint32_t sizeFileList	=	f_size( f );
	uint32_t countItem	=	sizeFileList / sizeof( itemFileInFat );
	if ( countItem <= numberFileInList )
		return 1;


	FRESULT fRes;

	/*!
	 * Переходим к этому файлу.
	 */
	uint32_t lseek = sizeof( itemFileInFat ) * numberFileInList;
	fRes = f_lseek( f, lseek );
	if ( fRes != FR_OK )
		return -1;

	UINT l;
	fRes = f_read( f, &this->fat.currentFileInfo, sizeof( itemFileInFat ), &l);
	if ( fRes != FR_OK )
		return -1;

	if ( l != sizeof( itemFileInFat ) )
		return -1;

	return 0;
}

int AyPlayer::startPlayFile ( void ) {
	EC_AY_FILE_MODE_ANSWER r;

	this->pcb->dp->connect_on();

	this->pcb->dp->value_set( 0, 0, 0xFF );			// B
	this->pcb->dp->value_set( 0, 1, 0x80 );			// C
	this->pcb->dp->value_set( 0, 2, 0xFF );			// A

	this->pcb->dp->value_set( 0, 3, 0XFF );			// A1
	this->pcb->dp->value_set( 1, 0, 0x80 );			// B2
	this->pcb->dp->value_set( 1, 1, 0xFF );			// C1

	this->pcb->dp->value_set( 1, 2, 0xFF );			// Левый наушник.
	this->pcb->dp->value_set( 1, 3, 0xFF );			// Правый.

	switch( static_cast< uint32_t >( this->fat.currentFileInfo.format ) ) {
	case static_cast< uint32_t >( AY_FORMAT::PSG ):
		r	=	this->ayFile->psgFilePlay( this->fat.currentFileInfo.fileName, 1 );
	}

	if (	( r == EC_AY_FILE_MODE_ANSWER::OK ) ||
			( r == EC_AY_FILE_MODE_ANSWER::TRACK_STOPPED ) ||
			( r == EC_AY_FILE_MODE_ANSWER::TRACK_END )	) {
		return 0;
	} else {
		return -1;
	}
}
