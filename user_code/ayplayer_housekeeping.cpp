#include "ayplayer_housekeeping.h"
#include "ayplayer_ay_note.h"               // Потом выпелить!


#include "microsd_card.h"
#include "ayplayer_spi.h"
#include "ayplayer_shift_register.h"
#include "ayplayer_microsd_card.h"
#include "ay_ym_file_mode.h"

/*
 * filemode
 */

USER_OS_STATIC_MUTEX_BUFFER microsd_mutex_buf = USER_OS_STATIC_MUTEX_BUFFER_INIT_VALUE;
USER_OS_STATIC_MUTEX        microsd_mutex     = nullptr;

FATFS                        fat;

extern ay_ym_low_lavel ay;
ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
    .ay_hardware                = &ay,
    .microsd_mutex              = &microsd_mutex,
};

ay_ym_file_mode ay_file_mode(&ay_f_mode_cfg);


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
extern microsd_spi sd2;

#include "ayplayer_digital_potentiometer.h"
#include "ayplayer_fat.h"
#include "ay_ym_low_lavel.h"

extern ay_ym_low_lavel ay;
void housekeeping_thread ( void* arg ) {
    (void)arg;

    vTaskDelay(2000);
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
    vTaskDelay(2000);
        shdn_obj.set();
        out_reg( 0, 0x80, 0, 0x80 );
       vTaskDelay(10);
        out_reg( 1, 0x80, 1, 0x80 );
        vTaskDelay(10);
        out_reg( 2, 0x80, 2, 0x80 );
        vTaskDelay(10);
        out_reg( 3, 0x80, 3, 0x80 );
        vTaskDelay(10);


    microsd_mutex = USER_OS_STATIC_MUTEX_CREATE( &microsd_mutex_buf );


    /*
     *
    volatile FRESULT ress;
    ( void )ress;
    ress = f_mount(&fat, "", 0);

    char name[256];
    uint32_t len;

    volatile EC_AY_FILE_MODE r;
    ( void )r;

    char path[256] = "0:/";
    r = ay_file_mode.find_psg_file( path );
    r = ay_file_mode.psg_file_get_name( path, 0, name, len );
    r = ay_file_mode.psg_file_play( path, 0 );*/

    ay_queue_struct a;
    a.number_chip = 0;
    a.reg = 7;
    a.data = 0;
    ay.queue_add_element(&a);

    a.number_chip = 1;
    a.reg = 7;
    a.data = 0;
    ay.queue_add_element(&a);


    ayplayer_note_mode.write_note_to_channel( 0, 0, 40 );
    ayplayer_note_mode.write_note_to_channel( 0, 1, 20 );
    ayplayer_note_mode.write_note_to_channel( 0, 2, 30 );

    ayplayer_note_mode.set_volume_channel( 0, 0, 10 );
    ayplayer_note_mode.set_volume_channel( 0, 1, 10 );
    ayplayer_note_mode.set_volume_channel( 0, 2, 10 );

    ayplayer_note_mode.write_note_to_channel( 1, 0, 40 );
    ayplayer_note_mode.write_note_to_channel( 1, 1, 50 );
    ayplayer_note_mode.write_note_to_channel( 1, 2, 60 );

    ayplayer_note_mode.set_volume_channel( 1, 0, 15 );
    ayplayer_note_mode.set_volume_channel( 1, 1, 10 );
    ayplayer_note_mode.set_volume_channel( 1, 2, 10 );


    while( true ) {

        vTaskDelay(1000);

    };
}

// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       1500
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


/*



  */
