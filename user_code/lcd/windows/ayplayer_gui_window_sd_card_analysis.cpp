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

char string_text[] = "Click me";

MPosition m_pos;

MContainer m_container = {
    gui           : &m_gui,
    el            : nullptr,
    position      : &m_pos,
    first         : nullptr,
    last          : nullptr,
    focused       : nullptr
};



// Заполняем контейнер окна.
void ayplayer_gui_window_sd_card_analysis_creature ( MContainer& c ) {
    makise_g_cont_clear( &c );                                          // Чистим контейнер.
    m_create_button( &button,                                           // указатель на структуру кнопки
                     &c,                                                // контейнер, в который будет добавлена кнопка после создания. В данном случае это контейнер MHost'a
                     mp_rel( 0,     0,                                  // координаты элемента относительно левого верхнего угла
                             100,   40 ),                               // ширина, высота
                     string_text,                                       // текст кнопки
                     //События
                     click,                                             // Вызывается при нажатии на кнопку
                     nullptr,                                           // Вызывается до обработки нажатия, может прервать обработку нажатия
                     nullptr,                                           // Вызывается при действиях с фокусом кнопки
                     &ts_button );                                      // стиль кнопки
}



