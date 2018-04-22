#include "ay_ym_low_lavel.h"
#include "pin.h"
#include "timer.h"
#include "ayplayer_os_object.h"

extern uint8_t								sr_out_buf_ay[2];
extern ShiftRegister						srAy;
extern ayplayerFreertosObjStrcut			osData;

extern Pin									bdir;
extern Pin									bc1;
extern Pin									pwr5vOn;

extern TimCompOneChannel					ayClk;
extern TimInterrupt							interruptAy;
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
void pwr5VSet ( bool state ) {
	pwr5vOn.set( state );
}

const ayYmLowLavelCfg ay_low_cfg {
	.sr					=	&srAy,
	.mutex				=	&osData.m_spi3,
	.srData				=	sr_out_buf_ay,
	.semaphoreSecOut	=	&osData.s_play_tic,
	.bdir				=	&bdir,
	.bc1				=	&bc1,
	.queueArray			=	osData.q_ay_low,
	.ayNumber			=	2,
	.connectCfg			=	array_connect_cfg,
	.taskPrio			=	3,
	.timFrequencyAy		=	&ayClk,
	.timInterruptTask	=	nullptr,// &interrupt_ay_obj,
	.pwrSet				=	pwr5VSet
};

AyYmLowLavel ayplayer_ay_low_obj( &ay_low_cfg );

extern "C" {
	void tim6_and_dac_handler ( void ) {
		ayplayer_ay_low_obj.timerInterruptHandler();
	}
}

