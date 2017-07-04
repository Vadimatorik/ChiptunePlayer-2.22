#include "ayplayer_lcd.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t lcd_buffer[1024] = { 0 };

void ayplayer_lcd_init ( void ) {
    ayplayer_lcd.reinit( spi_master_hardware_os< SPI1_CFG_OBJ_PARAM >::instance() );
    memset(lcd_buffer, 0, 1024);
    ayplayer_lcd.reset();

    ayplayer_lcd.fill_rect_to_buffer(1, 1, 100,30 ,1);
    ayplayer_lcd.update();
}


void housekeeping_thread ( void* arg ) {
    (void) arg;
    TickType_t xLastWakeTime = xTaskGetTickCount ();
    ayplayer_lcd_init();
    while (1) {
        vTaskDelayUntil( &xLastWakeTime, 1000 );
    }
}
