#include "ayplayer_shift_register.h"

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf_ay[2]         = { 0 };           // Для AY.
uint8_t sr_out_buf_button[1]     = { 0 };           // Для кнопок.


const module_shift_register_cfg_t sr_ay_cfg_cfg = {
    .st                     = &spi_audio_st_reg_obj,
    .number_output_byte     = 2,
    .strob_active           = true,
    .p_spi                  = &spi3,
    .mutex                  = &m_spi3
};
module_shift_register   sr_ay( &sr_ay_cfg_cfg );

const module_shift_register_cfg_t sr_button_cfg_cfg = {
    .st                     = &spi_audio_st_reg_obj,
    .number_output_byte     = 1,
    .strob_active           = true,
    .p_spi                  = &spi3,
    .mutex                  = &m_spi3
};
module_shift_register   sr_button( &sr_button_cfg_cfg );

void ayplayer_shift_register ( void ) {
    sr_ay.init( sr_out_buf_ay );
    sr_button.init( sr_out_buf_button );
}
