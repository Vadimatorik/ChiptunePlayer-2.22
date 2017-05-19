#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_CLASS_GLOBAL_PORT_CONSTEXPR_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_FUNC_CLASS_GLOBAL_PORT_CONSTEXPR_H_
#include "stm32_f20x_f21x_conf.h"
#include "stm32_f20x_f21x_port_struct.h"
/*
 * Конструктор готовит маски для начальной инициализации выводов.
 * Количество портов, а так же их имена задаются автоматически после выбора чипа в stm32_f20x_f21x_conf.h.
 */
constexpr global_port::global_port( const pin_config_t *const pin_cfg_array, const uint32_t pin_count ):
	init_array({
#ifdef PORTA															// Если данный порт есть в чипе.
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, PORT_A),		// Создаем структуру масок его начальной инициализации.
#endif
#ifdef PORTB
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, PORT_B),
#endif
#ifdef PORTC
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, PORT_C),
#endif
#ifdef PORTD
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, PORT_D),
#endif
#ifdef PORTE
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_e),
#endif
#ifdef PORTF
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_f),
#endif
#ifdef PORTG
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_g),
#endif
#ifdef PORTH
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, PORT_H),
#endif
#ifdef PORTI
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_i)
#endif
}) {};

/*****************************************************************************************************
 * Необходимые для конструктора global_port constexpr функции (готовят маски из массива структур).
 * Методы проверяет все pin_config структуры и в случае, если структура относится к port_name порту,
 * на основе ее конфигурации производится изменение маски регистра порта.
 *****************************************************************************************************/
constexpr uint32_t global_port::moder_reg_reset_init_msk( enum_port_name port_name ) {
	switch(port_name){
		case PORT_A:	return 0xA8000000;
		case PORT_B:	return 0x00000280;
		default: 		return 0;
	};
}

// Режим работы.
constexpr uint32_t global_port::reg_moder_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_moder = this->moder_reg_reset_init_msk(port_name);								// Начальное значение зависит от порта.
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){								// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };							// Если вывод не относится к нашему порту - выходим.
		reg_moder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);							// Сбрасываем предыдущую настройку этого вывода.
		reg_moder |= pin_cfg_array[loop_pin].mode << pin_cfg_array[loop_pin].pin_name * 2;		// Иначе производим добавление по маске.
	}
	return reg_moder;
}

// Режим выхода.
constexpr uint32_t global_port::reg_otyper_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		reg_otyper &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		reg_otyper |= pin_cfg_array[loop_pin].output_config << pin_cfg_array[loop_pin].pin_name;
	}
	return reg_otyper;
}

// Скорость.
constexpr uint32_t global_port::reg_ospeeder_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_ospeeder = 0;
	if (port_name == PORT_B){					// Для порта B свое значение.
		reg_ospeeder = 0x000000C0;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_ospeeder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		reg_ospeeder |= pin_cfg_array[loop_pin].speed << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return reg_ospeeder;
}

// Подтяжка.
constexpr uint32_t global_port::reg_pupdr_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_pupdr = 0;
	switch(port_name){											// Начальное значение зависит от порта.
		case PORT_A:	reg_pupdr = 0x64000000; break;
		case PORT_B:	reg_pupdr = 0x00000100; break;
		default: 		reg_pupdr = 0; 			break;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_pupdr &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		reg_pupdr |= pin_cfg_array[loop_pin].pull << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return reg_pupdr;
}

// Блокировка настроек.
constexpr uint32_t global_port::reg_lckr_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_lckr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		reg_lckr |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name;
	}
	return reg_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port::reg_afrl_init_msk( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_afrl = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		if (pin_cfg_array[loop_pin].pin_name < PORT_PIN_8) {
			reg_afrl &= ~(0b1111 << pin_cfg_array[loop_pin].pin_name * 4);
			reg_afrl |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name * 4;
		}
	}
	return reg_afrl;
}

// Старший регистр выбора альтернативной функции.
constexpr uint32_t global_port::reg_afrh_msk_init_get( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_afrh = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++) {
		if (pin_cfg_array[loop_pin].port != port_name) { continue; };
		if (pin_cfg_array[loop_pin].pin_name > PORT_PIN_7) {
			reg_afrh &= ~(0b1111 << (pin_cfg_array[loop_pin].pin_name - 8) * 4);
			reg_afrh |= pin_cfg_array[loop_pin].locked << (pin_cfg_array[loop_pin].pin_name - 8) * 4;
		}
	}
	return reg_afrh;
}

// Состояние на выводах после инициализации (для выводов, настроенных на выход).
constexpr uint32_t global_port::reg_odr_msk_init_get( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name ) {
	uint32_t reg_odr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){ continue; };
		reg_odr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		reg_odr |= pin_cfg_array[loop_pin].state_after_init << pin_cfg_array[loop_pin].pin_name;
	}
	return reg_odr;
}
#endif
