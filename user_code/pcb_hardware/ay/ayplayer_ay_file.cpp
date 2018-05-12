#include "ay_ym_file_mode.h"
#include "ay_ym_low_lavel.h"
#include "user_os.h"
#include "pin.h"

extern AyYmLowLavel						ayLow;
extern Pin								chip1PwrOn;
extern Pin								chip2PwrOn;

/*!
 * Метод позволяет отключать неиспользуемый в данный момент AY/YM чип
 * для экономии энергии.
 */
void pwrChipOn ( uint32_t chip, bool state ) {
	switch ( chip ) {
	case 0: chip2PwrOn.set( state ); break;
	case 1: chip1PwrOn.set( state ); break;
	}
}

ayYmFileModeCfg ayFileModeCfg = {
	.ay							= &ayLow,
	.pwrChipOn					= pwrChipOn
};

AyYmFileMode ayFileMode(&ayFileModeCfg);

