#include "ayplayer_os_object.h"
#include "mono_lcd_lib_st7565.h"
#include "makise.h"
#include "makise_gui.h"

extern ST7565					ayplayer_lcd_obj;
extern ay_player_freertos_obj_strcut		os_data;

/*
 * Методы-перестыки для связки драйвера экрана c MakiseGUI.
 */
extern "C" {

extern const MakiseGUI m_gui;

uint8_t m_driver_init ( MakiseGUI* gui ) {
	( void )gui;
	return M_OK;
}

uint8_t m_driver_start ( MakiseGUI* gui ) {
	( void )gui;
	if ( ayplayer_lcd_obj.reset()			!= BASE_RESULT::OK ) return M_ERROR;
	if ( ayplayer_lcd_obj.setContrast( 8 )	!= BASE_RESULT::OK ) return M_ERROR;
	if ( ayplayer_lcd_obj.clear()			!= BASE_RESULT::OK ) return M_ERROR;
	if ( ayplayer_lcd_obj.on()				!= BASE_RESULT::OK ) return M_ERROR;
	return M_OK;
}

uint8_t m_driver_sleep ( MakiseGUI* gui ) {
	( void )gui;
	while( true );
	return M_OK;
}

uint8_t m_driver_awake ( MakiseGUI* gui ) {
	( void )gui;
	while( true );
	return M_OK;
}

uint8_t m_driver_set_backlight ( MakiseGUI* gui, uint8_t ) {
	( void )gui;
	while( true );
	return M_OK;
}

void m_gui_draw ( MakiseGUI* gui ) {
	( void )gui;
	ayplayer_lcd_obj.update();	
}

void m_gui_predraw ( MakiseGUI* gui ) {
	while( true );
	( void )gui;
}

void m_gui_update ( MakiseGUI* gui ) {
	ayplayer_lcd_obj.update();
	( void )gui;
}

//**********************************************************************
// Необходимые для внутренней связки драйвера и GUI структуры.
//**********************************************************************
extern uint8_t		lcd_buffer[1024];

const MakiseDriver m_driver = {
	.gui				= ( MakiseGUI* )&m_gui,			// Структура используемого GUI объекта.
	.lcd_height			= 64,							// Реальная высота экрана.
	.lcd_width			= 128,							// Реальная ширина экрана.
	.buffer_height		= MAKISE_BUF_H,					// Ширина/высота буфера.
	.buffer_width		= MAKISE_BUF_W,
	.pixeldepth			= MAKISEGUI_DRIVER_DEPTH,		// Глубина цвета в LCD.
	.buffer				= (uint32_t*)lcd_buffer,		// Буфер на отправку в LCD.
	.size				= 256,							// Его размер.
	.posx				= 0,							// позиция плавающего буфера(если размера буфера на отправку должен быть меньше чем буфер гуя).
	.posy				= 0,

	// Методы для взаимодействия с LCD.
	.init				= m_driver_init,				// Первичная инициализация экрана.
	.start				= m_driver_start,				// Старт работы экрана.
	.sleep				= m_driver_sleep,				// Переход экрана в спящий режим.
	.awake				= m_driver_awake,				// Выход экрана из спящего режима.
	.set_backlight		= m_driver_set_backlight		// Управление подсветкой.
};

const MakiseBuffer m_buf_st = {
	.gui			= ( MakiseGUI* )&m_gui,				// Структура используемого GUI объекта.
	.height			= 64,								// Реальная высота экрана.
	.width			= 128,								// Реальная ширина экрана.
	.pixeldepth		= MAKISEGUI_BUFFER_DEPTH,			// Глубина цвета в виртуальном буфере.
	.depthmask		= MAKISEGUI_BUFFER_DEPTHMASK,		// Как правильно записать?...
	.buffer			= (uint32_t*)lcd_buffer,			// Виртуальный буфер ( совпадает с драйвером ).
	.size			= 256,								// Его размер.
	.border			= {									// Границы рабочей области ГУИ.
		.x		= 0,
		.y		= 0,
		.w		= 128,
		.h		= 64,
		.ex		= 128,
		.ey		= 64
	}
};

const MakiseGUI m_gui = {
	.buffer		= ( MakiseBuffer* )&m_buf_st,
	.driver		= ( MakiseDriver* )&m_driver,
	.draw		= m_gui_draw,
	.predraw	= m_gui_predraw,
	.update		= m_gui_update
};

}

