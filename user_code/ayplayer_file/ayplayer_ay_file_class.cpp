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

#define CHECK_RESULT(r)		if ( r != 0 ) {			\
								this->abort();		\
								return r;			\
							} else {				\
								return 0;			\
							}

#define CHECK_STOP()		if ( this->flagStop == true ) {	\
								this->abort();				\
								return -5;					\
							}

int AyYmFilePlay::openFile ( void ) {
	/// Сброс флагов.
	this->flagStop		=	false;
	this->f = AyPlayerFat::openFileInCurrentDir( this->sd, this->fileName );
	return ( this->f ) ? 0 : -1;
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
	CHECK_RESULT( r );
}

int AyYmFilePlay::setOffsetByteInFile ( const uint32_t offsetByte ) {
	int	r;
	r = AyPlayerFat::setOffsetByteInOpenFile( this->f, offsetByte );
	CHECK_RESULT( r );
}

int AyYmFilePlay::readInArray (	uint8_t*		returnDataBuffer,
								const uint32_t	countByteRead	) {
	int	r;
	r = AyPlayerFat::readFromOpenFile( this->f, returnDataBuffer, countByteRead );
	CHECK_RESULT( r );
}

int AyYmFilePlay::setPwrChip ( bool state ) {
	pwrPin[ this->usingChip ].set( state );
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


