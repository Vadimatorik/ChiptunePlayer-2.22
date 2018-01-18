#include "ayplayer_lcd_driver.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

const mono_lcd_lib_st7565_cfg_t st7565_cfg {
    .a0     = &ayplayer_lcd_dc_pin_obj,
    .res    = &ayplayer_lcd_res_pin_obj,
    .cs     = &ayplayer_lcd_cs_pin_obj,
    .p_spi  = &spi1_obj,
    .mode   = ST7565_MODE::STANDARD
};

extern "C" {

uint8_t lcd_buffer[1024] = { 0 };

}

mono_lcd_lib_st7565 ayplayer_lcd( &st7565_cfg, lcd_buffer );
