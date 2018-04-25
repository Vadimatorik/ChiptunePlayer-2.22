#include "rcc.h"
#include "user_os.h"
#include "ayplayer.h"

const rccCfg ay_player_clock_cfg[ AYPLAYER_RCC_CFG_COUNT ] = {
	/*!
	 * Индекс: 0
	 * Источник: внешний резонатор на 16 МГц.
	 * PCLK:			120 МГц.
	 * AHB1:			120 МГц.
	 * APB2:			60 МГц.
	 * APB1:			30 МГц.
	 */
	{
		.osc = {
			.OscillatorType				=	RCC_OSCILLATORTYPE_HSE,
			.HSEState					=	RCC_HSE_ON,
			.LSEState					=	RCC_LSE_OFF,
			.HSIState					=	RCC_HSI_OFF,
			.HSICalibrationValue		=	RCC_HSICALIBRATION_DEFAULT,
			.LSIState					=	RCC_LSI_OFF,
			.PLL = {
				.PLLState				=	RCC_PLL_ON,
				.PLLSource				=	RCC_PLLSOURCE_HSE,
				.PLLM					=	16,
				.PLLN					=	240,
				.PLLP					=	RCC_PLLP_DIV2,
				.PLLQ					=	5
			}
		},
		.clk = {
			.ClockType					=	RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
			.SYSCLKSource				=	RCC_SYSCLKSOURCE_PLLCLK,
			.AHBCLKDivider				=	RCC_SYSCLK_DIV1,
			.APB1CLKDivider				=	RCC_HCLK_DIV4,
			.APB2CLKDivider				=	RCC_HCLK_DIV2,
		},
		.fLatency						=	FLASH_LATENCY_3
	},
	/*!
	 * Индекс: 1
	 * Источник: внутренняя RC-цепь.
	 * PCLK:			120 МГц.
	 * AHB1:			120 МГц.
	 * APB2:			60 МГц.
	 * APB1:			30 МГц.
	 */
	{
		.osc = {
			.OscillatorType				=	RCC_OSCILLATORTYPE_HSI,
			.HSEState					=	RCC_HSE_OFF,
			.LSEState					=	RCC_LSE_OFF,
			.HSIState					=	RCC_HSI_ON,
			.HSICalibrationValue		=	RCC_HSICALIBRATION_DEFAULT,
			.LSIState					=	RCC_LSI_OFF,
			.PLL = {										 // Не используется. Значения на угад в реальном диапазоне.
				.PLLState				=	RCC_PLL_ON,
				.PLLSource				=	RCC_PLLSOURCE_HSI,
				.PLLM					=	16,
				.PLLN					=	240,
				.PLLP					=	RCC_PLLP_DIV2,
				.PLLQ					=	5
			}
		},
		.clk = {
			.ClockType					=	RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
			.SYSCLKSource				=	RCC_SYSCLKSOURCE_PLLCLK,
			.AHBCLKDivider				=	RCC_SYSCLK_DIV1,
			.APB1CLKDivider				=	RCC_HCLK_DIV4,
			.APB2CLKDivider				=	RCC_HCLK_DIV2
		},
		.fLatency						=	FLASH_LATENCY_3
	},
	/*!
	 * Индекс: 2
	 * Источник: внутренняя RC-цепь.
	 * PCLK:			16 МГц.
	 * AHB1:			16 МГц.
	 * APB2:			16 МГц.
	 * APB1:			16 МГц.
	 */
	{
		.osc = {
			.OscillatorType				=	RCC_OSCILLATORTYPE_HSI,
			.HSEState					=	RCC_HSE_OFF,
			.LSEState					=	RCC_LSE_OFF,
			.HSIState					=	RCC_HSI_ON,
			.HSICalibrationValue		=	RCC_HSICALIBRATION_DEFAULT,
			.LSIState					=	RCC_LSI_OFF,
			.PLL = {
				.PLLState				=	RCC_PLL_OFF,
				.PLLSource				=	RCC_PLLSOURCE_HSI,
				.PLLM					=	16,
				.PLLN					=	240,
				.PLLP					=	RCC_PLLP_DIV2,
				.PLLQ					=	1
			}
		},
		.clk = {
			.ClockType					=	RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
			.SYSCLKSource				=	RCC_SYSCLKSOURCE_HSI,
			.AHBCLKDivider				=	RCC_SYSCLK_DIV1,
			.APB1CLKDivider				=	RCC_HCLK_DIV1,
			.APB2CLKDivider				=	RCC_HCLK_DIV1,
		},
		.fLatency						=	FLASH_LATENCY_0
	},
	/*!
	 * Индекс: 3
	 * Источник: внешний HSE.
	 * PCLK:			16 МГц.
	 * AHB1:			16 МГц.
	 * APB2:			16 МГц.
	 * APB1:			16 МГц.
	 */
	{
		.osc = {
			.OscillatorType				=	RCC_OSCILLATORTYPE_HSE,
			.HSEState					=	RCC_HSE_ON,
			.LSEState					=	RCC_LSE_OFF,
			.HSIState					=	RCC_HSI_OFF,
			.HSICalibrationValue		=	RCC_HSICALIBRATION_DEFAULT,
			.LSIState					=	RCC_LSI_OFF,
			.PLL = {
				.PLLState				=	RCC_PLL_OFF,
				.PLLSource				=	RCC_PLLSOURCE_HSI,
				.PLLM					=	16,
				.PLLN					=	240,
				.PLLP					=	RCC_PLLP_DIV2,
				.PLLQ					=	1
			},
		},
		.clk = {
			.ClockType					=	RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
			.SYSCLKSource				=	RCC_SYSCLKSOURCE_HSI,
			.AHBCLKDivider				=	RCC_SYSCLK_DIV1,
			.APB1CLKDivider				=	RCC_HCLK_DIV1,
			.APB2CLKDivider				=	RCC_HCLK_DIV1,
		},
		.fLatency						=	FLASH_LATENCY_0
	}
};

Rcc ayplayer_rcc( ay_player_clock_cfg, AYPLAYER_RCC_CFG_COUNT );
