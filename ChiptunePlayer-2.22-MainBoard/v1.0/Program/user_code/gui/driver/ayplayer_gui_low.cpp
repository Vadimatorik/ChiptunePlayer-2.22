#include "ayplayer_os_object.h"
#include "mono_lcd_lib_st7565.h"
#include "makise.h"
#include "makise_gui.h"
#include "makise_gui_input.h"

extern "C" {

MHost								makiseHost;
MakiseGUI							makiseGui;
MakiseBuffer						makiseBuf;
extern uint8_t						makiseLcdBuf[1024];

MakiseDriver makiseGuiDriver = {
	.gui				= ( MakiseGUI* )&makiseGui,		// Структура используемого GUI объекта.
	.lcd_height			= 64,							// Реальная высота экрана.
	.lcd_width			= 128,							// Реальная ширина экрана.
	.buffer_height		= MAKISE_BUF_H,					// Ширина/высота буфера.
	.buffer_width		= MAKISE_BUF_W,
	.pixeldepth			= MAKISEGUI_DRIVER_DEPTH,		// Глубина цвета в LCD.
	.buffer				= ( uint32_t* )makiseLcdBuf,	// Буфер на отправку в LCD.
	.size				= 256,							// Его размер.
	.posx				= 0,							// позиция плавающего буфера(если размера буфера на отправку должен быть меньше чем буфер гуя).
	.posy				= 0
};

uint32_t* makiseGuiGetBuffer ( uint32_t size ) {
	( void )size;
	/// Память под буффер выделена статически.
	return ( uint32_t* )makiseLcdBuf;
}


void makiseGuiPredraw ( MakiseGUI* gui ) {
    makise_gui_input_perform( &makiseHost );
    makise_g_host_call( &makiseHost, gui, M_G_CALL_PREDRAW );
}
void makiseGuiDraw ( MakiseGUI* gui ) {
    makise_g_host_call( &makiseHost, gui, M_G_CALL_DRAW );
}

MInputData makiseGuiInpHandler ( MInputData d, MInputResultEnum res ) {
	(void)d;
	(void)res;
	//MInputData	r;
    return d;
}

extern ST7565		lcd;

void makiseGuiUpdate ( __attribute__((unused)) MakiseGUI* gui ) {
	lcd.update();
}

}
