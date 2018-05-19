#include "ayplayer_ay_file_class.h"

void AyYmFilePlay::setPlaySd ( AY_MICROSD sd ) {
	this->sd = sd;
}

void AyYmFilePlay::setUsingChip ( uint32_t chipNumber ) {
	this->usingChip = chipNumber;
}

void AyYmFilePlay::setPlayFileName ( const char* fileName ) {
	this->fileName = fileName;
}

void AyYmFilePlay::setPause ( bool state ) {
	this->ayLow->playStateSet( state );
}

void AyYmFilePlay::stop ( void ) {
	this->flagStop	=	true;
}

#define CHECK_ERROR(r)		if ( r != 0 ) {			\
								this->abort();		\
								return r;			\
							}

#define CHECK_STOP()		if ( this->flagStop == true ) {	\
								this->abort();				\
								return -5;					\
							}

int AyYmFilePlay::openFile ( void ) {
	/// Сброс флагов.
	this->flagStop		=	false;
	this->f = AyPlayerFat::openFileInCurrentDir( this->sd, this->fileName );

	/// Если открыть файл не удалось - выход.
	if ( this->f == nullptr )
		return -1;

	/// Узнаем длину трека.
	uint32_t counByteInTreck;
	if ( AyPlayerFat::getSizeFromOpenTreck( this->f, counByteInTreck ) != 0 ) {
		AyPlayerFat::closeFile( this->f );
		return -1;
	}

	/// Решаем, сколько скопировать в буффер.
	UINT getCountByte;
	if ( counByteInTreck < AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE ) {
		getCountByte = counByteInTreck;
	} else {
		getCountByte = AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE;
	}

	/// Забираем в буффер данные.
	if ( AyPlayerFat::readFromOpenFile( this->f, this->flashBuffer, getCountByte ) != 0 ) {
		AyPlayerFat::closeFile( this->f );
		return -1;
	}

	/// Ставим указатель на данные в начало.
	this->pointStartSeekBuffer		=	0;
	this->pointInBuffer				=	0;

	return 0;
}

int AyYmFilePlay::closeFile ( void ) {
	while( this->ayLow->queueEmptyCheck() != true ) {			/// Ждем, пока AY освободится.
		CHECK_STOP();
		USER_OS_DELAY_MS(20);
	}

	this->ayLow->playStateSet( 0 );								/// Отключаем аппаратку.
	this->setPwrChip( false );									/// Питание чипа.
	this->ayLow->queueClear();									/// Чистим очередь.

	return AyPlayerFat::closeFile( this->f );
}

int AyYmFilePlay::getFileLen ( uint32_t& returnFileLenByte ) {
	int	r;
	r = AyPlayerFat::getSizeFromOpenTreck( this->f, returnFileLenByte );
	CHECK_ERROR( r );
	return 0;
}

int AyYmFilePlay::setOffsetByteInFile ( const uint32_t offsetByte ) {
	int	r;

	/// Узнаем длину трека.
	uint32_t counByteInTreck;
	r = AyPlayerFat::getSizeFromOpenTreck( this->f, counByteInTreck );
	CHECK_ERROR( r );

	/// Если смещаемся дальше размера трека.
	if ( offsetByte >= counByteInTreck ) {
		this->abort();
		return -1;
	}

	/// Если смещение попало в диапазон, который есть в буффере.
	if (	( offsetByte > this->pointStartSeekBuffer ) &&
			( offsetByte < this->pointStartSeekBuffer + AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE )	) {
		this->pointInBuffer = offsetByte - this->pointStartSeekBuffer;
		return 0;
	}

	/// Если меньше самого младшего адреса байта в буффере,
	/// Или больше самого старшего.
	/// тогда придется перезагрузить буффер.
	/// Адрес самого младшего байта теперь будет изменен.
	this->pointStartSeekBuffer = offsetByte;

	/// Решаем, сколько скопировать в буффер.
	UINT getCountByte;

	/// Если влезает весь трек с момента смещения - забираем весь.
	if (	counByteInTreck - this->pointStartSeekBuffer
			< AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE	) {
		getCountByte = counByteInTreck - this->pointStartSeekBuffer;
	} else {
		/// Если весь не влезает, то хоть сколько влезает.
		getCountByte = AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE;
	}

	/// Смещаемся к нужному месту.
	r = AyPlayerFat::setOffsetByteInOpenFile( this->f, offsetByte );
	CHECK_ERROR( r );

	/// Забираем в буффер данные.
	r =  AyPlayerFat::readFromOpenFile( this->f, this->flashBuffer, getCountByte );
	CHECK_ERROR( r );

	this->pointInBuffer = 0;

	return 0;
}

