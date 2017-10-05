#include "ayplayer_battery_check.h"

extern ayplayer_state ayplayer_control;

static void battery_check_thread ( void* arg ) {
    ( void )arg;
    uint32_t        adc_value   = 0;

    adc_input.start_continuous_conversion();

    while ( true ) {
        // ВАЖНО! Из-за проеба в схеме мы не можем детектировать напряжение меньше 3.4 с погрешностью (3.5).
        // Т.к. МК питается от LDO. А он напрямую от  Li-ION. А т.к. резистор стоит на 2 (резисторный делитель),
        // то ловить мы можем максимум 1.65 В и выше. Но для питания от Li-ION большего и не нужно.
        USER_OS_DELAY_MS( 10 );
        adc_input.get_measurement( adc_value );
        float battery_voltage = adc_value * 3.3 / 4096 * 2;
        ayplayer_control.battery_voltage_set( battery_voltage );
    }
}

void ayplayer_battery_check_init ( void ) {
    USER_OS_STATIC_TASK_CREATE( battery_check_thread, "bat_chack", TB_BATTERY_CHECK_SIZE, NULL, 2, tb_battery_check, &ts_battery_check );
}
