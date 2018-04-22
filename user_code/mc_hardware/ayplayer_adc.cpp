#include "adc.h"

const AdcOneChannelCfg adcBatCfg = {
	.ADCx				=	ADC1,
	.clockPrescaler		=	ADC_CLOCK_SYNC_PCLK_DIV8,
	.resolution			=	ADC_RESOLUTION_12B,
	.dataAlign			=	ADC_DATAALIGN_RIGHT,
	.channel			=	ADC_CHANNEL_0,
	.samplingTime		=	ADC_SAMPLETIME_480CYCLES
};

AdcOneChannel	adcBat( &adcBatCfg, 1 );
