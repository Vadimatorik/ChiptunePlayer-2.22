#include "ff.h"
#include "diskio.h"
#include "user_os.h"
#include "ffconf.h"
#include "microsd_card.h"

extern microsd_spi ayplayer_sd2_obj;

extern "C" {

DWORD get_fattime ( void ) {
	return 0;
}

DSTATUS disk_initialize ( BYTE drv ) {
	if ( drv == 0 ) {
		return ( ayplayer_sd2_obj.initialize() != EC_MICRO_SD_TYPE::ERROR ) ? 0 : STA_NOINIT;
	} else {
		/// Карта по SDIO.
		return RES_ERROR;
	}
}

DSTATUS disk_status ( BYTE pdrv ) {
	if ( pdrv == 0 ) {
		return ( DSTATUS )ayplayer_sd2_obj.send_status();
	} else {
		/// Карта по SDIO.
		return RES_ERROR;
	}
}

DRESULT disk_read ( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
	if ( pdrv == 0 ) {
		for (UINT i = 0; i < count; i++) {	// Считываем нужное количество блоков.
			if ( ayplayer_sd2_obj.read_sector( sector, buff ) != EC_SD_RESULT::OK ) return RES_ERROR;
			sector++;
			buff += 512;
		}
		return RES_OK;
	} else {
		/// Карта по SDIO.
		return RES_ERROR;
	}
}

DRESULT disk_write ( BYTE pdrv, const BYTE* buff, DWORD sector, UINT count ) {
	if ( pdrv == 0 ) {
		for (UINT i = 0; i < count; i++) {
			if ( ayplayer_sd2_obj.write_sector( buff, sector ) != EC_SD_RESULT::OK ) return RES_ERROR;
			sector++;
			buff += 512;
		}
		return RES_OK;
	} else {
		/// Карта по SDIO.
		return RES_ERROR;
	}
}

DRESULT disk_ioctl ( BYTE pdrv, BYTE cmd, void* buff ) {
	( void )pdrv;
	( void )cmd;
	( void )buff;
	return RES_OK;
}

}
