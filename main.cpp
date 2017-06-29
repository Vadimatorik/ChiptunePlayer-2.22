#include "main.h"

__attribute__( ( section( ".irq_table" ) ) )
volatile const char ddd_test_arry[] = "1234567";

extern "C" {
int main (void){
    ayplayer_clock_init();
    ayplayer_port_init();
    ayplayer_spi_init();
    ayplayer_housekeeping_init();

    vTaskStartScheduler();
    while ( true ) {};
}
}
