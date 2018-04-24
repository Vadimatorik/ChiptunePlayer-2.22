#include "uart.h"
#include <stdio.h>
#include <string.h>

#include "../module_run_time_logger/run_time_logger.h"

extern Uart usart3;
BASE_RESULT uart_send_message ( char* string );

const run_time_logger_cfg log_cfg = {
	.color = {
		.init_ok_color_string			= ANSI_RESET,
		.init_issue_color_string		= ANSI_YEL,
		.init_error_color_string		= ANSI_RED,
		.run_message_ok_color_string	= ANSI_RESET,
		.run_message_issue_color_string	= ANSI_YEL,
		.run_message_error_color_string	= ANSI_RED
	},
	.out_buffer = uart_send_message
};

RunTimeLogger ayLog( &log_cfg );

BASE_RESULT uart_send_message ( char* string ) {
	return usart3.tx( (uint8_t*)string, strlen(string), 100 );
}
