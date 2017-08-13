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
    .border_c            = MC_Black,
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
void ayplayer_gui_window_sd_card_analysis_creature ( MContainer& c, MProgressBar& pb, MLable& lb, MSList& sl ) {
    makise_g_cont_clear( &c );                                          // Чистим контейнер.

    m_create_lable( &lb, &c,
                    mp_rel( 0,     0,
                            128,   14 ),
                    string_scanning_dir,
                    &makise_lable_style );

    m_create_progress_bar( &pb, &c,
                           mp_rel( 0,   54,
                                   128, 10 ),
                           0,
                           1,
                           &makise_progress_bar_style );

    m_create_slist( &sl, &c,
                    mp_rel( 0,   20,
                            128, 30 ),
                    string_slist,
                    nullptr,
                    nullptr,
                    MSList_List,
                    &sl_style,
                    &sl_style );
}



