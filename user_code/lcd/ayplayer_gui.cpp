#include "ayplayer_gui.h"

//#########################################
// Используемые объекты.
//#########################################
const constexpr simple_drawing_lib sd_lcd( lcd_buffer );                // Рисование приметивов.

#define GUI_MAIN_WINDOW_STRING_COUNT        3
#define GUI_MAIN_WINDOW_STRING_COUNT_CHAR   100

char string_name_0[GUI_MAIN_WINDOW_STRING_COUNT_CHAR] = { 0 };
char string_name_1[GUI_MAIN_WINDOW_STRING_COUNT_CHAR] = { 0 };
char string_name_2[GUI_MAIN_WINDOW_STRING_COUNT_CHAR] = { 0 };

char* gui_main_window_string_name_array[GUI_MAIN_WINDOW_STRING_COUNT] = {
    string_name_0, string_name_1, string_name_2
};

char string_time_0[6] = "00:00";
char string_time_1[6] = "00:00";
char string_time_2[6] = "00:00";

char* gui_main_window_string_time_array[GUI_MAIN_WINDOW_STRING_COUNT] = {
    string_time_0, string_time_1, string_time_2
};

/*
 * Прослойка методов рисования (между объектами GUI и библиотекой рисования).
 */
static void virtual_layer_fill_rect ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const bool& color ) {
    sd_lcd.fill_rect( x1, y1, x2, y2, color );
}

void virtual_layer_print_string ( const font_t& font, uint8_t x, uint8_t y, char *string, const bool& color, const bool& rle ) {
    sd_lcd.print_string( font, x, y,string, color, rle );
}

static void virtual_layer_print_string_number ( const font_t& font, uint8_t x, uint8_t y, char *string, uint8_t number_char, const bool& color, const bool& rle ) {
    sd_lcd.print_string_number( font, x, y, string, number_char, color, rle );
}

static void virtual_layer_draw_frame ( const uint8_t& x, const uint8_t& y, const uint8_t& width, const uint8_t& height, const uint8_t& thickness, const bool& color ) {
    sd_lcd.draw_frame( x, y, width, height, thickness, color );
}

static void virtual_layer_fill_rect_and_frame ( const uint8_t& x, const uint8_t& y, const uint8_t& width, const uint8_t& height, const uint8_t& thickness, const bool& color_rect, const bool& color_line ) {
    sd_lcd.fill_rect_and_frame( x, y, width, height, thickness, color_rect, color_line );
}

/*
 * Объекты главного окна.
 */
mini_gui_by_vadimatorik_lcd_mono_string_box_cfg_t gui_main_window_string_box_init_cfg = {
    .fill_rect                  = virtual_layer_fill_rect,
    .print_string_number        = virtual_layer_print_string_number,
    .draw_frame                 = virtual_layer_draw_frame,
    .fill_rect_and_frame        = virtual_layer_fill_rect_and_frame,

    .width_string_box_pixel     = 128,
    .height_string_box_pixel    = 52,   // 12 пикселей шрифт * 4 строки, + 2 пикселя между зазор сверху и 2 снизу.
    .width_line                 = 1,
    .thickness_slider           = 5,
    .x_pos                      = 0,
    .y_pos                      = 0,

    .string_number              = 3,
    .string_name                = gui_main_window_string_name_array,
    .string_time                = gui_main_window_string_time_array,

    .font                       = &font_gost_type_b_12_rle,
    .font_rle                   = true
};

mini_gui_by_vadimatorik_lcd_mono_string_box main_s_box( &gui_main_window_string_box_init_cfg );

mini_gui_by_vadimatorik_status_bar_mono_cfg_t gui_main_window_status_bar_init_cfg = {
    .fill_rect                  = virtual_layer_fill_rect,
    .draw_frame                 = virtual_layer_draw_frame,

    .width_bar_pixel            = 76,
    .height_barpixel            = 6,
    .width_line                 = 1,
    .x_pos                      = 26,
    .y_pos                      = 64 - 6 - 2
};

mini_gui_by_vadimatorik_lcd_mono_status_bar main_status_bar( &gui_main_window_status_bar_init_cfg );

