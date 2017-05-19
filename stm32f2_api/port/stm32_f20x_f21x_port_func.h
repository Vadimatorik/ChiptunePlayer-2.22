#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_H_
#include "stm32_f20x_f21x_conf.h"
#include "stm32_f20x_f21x_port_struct.h"

/*
 * Возвращает указатель на базовый адрес выбранного порта ввода-вывода
 * на карте памяти в соответствии с выбранным контроллером.
 */
constexpr uint32_t p_base_port_address_get( enum_port_name port_name ) {
	switch(port_name){
#ifdef PORTA
		case PORT_A:	return 0x40020000;
#endif
#ifdef PORTB
		case PORT_B:	return 0x40020400;
#endif
#ifdef PORTC
		case PORT_C:	return 0x40020800;
#endif
#ifdef PORTD
		case PORT_D:	return 0x40020C00;
#endif
#ifdef PORTE
		case port_e:	return 0x40021000;
#endif
#ifdef PORTF
		case port_f:	return 0x40021400;
#endif
#ifdef PORTG
		case port_g:	return 0x40021800;
#endif
#ifdef PORTH
		case PORT_H:	return 0x40021C00;
#endif
#ifdef PORTI
		case port_i:	return 0x40022000;
#endif
		default:
			/*
			 * В случае, если вы попали сюда, то в структуре описания
			 * порта pin_config_t в пункте port был указан несуществующий порт.
			 */
			throw("The specified port does not exist!");
			return 0xFFFFFFFF;
	}
}

// Указатель на bit_banding область памяти, в которой находится бит блокировки порта.
constexpr uint32_t bb_p_port_look_key_get ( enum_port_name port_name ) {
	uint32_t port_point = p_base_port_address_get(port_name);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;											// Прибавляем смещение к IDR регистру.
	return MACRO_GET_BB_P_PER(port_point, 16);					// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}
#endif
