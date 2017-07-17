#pragma once

#include "mono_lcd_lib_st7565.h"
#include "ayplayer_port.h"
#include "ayplayer_spi.h"
#include "simple_mono_drawing_lib.h"

extern uint8_t lcd_buffer[1024];

extern mono_lcd_lib_st7565 ayplayer_lcd;
/*
 * Метод инициализирует экран из ОС.
 */
void ayplayer_lcd_init ( uint8_t contrast );
