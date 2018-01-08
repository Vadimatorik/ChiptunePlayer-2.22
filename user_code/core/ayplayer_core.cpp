#include "ayplayer_core.h"
#include <stdio.h>

char                   path_dir[512] = "0:/";

// Элементы GUI.
MContainer             m_cont   = { &m_gui, nullptr, nullptr, nullptr, nullptr, nullptr };

MPlayList              gui_pl;
MPlayList_Item         gui_pl_item_array[4];
MPlayBar               gui_e_pb;

MPlayerStatusBar       gui_e_psb;
  //USER_OS_TAKE_MUTEX( m_mhost, portMAX_DELAY );
//ayplayer_control.active_window_get()
// USER_OS_GIVE_MUTEX( m_mhost );
extern MakiseGUI       m_gui;  
extern MHost           host;
//**********************************************************************
// Обновляет экран раз в секунду,
// если никто другой не обновил за это время.
//**********************************************************************
void ayplayer_gui_update_task ( __attribute__((unused)) void* param ) {
    while ( true ) {
        if ( USER_OS_TAKE_BIN_SEMAPHORE( s_gui_update, 1000 ) == pdFALSE ) {
            if ( ayplayer_control.stait_get() == EC_AY_STATE::RUN )
            gui_update();
        }
    }
}

void select_window_main ( void ) {
    USER_OS_TAKE_MUTEX( m_mhost, portMAX_DELAY );
    ayplayer_gui_player_status_bar_creature( &m_cont, &gui_e_psb );
    ayplayer_gui_window_main_creature( &m_cont, &gui_e_pb );
    ayplayer_control.active_window_set( EC_AY_ACTIVE_WINDOW::MAIN );
    USER_OS_GIVE_MUTEX( m_mhost );
}

void select_window_play_list ( void ) {
    USER_OS_TAKE_MUTEX( m_mhost, portMAX_DELAY );
    ayplayer_gui_player_status_bar_creature( &m_cont, &gui_e_psb );
    ayplayer_gui_window_play_list_creature( &m_cont, &gui_pl, gui_pl_item_array, path_dir );
    makise_g_focus( &gui_pl.e, M_G_FOCUS_GET );
    ayplayer_control.active_window_set( EC_AY_ACTIVE_WINDOW::PLAY_LIST );
    USER_OS_GIVE_MUTEX( m_mhost );
}

/*
static bool delay_max ( const fsm_step* previous_step ) {
    ( void )previous_step;
    while( true ) {
        USER_OS_DELAY_MS( 1000 );
    }
    return false;
}*/


// Настраиваем потенциометры.
/*
static bool dp_init ( const fsm_step* previous_step ) {
    ( void )previous_step;
    sound_dp.connect_off();
    ayplayer_control.dp_update_value();
    sound_dp.connect_on();
    return true;
}*/

// @startuml
// state NotShooting {
// }
// @enduml
#include "run_time_logger.h"

extern const fsm_step step_gui_init;
fsm core_fsm( &step_gui_init );

extern run_time_logger ay_log_obj;

//**********************************************************************
// Через данную задачу будут происходить все монипуляции с GUI.
//**********************************************************************
void ayplayer_core_task ( __attribute__((unused)) void* param ) {
	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "FreeRTOS started." );
	ay_log_obj.send_message( RTL_TYPE_M::INIT_OK, "FSM started." );
	core_fsm.start();


	while(1) vTaskDelay(1000);

	// Сюда пришли точно с рабочей картой.
    // Составить список PSG файлов, если нет такого на карте.
    FIL file_list;
    DSTATUS fr = f_open( &file_list, "playlist.sys", FA_READ );
    if ( fr == FR_NO_FILE ) {                                                                   // Если файл просто не был найден - составляем список.
        ayplayer_sd_card_scan( path_dir, &m_cont );
    } else if ( fr != FR_OK ) {                                                                 // Если просто какой-то баг при открытии.
        const char er[] = "E:SD2:1";
        ayplayer_error_string_draw( &m_cont, er );
        //delay_max();
    }

    // Формируем главное окно.
    select_window_main();

    gui_update();
    ayplayer_control.stait_set( EC_AY_STATE::RUN );

    uint8_t b_buf_nember;

    while ( true ) {
        USER_OS_QUEUE_RESET( q_ay_button );  // Старые команды нас не интересуют.
        USER_OS_QUEUE_RECEIVE( q_ay_button, &b_buf_nember, portMAX_DELAY );

        switch ( M_EC_TO_U32( ayplayer_control.active_window_get() ) ) {
        case M_EC_TO_U32( EC_AY_ACTIVE_WINDOW::PLAY_LIST ):
            switch ( b_buf_nember ) {
            case M_EC_TO_U8( EC_BUTTON_NAME::DOWN ):
                makise_gui_input_send_button( &host, M_KEY_DOWN, M_INPUT_CLICK, 0 );
                break;

            case M_EC_TO_U8( EC_BUTTON_NAME::UP ):
                makise_gui_input_send_button( &host, M_KEY_UP, M_INPUT_CLICK, 0 );
                break;

            case M_EC_TO_U8( EC_BUTTON_NAME::ENTER ):
                makise_gui_input_send_button( &host, M_KEY_OK, M_INPUT_CLICK, 0 );
                break;

            case M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK ):
                select_window_main();
                break;
            }
            makise_gui_input_perform( &host );
            gui_update();
            break;

        case M_EC_TO_U32( EC_AY_ACTIVE_WINDOW::MAIN ):
            switch ( b_buf_nember ) {
            case M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ):
                select_window_play_list();
                break;

            // Эмулируем проход по play_list.
            case M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK ):
                m_click_play_list( &gui_pl, M_KEY_UP );
                m_click_play_list( &gui_pl, M_KEY_OK );
                break;

            case M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK ):
                m_click_play_list( &gui_pl, M_KEY_DOWN );
                m_click_play_list( &gui_pl, M_KEY_OK );
                break;

            case M_EC_TO_U8( EC_BUTTON_NAME::ENTER ):
                m_click_play_list( &gui_pl, M_KEY_OK );
                break;

            // Началась перемотка вперед.
            case M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ):
               //ay_player_interrupt_ay.period_dev( 2 );
                break;

            // Перемотка назад закончилась.
            case M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ):
                //ay_player_interrupt_ay.period_reset();
                break;
            }
            gui_update();
            break;
        }
    }
}

//**********************************************************************
// Задача GUI.
//**********************************************************************
void ayplayer_core_init ( void ) {
    USER_OS_STATIC_TASK_CREATE( ayplayer_core_task, "gui_main", TB_GUI_SIZE, NULL, CORE_TASK_PRIO, tb_gui, &ts_gui );
    //USER_OS_STATIC_TASK_CREATE( ayplayer_gui_update_task, "gui_up", TB_STATUS_BAR_UPDATE_SIZE, NULL, GUI_UPDATE_TASK_PRIO, tb_gui_status_bar_update, &ts_gui_status_bar_update );
    m_mhost_init();
    s_gui_update_init();
}
