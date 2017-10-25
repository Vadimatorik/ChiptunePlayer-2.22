#include "play_task.h"

//**********************************************************************
// Задача ожидает появления в очереди указателя на полный путь до файла,
// который требуется воспроизвести и пытается воспроизвести его.
// После открытия файла - строка с его именем не нужна.
//**********************************************************************
static void ayplayer_play_task ( void* p_obj ) {
    ( void )p_obj;
    char* name;
    EC_AY_FILE_MODE_ANSWER  r;
    while ( true ) {
        USER_OS_QUEUE_RECEIVE( q_play, &name, portMAX_DELAY );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::PLAY );
        r = ay_file_mode.psg_file_play( name, 1 );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::STOP );

        // Переходим на следующий трек.
        if ( r == EC_AY_FILE_MODE_ANSWER::TRACK_END ) {
      //      m_click_play_list( &gui_pl, M_KEY_DOWN );
       //     m_click_play_list( &gui_pl, M_KEY_OK );
            gui_update();
        }
    }
}

//**********************************************************************
// Задача ожэидает, когда пройдет одни секунда файла, чтобы увеличить
// счетчик секунд и прогресс бара.
//**********************************************************************
extern MPlayBar gui_e_pb;
extern ayplayer_state ayplayer_control;
static void ayplayer_play_tic ( void* p_obj ) {
    ( void )p_obj;
    while ( true ) {
        USER_OS_TAKE_BIN_SEMAPHORE( s_play_tic, portMAX_DELAY );
        m_play_bar_inc_sec( &gui_e_pb );
        if ( ayplayer_control.active_window_get() == EC_AY_ACTIVE_WINDOW::MAIN ) {
            gui_update();
        }
    }
}

void ayplayer_play_task_init ( void ) {
    q_play_init();
    s_play_tic_init();
    USER_OS_STATIC_TASK_CREATE( ayplayer_play_task, "ay_play", TB_PLAY_SIZE, nullptr, 4, tb_play, &ts_play );
    USER_OS_STATIC_TASK_CREATE( ayplayer_play_tic, "play_tic", TB_PLAY_TIC_SIZE, nullptr, 3, tb_play_tic, &ts_play_tic );
}
