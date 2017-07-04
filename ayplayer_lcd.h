#pragma once

#include "ayplayer_port.h"
#include "ayplayer_spi.h"
#include "mono_lcd_lib_ssd1306.h"

const ssd1306_cfg_t ssd1306_cfg {
    .cs     = &lcd_cs_obj,
    .res    = &lcd_res_obj,
    .dc     = &lcd_dc_obj,
};

extern uint8_t lcd_buffer[1024];

const constexpr ssd1306 ayplayer_lcd( &ssd1306_cfg, lcd_buffer );

void ayplayer_lcd_init ( void );
