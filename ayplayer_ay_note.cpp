#include "ayplayer_ay_note.h"

const ay_ym_note_cfg_t ayplayer_note_mode_cfg = {
    .array_chip = &ay
};

ay_ym_note ayplayer_note_mode( &ayplayer_note_mode_cfg );
