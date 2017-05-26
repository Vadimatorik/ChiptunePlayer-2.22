#ifndef STM32F2_API_RCC_STM32_F20X_F21X_RCC_STRUCT_H_
#define STM32F2_API_RCC_STM32_F20X_F21X_RCC_STRUCT_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

/*
 * Регистры физического модуля RCC.
 * res_x - зарезервированные области памяти rcc модуля.
 */
struct __attribute__((packed)) rcc_registers_struct {
	volatile uint32_t	c;
	volatile uint32_t	pll_cfg;
	volatile uint32_t	cfg;
	volatile uint32_t	ci;
	volatile uint32_t	ahb_1_rst;
	volatile uint32_t	ahb_2_rst;
	volatile uint32_t	ahb_3_rst;
	volatile uint32_t	res_0;
	volatile uint32_t	apb_1_rst;
	volatile uint32_t	apb_2_rst;
	volatile uint32_t	res_1;
	volatile uint32_t	res_2;
	volatile uint32_t	ahb_1_en;
	volatile uint32_t	ahb_2_en;
	volatile uint32_t	ahb_3_en;
	volatile uint32_t	res_3;
	volatile uint32_t	apb_1_en;
	volatile uint32_t	apb_2_en;
	volatile uint32_t	res_4;
	volatile uint32_t	res_5;
	volatile uint32_t	ahb_1_lp_en;
	volatile uint32_t	ahb_2_lp_en;
	volatile uint32_t	ahb_3_lp_en;
	volatile uint32_t	res_6;
	volatile uint32_t	apb_1_lp_en;
	volatile uint32_t	apb_2_lp_en;
	volatile uint32_t	res_7;
	volatile uint32_t	res_8;
	volatile uint32_t	bdc;
	volatile uint32_t	cs;
	volatile uint32_t	res_9;
	volatile uint32_t	res_10;
	volatile uint32_t	sscg;
	volatile uint32_t	pll_i2s_cfg;
};

// Задает источник тактового сигнала для PLL.
enum enum_pll_source {
	pll_source_hsi	= 0,
	pll_source_hse	= 1,
};

/*
 * Структура описывает один режим работы PLL.
 */
struct pll_cfg {
	enum_pll_source			s;		// Источник тактового сигнала PLL (Основного и audio).
	uint8_t					m;		// Входная частота в PLL должна быть разделена
									// этим делителем до 1-2 МГц.
									// m должно находится в диапазоне 2..63 включая границы.
	uint16_t				n;		// Этот множитель умножает частоту, полученную
									// делителем выше (1-2 МГц).
									// Выходная частота после этого множителя
									// должна быть в диапазоне 192..432 МГц включая границы.
									// n должен принимать значение в диапазоне 192..432,
									// включая границы.
	uint8_t					p;		// Этот делитель делит полученную предыдущим множителем
									// частоту (192..432 МГц) в частоту системной шины.
									// Выходная частота не должна превышать 120 МГц.
									// p должен принимать значения: 2, 4, 6, 8.
};

/*
 * Структура включает в себя все структуры, которые планируется
 * использовать во время работы для изменения параметров RCC.
 */
struct rcc_cfg {
	const pll_cfg			*const pll;			// Режимы PLL.
	uint8_t					pll_count;			// Количество режимов.
};

/*
 * Для работы внутренних функций.
 */
enum enum_rcc_cfgr_reg_pos {};
#endif
#endif
