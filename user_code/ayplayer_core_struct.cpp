#include "ayplayer_core_struct.h"

ayplayer_state ayplayer_control;

void ayplayer_state::play_state_set ( EC_AY_PLAY_STATE state ) {
    this->play_state = state;
}

EC_AY_PLAY_STATE ayplayer_state::play_state_get ( void ) {
    return this->play_state;
}

void ayplayer_state::active_window_set ( EC_AY_ACTIVE_WINDOW win ) {
    this->active_window = win;
}

EC_AY_ACTIVE_WINDOW ayplayer_state::active_window_get ( void ) {
    return this->active_window;
}

void ayplayer_state::battery_voltage_set ( float battery_voltage ) {
     this->battery_voltage.post_val( battery_voltage );
}

float ayplayer_state::battery_voltage_get ( void ) {
    return this->battery_voltage.get_and_reset();
}

EC_AD5204_ANSWER ayplayer_state::dp_update_value ( void ) {
    EC_AD5204_ANSWER    r;
    r = sound_dp.value_set( 0, 0, this->dp_low.b );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 1, this->dp_low.c );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 2, this->dp_low.a );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 0, 3, this->dp_low.a1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 0, this->dp_low.b1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 1, this->dp_low.c1 );
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 2, this->dp_low.left);
    if ( r != EC_AD5204_ANSWER::OK ) return r;
    r = sound_dp.value_set( 1, 3, this->dp_low.right );
    return r;
}
