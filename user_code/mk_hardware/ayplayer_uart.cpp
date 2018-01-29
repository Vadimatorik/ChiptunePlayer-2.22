#include "uart.h"

#include "core_cm3.h"

const uart_cfg usart1_cfg = {
	.UARTx				= USART3,
	.baudrate			= 115200,
	.mode				= UART_MODE_TX_RX,
	.dma_tx				= nullptr,
	.dma_tx_ch			= 0
};

uart usart3_obj( &usart1_cfg );

/*!
 * Метод-прослойка вызывает метод инициализации (init)
 * глобального объекта отладочного UART-а usart3_obj
 */
void ayplayer_uart_init ( void ) {
	usart3_obj.reinit();
	NVIC_EnableIRQ( USART3_IRQn );
}

/*!
 * Обработчик прерывания принятого байта
 * (или ошибки при принятии).
 */
extern "C" void USART3_IRQHandler ( void ) {
	usart3_obj.irq_handler();
}
