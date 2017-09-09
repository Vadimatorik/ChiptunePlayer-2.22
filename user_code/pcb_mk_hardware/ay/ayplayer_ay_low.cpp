#include "ayplayer_ay_low.h"

extern uint8_t sr_out_buf_ay[2];

// В этих очередях содержатся данные для каждого AY.
// Они (данные) будут выдаваться в прерывании с заданной частотой.
#define AY_LOW_QUEUE_BUF_SIZE                   128
uint8_t ay_low_queue_0_buf[ sizeof( ay_low_out_data_struct ) * AY_LOW_QUEUE_BUF_SIZE ] = { 0 };
uint8_t ay_low_queue_1_buf[ sizeof( ay_low_out_data_struct ) * AY_LOW_QUEUE_BUF_SIZE ] = { 0 };
USER_OS_STATIC_QUEUE_STRUCT  ay_low_q_0_st;
USER_OS_STATIC_QUEUE_STRUCT  ay_low_q_1_st;

USER_OS_STATIC_QUEUE         ay_low_p_queue_array[2];

extern USER_OS_STATIC_BIN_SEMAPHORE        ayplayer_play_tic_semaphore;
uint8_t r7_array[2] = { 0 };

ay_ym_connection_chip_cfg_t ay_connect_cfg = { 0, 1, 2, 3, 4, 5, 6, 7 };
ay_ym_connection_chip_cfg_t ym_connect_cfg = { 7, 6, 5, 4, 3, 2, 1, 0 };

ay_ym_connection_chip_cfg_t array_connect_cfg[] = {
    ym_connect_cfg, ay_connect_cfg
    // 0 - 40 пиновый, 1 - 28.
};

void ayplayer_pwr_5_v_set ( bool state );
extern module_shift_register       sr_ay;
extern USER_OS_STATIC_MUTEX        spi3_mutex;

const ay_ym_low_lavel_cfg_t ay_low_cfg {
    .sr                 = &sr_ay,
    .mutex              = &spi3_mutex,
    .p_sr_data          = &sr_out_buf_ay[0],
    .semaphore_sec_out  = &ayplayer_play_tic_semaphore,
    .bdir               = &bdir_obj,
    .bc1                = &bc1_obj,
    .queue_array        = ay_low_p_queue_array,
    .ay_number          = 2,
    .con_cfg            = array_connect_cfg,
    .task_prio          = 3,
    .tim_frequency_ay   = &ay_player_clk_tim,
    .tim_interrupt_task = &ay_player_interrupt_ay,
    .pwr_set            = ayplayer_pwr_5_v_set
};

ay_ym_low_lavel ay( &ay_low_cfg );


void ayplayer_ay_init (void) {
    ay_low_p_queue_array[0] = USER_OS_STATIC_QUEUE_CREATE( AY_LOW_QUEUE_BUF_SIZE, sizeof( ay_low_out_data_struct ), ay_low_queue_0_buf, &ay_low_q_0_st );
    ay_low_p_queue_array[1] = USER_OS_STATIC_QUEUE_CREATE( AY_LOW_QUEUE_BUF_SIZE, sizeof( ay_low_out_data_struct ), ay_low_queue_1_buf, &ay_low_q_1_st );
}

void ayplayer_pwr_5_v_set ( bool state ) {
    if ( state == 1 ) {
        pwr_5_v_on_obj.set( true );
    } else {
        pwr_5_v_on_obj.set( false );
    }
    vTaskDelay(10);
}

extern "C" {
    void tim6_and_dac_handler ( void ) {
        ay.timer_interrupt_handler();
    }
}

