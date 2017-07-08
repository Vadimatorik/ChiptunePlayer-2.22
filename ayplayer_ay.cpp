#include "ayplayer_ay.h"

extern uint8_t sr_out_buf[2];
extern module_shift_register   sr;

uint8_t queue_0_buf[ sizeof( ay_low_out_data ) * 32 ] = { 0 };
uint8_t queue_1_buf[ sizeof( ay_low_out_data ) * 32 ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  q_0_st             = USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE;
USER_OS_STATIC_QUEUE_STRUCT  q_1_st             = USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE;

USER_OS_STATIC_QUEUE         p_queue_array[2];

const ay_ym_low_lavel_cfg_t ay_low_cfg {
    .sr                 = &sr,
    .p_sr_data          = &sr_out_buf[1],
    .semaphore_sec_out  = nullptr,
    .bdir               = &bdir_obj,
    .bc1                = &bc1_obj,
    .p_queue_array      = p_queue_array
};

const ay_ym_low_lavel< 1, 3, &ay_low_cfg >*ay = nullptr;

void ayplayer_ay_init (void) {
    p_queue_array[0] = USER_OS_STATIC_QUEUE_CREATE( 32, sizeof( ay_low_out_data ), queue_0_buf, &q_0_st );
    p_queue_array[1] = USER_OS_STATIC_QUEUE_CREATE( 32, sizeof( ay_low_out_data ), queue_1_buf, &q_1_st );

    ay = ay_ym_low_lavel< 1, 3, &ay_low_cfg >::instance();

    ay->init();
}
