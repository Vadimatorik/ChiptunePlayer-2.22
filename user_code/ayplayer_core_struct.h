#pragma once

#include <stdint.h>

enum class EC_AY_PLAY_STATE {
    STOP        = 0,
    PLAY        = 1,
    POUSE       = 2
};

enum class EC_AY_ACTIVE_WINDOW {
    MAIN                = 0,                // Окно с текущим треком.
    PLAY_LIST,                              // Список треков на карте.
    SYSTEM                                  // Системное окно с предупреждениями.
};

class ayplayer_state {
public:
    ayplayer_state ( void ) {}
    void play_state_set ( EC_AY_PLAY_STATE state );
    EC_AY_PLAY_STATE play_state_get ( void );

    void active_window_set ( EC_AY_ACTIVE_WINDOW win );
    EC_AY_ACTIVE_WINDOW active_window_get ( void );

    void battery_voltage_mv_set ( uint32_t battery_voltage_mv );
    uint32_t battery_voltage_mv_get ( void );

private:
    EC_AY_PLAY_STATE        play_state          = EC_AY_PLAY_STATE::STOP;
    EC_AY_ACTIVE_WINDOW     active_window       = EC_AY_ACTIVE_WINDOW::SYSTEM;
    uint32_t                battery_voltage_mv  = 0;
};
