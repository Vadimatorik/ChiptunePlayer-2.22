#pragma once

#include "buttons_through_shift_register_one_in.h"
#include "ayplayer_port.h"
#include "ayplayer_os_object.h"
#include "ayplayer_shift_register.h"

void ayplayer_button_init ( void );


enum class EC_BUTTON_NAME {
    UP              = 0,
    DOWN,
    LEFT_LONG_PRESS,    LEFT_LONG_CLICK,    LEFT_CLICK,
    RIGHT_LONG_PRESS,   RIGHT_LONG_CLICK,   RIGHT_CLICK,
    ENTER,
    MENU,
    BACK,
};
