#pragma once

#include "ay_ym_file_play.h"
#include "ay_ym_low_lavel.h"
#include "ayplayer_fat.h"
#include "pin.h"

class AyYmFilePlay : public AyYmFilePlayBase {
public:
	AyYmFilePlay( Pin* pwrPinArray, AyYmLowLavel* ayLow ) :
		 pwrPin(pwrPinArray), ayLow( ayLow ) {}

	void	setPlaySd					(	AY_MICROSD	sd	);
	void	setUsingChip				(	uint32_t	chipNumber	);
	void	setPlayFileName				(	const char* fileName	);

	void	setPause					(	bool	state	);
	void	stop						(	void	);

private:
	int	openFile						(	void	);
	int	closeFile						(	void	);
	int	getFileLen						(	uint32_t&		returnFileLenByte	);
	int	setOffsetByteInFile				(	const uint32_t	offsetByte	);
	int	readInArray						(	uint8_t*		returnDataBuffer,
											const uint32_t	countByteRead	);
	int	setPwrChip						(	bool			state	);
	int	initChip						(	void	);
	int	sleepChip						(	const uint32_t	countTick	);
	int	writePacket						(	const uint8_t	reg,
											const uint8_t	data	);

	void	abort						(	void	);

	Pin*					pwrPin;
	AyYmLowLavel*			ayLow;
	AY_MICROSD				sd;
	const char*				fileName			=	nullptr;
	FIL*					f					=	nullptr;
	uint32_t				usingChip;
	bool					flagStop;
};
