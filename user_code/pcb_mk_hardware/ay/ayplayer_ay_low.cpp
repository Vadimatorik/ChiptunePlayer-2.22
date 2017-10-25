#include "ayplayer_ay_low.h"

extern uint8_t sr_out_buf_ay[2];

uint8_t r7_array[2] = { 0 };

ay_ym_connection_chip_cfg_t ay_connect_cfg = { 0, 1, 2, 3, 4, 5, 6, 7 };
ay_ym_connection_chip_cfg_t ym_connect_cfg = { 7, 6, 5, 4, 3, 2, 1, 0 };

ay_ym_connection_chip_cfg_t array_connect_cfg[] = {
    ym_connect_cfg, ay_connect_cfg
    // 0 - 40 пиновый, 1 - 28.
};

void ayplayer_pwr_5_v_set ( bool state );
extern module_shift_register       sr_ay;

const ay_ym_low_lavel_cfg_t ay_low_cfg {
    .sr                 = &sr_ay,
    .mutex              = &m_spi3,
    .p_sr_data          = &sr_out_buf_ay[0],
    .semaphore_sec_out  = &s_play_tic,
    .bdir               = &bdir_obj,
    .bc1                = &bc1_obj,
    .queue_array        = q_ay_low,
    .ay_number          = 2,
    .con_cfg            = array_connect_cfg,
    .task_prio          = 3,
    .tim_frequency_ay   = &ay_player_clk_tim,
    .tim_interrupt_task = &ay_player_interrupt_ay,
    .pwr_set            = ayplayer_pwr_5_v_set
};

ay_ym_low_lavel ay( &ay_low_cfg );


void ayplayer_ay_init (void) {
    q_ay_low_init();
}

extern uint8_t v_table[16];
extern int32_t current_volume;

void ayplayer_pwr_5_v_set ( bool state ) {
    if ( state == 1 ) {
        pwr_5_v_on_obj.set( true );             // Пережидаем щелчок.
        sound_dp.value_set( 1, 2, v_table[ current_volume ] );           // Левый наушник.
        sound_dp.value_set( 1, 3, v_table[ current_volume ] );           // Правый.
    } else {
        pwr_5_v_on_obj.set( false );
    }
}

extern "C" {
    void tim6_and_dac_handler ( void ) {
        ay.timer_interrupt_handler();
    }
}

