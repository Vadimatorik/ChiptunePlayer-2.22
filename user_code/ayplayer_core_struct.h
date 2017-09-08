#pragma once

enum class EC_AY_PLAY_STATE {
    STOP        = 0,
    PLAY        = 1,
    POUSE       = 2
};

class ayplayer_state {
public:
    ayplayer_state ( void ) {}
    void play_state_set ( EC_AY_PLAY_STATE state );
    EC_AY_PLAY_STATE play_state_get ( void );

private:
    EC_AY_PLAY_STATE        play_state = EC_AY_PLAY_STATE::STOP;
};
