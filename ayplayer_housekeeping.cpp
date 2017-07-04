#include "ayplayer_housekeeping.h"

/*
 * Каждые 500 мс мигаем светодиодом.
 */
void housekeeping_thread ( void* arg );

/*
 * Конфигурируем "домшнее хозяество".
 */
void ayplayer_housekeeping_init (void) {
    xTaskCreate( housekeeping_thread, "hous_th", 128, NULL, 3, NULL );        // Каждые 500 мс мигаем светодиодом.
}
