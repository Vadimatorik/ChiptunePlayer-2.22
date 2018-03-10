#pragma once

#include "fsm.h"
#include "wdt.h"
#include "uart.h"
#include "rcc.h"
#include "spi.h"
#include "adc.h"
#include "timer.h"

#include "ayplayer_port.h"
#include "run_time_logger.h"
#include "module_shift_register.h"

#define HANDLER_FSM_STEP(NAME_STEP)				static int NAME_STEP ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj )

struct ay_player_mc_strcut {
	wdt_base*						wdt;
	ayplayer_gpio_struct*			gpio;
	global_port_base*				gp;
	uart_base*						debug_uart;
	rcc_base*						rcc;
	spi_master_8bit_base*			spi1;
	spi_master_8bit_base*			spi2;
	spi_master_8bit_base*			spi3;
	adc_one_channel_base*			adc1;
	tim_comp_one_channel_base*		ay_clk;
	tim_pwm_one_channel_base*		lcd_pwm;
	tim_interrupt_base*				interrupt_ay;
};

struct ay_player_pcb_strcut {
	module_shift_register*			sr_ay;
	module_shift_register*			sr_button;
};

struct ay_player_class_config_strcut {
	ay_player_mc_strcut*	mcu;
	run_time_logger*		l;
	ay_player_pcb_strcut*	pcb;
};

class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) :
		mcu			( cfg->mcu ),
		l			( cfg->l ),
		pcb			( cfg->pcb )
	{}

	void init ( void );

	HANDLER_FSM_STEP( fsm_step_func_wdt_init );
	HANDLER_FSM_STEP( fsm_step_func_gpio_init );
	HANDLER_FSM_STEP( fsm_step_func_rcc_init );
	HANDLER_FSM_STEP( fsm_step_func_debug_uart_init );
	HANDLER_FSM_STEP( fsm_step_func_nvic_init );	
	HANDLER_FSM_STEP( fsm_step_func_spi_init );	
	HANDLER_FSM_STEP( fsm_step_func_adc_init );
	HANDLER_FSM_STEP( fsm_step_func_timer_init );

	HANDLER_FSM_STEP( fsm_step_func_rcc_falling );
	HANDLER_FSM_STEP( fsm_step_func_spi_falling );
	HANDLER_FSM_STEP( fsm_step_func_debug_uart_falling );
	HANDLER_FSM_STEP( fsm_step_func_adc_falling );
	HANDLER_FSM_STEP( fsm_step_func_timer_falling );

	HANDLER_FSM_STEP( fsm_step_func_shift_register_init );

private:
	/// Текущий режим работы RCC.
	uint32_t						rcc_index = 0;

	fsm_class< ay_player_class >	fsm;

	ay_player_mc_strcut*			mcu;
	run_time_logger*				l;
	ay_player_pcb_strcut*			pcb;
};
