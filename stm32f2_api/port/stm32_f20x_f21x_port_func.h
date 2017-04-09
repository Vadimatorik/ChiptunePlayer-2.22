#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_H_
#include "stm32_f20x_f21x_conf.h"
#include "stm32_f20x_f21x_port_struct.h"

/*
 * Возвращает указатель на выбранный порт ввода-вывода на карте памяти в соответствии с выбранным контроллером.
 */
constexpr uint32_t p_base_port_address_get( port_name port_name ) {
	switch(port_name){
#ifdef PORTA
	case port_a: return 0x40020000;
#endif
#ifdef PORTB
	case port_b: return 0x40020400;
#endif
#ifdef PORTC
	case port_c: return 0x40020800;
#endif
#ifdef PORTD
	case port_d: return 0x40020C00;
#endif
#ifdef PORTE
	case port_e: return 0x40021000;
#endif
#ifdef PORTF
	case port_f: return 0x40021400;
#endif
#ifdef PORTG
	case port_g: return 0x40021800;
#endif
#ifdef PORTH
	case port_h: return 0x40021C00;
#endif
#ifdef PORTI
	case port_i: return 0x40022000;
#endif
	default:	 return 0xFFFFFFFF;					// В случае, если был задан несуществующий порт (просто защита).
	}
}

// Указатель на bit_banding область памяти, в которой находится бит блокировки порта.
constexpr uint32_t bb_p_port_look_key_get ( port_name port_name ) {
	uint32_t port_point = p_base_port_address_get(port_name);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;											// Прибавляем смещение к IDR регистру.
	return BIT_BAND_PER(port_point, 16);						// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

/*****************************************************************************************************
 * Методы, необходимые для констурктора класса вывода.
 *****************************************************************************************************/
// Маска установки выхода в "1".
constexpr uint32_t pin_set_msk ( const pin_config *pin_cfg_array ) {
	return 1 << pin_cfg_array->pin_name;
}

// Маска установки выхода в "0".
constexpr uint32_t pin_reset_msk ( const pin_config *pin_cfg_array ) {
	return 1 << (pin_cfg_array->pin_name + 16);
}

// Указатель на bit_banding область памяти, в которой находится бит состояния входа.
constexpr uint32_t pin_bb_p_idr_read ( const pin_config *pin_cfg_array ) {
	uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);		// Получаем физический адресс порта вывода.
	uint32_t p_idr	= p_port + 0x10;									// Прибавляем смещение к IDR регистру.
	return BIT_BAND_PER(p_idr, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

// Возвращаем указатель на регистр ODR, к которому относится вывод.
constexpr uint32_t pin_p_odr( const pin_config *pin_cfg_array ) {
	uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);		// Получаем физический адресс порта вывода.
	return p_port + 0x14;												// 0x14 - смещение от начала порта.
}

// Получаем указатель на bit banding область памяти, с выставленным пользователем состоянием.
constexpr uint32_t pin_odr_bit_read_bb_p ( const pin_config *pin_cfg_array ) {
	uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);		// Получаем физический адресс порта вывода.
	uint32_t p_odr	= p_port + 0x14;									// Прибавляем смещение к ODR регистру.
	return BIT_BAND_PER(p_odr, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра ODR (состояние на входе).
}

// Получаем указатель на бит блокировки конфигурации конкретного вывода.
constexpr uint32_t pin_bb_p_looking_bit ( const pin_config* pin_cfg_array ) {
	uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);		// Получаем физический адресс порта вывода.
	uint32_t p_looking_bit = p_port + 0x1C;								// Прибавляем смещение к LCKR регистру.
	return BIT_BAND_PER(p_looking_bit, pin_cfg_array->pin_name);		// Получаем адрес конкретного бита регистра LCKR.
}

/*****************************************************************************************************
 * Необходимые для конструктора global_port constexpr функции (готовят маски из массива структур).
 * Методы проверяет все pin_config структуры и в случае, если структура относится к port_name порту,
 * на основе ее конфигурации производится изменение маски регистра порта.
 *****************************************************************************************************/
constexpr uint32_t global_port_moder_registr_reset_init_msk( port_name port_name ) {
	switch(port_name){
		case port_a:	return 0xA8000000;
		case port_b:	return 0x00000280;
		default: 		return 0;
	};
}

// Режим работы.
constexpr uint32_t global_port_registr_moder_init_msk( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_moder = global_port_moder_registr_reset_init_msk(port_name);					// Начальное значение зависит от порта.
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){									// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };								// Если вывод не относится к нашему порту - выходим.
		registr_moder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);							// Сбрасываем предыдущую настройку этого вывода.
		registr_moder |= pin_cfg_array[loop_pin].mode << pin_cfg_array[loop_pin].pin_name * 2;		// Иначе производим добавление по маске.
	}
	return registr_moder;
}

// Режим выхода.
constexpr uint32_t global_port_registr_otyper_init_msk( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		registr_otyper &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_otyper |= pin_cfg_array[loop_pin].output_config << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_otyper;
}

// Скорость.
constexpr uint32_t global_port_registr_ospeeder_init_msk( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_ospeeder = 0;
	if (port_name == port_b){					// Для порта B свое значение.
		registr_ospeeder = 0x000000C0;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		registr_ospeeder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_ospeeder |= pin_cfg_array[loop_pin].speed << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_ospeeder;
}

// Подтяжка.
constexpr uint32_t global_port_registr_pupdr_init_msk( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_pupdr = 0;
	switch(port_name){											// Начальное значение зависит от порта.
		case port_a:	registr_pupdr = 0x64000000; break;
		case port_b:	registr_pupdr = 0x00000100; break;
		default: 		registr_pupdr = 0; 			break;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		registr_pupdr &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_pupdr |= pin_cfg_array[loop_pin].pull << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_pupdr;
}

// Блокировка настроек.
constexpr uint32_t global_port_registr_lckr_init_msk( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		registr_lckr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_lckr |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrl_init_msk( const pin_config *pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_afrl = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		if (pin_cfg_array[loop_pin].pin_name < port_pin_8) {
			registr_afrl &= ~(0b1111 << pin_cfg_array[loop_pin].pin_name * 4);
			registr_afrl |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name * 4;
		}
	}
	return registr_afrl;
}

// Старший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrh_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_afrh = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++) {
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		if (pin_cfg_array[loop_pin].pin_name > port_pin_7) {
			registr_afrh &= ~(0b1111 << (pin_cfg_array[loop_pin].pin_name - 8) * 4);
			registr_afrh |= pin_cfg_array[loop_pin].locked << (pin_cfg_array[loop_pin].pin_name - 8) * 4;
		}
	}
	return registr_afrh;
}

// Состояние на выводах после инициализации (для выводов, настроенных на выход).
constexpr uint32_t global_port_registr_odr_msk_init_get(const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_odr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		registr_odr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_odr |= pin_cfg_array[loop_pin].state_after_init << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_odr;
}

#endif
