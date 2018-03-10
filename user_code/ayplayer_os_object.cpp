//**********************************************************************
// В данном файле содержатся все используемые FreeRTOS-ом элементы.
//**********************************************************************
#include "ayplayer_os_object.h"
#include "ay_ym_low_lavel.h"

/*
 q_play = USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( char* ), qb_play, &qs_play );

q_ay_low[0] = USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &qb_ay_low[0][0], &qs_ay_low[0] );
q_ay_low[1] = USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &qb_ay_low[1][0], &qs_ay_low[1] );
	q_ay_button = USER_OS_STATIC_QUEUE_CREATE( QB_BUTTON_SIZE, sizeof( uint8_t ), qb_ay_button, &qs_ay_button );

	/// Semaphore init.
	s_play_tic = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &sb_play_tic );
	s_gui_update = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &sb_gui_update );

	/// Mutex init.
	m_mhost = USER_OS_STATIC_MUTEX_CREATE( &mb_mhost );
    m_spi3 = USER_OS_STATIC_MUTEX_CREATE( &mb_spi3 );
}
*/
