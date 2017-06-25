#include "main.h"

int main (void){
    ayplayer_clock_init();
    ayplayer_port_init();

    vTaskStartScheduler();
    while ( true ) {};
}
