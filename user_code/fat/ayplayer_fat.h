#pragma once

#include "ff.h"
#include "ayplayer_microsd_card.h"

#define ITEM_FILE_IN_FAT_FILE_NAME_LEN			256

enum class AY_FORMAT {
	PSG				=	0,
};

/// Структура одного элемента в файле <<*.list>>.
struct itemFileInFat {
	char			fileName[ ITEM_FILE_IN_FAT_FILE_NAME_LEN ];
	AY_FORMAT		format;
	uint32_t		lenTick;
};


class AyPlayerFat {
public:
	/*!
	 * Выделяет память в куче под строку с полным путем до файла с расширением.
	 * В случае, если не хватит памяти - упадет в assertParam.
	 * \param[in]		path		-	путь до текущего каталога.
	 * \param[in]		fileName	-	имя файла.
	 *
	 * \return			{	Строка с полным путем.	}
	 */
	static	char*		getFullPath						( const char* const path, const char* const fileName );

	/*!
	 * Открывает директорию по заданному пути с созданием ее объекта FatFS.
	 * \param[in]		path		-	путь до требуемого каталога.
	 * 									(полный, включая карту).
	 *
	 * \return			{	Указатель на объект директории FatFs
	 * 						или nullptr, если открыть не удалось.	}
	 */
	static	DIR*		openDir							( char* path );

	/*!
	 * Закрывает ранее открытую директорию и удаляет ее объект FatFS.
	 * \param[in]		d			-	объект директории FatFS.
	 *
	 * \return			{	0	-	директория успешно закрыта, объект
	 * 								директории FatFS удален.
	 * 						-1	-	директория закрыта с ошибкой, объект
	 * 								директории FatFS удален.	}
	 */
	static	int			closeDir						( DIR* d );

	/*!
	 * Открывает файл по заданному пути или создает его заново.
	 * Если файл по данному пути существовал ранее - заменяет его.
	 * \param[in]		path		-	путь до файла, который будет открыт
	 * 									(полный, включая расширение и карту).
	 *
	 * \return			{	Указатель на объект файла FatFS
	 * 						или nullptr, если открыть не удалось.	}
	 */
	static	FIL*		openFileListWithRewrite			( const char* const path, const char* const name );

	/*!
	 * Открывает файл по заданному пути/
	 * Файл должен существовать.
	 * Если файл по данному пути существовал ранее - заменяет его.
	 * \param[in]		path		-	путь до файла, который будет открыт
	 * 									(полный, включая расширение и карту).
	 *
	 * \return			{	Указатель на объект файла FatFS
	 * 						или nullptr, если открыть не удалось.	}
	 */
	static	FIL*		openFile					( const char* const path, const char* const name );

	static	FIL*		openFileInCurrentDir		( const AY_MICROSD sd, const char* const name );
	/*!
	 * Закрывает ранее открытый файл и удаляет его объект FatFS.
	 * \param[in]		f			-	объект файла FatFS.
	 *
	 * \return			{	0	-	файл успешно закрыт, объект
	 * 								файла FatFS удален.
	 * 						-1	-	файл закрыт с ошибкой, объект
	 * 								файла FatFS удален.	}
	 */
	static	int			closeFile					( FIL* f );

	/*!
	 * Записывает структуру элемента в <<.fileList>> (информацию о треке).
	 * Вне зависимости от результата записи структура удаляется.
	 * \param[in]		f			-	объект файла FatFS.
	 * \param[in]		item		-	структура записываемого элемента.
	 *
	 * \return			{	0	-	элемент успешно записан, структура
	 * 								элемента удалена.
	 * 						-1	-	элемент записан с ошибкой, структура
	 * 								элемента удалена.	}
	 *
	 */
	static	int			writeItemFileListAndRemoveItem	( FIL* f, itemFileInFat* item );

	static	int			readItemFileListAndRemoveItem	( FIL* f, itemFileInFat* item, uint32_t numberTrack );

	/*!
	 * Открывает директорию и ищет в ней первый элемент по маске.
	 * \param[out]		fInfo		-	указатель на указатель на структуру информации о файле FatFS.
	 * \prarm[out]		d			-	указатель на указатель на объект директории FatFS.
	 * \param[in]		pathDir		-	директория, в которой будет производится поиск.
	 * \param[in]		maskFind	-	маска поиска.
	 *
	 * \return			{	0	-	элемент найден успешно, информация о
	 * 								нем находится в объекте информации о файле FatFS
	 * 								( fInfo ).
	 * 						-1	-	произошла ошибка на уровне FatFS, память была высвобождена.
	 * 						1	-	закончились файлы по маске в директории, память была высвобождена.	}
	 */
	static	int			startFindingFileInDir			( DIR** dir, FILINFO** fInfo, const char* const pathDir, const char* const maskFind );

	/*!
	 * Продолжает поиск файла по заданной методом startFindingFileInDir маске.
	 * \param[in]		f			-	объект директории FatFS.
	 * \param[out]		fInfo		-	объект структуры информации о файле FatFS.
	 */
	static	int			findingFileInDir				( DIR* d, FILINFO* fInfo );

	/*!
	 * Достает из ранее открытого файла-списка имя трека с заданным номером.
	 * \param[in]		f			-	файл со списком треков.
	 * \param[in]		nubmerTrack	-	номер трека в списке. Счет с 0.
	 *
	 * \return			{	Строка с именем или nullptr.	}
	 */
	static	char*		getNameTrackFromFile			( FIL* f, uint32_t nubmerTrack );

	/*!
	 * Достает из ранее открытого файла-списка размер трека с заданным номером.
	 * \param[in]		f			-	файл со списком треков.
	 * \param[in]		nubmerTrack	-	номер трека в списке. Счет с 0.
	 *
	 * \return			{	Длина трека или 0xFFFFFFFF	}
	 */
	static	uint32_t	getSizeTrackFromFile				( FIL* f, uint32_t nubmerTrack );



	static	int	setOffsetByteInOpenFile			( FIL* f, uint32_t offset );

	static	int	readFromOpenFile			( FIL* f, uint8_t* returnData, const uint32_t countByte );

	/*!
	 * Возвращает размер файла.
	 * \param[in]		f				-	открытый файл, размер которого необходимо получить.
	 * \param[in]		returnSizeByte	-	переменная, в которую будет положен размер трека.
	 *
	 * \return			{	Длина трека или 0xFFFFFFFF	}
	 */
	static	int			getSizeFromOpenTreck				( FIL* f, uint32_t& returnSizeByte );



	/*!
	 * Проверяет наличие файла.
	 */
	static	int			checkingFileOrDir					( const char* path, const char* nameFile, FILINFO* fi, FRESULT& fatReturn );

	static	int			removeFile						( const char* path, const char* nameFile, FRESULT& fatReturn );

	/// Внимание! Нужен большой под path массив!
	static	int			removeDir						( const char* path, FRESULT& fatReturn );

	static	int			removeDirRecurisve				( char* path, FRESULT& fatReturn );
};
