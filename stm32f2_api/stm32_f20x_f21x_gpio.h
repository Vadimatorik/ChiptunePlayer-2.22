#ifndef STM32F2_API_STM32_F20X_F21X_GPIO_H_
#define STM32F2_API_STM32_F20X_F21X_GPIO_H_

#include <stdint.h>

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct port_registers_struct{
	volatile uint32_t	moder;		// Регистр выбора режима работы выводов.
	volatile uint32_t	otyper;		// Регистр выбора режима выхода (в случае, если вывод настроен как выход).
	volatile uint32_t	ospeeder;	// Регистр выбора скорости выводов.
	volatile uint32_t	pupdr;		// Регистр включения подтяжки выводов.
	volatile uint32_t	idr;		// Регистр с текущими данными на входе вывода.
	volatile uint32_t	odr;		// Регистр с выставленными пользователем на выход данными (в случае, если вывод настроен как выход).
	volatile uint32_t	bsrr;		// Регистр быстрой установки состояния выводов (когда вывод настроен как выход).
	volatile uint32_t	lckr;		// Регистр блокировки настроек.
	volatile uint32_t	afrl;		// Младший регистр настройки альтернативных функций выводов.
	volatile uint32_t	afrh;		// Старший регистр настройки вльтернативных функций выводов.
};

/*
 * Данная структура содержит лишь необходимые для инициализации порта данные.
 * Заполняется внутри объекта global_port при передачи в него массива pin_config элементов.
 */
struct port_registers_flash_copy_struct{
	volatile uint32_t	moder;		// Регистр выбора режима работы выводов.
	volatile uint32_t	otyper;		// Регистр выбора режима выхода (в случае, если вывод настроен как выход).
	volatile uint32_t	ospeeder;	// Регистр выбора скорости выводов.
	volatile uint32_t	pupdr;		// Регистр включения подтяжки выводов.
	volatile uint32_t	lckr;		// Регистр блокировки настроек.
	volatile uint32_t	afrl;		// Младший регистр настройки альтернативных функций выводов.
	volatile uint32_t	afrh;		// Старший регистр настройки вльтернативных функций выводов.
};

/*
port_a = 0x40020000,
port_b = 0x40020400,
port_c = 0x40020800,
port_d = 0x40020C00,
port_e = 0x40021000,
port_f = 0x40021400,
port_g = 0x40021800,
port_h = 0x40021C00,
port_i = 0x40022000*/

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера.
 */
enum port_name {
	port_a = 0,	port_b = 1,	port_c = 2,	port_d = 3,
	port_e = 4,	port_f = 5,	port_g = 6,	port_h = 7,
	port_i = 8
};

/*
 * Перечень выводов каждого порта.
 */
enum port_pin_name {
	port_pin_0	= 0,
	port_pin_1	= 1,
	port_pin_2	= 2,
	port_pin_3	= 3,
	port_pin_4	= 4,
	port_pin_5	= 5,
	port_pin_6	= 6,
	port_pin_7	= 7,
	port_pin_8	= 8,
	port_pin_9	= 9,
	port_pin_10	= 10,
	port_pin_11	= 11,
	port_pin_12	= 12,
	port_pin_13	= 13,
	port_pin_14	= 14,
	port_pin_15	= 15
};

/*
 * Класс описания конфигурации одного вывода.
 */
enum pin_mode 			{pin_input_mode = 0, pin_output_mode = 1, pin_alternate_function_mode = 2, pin_analog_mode = 3};
enum pin_output_config	{pin_output_not_use = 0, pin_output_push_pull_config = 0, pin_output_open_drain_config = 1};
enum pin_speed			{pin_low_speed = 0, pin_medium_speed = 1, pin_fast_speed = 2, pin_high_speed = 3};
enum pin_pull			{pin_no_pull = 0, pin_pull_up = 1, pin_pull_down = 2};
enum pin_alternate_function {pin_af_not_use = 0,
	pin_af0		= 0,	pin_af1		= 1,	pin_af2		= 2,	pin_af3		= 3,
	pin_af4		= 4,	pin_af5		= 5,	pin_af6		= 6,	pin_af7		= 7,
	pin_af8		= 8,	pin_af9		= 9,	pin_af10	= 10,	pin_af11	= 11,
	pin_af12	= 12,	pin_af13	= 13,	pin_af14	= 14,	pin_af15	= 15
};

/*
 * Объекты данного класса используются как блоки конфигурации
 * объекта глобального порта.
 */
class pin_config {
public:
	/* Конструктор просто заполняет переменные ниже */
	constexpr pin_config(port_name port_point, port_pin_name p_name, pin_mode p_mode,
			pin_output_config p_out_cfg, pin_speed p_speed, pin_pull p_pull, pin_alternate_function	p_af);

	port_name				port;					// Имя порта (пример: port_a).
	port_pin_name			pin_name;				// Номер вывода (пример: port_pin_1).
	pin_mode				mode;					// Режим вывода (пример: pin_output_mode).
	pin_output_config		output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	pin_speed				speed;					// Скорость вывода (пример: pin_low_speed).
	pin_pull				pull;					// Подтяжка вывода (пример: pin_no_pull).
	pin_alternate_function	af;						// Альтернативная функция вывода (пример: pin_af_not_use).
};

/*
 * Класс для создания объекта линии ввода-вывода.
 * Прототип (объект) данного класса следует создавать в том случае, когда вывод точно будет использоваться
 * в ручном (управляется пользователем) режиме. Помимо этого разрешено использование и других конфигураций этой же
 * линии порта ввода-вывода,которые можно менять в процессе работы. Подробнее в примерах.
 */
class pin {
public:
	pin (pin_config *pin_cfg_array, int pin_cout);

public:
	pin_config *array_cfg_point;								// Указатель на оставшиеся конфигурации (или null, если таковых нет).
};

/*
 * Класс глобального порта. Через него происходит управление выводами и сменой конфигурации.
 */
class global_port {
public:
	global_port	(pin_config *pin_cfg_array, uint32_t pin_count);
	void		init		();												// Метод инициализирует в реальном времени все порты ввода-вывода контроллера,
																			// основываясь на переданном во время формирования объекта pin_config массива.
	void		set_pin		(pin_config &pin);								// Устанавливает "1" на выходе (для случая, когда вывод настроен как выход).
	void		reset_pin	(pin_config &pin);								// Устанавливает "0" на выходе (для случая, когда вывод настроен как выход).
	void		invert_pin	(pin_config &pin);								// Логическое "не" состояния на выходе вывода (для случая, когда вывод настроен как выход).
	int			reinit_pin	(pin_config &pin, uint32_t number_config);		// Переинициализирует вывод в ходе выполнения программы в выбранную конфигурацию.
	int			read_pin	(pin_config &pin);								// Считывает состояние вывода (для случая, когда вывод настроен как вход).

private:
	port_registers_flash_copy_struct		init_array[9];					// Дубликат регистров для переинициализации всех портов контроллера.
	//uint32_t								rcc_msk;
};

#endif
