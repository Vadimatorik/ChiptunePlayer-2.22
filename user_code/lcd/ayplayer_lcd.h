#pragma once

#include "ayplayer_port.h"
#include "ayplayer_spi.h"
#include "mono_lcd_lib_st7565.h"

extern mono_lcd_lib_st7565 ayplayer_lcd;

//
// Метод инициализирует экран из ОС.
//
void ayplayer_lcd_init ( uint8_t contrast );
