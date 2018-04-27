#include "pwr.h"

pwrCfg ayPwrCfg = {
	.cfg = {
		/// Min: 2.65; Typ: 2.84; Max: 3.02
		.PVDLevel		=	PWR_PVDLEVEL_5,
		.Mode			=	PWR_PVD_MODE_IT_RISING
	}
};

Pwr	pwr( &ayPwrCfg, 1 );
