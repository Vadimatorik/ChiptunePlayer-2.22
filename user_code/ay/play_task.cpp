#include "play_task.h"

static USER_OS_STATIC_STACK_TYPE           ayplayer_play_task_stack[ AY_PLAYER_PLAY_TASK_STACK_SIZE ];
static USER_OS_STATIC_TASK_STRUCT_TYPE     ayplayer_play_task_struct;

extern ay_ym_file_mode ay_file_mode;

uint8_t                         ayplayer_play_queue_buf[ sizeof( char* ) * 1 ];
USER_OS_STATIC_QUEUE_STRUCT     ayplayer_play_queue_st;
USER_OS_STATIC_QUEUE            ayplayer_play_queue;

//**********************************************************************
// Задача ожидает появления в очереди указателя на полный путь до файла,
// который требуется воспроизвести и пытается воспроизвести его.
// После открытия файла - строка с его именем не нужна.
//**********************************************************************
extern USER_OS_STATIC_MUTEX        spi2_mutex;

char sss[] = "MmcM - Its life (2003).psg";

static void ayplayer_play_task ( void* p_obj ) {
    ( void )p_obj;
    char* name;
    while ( true ) {
        USER_OS_QUEUE_RECEIVE( ayplayer_play_queue, &name, portMAX_DELAY );
        USER_OS_TAKE_MUTEX( spi2_mutex, portMAX_DELAY );    // sdcard занята нами.
        ay_file_mode.psg_file_play( sss, 0 );
        USER_OS_GIVE_MUTEX( spi2_mutex );

    }
}

void ayplayer_play_task_init ( void ) {
    ayplayer_play_queue = USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( char* ), ayplayer_play_queue_buf, &ayplayer_play_queue_st );
    USER_OS_STATIC_TASK_CREATE( ayplayer_play_task, "ay_play", AY_PLAYER_PLAY_TASK_STACK_SIZE, nullptr, 4, ayplayer_play_task_stack, &ayplayer_play_task_struct );
}
