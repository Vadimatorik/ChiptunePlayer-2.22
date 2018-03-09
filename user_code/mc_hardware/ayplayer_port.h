#pragma once

#include "pin.h"
#include "port.h"

/*!
 * Комплектация выводов плеера по назначению.
 */
struct ayplayer_gpio_lcd_struct {							/// LCD.
	pin_base*	res;
	pin_base*	dc;
	pin_base*	cs;
};

struct ayplayer_gpio_spi_sd_struct {						/// SPI MicroSD.
	pin_base*	cs;
};

struct ayplayer_gpio_shift_register_struct {				/// Расширитель портов.
	pin_base*	st;
};

struct ayplayer_gpio_ay_chip_struct {						/// AY/YM.
	pin_base*	bdir;
	pin_base*	bc1;
};

struct ayplayer_gpio_pwr_struct {							/// Питание на плате.
	pin_base*	chip_1_pwr;
	pin_base*	chip_2_pwr;
	pin_base*	pwr_5v;
	pin_base*	all_pwr;
};

struct ayplayer_gpio_digital_potentiometer_struct {			/// Цифровые потенциометры.
	pin_base*	cs;
	pin_base*	shdn;
};

struct ayplayer_gpio_volume_rocker_struct {					/// Качелька громкости.
	pin_base*	inc;
	pin_base*	dec;
};

/*!
 * Все используемые программно выводы плеера.
 */
struct ayplayer_gpio_struct {
	ayplayer_gpio_lcd_struct					lcd;
	ayplayer_gpio_spi_sd_struct					sd2;
	ayplayer_gpio_shift_register_struct			sr_spi_audio;
	ayplayer_gpio_ay_chip_struct				ay;
	ayplayer_gpio_pwr_struct					pwr;
	ayplayer_gpio_digital_potentiometer_struct	dp;
	pin_base*									button_in;
	ayplayer_gpio_volume_rocker_struct			vr;
};
