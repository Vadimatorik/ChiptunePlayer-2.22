#include "stm32f2xx_hal.h"

extern "C" {

extern void xPortSysTickHandler ( void );
void SysTick_Handler(void) {
	HAL_IncTick();
	xPortSysTickHandler();
}

}
