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