int AyYmFilePlay::readInArray (	uint8_t*		returnDataBuffer,
								const uint32_t	countByteRead	) {
	int	r;

	/// Если то, что мы хотим считать уже есть в буффере.
	if ( this->pointInBuffer + countByteRead <= AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE ) {
		/// Просто копируем из массива и смещаем указатель.
		memcpy( returnDataBuffer, &this->flashBuffer[ this->pointInBuffer ], countByteRead );
		this->pointInBuffer += countByteRead;

		return 0;
	}

	/// Если мы не влезли, то придется скопировть часть из буффера, а часть загрузить из
	/// обновленного буфера (который еще надо обновить...).

	/// Копируем что есть.
	uint32_t fromBufferByte = AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE - this->pointInBuffer;
	memcpy( returnDataBuffer, &this->flashBuffer[ this->pointInBuffer ], fromBufferByte );

	/// Теперь буффер у нас на одно "окно" дальше.
	this->pointStartSeekBuffer += AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE;
	this->pointInBuffer	= 0;

	/// Далее будем класть уже после скопированного.
	uint8_t* nextPart = returnDataBuffer + fromBufferByte;

	/// Узнаем длину трека.
	uint32_t counByteInTreck;
	if ( AyPlayerFat::getSizeFromOpenTreck( this->f, counByteInTreck ) != 0 ) {
		AyPlayerFat::closeFile( this->f );
		return -1;
	}

	/// Решаем, сколько скопировать в буффер.
	UINT getCountByte;
	if (	counByteInTreck - this->pointStartSeekBuffer <
			AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE	) {
		getCountByte = counByteInTreck - this->pointStartSeekBuffer;
	} else {
		getCountByte = AY_YM_FILE_PLAY_FLASH_BUFFER_SIZE_BYTE;
	}

	/// Забираем в буффер данные.
	r = AyPlayerFat::readFromOpenFile( this->f, this->flashBuffer, getCountByte );
	CHECK_ERROR( r );

	/// Забираем оставшуюся часть.
	memcpy( nextPart, &this->flashBuffer[ this->pointInBuffer ], countByteRead - fromBufferByte );
	pointInBuffer += countByteRead - fromBufferByte;

	return 0;
}

int AyYmFilePlay::setPwrChip ( bool state ) {
	if ( state == true ) {
		pwrPin[ this->usingChip ].set( false );
		if ( this->usingChip == 0 ) {
			/// 40 PIN чип, надо включать оба...
			pwrPin[ 0 ].set( true );
			pwrPin[ 1 ].set( true );
		} else {
			pwrPin[ 0 ].set( true );
		}
	} else {
		pwrPin[ 0 ].set( false );
		pwrPin[ 1 ].set( false );
	}

	return 0;
}

int AyYmFilePlay::initChip ( void ) {
	this->ayLow->queueClear();
	this->ayLow->hardwareClear();
	this->ayLow->playStateSet( 1 );
	return 0;
}

int AyYmFilePlay::sleepChip ( const uint32_t countTick ) {
	int r;
	for ( uint32_t i = 0; i < countTick; i++ ) {
		r = this->writePacket( 0xFF, 0 );			/// 0xFF - знак паузы.
		if ( r != 0 )								/// Если была остановка или проблемы на нижнем уровне...
			return r;								///  - выходим.
	}
	return 0;
}

int AyYmFilePlay::writePacket (	const uint8_t	reg,
								const uint8_t	data ) {
	ayQueueStruct		s;
	s.data			=	data;
	s.reg			=	reg;
	s.numberChip	=	static_cast< uint8_t >( this->usingChip );

	while( 1 ) {
		CHECK_STOP();

		if ( this->ayLow->queueAddElement( &s ) == 0 )
			return 0;		/// Место в очереди есть, все хорошо.

		/// Если нет, снова смотрим флаги и ждем.
	}
}

void AyYmFilePlay::abort ( void ) {
	this->ayLow->playStateSet( 0 );				/// Отключаем аппаратку.
	this->setPwrChip( false );					/// Питание чипа.
	this->ayLow->queueClear();					/// Чистим очередь.
	AyPlayerFat::closeFile( this->f );			///	Хотя бы удаляем FIL-структуру.
}


