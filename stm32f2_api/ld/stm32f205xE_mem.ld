/* 
 * Карта памяти контроллеров STM32F205RE, STM32F205VE, STM32F205ZE
 * 
 * После "E" могут следовать любые символы, уточняющие остальные 
 * параметры контроллера.
 */
MEMORY
{
	FLASH :		ORIGIN = 0x08000000,	LENGTH = 512K
	RAM1 :		ORIGIN = 0x20000000,	LENGTH = 112K
	RAM2 :		ORIGIN = 0x2001C000,	LENGTH = 16K
}
