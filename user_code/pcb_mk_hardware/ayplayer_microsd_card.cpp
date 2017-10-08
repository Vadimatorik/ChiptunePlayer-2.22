#include "ayplayer_microsd_card.h"

microsd_spi_cfg_t microsd_card_cfg = {
    .cs         = &sd2_cs_obj,
    .p_spi_slow = &spi2_slow,
    .p_spi_fast = &spi2_fast
};

microsd_spi sd2( &microsd_card_cfg );

// Проверяет наличие карты в слоте.
// True - карта вставлена.
bool sd2_get_presence_state ( void ) {
    bool r;
    r = sd2_push_obj.read();
    return !r;
}
