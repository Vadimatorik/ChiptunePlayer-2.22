#include "ayplayer.h"
#include "ayplayer_button.h"

void AyPlayer::powerOff (	CAUSE_SHUTDOWN	cause	) {
	if ( cause == CAUSE_SHUTDOWN::TIMEOUT ) {

	}

	if ( cause == CAUSE_SHUTDOWN::UNDERVOLTAGE ) {

	}

	if ( cause == CAUSE_SHUTDOWN::USER_OFF ) {

	}

	/// Остонавливаем ОС.
	vTaskEndScheduler();

	/// Отключаем питание.
	this->mcu->gpio->pwr.all_pwr->reset();
}
