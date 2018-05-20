#include "ayplayer_gpio.h"
#include "port.h"
#include "user_os.h"

/*!
 * Структуры конфигурации аналоговых входов.
 */

/// Напряжение на аккумуляторе
/// ( делитель 1/2 ).
const pinCfg adcBatCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_0,
		.Mode		=	GPIO_MODE_ANALOG,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Правый аудио канал (перед усилителем).
/// ( делитель 1/2 ).
const pinCfg adcRightCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_4,
		.Mode		=	GPIO_MODE_ANALOG,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Левый аудио канал (перед усилителем).
/// ( делитель 1/2 ).
const pinCfg adcLeftPinCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_1,
		.Mode		=	GPIO_MODE_ANALOG,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/*!
 * Структуры конфигурации выводов качельки громкости.
 */

/// Вход кнопки "громче", без подтяжки.
const pinCfg buttonIncCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_1,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Вход кнопки "тише", без подтяжки.
const pinCfg buttonDecCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_2,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/*!
 * Структура конфигурации вывода MIDI входа ( USART2 ).
 */

const pinCfg midiUartRxCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_3,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF7_USART2
	}
};

/*!
 * Структуры конфигурации выводов управления связи с lcd.
 * LCD == SPI1 + TIM3.
 */

/// SPI1.CLK
const pinCfg lcdClkCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_5,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF5_SPI1
	}
};

/// TIM3.CHANNEL_1 PWM (подсветка).
const pinCfg lcdPwmCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_6,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF2_TIM3
	}
};

/// SPI1.MOSI
const pinCfg lcdMosiCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_7,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF5_SPI1
	}
};

/// LCD.RESET
const pinCfg lcdResCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_4,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/// LCD.DC
const pinCfg lcdDcCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_5,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/// LCD.CS
const pinCfg lcdCsCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_2,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/*!
 * Структуры конфигурации выводов взаимодействия
 * с картой памяти, подключенной по SDIO.
 * SD1 == SDIO + GPIO
 */

/// SD1.PUSH
const pinCfg sd1PushCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_0,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// SDIO.SMD
const pinCfg sd1SmdCfg = {
	.GPIOx			=	GPIOD,
	.init = {
		.Pin		=	GPIO_PIN_2,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/// SDIO.D0
const pinCfg sd1D0Cfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_8,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/// SDIO.D1
const pinCfg sd1D1Cfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_9,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/// SDIO.D2
const pinCfg sd1D2Cfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_10,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/// SDIO.D3
const pinCfg sd1D3Cfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_11,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/// SDIO.CLK
const pinCfg sd1ClkCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_12,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF12_SDIO
	}
};

/*!
 * Структуры конфигурации выводов USB_FS.
 */

/// USB.VBUS
const pinCfg otgFsVbusCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_9,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// USB.DM
const pinCfg usbDmCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_11,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF10_OTG_FS
	}
};

/// USB.DP
const pinCfg usbDpCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_12,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF10_OTG_FS
	}
};

/*!
 * Структуры конфигурации выводов взаимодействия
 * с AY и YM чипами.
 * AY == GPIO + TIM1 + SPI3
 */

/// AY1.BDIR
/// AY2.BDIR
const pinCfg bdirCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_12,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/// AY1.RES
const pinCfg ay1ResCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_15,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// AY2.RES
const pinCfg ay2ResCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_15,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// AY1.BC1
/// AY2.BC1
const pinCfg bc1Cfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_6,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	0
	}
};

/// AY1.CLK (TIM1 CHANNEL_2N)
/// AY2.CLK (TIM1 CHANNEL_2N)
/// Опорная частота звуковых генераторов.
const pinCfg ayClkCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_0,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF1_TIM1
	}
};

/// SPI3.CLK
/// Тактовый сигнал для интерфейса SPI цифровых
/// потенциометров и сдвиговых регистров параллельной
/// шины звуковых генераторов.
const pinCfg spiAudioClkCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_3,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	GPIO_AF6_SPI3
	}
};

/// SPI3.TX
/// Сигнал данных интерфейса SPI цифровых
/// потенциометров и сдвиговых регистров параллельной
/// шины звуковых генераторов.
const pinCfg spiAudioTxCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_5,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	GPIO_AF6_SPI3
	}
};

