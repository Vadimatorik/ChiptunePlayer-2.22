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
	.pwr						=	&pwr,

#ifdef configGENERATE_RUN_TIME_STATS
	.timRunTimeStats			=	&timRunTimeStats
#endif
};

ayplayerPcbStrcut ayPcbCfg = {
	.srAy						=	&srAy,
	.srButton					=	&srButton,
	.button						=	&button,
	.dp							=	&soundDp,
	.ay							=	&ayLow,
	.lcd						=	&lcd,
	.sd							=	sdArray
};

extern const MakiseFont F_minecraft_rus_regular_8;

ayplayerGuiCfg ayGuiCfg = {
	.smw = {
		.font							=	&F_minecraft_rus_regular_8,
		.font_line_spacing				=	2,

		.bg_color						=	MC_White,
		.font_col						=	MC_Black,
		.border_color					=	MC_Black,
	},
	.ssl = {
		.font							=	&F_minecraft_rus_regular_8,

		.font_line_spacing				=	0,
		.left_margin					=	0,
		.item_margin					=	0,

		.scroll_width					=	0,
		.scroll_bg_color				=	0,
		.scroll_color					=	0,

		.normal = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		},

		.focused = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		},
		.active	= {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		}
	},
	.sslItem = {
		.font							=	&F_minecraft_rus_regular_8,
		.font_line_spacing				=	0,

		.normal = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		},
		.focused = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		},
		.active = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	0
		}
	}
};

ayPlayerCfg ayCfg = {
	.mcu						=	&ayMcuCfg,
	.l							=	&ayLog,
	.pcb						=	&ayPcbCfg,
	.ayF						=	&ayFileMode,
	.os							=	&osData,
	.gui						=	&ayGuiCfg
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
