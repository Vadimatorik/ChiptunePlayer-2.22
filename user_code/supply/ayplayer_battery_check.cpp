#include "ayplayer_battery_check.h"

static StaticTask_t     ayplayer_battery_check_task_buffer;
static StackType_t      ayplayer_battery_check_task_stack[ AY_PLAYER_BATTERY_CHECK_TASK_STACK_SIZE ];

extern ayplayer_state ayplayer_control;

static void battery_check_thread ( void* arg ) {
    ( void )arg;
    uint32_t        adc_value;
    while ( true ) {
        adc_input.start_measurement();
        USER_OS_DELAY_MS( 10 );
        adc_input.get_measurement( adc_value );
        uint32_t battery_voltage_mv;
        battery_voltage_mv = adc_value * 3300 / 255 * 2;
        ayplayer_control.battery_voltage_mv_set( battery_voltage_mv );
        USER_OS_DELAY_MS( 990 );
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
