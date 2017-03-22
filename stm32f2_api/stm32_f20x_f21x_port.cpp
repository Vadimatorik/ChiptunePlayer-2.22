#include "stm32_f20x_f21x_port.h"

/*
 * Возвращает указатель на выбранный порт ввода-вывода на карте памяти в соответствии с выбранным контроллером.
 */
constexpr port_registers_struct* point_base_port_address_get(port_name port_name) {
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

// Указатель на bit_banding область памяти, в которой находится бит блокировки порта.
constexpr uint32_t* bit_banding_point_look_port_key_get (port_name port_name) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(port_name);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;														// Прибавляем смещение к IDR регистру.
	return (uint32_t*)BIT_BAND_PER(port_point, 16);							// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

/*
 * Методы, необходимые для констурктора класса вывода.
 */
// Маска установки выхода в "1".
constexpr uint32_t pin_set_msk_get (pin_config *pin_cfg_array) {
	return 1 << pin_cfg_array->pin_name;
}

// Маска установки выхода в "0".
constexpr uint32_t pin_reset_msk_get (pin_config *pin_cfg_array) {
	return 1 << (pin_cfg_array->pin_name + 16);
}

// Указатель на bit_banding область памяти, в которой находится бит состояния входа.
constexpr uint32_t* pin_read_banding_point_bit_get (pin_config *pin_cfg_array) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x10;																	// Прибавляем смещение к IDR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

// Возвращаем указатель на регистр ODR, к которому относится вывод.
constexpr uint32_t* pin_odr_registr_point_get(pin_config *pin_cfg_array) {
	uint32_t point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем указатель на порт, к которому относится бит.
	return (uint32_t *)(point += 0x14);												// 0x14 - смещение от начала порта.
}

// Получаем указатель на bit banding область памяти, с выставленным пользователем состоянием.
constexpr uint32_t* pin_odr_read_bit_banding_point_bit_get (pin_config *pin_cfg_array) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x14;																	// Прибавляем смещение к ODR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра ODR (состояние на входе).
}

// Получаем указатель на бит блокировки конфигурации конкретного вывода.
constexpr uint32_t* pin_bit_banding_point_looking_bit_get (pin_config *pin_cfg_array) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;																	// Прибавляем смещение к LCKR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра LCKR.
}
/*
 * Конструктор готовит маски регистров для быстрой работы с выводом в режиме порта ввода-вывода.
 */
constexpr pin::pin (pin_config *pin_cfg_array, uint32_t pin_cout):
	cfg(pin_cfg_array), count(pin_cout), set_msk(pin_set_msk_get(pin_cfg_array)),
	port(point_base_port_address_get(pin_cfg_array->port)),	odr(pin_odr_registr_point_get(pin_cfg_array)),
	bit_banding_odr_read(pin_odr_read_bit_banding_point_bit_get(pin_cfg_array)),
	reset_msk(pin_reset_msk_get(pin_cfg_array)), bit_banding_idr_read(pin_read_banding_point_bit_get(pin_cfg_array)),
	bit_banding_key_looking(bit_banding_point_look_port_key_get(pin_cfg_array->port)),
	bit_banding_looking_bit(pin_bit_banding_point_looking_bit_get(pin_cfg_array))
{};

// Устанавливаем бит.
void pin::set() {
	*odr = set_msk;
}

// Сбрасываем бит.
void pin::reset() {
	*odr = reset_msk;
}

// Инавертируем бит.
void pin::invert() {
	if (*bit_banding_odr_read) {			// Если был 1, то выставляем 0.
		*odr = reset_msk;
	} else {
		*odr = set_msk;
	}
}

// Считываем текущее состояние на выводе.
int pin::read() {
	return *bit_banding_idr_read;
}

