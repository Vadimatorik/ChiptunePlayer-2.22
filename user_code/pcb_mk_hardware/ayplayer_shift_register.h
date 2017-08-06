#pragma once

#include "module_shift_register.h"
#include "ayplayer_spi.h"
#include "ayplayer_port.h"
#include "user_os.h"

extern module_shift_register   sr;
extern uint8_t sr_out_buf[2];

void ayplayer_shift_register ( void );
