#include "ff.h"
#include "diskio.h"
#include "user_os.h"
#include "ffconf.h"
#include "microsd_card_spi.h"
#include "microsd_card_sdio.h"

extern MicrosdSdio			sd1;
extern MicrosdSpi			sd2;

MicrosdBase* sdArray[ 2 ] = {
	&sd1,
	&sd2
};

extern "C" {

DWORD get_fattime ( void ) {
	return 0;
}

DSTATUS disk_initialize ( BYTE pdrv ) {
	return ( sdArray[ pdrv ]->initialize() != EC_MICRO_SD_TYPE::ERROR ) ? 0 : STA_NOINIT;
}

DSTATUS disk_status ( BYTE pdrv ) {
	return ( DSTATUS )sdArray[ pdrv ]->getStatus();
}

DRESULT disk_read ( BYTE pdrv, BYTE* buff, DWORD sector, UINT count ) {
	return ( DRESULT )sdArray[ pdrv ]->readSector( sector, buff, count, 1000 );
}

DRESULT disk_write ( BYTE pdrv, const BYTE* buff, DWORD sector, UINT count ) {
	return ( DRESULT )sdArray[ pdrv ]->writeSector( buff, sector, count, 1000 );
}

DRESULT disk_ioctl ( BYTE pdrv, BYTE cmd, void* buff ) {
	( void )pdrv;
	( void )cmd;
	( void )buff;
	return RES_OK;
}

#if FF_FS_REENTRANT

int ff_cre_syncobj ( BYTE vol,  FF_SYNC_t *sobj ) {
	int ret;
	static FF_SYNC_t								mutex[ FF_VOLUMES ];
	static USER_OS_STATIC_BIN_SEMAPHORE_BUFFER		mutex_buf[ FF_VOLUMES ];
	if (!mutex[vol])
	mutex[vol] = USER_OS_STATIC_MUTEX_CREATE( &mutex_buf[vol] );
	*sobj = mutex[vol];
	ret = (*sobj != NULL);

	return ret;
}

int ff_del_syncobj ( FF_SYNC_t sobj ) {
	( void )sobj;
	USER_OS_STATIC_MUTEX_DELETE(sobj);
	return 1;
}

int ff_req_grant ( FF_SYNC_t sobj ) {
	int ret;
	ret = (USER_OS_TAKE_MUTEX( sobj, FF_FS_TIMEOUT ) == pdTRUE);
	return ret;
}

void ff_rel_grant ( FF_SYNC_t sobj ) {
	USER_OS_GIVE_MUTEX(sobj);
}

#endif

}
