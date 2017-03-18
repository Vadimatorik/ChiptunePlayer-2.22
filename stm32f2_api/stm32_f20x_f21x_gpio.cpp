#include "stm32_f20x_f21x_gpio.h"

/*
 * Конструктор просто заполняет внутренние поля.
 * Данный объект, по сути, просто структура.
 */
constexpr pin_config::pin_config(port_name port_point, port_pin_name p_name, pin_mode p_mode,
		pin_output_config p_out_cfg, pin_speed p_speed, pin_pull p_pull, pin_alternate_function	p_af):
		port(port_point), pin_name(p_name), mode(p_mode), output_config(p_out_cfg),
		speed(p_speed), pull(p_pull), af(p_af) {}

/*
 * Конструктор готовит маски регистров для быстрой работы с выводом в режиме порта ввода-вывода.
 */
pin::pin (pin_config *pin_cfg_array, int pin_cout):
		array_cfg_point(pin_cfg_array){					// Указатель на массив конфигураций.
}

/*
 * Конструктор готовит маски для начальной инициализации выводов.
 */
global_port::global_port(pin_config *pin_cfg_array, uint32_t pin_count){
	if (pin_count == 0) return;
	for (uint32_t l_pin = 0; l_pin < pin_count; l_pin++){
		// Создаем маску настроек вывода в копии регистров (init_array).
		init_array[pin_cfg_array[l_pin].port].moder |=											// Режим работы.
				pin_cfg_array[l_pin].mode << pin_cfg_array[l_pin].pin_name * 2;
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
	};
}

void global_port::init(){

}
