#include "ayplayer_fsm_step.h"

// Конфигурации окон.
#include "ayplayer_gui_win_sd_card_analysis.h"
#include "ayplayer_gui_win_file_list.h"
#include "ayplayer_gui_win_main.h"
#include "ayplayer_gui_player_status_bar.h"
#include "ayplayer_gui_win_error.h"

// SD + FATFS
#include "ayplayer_microsd_card.h"
#include "ayplayer_fat_love_level.h"

// Кнопки.
#include "ayplayer_button.h"
#include "ayplayer_digital_potentiometer.h"

#include "ayplayer_core_obj.h"

#include "ayplayer_timers.h"
#include "ayplayer_os_object.h"

#include "ayplayer_fat_api.h"

extern MakiseGUI						m_gui;
extern MHost							host;
extern MContainer						m_cont;
extern FATFS							fat;

// Готовим низкий уровень GUI и все необходимые структуры.
bool init_gui ( __attribute__((unused)) const fsm_step* previous_step ) {
    host.host                       = &m_cont;
    makise_start( &m_gui );
    return true;
}

// Настраиваем потенциометры.
bool dp_init ( __attribute__((unused)) const fsm_step* previous_step ) {
    sound_dp.connect_off();
    ayplayer_control.dp_update_value();
    sound_dp.connect_on();
    return true;
}

bool fat_init ( __attribute__((unused)) const fsm_step* previous_step ) {
    FRESULT fr;
    fr = f_mount( &fat, "0:", 0 );

    if ( fr != FR_OK ) {                                                                        // Решаем вопрос с системной картой.
        return false;
    } else return true;
}