mini_gui_by_vadimatorik_lcd_mono_play_bar_init_cfg_t gui_main_window_play_bar_init_cfg = {
    .status_bar_obj             = &main_status_bar,
    .print_string               = virtual_layer_print_string,
    .fill_rect                  = virtual_layer_fill_rect,

    .time_up_font               = &font_gost_type_b_12_rle,
    .string_time_up_rle         = true,
    .y_time                     = 64 - 12,
    .width_status_bar           = 128,
    .time_down_font             = &font_gost_type_b_12_rle,
    .string_time_down_rle       = true,
    .height_font_up             = 12,
    .height_font_down           = 12,
    .spase                      = 0
};

mini_gui_by_vadimatorik_lcd_mono_play_bar main_play_bar( &gui_main_window_play_bar_init_cfg );

/*
extern FATFS 	*fat_fs_cfg_microsd;
extern xQueueHandle button_click;
extern xQueueHandle fat_command;
extern xSemaphoreHandle semaphore_sec_out_ay;
extern int ay_file_fd;
extern int ay_fd;
extern int lcd_fd;
extern int tim_event_fd;
extern const tFont font_gost_type_b_12_rle;			// Используем шрифт, сжатый RLE. Для экномии места.
*/

/*
 * Инициализируем объекты формы.
 */
void ayplayer_gui_main_window_show ( void ) {
    sd_lcd.clear();
    main_s_box.reset(0,0,10,0);
    main_play_bar.reset();
    ayplayer_lcd.clear();
    ayplayer_lcd.update();
}

extern const pin shdn_obj;

void ayplayer_lcd_update_task ( void* param ) {
    (void)param;
    ayplayer_lcd_init( 8 );
    ayplayer_gui_main_window_show();

    while( true ) {
        vTaskDelay(1000);
    }
}

// 400 байт задаче.
#define AY_PLAYER_GUI_TASK_STACK_SIZE       200
static StaticTask_t     ayplayer_gui_task_buffer;
static StackType_t      ayplayer_gui_task_stack[ AY_PLAYER_GUI_TASK_STACK_SIZE ];
void ayplayer_gui_init ( void ) {
    xTaskCreateStatic( ayplayer_lcd_update_task,
                       "gui",
                       AY_PLAYER_GUI_TASK_STACK_SIZE,
                       NULL,
                       3,
                       ayplayer_gui_task_stack,
                       &ayplayer_gui_task_buffer );
}

/*
 * Заполняем строки данными с microsd.
 * Метод смотрит, на какую строку (номер строки) указывает point_file и обновляет string_number строк "вниз".
 * По сути, мы указываем, начиная с какого файла по списку (счет с 0) мы хотим обновить список.
 * Если файлов меньше, чем колличество строк в буффере (например, буффер рассчитан под 3 строки, а после
 * указанного файла на флешке всего 1 строка (не включая ту, на которую указывает указатель), то
 * первые 2 строки будут заполнены именями из списка, а последняя - пустой строкой. Причем, это касается
 * как массива имен, так и времени. Время будет так же пустым.
 *//*
int update_string_data (main_form_cfg_t *main_form){
    // Заполняем строки.
    for ( uint32_t l_string = 0; l_string < gui_string_box_init_cfg.string_number; l_string++){
        if (l_string + main_form->point_file < main_form->psg_file_number){	// Если файлы еще не закончились (моежт быть, что строки 4, а файла 2).
            uint32_t time_sec;
            ay_psg_file_get_name(ay_file_fd, l_string + main_form->point_file, main_form->string_menu[l_string], &time_sec);
            file_update(ay_file_fd, NULL, main_form->string_menu[l_string]); 	// Выбираем эту строку.
            time_gui_convert_sec_to_string(time_sec, main_form->string_time_many[l_string]);	// Преобразовываем секунды в строковое предстовление.
            main_form->time[l_string] = time_sec;		// Но сохраняем и в текстовом.
        } else {
            strcpy(main_form->string_time_many[l_string], "");		// Если фалов тут нет - очищаем строку.
            strcpy( main_form->string_menu[l_string], "");
        }
    };
    return 0;
*/
/*
 * Прокрутить указатель на одну позицию вниз.
 * В случае, если выходим за пределы экрана/списка, обновить
 * список следущими по списку именами и поставить указатель в нужную позицию.
 * В случае, если весь список был пройден - начать с начала.
 */
