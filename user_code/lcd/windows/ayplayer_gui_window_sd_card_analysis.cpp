#include "ayplayer_gui_window_sd_card_analysis.h"

//**********************************************************************
// Данное окно будет возникать в моменты анализа SD карты.
//**********************************************************************
extern const MakiseFont F_minecraft_rus_regular_8;

// Используемые стили элементов.
MakiseStyle_ProgressBar makise_progress_bar_style = {
    .bg_color           = MC_White,
    .border_color       = MC_Black,
    .duty_color         = MC_Black
};

MakiseStyle_Lable makise_lable_style = {
    .font                = &F_minecraft_rus_regular_8,
    .font_col            = MC_Black,
    .bg_color            = MC_White,
    .border_c            = MC_White,
    .double_border       = 0
};

MakiseStyle_SList sl_style = {
    .font               = &F_minecraft_rus_regular_8,
    .font_line_spacing  = 0,

    .left_margin        = 0,
    .item_margin        = 0,

    .scroll_width       = 0,
    .scroll_bg_color    = 0,
    .scroll_color       = 0,

    // Фон     Шрифт     Ободок    Доп. ширина.
    .normal             = { MC_White, MC_Black, MC_Black, 0 },  // Не активен.
    .focused            = { MC_White, MC_Black, MC_Black, 0 },  // Нормальный.
    .active             = { MC_White, MC_Black, MC_Black, 0 }   // Фокус.
};

MakiseStyle_SListItem sl_item_style = {
    .font               = &F_minecraft_rus_regular_8,
    .font_line_spacing  = 0,

    .normal             = { MC_White, MC_Black, MC_Black, 0 },  // Не активен.
    .focused            = { MC_White, MC_Black, MC_Black, 0 },  // Нормальный.
    .active             = { MC_White, MC_Black, MC_Black, 0 }   // Фокус.
};

// Надписи.
char string_scanning_dir[] = "The directory is scanned:"; //"Производится сканирование директории:";

MPosition m_pos;

// Заполняем контейнер окна.
void ayplayer_gui_window_sd_card_analysis_creature ( MContainer* c, MProgressBar* pb, MLable* l, MSList* sl ) {
    makise_g_cont_clear( c );                                          // Чистим контейнер.

    (void)l;
    /*m_create_lable( l, c,
                    mp_rel( 0,     0,
                            128,   12 ),
                    string_scanning_dir,
                    &makise_lable_style );*/

    m_create_progress_bar( pb, c,
                           mp_rel( 0,   0,
                                   128, 6 ),
                           0,
                           1,
                           &makise_progress_bar_style );

    m_create_slist( sl, c,
                    mp_rel( 0,   7,
                            128, 57 ),
                    string_scanning_dir,
                    nullptr,
                    nullptr,
                    MSList_List,
                    &sl_style,
                    &sl_item_style );
}


extern ay_ym_file_mode              ay_file_mode;

// Метод сдвигает вниз все строки (1 удаляется) и добавляет вверх новую.
void item_shift ( MSList_Item* i_ar, uint32_t cout, char* new_st ) {
    for ( uint32_t l = cout - 1; l > 0 ; l-- ) {
        i_ar[ l ].text = i_ar[ l - 1 ].text;
    }
    i_ar[0].text = new_st;
}

