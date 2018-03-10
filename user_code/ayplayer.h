#pragma once

#include "fsm.h"
#include "wdt.h"
#include "uart.h"
#include "rcc.h"
#include "spi.h"
#include "ayplayer_port.h"

#define HANDLER_FSM_STEP(NAME_STEP)				static int NAME_STEP ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj )


struct ay_player_mc_strcut {
	wdt_base*				wdt;
	ayplayer_gpio_struct*	gpio;
	global_port_base*		gp;
	uart_base*				debug_uart;
	rcc_base*				rcc;
	spi_master_8bit_base*	spi1;
	spi_master_8bit_base*	spi2;
	spi_master_8bit_base*	spi3;
};

struct ay_player_class_config_strcut {
	ay_player_mc_strcut*	mcu;
};

class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) :
		mcu			( cfg->mcu )
	{}

	void init ( void );

	HANDLER_FSM_STEP( fsm_step_func_wdt_init );
	HANDLER_FSM_STEP( fsm_step_func_gpio_init );
	HANDLER_FSM_STEP( fsm_step_func_rcc_init );
	HANDLER_FSM_STEP( fsm_step_func_debug_uart_init );
	HANDLER_FSM_STEP( fsm_step_func_nvic_init );
	HANDLER_FSM_STEP( fsm_step_func_rcc_falling );
	HANDLER_FSM_STEP( fsm_step_func_spi_init );
	HANDLER_FSM_STEP( fsm_step_func_spi_falling );

private:
	fsm_class< ay_player_class >	fsm_init;

	ay_player_mc_strcut*			mcu;
};
