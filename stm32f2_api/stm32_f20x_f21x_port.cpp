#include "stm32_f20x_f21x_port.h"

/*
 * Конструктор готовит маски регистров для быстрой работы с выводом в режиме порта ввода-вывода.
 */
pin::pin (pin_config *pin_cfg_array, int pin_cout):
		array_cfg_point(pin_cfg_array){					// Указатель на массив конфигураций.
}

/*
 * Необходимые для конструктора global_port constexpr функции (готовят маски из массива структур).
 * Методы проверяет все pin_config структуры и в случае, если структура относится к port_name порту,
 * на основе ее конфигурации производится изменение маски регистра порта.
 */
constexpr port_registers_struct* global_port_point_base_port_address_get(port_name port_name){
	switch(port_name){
#ifdef PORTA
	case port_a: return (port_registers_struct *)0x40020000;
#endif
#ifdef PORTB
	case port_b: return (port_registers_struct *)0x40020400;
#endif
#ifdef PORTC
	case port_c: return (port_registers_struct *)0x40020800;
#endif
#ifdef PORTD
	case port_d: return (port_registers_struct *)0x40020C00;
#endif
#ifdef PORTE
	case port_e: return (port_registers_struct *)0x40021000;
#endif
#ifdef PORTF
	case port_f: return (port_registers_struct *)0x40021400;
#endif
#ifdef PORTG
	case port_g: return (port_registers_struct *)0x40021800;
#endif
#ifdef PORTH
	case port_h: return (port_registers_struct *)0x40021C00;
#endif
#ifdef PORTI
	case port_i: return (port_registers_struct *)0x40022000;
#endif
	}
	return (port_registers_struct *)0xFFFFFFFF;					// В случае, если был задан несуществующий порт (просто защита).
}

// Режим работы.
constexpr uint32_t global_port_registr_moder_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_moder = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){									// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name){continue;};									// Если вывод не относится к нашему порту - выходим.
		registr_moder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);							// Сбрасываем предыдущую настройку этого вывода.
		registr_moder |= pin_cfg_array[loop_pin].mode << pin_cfg_array[loop_pin].pin_name * 2;	// Иначе производим добавление по маске.
	}
	return registr_moder;
}

// Режим выхода.
constexpr uint32_t global_port_registr_otyper_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_otyper &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_otyper |= pin_cfg_array[loop_pin].output_config << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_otyper;
}

// Скорость.
constexpr uint32_t global_port_registr_ospeeder_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_ospeeder = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_ospeeder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_ospeeder |= pin_cfg_array[loop_pin].speed << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_ospeeder;
}

// Подтяжка.
constexpr uint32_t global_port_registr_pupdr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_pupdr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_pupdr &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_pupdr |= pin_cfg_array[loop_pin].pull << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_pupdr;
}

// Блокировка настроек.
constexpr uint32_t global_port_registr_lckr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_lckr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_lckr |= pin_cfg_array[loop_pin].look << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrl_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_afrl = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		if (pin_cfg_array[loop_pin].pin_name < port_pin_8) {
			registr_afrl &= ~(0b1111 << pin_cfg_array[loop_pin].pin_name * 4);
			registr_afrl |= pin_cfg_array[loop_pin].look << pin_cfg_array[loop_pin].pin_name * 4;
		}
	}
	return registr_afrl;
}

// Старший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrh_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_afrh = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		if (pin_cfg_array[loop_pin].pin_name > port_pin_7) {
			registr_afrh &= ~(0b1111 << (pin_cfg_array[loop_pin].pin_name - 8) * 4);
			registr_afrh |= pin_cfg_array[loop_pin].look << (pin_cfg_array[loop_pin].pin_name - 8) * 4;
		}
	}
	return registr_afrh;
}

// Состояние на выводах после инициализации (для выводов, настроенных на выход).
constexpr uint32_t global_port_registr_odr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name){
	uint32_t registr_odr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_odr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_odr |= pin_cfg_array[loop_pin].state_after_init << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_odr;
}
// Позволяет получить структуру масок начальной инициализации порта из массива структур настроек выводов.
// Пример использования: GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_a);	// Передаем массив структур pin_config, их колличество, имя порта, для которого требуется получить структуру масок настроки порта.
#define GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port)	\
	{ \
		.p_port		= global_port_point_base_port_address_get	(port), \
		.moder		= global_port_registr_moder_msk_init_get	(pin_cfg_array, pin_count, port), \
		.otyper		= global_port_registr_otyper_msk_init_get	(pin_cfg_array, pin_count, port), \
		.ospeeder 	= global_port_registr_ospeeder_msk_init_get	(pin_cfg_array, pin_count, port), \
		.pupdr		= global_port_registr_pupdr_msk_init_get	(pin_cfg_array, pin_count, port), \
		.lckr 		= global_port_registr_lckr_msk_init_get		(pin_cfg_array, pin_count, port), \
		.afrl		= global_port_registr_afrl_msk_init_get		(pin_cfg_array, pin_count, port), \
		.afrh		= global_port_registr_afrh_msk_init_get		(pin_cfg_array, pin_count, port), \
		.odr		= global_port_registr_odr_msk_init_get		(pin_cfg_array, pin_count, port) \
	}

/*
 * Конструктор готовит маски для начальной инициализации выводов.
 * Колличество портов, а так же их именя задаются автоматически после выбора чипа в stm32_f20x_f21x_conf.h.
 */
constexpr global_port::global_port(pin_config *pin_cfg_array, uint32_t pin_count):
	init_array({
#ifdef PORTA															// Если данный порт есть в чипе.
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_a),		// Создаем структуру масок его начальной инициализации.
#endif
#ifdef PORTB
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_b),
#endif
#ifdef PORTC
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_c),
#endif
#ifdef PORTD
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_d),
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
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_h),
#endif
#ifdef PORTI
			GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_i)
#endif
}) {};

void global_port::init(){

}
