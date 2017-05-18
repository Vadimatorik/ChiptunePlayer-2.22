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
enum enum_pin_mode 			{										// Режим вывода:
							pin_input_mode				= 0,	// Вход.
							pin_output_mode				= 1, 	// Выход.
							pin_alternate_function_mode	= 2, 	// Альтернативная функция.
							pin_analog_mode				= 3		// Аналоговый режим.
						};

enum enum_pin_output_config	{										// Режим выхода:
							pin_output_not_use				= 0,// Вывод не используется как вывод.
							pin_output_push_pull_config		= 0,// "Тянуть-толкать".
							pin_output_open_drain_config	= 1	// "Открытый сток".
						};

enum enum_pin_speed			{										// Скорость выхода:
							pin_low_speed		= 0,			// Низкая.
							pin_medium_speed	= 1,			// Средняя.
							pin_fast_speed		= 2,			// Быстрая.
							pin_high_speed		= 3				// Очень быстрая
						};

enum enum_pin_pull			{										// Выбор подтяжки:
							pin_no_pull	= 0,					// Без подтяжки.
							pin_pull_up = 1,					// Подтяжка к питанию.
							pin_pull_down = 2					// Подтяжка к земле.
						};

enum enum_pin_alternate_function {	// Выбираем альтернативную функцию, если используется.
	pin_af_not_use = 0,																// Альтернативная функция не используется.
	pin_af0		= 0,	pin_af1		= 1,	pin_af2		= 2,	pin_af3		= 3,	// Какая-либо альтернативная функция.
	pin_af4		= 4,	pin_af5		= 5,	pin_af6		= 6,	pin_af7		= 7,
	pin_af8		= 8,	pin_af9		= 9,	pin_af10	= 10,	pin_af11	= 11,
	pin_af12	= 12,	pin_af13	= 13,	pin_af14	= 14,	pin_af15	= 15
};

/*
 * Заблокировать настройку вывода после начальной инициализации.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
enum pin_locked			{
							pin_config_not_locked	= 0,	// Не блокировать вывод.
							pin_config_locked		= 1		// Заблокировать вывод.
						};

enum pin_state_after_init {				// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
	pin_state_no_use			= 0,
	pin_state_after_init_reset	= 0,
	pin_state_after_init_set	= 1
};

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct __attribute__((packed)) port_registers_struct {
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
 * Структура настройки вывода.
 */
struct pin_config_t {
	enum_port_name				port;					// Имя порта (пример: port_a).
	enum_port_pin_name			pin_name;				// Номер вывода (пример: port_pin_1).
	enum_pin_mode				mode;					// Режим вывода (пример: pin_output_mode).
	enum_pin_output_config		output_config;			// Режим выхода (пример: pin_output_push_pull_config).
	enum_pin_speed				speed;					// Скорость вывода (пример: pin_low_speed).
	enum_pin_pull				pull;					// Подтяжка вывода (пример: pin_no_pull).
	enum_pin_alternate_function	af;						// Альтернативная функция вывода (пример: pin_af_not_use).
	pin_locked				locked;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	pin_state_after_init	state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

/*
 * Структура содержит необходимые для инициализации порта данные.
 * Заполняется внутри объекта global_port при передачи в него массива pin_config элементов.
 */
struct port_registers_flash_copy_struct {
	uint32_t				p_port;				// Указатель на структуру порта port_registers_struct в области памяти переферии (базовое смещение порта в карте памяти контроллера).
	uint32_t				moder;				// Данные регистра выбора режима работы выводов.
	uint32_t				moder_reset;		// Значение регистра moder, которое имеет порт по-умолчанию (для безопасного переключения).
	uint32_t				otyper;				// Данные регистра выбора режима выхода (в случае, если вывод настроен как выход).
	uint32_t				ospeeder;			// Данные регистра выбора скорости выводов.
	uint32_t				pupdr;				// Данные регистра включения подтяжки выводов.
	uint32_t				lckr;				// Данные регистра блокировки настроек.
	uint32_t				afrl;				// Данные младший регистра настроек альтернативных функций выводов.
	uint32_t				afrh;				// Данные cтарши[ регистрjd настроек альтернативных функций выводов.
	uint32_t				odr;				// Состояние на выводах порта после инициализации (в случае, если выводы настроены как выходы).
	uint32_t				p_look_key;			// Указатель на бит блокировки в bit band регионе (быстрое чтение).
};

// Позволяет получить структуру масок начальной инициализации порта из массива структур настроек выводов.
// Пример использования: GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port_a);	// Передаем массив структур pin_config, их колличество, имя порта, для которого требуется получить структуру масок настроки порта.
#define GET_MSK_INIT_PORT(pin_cfg_array, pin_count, port) { \
		.p_port			= p_base_port_address_get					( port ), \
		.moder			= global_port_registr_moder_init_msk		( pin_cfg_array, pin_count, port ), \
		.moder_reset	= global_port_moder_registr_reset_init_msk	( port), \
		.otyper			= global_port_registr_otyper_init_msk		( pin_cfg_array, pin_count, port ), \
		.ospeeder 		= global_port_registr_ospeeder_init_msk		( pin_cfg_array, pin_count, port ), \
		.pupdr			= global_port_registr_pupdr_init_msk		( pin_cfg_array, pin_count, port ), \
		.lckr 			= global_port_registr_lckr_init_msk			( pin_cfg_array, pin_count, port ), \
		.afrl			= global_port_registr_afrl_init_msk			( pin_cfg_array, pin_count, port ), \
		.afrh			= global_port_registr_afrh_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.odr			= global_port_registr_odr_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.p_look_key		= bb_p_port_look_key_get					( port ) \
	}

enum answer_pin_reinit {						// Возвращаемые значения функции переинициализации порта
	answer_pin_reinit_ok				= 0,	// Вывод был успешно переинициализирован.
	answer_pin_reinit_locked			= 1,	// Конфигурация вывода была заблокирована.
	answer_pin_reinit_cfg_number_error	= 2		// Вы попытались инициализировать вывод несуществующей конфигурацией.
};

/*
 * Ответы от функций reinit_all, reinit_port объекта global_port.
 */
enum answer_global_port {
	global_port_reinit_success = 0,				// Переинициализация была успешной.
	global_port_reinit_look = 1					// Порт заблокирован, переинициализация некоторых (или всех) выводов невозможна.
	// В случае reinit_all может быть, что выводы одного или нескольких портов не были переинициализированы.
	// В случае обнаружения блокировки порта - производится попытка переинициализации (на случай, если
	// требуется переинициализировать те выводы, которые заблокированы не были).
	// Данное поведение можно изменить раскомментировав define NO_REINIT_PORT_AFTER_LOOKING в файле
	// stm32_f20x_f21x_conf.h.
};

// Состояние ключа блокировки порта.
enum port_locked_key {
	port_locked_kay_set			= 1,
	port_locked_kay_reset		= 0
};

// Возвращаемые значения функции блокировки порта/портов.
enum answer_port_set_lock {
	answer_port_lock_ok			= 0,			// Порт был успешно заблокирован.
	answer_port_look_already	= 1,			// Порт был уже заблокирован до нас.
	answer_port_lock_error		= 2				// После попытки заблокировать порт - порт не был заблокирован.
};

#endif
