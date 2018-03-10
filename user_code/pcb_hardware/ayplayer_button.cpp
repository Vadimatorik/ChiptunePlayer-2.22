#include "ayplayer_button.h"
#include "buttons_through_shift_register_one_in.h"
#include "user_os.h"
#include "ayplayer_os_object.h"
#include "pin.h"

extern ay_player_freertos_obj_strcut	os_data;
extern pin								ayplayer_button_in_pin_obj;
extern module_shift_register			sr_button;
extern uint8_t							sr_out_buf_button[1];

sr_one_in_button_status_struct	b_s_ar[7];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg ayplayer_button_cfg[7] = {
	{ 0, 0, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,                                              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                 nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::UP ),                  &b_s_ar[0] },
	{ 0, 1, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,                                              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::DOWN ),               nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),                 &b_s_ar[1] },
	{ 0, 2, 50, 700, nullptr, nullptr, 0, nullptr, &os_data.q_ay_button,	M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ),  nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_CLICK ),    nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK),           &b_s_ar[2] },
	{ 0, 3, 50, 700, nullptr, nullptr, 0, nullptr, &os_data.q_ay_button,	M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ), nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ),   nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK),          &b_s_ar[3] },
	{ 0, 4, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,                                              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::ENTER ),              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::ENTER),                &b_s_ar[4] },
	{ 0, 6, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,                                              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::BACK ),               nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::BACK),                 &b_s_ar[5] },
	{ 0, 5, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,                                              nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::MENU ),               nullptr, &os_data.q_ay_button, M_EC_TO_U8( EC_BUTTON_NAME::MENU),                 &b_s_ar[6] },
};

buttons_through_shift_register_one_in_cfg b_sr_cfg = {
    .p_in_pin                   = &ayplayer_button_in_pin_obj,
    .p_sr                       = &sr_button,
    .p_pin_conf_array           = ayplayer_button_cfg,
    .pin_count                  = 7,
    .delay_ms                   = 10,
	.prio                       = 1,
	.p_button_array             = sr_out_buf_button,
    .sr_buffer_byte_count       = 1,
	.mutex                      = &os_data.m_spi3
};

buttons_through_shift_register_one_in ayplayer_button( &b_sr_cfg );
