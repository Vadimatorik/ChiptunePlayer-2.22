#include "main.h"
#include "ayplayer.h"

extern wdt											ayplayer_wdt_obj;
extern ayplayer_gpio_struct							ayplayer_gpio_struct_obj;
extern global_port									ayplayer_gp_obj;
extern uart											usart3_obj;
extern rcc											ayplayer_rcc;
extern spi_master_8bit								ayplayer_spi1_obj;
extern spi_master_8bit								ayplayer_spi2_obj;
extern spi_master_8bit								ayplayer_spi3_obj;
extern adc_one_channel								adc_bat_obj;
extern tim_comp_one_channel							ay_clk_obj;
extern tim_pwm_one_channel							lcd_pwm_obj;
extern tim_interrupt								interrupt_ay_obj;
extern run_time_logger								ay_log_obj;

extern module_shift_register						sr_ay;
extern module_shift_register						sr_button;
extern buttons_through_shift_register_one_in		ayplayer_button;
extern ad5204< 2 >									sound_dp;
extern microsd_spi									ayplayer_sd2_obj;
extern ay_ym_file_mode								ayplayer_ay_file_mode_obj;

ay_player_mc_strcut ay_mcu = {
	.wdt						= &ayplayer_wdt_obj,
	.gpio						= &ayplayer_gpio_struct_obj,
	.gp							= &ayplayer_gp_obj,
	.debug_uart					= &usart3_obj,
	.rcc						= &ayplayer_rcc,
	.spi1						= &ayplayer_spi1_obj,
	.spi2						= &ayplayer_spi2_obj,
	.spi3						= &ayplayer_spi3_obj,
	.adc1						= &adc_bat_obj,
	.ay_clk						= &ay_clk_obj,
	.lcd_pwm					= &lcd_pwm_obj,
	.interrupt_ay				= &interrupt_ay_obj
};

ay_player_pcb_strcut ay_pcb = {
	.sr_ay						= &sr_ay,
	.sr_button					= &sr_button,
	.button						= &ayplayer_button,
	.dp							= &sound_dp,
	.sd2						= &ayplayer_sd2_obj
};

ay_player_class_config_strcut ay_cfg = {
	.mcu						= &ay_mcu,
	.l							= &ay_log_obj,
	.pcb						= &ay_pcb,
	.ay_f						= &ayplayer_ay_file_mode_obj
};

ay_player_class		ay( &ay_cfg );

extern "C" {

int main ( void ) {
	ay.init();
	ay.start();
    while ( true );
}

}

/*

EC_AD5204_ANSWER dp_update_value ( void ) {
	EC_AD5204_ANSWER    r;
	r = sound_dp.value_set( 0, 0, g.dp.b );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 1, g.dp.c );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 2, g.dp.a );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 0, 3, g.dp.a1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 0, g.dp.b1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 1, g.dp.c1 );
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 2, g.dp.left);
	if ( r != EC_AD5204_ANSWER::OK ) return r;
	r = sound_dp.value_set( 1, 3, g.dp.right );
	return r;
}

#include "ayplayer_port.h"
#include "ayplayer_os_object.h"
#include "ayplayer_shift_register.h"

void ayplayer_button_init ( void );

#define INC_AND_DEC_STABIL_TIME  			    	100
#define OFF_WAIT_TIME             				   	3000
#define PERIOD_DETECT_PRESS_BUTTON_INC_DEC			10


int32_t current_volume = 4;

#include "ayplayer_digital_potentiometer.h"

uint8_t v_table[16] = { 0x0, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xFF };

static void device_power_off ( void ) {								// Отключает всю цепь питания устройства.
	ayplayer_pwr_on_pin_obj.reset();
}

static void volume_set( uint8_t left, uint8_t right) {
	sound_dp.value_set( 1, 2, left );						// Левый наушник.
	sound_dp.value_set( 1, 3, right );						// Правый.
}

// Детектирование изменения уровня громкости.
void ayplayer_button_inc_and_dec_detect ( void* param ) {
	( void )param;

	int32_t inc_stabil_time = INC_AND_DEC_STABIL_TIME;
	int32_t dec_stabil_time = INC_AND_DEC_STABIL_TIME;
	int32_t off_time = OFF_WAIT_TIME;

	bool inc_f = false;
	bool dec_f = false;

	while ( true ) {
		USER_OS_DELAY_MS( PERIOD_DETECT_PRESS_BUTTON_INC_DEC );

		inc_f = ayplayer_button_inc_pin_obj.read();
		dec_f = ayplayer_button_dec_pin_obj.read();

		// Обе зажатые клавиши - старт отсчета времени нажатия для отключения.
		if ( ( inc_f == false ) && ( dec_f == false ) ) {
			if ( off_time > 0 ) {
				off_time -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
			} else {
				device_power_off();
			}
		} else {
			off_time = OFF_WAIT_TIME;
		}

		if ( inc_f == false ) {
			if ( inc_stabil_time > 0 ) inc_stabil_time -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
		} else {
			if ( inc_stabil_time == 0 ) {
				if ( current_volume < 15 )	current_volume++;
				inc_stabil_time = INC_AND_DEC_STABIL_TIME;
				volume_set( v_table[ current_volume ], v_table[ current_volume ] );
				continue;
			}
		}

		if ( dec_f == false ) {
			if ( dec_stabil_time > 0 ) dec_stabil_time -= PERIOD_DETECT_PRESS_BUTTON_INC_DEC;
		} else {
			if ( dec_stabil_time == 0 ) {
				if ( current_volume > 0 )	current_volume--;
				dec_stabil_time = INC_AND_DEC_STABIL_TIME;
				volume_set( v_table[ current_volume ], v_table[ current_volume ] );
				continue;
			}
		}
	}
}

void ayplayer_button_init ( void ) {
	&os_data.q_ay_button_init();
	//ayplayer_button.init();
	USER_OS_STATIC_TASK_CREATE( ayplayer_button_inc_and_dec_detect, "b_incdec", TB_B_INC_DEC_SIZE,  NULL, 2, tb_inc_dec_detect, &ts_inc_dec_detect );



/// Перерисовывает GUI и обновляет экран.
void gui_update ( void ) {
	USER_OS_TAKE_MUTEX( os_data.m_host, portMAX_DELAY );
	ayplayer_lcd_obj.buf_clear();
	makise_g_host_call( &os_data.m_host, M_G_CALL_PREDRAW );
	makise_g_host_call( &os_data.m_host, M_G_CALL_DRAW );
	m_gui_update( os_data.m_host.host->gui );
	USER_OS_GIVE_BIN_SEMAPHORE( os_data.s_gui_update );
	USER_OS_GIVE_MUTEX( os_data.m_host );
}


}*/
