#include "ayplayer_lcd.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

const mono_lcd_lib_st7565_cfg_t st7565_cfg {
    .a0     = &lcd_dc_obj,
    .res    = &lcd_res_obj,
    .cs     = &lcd_cs_obj,
    .spi    = &spi1
};

uint8_t lcd_buffer[1024] = { 0 };
mono_lcd_lib_st7565 ayplayer_lcd( &st7565_cfg, lcd_buffer );

void ayplayer_lcd_init ( uint8_t contrast ) {
    ayplayer_lcd.reinit();
    ayplayer_lcd.reset();
    ayplayer_lcd.set_contrast( contrast );
    ayplayer_lcd.on();
}
