#pragma once

#include "adc.h"

//#define ADC_BATTERY_CHANNEL_CFG                 ADC::CFG::NAME::ADC1, 0, ADC::CFG::RES::R_12BIT, ADC::CFG::SAMPLING_TIME::C_480
extern adc_one_channel adc_input_obj;

void ayplayer_adc_init ( void );
