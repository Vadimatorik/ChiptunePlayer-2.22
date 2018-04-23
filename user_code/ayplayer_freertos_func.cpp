#include <stdint.h>
#include "stm32f2xx_hal_conf.h"
#include "stm32f2xx_hal.h"
#include "timer.h"
#include "FreeRTOSConfig.h"
#include "ayplayer.h"

extern AyPlayer							ay;

#ifdef configGENERATE_RUN_TIME_STATS
extern TimCounter						timRunTimeStats;
#endif

extern "C" {

#ifdef configGENERATE_RUN_TIME_STATS

void vConfigureTimerForRunTimeStats ( void ) {
	/// Таймер настроится при конфигурации RCC внутри AyPlayer.
}

uint32_t vGetRunTimeCounterValue ( void ) {
	return timRunTimeStats.getCounter();
}

#endif

}
