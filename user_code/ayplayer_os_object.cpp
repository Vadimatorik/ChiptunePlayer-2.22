//**********************************************************************
// В данном файле содержатся все используемые FreeRTOS-ом элементы.
//**********************************************************************
#include "ayplayer_os_object.h"
#include "ay_ym_low_lavel.h"

//**********************************************************************
// Queue.
//**********************************************************************
USER_OS_STATIC_QUEUE                    q_play              = nullptr;
USER_OS_STATIC_QUEUE                    q_ay_low[2]         = { nullptr, nullptr };
USER_OS_STATIC_QUEUE                    q_ay_button         = nullptr;

//**********************************************************************
// Queue buffer.
//**********************************************************************
uint8_t                                 qb_play             [ sizeof( char* ) * 1 ]                                  = { 0 };
uint8_t                                 qb_ay_low           [2][ sizeof( ay_low_out_data_struct ) * QB_AY_LOW_SIZE ] = { 0 };
uint8_t                                 qb_ay_button        [ QB_BUTTON_SIZE ]                                       = { 0 };

//**********************************************************************
// Queue struct.
//**********************************************************************
USER_OS_STATIC_QUEUE_STRUCT             qs_play;
USER_OS_STATIC_QUEUE_STRUCT             qs_ay_low[2];
USER_OS_STATIC_QUEUE_STRUCT             qs_ay_button;

//**********************************************************************
// Mutex.
//**********************************************************************
// Mutex служит для предотвращения одновременной отрисовки окна Makise и
// смены окна container_set_to_mhost.
USER_OS_STATIC_MUTEX                    m_mhost             = nullptr;
USER_OS_STATIC_MUTEX                    m_spi3              = nullptr;

//**********************************************************************
// Mutex buffer.
//**********************************************************************
USER_OS_STATIC_MUTEX_BUFFER             mb_mhost;
USER_OS_STATIC_MUTEX_BUFFER             mb_spi3;

//**********************************************************************
// Semaphore.
//**********************************************************************
USER_OS_STATIC_BIN_SEMAPHORE            s_play_tic          = nullptr;
USER_OS_STATIC_BIN_SEMAPHORE            s_gui_update        = nullptr;

//**********************************************************************
// Semaphore buffer.
//**********************************************************************
USER_OS_STATIC_BIN_SEMAPHORE_BUFFER     sb_play_tic;
USER_OS_STATIC_BIN_SEMAPHORE_BUFFER     sb_gui_update;

//**********************************************************************
// Task stack (buffer).
//**********************************************************************
USER_OS_STATIC_STACK_TYPE               tb_play                     [ TB_PLAY_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_play_tic                 [ TB_PLAY_TIC_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_gui                      [ TB_GUI_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_gui_status_bar_update    [ TB_STATUS_BAR_UPDATE_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_inc_dec_detect           [ TB_B_INC_DEC_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_battery_check            [ TB_BATTERY_CHECK_SIZE ];
USER_OS_STATIC_STACK_TYPE               tb_housekeeping             [ TB_HOUSEKEEPING_SIZE ];

//**********************************************************************
// Task struct.
//**********************************************************************
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_play_tic;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_gui_status_bar_update;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_inc_dec_detect;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_battery_check;
USER_OS_STATIC_TASK_STRUCT_TYPE         ts_housekeeping;

//**********************************************************************
// Queue init.
//**********************************************************************
void q_play_init ( void ) {
    q_play = USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( char* ), qb_play, &qs_play );
}

void q_ay_low_init ( void ) {
    q_ay_low[0] = USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &qb_ay_low[0][0], &qs_ay_low[0] );
    q_ay_low[1] = USER_OS_STATIC_QUEUE_CREATE( QB_AY_LOW_SIZE, sizeof( ay_low_out_data_struct ), &qb_ay_low[1][0], &qs_ay_low[1] );
}

void q_ay_button_init ( void ) {
    q_ay_button = USER_OS_STATIC_QUEUE_CREATE( QB_BUTTON_SIZE, sizeof( uint8_t ), qb_ay_button, &qs_ay_button );
}


//**********************************************************************
// Semaphore init.
//**********************************************************************
void s_play_tic_init ( void ) {
    s_play_tic = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &sb_play_tic );
}

void s_gui_update_init ( void ) {
    s_gui_update = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &sb_gui_update );
}

//**********************************************************************
// Mutex init.
//**********************************************************************
void m_mhost_init ( void ) {
    m_mhost = USER_OS_STATIC_MUTEX_CREATE( &mb_mhost );
}

void m_spi3_init ( void ) {
    m_spi3 = USER_OS_STATIC_MUTEX_CREATE( &mb_spi3 );
}
