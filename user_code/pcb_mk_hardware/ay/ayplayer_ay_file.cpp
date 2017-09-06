#include "ayplayer_ay_file.h"

extern USER_OS_STATIC_MUTEX spi2_mutex;

extern ay_ym_low_lavel ay;
ay_ym_file_mode_struct_cfg_t ay_f_mode_cfg = {
    .ay_hardware                = &ay,
    .microsd_mutex              = &spi2_mutex,
};

ay_ym_file_mode ay_file_mode(&ay_f_mode_cfg);
