#include "ayplayer_gui_window_sd_card_analysis.h"

//**********************************************************************
// Данное окно будет возникать в моменты анализа SD карты.
//**********************************************************************

// Используемые стили элементов.
MakiseStyle_ProgressBar makise_progress_bar_style = {
    .bg_color           = MC_White,
    .border_color       = MC_Black,
    .duty_color         = MC_Black
};

MakiseStyle_Lable makise_lable_style = {
    .font                = &F_Arial12,
    .font_col            = MC_Black,
    .bg_color            = MC_White,
    .border_c            = MC_White,
    .double_border       = 0
};

MakiseStyle_SList sl_style = {
    &F_Arial12,
    0,
    // Фон     Шрифт     Ободок    Доп. ширина.
    { MC_White, MC_Black, MC_Black, 0 },  // Не активен.
    { MC_White, MC_Black, MC_Black, 0 },  // Нормальный.
    { MC_White, MC_Black, MC_Black, 0 },  // Фокус.
};

// Надписи.
char string_text[] = "Click me";
char string_scanning_dir[] = "The directory is scanned:"; //"Производится сканирование директории:";
char string_slist[] = "Check file";

MPosition m_pos;

// Заполняем контейнер окна.
void ayplayer_gui_window_sd_card_analysis_creature ( MContainer* c, MProgressBar* pb, MLable* l, MSList* sl ) {
    makise_g_cont_clear( c );                                          // Чистим контейнер.

    m_create_lable( l, c,
                    mp_rel( 0,     0,
                            128,   12 ),
                    string_scanning_dir,
                    &makise_lable_style );

    m_create_progress_bar( pb, c,
                           mp_rel( 0,   13,
                                   128, 6 ),
                           0,
                           1,
                           &makise_progress_bar_style );

    m_create_slist( sl, c,
                    mp_rel( 0,   20,
                            128, 45 ),
                    string_slist,
                    nullptr,
                    nullptr,
                    MSList_List,
                    &sl_style,
                    &sl_style );
}

extern ay_ym_file_mode ay_file_mode;

EC_SD_CARD_SCAN_ANSWER ayplayer_sd_card_scan ( char* dir, MContainer* c ) {

    MProgressBar    pb;
    MLable          l;
    MSList          sl;

    // Инициализируем окно.
    ayplayer_gui_window_sd_card_analysis_creature( c, &pb, &l, &sl );

    if ( ay_file_mode.find_psg_file( dir ) == EC_AY_FILE_MODE::OK ) {
        return EC_SD_CARD_SCAN_ANSWER::OK;
    }

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


