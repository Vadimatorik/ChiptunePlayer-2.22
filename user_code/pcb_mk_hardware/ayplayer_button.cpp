#include "ayplayer_button.h"

#define AY_BUTTON_QUEUE_SIZE    1

uint8_t ay_b_queue_buf[ AY_BUTTON_QUEUE_SIZE ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  ay_b_queue_st;
USER_OS_STATIC_QUEUE         ay_b_queue;

sr_one_in_button_status_struct b_s_ar[7];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg ayplayer_button_cfg[7] = {
    { 0, 0, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::UP ),   nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::UP ),     &b_s_ar[0] },
    { 0, 1, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),  nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),    &b_s_ar[1] },
    { 0, 2, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::LEFT),  nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::LEFT),    &b_s_ar[2] },
    { 0, 3, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT), nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT),   &b_s_ar[3] },
    { 0, 4, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::ENTER), nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::ENTER),   &b_s_ar[4] },
    { 0, 5, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::MENU),  nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::MENU),    &b_s_ar[5] },
    { 0, 6, 50, 700, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::BACK),  nullptr, &ay_b_queue, M_EC_TO_U8( EC_BUTTON_NAME::BACK),    &b_s_ar[6] },
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

void ayplayer_button_init ( void ) {
    ay_b_queue = USER_OS_STATIC_QUEUE_CREATE( AY_BUTTON_QUEUE_SIZE, sizeof( uint8_t ), ay_b_queue_buf, &ay_b_queue_st );
    ayplayer_button.init();
}
