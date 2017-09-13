#include "ayplayer_battery_check.h"

static StaticTask_t     ayplayer_battery_check_task_buffer;
static StackType_t      ayplayer_battery_check_task_stack[ AY_PLAYER_BATTERY_CHECK_TASK_STACK_SIZE ];

extern ayplayer_state ayplayer_control;

static void battery_check_thread ( void* arg ) {
    ( void )arg;
    uint32_t        adc_value   = 0;

    float        adc_res_array[100] = { 0 };
    for ( int i = 0; i < 100; i++ ) {
        adc_input.start_measurement();
        USER_OS_DELAY_MS( 1 );
        adc_input.get_measurement( adc_value );
        adc_res_array[i] = adc_value;
        i++;
    }

    uint32_t i = 0;
    while ( true ) {
        adc_input.start_measurement();
        USER_OS_DELAY_MS( 1 );

        adc_input.get_measurement( adc_value );
        adc_res_array[i] = adc_value;



        float adc_sr = 0;
        for ( int i = 0; i < 100; i++ ) {
            adc_sr += adc_res_array[i];
        }
        adc_sr /= (float)100;

        uint32_t battery_voltage;
        battery_voltage = adc_sr * (float)3300 / (float)4096 * (float)2;
        ayplayer_control.battery_voltage_set( battery_voltage );

        i++;
        if ( i == 100 ) i = 0;
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
