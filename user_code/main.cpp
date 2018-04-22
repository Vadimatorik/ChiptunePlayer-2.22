#include "main.h"

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

}
