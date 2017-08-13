#include "ayplayer_spi.h"

USER_OS_STATIC_MUTEX_BUFFER mutex_spi_buf[3];

USER_OS_STATIC_MUTEX mutex_spi[3] = { nullptr, nullptr, nullptr };

spi_master_8bit_hardware_os_cfg_t spi1_cfg = {
    .mutex = &mutex_spi[0]
};

spi_master_8bit_hardware_os_cfg_t spi2_cfg = {
    .mutex = &mutex_spi[2]
};

spi_master_8bit_hardware_os_cfg_t spi3_cfg = {
    .mutex = &mutex_spi[3]
};

spi_master_8bit_hardware_os < SPI1_CFG_OBJ_PARAM > spi1( &spi1_cfg );
spi_master_8bit_hardware_os < SPI2_SLOW_CFG_OBJ_PARAM > spi2_slow( &spi2_cfg );
spi_master_8bit_hardware_os < SPI2_FAST_CFG_OBJ_PARAM > spi2_fast( &spi2_cfg );
spi_master_8bit_hardware_os < SPI3_CFG_OBJ_PARAM > spi3( &spi1_cfg );

// Для предотвращения коллизий на SPI шине (из-за дерганья CS).
// На SPI весят сдвиговые регистры для клавиатуры, AY/YM, потенциометры.
// Это дополнительная защита, т.к. иногда, после передачи некторое время нельзя
// отдавать SPI другим устройствам (например, когда программный CS и после
// передачи чип должен еще что-то сделать и дернуть CS сам. В это время нельзя
// совершать иных передач.
USER_OS_STATIC_MUTEX_BUFFER spi3_mutex_buf;
USER_OS_STATIC_MUTEX        spi3_mutex = nullptr;

int ayplayer_spi_init ( void ) {
    mutex_spi[0] = USER_OS_STATIC_MUTEX_CREATE( &mutex_spi_buf[0] );
    mutex_spi[1] = USER_OS_STATIC_MUTEX_CREATE( &mutex_spi_buf[1] );
    mutex_spi[2] = USER_OS_STATIC_MUTEX_CREATE( &mutex_spi_buf[2] );

    spi3_mutex   = USER_OS_STATIC_MUTEX_CREATE( &spi3_mutex_buf );

    spi1.reinit();
    spi3.reinit();

    spi1.on();
    spi3.on();

    return 0;
}
