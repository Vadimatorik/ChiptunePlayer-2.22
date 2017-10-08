#include "ayplayer_gui_core.h"

FATFS                  fat;
char                   path_dir[512] = "0:/";

// Элементы GUI.
MContainer             m_cont   = { &m_gui, nullptr, nullptr, nullptr, nullptr, nullptr };

MPlayList              gui_pl;
MPlayList_Item         gui_pl_item_array[4];
MPlayBar               gui_e_pb;

MPlayerStatusBar       gui_e_psb_copy_0;
MPlayerStatusBar       gui_e_psb_copy_1;
  //USER_OS_TAKE_MUTEX( m_mhost, portMAX_DELAY );
//ayplayer_control.active_window_get()
// USER_OS_GIVE_MUTEX( m_mhost );
extern MakiseGUI       m_gui;  

//**********************************************************************
// Обновляет экран раз в секунду,
// если никто другой не обновил за это время.
//**********************************************************************
void ayplayer_gui_update_task ( __attribute__((unused)) void* param ) {
    while ( true ) {
        if ( USER_OS_TAKE_BIN_SEMAPHORE( s_gui_update, 1000 ) == pdFALSE ) {
            gui_update();
        }
    }
}

char sd2_not_presence[] = "System microsd not presence!";

//**********************************************************************
// Через данную задачу будут происходить все монипуляции с GUI.
//**********************************************************************
void ayplayer_gui_core_task ( __attribute__((unused)) void* param ) {
    // Настраиваем потенциометры.
    sound_dp.connect_on();
    ayplayer_control.dp_update_value();

    // Проверяем наличие SD карты.
    while(1){

    if ( !sd2_get_presence_state() ) {
        ayplayer_error_string_draw( &m_cont, sd2_not_presence );
    }
}

    // Инициализация FAT объекта (общий на обе карты).
    FRESULT fr = f_mount( &fat, "", 0 );
    if ( fr != FR_OK ) {
        ayplayer_error_microsd_draw( &m_cont, fr );
    }







    //uint8_t b_buf_nember;

    // Составить список PSG файлов, если нет такого на карте.
    FIL file_list;
    fr = f_open( &file_list, "psg_list.txt", FA_READ );

    if ( fr == FR_NO_FILE )     ayplayer_sd_card_scan( path_dir, &m_cont );

    /*
    // Готовим низкий уровень GUI и все необходимые структуры.
    ayplayer_gui_low_init();
    container_set_to_mhost();                                           // Выбираем системное окно.

    // Статус бар. Он есть во всех неигровых окнах.
    ayplayer_gui_player_status_bar_creature( &ayplayer_gui_win_play_list, &gui_e_psb_copy_0 );
    ayplayer_gui_player_status_bar_creature( &ayplayer_gui_win_play, &gui_e_psb_copy_1 );

    // Конфигурируем постоянные окна (которые живут все время).
    ayplayer_gui_window_play_list_creature( &ayplayer_gui_win_play_list, &gui_pl, gui_pl_item_array, path_dir );
    ayplayer_gui_window_main_creature( &ayplayer_gui_win_play, &gui_e_pb );

    ayplayer_control.active_window_set( EC_AY_ACTIVE_WINDOW::MAIN );
    container_set_to_mhost();

    makise_g_focus( &gui_pl.e, M_G_FOCUS_GET );
    gui_update();

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
                ayplayer_control.active_window_set( EC_AY_ACTIVE_WINDOW::MAIN );
                container_set_to_mhost();
                break;
            }
            makise_gui_input_perform( &host );
            gui_update();
            break;

        case M_EC_TO_U32( EC_AY_ACTIVE_WINDOW::MAIN ):
            switch ( b_buf_nember ) {
            case M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ):
                ayplayer_control.active_window_set( EC_AY_ACTIVE_WINDOW::PLAY_LIST );
                container_set_to_mhost();
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
                ay_player_interrupt_ay.period_dev( 2 );
                break;

            // Перемотка назад закончилась.
            case M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ):
                ay_player_interrupt_ay.period_reset();
                break;
            }
            gui_update();
            break;
        }
    }*/
}

//**********************************************************************
// Задача GUI.
//**********************************************************************
void ayplayer_gui_core_init ( void ) {
    USER_OS_STATIC_TASK_CREATE( ayplayer_gui_core_task, "gui_main", TB_GUI_SIZE, NULL, GUI_CORE_TASK_PRIO, tb_gui, &ts_gui );
    USER_OS_STATIC_TASK_CREATE( ayplayer_gui_update_task, "gui_up", TB_STATUS_BAR_UPDATE_SIZE, NULL, GUI_UPDATE_TASK_PRIO, tb_gui_status_bar_update, &ts_gui_status_bar_update );
    m_mhost_init();
    s_gui_update_init();
}
