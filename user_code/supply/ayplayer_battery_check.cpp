#include "ayplayer_battery_check.h"

static StaticTask_t     ayplayer_battery_check_task_buffer;
static StackType_t      ayplayer_battery_check_task_stack[ AY_PLAYER_BATTERY_CHECK_TASK_STACK_SIZE ];

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
    xTaskCreateStatic( battery_check_thread,
                       "bat_chack",
                       AY_PLAYER_BATTERY_CHECK_TASK_STACK_SIZE,
                       NULL,
                       2,
                       ayplayer_battery_check_task_stack,
                       &ayplayer_battery_check_task_buffer );
}
