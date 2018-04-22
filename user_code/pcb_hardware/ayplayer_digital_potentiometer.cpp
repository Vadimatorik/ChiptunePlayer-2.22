#include "module_digital_potentiometer_ad5204.h"
#include "pin.h"
#include "spi.h"
#include "ayplayer_os_object.h"

extern Pin dpCs;
extern Pin shdn;

extern ayplayerFreertosObjStrcut		osData;
extern SpiMaster8Bit					spi3;

ad5204_struct_cfg_t soundDpCfg = {
	.spi		=	&spi3,
	.mutex		=	&osData.m_spi3,
	.cs			=	&dpCs,
	.shdn		=	&shdn
};

ad5204< 2 > soundDp( &soundDpCfg );
