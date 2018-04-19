#pragma once

#include "pin.h"
#include "port.h"

/*!
 * Комплектация выводов плеера по назначению.
 */
struct gpioLcd {							/// LCD.
	PinBase*	res;
	PinBase*	dc;
	PinBase*	cs;
};

struct gpioSpiSd {							/// SPI MicroSD.
	PinBase*	cs;
};

struct gpioShiftRegister {					/// Расширитель портов.
	PinBase*	st;
};

struct gpioAyChip {							/// AY/YM.
	PinBase*	bdir;
	PinBase*	bc1;
};

struct gpioPwr {							/// Питание на плате.
	PinBase*	chip_1_pwr;
	PinBase*	chip_2_pwr;
	PinBase*	pwr_5v;
	PinBase*	all_pwr;
};

struct gpioDigitalPotentiometer {			/// Цифровые потенциометры.
	PinBase*	cs;
	PinBase*	shdn;
};

struct gpioVolumeRocker {					/// Качелька громкости.
	PinBase*	inc;
	PinBase*	dec;
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
