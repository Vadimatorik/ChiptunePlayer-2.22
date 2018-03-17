#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"
#include "makise.h"
#include "makise_gui.h"
#include "ff.h"
#include "diskio.h"



/*!
 * Основное дерево проекта.
 */
extern const fsm_step< ay_player_class > ay_player_class_init_gui_fsm_step;

extern "C" {
extern const MakiseGUI m_gui;
}

void ay_player_class::main_task ( void* p_obj ) {
	ay_player_class* o = ( ay_player_class* )p_obj;
	o->fsm.relinking( &ay_player_class_init_gui_fsm_step, o );
	o->fsm.start();
}

int ay_player_class::fsm_step_func_init_gui ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );

	obj->g.c.gui						= ( MakiseGUI* )&m_gui;
	obj->g.h.host						= &obj->g.c;
	obj->g.h.host->gui					= ( MakiseGUI* )&m_gui;

	int r;
	r = makise_start( obj->g.h.host->gui );
	if ( r != M_OK ) {
		return 1;
	}

	if ( obj->l->send_message( RTL_TYPE_M::INIT_OK, "MakiseGui started." ) != BASE_RESULT::OK ) return 2;

	return 0;
}

int ay_player_class::fsm_step_func_fat_init ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	FRESULT fr;
	fr = f_mount( &obj->f, "0:", 0 );

	if ( fr == FR_OK ) {
		if ( obj->l->send_message( RTL_TYPE_M::INIT_OK, "FatFS initialized successfully." ) != BASE_RESULT::OK ) return 2;
		return 0;
	} else {
		if ( obj->l->send_message( RTL_TYPE_M::INIT_OK, "FatFS was not initialized!" ) != BASE_RESULT::OK ) return 2;
		return 1;
	}
}

int ay_player_class::fsm_step_func_sd1_check ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	DSTATUS r;
	r = disk_status( 0 );
	if ( r == STA_NODISK ) {
		if ( obj->l->send_message( RTL_TYPE_M::INIT_ISSUE, "SD2 missing!" ) != BASE_RESULT::OK ) return 2;
		return 1;
	} else {
		if ( obj->l->send_message( RTL_TYPE_M::INIT_OK, "SD2 is detected!" ) != BASE_RESULT::OK ) return 2;
		return 0;
	}
}

int ay_player_class::fsm_step_func_check_playlist_sys ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	DSTATUS r;
	char path[] = "0:/playlist.sys";
	r = f_stat( path, &obj->sd1_fi );
	switch( ( uint32_t )r ) {
	case FR_OK:
		if ( obj->l->send_message( RTL_TYPE_M::INIT_ISSUE, "The <<0:/playlist.sys>> file exists!" ) != BASE_RESULT::OK ) return 2;
		return 3;///0;
	case FR_NO_FILE:
		if ( obj->l->send_message( RTL_TYPE_M::INIT_ISSUE, "The <<0:/playlist.sys>> file not exists!" ) != BASE_RESULT::OK ) return 2;
		return 3;
	default:
		return 1;
	}
}

int ay_player_class::fsm_step_func_create_playlist_sys ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	UNUSED( obj );

	DSTATUS r;

	FIL		f_list;



	/// Поиск по маске PSG.
	FILINFO		f_scan;

	UINT		writing_byte;
	r = f_findfirst( &obj->sd1_fdir, &f_scan, "0:/", "*.psg");
	while ( r == FR_OK && f_scan.fname[0] ) {
		uint32_t	len_file;
		EC_AY_FILE_MODE_ANSWER r_ay;
		r_ay = obj->ay_f->psg_file_get_long( f_scan.fname, len_file );
		if ( r_ay == EC_AY_FILE_MODE_ANSWER::OK ) {
			r = f_open( &f_list, "0:/playlist.sys", FA_WRITE | FA_CREATE_ALWAYS);
				if ( r != FR_OK ) {
				if ( r == FR_DISK_ERR ) return 1;
				return 3;
			}

			r = f_write( &f_list, f_scan.fname, 256, &writing_byte );
			if ( r == FR_DISK_ERR ) return 1;
			if ( writing_byte != 256 ) return 1;
			r = f_write( &f_list, &len_file, 4, &writing_byte );
			if ( r == FR_DISK_ERR ) return 1;
			if ( writing_byte != 4 ) return 1;

			r = f_close( &f_list );
		}

		r = f_findnext( &obj->sd1_fdir, &f_scan );
	}

	r = f_close( &f_list );
	if ( r != FR_OK ) {
		if ( r == FR_DISK_ERR ) return 1;
		return 3;
	}



	return 0;
}

int ay_player_class::fsm_step_func_gui_fall ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_logger_fall ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_fat_fall ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_sd1_fall ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	UNUSED( obj );
	if ( obj->l->send_message( RTL_TYPE_M::INIT_ISSUE, "Fall SDIO!" ) != BASE_RESULT::OK ) return 2;
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}



