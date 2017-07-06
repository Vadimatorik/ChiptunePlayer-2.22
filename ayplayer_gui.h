#pragma once

#include "ayplayer_lcd.h"
#include "mini_gui_by_vadimatorik_include_module.h"
#include "freertos_headers.h"

/*
// Структура главной формы.
typedef struct {
    int			psg_file_number;			// Колличество psg файлов в текущей директории.
    char		**string_menu;				// Указатель на массив указателей, в которых находятся именя строк, которые в данный момент отображаются на экране. Каждая строка будет 255 элементов.
    char		**string_time_many;
    uint32_t	*time;						// Время в цифровом предстовлении.
    char		dir[255];					// Текущая директория.

    // Для GUI.
    int			point_file;					// Файл, на котором сейчас указатель выбора. Счет с 0.
    int			play_file;					// Файл, который воспроизводится сейчас. Счет с 1.
    uint8_t 	flag;						// Флаг состояния воспроизведения. Указыват на то, в каком состоянии сейчас плеер (не играет ничего, играет, на паузе).
} main_form_cfg_t;

enum MICRO_SD_STATUS {
    PSG_NONE = 0,
    MICRO_SD_ERROR = 1,
};*/

void ayplayer_gui_init ( void );                // Инициализирует задчу (вызывать до ОС).
void ayplayer_gui_main_window_show ( void );    // Отрисовываем в буфере основное окно.
void ayplayer_lcd_update_task ( void );         // Задача разруливает перемещение по меню.
