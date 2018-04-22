#include "main.h"
#include "ayplayer.h"
#include "stm32f2xx_hal.h"

extern Wdt											wdtObj;
extern ayplayerGpio									gpioStruct;
extern GlobalPort									gp;
extern Uart											usart3_obj;
extern Rcc											ayplayer_rcc;
extern SpiMaster8Bit								spi1;
extern SpiMaster8Bit								spi2;
extern SpiMaster8Bit								spi3;
extern AdcOneChannel								adcBat;
extern TimCompOneChannel							ayClk;
extern TimPwmOneChannel								lcdPwm;
extern TimInterrupt									interruptAy;
extern run_time_logger								ayLog;

extern ShiftRegister								srAy;
extern ShiftRegister								srButton;
extern ButtonsThroughShiftRegisterOneInputPin		button;
extern ad5204< 2 >									soundDp;
extern AyYmFileMode									ayFileMode;

ayplayerMcStrcut ayMcuCfg = {
	.wdt						= &wdtObj,
	.gpio						= &gpioStruct,
	.gp							= &gp,
	.debugUart					= &usart3_obj,
	.rcc						= &ayplayer_rcc,
	.spi1						= &spi1,
	.spi2						= &spi2,
	.spi3						= &spi3,
	.adc1						= &adcBat,
	.ayClkTim					= &ayClk,
	.lcdPwmTim					= &lcdPwm,
	.interruptAyTim				= &interruptAy
};

ayplayerPcbStrcut ayPcbCfg = {
	.ay							= &srAy,
	.srButton					= &srButton,
	.button						= &button,
	.dp							= &soundDp
};

AyPlayerCfg ayCfg = {
	.mcu						= &ayMcuCfg,
	.l							= &ayLog,
	.pcb						= &ayPcbCfg,
	.ayF						= &ayFileMode
};

AyPlayer											ay( &ayCfg );

extern "C" {

int main ( void ) {
	ay.init();
	ay.start();
    while ( true );
}

extern void xPortSysTickHandler ( void );
void sys_tick_handler(void) {
	HAL_IncTick();
	xPortSysTickHandler();
}

}
