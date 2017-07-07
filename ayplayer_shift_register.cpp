#include "ayplayer_shift_register.h"

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf[2] = { 0 };

const module_shift_register_cfg_t sr_cfg_sr_cfg = {
    .st                     = &spi_audio_st_reg_obj,
    .number_output_byte     = 2,
    .buffer_out             = sr_out_buf,
    .strob_active           = true
};

module_shift_register   sr( &sr_cfg_sr_cfg );

void ayplayer_shift_register ( void ) {
    sr.init( spi3 );
    sr_out_buf[1] = 0b00001111;
    sr.write();
}
