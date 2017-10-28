#pragma once

#include "ayplayer_lcd_driver.h"
#include "freertos_headers.h"
#include "ayplayer_microsd_card.h"

#include "makise.h"
#include "makise_gui.h"

extern "C" {

extern MakiseGUI m_gui;

}

void gui_update ( void );
