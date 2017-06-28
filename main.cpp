#include "main.h"

int main (void){
    ayplayer_clock_init();
    ayplayer_port_init();
    ayplayer_spi_init();
    ayplayer_housekeeping_init();

    vTaskStartScheduler();
    while ( true ) {};
}
