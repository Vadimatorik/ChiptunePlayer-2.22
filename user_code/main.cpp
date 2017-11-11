#include "main.h"

extern "C" {

int main (void){
  //  ayplayer_wdt_init();
    ayplayer_port_init();
    ayplayer_clock_init();
    ayplayer_adc_init();

    ayplayer_spi_init();
    ayplayer_housekeeping_init();
   // ayplayer_timers_init();
   // ayplayer_button_init();
   // ayplayer_core_init();
  /*  ayplayer_shift_register();
    ayplayer_ay_init();
    ayplayer_play_task_init();
    ayplayer_battery_check_init();*/
    vTaskStartScheduler();
    while ( true ) {};
}

}
