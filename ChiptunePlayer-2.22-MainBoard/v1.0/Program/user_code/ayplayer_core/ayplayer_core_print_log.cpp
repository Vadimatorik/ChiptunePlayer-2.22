#include "ayplayer.h"

void AyPlayer::printMessageAndArg ( RTL_TYPE_M type, const char* const message, const char* const arg ) {
	const uint32_t lenPath				=	strlen( arg ) + 1;
	const uint32_t infoStringLen		=	strlen( message ) + 1;
	const uint32_t mallocByteGetValue	=	lenPath + infoStringLen;

	/// Открываем корень.
	char*		outputMessage;
	outputMessage = ( char* )pvPortMalloc( mallocByteGetValue );
	assertParam( outputMessage );

	sprintf( outputMessage, "%s\t%s", message, arg );

	this->l->sendMessage( type, outputMessage );

	vPortFree( outputMessage );
}
