#ifndef STM32F2_API_STM32_F20X_F21X_PORT_H_
#define STM32F2_API_STM32_F20X_F21X_PORT_H_

#include "stm32_f20x_f21x_conf.h"

/*
 * В данном файле содержатся классы объектов для полноценной работы с портами ввода-вывода.
 * Краткое описание:
 * global_port	- данный объект позволяет работать со всеми имеющимеся в контроллере портами ввода-вывода.
 *                В проекте должен быть один экземляр (объект) данного класса.
 *                Объект предоставляет следущие возможности:
 *                1. Переинициализации конкретных или всех портов (при условии, что те не были заблокированы).
 *                		О блокировки более подробно написано в описании global_port класса.
 *                2. Имеется возможность блокировки конкретных или всех портов.
 *                3. Получаение данных о текущем состоянии блокировки.
 * Примечание: Для инициализации объекта используюется массив структур pin_config.
 * 1. В случае, если не была передана структура какого-либо вывода (структура, описывающая режим работы вывода),
 * то он настроен в состояние по-умолчанию (за исключением некоторых выводов, предназначенных для отладки,
 * это "вход без подтяжки").
 * 2. На каждый вывод порта должна быть одни структура. В случае, если на один вывод будет передано несколько
 * структур - вывод будет переинициализирован именно по последней указанной (чей индекс в массиве старше).
 * 3. Объект не предполагает работу с конкретными выводами. Наименьшая единица, которой может упровлять объект -
 * - порт.
 * 4. Массив объектов pin_config (объявленных как constexpr const), не должен быть помещен во flash память
 * (линкер автоматически выкинет их из .elf или любого другого конечного файла прошивки). Т.к. объект использует
 * constexpr методы, которые анализируют все переданные в объект структуры и выдают на выходе готовые маски портов.
 * С помощью которых можно значительно ускорить процесс инициализации портов.
 *
 * pin - данный объект позволяет работать с конкретным выводом порта. При инициализации объекта в него можно передать
 * массив структур pin_config. В отличии от объекта global_port, объект pin использует их в реальном времени.
 * В связи с чем они пойдут в итоговый файл прошивки (что скажется на его объеме).
 * Важно понимать, что все структуры конфигурации вывода должны относится к одному физическому выводу (изменяя
 * лишь режим его работы).
 * Предполагается, что начальная инициализая всех выводов производится при инициализации всех портов объектом
 * global_port. Что избавляет от надобности начальной инициализации выводов.
 * В случае, если в процессе работы программы будет нужно сменить режим работы вывода (при условии, что он не был
 * заблокирован объектом global_port), это можно сделать по средствам метода reinit, в который требуется передать
 * номер (счет с 0), структуры инициализации в массиве, указанной при создании объекта.
 */

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
	port_registers_struct	*p_port;			// Указатель на структуру порта port_registers_struct в области памяти переферии (базовое смещение порта в карте памяти контроллера).
	uint32_t				moder;				// Данные регистра выбора режима работы выводов.
	uint32_t				moder_reset;		// Значение регистра moder, которое имеет порт по-умолчанию (для безопасного переключения).
	uint32_t				otyper;				// Данные регистра выбора режима выхода (в случае, если вывод настроен как выход).
	uint32_t				ospeeder;			// Данные регистра выбора скорости выводов.
	uint32_t				pupdr;				// Данные регистра включения подтяжки выводов.
	uint32_t				lckr;				// Данные регистра блокировки настроек.
	uint32_t				afrl;				// Данные младший регистра настроек альтернативных функций выводов.
	uint32_t				afrh;				// Данные cтарши[ регистрjd настроек альтернативных функций выводов.
	uint32_t				odr;				// Состояние на выводах порта после инициализации (в случае, если выводы настроены как выходы).
	uint32_t				*look_key;			// Указатель на бит блокировки в bit band регионе (быстрое чтение).
};

/*
 * Перечень имеющихся физических портов ввода-вывода контроллера (зависит от выбранного в stm32_f20x_f21x_conf.h контроллера).
 */
#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE) \
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

/*
 * Заблокировать настройку вывода после начальной инициализации.
 * Важно! Блокировка применяется только один раз объектом global_port. Во время последующей
 * работы заблокировать иные выводы или же отключить блокировку текущих - невозможно.
 * Единственный способ снять блокировку - перезагрузка чипа.
 */
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
	pin_locked				locked;					// Заблокировать ли настройку данного вывода во время инициализации global_port объекта.
	pin_state_after_init	state_after_init;		// Состояние на выходе после инициализации (в случае, если вывод настроен как выход).
};

// Возвращаемые значения функции переинициализации порта
enum answer_pin_reinit	{
	answer_pin_reinit_ok = 0,				// Вывод был успешно переинициализирован.
	answer_pin_reinit_locked = 1,			// Конфигурация вывода была заблокирована.
	answer_pin_reinit_cfg_number_error = 2	// Вы попытались инициализировать вывод несуществующей конфигурацией.
};


/*
 * Возвращает указатель на выбранный порт ввода-вывода на карте памяти в соответствии с выбранным контроллером.
 */
