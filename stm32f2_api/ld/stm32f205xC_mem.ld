/* 
 * Карта памяти контроллеров STM32F205RC, STM32F205VC, STM32F205ZC
 * 
 * После "C" могут следовать любые символы, уточняющие остальные 
 * параметры контроллера.
 */
MEMORY
{
	FLASH :		ORIGIN = 0x08000000,	LENGTH = 256K
	RAM1 :		ORIGIN = 0x20000000,	LENGTH = 80K
	RAM2 :		ORIGIN = 0x2001C000,	LENGTH = 16K
}
