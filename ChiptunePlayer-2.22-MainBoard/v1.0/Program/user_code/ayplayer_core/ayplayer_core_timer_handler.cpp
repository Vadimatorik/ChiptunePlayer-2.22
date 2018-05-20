#include "ayplayer.h"
#include "ayplayer_button.h"

/// Вызывается только когда активно основное окно.
void AyPlayer::scrollNameInMainWindow ( TimerHandle_t timer ) {
	AyPlayer* o = ( AyPlayer* )pvTimerGetTimerID( timer );

	int r;
	r = mSlimHorizontalListScrollString( o->g.shl );

	if ( r != 1 ) {
		if ( USER_OS_STATIC_TIMER_GET_PERIOD( timer ) == SCROLL_STRING_NAME_LOW ) {
			USER_OS_STATIC_TIMER_CHANGE_PERIOD(timer, SCROLL_STRING_NAME_FAST);
		}
	} else {
		USER_OS_STATIC_TIMER_CHANGE_PERIOD(timer, SCROLL_STRING_NAME_LOW);
	}

	o->guiUpdate();
}