constexpr port_registers_struct* point_base_port_address_get( port_name port_name ) {
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
constexpr uint32_t* bit_banding_point_look_port_key_get ( port_name port_name ) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(port_name);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;														// Прибавляем смещение к IDR регистру.
	return (uint32_t*)BIT_BAND_PER(port_point, 16);							// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

/*
 * Методы, необходимые для констурктора класса вывода.
 */
// Маска установки выхода в "1".
constexpr uint32_t pin_set_msk_get ( const pin_config *pin_cfg_array ) {
	return 1 << pin_cfg_array->pin_name;
}

// Маска установки выхода в "0".
constexpr uint32_t pin_reset_msk_get ( const pin_config *pin_cfg_array ) {
	return 1 << (pin_cfg_array->pin_name + 16);
}

// Указатель на bit_banding область памяти, в которой находится бит состояния входа.
constexpr uint32_t* pin_read_banding_point_bit_get ( const pin_config *pin_cfg_array ) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x10;																	// Прибавляем смещение к IDR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

// Возвращаем указатель на регистр ODR, к которому относится вывод.
constexpr uint32_t* pin_odr_registr_point_get( const pin_config *pin_cfg_array ) {
	uint32_t point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем указатель на порт, к которому относится бит.
	return (uint32_t *)(point += 0x14);												// 0x14 - смещение от начала порта.
}

// Получаем указатель на bit banding область памяти, с выставленным пользователем состоянием.
constexpr uint32_t* pin_odr_read_bit_banding_point_bit_get ( const pin_config *pin_cfg_array ) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x14;																	// Прибавляем смещение к ODR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра ODR (состояние на входе).
}

// Получаем указатель на бит блокировки конфигурации конкретного вывода.
constexpr uint32_t* pin_bit_banding_point_looking_bit_get ( const pin_config* pin_cfg_array ) {
	uint32_t port_point = (uint32_t)point_base_port_address_get(pin_cfg_array->port);	// Получаем физический адресс порта вывода.
	port_point += 0x1C;																	// Прибавляем смещение к LCKR регистру.
	return (uint32_t *)BIT_BAND_PER(port_point, pin_cfg_array->pin_name);				// Получаем адрес конкретного бита регистра LCKR.
}

/*
 * Класс для создания объекта линии ввода-вывода.
 * Прототип (объект) данного класса следует создавать в том случае, когда вывод точно будет использоваться
 * в ручном (управляется пользователем) режиме. Помимо этого разрешено использование и других конфигураций этой же
 * линии порта ввода-вывода, которые можно менять в процессе работы. Подробнее в примерах.
 */
class pin {
public:
	constexpr pin ( const pin_config *pin_cfg_array, const uint32_t pin_cout ):
		cfg(pin_cfg_array), count(pin_cout), set_msk(pin_set_msk_get(pin_cfg_array)),
		port(point_base_port_address_get(pin_cfg_array->port)),	odr(pin_odr_registr_point_get(pin_cfg_array)),
		bit_banding_odr_read(pin_odr_read_bit_banding_point_bit_get(pin_cfg_array)),
		reset_msk(pin_reset_msk_get(pin_cfg_array)), bit_banding_idr_read(pin_read_banding_point_bit_get(pin_cfg_array)),
		bit_banding_key_looking(bit_banding_point_look_port_key_get(pin_cfg_array->port)),
		bit_banding_looking_bit(pin_bit_banding_point_looking_bit_get(pin_cfg_array))
	{};

	void		set			();							// Устанавливает "1" на выходе (для случая, когда вывод настроен как выход).
	void		reset		();							// Устанавливает "0" на выходе (для случая, когда вывод настроен как выход).
	void		invert		();							// Логическое "не" состояния на выходе вывода (для случая, когда вывод настроен как выход).
	int			read		();							// Считывает состояние вывода (для случая, когда вывод настроен как вход).
	answer_pin_reinit reinit (uint32_t number_config);	// Переинициализирует вывод в ходе выполнения программы в выбранную конфигурацию.

private:
	const pin_config		*cfg;						// Указатель на конфигурации, используемые выводом.
	const uint32_t			count;						// Колличество объектов конфигурации.
	uint32_t				*odr;						// Указатель на ODR регистр порта, к которому относится вывод.
	port_registers_struct	*port;						// Указатель на структуру регистров порта в памяти переферии мк.
	uint32_t				*bit_banding_odr_read;		// Для быстрого чтения выставленного в ODR состояния вывода (ножно для invert метода).
	uint32_t				set_msk;					// По этой маске устанавливается бит в ODR.
	uint32_t				reset_msk;					// Соответственно, сбрасывается бит в ODR.
	uint32_t				*bit_banding_idr_read;		// Для быстрого чтения состояния вывода.
	uint32_t				*bit_banding_key_looking;	// Указатель на ключ блокировки порта, к которому относится вывод.
	uint32_t				*bit_banding_looking_bit;	// Указатель на бит блокировки конкретного вывода в порту, к которому относится вывод.
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
enum port_locked_key		{port_locked_kay_set = 1, port_locked_kay_reset = 0};

// Возвращаемые значения функции блокировки порта/портов.
enum answer_port_set_lock	{
	answer_port_lock_ok = 0,				// Порт был успешно заблокирован.
	answer_port_look_already = 1,			// Порт был уже заблокирован до нас.
	answer_port_lock_error = 2				// После попытки заблокировать порт - порт не был заблокирован.
};


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
constexpr uint32_t global_port_registr_moder_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_moder = global_port_registr_moder_reset_msk_init_get(port_name);	// Начальное значение зависит от порта.

	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){									// Проходимся по всем структурам.
		if (pin_cfg_array[loop_pin].port != port_name){continue;};									// Если вывод не относится к нашему порту - выходим.
		registr_moder &= ~(0b11 << pin_cfg_array[loop_pin].pin_name * 2);							// Сбрасываем предыдущую настройку этого вывода.
		registr_moder |= pin_cfg_array[loop_pin].mode << pin_cfg_array[loop_pin].pin_name * 2;		// Иначе производим добавление по маске.
	}
	return registr_moder;
}

