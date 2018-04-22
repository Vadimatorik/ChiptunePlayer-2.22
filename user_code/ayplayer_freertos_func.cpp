#include <stdint.h>
#include "stm32f2xx_hal_conf.h"
#include "stm32f2xx_hal.h"
#include "timer.h"
#include "FreeRTOSConfig.h"
#include "ayplayer.h"

extern AyPlayer		ay;

#ifdef configGENERATE_RUN_TIME_STATS
extern TimCounter		timRunTimeStatsInterruptObj;
#endif

extern "C" {

#ifdef configGENERATE_RUN_TIME_STATS

void vConfigureTimerForRunTimeStats ( void ) {
	timRunTimeStatsInterruptObj.reinit( 0 );
	timRunTimeStatsInterruptObj.on();
}

uint32_t vGetRunTimeCounterValue ( void ) {
	return timRunTimeStatsInterruptObj.getCounter();
}

#endif

}
