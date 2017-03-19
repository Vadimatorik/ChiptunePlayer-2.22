#ifndef STM32F2_API_STM32_F20X_F21X_CONF_H_
#define STM32F2_API_STM32_F20X_F21X_CONF_H_

/*
 * В данном файле происходит настройка всех параметров бибилиотеки.
 */
#include <stdint.h>

/*
 * Раскомментируйте строку с выбранным вами контроллером.
 */
// #define STM32F205RB
#define STM32F205RC
// #define STM32F205RE
// #define STM32F205RF
// #define STM32F205RG
// #define STM32F205VB
// #define STM32F205VC
// #define STM32F205VE
// #define STM32F205VF
// #define STM32F205VG
// #define STM32F205ZC
// #define STM32F205ZE
// #define STM32F205ZF
// #define STM32F205ZG

// #define STM32F207IC
// #define STM32F207IE
// #define STM32F207IF
// #define STM32F207IG
// #define STM32F207VC
// #define STM32F207VE
// #define STM32F207VF
// #define STM32F207VG
// #define STM32F207ZC
// #define STM32F207ZE
// #define STM32F207ZF
// #define STM32F207ZG

//******************************************************************************************************************
//											Для модуля PORT.
//******************************************************************************************************************
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE)\
	|defined(STM32F205RF)|defined(STM32F205RG)
#define PORTA
#define PORTB
#define PORTC
#define PORTD
#define PORTH
#define STM32_F2_PORT_COUNT				5
#else
	#error Не выбран микроконтроллер. Выбирете модель микрококнтроллера. Например, STM32F205RC.
#endif
#endif
