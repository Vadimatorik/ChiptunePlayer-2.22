#pragma once

#include "makise_e.h"

// SD + FATFS
#include "ayplayer_microsd_card.h"
#include "ayplayer_fat_love_level.h"

#include "ayplayer_gui_low.h"

// AY.
#include "ay_ym_low_lavel.h"
#include "ay_ym_file_mode.h"

// Вывод ошибки.
#include "ayplayer_gui_win_sd_card_error.h"

bool ayplayer_sd_card_scan ( char* dir, MContainer* c );
