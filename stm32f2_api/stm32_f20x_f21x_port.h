#ifndef STM32F2_API_STM32_F20X_F21X_PORT_H_
#define STM32F2_API_STM32_F20X_F21X_PORT_H_

#include "stm32_f20x_f21x_conf.h"

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
	port_registers_struct *	p_port;				// Указатель на структуру порта port_registers_struct в области памяти переферии (базовое смещение порта в карте памяти контроллера).
	uint32_t				moder;				// Регистр выбора режима работы выводов.
	uint32_t				otyper;				// Регистр выбора режима выхода (в случае, если вывод настроен как выход).
	uint32_t				ospeeder;			// Регистр выбора скорости выводов.
	uint32_t				pupdr;				// Регистр включения подтяжки выводов.
	uint32_t				lckr;				// Регистр блокировки настроек.
	uint32_t				afrl;				// Младший регистр настройки альтернативных функций выводов.
	uint32_t				afrh;				// Старший регистр настройки вльтернативных функций выводов.
	uint32_t				odr;				// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера (зависит от выбранного в stm32_f20x_f21x_conf.h контроллера).
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE)\
	|defined(STM32F205RF)|defined(STM32F205RG)
enum port_name {
	port_a = 0,	port_b = 1,	port_c = 2,	port_d = 3, port_h = 4
};
#endif

/*
 * Перечень выводов каждого порта.
 */
enum port_pin_name {
	port_pin_0	= 0,	port_pin_1	= 1,	port_pin_2	= 2,	port_pin_3	= 3,
	port_pin_4	= 4,	port_pin_5	= 5,	port_pin_6	= 6,	port_pin_7	= 7,
	port_pin_8	= 8,	port_pin_9	= 9,	port_pin_10	= 10,	port_pin_11	= 11,
	port_pin_12	= 12,	port_pin_13	= 13,	port_pin_14	= 14,	port_pin_15	= 15
};

/*
 * Класс описания конфигурации одного вывода.
 */
enum pin_mode 			{pin_input_mode = 0, pin_output_mode = 1, pin_alternate_function_mode = 2, pin_analog_mode = 3};	// Режим вывода: вход, выход, альтернативная функция, аналоговый режим.
enum pin_output_config	{pin_output_not_use = 0, pin_output_push_pull_config = 0, pin_output_open_drain_config = 1};		// Режим выхода: вывод не используется как вывод, "тянуть-толкать", "открытый сток".
enum pin_speed			{pin_low_speed = 0, pin_medium_speed = 1, pin_fast_speed = 2, pin_high_speed = 3};					// Скорость выхода: низкая, средняя, быстрая, очень быстрая.
enum pin_pull			{pin_no_pull = 0, pin_pull_up = 1, pin_pull_down = 2};												// Выбор подтяжки: без подтяжки, подтяжка к питанию, подтяжка к земле.
enum pin_alternate_function {pin_af_not_use = 0,											// Альтернативная функция не используется.
	pin_af0		= 0,	pin_af1		= 1,	pin_af2		= 2,	pin_af3		= 3,			// Какая-либо альтернативная функция.
	pin_af4		= 4,	pin_af5		= 5,	pin_af6		= 6,	pin_af7		= 7,
	pin_af8		= 8,	pin_af9		= 9,	pin_af10	= 10,	pin_af11	= 11,
	pin_af12	= 12,	pin_af13	= 13,	pin_af14	= 14,	pin_af15	= 15
};
// Заблокировать настройку вывода после начальной инициализации.
// Важно! Блокировка применяется только во время начальной инициализации выводов объектом global_port, при вызове функции
// init. Во время последующей работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
enum pin_locked				{pin_config_not_locked = 0, pin_config_locked = 1};

// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
enum pin_state_after_init	{pin_state_no_use = 0, pin_state_after_init_reset = 0, pin_state_after_init_set = 1};

/*
 * Структура настройки вывода.
 */
struct pin_config{
	port_name				port;					// Имя порта (пример: port_a).
	port_pin_name			pin_name;				// Номер вывода (пример: port_pin_1).
	pin_mode				mode;					// Режим вывода (пример: pin_output_mode).
	pin_output_config		output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	pin_speed				speed;					// Скорость вывода (пример: pin_low_speed).
	pin_pull				pull;					// Подтяжка вывода (пример: pin_no_pull).
	pin_alternate_function	af;						// Альтернативная функция вывода (пример: pin_af_not_use).
	pin_locked				look;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	pin_state_after_init	state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

/*
 * Класс для создания объекта линии ввода-вывода.
 * Прототип (объект) данного класса следует создавать в том случае, когда вывод точно будет использоваться
 * в ручном (управляется пользователем) режиме. Помимо этого разрешено использование и других конфигураций этой же
 * линии порта ввода-вывода, которые можно менять в процессе работы. Подробнее в примерах.
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
	constexpr	global_port	(pin_config *pin_cfg_array, uint32_t pin_count);
	void		init		();												// Метод инициализирует в реальном времени все порты ввода-вывода контроллера,
																			// основываясь на переданном во время формирования объекта pin_config массива.
	void		set_pin		(pin_config &pin);								// Устанавливает "1" на выходе (для случая, когда вывод настроен как выход).
	void		reset_pin	(pin_config &pin);								// Устанавливает "0" на выходе (для случая, когда вывод настроен как выход).
	void		invert_pin	(pin_config &pin);								// Логическое "не" состояния на выходе вывода (для случая, когда вывод настроен как выход).
	int			reinit_pin	(pin_config &pin, uint32_t number_config);		// Переинициализирует вывод в ходе выполнения программы в выбранную конфигурацию.
	int			read_pin	(pin_config &pin);								// Считывает состояние вывода (для случая, когда вывод настроен как вход).

private:
	port_registers_flash_copy_struct		init_array[STM32_F2_PORT_COUNT];// Дубликат регистров для переинициализации всех портов контроллера.
		// STM32_F2_PORT_COUNT - этот define автоматически определяется при выборе конкретного контроллера в stm32_f20x_f21x_conf.h.
};

#endif
