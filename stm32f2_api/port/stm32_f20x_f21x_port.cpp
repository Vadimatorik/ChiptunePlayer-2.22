#include "stm32_f20x_f21x_port.h"

/*
 * В данном файле содержатся только исполняемые в реальном времени контроллером функции.
 */
// Устанавливаем бит.
void pin::set() const {
	*((uint32_t *)p_odr) = set_msk;
}

// Сбрасываем бит.
void pin::reset() const {
	*((uint32_t *)p_odr) = reset_msk;
}

// Инавертируем бит.
void pin::invert() const {
	if (*((uint32_t *)p_bb_odr_read)) {			// Если был 1, то выставляем 0.
		*((uint32_t *)p_odr) = reset_msk;
	} else {
		*((uint32_t *)p_odr) = set_msk;
	}
}

// Считываем текущее состояние на выводе.
int pin::read() const {
	return *((uint32_t *)p_bb_idr_read);
}

// Переинициализируем вывод выбранной конфигурацией.
answer_pin_reinit pin::reinit (uint32_t number_config) const{
	if (number_config >= count) return answer_pin_reinit_cfg_number_error;		// Защита от попытки инициализации вывода несуществующей конфигурацией.
	if ((*((uint32_t *)p_bb_key_looking))										// Если порт, к кторому относится вывод был заблокирован.
			&& (*((uint32_t *)p_bb_looking_bit)))								// И сам вывод так же был заблокирован.
		return answer_pin_reinit_locked;										// Выходим с ошибкой.

	// Если дошли до сюда, то вывод можно переинициализировать.
	((port_registers_struct *)p_port)->moder	&= ~(0b11 << cfg[number_config].pin_name * 2);						// Переводим вывод в режим "входа" (чтобы не было неготивных последствий от переключений).
	((port_registers_struct *)p_port)->otyper	&= ~(1 << cfg[number_config].pin_name);								// Далее все как в constexpr функциях, инициализирующие маски портов.
	((port_registers_struct *)p_port)->otyper	|= cfg[number_config].output_config << cfg[number_config].pin_name;
	((port_registers_struct *)p_port)->ospeeder	&= ~(0b11 << cfg[number_config].pin_name * 2);
	((port_registers_struct *)p_port)->ospeeder	|= cfg[number_config].speed << cfg[number_config].pin_name * 2;
	((port_registers_struct *)p_port)->pupdr	&= ~(0b11 << cfg[number_config].pin_name * 2);
	((port_registers_struct *)p_port)->pupdr	|= cfg[number_config].pull << cfg[number_config].pin_name * 2;
	if (cfg[number_config].pin_name < PORT_PIN_8) {
		((port_registers_struct *)p_port)->afrl &= ~(0b1111 << cfg[number_config].pin_name * 4);
		((port_registers_struct *)p_port)->afrl |= cfg[number_config].locked << cfg[number_config].pin_name * 4;
	} else {
		((port_registers_struct *)p_port)->afrh &= ~(0b1111 << (cfg[number_config].pin_name - 8) * 4);
		((port_registers_struct *)p_port)->afrh |= cfg[number_config].locked << (cfg[number_config].pin_name - 8) * 4;
	}
	((port_registers_struct *)p_port)->moder |= cfg[number_config].mode << cfg[number_config].pin_name * 2;	// Выставляем тот режим, который указан в конфигурации.

	return answer_pin_reinit_cfg_number_error;
}

// Служебная функция записи образа регистров порта.
void global_port::write_image_port_in_registrs(uint32_t number) const {
	((port_registers_struct *)init_array[number].p_port)->moder		= init_array[number].moder_reset;	// Переключаем сначала порт на вход, чтобы ничего не натворить.
																				// С учетом особенностей порта.
	((port_registers_struct *)init_array[number].p_port)->otyper	= init_array[number].otyper;
	((port_registers_struct *)init_array[number].p_port)->afrl		= init_array[number].afrl;
	((port_registers_struct *)init_array[number].p_port)->afrh		= init_array[number].afrh;
	((port_registers_struct *)init_array[number].p_port)->odr		= init_array[number].odr;
	((port_registers_struct *)init_array[number].p_port)->pupdr		= init_array[number].pupdr;
	((port_registers_struct *)init_array[number].p_port)->ospeeder	= init_array[number].ospeeder;
	((port_registers_struct *)init_array[number].p_port)->moder		= init_array[number].moder;
}


/*
 * Переинициализируем все порты ввода-вывода.
 */
answer_global_port global_port::reinit_all_ports() const {
	answer_global_port answer = global_port_reinit_success;		// Флаг того, что во время переинициализации была обнаружен порт со включенной блокировкой (или же инициализация прошла удачно).
	for (uint32_t loop_port = 0; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (get_state_locked_key_port((enum_port_name)loop_port) == port_locked_kay_set) {
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

answer_global_port	global_port::reinit_port(enum_port_name port) const {
// В случае, если пользователь посчитал, что при обнаружении заблокированного порта не следует пытаться
// переинициализировать незаблокированные выводы, проверяем наличие блокировки. И в случае, если она есть -
// - выходим.
#if defined(NO_REINIT_PORT_AFTER_LOOKING)
	if (get_state_locked_key_port(port) == port_locked_kay_set) const {
		return global_port_reinit_look;
	};
#endif
	write_image_port_in_registrs((uint32_t)port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	return global_port_reinit_success;
}

// Возвращаем состояние ключа.
port_locked_key global_port::get_state_locked_key_port(enum_port_name port) const {
	if (*((uint32_t *)init_array[port].p_look_key)) {
		return port_locked_kay_set;
	} else {
		return port_locked_kay_reset;
	}
}

// Производим попытку заблокировать порт.
answer_port_set_lock	global_port::set_locked_key_port(enum_port_name port) const {
	if (get_state_locked_key_port(port) == port_locked_kay_set) {		// Если порт уже заблокирован.
		return answer_port_look_already;
	}
	// Специальная последовательность для блокировки порта.
	((port_registers_struct *)init_array[(uint32_t)port].p_port)->lckr = init_array[port].lckr | (1<<16);
	((port_registers_struct *)init_array[(uint32_t)port].p_port)->lckr = init_array[port].lckr;
	((port_registers_struct *)init_array[(uint32_t)port].p_port)->lckr = init_array[port].lckr | (1<<16);
	volatile uint32_t buffer = ((port_registers_struct *)init_array[(uint32_t)port].p_port)->lckr;			// Порт должен заблокироваться после этого действия.
	(void)buffer;
	if (get_state_locked_key_port(port) == port_locked_kay_set) {		// Проверяем.
		return answer_port_lock_ok;
	} else {
		return answer_port_lock_error;
	}
}

// Пытаемся заблокировать все порты.
answer_port_set_lock	global_port::set_locked_keys_all_port() const {
	answer_port_set_lock answer = answer_port_lock_ok;			// Возвратим OK или error, если хоть в одном из портов будет ошибка.
	for (uint32_t loop_port; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (set_locked_key_port((enum_port_name)loop_port) == answer_port_lock_error) {
			answer == answer_port_lock_error;
		};
	}
	return answer;
}


