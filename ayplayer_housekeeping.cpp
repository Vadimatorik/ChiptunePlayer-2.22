#include "ayplayer_housekeeping.h"

/*
 * Каждые 500 мс мигаем светодиодом.
 */
void housekeeping_thread ( void* arg ) {
    (void) arg;
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    uint8_t out[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    while (1) {
        spi1.tx ( ( void* )out, 10, 10 );
       // spi1.rx( in );
        out[0]++;
        vTaskDelayUntil( &xLastWakeTime, 500 );
    }
}

/*
 * Конфигурируем "домшнее хозяество".
 */
void ayplayer_housekeeping_init (void) {
    xTaskCreate( housekeeping_thread, "hous_th", 128, NULL, 3, NULL );        // Каждые 500 мс мигаем светодиодом.
}
