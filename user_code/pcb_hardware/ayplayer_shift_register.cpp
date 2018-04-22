#include "../../module_shift_register/shift_register.h"
#include "spi.h"
#include "pin.h"
#include "user_os.h"

extern SpiMaster8Bit	ayplayer_spi3_obj;
extern Pin				ayplayer_spi_audio_st_reg_pin_obj;

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf_ay[2]		 = { 0 };			// Для AY.
uint8_t sr_out_buf_button[1]	 = { 0 };			// Для кнопок.

const ShiftRegisterCfg sr_ay_cfg_cfg = {
	.st						= &ayplayer_spi_audio_st_reg_pin_obj,
	.dataArray				= sr_out_buf_ay,
	.arraySize				= M_SIZE_ARRAY( sr_out_buf_ay ),
	.strobActive			= true,
	.spiObj					= &ayplayer_spi3_obj,
	.mutex					= nullptr
};

ShiftRegister	sr_ay( &sr_ay_cfg_cfg );

const ShiftRegisterCfg sr_button_cfg_cfg = {
	.st						= &ayplayer_spi_audio_st_reg_pin_obj,
	.dataArray				= sr_out_buf_button,
	.arraySize				= M_SIZE_ARRAY( sr_out_buf_button ),
	.strobActive			= true,
	.spiObj					= &ayplayer_spi3_obj,
	.mutex					= nullptr
};

ShiftRegister	sr_button( &sr_button_cfg_cfg );
