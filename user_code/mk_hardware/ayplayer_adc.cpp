#include "ayplayer_adc.h"

adc_one_channel adc_input_obj( nullptr );

void ayplayer_adc_init ( void ) {
    adc_input_obj.reinit();
    adc_input_obj.on();
}
