#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"

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

int AyPlayer::fsmStepFuncIndexingSupportedFiles ( HANDLER_FSM_INPUT_DATA ) {
	/// Путь до актуального каталога.
	char*			path		=	( char* )pvPortMalloc( 1024 );
	assertParam( path );
	strcpy( path, "0:");

	/// Лог: начат анализ.
	obj->l->sendMessage( RTL_TYPE_M::RUN_MESSAGE_OK, "Indexing files start." );

	/// Готовим окно list-а c файлами..
	obj->initWindowIndexingSupportedFiles();

	/// Составляем список.
	FRESULT r;
	r = obj->indexingSupportedFiles( path );

	/// Закрываем окно поиска.
	obj->removeWindowIndexingSupportedFiles();

	/// Чистим память.
	vPortFree( path );
	obj->slItemClean( 4 );

	if ( r == FRESULT::FR_OK ) {
		return 0;
	} else {
		obj->errorMicroSdDraw( AY_MICROSD::SD1, r );
		return 1;
	}
}

int AyPlayer::fsmStepFuncSortingFileList ( HANDLER_FSM_INPUT_DATA ) {
	char*			path		=	( char* )pvPortMalloc( 1024 );
	int				r;

	assertParam( path );
	strcpy( path, "0:");

	obj->initWindowSortingFileList();

	/// Лог: начат анализ.
	obj->l->sendMessage( RTL_TYPE_M::RUN_MESSAGE_OK, "Started sorting fileList." );
	r = obj->findingFileListAndSort( path );

	vPortFree( path );

	obj->removeWindowSortingFileList();

	if ( r != 0 ) return 1;

	return 0;
}

int AyPlayer::fsmStepFuncCheckingChangeFatVolume ( HANDLER_FSM_INPUT_DATA ) {
	return obj->checkingSystemFileInRootDir( AY_MICROSD::SD1, "0:" );
}

int AyPlayer::fsmStepFuncCleanFlagChangeFatVolume ( HANDLER_FSM_INPUT_DATA ) {
	obj->removeSystemFileInRootDir( AY_MICROSD::SD1, "0:" );
	return 0;
}

int AyPlayer::fsmStepFuncInitMainWindow ( HANDLER_FSM_INPUT_DATA ) {
	/// Вместо считывания с карты памяти (системной).
	/// Заполняем стандартные параметры.
	obj->lType			=	FILE_LIST_TYPE::NAME_SORT;
	obj->playState		=	AYPLAYER_STATUS::STOP;
	obj->currentFile	=	0;
	obj->wNow			=	AYPLAYER_WINDOW_NOW::MAIN;

	/// Таблица громкости по умолчанию.
	memcpy( obj->volumeTable, volumeTableDafault, sizeof( volumeTableDafault ) );
	obj->currentVolumeIndex	=	4;

	/// Забираем начальные значения потенциометров.
	memcpy( &obj->eq, &ayplayerEqualizerDafault, sizeof( ayplayerEqualizer ) );

	/// Переносим каталог воспроизведения в центр.
	FRESULT	fr;
	fr	=	f_chdir("0:");
	(void)fr;

	int		r;

	/// забираем колличество файлов в текущей директории.
	r = obj->getFileCountInCurDir( obj->lType, obj->countFileInCurrentDir );

	/// Забираем данные о треке, на котором остановили воспроизведение.
	r = obj->getFileInfoFromListCurDir( obj->lType, obj->currentFile );

	obj->initPlayWindow();													/// Открываем главное окно.
	(void)r;


	obj->guiUpdate();
	return 0;
}
