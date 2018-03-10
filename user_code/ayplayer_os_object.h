#pragma once

#include "user_os.h"

/*
// Размеры steck-ов задач.
#define TB_PLAY_SIZE                    5000
#define TB_PLAY_TIC_SIZE                1000
#define TB_GUI_SIZE                     5000
#define TB_STATUS_BAR_UPDATE_SIZE       1000
#define TB_B_INC_DEC_SIZE               200
#define TB_HOUSEKEEPING_SIZE            1000
#define TB_BATTERY_CHECK_SIZE           1000


// Приоритеты задач.

#define CORE_TASK_PRIO              	3
#define GUI_UPDATE_TASK_PRIO            2

#define QB_BUTTON_SIZE                  1

// В этих очередях содержатся данные для каждого AY.
// Они (данные) будут выдаваться в прерывании с заданной частотой.
#define QB_AY_LOW_SIZE                   128

struct ay_player_freertos_obj_strcut {
	/// Queue.
	USER_OS_STATIC_QUEUE                    q_play;
	USER_OS_STATIC_QUEUE                    q_ay_low[2];
	USER_OS_STATIC_QUEUE                    q_ay_button;

	/// Queue buffer.
	uint8_t                                 qb_play[ sizeof( char* ) * 1 ];
	uint8_t                                 qb_ay_low[2][ sizeof( ay_low_out_data_struct ) * QB_AY_LOW_SIZE ];
	uint8_t                                 qb_ay_button[ QB_BUTTON_SIZE ];

	/// Queue struct.
	USER_OS_STATIC_QUEUE_STRUCT             qs_play;
	USER_OS_STATIC_QUEUE_STRUCT             qs_ay_low[2];
	USER_OS_STATIC_QUEUE_STRUCT             qs_ay_button;

	/// Mutex.
	/// Mutex служит для предотвращения одновременной отрисовки окна Makise и
	/// смены окна container_set_to_mhost.
	USER_OS_STATIC_MUTEX                    m_mhost;
	USER_OS_STATIC_MUTEX                    m_spi3;

	/// Semaphore.
	USER_OS_STATIC_BIN_SEMAPHORE            s_play_tic;
	USER_OS_STATIC_BIN_SEMAPHORE            s_gui_update;

	/// Semaphore buffer.
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER     sb_play_tic;
	USER_OS_STATIC_BIN_SEMAPHORE_BUFFER     sb_gui_update;

	/// Task stack (buffer).
	USER_OS_STATIC_STACK_TYPE               tb_play                     [ TB_PLAY_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_play_tic                 [ TB_PLAY_TIC_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_gui                      [ TB_GUI_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_gui_status_bar_update    [ TB_STATUS_BAR_UPDATE_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_inc_dec_detect           [ TB_B_INC_DEC_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_battery_check            [ TB_BATTERY_CHECK_SIZE ];
	USER_OS_STATIC_STACK_TYPE               tb_housekeeping             [ TB_HOUSEKEEPING_SIZE ];

	/// Task struct.
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play_tic;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui_status_bar_update;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_inc_dec_detect;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_battery_check;
	USER_OS_STATIC_TASK_STRUCT_TYPE         ts_housekeeping;
}*/
