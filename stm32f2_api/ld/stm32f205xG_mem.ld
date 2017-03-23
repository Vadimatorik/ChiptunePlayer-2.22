/* 
 * Карта памяти контроллеров STM32F205RG, STM32F205VG, STM32F205ZG
 * 
 * После "G" могут следовать любые символы, уточняющие остальные 
 * параметры контроллера.
 */
MEMORY
{
	FLASH :		ORIGIN = 0x08000000,	LENGTH = 1024K
	RAM1 :		ORIGIN = 0x20000000,	LENGTH = 112K
	RAM2 :		ORIGIN = 0x2001C000,	LENGTH = 16K
}
