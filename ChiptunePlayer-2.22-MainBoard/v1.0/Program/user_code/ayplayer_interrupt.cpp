#include "stm32f2xx_hal.h"
#include "ay_ym_low_lavel.h"
#include "microsd_card_sdio.h"
#include "uart.h"
#include "spi.h"
#include "pwr.h"

extern AyYmLowLavel				ayLow;
extern MicrosdSdio				sd1;
extern Uart						usart3;
extern SpiMaster8Bit			spi1;
extern SpiMaster8Bit			spi2;
extern SpiMaster8Bit			spi3;
extern Pwr						pwr;
extern AyYmLowLavel				ayLow;

extern "C" {

extern void xPortSysTickHandler ( void );

void HardFault_Handler ( void ) {
	__asm volatile
	(
		" tst lr, #4												\n"
		" ite eq													\n"
		" mrseq r0, msp												\n"
		" mrsne r0, psp												\n"
		" ldr r1, [r0, #24]											\n"
		" ldr r2, handler2_address_const							\n"
		" bx r2														\n"
		" handler2_address_const: .word prvGetRegistersFromStack	\n"
	);
}

void PVD_IRQHandler					( void ) {
	pwr.irqHandler();
	while(1);
}

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

