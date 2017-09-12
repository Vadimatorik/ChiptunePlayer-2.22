#include "ayplayer_adc.h"

#define ADC_BATTERY_CHANNEL_CFG                 ADC::CFG::NAME::ADC1, 0, ADC::CFG::RES::R_8BIT, ADC::CFG::SAMPLING_TIME::C_28
const constexpr adc_one_channel< ADC_BATTERY_CHANNEL_CFG > adc_input;

void ayplayer_adc_init ( void ) {
    adc_input.reinit();
    adc_input.on();
}
