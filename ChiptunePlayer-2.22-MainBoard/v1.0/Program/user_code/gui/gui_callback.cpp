#include "ayplayer.h"

extern AyPlayer						ay;

uint32_t ayplayerGetStatePlay ( void ) {
	return ay.getStatePlay();
}

extern uint32_t	ayplayerGetPercentBattery ( void ) {
	return ay.getPercentBattery();
}
