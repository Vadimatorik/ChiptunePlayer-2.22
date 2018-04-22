#pragma once

#include "pin.h"
#include "port.h"

/*!
 * Комплектация выводов плеера по назначению.
 */
struct gpioLcd {							/// LCD.
	PinBase*	const res;
	PinBase*	const dc;
	PinBase*	const cs;
};

struct gpioSpiSd {							/// SPI MicroSD.
	PinBase*	const cs;
};

struct gpioShiftRegister {					/// Расширитель портов.
	PinBase*	const st;
};

struct gpioAyChip {							/// AY/YM.
	PinBase*	const bdir;
	PinBase*	const bc1;
};

struct gpioPwr {							/// Питание на плате.
	PinBase*	const chip_1_pwr;
	PinBase*	const chip_2_pwr;
	PinBase*	const pwr_5v;
	PinBase*	const all_pwr;
};

struct gpioDigitalPotentiometer {			/// Цифровые потенциометры.
	PinBase*	const cs;
	PinBase*	const shdn;
};

struct gpioVolumeRocker {					/// Качелька громкости.
	PinBase*	const inc;
	PinBase*	const dec;
};

/*!
 * Все используемые программно выводы плеера.
 */
struct ayplayerGpio {
	gpioLcd						lcd;
	gpioSpiSd					sd2;
	gpioShiftRegister			srSpiAudio;
	gpioAyChip					ay;
	gpioPwr						pwr;
	gpioDigitalPotentiometer	dp;
	PinBase*					buttonIn;
	gpioVolumeRocker			vr;
};
