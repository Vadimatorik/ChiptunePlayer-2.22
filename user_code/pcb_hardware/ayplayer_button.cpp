#include "ayplayer_button.h"

#include "buttons_through_shift_register_one_input_pin.h"
#include "user_os.h"
#include "ayplayer_os_object.h"
#include "pin.h"

extern freeRtosObj						osData;
extern Pin								buttonIn;
extern ShiftRegister					srButton;
extern uint8_t							srOutBufButton[ 1 ];

srOneInButtonStatusStruct				bSAr[ 7 ];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg buttonChannelcfg[ 7 ] = {
	{
		.byte				=	0,
		.bit				=	0,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::UP_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::UP_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::UP_CLICK ),
		.status				=	&bSAr[0]
	},
	{
		.byte				=	0,
		.bit				=	1,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::DOWN_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::DOWN_LONG_CLICK),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::DOWN_CLICK ),
		.status				=	&bSAr[1]
	},
	{
		.byte				=	0,
		.bit				=	2,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK ),
		.status				=	&bSAr[2]
	},
	{
		.byte				=	0,
		.bit				=	3,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK ),
		.status				=	&bSAr[3]
	},
	{
		.byte				=	0,
		.bit				=	4,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::ENTER_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::ENTER_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::ENTER_CLICK ),
		.status				=	&bSAr[4]
	},
	{
		.byte				=	0,
		.bit				=	6,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::BACK_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::BACK_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::BACK_CLICK ),
		.status				=	&bSAr[5]
	},
	{
		.byte				=	0,
		.bit				=	5,
		.stabildDelayMs		=	50,
		.delayMsLongPress	=	700,
		.sPress				=	nullptr,
		.qPress				=	nullptr,
		.vPress				=	0,
		.sStartLongPress	=	nullptr,
		.qStartLongPress	=	&osData.qAyButton,
		.vStartLongPress	=	M_EC_TO_U8( EC_BUTTON_NAME::MENU_LONG_PRESS ),
		.sReleaseLongClick	=	nullptr,
		.qReleaseLongClick	=	&osData.qAyButton,
		.vReleaseLongClick	=	M_EC_TO_U8( EC_BUTTON_NAME::MENU_LONG_CLICK ),
		.sReleaseClick		=	nullptr,
		.qReleaseClick		=	&osData.qAyButton,
		.vReleaseClick		=	M_EC_TO_U8( EC_BUTTON_NAME::MENU_CLICK ),
		.status				=	&bSAr[6]
	},
};

ButtonsThroughShiftRegisterOneInputPinCfg buttonCfg = {
	.pinInObj					=	&buttonIn,
	.srObj						=	&srButton,
	.pinCfgArray				=	buttonChannelcfg,
	.pinCount					=	7,
	.delayMs					=	10,
	.prio						=	1,
	.pointingButtonArray		=	srOutBufButton,
	.srBufferByteCount			=	1,
	.mutex						=	&osData.mSpi3
};

ButtonsThroughShiftRegisterOneInputPin button( &buttonCfg );
