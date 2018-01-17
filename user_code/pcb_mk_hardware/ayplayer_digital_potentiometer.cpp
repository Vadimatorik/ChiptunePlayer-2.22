#include "ayplayer_digital_potentiometer.h"
#include "ayplayer_core_obj.h"

ad5204_struct_cfg_t sound_dp_cfg = {
    .spi        = &spi3_obj,
    .mutex      = &m_spi3,
    .cs         = &dp_cs_res_pin_obj,
    .shdn       = &shdn_pin_obj
};

ad5204< 2 > sound_dp( &sound_dp_cfg );

extern ayplayer_global_data_struct g;

EC_AD5204_ANSWER dp_update_value ( void ) {
    EC_AD5204_ANSWER    r;
    r = sound_dp.value_set( 0, 0, g.dp.b );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 1, g.dp.c );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 2, g.dp.a );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 3, g.dp.a1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 0, g.dp.b1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 1, g.dp.c1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 2, g.dp.left);
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 3, g.dp.right );
    return r;
}
