#include "uart.h"


const uart_cfg usart3_cfg = {
	.UARTx				= USART3,
	.baudrate			= 115200,
	.mode				= UART_MODE_TX_RX,

	/// Нет доступных каналов для этого UART-а.
	.dma_tx				= nullptr,
	.dma_tx_ch			= 0,
	.handler_prio		= 0					/// Приоритет только для DMA.
};

uart usart3_obj( &usart3_cfg );

/*!
 * Обработчик прерывания принятого байта
 * (или ошибки при принятии).
 */
extern "C" void usart3_handler ( void ) {
	usart3_obj.irq_handler();
}
