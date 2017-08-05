#include "ayplayer_ay_low.h"

extern uint8_t sr_out_buf[2];

uint8_t queue_0_buf[ sizeof( ay_low_out_data_struct ) * 32 ] = { 0 };
uint8_t queue_1_buf[ sizeof( ay_low_out_data_struct ) * 32 ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  q_0_st             = USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE;
USER_OS_STATIC_QUEUE_STRUCT  q_1_st             = USER_OS_STATIC_QUEUE_STRUCT_INIT_VALUE;

USER_OS_STATIC_QUEUE         p_queue_array[2];

uint8_t r7_array[2] = { 0 };

ay_ym_connection_chip_cfg_t ay_connect_cfg = { 0, 1, 2, 3, 4, 5, 6, 7 };
ay_ym_connection_chip_cfg_t ym_connect_cfg = { 7, 6, 5, 4, 3, 2, 1, 0 };

ay_ym_connection_chip_cfg_t array_connect_cfg[] = {
    ym_connect_cfg, ay_connect_cfg
    // 0 - 40 пиновый, 1 - 28.
};

const ay_ym_low_lavel_cfg_t ay_low_cfg {
    .sr                 = &sr,
    .p_sr_data          = &sr_out_buf[0],
    .semaphore_sec_out  = nullptr,
    .bdir               = &bdir_obj,
    .bc1                = &bc1_obj,
    .p_queue_array      = p_queue_array,
    .ay_number          = 2,
    .con_cfg            = array_connect_cfg,
    .task_prio          = 3,
    .r7_reg             = r7_array,
    .tim_frequency_ay   = &ay_player_clk_tim
};

ay_ym_low_lavel ay( &ay_low_cfg );


void ayplayer_ay_init (void) {
    p_queue_array[0] = USER_OS_STATIC_QUEUE_CREATE( 32, sizeof( ay_low_out_data_struct ), queue_0_buf, &q_0_st );
    p_queue_array[1] = USER_OS_STATIC_QUEUE_CREATE( 32, sizeof( ay_low_out_data_struct ), queue_1_buf, &q_1_st );
    ay.init();
}
