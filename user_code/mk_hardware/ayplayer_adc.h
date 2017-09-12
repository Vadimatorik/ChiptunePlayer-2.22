#pragma once

#include "include_module_lib.h"

#define ADC_BATTERY_CHANNEL_CFG                 ADC::CFG::NAME::ADC1, 0, ADC::CFG::RES::R_8BIT, ADC::CFG::SAMPLING_TIME::C_28
extern const adc_one_channel< ADC_BATTERY_CHANNEL_CFG > adc_input;

void ayplayer_adc_init ( void );
