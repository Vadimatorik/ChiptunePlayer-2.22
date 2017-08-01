#include "ayplayer_housekeeping.h"
#include "ayplayer_ay_note.h"               // Потом выпелить!



#include "ayplayer_spi.h"
#include "ayplayer_shift_register.h"
#include "ayplayer_microsd_card.h"

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
void housekeeping_thread ( void* arg ) {
    (void)arg;

    // Костыль для потенциометров. Выставляем 5 кОм на всехъ каналах.

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


    while( true ) {
        vTaskDelay(1000);



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
