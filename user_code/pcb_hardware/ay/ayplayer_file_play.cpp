#include "ayplayer_ay_file_class.h"
#include "ay_ym_low_lavel.h"

extern AyYmLowLavel		ayLow;
extern Pin				pwrAy[ 2 ];

AyYmFilePlay		ayYmFilePlay( pwrAy, &ayLow );
