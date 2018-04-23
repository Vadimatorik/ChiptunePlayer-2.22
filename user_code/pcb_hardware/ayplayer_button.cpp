#include "ayplayer_button.h"

#include "buttons_through_shift_register_one_input_pin.h"
#include "user_os.h"
#include "ayplayer_os_object.h"
#include "pin.h"

extern freeRtosObj						osData;
extern Pin								buttonIn;
extern ShiftRegister					srButton;
extern uint8_t							srOutBufButton[1];

srOneInButtonStatusStruct				bSAr[ 7 ];

// При опуске коротком или длинном - одна и та же очередь.
sr_one_in_button_item_cfg buttonChannelcfg[ 7 ] = {
	{ 0, 0, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,												nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::UP ),					nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::UP ),				&bSAr[0] },
	{ 0, 1, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,												nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::DOWN ),					nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::DOWN),				&bSAr[1] },
	{ 0, 2, 50, 700, nullptr, nullptr, 0, nullptr, &osData.qAyButton,		M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_PRESS ),	nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_LONG_CLICK ),		nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::LEFT_CLICK),		&bSAr[2] },
	{ 0, 3, 50, 700, nullptr, nullptr, 0, nullptr, &osData.qAyButton,		M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_PRESS ), nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_LONG_CLICK ),		nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::RIGHT_CLICK),		&bSAr[3] },
	{ 0, 4, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,												nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::ENTER ),				nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::ENTER),				&bSAr[4] },
	{ 0, 6, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,												nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::BACK ),					nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::BACK),				&bSAr[5] },
	{ 0, 5, 50, 700, nullptr, nullptr, 0, nullptr, nullptr,					0,												nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::MENU ),					nullptr, &osData.qAyButton, M_EC_TO_U8( EC_BUTTON_NAME::MENU),				&bSAr[6] },
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
