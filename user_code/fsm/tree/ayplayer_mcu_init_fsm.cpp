#include "fsm.h"
#include "ayplayer.h"

extern const fsmStep< AyPlayer > ayPlayerSpiFailureHandlerFsmStep;
extern const fsmStep< AyPlayer > ayPlayerGuiInitFsmStep;
extern const fsmStep< AyPlayer > ayPlayerDpInitFsmStep;
extern const fsmStep< AyPlayer > ayPlayerFurtherActionsFsmStep;

const fsmStep< AyPlayer > AyPlayerspiFailureHandlerFsmStep = {
	.funcStep				= ayPlayer::fsmStepFuncSpiFailureHandler,
	.nextStepArray			= nullptr,
	.numberArray			= 0
};

const fsmStep< AyPlayer >* ayPlayerGuiInitFsmStepArray[ 2 ] = {
	&ayPlayerDpInitFsmStep,
	&ayPlayerSpiFailureHandlerFsmStep
};

const fsmStep< AyPlayer > AyPlayerguiInitFsmStep = {
	.funcStep				= ayPlayer::fsmStepFuncGuiInit,
	.nextStepArray			= ayPlayerGuiInitFsmStepArray,
	.numberArray			= 2
};

const fsmStep< AyPlayer >* ayPlayerDpInitFsmStepArray[ 3 ] = {
	&ayPlayerFurtherActionsFsmStep,
	nullptr,
	&ayPlayerSpiFailureHandlerFsmStep
};

const fsmStep< AyPlayer > AyPlayerdpInitFsmStep = {
	.funcStep				= ayPlayer::fsmStepFuncDpInit,
	.nextStepArray			= ayPlayerDpInitFsmStepArray,
	.numberArray			= 3
};

const fsmStep< AyPlayer > AyPlayerfurtherActionsFsmStep = {
	.funcStep				= ayPlayer::fsmStepFuncFurtherActions,
	.nextStepArray			= nullptr,
	.numberArray			= 0
};

