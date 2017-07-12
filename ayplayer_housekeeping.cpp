#include "ayplayer_housekeeping.h"
#include "ayplayer_ay_note.h"               // Потом выпелить!
/*
 * Каждые 500 мс мигаем светодиодом.
 */
void housekeeping_thread ( void* arg ) {
    (void)arg;
    ayplayer_note_mode.write_note_to_channel( 0, 0, 40 );
    ayplayer_note_mode.write_note_to_channel( 0, 1, 20 );
    ayplayer_note_mode.write_note_to_channel( 0, 2, 30 );

    ayplayer_note_mode.set_volume_channel( 0, 0, 10 );
    ayplayer_note_mode.set_volume_channel( 0, 1, 10 );
    ayplayer_note_mode.set_volume_channel( 0, 2, 10 );

    ayplayer_note_mode.write_note_to_channel( 1, 0, 40 );
    ayplayer_note_mode.write_note_to_channel( 1, 1, 50 );
    ayplayer_note_mode.write_note_to_channel( 1, 2, 60 );

    ayplayer_note_mode.set_volume_channel( 1, 0, 10 );
    ayplayer_note_mode.set_volume_channel( 1, 1, 10 );
    ayplayer_note_mode.set_volume_channel( 1, 2, 10 );

    while( true ) {
        vTaskDelay(1000);
    }
}

// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       200
static StaticTask_t     ayplayer_housekeeping_task_buffer;
static StackType_t      ayplayer_housekeeping_task_stack[ AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE ];

/*
 * Конфигурируем "домшнее хозяество".
 */
void ayplayer_housekeeping_init ( void ) {
    xTaskCreateStatic( housekeeping_thread,
                       "hous",
                       AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE,
                       NULL,
                       1,
                       ayplayer_housekeeping_task_stack,
                       &ayplayer_housekeeping_task_buffer );
}
