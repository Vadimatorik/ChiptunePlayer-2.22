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

#include "run_time_logger.h"
#include <errno.h>

extern MakiseGUI						m_gui;
extern MHost							host;
extern MContainer						m_cont;

FATFS									fat;
FIL										file_list;
extern run_time_logger					ay_log_obj;

// Готовим низкий уровень GUI и все необходимые структуры.
int init_gui ( __attribute__((unused)) const fsm_step* previous_step ) {
    host.host                       = &m_cont;
    makise_start( &m_gui );
    ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "MakiseGui started." );
    return 0;
}

// Настраиваем потенциометры.
int dp_init ( __attribute__((unused)) const fsm_step* previous_step ) {
	EC_AD5204_ANSWER res;
    sound_dp.connect_off();
    res = ayplayer_control.dp_update_value();
    sound_dp.connect_on();

    if ( res == EC_AD5204_ANSWER::OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "Digital potentiometer set up." );
    	return 0;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "Digital potentiometer not configured! SPI error!" );
    	return FSM_RET_ERROR;	// Такого быть не должно точно. Выходим с ошибкой.
    }
}

// Инициализация FAT.
int fat_init ( __attribute__((unused)) const fsm_step* previous_step ) {
    FRESULT fr;
    fr = f_mount( &fat, "0:", 0 );

    if ( fr == FR_OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "FatFS initialized successfully." );
        return 0;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "FatFS was not initialized!" );
    	return FSM_RET_ERROR;
    }
}

// Ждем стабилизации питания.
int waiting_for_food_stabilization ( __attribute__((unused)) const fsm_step* previous_step ) {
	USER_OS_DELAY_MS(50);
	return 0;
}

// Проверяем наличие в слоте microsd.
// 0 - все четко.
// 1 - карты нет.
int sd2_chack ( __attribute__((unused)) const fsm_step* previous_step ) {
	EC_MICRO_SD_TYPE r;
	r = sd2.initialize();
	if ( r != EC_MICRO_SD_TYPE::ERROR ) {
		ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
		ayplayer_error_string_draw( &m_cont, "SD2 is detected!" );
		return 0;
	} else {
		ay_log_obj.send_message( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" );
		ayplayer_error_string_draw( &m_cont, "SD2 missing!" );
		return FSM_RET_REPEAT;
	}
}

// Проверяем наличие системного файла со списком треков.
// 0 - файл уже существует.
// 1 - файл отсуствует.
// 2 - невозможно прочитать.
int sd2_track_file_open ( __attribute__((unused)) const fsm_step* previous_step ) {
    DSTATUS fr = f_open( &file_list, "playlist.sys", FA_READ );
    if ( fr == FR_OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "File <<playlist.sys>> open." );
    	ayplayer_error_string_draw( &m_cont, "File <<playlist.sys>>\n open." );
    	return 0;
    }

    if ( fr == FR_NO_FILE ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "File <<playlist.sys>> does not exist." );
    	ayplayer_error_string_draw( &m_cont, "File <<playlist.sys>>\ndoes not exist." );
    	return 1;
    }

    ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "File <<playlist.sys>> create/open error!" );
    ayplayer_error_string_draw( &m_cont, "File <<playlist.sys>>\ncreate/open error!" );
    return 2;
}

//         ayplayer_sd_card_scan( path_dir, &m_cont );

