#pragma once

/*
 * В данном файле происходит настройка всех параметров бибилиотеки.
 */
#include <stdint.h>
#include "user_os.h"

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

// Частота внешнего кварцевого генератора (если таковой будет использован).
#define	HSE_VALUE							16000000

//**********************************************************************
// Модули, которые планируется использовать в проекте.
// Для того, чтобы библиотека могла использовать модуль -
// - раскомментируйте строчку с требуемым модулем.
//**********************************************************************
#define MODULE_PORT
#define MODULE_RCC
#define MODULE_SPI
#define MODULE_TIMER



//**********************************************************************
//								Определения, не касающиеся основных модулей.
//**********************************************************************
#define BIT_BAND_SRAM_REF   0x20000000
#define BIT_BAND_SRAM_BASE  0x22000000

//Получаем адрес бита RAM в Bit Banding области.
#define MACRO_GET_BB_P_SRAM(reg, bit) ((BIT_BAND_SRAM_BASE + (reg - BIT_BAND_SRAM_REF)*32 + (bit * 4)))

#define BIT_BAND_PER_REF    ((uint32_t)0x40000000)
#define BIT_BAND_PER_BASE   ((uint32_t)0x42000000)

// Получаем адрес бита периферии в Bit Banding области.
#define M_GET_BB_P_PER(ADDRESS,BIT) ((BIT_BAND_PER_BASE + (ADDRESS - BIT_BAND_PER_REF)*32 + (BIT * 4)))

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Причем запрещает переписывать то, что по указателю (только чтение).
#define M_U32_TO_P_CONST(point)         ( ( const uint32_t *const )( point ) )

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Данные по указателю можно изменять.
#define M_U32_TO_P(point)               ( ( uint32_t * )point )

// Преобразует enum class в uint8_t.
#define M_EC_TO_U8(ENUM_VALUE)          ( ( uint8_t )ENUM_VALUE )

// Преобразует enum class в uint32_t.
#define M_EC_TO_U32(ENUM_VALUE)         ( ( uint32_t )ENUM_VALUE )


// Возвращаем размер массива.
#define M_SIZE_ARRAY(ARRAY)             (sizeof(ARRAY)/sizeof(ARRAY[0]))

// Служит для записи таблицы векторов прерываний.
#define M_ISR_TO_CONST_P_VOID(POINT)    ((void*)(POINT))

//**********************************************************************
//                          Для модуля PORT.
//**********************************************************************

/*
 * Раскомментировать данный define, если требуется в случае наличия блокировки порта пропустить повторную
 * переинициализацию.
 * Без данного define, при обнаружении флага блокировки порта, повторная переинициализация производится, т.к.,
 * возможно, пользователь хочет переинициализировать не заблокированные выводы.
 */
//#define NO_REINIT_PORT_AFTER_LOOKING

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

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера
 * (зависит от выбранного в stm32_f20x_f21x_conf.h контроллера).
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
    |defined(STM32F205RF)|defined(STM32F205RG)
enum class EC_PORT_NAME {
    A   = 0,
    B   = 1,
    C   = 2,
    D   = 3,
    H   = 4
};

/*
 * Возвращает указатель на базовый адрес выбранного порта ввода-вывода
 * на карте памяти в соответствии с выбранным контроллером.
 */
constexpr uint32_t p_base_port_address_get( EC_PORT_NAME port_name ) {
    switch( port_name ) {
#ifdef PORTA
    case EC_PORT_NAME::A:   return 0x40020000;
#endif
#ifdef PORTB
    case EC_PORT_NAME::B:   return 0x40020400;
#endif
#ifdef PORTC
    case EC_PORT_NAME::C:   return 0x40020800;
#endif
#ifdef PORTD
    case EC_PORT_NAME::D:   return 0x40020C00;
#endif
#ifdef PORTE
    case EC_PORT_NAME::E:   return 0x40021000;
#endif
#ifdef PORTF
    case EC_PORT_NAME::F:   return 0x40021400;
#endif
#ifdef PORTG
    case EC_PORT_NAME::G:   return 0x40021800;
#endif
#ifdef PORTH
    case EC_PORT_NAME::H:   return 0x40021C00;
#endif
#ifdef PORTI
    case EC_PORT_NAME::I:   return 0x40022000;
#endif
    }
    // Это не произойдет, т.к. ранее уже ранее была проверка,
    // что данные верны.
    return 0;
}
#endif
