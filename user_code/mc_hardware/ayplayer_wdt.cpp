#include "wdt.h"

const wdtCfg ayplayer_wdt_cfg = {
	.taskPrio			= 1,
	.runTimeMs			= 1000,
	.startupTimeMs		= 5000,
	.serviceTimeMs		= 5000
};

Wdt wdtObj ( &ayplayer_wdt_cfg, 1 );
