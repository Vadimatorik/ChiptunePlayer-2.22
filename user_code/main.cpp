#include "main.h"

ayplayerMcStrcut ayMcuCfg = {
	.wdt						=	&wdtObj,
	.gpio						=	&gpioStruct,
	.gp							=	&gp,
	.debugUart					=	&usart3,
	.rcc						=	&ayplayer_rcc,
	.spi1						=	&spi1,
	.spi2						=	&spi2,
	.spi3						=	&spi3,
	.adc1						=	&adcBat,
	.ayClkTim					=	&ayClk,
	.lcdPwmTim					=	&lcdPwm,
	.interruptAyTim				=	&interruptAy,

#ifdef configGENERATE_RUN_TIME_STATS
	.timRunTimeStats			=	&timRunTimeStats
#endif
};

ayplayerPcbStrcut ayPcbCfg = {
	.srAy						=	&srAy,
	.srButton					=	&srButton,
	.button						=	&button,
	.dp							=	&soundDp,
	.ay							=	&ayLow
};

AyPlayerCfg ayCfg = {
	.mcu						=	&ayMcuCfg,
	.l							=	&ayLog,
	.pcb						=	&ayPcbCfg,
	.ayF						=	&ayFileMode,
	.os							=	&osData
};

AyPlayer											ay( &ayCfg );

extern "C" {

int main ( void ) {
	ay.start();
    while ( true );
}

}

void assertFailed ( uint8_t* file, uint32_t line ) {
	(void)file;
	(void)line;
	while(1);
}
