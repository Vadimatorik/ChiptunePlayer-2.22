#include "ayplayer_gui_window_file_list.h"

extern const MakiseFont F_minecraft_rus_regular_8;

//**********************************************************************
// Функции, используемые плей-листом.
//**********************************************************************
static MPlayList_Item*  item_pl_array           = nullptr;
static uint32_t         count_file_in_dir       = 0;
static char             item_time[4][9]         = { 0 };
static char             item_name[4][256]       = { 0 };

MPlayList_Item* create_array_item ( uint32_t len ) {                       // Эмулируем динамическое выделение памяти на 4 элемента.
    for ( uint32_t l = 0; l < len; l++ ) {                                 // Привязываем элементы и массивы строк.
        item_pl_array[l].name = &item_name[ l ][ 0 ];
        item_pl_array[l].time = &item_time[ l ][ 0 ];
    }
    return item_pl_array;
}

void item_selected ( MPlayList_Item* selected_item ) {
    (void)selected_item;
}

// flag_senior_character - флаг решает, делать ли старший символ 0-м (если он таковым является) или упустить его вообще.
// true - можно пропустить если 0.
// false - писать всегда.
uint32_t uint32_t_to_2_char ( uint32_t& number, char* p, bool flag_senior_character ) {
    uint32_t p_inc = 1;                 // На сколько после выхода из функции нужно сместить указатель.
    // Разложим часы на 2 символа (предполагается, что тут до 99 часов).
    *p = '0';
    while ( number >= 10 ) {
        number -= 10;
        *p += 1;                        // '0', '1', '2'.. '9'.
    }
    if ( flag_senior_character == true ) {
        if ( *p != '0' ) {
            p++;           // Защита от пустого старшего 0.
            p_inc++;
        }
    } else {
        p++;
        p_inc++;
    }
    *p = '0' + number;
    return p_inc;
}

// Преобразовываем время в "тиках" в привычное глазу ЧЧ:ММ:СС.
void convert_tic_to_char_time ( uint32_t tic, char* array ) {
    // Константы соответствия времени и тиков.
    const uint32_t one_sec  = 50;
    const uint32_t one_min  = one_sec * 60;
    const uint32_t one_hour = 60 * one_min;

    // Разложим тики на часы, минуты и секунды.
    uint32_t hour       = 0;
    uint32_t min        = 0;
    uint32_t sec        = 0;

    while ( tic > one_hour ) {
        tic -= one_hour;
        hour++;
    }

    while ( tic > one_min ) {
        tic -= one_min;
        min++;
    }

    while ( tic > one_sec ) {
        tic -= one_sec;
        sec++;
    }

    if ( tic != 0 ) sec++;              // То, что меньше секунды, все равно приписываем к 1 секунде +.

    // Преобразовываем в символы.
    char* p = array;
    bool flag_pr = true;
    if ( hour != 0 ) {
        p += uint32_t_to_2_char( hour, p, flag_pr );
        *p++ = ':';
        flag_pr = false;
    }

    if ( flag_pr != false ) {       // Если часы уже были, то все остальные значения выводим как положено.
        if ( min != 0 ) {
            p += uint32_t_to_2_char( min, p, flag_pr );
            *p++ = ':';
            flag_pr = false;
        }
    } else {
        p += uint32_t_to_2_char( min, p, flag_pr );
        *p++ = ':';
    }

    if ( flag_pr != false ) {       // Если часы уже были, то все остальные значения выводим как положено.
        if ( sec != 0 ) {
            p += uint32_t_to_2_char( sec, p, flag_pr );
            flag_pr = false;
        }
    } else {
        p += uint32_t_to_2_char( sec, p, flag_pr );
    }
    p++;
    *p = 0;
}

void get_item_name_and_time ( MPlayList_Item* selected_item, uint32_t treck_number ) {
    if ( treck_number >= count_file_in_dir ) {          // Если такого трека нет, а поле есть.
        selected_item->name[0] = 0;
        selected_item->time[0] = 0;
        return;
    }

    FIL             file_list;
    FRESULT         r;
    UINT            l;
    r = f_open( &file_list, "psg_list.txt", FA_READ );      if ( r != FR_OK ) while ( true ) {};
    r = f_lseek( &file_list, 512 * treck_number );          if ( r != FR_OK ) while ( true ) {};
    r = f_read( &file_list, selected_item->name, 256, &l );  if ( r != FR_OK ) while ( true ) {};
    if ( l != 256 ) while ( true );
    uint32_t time_tic;
    r = f_read( &file_list, &time_tic, 4, &l );    if ( r != FR_OK ) while ( true ) {};
    convert_tic_to_char_time( time_tic, selected_item->time );
    if ( l != 4 ) while ( true );
    f_close( &file_list );
}

extern USER_OS_STATIC_QUEUE ayplayer_play_queue;
void item_click ( MPlayList_Item* click_item ) {
    USER_OS_QUEUE_SEND( ayplayer_play_queue,&click_item->name, 0 );
}

uint32_t get_file_count_of_dir ( char* dir ) {
    FIL             file_list;
    FRESULT         r;
    (void)dir;
    r = f_open( &file_list, "psg_list.txt", FA_READ );      if ( r != FR_OK ) while (1) {};
    uint32_t size = f_size( &file_list );
    r = f_close( &file_list );
    count_file_in_dir = size / 512;  // 1 файл - 512 байт.
    return count_file_in_dir;
}

MakiseStyle_PlayListItem s_pl_item_st = {
    .font                       = &F_minecraft_rus_regular_8,
    .font_line_spacing          = 0,

    { MC_White, MC_Black, MC_Black, 0 },              // Нормальный.
    { MC_Black, MC_White, MC_Black, 0 },              // Играет.
    { MC_Black, MC_White, MC_Black, 0 },              // Выбран.
};

MakiseStyle_PlayList s_pl_st = {
    .font                       = &F_minecraft_rus_regular_8,
    .font_line_spacing          = 0,
    .left_margin                = 0,
    .item_margin                = 0,
    .scroll_width               = 5,
    .scroll_bg_color            = MC_White,
    .scroll_color               = MC_Black,
    .theme                      = { MC_White, MC_Black, MC_Black , 0 }
};

MPlayList_CallbackFunc pl_func_st = {
    .create_array_item          = create_array_item,
    .item_selected              = item_selected,
    .item_click                 = item_click,
    .get_item_name_and_time     = get_item_name_and_time,
    .get_file_count_of_dir      = get_file_count_of_dir
};

static char s_file_manager[] = "Выбор трека:";

void ayplayer_gui_window_file_list_creature ( MContainer* c, MPlayList* pl, MPlayList_Item* pl_array, char* dir ) {
    item_pl_array = pl_array;

    m_create_play_list ( pl, c,
                         mp_rel( 0,   0,
                                 128, 57 ),
                         s_file_manager,
                         dir,
                         &pl_func_st,
                         &s_pl_st,
                         &s_pl_item_st );
}
