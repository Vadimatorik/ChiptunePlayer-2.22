#include "ayplayer.h"
#include "ayplayer_button.h"


void AyPlayer::start ( void ) {
	/*!
	 * Основной поток проекта.
	 */
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::mainTask,
								"main",
								TB_MAIN_TASK_SIZE,
								( void* )this,
								MAIN_TASK_PRIO,
								this->tbMainTask,
								&this->tsMainTask );

	/*!
	 * Контроль подсветки экрана.
	 */
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::illuminationControlTask,
								"illuminationControl",
								TB_ILLUMINATION_CONTROL_TASK_SIZE,
								( void* )this,
								ILLUMINATION_CONTROL_TASK_PRIO,
								this->tbIlluminationControlTask,
								&this->tsIlluminationControlTask	);

	/// Обработка нажатой клавиши.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::buttonClickHandlerTask,
								"buttonClickHandler",
								TB_BUTTON_CLICK_HANDLER_TASK_SIZE,
								( void* )this,
								BUTTON_CLICK_HANDLER_TASK_PRIO,
								this->tbButtonClickHandlerTask,
								&this->tsButtonClickHandlerTask	);

	/// Воспроизведение трека.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::playTask,
								"play",
								TB_PLAY_TASK_SIZE,
								( void* )this,
								PLAY_TASK_PRIO,
								this->tbPlayTask,
								&this->tsPlayTask	);

	/// Обновление плей-бара при прохождении секунды.
	USER_OS_STATIC_TASK_CREATE(	AyPlayer::playTickHandlerTask,
								"playTick",
								TB_PLAY_TICK_TASK_SIZE,
								( void* )this,
								PLAY_TICK_TASK_PRIO,
								this->tbPlayTickTask,
								&this->tsPlayTickTask	);

	/// Прокрутка строки.
	this->timNameScroll = USER_OS_STATIC_TIMER_CREATE(	"ScrollStringName",
														1000,
														( void* )this,
														AyPlayer::scrollNameInMainWindow,
														&this->timStNameScroll	);

	USER_OS_STATIC_TIMER_START( this->timNameScroll );

	vTaskStartScheduler();
}
