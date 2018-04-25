#include "ayplayer.h"
#include "core_cm3.h"
#include "ayplayer_os_object.h"
#include "makise.h"
#include "makise_gui.h"
#include "ff.h"
#include "diskio.h"

#include "ayplayer_microsd_card.h"

/*
int ay_player_class::fsm_step_func_check_playlist_sys ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );
	DSTATUS r;
	char path[] = "0:/playlist.sys";
	r = f_stat( path, &obj->sd1_fi );
	switch( ( uint32_t )r ) {
	case FR_OK:
		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "The <<0:/playlist.sys>> file exists!" ) != BASE_RESULT::OK ) return 2;
		return 0;
	case FR_NO_FILE:
		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_ISSUE, "The <<0:/playlist.sys>> file not exists!" ) != BASE_RESULT::OK ) return 2;
		return 3;
	default:
		return 1;
	}
}

static int writeDataOfTreck ( FIL& f, char* nameTreck, uint32_t& len ) {
	int					intResult;
	UINT				writingByte;

	intResult = f_write( &f, nameTreck, 256, &writingByte );

	if ( intResult == FR_DISK_ERR ) {
		return 1;
	}

	if ( writingByte != 256 ) {
		return 1;
	}

	intResult = f_write( &f, &len, 4, &writingByte );

	if ( intResult == FR_DISK_ERR ) {
		return 1;
	}

	if ( writingByte != 4 ) {
		return 1;
	}

	return 0;
}

int ay_player_class::fsm_step_func_create_playlist_sys ( HANDLER_FSM_INPUT_DATA ) {
	UNUSED( previous_step );

	DSTATUS			r;
	FIL				f_list;

	if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "Creating file <<0:/playlist.sys>> in sd1." ) != BASE_RESULT::OK ) return 2;

	r = f_open( &f_list, "0:/playlist.sys", FA_WRITE | FA_CREATE_ALWAYS);
	if ( r != FR_OK ) {
		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<0:/playlist.sys>> in sd1 was not create." ) != BASE_RESULT::OK ) return 2;
		if ( r == FR_DISK_ERR ) return 1;
		return 3;
	}

	if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File <<0:/playlist.sys>> in sd1 created." ) != BASE_RESULT::OK ) return 2;

	/// Поиск по маске PSG.
	FILINFO		f_scan;

	if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "Started scanning <<.psg>> file in sd1." ) != BASE_RESULT::OK ) return 2;

	r = f_findfirst( &obj->sd1_fdir, &f_scan, "0:/", "*.psg");
	while ( r == FR_OK && f_scan.fname[0] ) {
		char massageBuf[1024];
		sprintf( massageBuf, "The file <<%s>> is found.", f_scan.fname );
		if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, massageBuf ) != BASE_RESULT::OK ) return 2;

		uint32_t	len_file;
		EC_AY_FILE_MODE_ANSWER r_ay;
		r_ay = obj->ay_f->psg_file_get_long( f_scan.fname, len_file );


		if ( r_ay == EC_AY_FILE_MODE_ANSWER::OK ) {
			sprintf( massageBuf, "Length file <<%lu>> ticks.", len_file );
			if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, massageBuf ) != BASE_RESULT::OK ) return 2;

			if ( writeDataOfTreck( f_list, f_scan.fname, len_file ) != 0 ) {
				if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_ERROR, "Write list file error!" ) != BASE_RESULT::OK ) return 2;
				return 1;
			} else {
				if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_OK, "File added to list." ) != BASE_RESULT::OK ) return 2;
			}
		} else {
			if ( obj->l->send_message( RTL_TYPE_M::RUN_MESSAGE_ERROR, "Length was not received." ) != BASE_RESULT::OK ) return 2;
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
*/

