#include "ayplayer_housekeeping.h"


void housekeeping_thread ( void* arg ) {
    (void)arg;
    // Минимальное время, чтобы напряжениен а схеме установилось и можно было считать, что плеер включили.
    vTaskDelay(300);
    pwr_on_pin_obj.set();
    while( true ) {
        vTaskDelay(10000);
    }
}

//**********************************************************************
// Конфигурируем "домшнее хозяество".
//**********************************************************************
void ayplayer_housekeeping_init ( void ) {
    USER_OS_STATIC_TASK_CREATE( housekeeping_thread, "hous", TB_HOUSEKEEPING_SIZE, NULL, 1, tb_housekeeping, &ts_housekeeping );
}
