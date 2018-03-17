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
#include "buttons_through_shift_register_one_in.h"
#include "module_digital_potentiometer_ad5204.h"
#include "microsd_card_spi.h"
#include "ay_ym_file_mode.h"

#include "makise_gui.h"
#include "makise.h"

#include <string>

#define HANDLER_FSM_STEP(NAME_STEP)				static int NAME_STEP ( const fsm_step< ay_player_class >* previous_step, ay_player_class* obj )
#define HANDLER_FSM_INPUT_DATA					const fsm_step< ay_player_class >* previous_step, ay_player_class* obj
#define TB_MAIN_TASK_SIZE				10000
#define MAIN_TASK_PRIO					2

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
	module_shift_register*						sr_ay;
	module_shift_register*						sr_button;
	buttons_through_shift_register_one_in*		button;
	ad5204< 2 >*								dp;
};

struct ay_player_class_config_strcut {
	ay_player_mc_strcut*	mcu;
	run_time_logger*		l;
	ay_player_pcb_strcut*	pcb;
	ay_ym_file_mode*		ay_f;
};

struct ay_player_class_gui_obj_strcut {
	MHost					h;
	MContainer				c;
};


class ay_player_class {
public:
	ay_player_class( ay_player_class_config_strcut* cfg ) :
		mcu			( cfg->mcu ),
		l			( cfg->l ),
		pcb			( cfg->pcb ),
		ay_f		( cfg->ay_f )
	{}

	void init			( void );
	void start			( void );

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

	HANDLER_FSM_STEP( fsm_step_func_freertos_obj_init );
	HANDLER_FSM_STEP( fsm_step_func_shift_register_init );
	HANDLER_FSM_STEP( fsm_step_func_button_init );

	static void main_task ( void* p_obj );

	HANDLER_FSM_STEP( fsm_step_func_init_gui );
	HANDLER_FSM_STEP( fsm_step_func_fat_init );
	HANDLER_FSM_STEP( fsm_step_func_sd1_check );
	HANDLER_FSM_STEP( fsm_step_func_check_playlist_sys );
	HANDLER_FSM_STEP( fsm_step_func_create_playlist_sys );

	//
	//
	//
	//
	//HANDLER_FSM_STEP( );
	//HANDLER_FSM_STEP( );
	//HANDLER_FSM_STEP( );
	//HANDLER_FSM_STEP( );
	//HANDLER_FSM_STEP( );
	//


	HANDLER_FSM_STEP( fsm_step_func_gui_fall );
	HANDLER_FSM_STEP( fsm_step_func_logger_fall );
	HANDLER_FSM_STEP( fsm_step_func_fat_fall );
	HANDLER_FSM_STEP( fsm_step_func_sd1_fall );
	///


private:
	/// Текущий режим работы RCC.
	uint32_t						rcc_index = 0;

	fsm_class< ay_player_class >	fsm;

	ay_player_mc_strcut*			mcu;
	run_time_logger*				l;
	ay_player_pcb_strcut*			pcb;
	ay_ym_file_mode*				ay_f;

	ay_player_class_gui_obj_strcut	g;

	USER_OS_STATIC_STACK_TYPE				tb_main_task[ TB_MAIN_TASK_SIZE ];
	USER_OS_STATIC_TASK_STRUCT_TYPE			ts_main_task;

	FATFS							f;
	FILINFO							sd1_fi;
	DIR								sd1_fdir;
};
