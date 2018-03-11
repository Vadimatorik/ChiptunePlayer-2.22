#include "run_time_logger.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

extern uart usart3_obj;
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

run_time_logger ay_log_obj( &log_cfg );

BASE_RESULT uart_send_message ( char* string ) {
	return usart3_obj.tx( (uint8_t*)string, strlen(string), 100 );
}
