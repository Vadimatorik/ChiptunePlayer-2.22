#include "ayplayer_housekeeping.h"

/*
 * filemode
 */
/*

*/

/*
 * Потенциометры
 */
void out_reg ( uint8_t reg2, uint8_t value2, uint8_t reg1, uint8_t value1) {
    uint8_t buf[3] = {0};
    buf[0] = reg2 << 3;
    buf[0] |= value2 >> 5;
    buf[1] = value2 << 3;
    buf[1] |= reg1;
    buf[2] = value1;
    dp_cs_res_obj.reset();
    spi3.tx(&buf[0], 1, 100);
    spi3.tx(&buf[1], 1, 100);
    spi3.tx(&buf[2], 1, 100);
    dp_cs_res_obj.set();
}
/*
 * Каждые 500 мс мигаем светодиодом.
 */
//extern microsd_spi sd2;

#include "ayplayer_digital_potentiometer.h"



//extern ay_ym_low_lavel ay;
extern USER_OS_STATIC_MUTEX spi3_mutex;

void housekeeping_thread ( void* arg ) {
    (void)arg;

    //vTaskDelay(2000);
    /*
    sound_dp.connect_off();
    sound_dp.value_set( 0, 0, 0x80 );
    sound_dp.value_set( 0, 1, 0x80 );
    sound_dp.value_set( 0, 2, 0x80 );
    sound_dp.value_set( 0, 3, 0x80 );

    sound_dp.value_set( 0, 0, 0x80 );
    sound_dp.value_set( 1, 1, 0x80 );
    sound_dp.value_set( 2, 2, 0x80 );
    sound_dp.value_set( 3, 3, 0x80 );
    sound_dp.connect_on();
*/
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );    // sdcard занята нами.

        out_reg( 0, 0x80, 0, 0x80 );
       vTaskDelay(10);
        out_reg( 1, 0x80, 1, 0x80 );
        vTaskDelay(10);
        out_reg( 2, 0x80, 2, 0x80 );
        vTaskDelay(10);
        out_reg( 3, 0x80, 3, 0x80 );
        vTaskDelay(10);
        shdn_obj.set();
    USER_OS_GIVE_MUTEX( spi3_mutex );



/*
    ayplayer_note_mode.reinit( 1 );
    ayplayer_note_mode.reinit( 0 );

    ayplayer_note_mode.write_note_to_channel( 1, 2, 50 );   vTaskDelay(1000);
    ayplayer_note_mode.set_volume_channel( 1, 2, 15 );vTaskDelay(1000);

    ayplayer_note_mode.write_note_to_channel( 1, 0, 40 );   vTaskDelay(1000);
    ayplayer_note_mode.set_volume_channel( 1, 20, 15 );  vTaskDelay(1000);

    ayplayer_note_mode.write_note_to_channel( 1, 1, 60 );   vTaskDelay(1000);
     ayplayer_note_mode.set_volume_channel( 1, 1, 15 );vTaskDelay(1000);*/
























    while( true ) {
        vTaskDelay(1000);
    }
}

// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       50
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
