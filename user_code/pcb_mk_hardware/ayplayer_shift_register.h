#pragma once

#include "module_shift_register.h"
#include "ayplayer_spi.h"
#include "ayplayer_port.h"
#include "ayplayer_os_object.h"

void ayplayer_shift_register ( void );

extern uint8_t sr_out_buf_ay[2];                    // Для AY.
extern uint8_t sr_out_buf_button[1];                // Для кнопок.

extern module_shift_register   sr_ay;
extern module_shift_register   sr_button;
