#include "ayplayer_digital_potentiometer.h"

ad5204_struct_cfg_t sound_dp_cfg = {
    .spi        = &spi3,
    .mutex      = &spi3_mutex,
    .cs         = &dp_cs_res_obj,
    .shdn       = &shdn_obj
};

ad5204< 2 > sound_dp( &sound_dp_cfg );

