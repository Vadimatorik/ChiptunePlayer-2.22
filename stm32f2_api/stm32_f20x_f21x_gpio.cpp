#include "stm32_f20x_f21x_gpio.h"

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

/*
 * Конструктор готовит маски для начальной инициализации выводов.
 */
global_port::global_port(pin_config *pin_cfg_array, uint32_t pin_count):
	init_array({.moder		= global_port_registr_moder_msk_init_get	(pin_cfg_array, pin_count, port_a),
				.otyper		= global_port_registr_otyper_msk_init_get	(pin_cfg_array, pin_count, port_a),
				.ospeeder 	= global_port_registr_ospeeder_msk_init_get	(pin_cfg_array, pin_count, port_a),
				.pupdr		= global_port_registr_pupdr_msk_init_get	(pin_cfg_array, pin_count, port_a),
				.lckr 		= global_port_registr_lckr_msk_init_get		(pin_cfg_array, pin_count, port_a),
				.afrl		= global_port_registr_afrl_msk_init_get		(pin_cfg_array, pin_count, port_a),
				.afrh		= global_port_registr_afrh_msk_init_get		(pin_cfg_array, pin_count, port_a)})
		{
	/*if (pin_count == 0) return;
	for (uint32_t l_pin = 0; l_pin < pin_count; l_pin++){
		// Создаем маску настроек вывода в копии регистров (init_array).

		init_array[pin_cfg_array[l_pin].port].otyper |=											// Режим выхода.
						pin_cfg_array[l_pin].output_config << pin_cfg_array[l_pin].pin_name;
		init_array[pin_cfg_array[l_pin].port].ospeeder |=										// Скорость вывода.
						pin_cfg_array[l_pin].speed << pin_cfg_array[l_pin].pin_name * 2;
		init_array[pin_cfg_array[l_pin].port].pupdr |=											// Подтяжка вывода.
						pin_cfg_array[l_pin].pull << pin_cfg_array[l_pin].pin_name * 2;
		if (pin_cfg_array[l_pin].pin_name > port_pin_7) {
			init_array[pin_cfg_array[l_pin].port].afrh |=										// Альтернативная функция.
						pin_cfg_array[l_pin].af << (pin_cfg_array[l_pin].pin_name - 8) * 4;
		} else {
			init_array[pin_cfg_array[l_pin].port].afrl |=
						pin_cfg_array[l_pin].af << pin_cfg_array[l_pin].pin_name * 4;
		};
	};*/
}

void global_port::init(){

}
