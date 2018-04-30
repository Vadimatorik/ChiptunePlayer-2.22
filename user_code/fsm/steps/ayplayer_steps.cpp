#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"
#include "makise.h"
#include "makise_gui.h"
#include "ff.h"
#include "diskio.h"

#include "ayplayer_microsd_card.h"

/*
static int writeDataOfTreck ( FIL& f, char* nameTreck, uint32_t& len ) {
	int					intResult;
	UINT				writingByte;

	intResult = f_write( &f, nameTreck, 256, &writingByte );

	if ( intResult == FR_DISK_ERR ) {
		return 1;
	}

	if ( writingByte != 256 ) {
		return 1;
	}

	intResult = f_write( &f, &len, 4, &writingByte );

	if ( intResult == FR_DISK_ERR ) {
		return 1;
	}

	if ( writingByte != 4 ) {
		return 1;
	}

	return 0;
}

int ay_player_class::fsm_step_func_create_playlist_sys ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );


}
*/

