#include "ayplayer.h"

extern "C" {

extern MHost				makiseHost;

}

bool AyPlayer::checkSd ( AY_MICROSD sd ) {
	/// Если тип карты определен, значит она есть в слоте.
	if ( this->pcb->sd[ (uint32_t)sd ]->getStatus() != EC_SD_STATUS::NOINIT )
		return true;

	if ( this->pcb->sd[ (uint32_t)sd ]->initialize() != EC_MICRO_SD_TYPE::ERROR ) {
		return true;
	} else {
		return false;
	}
}

void AyPlayer::waitSdCardInsert ( void ) {
	/*!
	 * -1	-	первое сканирование.
	 * 0	-	отсуствует.
	 * 1	-	обнаружена.
	 */
	int flagMicroSd1Present = -1;
	int flagMicroSd2Present = -1;

	do {
		if ( this->checkSd( AY_MICROSD::SD1 ) ) {
			if ( flagMicroSd1Present != 1 ) {
				flagMicroSd1Present = 1;
				this->l->sendMessage( RTL_TYPE_M::INIT_OK, "SD1 is detected!" );
			}
		} else {
			if ( flagMicroSd1Present != 0 ) {
				flagMicroSd1Present = 0;

				this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD1 missing!" );

				const char SD1_NOT_PRESENT[]	=	"SD1 not present!";

				/// Создаем временный граф. объект.
				MMessageWindow*			m;
				m	=	( MMessageWindow* )pvPortMalloc( sizeof( MMessageWindow ) );
				assertParam( m );


				m_create_message_window(	m,
											&makiseHost.host,
											mp_rel( 0,	11,
													128, 64 - 11 ),
											( char* )SD1_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();

				makise_g_cont_rem( &m->el );
				vPortFree( m );
			}

			vTaskDelay( 100 );
			continue;
		}

		if ( this->checkSd( AY_MICROSD::SD2 ) ) {
			if ( flagMicroSd2Present != 1 ) {
				flagMicroSd2Present = 1;
				this->l->sendMessage( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
			}
		} else {
			if ( flagMicroSd2Present != 0 ) {
				flagMicroSd2Present = 0;

				this->l->sendMessage( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" );

				const char SD2_NOT_PRESENT[]	=	"SD2 not present!";

				/// Создаем временный граф. объект.
				MMessageWindow*			m;
				m	=	( MMessageWindow* )pvPortMalloc( sizeof( MMessageWindow ) );
				assertParam( m );

				m_create_message_window(	m,
											&makiseHost.host,
											mp_rel( 0,	11,
													128, 64 - 11 ),
											( char* )SD2_NOT_PRESENT,
											( MakiseStyle_SMessageWindow* )&this->gui->smw );
				this->guiUpdate();

				makise_g_cont_rem( &m->el );
				vPortFree( m );
			}

			vTaskDelay( 100 );
			continue;
		}

	} while( !( flagMicroSd1Present && flagMicroSd2Present ) );
}

void AyPlayer::waitSdCardDisconnect ( const AY_MICROSD sd ) {
	while( true ) {
		if ( this->pcb->sd[ (uint32_t)sd ]->getStatus() != EC_SD_STATUS::OK )
			break;
	}

	char	massage[] = "SDX was been disconnect.";

	if ( sd == AY_MICROSD::SD1 ) {
		massage[ 2 ]	=	'1';
	} else {
		massage[ 2 ]	=	'2';
	}

	this->l->sendMessage( RTL_TYPE_M::INIT_OK, massage );

}
