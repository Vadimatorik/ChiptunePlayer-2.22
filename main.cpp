#include <stdint.h>
#include "ayplayer_port.h"

int main (void){
    *((uint32_t*)(0x40023800 + 0x30)) |= 0xFF;

    ayplayer_port_init();

    while ( true ) {
    };
}