/// DP.SHDN
/// Вывод размыкания цифровых потенциометров от общей цепи.
const pinCfg shdnCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_6,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// SR.ST
/// Вывод-защелка сдвигового регистра
/// параллельной шины звуковых генераторов.
const pinCfg spiAudioStRegCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_8,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/// DP.CS
/// Выбор в качестве приемника данных от
/// SPI цифровых потенциометров.
const pinCfg dpCsCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_14,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/*!
 * Структура конфигурации вывода настроенного
 * как вход для считывания состояния клавиш с
 * клавиатуры, подключенной через сдвиговые
 * регистры в параллель с одном входом (смотреть схему)
 */
const pinCfg buttonInCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_7,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLDOWN,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/*!
 * Структуры конфигурации выводов SWD отладки.
 */

/// SWD.IO
const pinCfg swdIoCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_13,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF0_SWJ
	}
};

/// SWD.CLK
const pinCfg swdClkCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_14,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLDOWN,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF0_SWJ
	}
};

/*!
 * Структуры конфигурации выводы контроля питания.
 */

/// Запуск DC-DC преобразователя VBAT --> 5V.
const pinCfg pwr5vOnCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_8,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Подача напряжения на всю плату
/// (может подаваться при нажатии на физическую
/// клавишу включения).
const pinCfg pwrOnCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_1,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Флаг окончания зарядки аккумулятора.
/// Подтягивается к земле по окончании зарядки.
/// В противном случае находится в
/// высокоимпедансном состоянии.
const pinCfg tpStCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_14,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Флаг того, что аккумулятор заряжается.
/// Подтягивается к земле на время зарядки.
/// В противном случае находится в высокоимпедансном состоянии.
const pinCfg tpChCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_15,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/// Подача питания на первый звуковой генератор.
const pinCfg chip1PwrOnCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_4,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	0
	}
};

/// Подача питания на второй звуковой генератор.
const pinCfg chip2PwrOnCfg = {
	.GPIOx			=	GPIOA,
	.init = {
		.Pin		=	GPIO_PIN_10,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	0
	}
};

/*!
 * Структуры конфигурации выводов взаимодействия
 * с картой памяти, подключенной по SPI.
 * SD2 == SPI2 + GPIO
 */

/// SPI2.RX
const pinCfg sd2RxCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_2,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF5_SPI2
	}
};

/// SPI2.TX
const pinCfg sd2TxCfg = {
	.GPIOx			=	GPIOC,
	.init = {
		.Pin		=	GPIO_PIN_3,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF5_SPI2
	}
};

/// SPI2.CLK
const pinCfg sd2ClkCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_13,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	GPIO_AF5_SPI2
	}
};

/// SD2.CS
const pinCfg sd2CsCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_7,
		.Mode		=	GPIO_MODE_OUTPUT_PP,
		.Pull		=	GPIO_PULLUP,
		.Speed		=	GPIO_SPEED_FREQ_VERY_HIGH,
		.Alternate	=	0
	}
};

/// SPI2.PUSH
/// (подтяжка к земле при подключенной карте)
const pinCfg sd2PushCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_9,
		.Mode		=	GPIO_MODE_INPUT,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_LOW,
		.Alternate	=	0
	}
};

/*!
 * Структуры конфигурации выводов
 * отладочного USART.
 */
/// USART3.TX
const pinCfg bootTxCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_10,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	GPIO_AF7_USART3
	}
};

/// USART3.RX
const pinCfg bootRxCfg = {
	.GPIOx			=	GPIOB,
	.init = {
		.Pin		=	GPIO_PIN_11,
		.Mode		=	GPIO_MODE_AF_PP,
		.Pull		=	GPIO_NOPULL,
		.Speed		=	GPIO_SPEED_FREQ_MEDIUM,
		.Alternate	=	GPIO_AF7_USART3
	}
};

/*!
 * Объекты выводов общего назначения,
 * которые будут использованы программно.
 */

/// LCD.
Pin lcdRes				( &lcdResCfg );				/// Сброс.
Pin lcdDc				( &lcdDcCfg );				/// Данные/команда.
Pin lcdCs				( &lcdCsCfg );				/// Выбор экрана в качестве
													/// приемника данных SPI.

