#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_STRUCT_H_
#include "stm32_f20x_f21x_conf.h"

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера
 * (зависит от выбранного в stm32_f20x_f21x_conf.h контроллера).
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
	|defined(STM32F205RF)|defined(STM32F205RG)
enum enum_port_name {
	PORT_A = 0,	PORT_B = 1,	PORT_C = 2,	PORT_D = 3, PORT_H = 4
};
#endif

/*
 * Перечень выводов каждого порта.
 */
enum enum_port_pin_name {
	PORT_PIN_0	= 0,	PORT_PIN_1	= 1,	PORT_PIN_2	= 2,	PORT_PIN_3	= 3,
	PORT_PIN_4	= 4,	PORT_PIN_5	= 5,	PORT_PIN_6	= 6,	PORT_PIN_7	= 7,
	PORT_PIN_8	= 8,	PORT_PIN_9	= 9,	PORT_PIN_10	= 10,	PORT_PIN_11	= 11,
	PORT_PIN_12	= 12,	PORT_PIN_13	= 13,	PORT_PIN_14	= 14,	PORT_PIN_15	= 15
};

/*
 * Предназначены для класса описания конфигурации одного вывода.
 */
enum enum_pin_mode {						// Режим вывода:
	PIN_INPUT_MODE					= 0,	// Вход.
	PIN_OUTPUT_MODE					= 1, 	// Выход.
	PIN_ALTERNATE_FUNCTION_MODE		= 2, 	// Альтернативная функция.
	PIN_ANALOG_MODE					= 3		// Аналоговый режим.
};

enum enum_pin_output_config	{				// Режим выхода:
	PIN_OUTPUT_NOT_USE				= 0,	// Вывод не используется как вывод.
	PIN_OUTPUT_PUSH_PULL_CONFIG		= 0,	// "Тянуть-толкать".
	PIN_OUTPUT_OPEN_DRAIN_CONFIG	= 1		// "Открытый сток".
};

enum enum_pin_speed {						// Скорость выхода:
	PIN_LOW_SPEED					= 0,	// Низкая.
	PIN_MEDIUM_SPEED				= 1,	// Средняя.
	PIN_FAST_SPEED					= 2,	// Быстрая.
	PIN_HIGH_SPEED					= 3		// Очень быстрая
};

enum enum_pin_pull {						// Выбор подтяжки:
	PIN_NO_PULL						= 0,	// Без подтяжки.
	PIN_PULL_UP						= 1,	// Подтяжка к питанию.
	pin_pull_down					= 2		// Подтяжка к земле.
};

enum enum_pin_alternate_function {	// Выбираем альтернативную функцию, если используется.
	PIN_AF_NOT_USE = 0,				// Альтернативная функция не используется.
	PIN_AF_0	= 0,	PIN_AF_1	= 1,	PIN_AF_2	= 2,	PIN_AF_3	= 3,
	PIN_AF_4	= 4,	PIN_AF_5	= 5,	PIN_AF_6	= 6,	PIN_AF_7	= 7,
	PIN_AF_8	= 8,	PIN_AF_9	= 9,	PIN_AF_10	= 10,	PIN_AF_11	= 11,
	PIN_AF_12	= 12,	PIN_AF_13	= 13,	PIN_AF_14	= 14,	PIN_AF_15	= 15
};

/*
 * Заблокировать настройку вывода после начальной инициализации.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
enum pin_locked {
	PIN_CONFIG_NOT_LOCKED			= 0,	// Не блокировать вывод.
	PIN_CONFIG_LOCKED				= 1		// Заблокировать вывод.
};

enum pin_state_after_init {			// Состояние на выходе после инициализации
									// (в случае, если вывод настроен как выход).
	PIN_STATE_NO_USE				= 0,
	PIN_STATE_AFTER_INIT_RESET		= 0,
	PIN_STATE_AFTER_INIT_SET		= 1
};

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct __attribute__((packed)) port_registers_struct {
	volatile uint32_t	mode;		// Регистр выбора режима работы выводов.
	volatile uint32_t	otype;		// Регистр выбора режима выхода (в случае, если вывод настроен как выход).
	volatile uint32_t	ospeede;	// Регистр выбора скорости выводов.
	volatile uint32_t	pupd;		// Регистр включения подтяжки выводов.
	volatile uint32_t	id;			// Регистр с текущими данными на входе вывода.
	volatile uint32_t	od;			// Регистр с выставленными пользователем на выход данными (в случае, если вывод настроен как выход).
	volatile uint32_t	bsr;		// Регистр быстрой установки состояния выводов (когда вывод настроен как выход).
	volatile uint32_t	lck;		// Регистр блокировки настроек.
	volatile uint32_t	afl;		// Младший регистр настройки альтернативных функций выводов.
	volatile uint32_t	afh;		// Старший регистр настройки альтернативных функций выводов.
};

/*
 * Структура настройки вывода.
 */
