#pragma once

#include "makise_e.h"

// SD + FATFS
#include "ayplayer_microsd_card.h"
#include "ayplayer_fat.h"

#include "ayplayer_gui_low.h"

// AY.
#include "ay_ym_low_lavel.h"
#include "ay_ym_file_mode.h"


enum class EC_SD_CARD_SCAN_ANSWER {
    OK                  = 0                     // Сканирование прошло удачно.
};

EC_SD_CARD_SCAN_ANSWER ayplayer_sd_card_scan ( char* dir, MContainer* c );
