#include "ayplayer_wdt.h"

wdt_cfg ayplayer_wdt_cfg = {
    .task_prio          = 1,
    .run_time_ms        = 200,
    .startup_time_ms    = 200,
    .service_time_ms    = 5000
};

wdt ayplayer_wdt ( &ayplayer_wdt_cfg );

void ayplayer_wdt_init ( void ) {
    ayplayer_wdt.init();
}
