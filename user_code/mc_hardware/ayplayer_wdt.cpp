#include "wdt.h"

const wdt_cfg ayplayer_wdt_cfg = {
	.task_prio			= 1,
	.run_time_ms		= 200,
	.startup_time_ms	= 500,
	.service_time_ms	= 5000
};

wdt ayplayer_wdt_obj ( &ayplayer_wdt_cfg );
