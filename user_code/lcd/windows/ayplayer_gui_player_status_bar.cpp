#include "ayplayer_gui_player_status_bar.h"

extern const MakiseFont F_minecraft_rus_regular_8;

uint32_t ayplayer_get_state_play        ( void );
uint32_t ayplayer_get_percent_battery   ( void );

MakiseStyle_SMPlayerStatusBar psb_s = {
    .font_ercent            = &F_minecraft_rus_regular_8,
    .font_font_ercent_col   = MC_Black,
    .bg_color               = MC_White,
    .border_color           = MC_Black
};

MPlayerStatusBar_CallbackFunc psb_cbf = {
    .get_state_play         = &ayplayer_get_state_play,
    .get_percent_battery    = &ayplayer_get_percent_battery
};

void ayplayer_gui_player_status_bar_creature ( MPlayerStatusBar* psb, MakiseGUI* gui ) {
    m_create_player_status_bar( psb, gui,
                                mp_rel( 0,   0,
                                        128, 12 ),
                                &psb_s,
                                &psb_cbf );
}

void ayplayer_gui_player_status_bar_add_to_container ( MContainer* c, MPlayerStatusBar* psb ) {
    m_player_status_bar_add_to_container( c, psb );
}

extern ayplayer_state ayplayer_control;

uint32_t ayplayer_get_state_play ( void ) {
    return ( uint32_t )ayplayer_control.play_state_get();
}

uint32_t ayplayer_get_percent_battery   ( void ) {
    uint32_t v = ayplayer_control.battery_voltage_mv_get();
    if ( v > 3700 ) v = 3700;
    if ( v < 3400 ) v = 3400;

    uint32_t p = (float)( 100 / 3700 - 3400 ) * (v - 3400);
    return p;
}
