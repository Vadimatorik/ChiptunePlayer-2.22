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

#include "run_time_logger.h"
#include <errno.h>

extern MakiseGUI						m_gui;
extern MHost							host;
extern MContainer						m_cont;
extern FATFS							fat;

extern run_time_logger					ay_log_obj;

// Готовим низкий уровень GUI и все необходимые структуры.
bool init_gui ( __attribute__((unused)) const fsm_step* previous_step ) {
    host.host                       = &m_cont;
    makise_start( &m_gui );
    ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "MakiseGui started." );
    return true;
}

// Настраиваем потенциометры.
bool dp_init ( __attribute__((unused)) const fsm_step* previous_step ) {
	EC_AD5204_ANSWER res;
    sound_dp.connect_off();
    res = ayplayer_control.dp_update_value();
    sound_dp.connect_on();

    if ( res == EC_AD5204_ANSWER::OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "Digital potentiometer set up." );
    	return true;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "Digital potentiometer not configured! SPI error!" );
    	return false;
    }
}

// Инициализация FAT.
bool fat_init ( __attribute__((unused)) const fsm_step* previous_step ) {
    FRESULT fr;
    fr = f_mount( &fat, "0:", 0 );

    if ( fr == FR_OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "FatFS initialized successfully." );
        return true;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "FatFS was not initialized!" );
    	return false;
    }
}

// Ждем стабилизации питания.
bool waiting_for_food_stabilization ( __attribute__((unused)) const fsm_step* previous_step ) {
	USER_OS_DELAY_MS(50);
	return true;
}

bool sd2_connect ( __attribute__((unused)) const fsm_step* previous_step ) {
	while(1) ayplayer_error_string_draw( &m_cont, "Attempt to discover SD2..." );
	if ( system_card_chack() == ECONNREFUSED ) {										// Проверяем наличие карты SD2.
		ay_log_obj.send_message( RTL_TYPE_M::INIT_ISSUE, "No SD2!" );					// Если карты нет, то делаем 5 попыток ее обноружить.
		DSTATUS r;
		uint32_t down_count = 5;
		while( down_count ) {
			ay_log_obj.send_message( RTL_TYPE_M::INIT_ISSUE, "Attempt to discover SD2..." );
			r = disk_initialize(0);
			if ( r == RES_OK ) {
				ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
				break;
			}
			USER_OS_DELAY_MS(100);
			down_count--;
		}
		ay_log_obj.send_message( RTL_TYPE_M::INIT_ISSUE, "Attempts SD2 failed." );
	} else {
		ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
	}

	// Не важно, есть флешка или нет. Мы просто сохраним в объект, что флешка отсутствует.
	return true;
}

