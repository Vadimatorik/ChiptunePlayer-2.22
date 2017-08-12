#include "ayplayer_gui_window_sd_card_analysis.h"

MButton button;

//**********************************************************************
// Данное окно будет возникать в моменты анализа SD карты.
//**********************************************************************



//метод будет вызыван при нажатии на кнопку
void click(MButton *b)
{
    (void)b;
   // b->text = "Clicked!"; //меняем текст кнопки

}


MakiseStyle ts_button = {
    MC_White,
    &F_Arial12,
    0,
    //bg       font     border   double_border
    {MC_White, MC_White, MC_White, 0},  //unactive
    {MC_White, MC_Black, MC_Black, 0},//normal
    {MC_White, MC_White, MC_White, 0}, //focused
    {MC_White, MC_White, MC_White, 0} //active
};

MakiseProgressBarStyle makise_progress_bar_style = {
    bg_color           : MC_White,
    border_color       : MC_Black,
    duty_color         : MC_Black
};

MakiseStyle l_style = {
    MC_White,
    &F_Arial12,
    0,
    //bg       font     border   double_border
    {MC_White, MC_White, MC_White, 0},  //unactive
    {MC_White, MC_Black, MC_Black, 0},  //normal
    {MC_White, MC_White, MC_White, 0}, //focused
    {MC_White, MC_White, MC_White, 0} //active
};

MakiseLableStyle makise_lable_style = {
    font                : &F_Arial12,
    font_col            : MC_Black,
    bg_color            : MC_White,
    border_c            : MC_Black,
    double_border       : 0
};

char string_text[] = "Click me";
char string_scanning_dir[] = "The directory is scanned:"; //"Производится сканирование директории:";

MPosition m_pos;

// Заполняем контейнер окна.
void ayplayer_gui_window_sd_card_analysis_creature ( MContainer& c, MProgressBar& pb, MLable& lb ) {
    (void)lb;
    makise_g_cont_clear( &c );                                          // Чистим контейнер.
    /*m_create_button( &button,                                           // указатель на структуру кнопки
                     &c,                                                // контейнер, в который будет добавлена кнопка после создания. В данном случае это контейнер MHost'a
                     mp_rel( 5,     5,                                  // координаты элемента относительно левого верхнего угла
                             50,   15 ),                                // ширина, высота
                     string_text,                                       // текст кнопки
                     //События
                     click,                                             // Вызывается при нажатии на кнопку
                     nullptr,                                           // Вызывается до обработки нажатия, может прервать обработку нажатия
                     nullptr,                                           // Вызывается при действиях с фокусом кнопки
                     &ts_button );                                      // стиль кнопки
*/

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
}



