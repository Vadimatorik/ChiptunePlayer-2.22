#include "ayplayer_gui_low.h"

// Конфигурации окон.
#include "ayplayer_gui_win_sd_card_analysis.h"
#include "ayplayer_gui_win_file_list.h"
#include "ayplayer_gui_win_main.h"
#include "ayplayer_gui_player_status_bar.h"

// SD + FATFS
#include "ayplayer_microsd_card.h"
#include "ayplayer_fat.h"

// Rнопки.
#include "ayplayer_button.h"

#include "ayplayer_core_struct.h"

// 400 байт задаче.
#define AY_PLAYER_GUI_TASK_STACK_SIZE       10000

#include "ayplayer_timers.h"

// Вызвать до запуска ОС.
void ayplayer_gui_core_init ( void );                   // Создает задачу для контроля всей графики.

// Основная задача ядра GUI.
void ayplayer_gui_core_task ( void* param );
