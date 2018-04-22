#pragma once

#include "ay_ym_low_lavel.h"
#include "user_os.h"

// В этих очередях содержатся данные для каждого AY.
// Они (данные) будут выдаваться в прерывании с заданной частотой.
#define QB_AY_LOW_SIZE					32

struct ay_player_freertos_obj_strcut {
	/// Queue.
	USER_OS_STATIC_QUEUE					q_ay_low[2];
	USER_OS_STATIC_QUEUE					q_ay_button;

	/// Queue buffer.
	uint8_t									qb_ay_low[2][ sizeof( ayLowOutDataStruct ) * QB_AY_LOW_SIZE ];
	uint8_t									qb_ay_button[ 1 ];

	/// Queue struct.
	USER_OS_STATIC_QUEUE_STRUCT				qs_ay_low[2];
	USER_OS_STATIC_QUEUE_STRUCT				qs_ay_button;

	/// Mutex.
	USER_OS_STATIC_MUTEX					m_spi3;
	USER_OS_STATIC_MUTEX					m_host;

	/// Mutex buffer.
	USER_OS_STATIC_MUTEX_BUFFER				mb_spi3;
	USER_OS_STATIC_MUTEX_BUFFER				mb_host;

	/// Semaphore.
	USER_OS_STATIC_BIN_SEMAPHORE			s_play_tic;
	USER_OS_STATIC_BIN_SEMAPHORE			s_gui_update;

	/// Semaphore buffer.
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		sb_play_tic;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		sb_gui_update;
};
