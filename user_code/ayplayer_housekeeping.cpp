#include "ayplayer_housekeeping.h"

/*
 * Каждые 500 мс мигаем светодиодом.
 */
//extern microsd_spi sd2;

void housekeeping_thread ( void* arg ) {
    (void)arg;
    while( true ) {
        vTaskDelay(10000);
    }
}
// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       500
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
