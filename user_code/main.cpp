#include "main.h"
#include "ayplayer.h"
#include "stm32f2xx_hal.h"

extern Wdt											wdtObj;
extern ayplayerGpio									ayplayer_gpio_struct_obj;
extern GlobalPort									ayplayer_gp_obj;
extern Uart											usart3_obj;
extern Rcc											ayplayer_rcc;
extern SpiMaster8Bit								ayplayer_spi1_obj;
extern SpiMaster8Bit								ayplayer_spi2_obj;
extern SpiMaster8Bit								ayplayer_spi3_obj;
extern AdcOneChannel								adcBatObj;
extern TimCompOneChannel							ay_clk_obj;
extern TimPwmOneChannel								lcd_pwm_obj;
extern TimInterrupt									interrupt_ay_obj;
extern run_time_logger								ay_log_obj;

extern ShiftRegister						sr_ay;
extern ShiftRegister						sr_button;
extern ButtonsThroughShiftRegisterOneInputPin		ayplayer_button;
extern ad5204< 2 >									sound_dp;
extern AyYmFileMode								ayplayer_ay_file_mode_obj;

ayplayerMcStrcut ayMcuCfg = {
	.wdt						= &wdtObj,
	.gpio						= &ayplayer_gpio_struct_obj,
	.gp							= &ayplayer_gp_obj,
	.debugUart					= &usart3_obj,
	.rcc						= &ayplayer_rcc,
	.spi1						= &ayplayer_spi1_obj,
	.spi2						= &ayplayer_spi2_obj,
	.spi3						= &ayplayer_spi3_obj,
	.adc1						= &adcBatObj,
	.ayClkTim					= &ay_clk_obj,
	.lcdPwmTim					= &lcd_pwm_obj,
	.interruptAyTim				= &interrupt_ay_obj
};

ayplayerPcbStrcut ayPcbCfg = {
	.ay							= &sr_ay,
	.srButton					= &sr_button,
	.button						= &ayplayer_button,
	.dp							= &sound_dp
};

AyPlayerCfg ayCfg = {
	.mcu						= &ayMcuCfg,
	.l							= &ay_log_obj,
	.pcb						= &ayPcbCfg,
	.ayF						= &ayplayer_ay_file_mode_obj
};

AyPlayer		ay( &ayCfg );

extern "C" {

int main ( void ) {
	ay.init();
	ay.start();
    while ( true );
}

extern void xPortSysTickHandler ( void );
void sys_tick_handler(void) {
	HAL_IncTick();
	xPortSysTickHandler();
}

}