// Переинициализируем вывод выбранной конфигурацией.
answer_pin_reinit pin::reinit (uint32_t number_config) {
	if (number_config >= count) return answer_pin_reinit_cfg_number_error;		// Защита от попытки инициализации вывода несуществующей конфигурацией.
	if ((*bit_banding_key_looking)												// Если порт, к кторому относится вывод был заблокирован.
			&& (*bit_banding_looking_bit))										// И сам вывод так же был заблокирован.
		return answer_pin_reinit_locked;										// Выходим с ошибкой.

	// Если дошли до сюда, то вывод можно переинициализировать.
	port->moder		&= ~(0b11 << cfg[number_config].pin_name * 2);				// Переводим вывод в режим "входа" (чтобы не было неготивных последствий от переключений).
	port->otyper	&= ~(1 << cfg[number_config].pin_name);						// Далее все как в constexpr функциях, инициализирующие маски портов.
	port->otyper	|= cfg[number_config].output_config << cfg[number_config].pin_name;
	port->ospeeder	&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->ospeeder	|= cfg[number_config].speed << cfg[number_config].pin_name * 2;
	port->pupdr		&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->pupdr		|= cfg[number_config].pull << cfg[number_config].pin_name * 2;
	if (cfg[number_config].pin_name < port_pin_8) {
		port->afrl &= ~(0b1111 << cfg[number_config].pin_name * 4);
		port->afrl |= cfg[number_config].locked << cfg[number_config].pin_name * 4;
	} else {
		port->afrh &= ~(0b1111 << (cfg[number_config].pin_name - 8) * 4);
		port->afrh |= cfg[number_config].locked << (cfg[number_config].pin_name - 8) * 4;
	}
	port->moder |= cfg[number_config].mode << cfg[number_config].pin_name * 2;	// Выставляем тот режим, который указан в конфигурации.

	return answer_pin_reinit_cfg_number_error;
}

/*
 * Необходимые для конструктора global_port constexpr функции (готовят маски из массива структур).
 * Методы проверяет все pin_config структуры и в случае, если структура относится к port_name порту,
 * на основе ее конфигурации производится изменение маски регистра порта.
 */

constexpr uint32_t global_port_registr_moder_reset_msk_init_get(port_name port_name) {
	switch(port_name){
		case port_a:	return 0xA8000000;
		case port_b:	return 0x00000280;
		default: 		return 0;
	};
}

// Режим работы.
constexpr uint32_t global_port_registr_moder_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_moder = global_port_registr_moder_reset_msk_init_get(port_name);	// Начальное значение зависит от порта.

	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){									// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name){continue;};									// Если вывод не относится к нашему порту - выходим.
		registr_moder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);							// Сбрасываем предыдущую настройку этого вывода.
		registr_moder |= pin_cfg_array[loop_pin].mode << pin_cfg_array[loop_pin].pin_name * 2;		// Иначе производим добавление по маске.
	}
	return registr_moder;
}

// Режим выхода.
constexpr uint32_t global_port_registr_otyper_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_otyper &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_otyper |= pin_cfg_array[loop_pin].output_config << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_otyper;
}

// Скорость.
constexpr uint32_t global_port_registr_ospeeder_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_ospeeder = 0;
	if (port_name == port_b){					// Для порта B свое значение.
		registr_ospeeder = 0x000000C0;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_ospeeder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_ospeeder |= pin_cfg_array[loop_pin].speed << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_ospeeder;
}

// Подтяжка.
constexpr uint32_t global_port_registr_pupdr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_pupdr = 0;
	switch(port_name){											// Начальное значение зависит от порта.
		case port_a:	registr_pupdr = 0x64000000; break;
		case port_b:	registr_pupdr = 0x00000100; break;
		default: 		registr_pupdr = 0; 			break;
	};
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_pupdr &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);
		registr_pupdr |= pin_cfg_array[loop_pin].pull << pin_cfg_array[loop_pin].pin_name * 2;
	}
	return registr_pupdr;
}

// Блокировка настроек.
constexpr uint32_t global_port_registr_lckr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_lckr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_lckr |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrl_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
	uint32_t registr_afrl = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		if (pin_cfg_array[loop_pin].pin_name < port_pin_8) {
			registr_afrl &= ~(0b1111 << pin_cfg_array[loop_pin].pin_name * 4);
			registr_afrl |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name * 4;
		}
	}
	return registr_afrl;
}

