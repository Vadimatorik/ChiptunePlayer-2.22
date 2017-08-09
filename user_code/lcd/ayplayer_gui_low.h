#pragma once

#include "ayplayer_lcd.h"
#include "freertos_headers.h"
#include "ayplayer_microsd_card.h"

#include "makise.h"
#include "makise_gui.h"

void ayplayer_gui_init ( void );                // Инициализирует задчу (вызывать до ОС).
void ayplayer_lcd_update_task ( void );         // Задача разруливает перемещение по меню.
