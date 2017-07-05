#pragma once

#include "ayplayer_port.h"
#include "ayplayer_spi.h"
#include "mono_lcd_lib_st7565.h"
#include "simple_mono_drawing_lib.h"

const mono_lcd_lib_st7565_cfg_t st7565_cfg {
    .a0     = &lcd_dc_obj,
    .res    = &lcd_res_obj,
    .cs     = &lcd_cs_obj,
};

extern uint8_t lcd_buffer[1024];

const mono_lcd_lib_st7565 ayplayer_lcd( &st7565_cfg, lcd_buffer );
const constexpr simple_drawing_lib sd_lcd( lcd_buffer );

void ayplayer_lcd_init ( void );