// Метод производит сканирование карты и создание списка файлов директории.
EC_SD_CARD_SCAN_ANSWER ayplayer_sd_card_scan ( char* dir, MContainer* c ) {

    MProgressBar    pb;
    MLable          l;
    MSList          sl;

    // Инициализируем окно.
    ayplayer_gui_window_sd_card_analysis_creature( c, &pb, &l, &sl );

    USER_OS_TAKE_MUTEX( spi3_mutex, portMAX_DELAY );    // sdcard занята нами.

    DIR         d;
    FILINFO     fi;
    FRESULT     r;
    FIL         file_list;

    (void)r;
    (void)file_list;

    //**********************************************************************
    // Получаем колличество файлов в директории.
    //**********************************************************************
    uint32_t file_count = 0;
    r = f_findfirst( &d, &fi, dir, "*.psg" );
    while ( ( r == FR_OK ) && ( fi.fname[0] != 0 ) ) {
        file_count++;
        r = f_findnext( &d, &fi );
    }

    if ( r != FR_OK ) {     // Защита на случай неудачного чтения.
        while( true );
    }

    gui_update();

    //**********************************************************************
    // Создаем файл со списком.
    //**********************************************************************
    r = f_open( &file_list, "psg_list.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE );
    if ( r != FR_OK ) {
        f_close( &file_list );
        f_closedir( &d );
        USER_OS_GIVE_MUTEX( spi3_mutex );   // sdcard свободна.
        while( true );
    }

    //**********************************************************************
    // Анализируем файлы.
    //**********************************************************************
    uint32_t valid_file_count = 0;                                      // Число валидных.

    MSList_Item sl_i[4];                                                // Для отображения просканированного.
    char s[4][256];                                                     // Строки для списка.
    uint8_t p_s = 0;                                                    // Указатель на строку, которую нужно будет перезаписать.

    for ( int i = 0; i < 4; i++ ) {
        sl_i[i].text = nullptr;
        m_slist_add( &sl, &sl_i[i] );
    }

    uint8_t scan_repeat = 0;
    r = f_findfirst( &d, &fi, dir, "*.psg" );
    while ( ( r == FR_OK ) && ( fi.fname[0] != 0 ) ) {
        uint32_t len;
        EC_AY_FILE_MODE r_psg_get;
        r_psg_get = ay_file_mode.psg_file_get_long( fi.fname, len );    // Проверяем валидность файла.
        if ( r_psg_get != EC_AY_FILE_MODE::OK ) continue;               // Если файл бракованный - выходим.
        // Файл рабочий.
        valid_file_count++;

        // Для каждого удачного файла - сохранение на 512 байт.

        char b[512] = {0};

        // Имя может быть длинным или коротким.
        memcpy( &s[p_s][0], fi.fname, 256 );                            // В буфер LCD.
        memcpy( b, fi.fname, 256 );                                     // В буфер на карту.


        memcpy( &b[256], &len, 4 );                                     // Далее 4 байта uint32_t - время.

        UINT l;                                                         // Количество записанных байт (должно быть 512).
        r = f_write( &file_list, b, 512, &l );
        if ( r != FR_OK ) {
            while( true );
        }

        if ( l != 512 ) {                                               // Если запись не прошла - аварийный выход.
            while( true );
        }

        // Обновляем GUI.
        scan_repeat++;                                                  // +1 повторно проанализированный файл.
        item_shift( sl_i, 4, &s[p_s][0] );
        m_progress_bar_set_duty( &pb, 100 / file_count * ( scan_repeat + 1 ) );
        gui_update();
        p_s++;
        if ( p_s == 4 ) p_s = 0;

        // Ищем следующий файл.
        r = f_findnext( &d, &fi );
    }

    // Если не удалось связаться с картой, то выходим без закрытия.
    if ( r == FR_OK ) {
        f_close( &file_list );
        f_closedir( &d );
    }

    USER_OS_GIVE_MUTEX( spi3_mutex );

    /*
    if ( ay_file_mode.find_psg_file( dir ) == EC_AY_FILE_MODE::OK ) {
        return EC_SD_CARD_SCAN_ANSWER::OK;
    }*/

    /*
    char        name[256];
    uint32_t    len;

    volatile EC_AY_FILE_MODE r;
    ( void )r;

    char path[256] = "0:/";*/


  // if (  ay_file_mode.psg_file_get_name( path, 0, name, len ) != EC_AY_FILE_MODE::OK ) continue;
  //   if (ay_file_mode.psg_file_play( path, 0 ) != EC_AY_FILE_MODE::OK ) continue;


    //m_slist_add( &sl, &ms );

    return EC_SD_CARD_SCAN_ANSWER::OK;
}


