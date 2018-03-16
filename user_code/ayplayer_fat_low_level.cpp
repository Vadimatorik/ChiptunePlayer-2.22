#include "ff.h"
#include "diskio.h"
#include "user_os.h"
#include "ffconf.h"
#include "microsd_card_spi.h"
#include "microsd_card_sdio.h"

extern microsd_sdio			ayplayer_sd1_obj;
extern microsd_spi			ayplayer_sd2_obj;

microsd_base* ayplayer_sd_obj_array[ 2 ] = {
	&ayplayer_sd1_obj,
	&ayplayer_sd2_obj
};

extern "C" {

DWORD get_fattime ( void ) {
	return 0;
}

DSTATUS disk_initialize ( BYTE pdrv ) {
	return ( ayplayer_sd_obj_array[ pdrv ]->initialize() != EC_MICRO_SD_TYPE::ERROR ) ? 0 : STA_NOINIT;
}

DSTATUS disk_status ( BYTE pdrv ) {
	return ( DSTATUS )ayplayer_sd_obj_array[ pdrv ]->send_status();
}

DRESULT disk_read ( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
	return ( DRESULT )ayplayer_sd_obj_array[ pdrv ]->read_sector( sector, buff, count, 1000 );
}

DRESULT disk_write ( BYTE pdrv, const BYTE* buff, DWORD sector, UINT count ) {
	return ( DRESULT )ayplayer_sd_obj_array[ pdrv ]->write_sector( buff, sector, count, 1000 );
}

DRESULT disk_ioctl ( BYTE pdrv, BYTE cmd, void* buff ) {
	( void )pdrv;
	( void )cmd;
	( void )buff;
	return RES_OK;
}

}
