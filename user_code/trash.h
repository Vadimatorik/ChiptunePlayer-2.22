/*
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while(1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
	  while(1);
  }


  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
*/


/*
#include "stm32f2xx_hal_conf.h"
#include "stm32f2xx_hal.h"
	SD_HandleTypeDef uSdHandle;

	 uint8_t wtext[1024] = "This is STM32 working with FatFs";


	  HAL_Init();

	  SystemClock_Config();


		  uSdHandle.Instance = SDIO;

		  uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
		  uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
		  uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
		  uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
		  uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
		  uSdHandle.Init.ClockDiv            = 0xFF;



		  __HAL_RCC_SDIO_CLK_ENABLE();
		  GPIO_InitTypeDef GPIO_Init_Structure;


		 // ayplayer_gp_obj.reinit_all_ports();
		  __HAL_RCC_GPIOC_CLK_ENABLE();
		  __HAL_RCC_GPIOD_CLK_ENABLE();



		  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
		  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
		  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
		  GPIO_Init_Structure.Alternate = GPIO_AF12_SDIO;


		  GPIO_Init_Structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;

		  HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);


		  GPIO_Init_Structure.Pin = GPIO_PIN_2;
		  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);




		  if(HAL_SD_Init(&uSdHandle) != HAL_OK)
		  {
		    while(1);
		  }



		    if(HAL_SD_ConfigWideBusOperation(&uSdHandle, SDIO_BUS_WIDE_4B) != HAL_OK)
		    {
		    while(1);
		    }


		  uint32_t timeout = 100000;

		  if(HAL_SD_WriteBlocks(&uSdHandle,(uint8_t*)wtext,
		                       0,
		                       1, 100000) == HAL_OK )
		  {
		    while(HAL_SD_GetCardState(&uSdHandle)!= HAL_SD_CARD_TRANSFER)
		    {
		      if (timeout-- == 0)
		      {
		        while(1);
		      }
		    }
		  }

		  while (1)
		  {
		  }
*/

/*


void sys_tick_handler ( void ) {
	//
	HAL_IncTick();
}

}*/



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
