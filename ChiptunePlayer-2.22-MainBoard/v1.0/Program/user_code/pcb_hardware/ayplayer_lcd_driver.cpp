#include "pin.h"
#include "spi.h"
#include "mono_lcd_lib_st7565.h"

extern Pin					lcdRes;
extern Pin					lcdDc;
extern Pin					lcdCs;

extern SpiMaster8Bit		spi1;

const ST7565Cfg st7565_cfg {
	.a0		=	&lcdDc,
	.res	=	&lcdRes,
	.cs		=	&lcdCs,
	.s		=	&spi1,
	.mode	=	ST7565_MODE::STANDARD
};

/// Для доступа MakiseGUI.
extern "C" {
uint8_t makiseLcdBuf[1024] = { 0 };
}

ST7565 lcd( &st7565_cfg, makiseLcdBuf );
