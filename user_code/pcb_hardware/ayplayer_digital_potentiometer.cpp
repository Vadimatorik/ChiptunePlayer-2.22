#include "module_digital_potentiometer_ad5204.h"
#include "pin.h"
#include "spi.h"
#include "ayplayer_os_object.h"

extern Pin dpCs;
extern Pin shdn;

extern freeRtosObj						osData;
extern SpiMaster8Bit					spi3;

#define AD5204_CHIP_COUNT				2

static uint8_t				ad5204Buffer[ AD5204_BUF_SIZE( AD5204_CHIP_COUNT ) ];
static ad5204chipData		ad5204StructBuffer[ AD5204_CHIP_COUNT ];

ad5204Cfg soundDpCfg = {
	.spi				=	&spi3,
	.mutex				=	&osData.mSpi3,
	.cs					=	&dpCs,
	.shdn				=	&shdn,
	.countChip			=	AD5204_CHIP_COUNT,
	.bufOutput			=	ad5204Buffer,
	.arraySize			=	AD5204_BUF_SIZE( AD5204_CHIP_COUNT ),
	.internalStructData	=	ad5204StructBuffer
};

ad5204		soundDp( &soundDpCfg );
