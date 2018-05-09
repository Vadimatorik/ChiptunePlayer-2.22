#include "ayplayer.h"

FRESULT AyPlayer::fatFsReinit( AY_MICROSD sd ) {
	FRESULT	r;

	switch( ( uint32_t )sd ) {
	case ( uint32_t )AY_MICROSD::SD1:
		r = f_mount( &this->fat.f[ 0 ], "0:", 1 );
		break;

	case ( uint32_t )AY_MICROSD::SD2:
		r = f_mount( &this->fat.f[ 1 ], "1:", 1 );
		break;

	default:
		return FRESULT::FR_INVALID_PARAMETER;
	};

	if ( r != FRESULT::FR_OK ) {
		this->errorMicroSdDraw( sd, r );
	} else {
		char massage[] = "FatFs connected witch SDX!";
		/// Пишем вместо X номер карты.
		massage[ sizeof( massage ) - 3 ] = '1' + ( uint32_t )sd;

		this->l->sendMessage( RTL_TYPE_M::INIT_OK, massage );
	}

	return r;
}