// Вызывается из "следущий трек" и "закончился старый". А так же "нажатие на плей".
//  Вызывается при нажатии вниз, следущий трек (+еще начать воспроизведение), закончено воспроизведение.
/*
int _next_down_track (main_form_cfg_t *main_form){
    uint16_t page = main_form->point_file/gui_string_box_init_cfg.string_number;	// Получаем страницу, на которой сейчас находились.
    main_form->point_file++;
    if (main_form->point_file<main_form->psg_file_number){		// Если мы не вышли за пределы списка.
        if (main_form->point_file+1 > (page+1)*gui_string_box_init_cfg.string_number){	// Если мы вышли за пределы списка.
            update_string_data(main_form);	// Если перешли на следущую страницу.
        };
    } else {		// Если промотали последний - с начала.
        main_form->point_file = 0;
        update_string_data(main_form);	// Выбираем новые строки из sdcard.
    };
    gui_string_box_reset(string_bar_fd, main_form->point_file % gui_string_box_init_cfg.string_number, 0,  main_form->psg_file_number, main_form->point_file+1);
    return 0;
}*/

/*
 * Прокрутить указатель на одну позицию вверх.
 * В случае, если выходим за пределы экрана/списка, обновить
 * список предыдущими по списку именами и поставить указатель в нужную позицию.
 * В случае, если весь список был пройден - начать с конечного файла.
 * Метод сам заботится о выравнивании списка по экрану.
 *//*
int _next_up_track (main_form_cfg_t *main_form){
    if (main_form->point_file>0){			// Ниже 0-ля не спускаемся (только если обратно по списку.
        uint16_t page = main_form->point_file/gui_string_box_init_cfg.string_number;	// Получили номер страницы, на которой были до этого.
        main_form->point_file--;
        if (main_form->point_file < page*gui_string_box_init_cfg.string_number) {	// Если мы вышли за пределы страницы.
            // Если придется на страницу назад.
            int buffer_number = main_form->point_file;	// Сохраняем, чтобы потом вернуть.
            main_form->point_file -= gui_string_box_init_cfg.string_number - 1;	// Узнаем номер первого элемента на странице.
            update_string_data(main_form);				// Выбираем новые строки из sdcard.
            main_form->point_file = buffer_number;		// Получаем номер последнего файла на странице.
        };
    } else {
        if (main_form->psg_file_number % gui_string_box_init_cfg.string_number != 0){
            main_form->point_file = (main_form->psg_file_number / gui_string_box_init_cfg.string_number)*gui_string_box_init_cfg.string_number;
            update_string_data(main_form);	// Выбираем новые строки из sdcard.
            main_form->point_file = main_form->psg_file_number -  main_form->psg_file_number%gui_string_box_init_cfg.string_number;		// Получаем номер последнего файла.
        } else {
            main_form->point_file = main_form->psg_file_number - gui_string_box_init_cfg.string_number - 1;	// Узнаем номер первого элемента на странице.
            update_string_data(main_form);	// Выбираем новые строки из sdcard.
            main_form->point_file = main_form->psg_file_number -  1;		// Получаем номер последнего файла
        }
    };
    gui_string_box_reset(string_bar_fd, main_form->point_file%gui_string_box_init_cfg.string_number, 0,  main_form->psg_file_number, main_form->point_file+1);
    return 0;
}*/

