#include "ayplayer_battery_check.h"

static StaticTask_t     ayplayer_battery_check_task_buffer;
static StackType_t      ayplayer_battery_check_task_stack[ AY_PLAYER_BATTERY_CHECK_TASK_STACK_SIZE ];

static void battery_check_thread ( void* arg ) {
    ( void )arg;
    uint32_t        adc_value;
    while ( true ) {
        adc_input.start_measurement();
        USER_OS_DELAY_MS( 10 );
        adc_input.get_measurement( adc_value );
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
