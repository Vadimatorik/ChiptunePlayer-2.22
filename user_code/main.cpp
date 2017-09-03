#include "main.h"

extern "C" {

int main (void){
    ayplayer_clock_init();
    ayplayer_port_init();
    ayplayer_spi_init();
    ayplayer_housekeeping_init();
    ayplayer_timers_init();
    ayplayer_button_init();
    ayplayer_gui_core_init();
    ayplayer_shift_register();
    ayplayer_ay_init();
    ayplayer_play_task_init();
    vTaskStartScheduler();
    while ( true ) {};
}

}
