#include "stm32_f20x_f21x_port.h"

/*
 * В данном файле содержатся только исполняемые в реальном времени контроллером функции.
 */
// Устанавливаем бит.
void pin::set() const {
	*U32_TO_P(p_odr) = set_msk;
}

// Сбрасываем бит.
void pin::reset() const {
	*U32_TO_P(p_odr) = reset_msk;
}

// Инавертируем бит.
void pin::invert() const {
	if (*U32_TO_P_CONST(p_bb_odr_read)) {			// Если был 1, то выставляем 0.
		*U32_TO_P(p_odr) = reset_msk;
	} else {
		*U32_TO_P(p_odr) = set_msk;
	}
}

// Считываем текущее состояние на выводе.
int pin::read() const {
	return *U32_TO_P_CONST(p_bb_idr_read);
}

// Переинициализируем вывод выбранной конфигурацией.
answer_pin_reinit pin::reinit (uint32_t number_config) const{
	if (number_config >= count) return ANSWER_PIN_REINIT_CFG_NUMBER_ERROR;		// Защита от попытки инициализации вывода несуществующей конфигурацией.
	if (*U32_TO_P_CONST(p_bb_key_looking)										// Если порт, к кторому относится вывод был заблокирован.
			&& *U32_TO_P_CONST(p_bb_looking_bit))								// И сам вывод так же был заблокирован.
		return ANSWER_PIN_REINIT_LOCKED;										// Выходим с ошибкой.

	port_registers_struct *port = (port_registers_struct *)p_port;
	// Если дошли до сюда, то вывод можно переинициализировать.
	port->mode		&= ~(0b11 << cfg[number_config].pin_name * 2);						// Переводим вывод в режим "входа" (чтобы не было неготивных последствий от переключений).
	port->otype	&= ~(1 << cfg[number_config].pin_name);								// Далее все как в constexpr функциях, инициализирующие маски портов.
	port->otype	|= cfg[number_config].output_config << cfg[number_config].pin_name;
	port->ospeede	&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->ospeede	|= cfg[number_config].speed << cfg[number_config].pin_name * 2;
	port->pupd		&= ~(0b11 << cfg[number_config].pin_name * 2);
	port->pupd		|= cfg[number_config].pull << cfg[number_config].pin_name * 2;
	if (cfg[number_config].pin_name < PORT_PIN_8) {
		port->afl &= ~(0b1111 << cfg[number_config].pin_name * 4);
		port->afl |= cfg[number_config].locked << cfg[number_config].pin_name * 4;
	} else {
		port->afh &= ~(0b1111 << (cfg[number_config].pin_name - 8) * 4);
		port->afh |= cfg[number_config].locked << (cfg[number_config].pin_name - 8) * 4;
	}
	port->mode |= cfg[number_config].mode << cfg[number_config].pin_name * 2;	// Выставляем тот режим, который указан в конфигурации.

	return ANSWER_PIN_REINIT_CFG_NUMBER_ERROR;
}

// Служебная функция записи образа регистров порта.
void global_port::write_image_port_in_registrs(uint32_t number) const {
	port_registers_struct *port = (port_registers_struct *)gb_msk_struct.port[number].p_port;
	port->mode		= gb_msk_struct.port[number].moder_reset;	// Переключаем сначала порт на вход, чтобы ничего не натворить.
																// С учетом особенностей порта.
	port->otype	= gb_msk_struct.port[number].otyper;
	port->afl		= gb_msk_struct.port[number].afrl;
	port->afh		= gb_msk_struct.port[number].afrh;
	port->od		= gb_msk_struct.port[number].odr;
	port->pupd		= gb_msk_struct.port[number].pupdr;
	port->ospeede	= gb_msk_struct.port[number].ospeeder;
	port->mode		= gb_msk_struct.port[number].moder;
}


/*
 * Переинициализируем все порты ввода-вывода.
 */
answer_global_port global_port::reinit_all_ports() const {
	answer_global_port answer = GLOBAL_PORT_REINIT_SUCCESS;		// Флаг того, что во время переинициализации была обнаружен порт со включенной блокировкой (или же инициализация прошла удачно).
	for (uint32_t loop_port = 0; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (get_state_locked_key_port((enum_port_name)loop_port) == PORT_LOCKED_KAY_SET) {
			answer = GLOBAL_PORT_REINIT_LOOK;
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
		return GLOBAL_PORT_REINIT_LOOK;
	};
#endif
	write_image_port_in_registrs((uint32_t)port);		// Записываем образ в регистры (с учётом предосторожностей переключения).
	return GLOBAL_PORT_REINIT_SUCCESS;
}

// Возвращаем состояние ключа.
port_locked_key global_port::get_state_locked_key_port(enum_port_name port) const {
	if (*U32_TO_P_CONST(gb_msk_struct.port[port].p_look_key)) {
		return PORT_LOCKED_KAY_SET;
	} else {
		return PORT_LOCKED_KAY_RESET;
	}
}

// Производим попытку заблокировать порт.
answer_port_set_lock	global_port::set_locked_key_port(enum_port_name port) const {
	if (get_state_locked_key_port(port) == PORT_LOCKED_KAY_SET) {		// Если порт уже заблокирован.
		return ANSWER_PORT_LOCK_ALREADY;
	}
	port_registers_struct *p = (port_registers_struct *)gb_msk_struct.port[(uint32_t)port].p_port;
	// Специальная последовательность для блокировки порта.
	p->lck = gb_msk_struct.port[port].lckr | (1<<16);
	p->lck = gb_msk_struct.port[port].lckr;
	p->lck = gb_msk_struct.port[port].lckr | (1<<16);
	volatile uint32_t buffer = p->lck;			// Порт должен заблокироваться после этого действия.
	(void)buffer;
	if (get_state_locked_key_port(port) == PORT_LOCKED_KAY_SET) {		// Проверяем.
		return ANSWER_PORT_LOCK_OK;
	} else {
		return ANSWER_PORT_LOCK_ERROR;
	}
}

// Пытаемся заблокировать все порты.
answer_port_set_lock	global_port::set_locked_keys_all_port() const {
	answer_port_set_lock answer = ANSWER_PORT_LOCK_OK;			// Возвратим OK или error, если хоть в одном из портов будет ошибка.
	for (uint32_t loop_port; loop_port < STM32_F2_PORT_COUNT; loop_port++) {
		if (set_locked_key_port((enum_port_name)loop_port) == ANSWER_PORT_LOCK_ERROR) {
			answer == ANSWER_PORT_LOCK_ERROR;
		};
	}
	return answer;
}


