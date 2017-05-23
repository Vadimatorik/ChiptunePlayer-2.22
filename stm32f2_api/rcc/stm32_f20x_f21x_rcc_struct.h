#ifndef STM32F2_API_RCC_STM32_F20X_F21X_RCC_STRUCT_H_
#define STM32F2_API_RCC_STM32_F20X_F21X_RCC_STRUCT_H_

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
	volatile uint32_t	bdc_;
	volatile uint32_t	cs;
	volatile uint32_t	res_9;
	volatile uint32_t	res_10;
	volatile uint32_t	sscg;
	volatile uint32_t	pll_i2s_cfg;
}

#endif
