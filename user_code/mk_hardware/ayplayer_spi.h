#pragma once

#include "ayplayer_os_object.h"
#include "ayplayer_port.h"
#include "spi.h"

extern spi_master_8bit spi1_obj;
extern spi_master_8bit spi2_obj;
extern spi_master_8bit spi3_obj;

int ayplayer_spi_init ( void );
