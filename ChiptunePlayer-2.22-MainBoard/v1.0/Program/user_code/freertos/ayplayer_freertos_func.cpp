#include <stdint.h>
#include "stm32f2xx_hal_conf.h"
#include "stm32f2xx_hal.h"
#include "timer.h"
#include "FreeRTOSConfig.h"
#include "ayplayer.h"

extern "C" {
static const uint8_t freeRTOSMemoryScheme = configUSE_HEAP_SCHEME;
}

extern AyPlayer							ay;

#ifdef configGENERATE_RUN_TIME_STATS
extern TimCounter						timRunTimeStats;
#endif

extern "C" {

void vApplicationMallocFailedHook( void ) {
	while(1);
}

void vApplicationStackOverflowHook ( void ) {
	while(1);
}

#ifdef configGENERATE_RUN_TIME_STATS

void vConfigureTimerForRunTimeStats ( void ) {
	/// Таймер настроится при конфигурации RCC внутри AyPlayer.
}

uint32_t vGetRunTimeCounterValue ( void ) {
	return timRunTimeStats.getCounter();
}

#endif

void prvGetRegistersFromStack ( uint32_t *pulFaultStackAddress ) {
	__attribute__((unused)) volatile uint32_t r0;
	__attribute__((unused)) volatile uint32_t r1;
	__attribute__((unused)) volatile uint32_t r2;
	__attribute__((unused)) volatile uint32_t r3;
	__attribute__((unused)) volatile uint32_t r12;
	__attribute__((unused)) volatile uint32_t lr; 		/// Link register.
	__attribute__((unused)) volatile uint32_t pc;		/// Program counter.
	__attribute__((unused)) volatile uint32_t psr;		/// Program status register.

	r0	=	pulFaultStackAddress[ 0 ];
	r1	=	pulFaultStackAddress[ 1 ];
	r2	=	pulFaultStackAddress[ 2 ];
	r3	=	pulFaultStackAddress[ 3 ];

	r12	=	pulFaultStackAddress[ 4 ];
	lr	=	pulFaultStackAddress[ 5 ];
	pc	=	pulFaultStackAddress[ 6 ];
	psr	=	pulFaultStackAddress[ 7 ];

	for( ;; );
}


}
