#include "ayplayer_button.h"

sr_one_in_button_status_struct b_s_ar[7];

sr_one_in_button_item_cfg ayplayer_button_cfg[7] = {
    {
        .byte                   = 0,
        .bit                    = 0,
        .ms_stabil              = 50,
        .dl_delay_ms            = 700,
        .s_press                = nullptr,
        .q_press                = nullptr,
        .v_press                = 0,
        .s_start_long_press     = nullptr,
        .q_start_long_press     = nullptr,
        .v_start_long_press     = 0,
        .s_release_long_click   = nullptr,
        .q_release_long_click   = nullptr,
        .v_release_long_click   = 0,
        .s_release_click        = nullptr,
        .q_release_click        = nullptr,
        .v_release_click        = 0,
        .status                 = &b_s_ar[0]
    }
};

extern USER_OS_STATIC_MUTEX         spi3_mutex;
extern module_shift_register        sr;
extern uint8_t                      sr_out_buf[2];

buttons_through_shift_register_one_in_cfg b_sr_cfg = {
    .p_in_pin                   = &b_in,
    .p_sr                       = &sr,
    .p_pin_conf_array           = ayplayer_button_cfg,
    .pin_count                  = 7,
    .delay_ms                   = 10,
    .prio                       = 1,
    .p_button_array             = &sr_out_buf[1],
    .sr_buffer_byte_count       = 1,
    .mutex                      = &spi3_mutex
};

buttons_through_shift_register_one_in ayplayer_button( &b_sr_cfg );
