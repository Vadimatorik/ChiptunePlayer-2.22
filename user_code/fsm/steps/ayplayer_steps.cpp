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

int ay_player_class::fsm_step_func_init_gui ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
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

int ay_player_class::fsm_step_func_fat_init ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
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

int ay_player_class::fsm_step_func_sd1_check ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
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

int ay_player_class::fsm_step_func_gui_fall ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_logger_fall ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}

int ay_player_class::fsm_step_func_fat_fall ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj ) {
	UNUSED( previous_step );
	UNUSED( obj );
	NVIC_SystemReset();			/// Контроллер перезагрузится тут.
	return 0;					/// Возвращено не будет.
}
