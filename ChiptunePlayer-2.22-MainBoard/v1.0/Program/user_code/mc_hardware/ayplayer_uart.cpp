#include "uart.h"

const uartCfg usart3_cfg = {
	.uart				= USART3,
	.baudrate			= 115200,
	.mode				= UART_MODE_TX_RX,

	/// Нет доступных каналов для этого UART-а.
	.dmaTx				= nullptr,
	.dmaTxCh			= 0,
};

Uart usart3( &usart3_cfg, 1 );
