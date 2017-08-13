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
MHost           host;
MProgressBar    pb;
MLable          l_0;
MSList          sl;
MSList_Item     sl_item_array[6];

uint8_t         pb_duty = 0;

char test_string_0[] = "String 0";
char test_string_1[] = "String 1";

void ayplayer_gui_core_task ( void* param ) {
    (void)param;
    ayplayer_gui_low_init();
    MContainer      c = { &m_gui, nullptr, nullptr, nullptr, nullptr, nullptr };
    host.host       = &c;

    ayplayer_gui_window_sd_card_analysis_creature( c, pb, l_0, sl );

    MSList_Item ms = {
        .text       = test_string_0,
        .value      = 0,
        .prev       = 0,
        .next       = 0,
        .id         = 0
    };

    m_slist_add( &sl, &ms );


    while( true ) {
        m_progress_bar_set_duty( &pb, pb_duty );
        pb_duty++;

        makise_g_host_call( &host, M_G_CALL_PREDRAW );
        makise_g_host_call( &host, M_G_CALL_DRAW );
        m_gui_update( &m_gui );

        vTaskDelay(800);
    }
}
