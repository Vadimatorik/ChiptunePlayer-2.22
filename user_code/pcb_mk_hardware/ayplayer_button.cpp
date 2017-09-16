#include "ayplayer_button.h"

#define AY_BUTTON_QUEUE_SIZE    1

uint8_t ay_b_queue_buf[ AY_BUTTON_QUEUE_SIZE ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  ay_b_queue_st;
USER_OS_STATIC_QUEUE         ay_b_queue;

sr_one_in_button_status_struct b_s_ar[7];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg ayplayer_button_cfg[7] = {
    { 0, 0, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                 nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                  &b_s_ar[0] },
    { 0, 1, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::DOWN ),               nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),                 &b_s_ar[1] },
    { 0, 2, 50, 700, nullptr, nullptr, 0, nullptr, &ay_b_queue,     M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ),  nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_CLICK ),    nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK),           &b_s_ar[2] },
    { 0, 3, 50, 700, nullptr, nullptr, 0, nullptr, &ay_b_queue,     M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ), nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ),   nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK),          &b_s_ar[3] },
    { 0, 4, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::ENTER ),              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::ENTER),                &b_s_ar[4] },
    { 0, 5, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::MENU ),               nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::MENU),                 &b_s_ar[5] },
    { 0, 6, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::BACK ),               nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::BACK),                 &b_s_ar[6] },
};

extern USER_OS_STATIC_MUTEX         spi3_mutex;
extern module_shift_register        sr_button;
extern uint8_t                      sr_out_buf_button[1];

buttons_through_shift_register_one_in_cfg b_sr_cfg = {
    .p_in_pin                   = &b_in,
    .p_sr                       = &sr_button,
    .p_pin_conf_array           = ayplayer_button_cfg,
    .pin_count                  = 7,
    .delay_ms                   = 10,
    .prio                       = 1,
    .p_button_array             = &sr_out_buf_button[0],
    .sr_buffer_byte_count       = 1,
    .mutex                      = &spi3_mutex
};

buttons_through_shift_register_one_in ayplayer_button( &b_sr_cfg );


#define INC_AND_DEC_STABIL      10
int32_t current_volume = 4;

#include "ayplayer_digital_potentiometer.h"

uint8_t v_table[16] = { 0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xFF };

// Детектирование изменения уровня громкости.
void ayplayer_button_inc_and_dec_detect ( void* param ) {
    ( void )param;
    uint8_t inc = INC_AND_DEC_STABIL;
    uint8_t dec = INC_AND_DEC_STABIL;
    while ( true ) {
        vTaskDelay( 10 );

        if ( b_inc.read() == false ) {
            if ( inc > 0 ) inc--;
        } else {
            if ( inc == 0 ) {
                if ( current_volume < 15 )
                    current_volume++;
                inc = INC_AND_DEC_STABIL;
                sound_dp.value_set( 1, 2, v_table[ current_volume ] );           // Левый наушник.
                sound_dp.value_set( 1, 3, v_table[ current_volume ] );           // Правый.
                continue;
            }
        }

        if ( b_dec.read() == false ) {
            if ( dec > 0 ) dec--;
        } else {
            if ( dec == 0 ) {
                if ( current_volume > 0 )
                    current_volume--;
                dec = INC_AND_DEC_STABIL;
                sound_dp.value_set( 1, 2, v_table[ current_volume ] );           // Левый наушник.
                sound_dp.value_set( 1, 3, v_table[ current_volume ] );           // Правый.
                continue;
            }
        }



    }
}

static StaticTask_t     ayplayer_inc_and_dec_detect_task_buffer;
static StackType_t      ayplayer_inc_and_dec_detect_task_stack[ AY_PLAYER_B_INC_DEC_TASK_STACK_SIZE ];

void ayplayer_button_init ( void ) {
    ay_b_queue = USER_OS_STATIC_QUEUE_CREATE( AY_BUTTON_QUEUE_SIZE, sizeof( uint8_t ), ay_b_queue_buf, &ay_b_queue_st );
    ayplayer_button.init();

    xTaskCreateStatic( ayplayer_button_inc_and_dec_detect,
                       "b_incdec",
                       AY_PLAYER_B_INC_DEC_TASK_STACK_SIZE,
                       NULL,
                       3,
                       ayplayer_inc_and_dec_detect_task_stack,
                       &ayplayer_inc_and_dec_detect_task_buffer );
}
