#include "module_digital_potentiometer_ad5204.h"
#include "pin.h"
#include "spi.h"
#include "ayplayer_os_object.h"

extern Pin ayplayer_dp_cs_pin_obj;
extern Pin ayplayer_shdn_pin_obj;

extern ay_player_freertos_obj_strcut	os_data;
extern SpiMaster8Bit					ayplayer_spi3_obj;

ad5204_struct_cfg_t sound_dp_cfg = {
    .spi        = &ayplayer_spi3_obj,
	.mutex      = &os_data.m_spi3,
    .cs         = &ayplayer_dp_cs_pin_obj,
    .shdn       = &ayplayer_shdn_pin_obj
};

ad5204< 2 > sound_dp( &sound_dp_cfg );
