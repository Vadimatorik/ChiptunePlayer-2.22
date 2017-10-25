#include "ayplayer_button.h"

sr_one_in_button_status_struct b_s_ar[7];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg ayplayer_button_cfg[7] = {
    { 0, 0, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                 nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                  &b_s_ar[0] },
    { 0, 1, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::DOWN ),               nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),                 &b_s_ar[1] },
    { 0, 2, 50, 700, nullptr, nullptr, 0, nullptr, &q_ay_button,    M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ),  nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_CLICK ),    nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK),           &b_s_ar[2] },
    { 0, 3, 50, 700, nullptr, nullptr, 0, nullptr, &q_ay_button,    M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ), nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ),   nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK),          &b_s_ar[3] },
    { 0, 4, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::ENTER ),              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::ENTER),                &b_s_ar[4] },
    { 0, 5, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::MENU ),               nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::MENU),                 &b_s_ar[5] },
    { 0, 6, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,         0,                                              nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::BACK ),               nullptr, &q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::BACK),                 &b_s_ar[6] },
};

buttons_through_shift_register_one_in_cfg b_sr_cfg = {
    .p_in_pin                   = &b_in,
    .p_sr                       = &sr_button,
    .p_pin_conf_array           = ayplayer_button_cfg,
    .pin_count                  = 7,
    .delay_ms                   = 10,
    .prio                       = 1,
    .p_button_array             = &sr_out_buf_button[0],
    .sr_buffer_byte_count       = 1,
    .mutex                      = &m_spi3
};

buttons_through_shift_register_one_in ayplayer_button( &b_sr_cfg );


#define INC_AND_DEC_STABIL      10
#define OFF_WITE                100

int32_t current_volume = 4;

#include "ayplayer_digital_potentiometer.h"

uint8_t v_table[16] = { 0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xFF };

// Детектирование изменения уровня громкости.
void ayplayer_button_inc_and_dec_detect ( void* param ) {
    ( void )param;
    uint8_t inc = INC_AND_DEC_STABIL;
    uint8_t dec = INC_AND_DEC_STABIL;
    uint8_t off_time = OFF_WITE;
    bool inc_f = false;
    bool dec_f = false;

    while ( true ) {
        vTaskDelay( 10 );

        inc_f = b_inc.read();
        dec_f = b_dec.read();

        if ( ( inc_f == false ) && ( dec_f == false ) ) {
            if ( off_time > 0 ) {
                off_time--;
            } else {
                pwr_on_obj.reset();
            }
        } else {
            off_time = OFF_WITE;
        }

        if ( inc_f == false ) {
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

        if ( dec_f == false ) {
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

void ayplayer_button_init ( void ) {
    q_ay_button_init();
    ayplayer_button.init();
    USER_OS_STATIC_TASK_CREATE( ayplayer_button_inc_and_dec_detect, "b_incdec", TB_B_INC_DEC_SIZE,  NULL, 3, tb_inc_dec_detect, &ts_inc_dec_detect );
}
