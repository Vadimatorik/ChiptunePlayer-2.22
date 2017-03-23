/* 
 * Карта памяти контроллеров STM32F205RB, STM32F205VB, STM32F205ZB
 * 
 * После "B" могут следовать любые символы, уточняющие остальные 
 * параметры контроллера.
 */
MEMORY
{
	FLASH :		ORIGIN = 0x08000000,	LENGTH = 128K
	RAM1 :		ORIGIN = 0x20000000,	LENGTH = 48K
	RAM2 :		ORIGIN = 0x2001C000,	LENGTH = 16K
}
