#include "module_shift_register.h"
#include "spi.h"
#include "pin.h"
#include "user_os.h"

extern spi_master_8bit	spi3_obj;
extern pin				ayplayer_spi_audio_st_reg_pin_obj;

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf_ay[2]		 = { 0 };			// Для AY.
uint8_t sr_out_buf_button[1]	 = { 0 };			// Для кнопок.

const module_shift_register_cfg_t sr_ay_cfg_cfg = {
	.st						= &ayplayer_spi_audio_st_reg_pin_obj,
	.data_array				= sr_out_buf_ay,
	.array_size				= M_SIZE_ARRAY( sr_out_buf_ay ),
	.strob_active			= true,
	.p_spi					= &spi3_obj,
	.mutex					= nullptr
};

module_shift_register	sr_ay( &sr_ay_cfg_cfg );

const module_shift_register_cfg_t sr_button_cfg_cfg = {
	.st						= &ayplayer_spi_audio_st_reg_pin_obj,
	.data_array				= sr_out_buf_button,
	.array_size				= M_SIZE_ARRAY( sr_out_buf_button ),
	.strob_active			= true,
	.p_spi					= &spi3_obj,
	.mutex					= nullptr
};

module_shift_register	sr_button( &sr_button_cfg_cfg );
