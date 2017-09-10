#include "play_task.h"

static USER_OS_STATIC_STACK_TYPE           ayplayer_play_task_stack[ AY_PLAYER_PLAY_TASK_STACK_SIZE ];
static USER_OS_STATIC_TASK_STRUCT_TYPE     ayplayer_play_task_struct;

static USER_OS_STATIC_STACK_TYPE           ayplayer_play_tic_task_stack[ AY_PLAYER_PLAY_TIC_TASK_STACK_SIZE ];
static USER_OS_STATIC_TASK_STRUCT_TYPE     ayplayer_play_tic_task_struct;

static USER_OS_STATIC_BIN_SEMAPHORE_BUFFER ayplayer_play_tic_semaphore_buf;
       USER_OS_STATIC_BIN_SEMAPHORE        ayplayer_play_tic_semaphore;

extern ay_ym_file_mode ay_file_mode;

uint8_t                         ayplayer_play_queue_buf[ sizeof( char* ) * 1 ];
USER_OS_STATIC_QUEUE_STRUCT     ayplayer_play_queue_st;
USER_OS_STATIC_QUEUE            ayplayer_play_queue;

//**********************************************************************
// Задача ожидает появления в очереди указателя на полный путь до файла,
// который требуется воспроизвести и пытается воспроизвести его.
// После открытия файла - строка с его именем не нужна.
//**********************************************************************
extern USER_OS_STATIC_MUTEX         spi2_mutex;
extern ayplayer_state               ayplayer_control;
extern MPlayList                    gui_pl;
extern MHost                        host;

static void ayplayer_play_task ( void* p_obj ) {
    ( void )p_obj;
    char* name;
    EC_AY_FILE_MODE_ANSWER  r;
    while ( true ) {
        USER_OS_QUEUE_RECEIVE( ayplayer_play_queue, &name, portMAX_DELAY );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::PLAY );
        r = ay_file_mode.psg_file_play( name, 1 );
        ayplayer_control.play_state_set( EC_AY_PLAY_STATE::STOP );

        // Переходим на следующий трек.
        if ( r == EC_AY_FILE_MODE_ANSWER::TRACK_END ) {
            m_click_play_list( &gui_pl, M_KEY_DOWN );
            m_click_play_list( &gui_pl, M_KEY_OK );
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
        USER_OS_TAKE_BIN_SEMAPHORE( ayplayer_play_tic_semaphore, portMAX_DELAY );
        m_play_bar_inc_sec( &gui_e_pb );
        if ( ayplayer_control.active_window_get() == EC_AY_ACTIVE_WINDOW::MAIN ) {
            gui_update();
        }
    }
}

void ayplayer_play_task_init ( void ) {
    ayplayer_play_queue         = USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( char* ), ayplayer_play_queue_buf, &ayplayer_play_queue_st );
    ayplayer_play_tic_semaphore = USER_OS_STATIC_BIN_SEMAPHORE_CREATE( &ayplayer_play_tic_semaphore_buf );

    USER_OS_STATIC_TASK_CREATE( ayplayer_play_task, "ay_play", AY_PLAYER_PLAY_TASK_STACK_SIZE, nullptr, 4, ayplayer_play_task_stack, &ayplayer_play_task_struct );
    USER_OS_STATIC_TASK_CREATE( ayplayer_play_tic, "play_tic", AY_PLAYER_PLAY_TIC_TASK_STACK_SIZE, nullptr, 3, ayplayer_play_tic_task_stack, &ayplayer_play_tic_task_struct );
}
