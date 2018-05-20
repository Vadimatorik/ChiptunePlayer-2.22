#include "shift_register.h"
#include "spi.h"
#include "pin.h"
#include "user_os.h"

extern SpiMaster8Bit	spi3;
extern Pin				spiAudioStReg;

// sr_out_buf[0] - 40-ми ногая.
// sr_out_buf[1] - 28-ка ногая.
uint8_t sr_out_buf_ay[2]			=	{ 0 };			// Для AY.
uint8_t srOutBufButton[1]			=	{ 0 };				// Для кнопок.

const ShiftRegisterCfg srAyCfg = {
	.st						=	&spiAudioStReg,
	.dataArray				=	sr_out_buf_ay,
	.arraySize				=	M_SIZE_ARRAY( sr_out_buf_ay ),
	.strobActive			=	true,
	.spiObj					=	&spi3,
	.mutex					=	nullptr
};

ShiftRegister	srAy( &srAyCfg );

const ShiftRegisterCfg srButtonCfg = {
	.st						=	&spiAudioStReg,
	.dataArray				=	srOutBufButton,
	.arraySize				=	M_SIZE_ARRAY( srOutBufButton ),
	.strobActive			=	true,
	.spiObj					=	&spi3,
	.mutex					=	nullptr
};

ShiftRegister	srButton( &srButtonCfg );
