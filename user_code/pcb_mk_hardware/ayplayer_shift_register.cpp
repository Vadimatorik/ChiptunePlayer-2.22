#include "ayplayer_shift_register.h"

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf[2] = { 0 };

USER_OS_STATIC_MUTEX_BUFFER     sr_mutex_buf = USER_OS_STATIC_MUTEX_BUFFER_INIT_VALUE;
USER_OS_STATIC_MUTEX            sr_mutex     = nullptr;

const module_shift_register_cfg_t sr_cfg_sr_cfg = {
    .st                     = &spi_audio_st_reg_obj,
    .number_output_byte     = 2,
    .buffer_out             = sr_out_buf,
    .strob_active           = true,
    .p_spi                  = &spi3,
    .mutex                  = &sr_mutex
};

module_shift_register   sr( &sr_cfg_sr_cfg );


void ayplayer_shift_register ( void ) {
    sr_mutex = USER_OS_STATIC_MUTEX_CREATE( &sr_mutex_buf );

    sr.init();
}
