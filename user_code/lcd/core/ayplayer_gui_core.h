#include "ayplayer_gui_low.h"

// Конфигурации окон.
#include "ayplayer_gui_window_sd_card_analysis.h"

// SD + FATFS
#include "ayplayer_microsd_card.h"
#include "ayplayer_fat.h"

// 400 байт задаче.
#define AY_PLAYER_GUI_TASK_STACK_SIZE       10000

// Вызвать до запуска ОС.
void ayplayer_gui_core_init ( void );                   // Создает задачу для контроля всей графики.

// Основная задача ядра GUI.
void ayplayer_gui_core_task ( void* param );