// MICROSD 2.
Pin sd2Cs				( &sd2CsCfg );				/// Выбор SD2 карты в качестве
													/// приемника данных SPI.
// Защелка сдвигового регистра.
Pin spiAudioStReg		( &spiAudioStRegCfg );

/// Звуковые генераторы..
Pin bdir				( &bdirCfg );
Pin bc1					( &bc1Cfg );
Pin chip1PwrOn			( &chip1PwrOnCfg );			/// Подача питания на первый чип.
Pin chip2PwrOn			( &chip2PwrOnCfg );			/// Подача питания на второй чип.

/// Для обращений file play.
Pin pwrAy[ 2 ] = {
	chip1PwrOn,
	chip2PwrOn
};

// PWR.
Pin pwr5vOn				( &pwr5vOnCfg );
Pin pwrOn				( &pwrOnCfg );

// Потенциометры.
Pin dpCs				( &dpCsCfg );				/// Выбор цифровых потенциометров в качестве
													/// приемников данных SPI.
Pin shdn				( &shdnCfg );				/// Отключение потенциометров от общей цепи.

// Общий вход кнопок.
Pin buttonIn			( &buttonInCfg );			/// Общий вход клавиатуры, подключенной
													/// через параллельную шину (сдвиговые регистры).

// + - громкость.
Pin buttonInc			( &buttonIncCfg );
Pin buttonDec			( &buttonDecCfg );



/*!
 * Передаем основному объекту все используемые выводы.
 */
ayplayerGpio gpioStruct = {
	.lcd = {
		.res				= &lcdRes,
		.dc					= &lcdDc,
		.cs					= &lcdCs,
	},
	.sd2 = {
		.cs					= &sd2Cs
	},
	.srSpiAudio = {
		.st					= &spiAudioStReg
	},
	.ay = {
		.bdir				= &bdir,
		.bc1				= &bc1
	},
	.pwr = {
		.chip_1_pwr			= &chip1PwrOn,
		.chip_2_pwr			= &chip2PwrOn,
		.pwr_5v				= &pwr5vOn,
		.all_pwr			= &pwrOn,
	},
	.dp = {
		.cs					= &dpCs,
		.shdn				= &shdn,
	},
	.buttonIn				= &buttonIn,
	.vr = {
		.inc				= &buttonInc,
		.dec				= &buttonDec
	}
};

/*!
 * Структура конфигурации объекта глобального порта.
 */
const pinCfg gpCfg[] = {
	/// BUTTON.
	buttonIncCfg, buttonDecCfg,

	/// ADC.
	adcBatCfg, adcRightCfg, adcLeftPinCfg,

	/// MIDI (USART2).
	midiUartRxCfg,

	/// LCD (SPI1 + TIMx).
	lcdClkCfg, lcdPwmCfg, lcdMosiCfg,
	lcdResCfg, lcdDcCfg, lcdCsCfg,

	// micro-sd (SDIO + GPIO).
	sd1PushCfg, sd1SmdCfg, sd1D0Cfg,
	sd1D1Cfg, sd1D2Cfg, sd1D3Cfg,
	sd1ClkCfg,

	/// USB (USB_FS + GPIO).
	otgFsVbusCfg, usbDmCfg, usbDpCfg,

	/// AY (GPIO + TIM1 + SPI3).
	bdirCfg, ay1ResCfg, ay2ResCfg,
	bc1Cfg, ayClkCfg, spiAudioClkCfg,
	spiAudioTxCfg, shdnCfg,
	spiAudioStRegCfg, dpCsCfg,

	/// SPI клавиатура (SPI общий AY, тут только вход).
	buttonInCfg,

	/// PWR.
	pwr5vOnCfg, pwrOnCfg, tpStCfg,
	tpChCfg, chip1PwrOnCfg,
	chip2PwrOnCfg,

	/// MICRO-SD SPI2 (SPI2 + GPIO).
	sd2RxCfg, sd2TxCfg, sd2ClkCfg,
	sd2CsCfg, sd2PushCfg,

	/// BOOT-USART (USART3).
	bootTxCfg, bootRxCfg,

	/// SWD.
	swdIoCfg, swdClkCfg,
};


/*!
 * Все используемые выводы контроллера.
 */
GlobalPort gp( gpCfg, M_SIZE_ARRAY( gpCfg ) );
