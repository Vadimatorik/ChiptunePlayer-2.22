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

class arithmetic_mean {
    public:
        arithmetic_mean () {}

        void post_val ( float val ) {
            this->val_counter++;
            if (val_counter == 1) {                    // Фиксируем первый пришедший элемент.
                this->value = val;
                return;
            }
            this->value = (this->value * (this->val_counter - 1) + val) / ((float)this->val_counter);
        }

        float             getMean () {
            return this->value;
        }

        float         get_and_reset () {
            this->val_counter = 0;
            return this->value;
        }

        void reset ( void ) {
            val_counter    = 0;
        }

        void reset_and_post_val ( float val ) {
            this->reset();
            this->post_val(val);
        }

        uint32_t    get_counter () {
            return val_counter;
        }

    private:
        float             value        = 0;
        uint32_t     val_counter    = 0;
};


class ayplayer_state {
public:
    ayplayer_state ( void ) {}
    void play_state_set ( EC_AY_PLAY_STATE state );
    EC_AY_PLAY_STATE play_state_get ( void );               // 0 - stop, 1 -play 2 - pause,

    void active_window_set ( EC_AY_ACTIVE_WINDOW win );
    EC_AY_ACTIVE_WINDOW active_window_get ( void );

    void battery_voltage_set ( float battery_voltage );
    float battery_voltage_get ( void );

private:
    EC_AY_PLAY_STATE        play_state          = EC_AY_PLAY_STATE::STOP;
    EC_AY_ACTIVE_WINDOW     active_window       = EC_AY_ACTIVE_WINDOW::SYSTEM;
    arithmetic_mean         battery_voltage;
};
