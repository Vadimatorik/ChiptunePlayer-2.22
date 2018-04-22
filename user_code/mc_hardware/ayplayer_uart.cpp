#include "uart.h"


const uartCfg usart3_cfg = {
	.uart				= USART3,
	.baudrate			= 115200,
	.mode				= UART_MODE_TX_RX,

	/// Нет доступных каналов для этого UART-а.
	.dmaTx				= nullptr,
	.dmaTxCh			= 0,
};

Uart usart3_obj( &usart3_cfg, 1 );

/*!
 * Обработчик прерывания принятого байта
 * (или ошибки при принятии).
 */
extern "C" void usart3_handler ( void ) {
	usart3_obj.irqHandler();
}
