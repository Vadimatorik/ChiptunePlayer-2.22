#include "ayplayer_gui_win_error.h"

extern const MakiseFont F_minecraft_rus_regular_8;

MakiseStyle_SMessageWindow smw = {
    .font               = &F_minecraft_rus_regular_8,
    .font_line_spacing  = 2,

    .bg_color           = MC_White,
    .font_col           = MC_Black,
    .border_color       = MC_Black,
};

void ayplayer_error_string_draw ( MContainer* c, const char* s ) {
    makise_g_cont_clear( c );
    MMessageWindow mw;
    m_create_message_window( &mw, c, mp_rel( 9, 10, 108, 44 ), (char*)s, &smw );
    gui_update();
}
