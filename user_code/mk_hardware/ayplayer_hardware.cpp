#include "ayplayer_hardware.h"

#include "ayplayer_wdt.h"
#include "ayplayer_port.h"
#include "ayplayer_clock.h"
#include "ayplayer_adc.h"
#include "ayplayer_spi.h"
#include "ayplayer_timers.h"
#include "ayplayer_uart.h"

/*!
 * Метод вызывает функции-прослойки, которые вызывают методы 
 * инициализации глобальных объектов, представляющих из себя 
 * программные абстракции аппаратных блоков переферии микроконтроллера.
 */
void ayplayer_mc_hardware ( void ) {
	ayplayer_wdt_init();					///< Инициализация сторожевого таймера.
	ayplayer_port_init();					///< Инициализация портов ввода-вывода.
	ayplayer_clock_init();					///< Инициализация системы генерации тактового сигнала.
	ayplayer_adc_init();					///< Инициализация аналогово цифровых преобразователей.
	ayplayer_spi_init();					///< Инициализация SPI.
	ayplayer_timers_init();					///< Инициализация таймеров.
	ayplayer_uart_init();					///< Инициализация UART.
}
