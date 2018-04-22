#include "../../../module_chiptune/ay_ym_file_mode/ay_ym_file_mode.h"
#include "../../../module_chiptune/ay_ym_low_lavel/ay_ym_low_lavel.h"
#include "user_os.h"
#include "pin.h"

extern AyYmLowLavel						ayplayer_ay_low_obj;
extern Pin									ayplayer_chip_1_pwr_on_pin_obj;
extern Pin									ayplayer_chip_2_pwr_on_pin_obj;

/*!
 * Метод позволяет отключать неиспользуемый в данный момент AY/YM чип
 * для экономии энергии.
 */
void pwr_chip_on ( uint32_t chip, bool state ) {
	switch ( chip ) {
	case 0: ayplayer_chip_2_pwr_on_pin_obj.set( state ); break;
	case 1: ayplayer_chip_1_pwr_on_pin_obj.set( state ); break;
	}
}


ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
	.ay_hardware                = &ayplayer_ay_low_obj,
    .microsd_mutex              = nullptr,
    .pwr_chip_on                = pwr_chip_on
};

AyYmFileMode ayplayer_ay_file_mode_obj(&ay_f_mode_cfg);

