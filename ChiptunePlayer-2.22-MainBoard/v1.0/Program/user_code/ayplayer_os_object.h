#pragma once

#include "ay_ym_low_lavel.h"
#include "user_os.h"

// В этих очередях содержатся данные для каждого AY.
// Они (данные) будут выдаваться в прерывании с заданной частотой.
#define QB_AY_LOW_SIZE					64

struct freeRtosObj {
	/// Queue.
	USER_OS_STATIC_QUEUE					qAyLow[2];
	USER_OS_STATIC_QUEUE					qAyButton;

	/// Queue buffer.
	uint8_t									qbAyLow[2][ sizeof( ayLowOutDataStruct ) * QB_AY_LOW_SIZE ];
	uint8_t									qbAyButton[ 1 ];

	/// Queue struct.
	USER_OS_STATIC_QUEUE_STRUCT				qsAyLow[2];
	USER_OS_STATIC_QUEUE_STRUCT				qsAyButton;

	/// Mutex.
	USER_OS_STATIC_MUTEX					mSpi3;
	USER_OS_STATIC_MUTEX					mHost;

	/// Mutex buffer.
	USER_OS_STATIC_MUTEX_BUFFER				mbSpi3;
	USER_OS_STATIC_MUTEX_BUFFER				mbHost;

	/// Semaphore.
	USER_OS_STATIC_BIN_SEMAPHORE			sPlayTic;
	USER_OS_STATIC_BIN_SEMAPHORE			sStartPlay;

	/// Semaphore buffer.
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		sbPlayTic;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		sbStartPlay;			/// Выдается, когда надо запустить воспроизведение,
																	///а все данные о треке уже указаны (внутри объекта ayplayer).
};
