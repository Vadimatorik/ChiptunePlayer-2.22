#ifndef STM32F2_API_RCC_STM32_F20X_F21X_RCC_H_
#define STM32F2_API_RCC_STM32_F20X_F21X_RCC_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

/*
 * В этом файле находится классы, предназначенные для работы
 * с RCC модулем stm32f2 (настройке частот и включения/выключения тактирования).
 */
#include "stm32_f20x_f21x_rcc_struct.h"			// Необходимые структуры.

/*
 * Объект конфигурации основного PLL.
 * Этот объект (или массив этих объектов) используется классом
 * rcc.
 */
class main_pll {
public:
	constexpr				main_pll					(const pll_cfg *const cfg):
		cfgr_msk(reg_cfgr_msk_get(cfg))
	{}

private:
	constexpr	uint32_t	reg_cfgr_msk_get			(const pll_cfg *const cfg);

	const		uint32_t	cfgr_msk;
};

/*
 * Через этот объект производятся все манипуляции с частотами.
 */
class rcc {
public:
	constexpr rcc(const rcc_cfg	*const cfg) {};

private:
	constexpr int get_array ( void );

	//const  uint8_t a[aaa];
};
#include "stm32_f20x_f21x_rcc_func.h"			// Функции constexpr.

#endif
#endif
