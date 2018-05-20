#include "main.h"

ayplayerMcStrcut ayMcuCfg = {
	.wdt								=	&wdtObj,
	.gpio								=	&gpioStruct,
	.gp									=	&gp,
	.debugUart							=	&usart3,
	.rcc								=	&ayplayer_rcc,
	.spi1								=	&spi1,
	.spi2								=	&spi2,
	.spi3								=	&spi3,
	.adc1								=	&adcBat,
	.ayClkTim							=	&ayClk,
	.lcdPwmTim							=	&lcdPwm,
	.interruptAyTim						=	&interruptAy,
	.pwr								=	&pwr,

#ifdef configGENERATE_RUN_TIME_STATS
	.timRunTimeStats					=	&timRunTimeStats
#endif
};

ayplayerPcbStrcut ayPcbCfg = {
	.srAy								=	&srAy,
	.srButton							=	&srButton,
	.button								=	&button,
	.dp									=	&soundDp,
	.ay									=	&ayLow,
	.lcd								=	&lcd,
	.sd									=	sdArray
};

extern const MakiseFont F_minecraft_rus_regular_8;
extern uint32_t	ayplayerGetStatePlay			( void );
extern uint32_t	ayplayerGetPercentBattery		( void );


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
		.text_scroll_speed				=	1,
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
	},
	.statusBarCfg = {
		.fontErcent						=	&F_minecraft_rus_regular_8,
		.fontErcentCol					=	MC_Black,
		.bgColor						=	MC_White,
		.borderColor					=	MC_Black
	},
	.statusBarCallbackCfg = {
		.getStatePlay					=	ayplayerGetStatePlay,
		.getPercentBattery				=	ayplayerGetPercentBattery
	},
	.playBarStyle = {
		.bgColor						=	MC_White,
		.borderColor					=	MC_Black,
		.dutyColor						=	MC_Black,
		.timeColor						=	MC_Black,
		.font							=	&F_minecraft_rus_regular_8
	},
	.horizontalListStyle = {
		.fontString						=	&F_minecraft_rus_regular_8,
		.stringColor					=	MC_Black,
		.bgColor						=	MC_White,
		.borderColor					=	MC_Black,
		.bgArrowColor					=	MC_Black
	},
	.m = {
		.maincolor						=	MC_Black,
		.font							=	&F_minecraft_rus_regular_8,
		.font_line_spacing				=	1,
		.unactive = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_White,
			.double_border				=	0
		},
		.normal = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_White,
			.double_border				=	0
		},
		.focused = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	1
		},
		.active = {
			.bg_color					=	MC_White,
			.font_col					=	MC_Black,
			.border_c					=	MC_Black,
			.double_border				=	1
		}
	}
};

ayPlayerCfg ayCfg = {
	.mcu								=	&ayMcuCfg,
	.l									=	&ayLog,
	.pcb								=	&ayPcbCfg,
	.os									=	&osData,
	.ay									=	&ayYmFilePlay,
	.gui								=	&ayGuiCfg
};

AyPlayer								ay( &ayCfg );

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
