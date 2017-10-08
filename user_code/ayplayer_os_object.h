#pragma once

#include "user_os.h"

//**********************************************************************
// Размеры steck-ов задач.
//**********************************************************************
#define TB_PLAY_SIZE                    5000
#define TB_PLAY_TIC_SIZE                1000
#define TB_GUI_SIZE                     10000
#define TB_STATUS_BAR_UPDATE_SIZE       1000
#define TB_B_INC_DEC_SIZE               1000
#define TB_HOUSEKEEPING_SIZE            1000
#define TB_BATTERY_CHECK_SIZE           1000

//**********************************************************************
// Приоритеты задач.
//**********************************************************************
#define GUI_CORE_TASK_PRIO              3
#define GUI_UPDATE_TASK_PRIO            2






#define QB_BUTTON_SIZE                  1


// В этих очередях содержатся данные для каждого AY.
// Они (данные) будут выдаваться в прерывании с заданной частотой.
#define QB_AY_LOW_SIZE                   128

//**********************************************************************
// Queue.
//**********************************************************************
extern USER_OS_STATIC_QUEUE                    q_play;
extern USER_OS_STATIC_QUEUE                    q_ay_low[2];
extern USER_OS_STATIC_QUEUE                    q_ay_button;

//**********************************************************************
// Mutex.
//**********************************************************************
extern USER_OS_STATIC_MUTEX                    m_mhost;
extern USER_OS_STATIC_MUTEX                    m_spi3;

//**********************************************************************
// Semaphore.
//**********************************************************************
extern USER_OS_STATIC_BIN_SEMAPHORE            s_play_tic;
extern USER_OS_STATIC_BIN_SEMAPHORE            s_gui_update;

//**********************************************************************
// Task stack (buffer).
//**********************************************************************
extern USER_OS_STATIC_STACK_TYPE               tb_play                      [ TB_PLAY_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_play_tic                  [ TB_PLAY_TIC_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_gui                       [ TB_GUI_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_gui_status_bar_update     [ TB_STATUS_BAR_UPDATE_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_inc_dec_detect            [ TB_B_INC_DEC_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_battery_check             [ TB_BATTERY_CHECK_SIZE ];
extern USER_OS_STATIC_STACK_TYPE               tb_housekeeping              [ TB_HOUSEKEEPING_SIZE ];

//**********************************************************************
// Task struct.
//**********************************************************************
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play_tic;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui_status_bar_update;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_inc_dec_detect;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_battery_check;
extern USER_OS_STATIC_TASK_STRUCT_TYPE         ts_housekeeping;

//**********************************************************************
// Queue init.
//**********************************************************************
void q_play_init                    ( void );
void q_ay_low_init                  ( void );
void q_ay_button_init               ( void );

//**********************************************************************
// Semaphore init.
//**********************************************************************
void s_play_tic_init                ( void );
void s_gui_update_init              ( void );

//**********************************************************************
// Mutex init.
//**********************************************************************
void m_mhost_init                   ( void );
void m_spi3_init                    ( void );
