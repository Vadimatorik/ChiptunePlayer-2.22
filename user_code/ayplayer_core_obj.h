#pragma once

#include <stdint.h>
#include "arithmetic_mean.h"
#include "ayplayer_digital_potentiometer.h"
#include "makise_gui.h"
#include "ayplayer_fat_love_level.h"

enum class EC_AY_PLAY_STATE {
	STOP		= 0,
	PLAY		= 1,
	POUSE	   = 2
};

enum class EC_AY_ACTIVE_WINDOW {
	MAIN				= 0,				// Окно с текущим треком.
	PLAY_LIST,							  // Список треков на карте.
	SYSTEM								  // Системное окно с предупреждениями.
};

enum class EC_AY_STATE {
	INIT = 0,
	RUN = 1,
};

struct dp_low_value_t {
	uint8_t	 a;
	uint8_t	 b;
	uint8_t	 c;
	uint8_t	 a1;
	uint8_t	 b1;
	uint8_t	 c1;
	uint8_t	 left;
	uint8_t	 right;
};

// Структура агрегатор всех изменяемых пользовательских полей.
struct ayplayer_global_data_struct {
	MHost					m_host;
	MContainer				m_cont;
	FATFS					fat;
	FIL						file_list;
	dp_low_value_t			dp = {
		.a	  	= 0xFF,
		.b	  	= 0xFF,
		.c	  	= 0x80,
		.a1	 	= 0xFF,
		.b1	 	= 0x80,
		.c1	 	= 0xFF,
		.left   = 0x80,
		.right  = 0x80
	};
};



class ayplayer_state {
public:
	ayplayer_state ( void ) {}
	void play_state_set ( EC_AY_PLAY_STATE state );
	EC_AY_PLAY_STATE play_state_get ( void );			   // 0 - stop, 1 -play 2 - pause,

	void active_window_set ( EC_AY_ACTIVE_WINDOW win );
	EC_AY_ACTIVE_WINDOW active_window_get ( void );

	void battery_voltage_set ( float battery_voltage );
	float battery_voltage_get ( void );

	EC_AD5204_ANSWER dp_update_value ( void );

	EC_AY_STATE stait_get ( void );
	void stait_set ( EC_AY_STATE stait );
private:
	EC_AY_PLAY_STATE		play_state		  = EC_AY_PLAY_STATE::STOP;
	EC_AY_ACTIVE_WINDOW	 active_window	   = EC_AY_ACTIVE_WINDOW::SYSTEM;
	EC_AY_STATE			 stait			   = EC_AY_STATE::INIT;
	dp_low_value_t		  dp_low			  = {

	};
	arithmetic_mean		 battery_voltage;
};

extern ayplayer_state ayplayer_control;
