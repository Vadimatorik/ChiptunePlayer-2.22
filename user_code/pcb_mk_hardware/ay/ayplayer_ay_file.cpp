#include "ayplayer_ay_file.h"

extern USER_OS_STATIC_MUTEX spi2_mutex;

extern ay_ym_low_lavel ay;
static void pwr_chip_on ( uint32_t chip, bool state );

ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
    .ay_hardware                = &ay,
    .microsd_mutex              = &spi2_mutex,
    .pwr_chip_on                = pwr_chip_on
};

ay_ym_file_mode ay_file_mode(&ay_f_mode_cfg);

static void pwr_chip_on ( uint32_t chip, bool state ) {
    switch ( chip ) {
    case 0: chip_2_pwr_on_obj.set( state ); break;
    case 1: chip_1_pwr_on_obj.set( state ); break;
    }
}
