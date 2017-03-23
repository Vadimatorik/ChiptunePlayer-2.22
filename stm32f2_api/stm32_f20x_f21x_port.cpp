#include "stm32_f20x_f21x_port.h"

/*
 * В данном файле содержатся только исполняемые в реальном времени контроллером функции.
 */

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

// Служебная функция записи образа регистров порта.
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


