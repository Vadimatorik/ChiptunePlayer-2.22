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

// Внутренние объекты (общие для всех окон).

extern MHost           host;
MContainer             c;
char                   path_dir[512] = "./";
FATFS                  fat;

//**********************************************************************
// Через данную задачу будут происходить все монипуляции с GUI.
//**********************************************************************
void ayplayer_gui_core_task ( void* param ) {
    ( void )param;
    // Готовим низкий уровень GUI и все необходимые структуры.
    ayplayer_gui_low_init();
    host.host       = &c;
    c = { &m_gui, nullptr, nullptr, nullptr, nullptr, nullptr };

    // Инициализация FAT объекта (общий на обе карты).
    FRESULT fr = f_mount( &fat, "", 0 );
    if ( fr != FR_OK ) while( true );

    // Пытаемся просканировать карту.
    ayplayer_sd_card_scan( path_dir, &c );

    while( true ) {
     //   m_progress_bar_set_duty( &pb, pb_duty );
    //    pb_duty++;
        //gui_update();


        vTaskDelay(800);
    }
}
