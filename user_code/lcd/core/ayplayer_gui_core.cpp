#include "ayplayer_gui_core.h"

static StaticTask_t     ayplayer_gui_task_buffer;
static StackType_t      ayplayer_gui_task_stack[ AY_PLAYER_GUI_TASK_STACK_SIZE ];

// Задача GUI.
void ayplayer_gui_core_init ( void ) {
    xTaskCreateStatic( ayplayer_gui_core_task,
                       "gui",
                       AY_PLAYER_GUI_TASK_STACK_SIZE,
                       NULL,
                       3,
                       ayplayer_gui_task_stack,
                       &ayplayer_gui_task_buffer );
}

ayplayer_state ayplayer_control;

// Внутренние объекты (общие для всех окон).

extern MHost           host;
MContainer             c;
char                   path_dir[512] = "0:/";
FATFS                  fat;
MPlayList              pl;
extern  USER_OS_STATIC_QUEUE         ay_b_queue;

//**********************************************************************
// Через данную задачу будут происходить все монипуляции с GUI.
//**********************************************************************
void ayplayer_gui_core_task ( void* param ) {
    ( void )param;
    // Готовим низкий уровень GUI и все необходимые структуры.
    ayplayer_gui_low_init();
    host.host       = &c;
    c = { &m_gui, nullptr, nullptr, nullptr, nullptr, nullptr };

    uint8_t b_buf_nember;

    // Инициализация FAT объекта (общий на обе карты).
    FRESULT fr = f_mount( &fat, "", 0 );
    if ( fr != FR_OK ) while( true );

    // Составить список PSG файлов, если нет такого на карте.
    FIL file_list;
    if ( f_open( &file_list, "psg_list.txt", FA_READ ) == FR_NO_FILE ) {
        ayplayer_sd_card_scan( path_dir, &c );
    }

    MPlayList_Item      pl_item_array[4];
    ayplayer_gui_window_file_list_creature( &c, &pl, pl_item_array, path_dir );
    makise_g_focus( &pl.e, M_G_FOCUS_GET );
    gui_update();

    while ( true ) {
        USER_OS_QUEUE_RECEIVE( ay_b_queue, &b_buf_nember, portMAX_DELAY );

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
            default:
                break;
            }
        }

        makise_gui_input_perform( &host );
        gui_update();
    }
}
