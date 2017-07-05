#include "ayplayer_lcd.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t lcd_buffer[1024] = { 0 };

char test_w[] = "Hello World!";

void ayplayer_lcd_init ( void ) {
    ayplayer_lcd.reinit( spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance() );
    ayplayer_lcd.reset();
    ayplayer_lcd.set_brightness(8);
    ayplayer_lcd.on();
    sd_lcd.clear();
    sd_lcd.print_string(font_gost_type_b_12_rle, 0, 0, (char*)"Hello World!!!", 1, 1 );
    ayplayer_lcd.update();
    //ayplayer_lcd.print_string_to_buffer(font_gost_type_b_12_rle, 10, 10, (char*)test_w, 1, 1);
    //ayplayer_lcd.fill_rect_to_buffer(1, 1, 100,30 ,1);
    //ayplayer_lcd.update();
}


void housekeeping_thread ( void* arg ) {
    (void) arg;
   // TickType_t xLastWakeTime = xTaskGetTickCount ();
    ayplayer_lcd_init();

    uint8_t l = 0;
    while (1) {
        sd_lcd.clear();
        sd_lcd.print_string(font_gost_type_b_12_rle, l, l, (char*)"Hello World!!!", 1, 1 );
        ayplayer_lcd.update();
        l++;
        if (l == 32) l =0 ;
//        /        vTaskDelayUntil( &xLastWakeTime, 10 );

    }
}
