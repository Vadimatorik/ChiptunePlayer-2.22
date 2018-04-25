#include "stm32f2xx_hal.h"
#include "ay_ym_low_lavel.h"
#include "microsd_card_sdio.h"
#include "uart.h"
#include "spi.h"

extern AyYmLowLavel				ayLow;
extern MicrosdSdio				sd1;
extern Uart						usart3;
extern SpiMaster8Bit			spi1;
extern SpiMaster8Bit			spi2;
extern SpiMaster8Bit			spi3;

extern "C" {

extern void xPortSysTickHandler ( void );

void SysTick_Handler				( void ) {
	HAL_IncTick();
	xPortSysTickHandler();
}

void TIM6_DAC_IRQHandler			( void ) {
	ayLow.timerInterruptHandler();
}

void DMA1_Stream3_IRQHandler		( void ) {
	spi2.irqHandler();
}

void DMA1_Stream4_IRQHandler		( void ) {
	spi2.irqHandler();
}

void DMA1_Stream7_IRQHandler		( void ) {
	spi3.irqHandler();
}

void DMA2_Stream5_IRQHandler		( void ) {
	spi1.irqHandler();
}

void DMA2_Stream6_IRQHandler		( void ) {
	sd1.dmaRxHandler();
};

void USART3_IRQHandler				( void ) {
	usart3.irqHandler();
}

}