struct __attribute__((packed)) pin_config_t {
	enum_port_name				port;					// Имя порта (пример: port_a).
	enum_port_pin_name			pin_name;				// Номер вывода (пример: port_pin_1).
	enum_pin_mode				mode;					// Режим вывода (пример: pin_output_mode).
	enum_pin_output_config		output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	enum_pin_speed				speed;					// Скорость вывода (пример: pin_low_speed).
	enum_pin_pull				pull;					// Подтяжка вывода (пример: pin_no_pull).
	enum_pin_alternate_function	af;						// Альтернативная функция вывода (пример: pin_af_not_use).
	pin_locked					locked;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	pin_state_after_init		state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

/*
 * Структура содержит необходимые для инициализации порта данные.
 * Заполняется внутри объекта global_port при передаче в него массива pin_config элементов.
 */
struct __attribute__((packed)) port_registers_flash_copy_struct {
	uint32_t				p_port;			// Указатель на структуру порта port_registers_struct в области памяти периферии (базовое смещение порта в карте памяти контроллера).
	uint32_t				mode;			// Данные регистра выбора режима работы выводов.
	uint32_t				mode_res;		// Значение регистра moder, которое имеет порт по умолчанию (для безопасного переключения).
	uint32_t				otype;			// Данные регистра выбора режима выхода (в случае, если вывод настроен как выход).
	uint32_t				speed;			// Данные регистра выбора скорости выводов.
	uint32_t				pupd;			// Данные регистра включения подтяжки выводов.
	uint32_t				lck;			// Данные регистра блокировки настроек.
	uint32_t				afl;			// Данные младший регистра настроек альтернативных функций выводов.
	uint32_t				afh;			// Данные старший регистр настроек альтернативных функций выводов.
	uint32_t				od;				// Состояние на выводах порта после инициализации (в случае, если выводы настроены как выходы).
	uint32_t				p_look_key;		// Указатель на бит блокировки в bit band регионе (быстрое чтение).
};

/*
 * Структура содержит в себе маски портов всех имеющихся регистров.
 * STM32_F2_PORT_COUNT - этот define автоматически определяется при
 * выборе конкретного контроллера в stm32_f20x_f21x_conf.h
 */
struct __attribute__((packed)) global_port_msk_reg_struct {
	port_registers_flash_copy_struct	port[STM32_F2_PORT_COUNT];
};

enum answer_pin_reinit {						// Возвращаемые значения функции пере инициализации порта
	ANSWER_PIN_REINIT_OK				= 0,	// Вывод был успешно пере инициализирован.
	ANSWER_PIN_REINIT_LOCKED			= 1,	// Конфигурация вывода была заблокирована.
	ANSWER_PIN_REINIT_CFG_NUMBER_ERROR	= 2		// Вы попытались инициализировать вывод несуществующей конфигурацией.
};

/*
 * Ответы от функций reinit_all, reinit_port объекта global_port.
 */
enum answer_global_port {
	GLOBAL_PORT_REINIT_SUCCESS			= 0,	// Переинициализация была успешной.
	GLOBAL_PORT_REINIT_LOOK				= 1		// Порт заблокирован, переинициализация некоторых
												// (или всех) выводов невозможна.
	// В случае reinit_all может быть, что выводы одного или нескольких портов не были переинициализированы.
	// В случае обнаружения блокировки порта - производится попытка пере инициализации (на случай, если
	// требуется пере инициализировать те выводы, которые заблокированы не были).
	// Данное поведение можно изменить раскомментировав define NO_REINIT_PORT_AFTER_LOOKING в файле
	// stm32_f20x_f21x_conf.h.
};

// Состояние ключа блокировки порта.
enum port_locked_key {
	PORT_LOCKED_KAY_SET					= 1,
	PORT_LOCKED_KAY_RESET				= 0
};

// Возвращаемые значения функции блокировки порта/портов.
enum answer_port_set_lock {
	ANSWER_PORT_LOCK_OK			= 0,			// Порт был успешно заблокирован.
	ANSWER_PORT_LOCK_ALREADY	= 1,			// Порт был уже заблокирован до нас.
	ANSWER_PORT_LOCK_ERROR		= 2				// После попытки заблокировать порт - порт не был заблокирован.
};

#endif
