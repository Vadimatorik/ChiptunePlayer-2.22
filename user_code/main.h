#pragma once

#include "freertos_headers.h"

#include "ayplayer_clock.h"
#include "ayplayer_port.h"
#include "ayplayer_spi.h"

#include "ayplayer_housekeeping.h"
#include "ayplayer_lcd.h"
#include "ayplayer_gui_low.h"
#include "ayplayer_microsd_card.h"
#include "ayplayer_timers.h"
#include "ayplayer_shift_register.h"
#include "ayplayer_ay_low.h"

#include <stdint.h>

/*
5.08.2017 18.42
Print Size:
   text	   data	    bss	    dec	    hex	filename
 119916	   3404	  21368	 144688	  23530	build/ay_player.elf

После переписи на pin внешний.
Print Size:
   text	   data	    bss	    dec	    hex	filename
 124768	   3432	  23744	 151944	  25188	build/ay_player.elf

 После решения проблемы с хардом.
 122328	   3408	  21584	 147320	  23f78
*/
