#include "main.h"

int main (void){
    *((uint32_t*)(0x40023800 + 0x30)) |= 0xFF;
    ayplayer_clock_init();
  //  ayplayer_port_init();

    vTaskStartScheduler();
    while ( true ) {};
}
