#include "ayplayer_housekeeping.h"

/*
 * Каждые 500 мс мигаем светодиодом.
 */
void housekeeping_thread ( void* arg ) {
    (void) arg;
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    uint8_t out = 0;
    while (1) {
       // spi1.tx ( out );
       // spi1.rx( in );
        out++;
        vTaskDelayUntil( &xLastWakeTime, 500 );
    }
}

/*
 * Конфигурируем "домшнее хозяество".
 */
void ayplayer_housekeeping_init (void) {
    xTaskCreate( housekeeping_thread, "hous_th", 128, NULL, 3, NULL );        // Каждые 500 мс мигаем светодиодом.
}
