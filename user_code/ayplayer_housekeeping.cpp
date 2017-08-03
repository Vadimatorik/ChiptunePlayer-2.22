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

uint8_t queue_ay_file_feedback_buf[ sizeof( uint8_t ) ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  queue_ay_file_feedback_st             = USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE;
USER_OS_STATIC_QUEUE         queue_ay_file_feedback;

FATFS                        sd2_fat;
uint8_t      circular_buffer[ 512*2 ];

extern ay_ym_low_lavel ay;
ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
    .ay_hardware                = &ay,
    .microsd_mutex              = &microsd_mutex,
    .queue_feedback             = &queue_ay_file_feedback,
    .fat                        = &sd2_fat,
    .circular_buffer_task_prio  = 3,
    .circular_buffer_size       = 512,
    .p_circular_buffer          = circular_buffer
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
uint8_t test_read[512] = {0};
uint8_t test_writre[512] = {0, 2, 3, 4, 5};

/*
 * Каждые 500 мс мигаем светодиодом.
 */
extern microsd_spi sd2;
void housekeeping_thread ( void* arg ) {
    (void)arg;

    // Костыль для потенциометров. Выставляем 5 кОм на всехъ каналах.
/*
    vTaskDelay(2000);
    shdn_obj.set();
    out_reg( 0, 0x80, 0, 0x80 );
    vTaskDelay(10);
    out_reg( 1, 0x80, 1, 0x80 );
    vTaskDelay(10);
    out_reg( 2, 0x80, 2, 0x80 );
    vTaskDelay(10);
    out_reg( 3, 0x80, 3, 0x80 );
    vTaskDelay(10);*/

    queue_ay_file_feedback = USER_OS_STATIC_QUEUE_CREATE( 1, sizeof( uint8_t ), queue_ay_file_feedback_buf, &queue_ay_file_feedback_st );
    microsd_mutex = USER_OS_STATIC_MUTEX_CREATE( &microsd_mutex_buf );

    volatile FRESULT ress;
    ress = f_mount(&sd2_fat, "", 0);
    ( void )ress;
    uint32_t count = 0;
    char path_dir[255] = "/";
    ay_file_mode.file_update(path_dir, nullptr);
    volatile EC_MICRO_SD_TYPE type_sd = EC_MICRO_SD_TYPE::ERROR;
    ( void )type_sd;
    volatile EC_SD_RESULT res;
    ( void )res;
    while( true ) {
        ay_file_mode.find_psg_file(count);
    }
}

// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       200
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

  */
