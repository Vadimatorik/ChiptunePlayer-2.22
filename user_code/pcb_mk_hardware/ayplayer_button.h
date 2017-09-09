#pragma once

#include "buttons_through_shift_register_one_in.h"
#include "ayplayer_port.h"

void ayplayer_button_init ( void );

enum class EC_BUTTON_NAME {
    UP              = 0,
    DOWN,
    LEFT_LONG_PRESS,        LEFT_CLICK,           LONG_LEFT_CLICK,
    RIGHT_LONG_PRESS,       RIGHT_CLICK,          LONG_RIGHT_CLICK,
    ENTER,
    MENU,
    BACK,
};