/*
 * Инициализируем буферы.
 *//*
void init_buffer (main_form_cfg_t *main_form){
    main_form->string_time_many = pvPortMalloc (sizeof (char *) * gui_string_box_init_cfg.string_number);	// Для строк времени.
    main_form->time = pvPortMalloc (sizeof (uint32_t) * gui_string_box_init_cfg.string_number);			// Время в цифровом представлении.
    // Создаем массив сторк, которые будем отображать.
    main_form->string_menu = pvPortMalloc (sizeof (char *) * gui_string_box_init_cfg.string_number);	// Создаем n указателей, по числу строк.
    for (int l_string = 0; l_string < gui_string_box_init_cfg.string_number; l_string++){		// Каждому указателю создаем строку.
        main_form->string_menu[l_string] = pvPortMalloc (sizeof (char) * 256);				// Строка до 256 элементов (255 + 0).
        configASSERT ( main_form->string_menu[l_string] );		// Проверяем, что память выделилась успешно.
    };

    // Создаем массив строк, для отображения времени.
    for (int l_time_string = 0; l_time_string < gui_string_box_init_cfg.string_number; l_time_string++){		// Каждому указателю создаем строку.
        main_form->string_time_many[l_time_string] = pvPortMalloc (sizeof (char) * 6);				// Время у нас до 99:99.
        (main_form->string_time_many[l_time_string])[2] = ':';		// Значения, которые меняться не будут.
        (main_form->string_time_many[l_time_string])[5] = 0;
        configASSERT ( main_form->string_time_many[l_time_string] );	// Проверяем, что память выделилась успешно.
    };

    // Привязываем наш буффер строк к строк-бару.
    for (uint8_t l_string = 0; l_string < gui_string_box_init_cfg.string_number; l_string++){
        gui_string_point_update(string_bar_fd, l_string, main_form->string_menu[l_string]);
    };
    // Тоже самое, но уже со строками времени.
    for (uint8_t l_string = 0; l_string < gui_string_box_init_cfg.string_number; l_string++){
        gui_string_time_point_update(string_bar_fd, l_string, main_form->string_time_many[l_string]);
    };
}*/
/*
 * Начать проигрывание нового трека.
 * Вызвается из методов нажатия на плей (при измененном исходном файле), следущий трек, закончился старый.
 * Метод сам разбирается с тем, в каком сейчас состоянии плеер. При надобности, сам остановит текущее
 * воспроизведение и разберется с флагами.
 *//*
int _play_new_file (main_form_cfg_t *main_form){
    if (main_form->flag != 0) {	// Если до этого уже был какой-то файл на воспроизведении/паузе.
        ay_psg_file_play_break(ay_file_fd);		// Остановили текущий трек (по сути, выставляем байт, который будет прочитан лишь при попытке положить следущее слово в очередь AY (но положено оно не будет, т.к. флаг. При этом мы получим флаг того, что АУ остановлен в виде байта в очередь клавиш)).
        ay_music_off(ay_fd);	// Отключаем звук, очищаем  AY, чистим очередь. В момент очистки очереди разблокируется задача выдачи новых данных в очередь.
        uint8_t buffer_button;
        xQueueReceive(button_click, &buffer_button, (TickType_t) portMAX_DELAY);	// Получаем свидетельство того, что задача проигрования psg вернулась в исходную точку.
    };

    gui_play_bar_reset_value(play_bar_fd);			// Меняем bar.
    main_form->play_file = main_form->point_file+1;	// Сохраняем номер нового.
    file_update(ay_file_fd, main_form->dir, main_form->string_menu[(main_form->play_file-1)%gui_string_box_init_cfg.string_number]);	// Выбранная строка готова к воспроизведению.
    gui_play_bar_new_all_time(play_bar_fd, main_form->time[(main_form->play_file-1)%gui_string_box_init_cfg.string_number]);	// Выводим на экран текущее время.
    uint8_t buf_command_play = 1;
    xQueueSend(fat_command, &buf_command_play, (TickType_t) portMAX_DELAY);		// Отдаем команду начать воспроизведение.
    main_form->flag = 2;	// Теперь мы начали воспроизводить трек.
    return 0;
}*/

/*
 * Создаем список и сортируем его.
 * Во время сортировки используем статус бар.
 *//*
int ayplayer_create_list_psg (main_form_cfg_t *main_form){
        main_form->psg_file_number = ay_find_psg_file(ay_file_fd);			// Ищем в директории все файлы (попутно составляя список).
        if (main_form->psg_file_number < 0) return MICRO_SD_ERROR;		// С картой что-то не так.
        if (main_form->psg_file_number == 0) return PSG_NONE;				// Если PSG нет, то дальше нам делать нечего.
        int result_sort = ay_file_sort(ay_file_fd);							// Пытаемся отсортировать список.
        if (result_sort == OPEN_FILE_ERROR)  return MICRO_SD_ERROR;

        return 0;
}*/

