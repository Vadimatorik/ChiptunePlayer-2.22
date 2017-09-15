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

void ayplayer_gui_player_status_bar_creature ( MContainer* c, MPlayerStatusBar* psb ) {
    m_create_player_status_bar( psb, c,
                                mp_rel( 0,   0,
                                        128, 12 ),
                                &psb_s,
                                &psb_cbf );
}

extern ayplayer_state ayplayer_control;

uint32_t ayplayer_get_state_play ( void ) {
    return ( uint32_t )ayplayer_control.play_state_get();
}


#define AY_PLAYER_BAT_MAX           4.2
#define AY_PLAYER_BAT_MIN           3.5

uint32_t ayplayer_get_percent_battery   ( void ) {
    float v = ayplayer_control.battery_voltage_get();
    if ( v > AY_PLAYER_BAT_MAX ) v = AY_PLAYER_BAT_MAX;
    if ( v < AY_PLAYER_BAT_MIN ) v = AY_PLAYER_BAT_MIN;

    uint32_t p = 100 / ( AY_PLAYER_BAT_MAX - AY_PLAYER_BAT_MIN ) * ( v - AY_PLAYER_BAT_MIN );
    return p;
}
