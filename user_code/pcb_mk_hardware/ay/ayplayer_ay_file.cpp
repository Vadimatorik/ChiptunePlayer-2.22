#include "ayplayer_ay_file.h"

extern ay_ym_low_lavel ay;
void pwr_chip_on ( uint32_t chip, bool state );

ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
    .ay_hardware                = &ay,
    .microsd_mutex              = nullptr,
    .pwr_chip_on                = pwr_chip_on
};

ay_ym_file_mode ay_file_mode(&ay_f_mode_cfg);

void pwr_chip_on ( uint32_t chip, bool state ) {
    switch ( chip ) {
    case 0: ayplayer_chip_2_pwr_on_pin_obj.set( state ); break;
    case 1: ayplayer_chip_1_pwr_on_pin_obj.set( state ); break;
    }
}