/*
 * Главная комната.
 *//*
void ayplayer_room_main_menu (void){
    // Все последущие методы будут взаимодействовать через эту структуру.
    main_form_cfg_t *main_form;
    main_form = pvPortMalloc (sizeof (*main_form));
    configASSERT ( main_form );
    init_buffer(main_form);				// Инициализируем все используемые массивы и буферы.

    ssd1306_reset(lcd_fd);

    main_form->point_file = 0;	// С 0-го файла.
    main_form->play_file = 0;	// Сейчас ничего не играет.

    if (f_mount(fat_fs_cfg_microsd, "0", 1) != FR_OK){			// Открываем карту до посинения.
        ssd1306_printString_to_buffer(lcd_fd, &font_gost_type_b_12_rle, 0, 0, "MICRO-SD ERROR", 1, 1);
        ssd1306_update(lcd_fd);	// Обновляем экран.
        while(1){
        }
    }

    // Сортируем начальную директорию. Получаем именя первых n строк для экрана.
    strcpy(main_form->dir, "");
    file_update(ay_file_fd, main_form->dir, NULL);			// Задаем начальную директорию.

    ayplayer_create_list_psg(main_form);					// Читаем файлы, составляем список.

    main_form->flag = 0;									// По-умолчанию плеер ничего не воспроизводит и файлы не открыты.
    main_form->point_file = 0;								// Изначально выбрано 0-й файл.



    update_string_data(main_form);	// Обновляем список файлов.

    // Тут сама форма.
    gui_play_bar_update(play_bar_fd);					// Рисуем статус-бар.
    gui_string_box_reset(string_bar_fd, main_form->point_file, 0,  main_form->psg_file_number, main_form->point_file+1);			// Рисуем список мелодий. По-умолчанию ни одна не играет, но 0-я выбрана.
    file_update(ay_file_fd, main_form->dir, main_form->string_menu[0]);		// Играть готовимся 0-ю, что выбрали.
    uint8_t buffer_button;					// То, что приходит в очередь.
    uint32_t tim_event_arr_buf = 0;			// Храним изначальный делитель. На случай перемотки.
    ssd1306_update(lcd_fd);	// Обновляем экран.
    while(1){	// Весим тут, пока не придет нажатие на другую клавишу./
        xQueueReceive(button_click, &buffer_button, (TickType_t) portMAX_DELAY);
        switch(buffer_button){
        case BUTTON_ENTER:			// Запуск/стоп/пауза трека.
            if ((main_form->play_file-1) == main_form->point_file){		// Если файл не сменили.
                if (main_form->flag == 0){		// Если еще даже не начали воспроизведение трека.
                    gui_play_bar_new_all_time(play_bar_fd, main_form->time[(main_form->play_file-1)%gui_string_box_init_cfg.string_number]);	// Выводим на экран текущее время.
                    uint8_t buf_command_play = 1;
                    xQueueSend(fat_command, &buf_command_play, (TickType_t) portMAX_DELAY);		// Отдаем команду начать воспроизведение.
                    main_form->flag = 2;	// Теперь мы начали воспроизводить трек.
                } else if (main_form->flag == 1) {		// Если мы просто стояли на паузе.
                    ay_play_stait(ay_fd, 1);
                    main_form->flag = 2;		// Мы воспроизводим.
                } else {
                    main_form->flag = 1;		// Мы встали на паузу.
                    ay_play_stait(ay_fd, 0);
                };
            } else {			// Если файл сменили.
                _play_new_file(main_form);
            }
            break;
        case BUTTON_RIGHT_LONG_PRESSURE:			// Перемотка вперед.
            tim_event_arr_buf = port_timer_event_clk_mul(tim_event_fd, 2);
            break;
        case BUTTON_RIGHT_LONG_RELEASED:			// Отключаем перемотку.
            port_timer_event_update(tim_event_fd, tim_event_arr_buf);
            break;
        case END_TRACK:					// Закончился старый.
            main_form->flag = 0;		// Т.к. трек закончился. А дальше, так же как и при "следущий".
            _next_down_track(main_form);		// Спускаемся по списку.
            _play_new_file(main_form);			// Включаем воспроизведение.
            main_form->flag = 2;	// Теперь мы начали воспроизводить трек.
            break;
        case BUTTON_RIGHT:  // Включили следущий трек.
            _next_down_track(main_form);		// Спускаемся по списку.
            _play_new_file(main_form);			// Включаем воспроизведение.
            main_form->flag = 2;	// Теперь мы начали воспроизводить трек.
            break;
        // Обработка перемещений по меню.
        case BUTTON_DOWN:
            _next_down_track(main_form);
            break;
        case BUTTON_LEFT:
            _next_up_track(main_form);
            _play_new_file(main_form);	// Включаем воспроизведение.
            main_form->flag = 2;		// Теперь мы начали воспроизводить трек.
            break;
        case BUTTON_UP:
            _next_up_track(main_form);
            break;
        break;
        };
        ssd1306_update(lcd_fd);	// Обновляем экран.
    };
}
}*/