// Старший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrh_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
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
constexpr uint32_t global_port_registr_odr_msk_init_get(pin_config *pin_cfg_array, uint32_t pin_count, port_name port_name) {
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
#define GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port) { \
		.p_port			= point_base_port_address_get					(port), \
		.moder			= global_port_registr_moder_msk_init_get		(pin_cfg_array, pin_count, port), \
		.moder_reset	= global_port_registr_moder_reset_msk_init_get	(port), \
		.otyper			= global_port_registr_otyper_msk_init_get		(pin_cfg_array, pin_count, port), \
		.ospeeder 		= global_port_registr_ospeeder_msk_init_get		(pin_cfg_array, pin_count, port), \
		.pupdr			= global_port_registr_pupdr_msk_init_get		(pin_cfg_array, pin_count, port), \
		.lckr 			= global_port_registr_lckr_msk_init_get			(pin_cfg_array, pin_count, port), \
		.afrl			= global_port_registr_afrl_msk_init_get			(pin_cfg_array, pin_count, port), \
		.afrh			= global_port_registr_afrh_msk_init_get			(pin_cfg_array, pin_count, port), \
		.odr			= global_port_registr_odr_msk_init_get			(pin_cfg_array, pin_count, port), \
		.look_key		= bit_banding_point_look_port_key_get			(port) \
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

void global_port::write_image_port_in_registrs(uint32_t number) {
	init_array[number].p_port->moder		= init_array[number].moder_reset;	// Переключаем сначала порт на вход, чтобы ничего не натворить.
																				// С учетом особенностей порта.
	init_array[number].p_port->otyper		= init_array[number].otyper;
	init_array[number].p_port->afrl			= init_array[number].afrl;
	init_array[number].p_port->afrh			= init_array[number].afrh;
	init_array[number].p_port->odr			= init_array[number].odr;
	init_array[number].p_port->pupdr		= init_array[number].pupdr;
	init_array[number].p_port->ospeeder		= init_array[number].ospeeder;
	init_array[number].p_port->moder		= init_array[number].moder;
}
/*
 * Переинициализируем все порты ввода-вывода.
 */
answer_global_port global_port::reinit_all_ports() {
	answer_global_port answer = global_port_reinit_success;		// Флаг того, что во время переинициализации была обнаружен порт со включенной блокировкой (или же инициализация прошла удачно).
	for (uint32_t loop_port = 0; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (get_state_locked_key_port((port_name)loop_port) == port_locked_kay_set) {
			answer = global_port_reinit_look;
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, пропускаем дальнейшую попытку переинициализации.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
			continue;
#endif
		};
		write_image_port_in_registrs(loop_port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	}
	return answer;
}

answer_global_port	global_port::reinit_port(port_name port) {
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, проверяем наличие блокировки. И в случае, если она есть -
// - выходим.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
	if (get_state_locked_key_port(port) == port_locked_kay_set) {
		return global_port_reinit_look;
	]:
#endif
	write_image_port_in_registrs((uint32_t)port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	return global_port_reinit_success;
}

// Возвращаем состояние ключа.
port_locked_key		global_port::get_state_locked_key_port(port_name port) {
	if (*init_array[port].look_key) {
		return port_locked_kay_set;
	} else {
		return port_locked_kay_reset;
	}
}

// Производим попытку заблокировать порт.
answer_port_set_lock	global_port::set_locked_key_port(port_name port) {
	if (get_state_locked_key_port(port) == port_locked_kay_set) {		// Если порт уже заблокирован.
		return answer_port_look_already;
	}
	// Специальная последовательность для блокировки порта.
	init_array[port].p_port->lckr = init_array[port].lckr | (1<<16);
	init_array[port].p_port->lckr = init_array[port].lckr;
	init_array[port].p_port->lckr = init_array[port].lckr | (1<<16);
	volatile uint32_t buffer = init_array[port].p_port->lckr;			// Порт должен заблокироваться после этого действия.
	if (get_state_locked_key_port(port) == port_locked_kay_set) {		// Проверяем.
		return answer_port_lock_ok;
	} else {
		return answer_port_lock_error;
	}
}

// Пытаемся заблокировать все порты.
answer_port_set_lock	global_port::set_locked_keys_all_port() {
	answer_port_set_lock answer = answer_port_lock_ok;			// Возвратим OK или error, если хоть в одном из портов будет ошибка.
	for (uint32_t loop_port; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (set_locked_key_port((port_name)loop_port) == answer_port_lock_error) {
			answer == answer_port_lock_error;
		};
	}
	return answer;
}


