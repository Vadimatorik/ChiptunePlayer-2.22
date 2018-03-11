#include "pin.h"
#include "spi.h"
#include "mono_lcd_lib_st7565.h"

extern pin					ayplayer_lcd_res_pin_obj;
extern pin					ayplayer_lcd_dc_pin_obj;
extern pin					ayplayer_lcd_cs_pin_obj;

extern spi_master_8bit		ayplayer_spi1_obj;

const mono_lcd_lib_st7565_cfg_t st7565_cfg {
	.a0		= &ayplayer_lcd_dc_pin_obj,
	.res	= &ayplayer_lcd_res_pin_obj,
	.cs		= &ayplayer_lcd_cs_pin_obj,
	.p_spi	= &ayplayer_spi1_obj,
	.mode	= ST7565_MODE::STANDARD
};

/// Для доступа MakiseGUI.
extern "C" {
uint8_t lcd_buffer[1024] = { 0 };
}

mono_lcd_lib_st7565 ayplayer_lcd_obj( &st7565_cfg, lcd_buffer );