// Режим выхода.
constexpr uint32_t global_port_registr_otyper_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_otyper = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_otyper &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_otyper |= pin_cfg_array[loop_pin].output_config << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_otyper;
}

// Скорость.
constexpr uint32_t global_port_registr_ospeeder_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
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
constexpr uint32_t global_port_registr_pupdr_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
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
constexpr uint32_t global_port_registr_lckr_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
	uint32_t registr_lckr = 0;
	for (uint32_t loop_pin = 0; loop_pin < pin_count; loop_pin++){
		if (pin_cfg_array[loop_pin].port != port_name){continue;};
		registr_lckr &= ~(1 << pin_cfg_array[loop_pin].pin_name);
		registr_lckr |= pin_cfg_array[loop_pin].locked << pin_cfg_array[loop_pin].pin_name;
	}
	return registr_lckr;
}

// Младший регистр выбора альтернативной функции.
constexpr uint32_t global_port_registr_afrl_msk_init_get( const pin_config *pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
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
constexpr uint32_t global_port_registr_afrh_msk_init_get( const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
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
constexpr uint32_t global_port_registr_odr_msk_init_get(const pin_config *const pin_cfg_array, const uint32_t pin_count, const port_name port_name) {
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
		.p_port			= point_base_port_address_get					( port), \
		.moder			= global_port_registr_moder_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.moder_reset	= global_port_registr_moder_reset_msk_init_get	( port), \
		.otyper			= global_port_registr_otyper_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.ospeeder 		= global_port_registr_ospeeder_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.pupdr			= global_port_registr_pupdr_msk_init_get		( pin_cfg_array, pin_count, port ), \
		.lckr 			= global_port_registr_lckr_msk_init_get			( pin_cfg_array, pin_count, port ), \
		.afrl			= global_port_registr_afrl_msk_init_get			( pin_cfg_array, pin_count, port ), \
		.afrh			= global_port_registr_afrh_msk_init_get			( pin_cfg_array, pin_count, port ), \
		.odr			= global_port_registr_odr_msk_init_get			( pin_cfg_array, pin_count, port ), \
		.look_key		= bit_banding_point_look_port_key_get			( port ) \
	}


/*
 * Класс глобального порта. Через него происходит управление выводами и сменой конфигурации.
 */
class global_port {
public:
	constexpr	global_port	( const pin_config *pin_cfg_array, const uint32_t pin_count );

	// Важно: в случае, если некоторые (или все) выводы порта/портов были заблокированы,
	// попытка переинициализации все равно производится.
	// Это нужно на случай, когда требуется переинициализировать некоторые (1 и более) выводов
	// не трогая другие.
	// Данное поведение можно сменить в stm32_f20x_f21x_conf.h, NO_REINIT_PORT_AFTER_LOOKING.
	answer_global_port		reinit_all_ports			();						// Метод инициализирует в реальном времени все порты ввода-вывода контроллера,
																				// основываясь на переданном во время формирования объекта pin_config массива.
	answer_global_port		reinit_port					(port_name port);		// Переинициализирует конкретный порт.
	port_locked_key			get_state_locked_key_port	(port_name port);		// Узнаем, заблокирован порт или нет.
	answer_port_set_lock	set_locked_key_port			(port_name port);		// Блокируем порт в соответствии с конфигурацией.
	answer_port_set_lock	set_locked_keys_all_port	();						// Блокируем все порты в соответствии с конфигурацией.

private:
	port_registers_flash_copy_struct					init_array[STM32_F2_PORT_COUNT];// Дубликат регистров для переинициализации всех портов контроллера.
		// STM32_F2_PORT_COUNT - этот define автоматически определяется при выборе конкретного контроллера в stm32_f20x_f21x_conf.h.
	void 		write_image_port_in_registrs			(uint32_t number);		// Служебный метод: записывает образ начальной инициализации в регистры порта.
};

/*
 * Конструктор готовит маски для начальной инициализации выводов.
 * Колличество портов, а так же их именя задаются автоматически после выбора чипа в stm32_f20x_f21x_conf.h.
 */
constexpr global_port::global_port( const pin_config *pin_cfg_array, const uint32_t pin_count):
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

#endif
