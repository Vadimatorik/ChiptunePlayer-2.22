#include "uart.h"
#include <stdio.h>
#include <string.h>

#include "run_time_logger.h"

extern Uart usart3;

BASE_RESULT		uartSendMessage ( const char* string );

const runTimeLoggerCfg log_cfg = {
	.color = {
		.initOkColorString			= ANSI_RESET,
		.initIssueColorString		= ANSI_YEL,
		.initErrorColorString		= ANSI_RED,
		.runMessageOkColorString	= ANSI_RESET,
		.runMessageIssueColorString	= ANSI_YEL,
		.runMessageErrorColorString	= ANSI_RED
	},
	.outBuffer = uartSendMessage
};

RunTimeLogger ayLog( &log_cfg );

BASE_RESULT uartSendMessage ( const char* string ) {
	return usart3.tx( (uint8_t*)string, strlen(string), 100 );
}
