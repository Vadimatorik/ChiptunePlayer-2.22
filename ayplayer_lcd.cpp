#include "ayplayer_lcd.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t lcd_buffer[1024] = { 0 };
mono_lcd_lib_st7565 ayplayer_lcd( &st7565_cfg, lcd_buffer );

void ayplayer_lcd_init ( uint8_t contrast ) {
    ayplayer_lcd.reinit( spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance() );
    ayplayer_lcd.reset();
    ayplayer_lcd.set_contrast( contrast );
    ayplayer_lcd.on();
}
