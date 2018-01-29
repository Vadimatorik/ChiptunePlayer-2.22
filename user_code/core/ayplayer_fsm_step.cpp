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
#include "ayplayer_fat_love_level.h"

ayplayer_global_data_struct g;
extern run_time_logger					ay_log_obj;

extern "C" {
	extern const MakiseGUI m_gui;
}


int init_gui ( __attribute__((unused)) const fsm_step* previous_step ) {
	g.m_cont.gui						= ( MakiseGUI* )&m_gui;
	g.m_host.host						= &g.m_cont;
	g.m_host.host->gui					= ( MakiseGUI* )&m_gui;

    makise_start( g.m_host.host->gui );
    ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "MakiseGui started." );
    return 0;
}


int dp_init ( __attribute__((unused)) const fsm_step* previous_step ) {
	EC_AD5204_ANSWER res;
    sound_dp.connect_off();
    res = dp_update_value();
    sound_dp.connect_on();

    if ( res == EC_AD5204_ANSWER::OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "Digital potentiometer set up." );
    	return 0;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "Digital potentiometer not configured! SPI error!" );
        return FSM_RET_ERROR;
    }
}


int fat_init ( __attribute__((unused)) const fsm_step* previous_step ) {
    FRESULT fr;
    fr = f_mount( &g.fat, "0:", 0 );

    if ( fr == FR_OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "FatFS initialized successfully." );
        return 0;
    } else {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "FatFS was not initialized!" );
    	return FSM_RET_ERROR;
    }
}


int waiting_for_food_stabilization ( __attribute__((unused)) const fsm_step* previous_step ) {
	USER_OS_DELAY_MS(50);
	return 0;
}



int sd2_chack ( __attribute__((unused)) const fsm_step* previous_step ) {
	DSTATUS r;
	r = disk_status( 0 );
	if ( r == STA_NODISK ) {
		ay_log_obj.send_message( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" );
		ayplayer_error_string_draw( &g.m_cont, "SD2 missing!" );
		return FSM_RET_REPEAT;

	} else {
		ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "SD2 is detected!" );
		ayplayer_error_string_draw( &g.m_cont, "SD2 is detected!" );
		return 0;
	}
}

int sd2_track_file_open ( __attribute__((unused)) const fsm_step* previous_step ) {
	FRESULT fr = f_open( &g.file_list, "playlist.sys", FA_READ );
    if ( fr == FR_OK ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "File <<playlist.sys>> open." );
    	ayplayer_error_string_draw( &g.m_cont, "File <<playlist.sys>>\n open." );
    	return 0;
    }

    if ( fr == FR_NO_FILE ) {
    	ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "File <<playlist.sys>> does not exist." );
    	ayplayer_error_string_draw( &g.m_cont, "File <<playlist.sys>>\ndoes not exist." );
    	return 1;
    }

    ay_log_obj.send_message( RTL_TYPE_M::INIT_ERROR, "File <<playlist.sys>> create/open error!" );
    ayplayer_error_string_draw( &g.m_cont, "File <<playlist.sys>>\ncreate/open error!" );
    return 2;
}

//         ayplayer_sd_card_scan( path_dir, &m_cont );

