#pragma once

#include "microsd_card.h"
#include "ayplayer_port.h"
#include "ayplayer_spi.h"

extern microsd_spi sd2;

bool sd2_get_presence_state ( void );
