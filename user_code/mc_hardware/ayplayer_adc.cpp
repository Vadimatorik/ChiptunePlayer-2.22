#include "adc.h"

const adc_one_channel_cfg adc_bat = {
    .ADCx               = ADC1,
    .clock_prescaler    = ADC_CLOCK_SYNC_PCLK_DIV8,
    .resolution         = ADC_RESOLUTION_12B,
    .data_align         = ADC_DATAALIGN_RIGHT,
    .channel            = ADC_CHANNEL_0,
    .sampling_time      = ADC_SAMPLETIME_480CYCLES
};

adc_one_channel adc_bat_obj( &adc_bat );
