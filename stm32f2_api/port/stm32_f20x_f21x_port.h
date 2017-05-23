#ifndef STM32F2_API_STM32_F20X_F21X_PORT_H_
#define STM32F2_API_STM32_F20X_F21X_PORT_H_

#include "stm32_f20x_f21x_conf.h"						// Конфигурация всей библиотеки.
#include "stm32_f20x_f21x_port_struct.h"				// Используемые структуры enum-ы.
#include "stm32_f20x_f21x_port_func.h"					// constexpr функции.

/*
 * В данном файле содержатся классы объектов для полноценной работы с портами ввода-вывода.
 * Краткое описание:
 * global_port	- данный объект позволяет работать со всеми имеющимися в контроллере портами ввода-вывода.
 *                В проекте должен быть один экземляр (объект) данного класса.
 *                Объект предоставляет следующие возможности:
 *                1. Переинициализации конкретных или всех портов (при условии, что те не были заблокированы).
 *                		О блокировки более подробно написано в описании global_port класса.
 *                2. Имеется возможность блокировки конкретных или всех портов.
 *                3. Получаение данных о текущем состоянии блокировки.
 * Примечание: Для инициализации объекта используются массив структур pin_config.
 * 1. В случае, если не была передана структура какого-либо вывода (структура, описывающая режим работы вывода),
 * то он настроен в состояние по умолчанию (за исключением некоторых выводов, предназначенных для отладки,
 * это "вход без подтяжки").
 * 2. На каждый вывод порта должна быть одна структура. В случае, если на один вывод будет передано несколько
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
 * Предполагается, что начальная инициализация всех выводов производится при инициализации всех портов объектом
 * global_port. Что избавляет от надобности начальной инициализации выводов.
 * В случае, если в процессе работы программы будет нужно сменить режим работы вывода (при условии, что он не был
 * заблокирован объектом global_port), это можно сделать по средствам метода reinit, в который требуется передать
 * номер (счет с 0), структуры инициализации в массиве, указанной при создании объекта.
 */

/*
 * Класс для создания объекта линии ввода-вывода.
 * Прототип (объект) данного класса следует создавать в том случае, когда вывод точно будет использоваться
 * в ручном (управляется пользователем) режиме. Помимо этого разрешено использование и других конфигураций этой же
 * линии порта ввода-вывода, которые можно менять в процессе работы. Подробнее в примерах.
 */

class pin {
public:
	constexpr	pin ( const pin_config_t *pin_cfg_array, const uint32_t pin_cout );
	constexpr	pin ( const pin_config_t *pin_cfg_array );
	void		set				( void ) const;					// Устанавливает "1" на выходе (для случая, когда вывод настроен как выход).
	void		reset			( void ) const;					// Устанавливает "0" на выходе (для случая, когда вывод настроен как выход).
	void		invert			( void ) const;					// Логическое "не" состояния на выходе вывода (для случая, когда вывод настроен как выход).
	int			read			( void ) const;					// Считывает состояние вывода (для случая, когда вывод настроен как вход).
	answer_pin_reinit reinit (uint32_t number_config) const;	// Переинициализирует вывод в ходе выполнения программы в выбранную конфигурацию.

private:
	constexpr	uint32_t		set_msk_get				( const pin_config_t *const pin_cfg_array );
	constexpr	uint32_t		reset_msk_get			( const pin_config_t *const pin_cfg_array );
	constexpr	uint32_t		bb_p_idr_read_get		( const pin_config_t *const pin_cfg_array );
	constexpr	uint32_t		p_odr_get				( const pin_config_t *const pin_cfg_array );
	constexpr	uint32_t		odr_bit_read_bb_p_get	( const pin_config_t *const pin_cfg_array );
	constexpr	uint32_t		bb_p_looking_bit_get	( const pin_config_t *const pin_cfg_array );

	const 		pin_config_t	*cfg;						// Указатель на конфигурации, используемые выводом.
	const 		uint32_t		count;						// Колличество объектов конфигурации.
	const		uint32_t		p_odr;						// Указатель на ODR регистр порта, к которому относится вывод.
	const		uint32_t		p_port;						// Указатель на структуру регистров порта в памяти периферии мк.
	const		uint32_t		p_bb_odr_read;				// Для быстрого чтения выставленного в ODR (пользователем) состояния вывода (ножно для invert метода).
	const		uint32_t		set_msk;					// По этой маске устанавливается бит в ODR.
	const		uint32_t		reset_msk;					// Соответственно, сбрасывается бит в ODR.
	const		uint32_t		p_bb_idr_read;				// Для быстрого чтения состояния вывода.
	const		uint32_t		p_bb_key_looking;			// Указатель на ключ блокировки порта, к которому относится вывод.
	const		uint32_t		p_bb_looking_bit;			// Указатель на бит блокировки конкретного вывода в порту, к которому относится вывод.
};
#include "stm32_f20x_f21x_port_func_class_pin_constexpr.h"

/*
 * Класс глобального порта. Через него происходит управление выводами и сменой конфигурации.
 */
class global_port {
public:
	constexpr	global_port	( const pin_config_t *const pin_cfg_array, const uint32_t pin_count );

	// Важно: в случае, если некоторые (или все) выводы порта/портов были заблокированы,
	// попытка переинициализации все равно производится.
	// Это нужно на случай, когда требуется переинициализировать некоторые (1 и более) выводов
	// не трогая другие.
	// Данное поведение можно сменить в stm32_f20x_f21x_conf.h, NO_REINIT_PORT_AFTER_LOOKING.
	answer_global_port		reinit_all_ports			( void ) const;					// Метод инициализирует в реальном времени все порты ввода-вывода контроллера,
																						// основываясь на переданном во время формирования объекта pin_config массива.
	answer_global_port		reinit_port					( enum_port_name port ) const;	// Переинициализирует конкретный порт.
	port_locked_key			get_state_locked_key_port	( enum_port_name port ) const;	// Узнаем, заблокирован порт или нет.
	answer_port_set_lock	set_locked_key_port			( enum_port_name port ) const;	// Блокируем порт в соответствии с конфигурацией.
	answer_port_set_lock	set_locked_keys_all_port	( void ) const; 				// Блокируем все порты в соответствии с конфигурацией.

private:
	const		global_port_msk_reg_struct				gb_msk_struct;						// Маски регистров всех портов.
				void 						write_image_port_in_registrs	( uint32_t number ) const;		// Служебный метод: записывает образ начальной инициализации в регистры порта.
	constexpr	uint32_t					moder_reg_reset_init_msk		( enum_port_name port_name );
	constexpr	uint32_t					reg_moder_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_otyper_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_ospeeder_init_msk			( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_pupdr_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_lckr_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_afrl_init_msk				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_afrh_msk_init_get			( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr	uint32_t					reg_odr_msk_init_get			( const pin_config_t *const pin_cfg_array, const uint32_t pin_count, const enum_port_name port_name );
	constexpr 	global_port_msk_reg_struct	fill_out_mas_struct				( const pin_config_t *const pin_cfg_array, const uint32_t pin_count );
	constexpr	port_registers_flash_copy_struct fill_out_one_port_struct( enum_port_name p_name, const pin_config_t *const pin_cfg_array, const uint32_t pin_count );

};
#include "stm32_f20x_f21x_port_func_class_global_port_constexpr.h"

#endif
