#pragma once

#include "module_digital_potentiometer_ad5204.h"
#include "ayplayer_spi.h"
#include "ayplayer_port.h"
#include "ayplayer_core_obj.h"

extern ad5204< 2 > sound_dp;

EC_AD5204_ANSWER dp_update_value ( void );
