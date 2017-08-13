#pragma once

#include "ayplayer_lcd_driver.h"
#include "freertos_headers.h"
#include "ayplayer_microsd_card.h"

#include "makise.h"
#include "makise_gui.h"

// Конфигурацию нижнего уровня GUI вызывать только из под какой-либо задачи ОС!
void ayplayer_gui_low_init ( void );

extern "C" {

extern MakiseGUI m_gui;
void m_gui_update ( MakiseGUI* gui );

}

void gui_update ( void );
