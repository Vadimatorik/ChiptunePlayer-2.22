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
extern USER_OS_STATIC_MUTEX spi3_mutex;

extern  void pwr_chip_on ( uint32_t chip, bool state );
extern void ayplayer_pwr_5_v_set ( bool state );
void housekeeping_thread ( void* arg ) {
    (void)arg;
    sound_dp.connect_on();

    sound_dp.value_set( 0, 0, 0xFF );
    sound_dp.value_set( 0, 1, 0x80 );
    sound_dp.value_set( 0, 2, 0xFF );
    sound_dp.value_set( 0, 3, 0 );           // Второй чип, пока не трогаем.

    sound_dp.value_set( 1, 0, 0 );              // Второй чип, пока не трогаем.
    sound_dp.value_set( 1, 1, 0 );              // Второй чип, пока не трогаем.

    sound_dp.value_set( 1, 2, 0 );               // Левый наушник.
    sound_dp.value_set( 1, 3, 0 );               // Правый.

/*
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );
      out_reg( 2, 0x80, 2, 0xFF );
      out_reg( 3, 0x80, 3, 0xFF );

      out_reg( 2, 0xF0, 2, 0xFF );
      out_reg( 3, 0xF0, 3, 0xFF );

      out_reg( 2, 0x00, 2, 0xFF );
      out_reg( 3, 0x00, 3, 0xFF );
    USER_OS_GIVE_MUTEX( spi3_mutex );*/


    pwr_chip_on(1, true);
   // pwr_chip_on(0, true);
    ay_player_clk_tim.on();
ay_player_interrupt_ay.on();
    ayplayer_pwr_5_v_set(1);
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );
       ayplayer_note_mode.reinit( 1 );
     //  ayplayer_note_mode.reinit( 0 );
    USER_OS_GIVE_MUTEX( spi3_mutex );
    /*USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 0, 20 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
     USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY ); ayplayer_note_mode.set_volume_channel( 1, 0, 15 ); USER_OS_GIVE_MUTEX( spi3_mutex );vTaskDelay(100);

    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 1, 25 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
     USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY ); ayplayer_note_mode.set_volume_channel( 1, 1, 15 );  USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);

    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 2, 60 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.set_volume_channel( 1, 2, 15 ); USER_OS_GIVE_MUTEX( spi3_mutex );vTaskDelay(100);
*/


       /*
      USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 1, 25 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
       USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY ); ayplayer_note_mode.set_volume_channel( 1, 1, 15 );  USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);

      USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 2, 60 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
      USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.set_volume_channel( 1, 2, 15 ); USER_OS_GIVE_MUTEX( spi3_mutex );vTaskDelay(100);*/

/*
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );
    shdn_obj.set();
    out_reg( 0, 0xFF, 0, 0xFF );
    out_reg( 1, 0xFF, 1, 0xFF );
    out_reg( 2, 0x0, 2, 0xFF );
    out_reg( 3, 0x0, 3, 0xFF );
    USER_OS_GIVE_MUTEX( spi3_mutex );
*/

/*

 USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );
    ayplayer_note_mode.reinit( 1 );
    ayplayer_note_mode.reinit( 0 );
 USER_OS_GIVE_MUTEX( spi3_mutex );
   USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 0, 20 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY ); ayplayer_note_mode.set_volume_channel( 1, 0, 15 ); USER_OS_GIVE_MUTEX( spi3_mutex );vTaskDelay(100);

   USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 1, 25 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY ); ayplayer_note_mode.set_volume_channel( 1, 1, 15 );  USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);

   USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.write_note_to_channel( 1, 2, 60 );   USER_OS_GIVE_MUTEX( spi3_mutex ); vTaskDelay(100);
   USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );  ayplayer_note_mode.set_volume_channel( 1, 2, 15 ); USER_OS_GIVE_MUTEX( spi3_mutex );vTaskDelay(100);







*/

//    uint8_t aaa = 0;
      // volatile uint32_t c = 0;
//volatile uint32_t r = 0;
    volatile uint8_t v = 0;
    while( true ) {
    //     USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );
      //    out_reg( r2, v2, r1, v1 );
       //   out_reg( 3, 0x0, 3, 0xFF );
     //     USER_OS_GIVE_MUTEX( spi3_mutex );
        sound_dp.value_set( 1, 2, v );
        sound_dp.value_set( 1, 3, v );
       //   sound_dp.value_set( c, r, v );
          //sound_dp.value_set( 1, 0, 0xFF );
      // sound_dp.value_set( c, r, v );
        v += 0x10;
        vTaskDelay(1000);
    }
}

// 400 байт задаче.
#define AY_PLAYER_HOUSEKEEPING_TASK_STACK_SIZE       500
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
