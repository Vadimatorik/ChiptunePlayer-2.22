#include "ayplayer_gui_win_main.h"

extern const MakiseFont F_minecraft_rus_regular_8;

MakiseStyle_PlayBar gui_pb_style = {
    .bg_color           = MC_White,
    .border_color       = MC_Black,
    .duty_color         = MC_Black,
    .time_color         = MC_Black,
    .font               = &F_minecraft_rus_regular_8
};

void ayplayer_gui_window_main_creature ( MContainer* c, MPlayBar* pl ) {
    m_create_play_bar( c,
                       pl,
                       mp_rel( 0,   57,
                               128, 7 ),
                       1,
                       &gui_pb_style );
}
