/*!
 * \file
 * \brief Файл содержит в себе заглушки обработчиков всех возможно 
 * используемых прерываний используемого микроконтроллера.
 */

extern "C" {
	void __attribute__( ( weak ) ) HardFault_Handler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) MemManage_Handler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) BusFault_Handler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) UsageFault_Handler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) SVC_Handler						( void ) { while( true ); }
	void __attribute__( ( weak ) ) DebugMon_Handler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) PendSV_Handler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) SysTick_Handler					( void ) { while( true ); }
    void __attribute__( ( weak ) ) NMI_Handler                      ( void ) { while( true ); }

	void __attribute__( ( weak ) ) WWDG_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) PVD_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) TAMP_STAMP_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) RTC_WKUP_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) FLASH_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) RCC_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI0_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI1_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI2_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI3_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI4_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream0_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream1_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream2_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream3_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream4_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream5_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream6_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) ADC_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN1_TX_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN1_RX0_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN1_RX1_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN1_SCE_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI9_5_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM1_BRK_TIM9_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM1_UP_TIM10_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM1_TRG_COM_TIM11_IRQHandler	( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM1_CC_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM2_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM3_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM4_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C1_EV_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C1_ER_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C2_EV_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C2_ER_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) SPI1_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) SPI2_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) USART1_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) USART2_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) USART3_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) EXTI15_10_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) RTC_Alarm_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_FS_WKUP_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM8_BRK_TIM12_IRQHandler		( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM8_UP_TIM13_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM8_TRG_COM_TIM14_IRQHandler	( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM8_CC_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA1_Stream7_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) FSMC_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) SDIO_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM5_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) SPI3_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) UART4_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) UART5_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM6_DAC_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) TIM7_IRQHandler					( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream0_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream1_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream2_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream3_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream4_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN2_TX_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN2_RX0_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN2_RX1_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) CAN2_SCE_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_FS_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream5_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream6_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) DMA2_Stream7_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) USART6_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C3_EV_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) I2C3_ER_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_HS_EP1_OUT_IRQHandler		( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_HS_EP1_IN_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_HS_WKUP_IRQHandler			( void ) { while( true ); }
	void __attribute__( ( weak ) ) OTG_HS_IRQHandler				( void ) { while( true ); }
	void __attribute__( ( weak ) ) HASH_RNG_IRQHandler				( void ) { while( true ); }
}
