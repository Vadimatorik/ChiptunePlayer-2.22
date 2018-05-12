#include "ayplayer.h"

uint32_t AyPlayer::getStatePlay ( void ) {
	return static_cast< uint32_t >( this->playState );
}

uint32_t AyPlayer::getPercentBattery ( void ) {
	return 0;
}
