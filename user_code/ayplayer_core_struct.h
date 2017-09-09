#pragma once

enum class EC_AY_PLAY_STATE {
    STOP        = 0,
    PLAY        = 1,
    POUSE       = 2
};

enum class EC_AY_ACTIVE_WINDOW {
    MAIN                = 0,
    PLAY_LIST
};

class ayplayer_state {
public:
    ayplayer_state ( void ) {}
    void play_state_set ( EC_AY_PLAY_STATE state );
    EC_AY_PLAY_STATE play_state_get ( void );

    void active_window_set ( EC_AY_ACTIVE_WINDOW win );
    EC_AY_ACTIVE_WINDOW active_window_get ( void );

private:
    EC_AY_PLAY_STATE        play_state          = EC_AY_PLAY_STATE::STOP;
    EC_AY_ACTIVE_WINDOW     active_window       = EC_AY_ACTIVE_WINDOW::MAIN;   // Поменять на main потом.
};
