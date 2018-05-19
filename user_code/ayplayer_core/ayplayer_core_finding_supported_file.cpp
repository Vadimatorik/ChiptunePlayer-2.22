#include "ayplayer.h"
#include "ayplayer_fat.h"

int	AyPlayer::scanDir ( char* path ) {
	int					r	=	0;

	FILINFO*			fi	=	nullptr;
	DIR*				d	=	nullptr;
	FIL*				f	=	nullptr;

	/// Ищем первый файл по маске.
	r	=	AyPlayerFat::startFindingFileInDir( &d, &fi, path, "*.psg" );

	/// Путь до файла со списком прошедших проверку файлов.
	bool	flagFileListCreate	=	false;

	/// Устанавливаем текущую директорию.
	if ( ( !r ) && ( f_chdir( path ) != FR_OK ) ) {
		r = -1;
	}

	while ( !r ) {
		/// Собираем строчку с полным путем.
		char*	fullPathToFile	=	AyPlayerFat::getFullPath( path, fi->fname );

		/// Лог: найден файл под маску.
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File found:", fullPathToFile );						/// Лог.

		/// Экран: начат анализ файла.
		m_slist_set_text_string( this->g.sl, "File analysis..." );											/// Экран.
		this->guiUpdate();


		/// Проверяем правильность файла.
		uint32_t fileLen;

		this->ay->setPlayFileName( fi->fname );
		this->ay->setPlaySd( AY_MICROSD::SD1 );

		int rPsgGet;
		rPsgGet = this->ay->psgFileGetLong( fileLen );

		/// Если файл прошел проверку.
		if ( rPsgGet == 0 ) {
			/// Если в этой директории еще не создавали файл со списком прошедших проверку файлов.
			if ( flagFileListCreate == false ) {
				flagFileListCreate = true;

				/// Пытаемся создать файл.
				f	=	AyPlayerFat::openFileListWithRewrite( path, LIST_NO_SORT_FAT_NAME );

				/// Если не удалось - чистим память и выходим.
				if ( f == nullptr ) {
					this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ERROR, "<<" LIST_NO_SORT_FAT_NAME ">> not created in dir:", path );
					vPortFree( fullPathToFile );
					r = -1;
					break;
				} else {
					this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "<<" LIST_NO_SORT_FAT_NAME ">> created in dir:", path );
				}
			}

			/// Лог: данный об проанализированном файле.
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Analysis was carried out successfully:", fullPathToFile );
			char lenString[50];
			sprintf( lenString, "%lu", fileLen );
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File len tick:", lenString );

			itemFileInFat*	fileListItem	=	this->structureItemFileListFilling( fi->fname, fileLen, AY_FORMAT::PSG );
			r	=	AyPlayerFat::writeItemFileListAndRemoveItem( f, fileListItem );

			if ( r != 0 ) {
				this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ISSUE, "Write item file in <<" LIST_NO_SORT_FAT_NAME ">> was not carried out successfully. Name item file: ", fi->fname );
				break;
			}

			/// В списке новый файл, сдвигаем.
			this->slItemShiftDown( 4, fi->fname );

			/// На экран.
			this->guiUpdate();
		} else {
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ISSUE, "Analysis was not carried out successfully:", fullPathToFile );
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

	r	=	( AyPlayerFat::closeFile( f ) != 0 ) ? -1 : r;
	if ( r == 0 ) {
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<" LIST_NO_SORT_FAT_NAME ">> was close successfully. Dir:" , path );
	} else {
		this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_ISSUE, "File <<" LIST_NO_SORT_FAT_NAME ">> was not close successfully. Dir:" , path );
	}

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

	this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Open  dir:", path );

	/// Рекурсивно обходим все папки.
	while( 1 ) {
		/// Gui: мы снова начали поиск нужного файла.
		m_slist_set_text_string( this->g.sl, "Find supported files..." );
		this->guiUpdate();

		r = f_readdir( d, &f );

		/// Если проблемы на нижнем уравне.
		if ( r != FR_OK )
			break;

		/// Закончились элементы в текущей директории.
		if ( f.fname[ 0 ] == 0 ) {
			/// Лог: директория закончилась.
			this->printMessageAndArg( RTL_TYPE_M::RUN_MESSAGE_OK, "Close dir:", path );

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


