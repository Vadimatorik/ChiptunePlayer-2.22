#include "../../../module_chiptune/ay_ym_low_lavel/ay_ym_low_lavel.h"
#include "pin.h"
#include "timer.h"
#include "ayplayer_os_object.h"

extern uint8_t								sr_out_buf_ay[2];
extern ShiftRegister				sr_ay;
extern ay_player_freertos_obj_strcut		os_data;

extern Pin									ayplayer_bdir_pin_obj;
extern Pin									ayplayer_bc1_pin_obj;
extern Pin									ayplayer_pwr_5_v_on_pin_obj;

extern TimCompOneChannel					ay_clk_obj;
extern TimInterrupt							interrupt_ay_obj;
/*!
 * Remap выводов.
 * Тут описаны соответствие бит сдвигового регистра и бит AY/YM чипов.
 * Например, 0-й бит сдвигового регистра == 7-му биту AY/YM.
 * Этим компенсируется легкая разводка.
 */
ayYmConnectionChipCfg ay_connect_cfg = { 0, 1, 2, 3, 4, 5, 6, 7 };
ayYmConnectionChipCfg ym_connect_cfg = { 7, 6, 5, 4, 3, 2, 1, 0 };

ayYmConnectionChipCfg array_connect_cfg[] = {
	ym_connect_cfg,					/// 40 PIN.
	ay_connect_cfg					/// 28 PIN.
};

/*!
 * Метод отключает все используемые AY/YM чипы.
 */
void ayplayer_pwr_5_v_set ( bool state ) {
	ayplayer_pwr_5_v_on_pin_obj.set( state );
}

const ayYmLowLavelCfg ay_low_cfg {
	.sr					= &sr_ay,
	.mutex				= &os_data.m_spi3,
	.srData				= sr_out_buf_ay,
	.semaphoreSecOut	= &os_data.s_play_tic,
	.bdir				= &ayplayer_bdir_pin_obj,
	.bc1				= &ayplayer_bc1_pin_obj,
	.queueArray		= os_data.q_ay_low,
	.ayNumber			= 2,
	.connectCfg			= array_connect_cfg,
	.taskPrio			= 3,
	.timFrequencyAy	= &ay_clk_obj,
	.timInterruptTask	= nullptr,// &interrupt_ay_obj,
	.pwrSet			= ayplayer_pwr_5_v_set
};

AyYmLowLavel ayplayer_ay_low_obj( &ay_low_cfg );

extern "C" {
	void tim6_and_dac_handler ( void ) {
		ayplayer_ay_low_obj.timerInterruptHandler();
	}
}

