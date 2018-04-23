#pragma once

#include "fsm.h"
#include "wdt.h"
#include "uart.h"
#include "rcc.h"
#include "spi.h"
#include "adc.h"
#include "timer.h"

#include "run_time_logger.h"
#include "module_digital_potentiometer_ad5204.h"
#include "microsd_card_spi.h"
#include "makise_gui.h"
#include "makise.h"

#include <string>

#include "ay_ym_file_mode.h"
#include "buttons_through_shift_register_one_input_pin.h"
#include "ayplayer_gpio.h"
#include "shift_register.h"
#include "ayplayer_os_object.h"

/*!
 * Количество режимов тактирования контроллера.
 */
#define	AYPLAYER_RCC_CFG_COUNT					4



#define HANDLER_FSM_STEP(NAME_STEP)				static int NAME_STEP ( const fsmStep< AyPlayer >* previousStep, AyPlayer* obj )
#define HANDLER_FSM_INPUT_DATA					__attribute__((unused)) const fsmStep< AyPlayer >* previousStep, AyPlayer* obj
#define TB_MAIN_TASK_SIZE						3000
#define MAIN_TASK_PRIO							2

struct ayplayerMcStrcut {
	WdtBase*						wdt;
	ayplayerGpio*					gpio;
	GlobalPortBase*					gp;
	UartBase*						debugUart;
	RccBase*						rcc;
	SpiMaster8BitBase*				spi1;
	SpiMaster8BitBase*				spi2;
	SpiMaster8BitBase*				spi3;
	AdcOneChannelBase*				adc1;
	TimCompOneChannelBase*			ayClkTim;
	TimPwmOneChannelBase*			lcdPwmTim;
	TimInterruptBase*				interruptAyTim;

#ifdef configGENERATE_RUN_TIME_STATS
	TimCounter*						timRunTimeStats;
#endif
};

struct ayplayerPcbStrcut {
	ShiftRegister*										ay;
	ShiftRegister*										srButton;
	ButtonsThroughShiftRegisterOneInputPin*				button;
	ad5204< 2 >*										dp;
};

struct AyPlayerCfg {
	ayplayerMcStrcut*		mcu;
	run_time_logger*		l;
	ayplayerPcbStrcut*		pcb;
	AyYmFileMode*			ayF;
	freeRtosObj*			os;
};

struct ayPlayerGuiCfg {
	MHost					h;
	MContainer				c;
};


class AyPlayer {
public:
	AyPlayer( AyPlayerCfg* cfg ) :
		mcu			( cfg->mcu ),
		l			( cfg->l ),
		pcb			( cfg->pcb ),
		ayFile		( cfg->ayF ),
		os			( cfg->os )
	{}

	void start			( void );

	HANDLER_FSM_STEP( fsmStepFuncHardwareMcInit );
	HANDLER_FSM_STEP( fsmStepFuncFreeRtosObjInit );

	/*
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
	HANDLER_FSM_STEP( fsm_step_func_button_init );*/

	static void mainTask ( void* obj );

	/*
	HANDLER_FSM_STEP( fsm_step_func_init_gui );
	HANDLER_FSM_STEP( fsm_step_func_fat_init );
	HANDLER_FSM_STEP( fsm_step_func_sd1_check );
	HANDLER_FSM_STEP( fsm_step_func_check_playlist_sys );
	HANDLER_FSM_STEP( fsm_step_func_create_playlist_sys );*/

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


	//HANDLER_FSM_STEP( fsm_step_func_gui_fall );
	//HANDLER_FSM_STEP( fsm_step_func_logger_fall );
//	HANDLER_FSM_STEP( fsm_step_func_fat_fall );
	//HANDLER_FSM_STEP( fsm_step_func_sd1_fall );
	///


private:
	/*!
	 * Останавливает все аппаратные модули, зависящие от тактового сигнала,
	 * пытается установить заданную тактовую частоту на шинах, после чего
	 * конфигурирует заново все объекты, зависящие от частоты тактового сигнала
	 * ( вызывается метод reinitObjDependingRcc ).
	 *
	 * Замечание: в случае, если не удалось настроить заданную конфигурацию - микроконтроллер переходит
	 * в режим работы по умолчанию.
	 */
	RCC_RESULT		setRccCfg							( uint32_t numberCfg );

	/*!
	 * Отключает все объекты, зависящие
	 * от частоты тактового сигнала.
	 */
	void			offObjDependingRcc					( void );

	/*!
	 * Метод переконфигурирует все объекты, зависящие
	 * от частоты тактового сигнала.
	 */
	void			reinitObjDependingRcc				( void );

	/// Текущий режим работы RCC.
	uint32_t											rccIndex = 0;

	fsmClass< AyPlayer >								fsm;

	ayplayerMcStrcut*									const mcu;
	run_time_logger*									const l;
	ayplayerPcbStrcut*									const pcb;
	AyYmFileMode*										const ayFile;
	freeRtosObj*										const os;
	ayPlayerGuiCfg										g;

	USER_OS_STATIC_STACK_TYPE				tbMainask[ TB_MAIN_TASK_SIZE ];
	USER_OS_STATIC_TASK_STRUCT_TYPE			tsMainTask;

	FATFS							f;
	FILINFO							sd1_fi;
	DIR								sd1_fdir;
};
