#include "ayplayer_adc.h"

const constexpr adc_one_channel< ADC_BATTERY_CHANNEL_CFG > adc_input;

void ayplayer_adc_init ( void ) {
    adc_input.reinit();
    adc_input.on();
}
