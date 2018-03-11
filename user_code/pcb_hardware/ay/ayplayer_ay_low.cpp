#include "pin.h"
#include "timer.h"
#include "ay_ym_low_lavel.h"
#include "ayplayer_os_object.h"

extern uint8_t								sr_out_buf_ay[2];
extern module_shift_register				sr_ay;
extern ay_player_freertos_obj_strcut		os_data;

extern pin									ayplayer_bdir_pin_obj;
extern pin									ayplayer_bc1_pin_obj;
extern pin									ayplayer_pwr_5_v_on_pin_obj;

extern tim_comp_one_channel					ay_clk_obj;
extern tim_interrupt						interrupt_ay_obj;
/*!
 * Remap выводов.
 * Тут описаны соответствие бит сдвигового регистра и бит AY/YM чипов.
 * Например, 0-й бит сдвигового регистра == 7-му биту AY/YM.
 * Этим компенсируется легкая разводка.
 */
ay_ym_connection_chip_cfg_t ay_connect_cfg = { 0, 1, 2, 3, 4, 5, 6, 7 };
ay_ym_connection_chip_cfg_t ym_connect_cfg = { 7, 6, 5, 4, 3, 2, 1, 0 };

ay_ym_connection_chip_cfg_t array_connect_cfg[] = {
	ym_connect_cfg,					/// 40 PIN.
	ay_connect_cfg					/// 28 PIN.
};

/*!
 * Метод отключает все используемые AY/YM чипы.
 */
void ayplayer_pwr_5_v_set ( bool state ) {
	ayplayer_pwr_5_v_on_pin_obj.set( state );
}

const ay_ym_low_lavel_cfg_t ay_low_cfg {
	.sr					= &sr_ay,
	.mutex				= &os_data.m_spi3,
	.p_sr_data			= sr_out_buf_ay,
	.semaphore_sec_out	= &os_data.s_play_tic,
	.bdir				= &ayplayer_bdir_pin_obj,
	.bc1				= &ayplayer_bc1_pin_obj,
	.queue_array		= os_data.q_ay_low,
	.ay_number			= 2,
	.con_cfg			= array_connect_cfg,
	.task_prio			= 3,
	.tim_frequency_ay	= &ay_clk_obj,
	.tim_interrupt_task	= nullptr,// &interrupt_ay_obj,
	.pwr_set			= ayplayer_pwr_5_v_set
};

ay_ym_low_lavel ayplayer_ay_low_obj( &ay_low_cfg );

extern "C" {
	void tim6_and_dac_handler ( void ) {
		ayplayer_ay_low_obj.timer_interrupt_handler();
	}
}

