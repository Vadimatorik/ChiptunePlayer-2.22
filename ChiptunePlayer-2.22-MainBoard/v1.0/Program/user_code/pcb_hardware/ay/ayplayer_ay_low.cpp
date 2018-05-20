#include "ay_ym_low_lavel.h"
#include "pin.h"
#include "timer.h"
#include "ayplayer_os_object.h"

extern uint8_t								sr_out_buf_ay[2];
extern ShiftRegister						srAy;
extern freeRtosObj							osData;

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
	ym_connect_cfg,					/// 40 PIN, AY2, AY2_VDD (включается вместе с AY1 по питании).
	ay_connect_cfg					/// 28 PIN. AY1.
};

/*!
 * Метод отключает все используемые AY/YM чипы.
 */
void pwr5VSet ( bool state ) {
	pwr5vOn.set( state );
}

const ayYmLowLavelCfg ayLowCfg {
	.sr					=	&srAy,
	.mutex				=	&osData.mSpi3,
	.srData				=	sr_out_buf_ay,
	.semaphoreSecOut	=	&osData.sPlayTic,
	.bdir				=	&bdir,
	.bc1				=	&bc1,
	.queueArray			=	osData.qAyLow,
	.ayNumber			=	2,
	.connectCfg			=	array_connect_cfg,
	.taskPrio			=	4,
	.timFrequencyAy		=	&ayClk,
	.timInterruptTask	=	&interruptAy,
	.pwrSet				=	pwr5VSet
};

AyYmLowLavel ayLow( &ayLowCfg );
